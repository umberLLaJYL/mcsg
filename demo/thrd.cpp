#include <sys/types.h>
#include <sys/wait.h>
#include <sys/un.h>
#include <stdint.h>
#include <time.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <sys/types.h>
#include <errno.h>
#include <stdint.h>
#include <fcntl.h>
#include <sys/select.h>

// #include <pthread.h>


#include <thread>
#include <vector>
#include <cstddef>
using namespace std;
#include <string>
#include <iostream>
#include <fstream>
#include <map>



class thrd {

private:
    int a;

    static int group[10];

    thread sthrd;

    static void fthrd1(const string &);
    void fthrd2(int);
    
public:
    thrd(/* args */);
    ~thrd();

    void start() {
        thread::id idx;

        thread lthrd(&thrd::fthrd1, "ajfj");

        idx = lthrd.get_id();
        cout << "lthrd: " << idx << endl;

        lthrd.swap(sthrd);

        idx = thrd::sthrd.get_id();
        cout << "sthrd: " << idx << endl;
    }

    void join() {
        sthrd.join();
    }

    void add() {
        group[0] = a;
    }
};

thrd::thrd(/* args */)
{

}

thrd::~thrd()
{
}

void thrd::fthrd1(const string &s)
{
    int i = 0;

    int sock = socket(AF_LOCAL, SOCK_STREAM, 0);

    while(i < 10){
        ++i;
        cout << "thrd1: " << i << ", " << s << endl;
        sleep(1);
    }
}

void thrd::fthrd2(int a)
{
    int i = 0;

    while(i < 20){
        ++i;
        cout << "thrd1: " << i << ", " << a << endl;
        sleep(1);
    }
}


void a(const string &s)
{
    cout << "thrd a: " << s << endl;
}


int main(int argc, char const *argv[])
{
    thrd *th = new thrd;

    // thread thrdd(a, "ssss");
    
    th->start();

    th->join();

    delete(th);
    // thrdd.join();

    cout << "main" << endl;

    return 0;
}

