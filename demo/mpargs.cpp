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

#include <sys/un.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <vector>
#include <cstddef>
#include <cstdio>
// using namespace std;
#include <string>
#include <iostream>
#include <fstream>

#include "../src/library/json/rapidjson/rapidjson.h"
#include "../src/library/json/rapidjson/document.h"
#include "../src/library/json/rapidjson/pointer.h"
#include "../src/library/json/rapidjson/stringbuffer.h"
#include "../src/library/json/rapidjson/writer.h"
#include "../src/library/json/rapidjson/prettywriter.h"
#include "../src/library/json/rapidjson/filereadstream.h"
#include "../src/library/json/rapidjson/filewritestream.h"

using namespace rapidjson;



class test : public std::fstream{

    const std::string prefix;

private:
    std::string identity;

public:
    test(const std::string &);
    ~test();

    const std::string &getIdentity() const {
        return this->identity;
    }
};

test::test(const std::string &name) : prefix("test")
{
    char buf[4096];
    identity = name;

    this->open(prefix+identity);
    this->read(buf, 4096);
    std::cout << buf << std::endl;
}

test::~test()
{
}



class a
{
private:
    /* data */
    int head;
public:
    a(int b) : head(b) {
        std::cout << "aaaa" << std::endl;
    }
    ~a();

    bool operator == (int ret) const {
        if (this->head == ret)
            return true;
        return false;
    }

    bool operator == (const a *ret) const {
        if (this != ret)
            return NULL;
    }
};

a::~a()
{
}

class b : public a {
public:
    b() : a::a(8) {
        std::cout << "aaaa" << std::endl;
    }
    ~b();
};




int main(int argc, char *argv[])
{
    // struct logopt logoption, *teststr;
    // static struct option options[] = {
    //     {"default", 2, NULL, 'a'},
    //     {"tcponly", 2, NULL, 'b'}
    // };
    char buf[4096];
    StringBuffer sbuf;

    char str[4096];
    std::string strbuf;

    FILE *fp;

    
    Document doc;
    Document::AllocatorType &allocator = doc.GetAllocator();
    doc.SetObject();

    doc.AddMember("a1", "b1", allocator);
    doc.AddMember("a2", "b2", allocator);
    doc.AddMember("a3", "b3", allocator);



    PrettyWriter<StringBuffer> pretty_writer(sbuf);
    pretty_writer.SetMaxDecimalPlaces(4);
    doc.Accept(pretty_writer);

    std::cout << sbuf.GetString() << std::endl;

    std::ofstream fout("b.json");
    fout << sbuf.GetString();
    fout.close();

    // sprintf(str, "abcdefghijklmnopqrstuvwxyz\n");

    a aaa(9);

    if(aaa == 9)
        std::cout << "null" << std::endl;


    // vector<string> sss{"aaa", "bbb", "ccc"};

    // cout << sss.size() << endl;

    // for(char c : s1)
    //     cout << c << endl;

    // while(getline(cin, s)){
    //     if(s == "quit")
    //         return 0;
    //     if(!s.empty())
    //         cout << "cin rcv: " << s + ", len: " << s.size() << endl;
    // }


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
