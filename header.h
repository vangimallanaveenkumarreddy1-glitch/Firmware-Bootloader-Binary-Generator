#ifndef HEADER_H
#define HEADER_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include"bin.h"

 
typedef struct phone {
    char name[30];
    int brit;
    int storage;
    char date[10];
    char sim[30];
} Phone;

typedef struct car {
    char name[30];
    char odo[10];
    int pres;
    char date[10];
    char fuel[30];
    char mode[30];
} Car;

typedef struct MW {
    char name[30];
    int heat;
    int lock;
    char date[10];
    char mode[30];
    int timer;
} Mcw;

typedef struct all {
    Phone phone;
    Car car;
    Mcw MW;
} Type;

 
typedef struct firmware {
    char file[100];
    unsigned char data[4096];
    int size;
    int valid;
} firmware;

// Function declarations
void disp_phone(Phone *p);
void disp_mic(Mcw *m);
void disp_car(Car *c);
void loadfirmware(firmware*,char*);
void validate(firmware*,char*);
void boot(firmware *,char*);
void creat_bin(Type *mchn, char *type);
void change_phone_data(Phone*);
void change_car_data(Car *);
void change_microwave_data(Mcw *);

#endif