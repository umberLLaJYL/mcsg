#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <map>

#include <unistd.h>
#include <fcntl.h>

// using namespace rapidjson;

#define GPIODir "/sys/class/gpio/gpio/direction"
#define PinAct(action) GPIODir#action

bool func(int i)
{
    bool b = false;
    return !(i < 0) && b;
}


class Test {
private:
    std::string str;
    std::map<std::string, std::string> table;

public:
    Test(/* args */) {
        this->str = "asdf";
        this->table.insert({"bb", "dd"});
    }
    ~Test() { }

    virtual void function() = 0;

    // template<class Controller>
    // Controller &bind() {
    //     return this->str;
    // }

    // const Test1 &operator = (const Test1 &) {
        
    // }
};


class Test1 : public Test {
private:
    /* data */
public:
    Test1(/* args */) { }
    ~Test1() { }

    void function() override {
        std::cout << "Ddda" << std::endl;
    }

};

class Test2: public Test {
private:
    /* data */
public:
    Test2(/* args */) { }
    ~Test2() { }

    void function() override {
        std::cout << "ssssa" << std::endl;
    }

    void function2() {

    }
};

int main(int argc, char *argv[])
{
    std::string str(GPIODir);

    if(func(1))
        printf("aaa\n");

    // if(1 && func(1))
    //     printf("bbb\n");

    // if(write(fd, "88", 8) < 0)
    //     perror("w");

    // ofs << "88";

    // str = test.bind<std::string>();

    // printf("i: %s\n", str.c_str());

    // while(1) {
    //     ++i;
    //     sleep(2);
    //     if(i > 5)
    //         break;
    //     fsw.execute("seq-pri");
    //     printf("0x%04x\n", fsw["ready"]);
    //     sleep(2);
    //     fsw.execute("seq-res");
    //     printf("0x%04x\n", fsw["ready"]);
    // }

    return 0;
}
