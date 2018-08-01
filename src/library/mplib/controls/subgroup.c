#include "subgroup.h"

int subgroupGenerate(Control *__restrict subgroup)
{
    FILE *fp;
    char line[4096];

    if((fp = fopen("", "r")) == NULL)
        return -1;

    while(fgets(line, sizeof(line), fp) != NULL){
        if(strncmp(line, "subgroup->", 10))
            continue;
    }
}

Control *ControlConstruct(Control *__restrict icontrols, const char *conf)
{
    Control *subgroup = icontrols;

    if(subgroup == NULL)
        return NULL;
    
    subgroup->next = NULL;
    subgroupGenerate(subgroup);

    return subgroup;
}
