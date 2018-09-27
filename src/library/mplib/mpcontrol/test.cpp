#include "control.h"
#include "../../json/rapidjson/document.h"

using namespace rapidjson;

int main(int argc, char *argv[])
{
    int i = 0, a;
    FILE *fp;
    char file[65535]={0}, line[4096];
    Document ctrl;
    std::vector<GPIO> cpin;
    std::map<std::string, int> sequence;
    std::map<std::string, int>::iterator element;

    fp = fopen("./fsw1.json", "r");

    while(fgets(line, sizeof(line), fp)) 
        strcat(file, line);

    fclose(fp);

    ctrl.Parse(file);

    printf("%s\n", file);

    for(SizeType cnt = 0; cnt != ctrl["pin"].Size(); ++cnt)
        cpin.push_back(GPIO());

    for(SizeType cnt = 0; cnt != ctrl["pin"].Size(); ++cnt)
        cpin[cnt].reexport(ctrl["pin"][cnt].GetInt(), ctrl["dir"][cnt].GetString());

    for(auto &seq : ctrl["sequence"].GetObject())
        sequence.insert({seq.name.GetString(), seq.value.GetInt()});

    std::string str("pri");
    if((element = sequence.find(str)) != sequence.end())
        printf("k: %d, size: %d\n", element->second, cpin.size());

    if(cpin[1].pullDown() == false)
        perror("pulldown");

    while(1) {
        ++i;
        sleep(1);
        if(i > 5)
            break;
        cpin[0].pullDown();
        sleep(1);
        cpin[0].pullUp();
    }

    return 0;
}
