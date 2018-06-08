#include "./mplib/mpmod.h"
#include "./json/cJSON.h"
#include "mpmsg.h"

extern int cJSON_GetKeyValue(const cJSON *const object, const char *key, void *value)
{
    char *objBuf, *location, *end;
    unsigned int length = 0;
    void *valueBuf;

    if(object == NULL || key == NULL)
        return -1;

    objBuf = cJSON_PrintUnformatted(object);
    if((location = strstr(objBuf, key)) == NULL)
        return -1;

    if(value == NULL)
        return 0;

    if((*(location -= 1)) != '\"')
        return -1;
    if((*(location += strlen(key)+1)) != '\"')
        return -1;
    if((*(location += 1)) != ':')
        return -1;

    if((*(location += 1)) == '\"'){
        location++;
 
        if((end = strstr(location, "\"")) == NULL)
            return -1;
        
        length = strlen(location) - strlen(end) + 1;
        valueBuf = malloc(length);
        memset(value, 0, length);
        
        memcpy(valueBuf, location, length-1);
        memcpy(value, valueBuf, length-1);
        free(valueBuf);
        return 0;
    }
    else if((*location >= '0') && (*location <= '9')){
        end = location;
        while(((*(end++)) >= '0') && (*end <= '9'))
            length++;
        if(length < 10){
            int numberInt;
        
            numberInt = atoi(location);
            memcpy(value, &numberInt, sizeof(int));
            return 0;
        }
        else if((length <= 20) && (*end == '.')){
            double numberDouble;

            numberDouble = atof(location);
            memcpy(value, &numberDouble, sizeof(double));
            return 0;
        }
    }
    return -1;
}

extern int mpParseMessage(const char *const message, char *msgIDStr)
{
    cJSON *objRoot, *msgID, *msgType;
    char *ID, *type;
    int hashSum;

    if((objRoot = cJSON_Parse(message)) == NULL)
        return -1;

    if((msgType = cJSON_GetObjectItem(objRoot, "type")) == NULL)
        return -1;
    if((type = cJSON_GetStringValue(msgType)) == NULL)
        return -1;
    MurmurHash3_x86_32(type, strlen(type), MP_MSGSEED, &hashSum);

    if((msgID = cJSON_GetObjectItem(objRoot, "ID")) == NULL)
        return -1;
    if((ID = cJSON_GetStringValue(msgID)) == NULL)
        return -1;
    memcpy(msgIDStr, ID, MP_MAXID);

    return hashSum;
}

static int mpGenerateACK(char *__restrict devinfo)
{
    FILE *devinfoFP;
    char buf[MP_MAXLINE];

    memset(buf, 0, sizeof(buf));

    if((devinfoFP = fopen("./.devinfo.json", "r")) == NULL)
        return -1;
    while(fgets(&buf[strlen(buf)], MP_MAXLINE, devinfoFP) != NULL)
        /* empty loop */;

    memcpy(devinfo, buf, MP_MAXLINE);

    fclose(devinfoFP);
    return 0;
}

extern int mpGenerateMessage(char *__restrict messageBuffer, const char *const type, ...)
{
    cJSON *objRoot, *objSubstance;
    char *buf, substanceBuf[MP_MAXLINE];
    int32_t hashRes;
    va_list messages;

    va_start(messages, type);

    if((buf = malloc(MP_MAXLINE)) == NULL)
        return -1;
    memset(buf, 0, MP_MAXLINE);
    memset(substanceBuf, 0, sizeof(substanceBuf));

    if((objRoot = cJSON_CreateObject()) == NULL)
        return -1;

    if(cJSON_AddNumberToObject(objRoot, "time", time(NULL)) == NULL)
        return -1;
    if(cJSON_AddNumberToObject(objRoot, "ID", time(NULL)) == NULL)
        return -1;
    if(cJSON_AddStringToObject(objRoot, "type", type) == NULL)
        return -1;

    MurmurHash3_x86_32(type, strlen(type), MP_MSGSEED, &hashRes);
    switch(hashRes){
        case MSG_ACK:
            mpGenerateACK(substanceBuf);
            objSubstance = cJSON_Parse(substanceBuf);
            cJSON_AddItemToObject(objRoot, "substance", objSubstance);
            break;
        case MSG_CMD:
            break;
    }

    buf = cJSON_PrintUnformatted(objRoot);
    memcpy(messageBuffer, buf, MP_MAXLINE);

    free(buf);
    cJSON_Delete(objRoot);

    va_end(messages);
    return 0;
}
