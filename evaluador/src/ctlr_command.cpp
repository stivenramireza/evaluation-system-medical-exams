#include "ctlr_command.h"

void command_ctlr(char* commands[], int length){
    char *n = (char*)"evaluator";
    string line;
    if (length == 2){
    }
    else if(length%2 != 0){
        cerr<<"command invalid\n";
        exit(EXIT_FAILURE);
    }else{
        for(int it=2; it<length; it+=2){
            if(strcmp(commands[it],"-n")==0){
                n = commands[it+1]; 
            }
        }
    }
    while(!cin.eof()){
           cout << "> ";
           getline(cin, line);
           stringstream ss(line);
           string arguments[3];
           ss >> arguments[0] >> arguments[1] >> arguments[2];
           if(arguments[0] == "list"){
               if(arguments[1] != ""){
                   subcommand_list(n, arguments[1]);
               }else{
                   cerr << "Usage: \nlist [ processing | waiting | reported | reactive | all ]\n";
                   exit(EXIT_FAILURE);
               }
           }else if(arguments[0] == "update"){
               if(arguments[1] != "" && arguments[2] != ""){
                   subcommand_update(n, arguments[1], arguments[2]);
               }else{
                   cerr << "Usage: update { B | D | S } <integer>\n";
                   exit(EXIT_FAILURE);
               }
           }else{
               cerr << "Subcommand invalid\n";
                exit(EXIT_FAILURE);
           }
    }
}

/** Subcomando list */
void subcommand_list(char* name_memory, string interactive_subcommand){
    if(interactive_subcommand == "processing"){
        subcommand_processing(name_memory);
    }else if(interactive_subcommand == "waiting"){
        subcommand_waiting(name_memory);
    }else if(interactive_subcommand == "reported"){
        subcommand_reported(name_memory);
    }else if(interactive_subcommand == "reactive"){
        subcommand_reactive(name_memory);
    }else if(interactive_subcommand == "all"){
        subcommand_all(name_memory);
    }else{
        cerr << "Subcommand invalid\n";
        exit(EXIT_FAILURE);
    }
}

