#include <vector>
#include <cstring>
#include "share_memory.h"
#include <semaphore.h>
using namespace std;

class RegistratorCommand {
    public:
        RegistratorCommand(char ** args, int length);
        void start();
    private:
        void put_sample(int _queue, char _type, int _quant);
        void usage();
        void interactive();
        void files(int _from, char ** _files, int _to);
        vector<sem_t *> reg_sems_mutex;
        vector<sem_t *> reg_sems_fulls;
        vector<sem_t *> reg_sems_empty;
        vector<int> out;
        vector<int> in;
        string _mem_name;
        int _length = 0;
        int fd = -1;
        void * dir;
        bool _int;
        int _from, _to;
        char ** _args;
};