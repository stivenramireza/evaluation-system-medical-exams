#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>
#include <semaphore.h>

#include "init_command.h"
#include "thread_info.h"
//Read all the commands 

static void* input_thread(void * info);

void command_init(char* commands[], int length){
    int i=5, ie=6, oe=10, b=100, d=100, s=100, q=6;
    string n = "evaluator";
    if (length == 2){
    }
    else if(length%2 != 0){
        cerr<<"command invalid\n";
        exit(EXIT_FAILURE);
    }
    else{
        for(int it=2; it<length; it+=2){
            if(strcmp(commands[it],"-i") == 0){
                i = atoi(commands[it+1]);
                if(i <= 0){
                    cerr<<"-i <integer>"<<endl;
                    exit(EXIT_FAILURE);
                }
            }
            else if(strcmp(commands[it],"-ie")==0){
                ie = atoi(commands[it+1]);
                if(ie <= 0){
                    cerr<<"-ie <integer>"<<endl;
                    exit(EXIT_FAILURE);
                }
            }
            else if(strcmp(commands[it],"-oe")==0){
                oe = atoi(commands[it+1]);
                if(oe <= 0){
                    cerr<<"-oe <integer>"<<endl;
                    exit(EXIT_FAILURE);
                }
            }
            else if(strcmp(commands[it],"-n")==0){
                n = commands[it+1];
            }
            else if(strcmp(commands[it],"-b")==0){
                b = atoi(commands[it+1]);
                if(b <= 0){
                    cerr<<"-b <integer>"<<endl;
                    exit(EXIT_FAILURE);
                }
            }
            else if(strcmp(commands[it],"-d")==0){
                d = atoi(commands[it+1]);
                if(d <= 0){
                    cerr<<"-d <integer>"<<endl;
                    exit(EXIT_FAILURE);
                }
            }
            else if(strcmp(commands[it],"-s")==0){
                s = atoi(commands[it+1]);
                if(s <= 0){
                    cerr<<"-s <integer>"<<endl;
                    exit(EXIT_FAILURE);
                }
            }
            else if(strcmp(commands[it],"-q")==0){
                q = atoi(commands[it+1]);
                if(q <= 0){
                    cerr<<"-q <integer>"<<endl;
                    exit(EXIT_FAILURE);
                }
            }
        }
    }

    //Create the shared memory  and initialice all the values
    int fd = shm_open(n.c_str(), O_RDWR | O_CREAT | O_EXCL, 0660);
    if (fd < 0) {
        cerr << "Error creando la memoria compartida: "<< endl;
        exit(EXIT_FAILURE);
    }

    int size_head =  sizeof(struct head);
    int size_exam =  sizeof(struct exam);
    
    int size_memory = size_head + i*ie*size_exam + oe*size_exam + q*3*size_exam + sizeof(int)*3*i; 
    if (ftruncate(fd, size_memory) != 0) {
        cerr << "Error creando la memoria compartida: "
	    << errno << strerror(errno) << endl;
        exit(EXIT_FAILURE);
  }

    void *dir;
    if ((dir = mmap(NULL, size_head, PROT_READ | PROT_WRITE, MAP_SHARED,
		fd, 0)) == MAP_FAILED) {
        cerr << "Error mapeando la memoria compartida: "
	    << errno << strerror(errno) << endl;
        exit(EXIT_FAILURE);
    }

    head *pHead = (head * )dir;
    pHead->_uuid = 0;
    pHead->i = i;
    pHead->ie = ie;
    pHead->oe = oe;
    pHead->b = b;
    pHead->d = d;
    pHead->s = s;
    pHead->q = q;
    pHead->first_exit = 0;
    pHead->end_exit = 0;
    pHead->first_b = 0;
    pHead->end_b = 0;
    pHead->first_d = 0;
    pHead->end_d = 0;
    pHead->first_s = 0;
    pHead->end_s = 0;
    pHead->stop = false;

    pthread_t* inputs_threads = new pthread_t[i];

    sem_t **_b = new sem_t*[3];
    _b[0] = sem_open((n+"_inter_b_mutex").c_str() ,O_CREAT | O_EXCL, 0660, 1);
    _b[1] = sem_open((n+"_inter_b_empty").c_str() ,O_CREAT | O_EXCL, 0660, q);
    _b[2] = sem_open((n+"_inter_b_full" ).c_str() ,O_CREAT | O_EXCL, 0660, 0);
    sem_t **_d = new sem_t*[3];
    _d[0] = sem_open((n+"_inter_d_mutex").c_str() ,O_CREAT | O_EXCL, 0660, 1);
    _d[1] = sem_open((n+"_inter_d_empty").c_str() ,O_CREAT | O_EXCL, 0660, q);
    _d[2] = sem_open((n+"_inter_d_full").c_str()  ,O_CREAT | O_EXCL, 0660, 0);
    
    sem_t **_s = new sem_t*[3];
    _s[0] = sem_open((n+"_inter_s_mutex").c_str(),O_CREAT | O_EXCL, 0660, 1);
    _s[1] = sem_open((n+"_inter_s_empty").c_str(),O_CREAT | O_EXCL, 0660, q);
    _s[2] = sem_open((n+"_inter_s_full").c_str() ,O_CREAT | O_EXCL, 0660, 0);
    
    for(int it = 0; it<i; it++){
        string sem_name_mutex = n + "_input_" + to_string(it).c_str() + "_mutex";
        string sem_name_empty = n + "_input_" + to_string(it).c_str() + "_empty";
        string sem_name_full  = n + "_input_" + to_string(it).c_str() + "_fulls"; 
        sem_t *mutex = sem_open(sem_name_mutex.c_str(), O_CREAT | O_EXCL, 0660,1); 
        sem_t *empty = sem_open(sem_name_empty.c_str(), O_CREAT | O_EXCL, 0660, ie);
        sem_t *full =  sem_open(sem_name_full.c_str(),  O_CREAT | O_EXCL, 0660, 0);
        Input_info* info = new Input_info(it , dir , mutex , full , empty , _b , _d , _s);
        pthread_create(&inputs_threads[it],NULL,input_thread,(void *) info);
    }
    pthread_join(inputs_threads[0],NULL);
}

