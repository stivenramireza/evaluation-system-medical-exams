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
    cout << "name_memory: " << name_memory << endl;
    cout << "Processing:\n";
    cout << "[id i k q p\n]\n";
}

void subcommand_waiting(char* name_memory){
    cout << "name_memory: " << name_memory << endl;
    
    cout << "Waiting:\n";
    cout << "[id i k q\n]\n";
}

void subcommand_reported(char* name_memory){
    cout << "name_memory: " << name_memory << endl;
    cout << "Reported:\n";
    cout << "[id i k r\n]\n";
}

void subcommand_reactive(char* name_memory){
    cout << "name_memory: " << name_memory << endl;
    cout << 100 << endl;;
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