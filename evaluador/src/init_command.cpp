#include "init_command.h"
//Read all the commands 
void command_init(char* commands[], int* length){
    int i=5, ie=6, oe=10, b=100, d=100, s=100, q=6;
    char *n = (char*)"evaluator";
    if (*length == 2){
    }
    else if(*length%2 != 0){
        cerr<<"command invalid\n";
        exit(EXIT_FAILURE);
    }
    else{
        for(int it=2; it<*length; it+=2){
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
    int fd = shm_open(n, O_RDWR | O_CREAT | O_EXCL, 0660);
    if (fd < 0) {
        cerr << "Error creando la memoria compartida: "<< endl;
        exit(EXIT_FAILURE);
    }

    int size_head =  sizeof(struct head);
    int size_exam =  sizeof(struct exam);

    cout<<size_head <<endl;
    if (ftruncate(fd, size_head + i*ie*size_exam) != 0) {
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
    cout<<"Head"<<endl;
    pHead->i = i;
    pHead->ie = ie; 
    cout<<(pHead->i)<<endl;
    cout<<pHead<<endl;
    cout<<dir<<endl;

    cout<<"Examen"<<endl;
    exam* pExam;
    char* dir_entradas = (char *)dir + size_head;
    for(int it=0; it<i; it++){
        for(int it2=0; it2<ie; it2++){
            pExam = (exam *)(dir_entradas + it*i*size_exam + it2*size_exam);
            pExam->id = 1000*it + it2;
            cout<<&(pExam->id)<<endl<<pExam->id<<endl;
        }
    }
    for(int it=0; it<oe; it++){
            pExam = (exam *)(dir_entradas + it*size_exam);
            cout<<pExam<<endl;
            pExam->id = 100*it;
            cout<<&(pExam->id)<<endl<<pExam->id<<endl;
            
    }
    close(fd);
}