static void* input_thread(void *input){
    int head_size = sizeof(head);
    int exam_size = sizeof(exam);
    Input_info* info = (Input_info*) input;
    char* init_pos = (char *)info->init_dir;
    head* phead = (head *)init_pos;
    int input_number = info->input;
    int length_array = phead->ie;
    int *last  = (int *)(init_pos + head_size + length_array*(phead->i)*exam_size + phead->oe*exam_size + 3*(phead->q)*exam_size + phead->i*sizeof(int) + input_number*sizeof(int));
    int *qua  = (int *)(init_pos + head_size + length_array*(phead->i)*exam_size  + phead->oe*exam_size + 3*(phead->q)*exam_size + 2*(phead->i*sizeof(int)) + input_number*sizeof(int));
    sem_t *mutex = info->mutex;
    sem_t *empty = info->empty;
    sem_t *full  = info->full;
    sem_t** b = info->b;
    sem_t** d = info->d;
    sem_t** s = info->s;
    char *input_array = init_pos + head_size + input_number*length_array*exam_size;
    char *dir_b = (char *)(init_pos + head_size + length_array*(phead->i)*exam_size + phead->oe*exam_size);
    char *dir_d = (char *)(init_pos + head_size + length_array*(phead->i)*exam_size + phead->oe*exam_size + (phead->q)*exam_size);
    char *dir_s = (char *)(init_pos + head_size + length_array*(phead->i)*exam_size + phead->oe*exam_size + 2*(phead->q)*exam_size);
    exam current_exam;
    exam *pinter_q;
    while(!phead->stop){
        sem_wait(full);
        sem_wait(mutex);
        current_exam = *((exam *) (input_array + *last*exam_size));
        *last = (*last + 1) % length_array;
        *qua = *qua-1;
        char type = current_exam.type;
        if(type == 'B'){
            sem_wait(b[1]);
            sem_wait(b[0]);
            pinter_q = (exam *)(dir_b + (phead->end_b)*exam_size);
            *pinter_q = current_exam;
            phead->end_b = (phead->end_b + 1)%(phead->q);
            phead->qua_b++; 
            sem_post(b[0]);
            sem_post(b[2]);
        }
        else if(type == 'D'){
            sem_wait(d[1]);
            sem_wait(d[0]);
            pinter_q = (exam *)(dir_d + (phead->end_d)*exam_size);
            *pinter_q = current_exam;
            phead->end_d = (phead->end_d + 1)%(phead->q);
            phead->qua_d++;
            sem_post(d[0]);
            sem_post(d[2]);
        }
        else if(type == 'S'){
            sem_wait(s[1]);
            sem_wait(s[0]);
            pinter_q = (exam *)(dir_s + (phead->end_s)*exam_size);
            *pinter_q = current_exam;
            phead->end_s = (phead->end_s + 1)%(phead->q);
            phead->qua_s++;
            sem_post(s[0]);
            sem_post(s[2]);
        }
        sem_post(mutex);
        sem_post(empty);
    }
    return NULL;
}   
