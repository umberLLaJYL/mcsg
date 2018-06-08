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

#include "../src/json/cJSON.h"
#include "../src/mplib/mpmod.h"

int main(int ac, char *av[])
{
    cJSON *root, *cmdAry, *item;
    char *croot, buf[MP_MAXLINE], *vlu;
    int fd, size;

    // root = cJSON_CreateObject();

    // fd = open("/mnt/hgfs/MCSG/demo/test.json", O_RDWR|O_CREAT, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);

    // cJSON_AddStringToObject(root, "aaa", "aaaa");
    // cJSON_AddStringToObject(root, "bbb", "bbbb");
    // cJSON_AddStringToObject(root, "ccc", "cccc");
    // cJSON_AddStringToObject(root, "ddd", "dddd");

    // cmdAry = cJSON_AddArrayToObject(root, "cmd");
    // cJSON_AddStringToObject(cmdAry, "aaa1", "aaaaa1");
    // cJSON_AddStringToObject(cmdAry, "ccc1", "ccccc1");
    // cJSON_AddStringToObject(cmdAry, "ddd1", "ddddd1");

    // croot = cJSON_Print(root);
    // mpWrite(fd, croot, strlen(croot));

    // cJSON_Delete(root);
    // close(fd);

    fd = open("/mnt/hgfs/MCSG/demo/test.json", O_RDONLY);
    mpRead(fd, buf, MP_MAXLINE);

    if((root = cJSON_Parse(buf)) == NULL)
        mpQuit(1, "Epase");

    cmdAry = cJSON_GetObjectItem(root, "cmd");
    size = cJSON_GetArraySize(cmdAry);

    croot = cJSON_Print(root);

    item = cJSON_GetArrayItem(cmdAry, 0);
    vlu = cJSON_GetStringValue(item);
    // vlu = cJSON_Print(cmdAry);

    printf("%s\nlen1: %lu, len2: %lu\n", croot, strlen(buf), strlen(croot));
    printf("arysize: %d, ary0: %s\n", size, vlu);

    cJSON_Delete(root);
    return 0;
}
