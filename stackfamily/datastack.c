#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef enum { false, true } bool;

typedef struct {
    char * key;
    char * value;
} DATA;

typedef struct {
    DATA * DATA;
    int MAXTOP;
    int TOP;
} DATA_STACK;

// Add data
void add(DATA * data, char * key, char * value) {
    data->key = (char*)malloc(strlen(key) * sizeof(char));
    data->value = (char*)malloc(strlen(value) * sizeof(char));
    strcpy(data->key, key);
    strcpy(data->value, value);
}

bool isFull(DATA_STACK * data) {
    return (data->TOP == data->MAXTOP);
}

bool isEmpty(DATA_STACK * data) {
    return (data->TOP == 0);
}

void createDataStack(DATA_STACK * data, int maxtop){
    data->DATA = (DATA*)malloc((maxtop+1) * sizeof(DATA));
    data->TOP = 0;
    data->MAXTOP = maxtop;
}

void addToDataStack(DATA_STACK * data, char * key, char * value) {
    if(!isFull(data)) {
        add(&data->DATA[data->TOP], key, value);
        data->TOP++;
    } else {
        // data is full;
    }
}

char * getValue(DATA_STACK data, char * key) {
    int i = 0;
    for(i = 0; i < data.TOP; i++ ) {
        if (strcmp(data.DATA[i].key, key)==0) {
            return data.DATA[i].value;
        }
    }
    return "";
}

void setValue(DATA_STACK * data, char * key, char * value) {
    int i=0;
    for(i = 0; i < data->TOP; i++ ) {
        if (strcmp(data->DATA[i].key, key)==0) {
            data->DATA[i].value = value;
        }
    }
}

void convertDataToJson(DATA_STACK data, char * json_output) {
    char temp[512]={0};
    char json[1024*1024]={0};
    json[0]='{';
    int i;
    for(i=0;i<data.TOP-1; i++) {
        memset(temp,0,sizeof(temp));
        sprintf(temp,"\"%s\":\"%s\",", data.DATA[i].key, data.DATA[i].value);
        strcat(json, temp);
    }
    
    if(!isEmpty(&data)) {
        memset(temp,0,sizeof(temp));
        sprintf(temp,"\"%s\":\"%s\"}", data.DATA[i].key, data.DATA[i].value);
        strcat(json, temp);
        memset(json_output,0,sizeof(json_output));
        sprintf(json_output,"%s",json);   
    }
}

// Program Test
int main() {
    // Global variable
    DATA_STACK myData;
    char myJson[1024]={0};
    
    // creat new data stack
    createDataStack(&myData,10);
    
    // add element to data stack
    addToDataStack(&myData,"type", "RequestType");
    addToDataStack(&myData,"name", "Sabituddin Bigbang");
    addToDataStack(&myData,"email", "kebunit@gmail.com");
    addToDataStack(&myData,"address", "Jakarta, Indonesia");
    
    // convert data stack to simple json
    convertDataToJson(myData, myJson);
    // display simple json
    printf("%s\n", myJson);
    // set value by key
    setValue(&myData,"name", "Sabituddin Bigbang Indonesia");
    // display by getValue using key
    printf("%s\n", getValue(myData, "name"));
    return 0;
}