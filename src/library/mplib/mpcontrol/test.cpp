#include "control.h"
#include "../../json/rapidjson/document.h"

using namespace rapidjson;

int main(int argc, char *argv[])
{
    int i = 0;
    FILE *fp;
    char file[65535]={0}, line[4096];
    Document ctrl;
    std::vector<GPIO> cpin;
    GPIO *gpio = new GPIO(36, 1);

    fp = fopen("./fsw1.json", "r");

    while(fgets(line, sizeof(line), fp)) 
        strcat(file, line);

    fclose(fp);

    ctrl.Parse(file);

    printf("%s\n", file);

    for(auto &pin : ctrl["pin"].GetArray()){
        // printf("%d\n", pin.GetInt());
        // gpio.reexport(pin.GetInt());
        cpin.push_back(GPIO(pin.GetInt()));
    }

    while(1) {
        ++i;
        sleep(1);
        if(i > 10)
            break;
        cpin[0].pullDown();
        sleep(1);
        cpin[0].pullUp();
    }
    delete gpio;

    return 0;
}
