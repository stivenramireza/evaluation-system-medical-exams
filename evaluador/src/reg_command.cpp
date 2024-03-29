#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <cstring>
#include <cstdio>
#include <string>
#include "reg_command.h"
#include "share_memory.h"

using namespace std;

RegistratorCommand::RegistratorCommand(char ** args, int length): _int(false){
    _length = length;
    _mem_name = "evaluator";
    if(length < 3){
        usage();
        exit(EXIT_FAILURE);
    }
    if(strcmp(args[2], "-n") == 0){
        _mem_name = args[3];
        if(length < 5){
            usage();
            exit(EXIT_FAILURE);
        }else{
            if(strcmp(args[4], "-") == 0){
                //RegistratorCommand::interactive();
                _int = true;
            }else{
                //RegistratorCommand::files(3, args, length);
                _int = false;
                _from = 3, _to = length;
                _args = args;
            }
        }
    }else if(strcmp(args[2],"-") == 0){
        // ... Interactivo .....
        _int = true;
    }else{
        // ... Ficheros .....
        //files(2, args, length);
        _int = false;
        _from = 2, _to = length, _args = args;
    }
    fd = shm_open(_mem_name.c_str(), O_RDWR, 0660);
    dir = mmap(NULL, sizeof(struct head), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    head *phead = (head *) dir;
    for(int i = 0; i < phead->i; ++i){
        // name_input_1_mutex
        // name_input_1_fulls
        // name_input_1_empty
        string mutex_name = _mem_name + "_input_" + to_string(i).c_str() + "_mutex";
        string fulls_name = _mem_name + "_input_" + to_string(i).c_str() + "_fulls";
        string empty_name = _mem_name + "_input_" + to_string(i).c_str() + "_empty";
        sem_t * new_sem_mutex = sem_open(mutex_name.c_str(), 0);
        sem_t * new_sem_fulls = sem_open(fulls_name.c_str(), 0);
        sem_t * new_sem_empty = sem_open(empty_name.c_str(), 0);
        reg_sems_mutex.push_back(new_sem_mutex);
        reg_sems_fulls.push_back(new_sem_fulls);
        reg_sems_empty.push_back(new_sem_empty);
    }
}
void RegistratorCommand::put_sample(int _queue, char ntype, int _quantity, FILE * f, bool file=false){
    //fd = shm_open(_mem_name.c_str(), O_RDWR, 0660);
    //dir = mmap(NULL, sizeof(struct head), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    head *phead = (head *) dir;
    int _ie_ = phead->ie;
    int _i_ =  phead->i;
    int _q_ =  phead->q;
    int _oe_ = phead->oe;
    int _uuid = phead->_uuid;
    int exam_size = sizeof(struct exam);
    int size_head =  sizeof(struct head);
    char* inputs_dirs = (char *)dir + size_head;
    _uuid = _uuid + 1;
    phead->_uuid = _uuid;
    sem_wait(reg_sems_empty[_queue]);
    sem_wait(reg_sems_mutex[_queue]);
    int *in = (int *)(inputs_dirs + _i_ * _ie_ * exam_size + _oe_*exam_size + 3 * _q_ * exam_size + _queue * sizeof(int));
    int *quantum = (int *)(inputs_dirs + _i_ * _ie_ * exam_size + _oe_*exam_size + 3 * _q_ * exam_size + _i_ * sizeof(int) + _i_ * sizeof(int) + _queue * sizeof(int));
    //cerr << *in << endl;
    exam *_exam = (exam *) (inputs_dirs + (_ie_ * _queue * exam_size) + (*in * exam_size));
    *in = (*in + 1) % _ie_;
    *quantum = *quantum + 1;
    if(file){
        fprintf(f, "id = %d\n", _uuid);
    }else{
        printf("id = %d\n", _uuid);
    }
    _exam->id = _uuid;
    _exam->_queue = _queue;
    _exam->_quant = _quantity;
    _exam->type = ntype;
    //cout << "Añadiendo " << _exam->id << " " << _exam << " " << _exam->_queue << " " << *in << endl;
    sem_post(reg_sems_mutex[_queue]);
    sem_post(reg_sems_fulls[_queue]);
}
void RegistratorCommand::usage(){
    
    printf("Usage: evaluator reg [-n string] {{file} | ... }\n");
}
void RegistratorCommand::files(int from, char ** files, int to){

    for(int i = from; i < to; ++i){
        FILE * f = fopen(files[i], "r");
        string fname = files[i];
        size_t found = fname.rfind(".");
        if(found == string::npos){
            fname += ".spl"; 
        }else{
            fname.replace(found, fname.size(), ".spl");
        }
        FILE * fout = fopen(fname.c_str(), "w");
        char t;
        int qq, hm;
        while(fscanf(f, "%d %c %d", &qq, &t, &hm) != EOF){
            put_sample(qq, t, hm, fout, true);
            //printf("%d %c %d\n", qq, t, hm);
        }
        fclose(f);
        fclose(fout);
    }
}
void RegistratorCommand::interactive(){
    printf("> ");
    char t;
    int qq, hm;
    FILE * f = nullptr;
    while(scanf("%d %c %d", &qq, &t, &hm) != EOF){
        put_sample(qq, t, hm, f);
        printf("> ");
    }
    printf("\n");
}

void RegistratorCommand::start(){
    if(_int){
        interactive();
    }else{
        files(_from, _args, _to);
    }
}