void subcommand_processing(char* name_memory){
    int fd = shm_open(name_memory, O_RDWR, 0660);
    void *dir = mmap(NULL, sizeof(struct head), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    head *phead = (head *) dir;
    int _ie_ = phead->ie;
    int _i_ =  phead->i;
    int _q_ =  phead->q;
    int _oe_ = phead->oe;
    int exam_size = sizeof(struct exam);
    int size_head =  sizeof(struct head);
    char* inputs_dirs = (char *)dir + size_head;
  
    int qua_1 = phead->qua_b;
    int cont_1 = phead->first_b;
    while(cont_1 != phead->end_b || qua_1 > 0){
        exam *_exam = (exam *) (inputs_dirs + (_ie_ * _i_ * exam_size) + _oe_*exam_size + (cont_1 * exam_size));
        time(&_exam->t_end);
        double seconds = difftime(_exam->t_end, _exam->t_start);
        cout << "Processing:\n";
        cout << _exam->id << " " << _exam->_queue << " " << _exam->type << " " << _exam->_quant << " " << seconds << endl;
        cont_1 = (cont_1 + 1) % _q_;
        qua_1--;
    }
    int qua_2 = phead->qua_d;
    int cont_2 = phead->first_d;
    while(cont_2 != phead->end_d || qua_2 > 0){
        exam *_exam = (exam *) (inputs_dirs + (_ie_ * _i_ * exam_size) + _oe_*exam_size + (cont_2 * exam_size) + _q_*exam_size);
        time(&_exam->t_end);
        double seconds = difftime(_exam->t_end, _exam->t_start);
        cout << "Processing:\n";
        cout << _exam->id << " " << _exam->_queue << " " << _exam->type << " " << _exam->_quant << " " << seconds<< endl;
        cont_2 = (cont_2 + 1) % _q_;
        qua_2--;
    }   
    int qua_3 = phead->qua_s;
    int cont_3 = phead->first_s;
    while(cont_3 != phead->end_s || qua_3 > 0){
        exam *_exam = (exam *) (inputs_dirs + (_ie_ * _i_ * exam_size) + _oe_*exam_size + (cont_3* exam_size) + 2*_q_*exam_size);
        time(&_exam->t_end);
        double seconds = difftime(_exam->t_end, _exam->t_start);
        cout << "Processing:\n";
        cout << _exam->id << " " << _exam->_queue << " " << _exam->type << " " << _exam->_quant << " " << seconds << endl;
        cont_3 = (cont_3 + 1) % _q_;
        qua_3--;
    }
}

void subcommand_waiting(char* name_memory){
    int fd = shm_open(name_memory, O_RDWR, 0660);
    void *dir = mmap(NULL, sizeof(struct head), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    head *phead = (head *) dir;
    int _ie_ = phead->ie;
    int _i_ =  phead->i;
    int _q_ =  phead->q;
    int _oe_ = phead->oe;
    int exam_size = sizeof(struct exam);
    int size_head =  sizeof(struct head);
    char* inputs_dirs = (char *)dir + size_head;
    for(int _queue = 0; _queue < _i_ ; _queue++){
        int *in = (int *)(inputs_dirs + _i_ * _ie_ * exam_size + _oe_*exam_size + 3 * _q_ * exam_size + _queue * sizeof(int));
        int *last  = (int *)(inputs_dirs + _ie_*_i_*exam_size + _oe_*exam_size + 3*_q_*exam_size + _i_*sizeof(int) + _queue*sizeof(int));
        int *quantum = (int *)(inputs_dirs + _i_ * _ie_ * exam_size + _oe_*exam_size + 3 * _q_ * exam_size + _i_ * sizeof(int) + _i_ * sizeof(int) + _queue * sizeof(int));
        int first = *last;
        int ultimate = *in;
        int cantidad = *quantum;
        while(first != ultimate || cantidad > 0){
            exam *_exam = (exam *) (inputs_dirs + (_ie_ * _queue * exam_size) + (first * exam_size));
            cout << "Waiting:\n";
            cout << _exam->id << " " << _exam->_queue << " " << _exam->type << " " << _exam->_quant << endl;
            first = (first + 1) % _ie_;
            cantidad--;
        }
    }
}

void subcommand_reported(char* name_memory){
    int fd = shm_open(name_memory, O_RDWR, 0660);
    void *dir = mmap(NULL, sizeof(struct head), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    head *phead = (head *) dir;
    int _ie_ = phead->ie;
    int _i_ =  phead->i;
    int _q_ =  phead->q;
    int _oe_ = phead->oe;
    int exam_size = sizeof(struct exam);
    int size_head =  sizeof(struct head);
    char* inputs_dirs = (char *)dir + size_head;
    int in = phead->first_o;
    int last  = phead->end_o;
    int quantum = phead->qua_o;
    while(in != last || quantum > 0){
        exam *_exam = (exam *) (inputs_dirs + (_ie_ * _i_ * exam_size) + (in * exam_size));
        cout << "Reported:\n";
        char state;
        if(_exam->_state <= 15){
            state = '?';
        }else if(_exam->_state <= 35){
            state = 'N';
        }else{
            state = 'P';
        }
        cout << _exam->id << " " << _exam->_queue << " " << _exam->type << " " << state << endl;
        in = (in + 1) % _oe_;
        quantum--;
    }
}

void subcommand_reactive(char* name_memory){
    int fd = shm_open(name_memory, O_RDWR, 0660);
    void *dir = mmap(NULL, sizeof(struct head), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    head *phead = (head *) dir;
    int _b = phead->b;
    int _d = phead->d;
    int _s = phead->s;
    cout << _b << " " << _d << " " << _s << endl;
}

void subcommand_all(char* name_memory){
    subcommand_processing(name_memory);
    subcommand_waiting(name_memory);
    subcommand_reported(name_memory);
    subcommand_reactive(name_memory);
}

/** Subcomando update */
void subcommand_update(char* name_memory, string reactive, string reactive_level){
    if(reactive == "B" || reactive == "D" || reactive == "S"){
        if(reactive_level != ""){
            cout << "name_memory: " << name_memory;
            update_reactive(reactive, stoi(reactive_level));
        }else{
            cerr<<"subcommand invalid\n";
            exit(EXIT_FAILURE);
        }
    }else{
        cerr<<"subcommand invalid\n";
        exit(EXIT_FAILURE);
    }
}

void update_reactive(string reactive, int reactive_level){
    cout << " reactive: " << reactive << " <integer>: " << reactive_level << endl;
}