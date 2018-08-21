#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdint.h>
// #include <pthread.h>
#include <getopt.h>

#include <vector>
#include <cstddef>
#include <iostream>
using namespace std;
#include <string>

// #define container_of(ptr, type, member)({ \
//             const typeof(((type *)0)->member) *__mptr = (ptr); \
//             (type *)((char *)__mptr - offsetof(type, member)); \
//         })
// #define container_of(ptr, type, member) ({                      \
//         const typeof( ((type *)0)->member ) *__mptr = (ptr);    \
//         (type *)( (char *)__mptr - __offsetof(type,member) );})





class Control {
private:

public:
    Control(/* args */);
    virtual ~Control();

    virtual int execute() = 0;
};

Control::Control(/* args */)
{

}

Control::~Control()
{

}



class Pd : public Control {
private:
    
public:
    Pd(/* args */);
    ~Pd();

    int execute() override;
};

Pd::Pd(/* args */)
{
    cout << "Pd has been created: "  << endl;
}

Pd::~Pd()
{
    cout << "Pd has been deleted: "  << endl;
}

int Pd::execute()
{
    return 0;
}




class Device {
private:
    Pd *pd = new Pd;
public:
    Device(const string &s);
    virtual ~Device();
};

Device::Device(const string &conf)
{
    cout << "device has been created: " << conf << endl;
}

Device::~Device()
{
    delete pd;
    cout << "device has been deleted" << endl;
}





int main(int argc, char *argv[])
{
    // struct logopt logoption, *teststr;
    // static struct option options[] = {
    //     {"default", 2, NULL, 'a'},
    //     {"tcponly", 2, NULL, 'b'}
    // };

    Device *dev = new Device("mpdev");
    delete(dev);

    string s, s1 = "zsljds";
    decltype(s) s2 = "decltype";

    cout << s2 << endl;

    for(char c : s1)
        cout << c << endl;

    while(getline(cin, s)){
        if(s == "quit")
            return 0;
        if(!s.empty())
            cout << "cin rcv: " << s + ", len: " << s.size() << endl;
    }


    // printf("argc: %d\n", argc);

    // for(i = 0; i < argc; i++)
    //     printf("argv%i: %s\n", i, argv[i]);

    // while((opt = getopt_long(argc, argv, "cd:e::", options, NULL)) != -1){
    //     switch(opt){
    //         case 'a':{
    //             break;
    //         }
    //         case 'b':{
    //             printf("b arg: %s, ind: %d, opt: %d\n", optarg, optind, optopt);
    //             break;
    //         }
    //         case 'c':{
    //             printf("c arg: %s, ind: %d, opt: %d\n", optarg, optind, optopt);
    //             break;
    //         }
    //         case 'd':{
    //             strncpy(logoption.lo_addr, optarg, strlen(optarg) - strlen(strchr(optarg, ':')));
    //             printf("d arg: %s, ind: %d, opt: %d\n", optarg, optind, optopt);
    //             printf("%s\n", logoption.lo_addr);
    //             port = strrchr(optarg, ':');
    //             printf("%d\n", atoi(++port));
    //             break;
    //         }
    //         case 'e':{
    //             printf("e arg: %s, ind: %d, opt: %d\n", optarg, optind, optopt);
    //             break;
    //         }
    //         default: printf("Usage: \n");break;
    //     }
    // }

    return 0;
}
