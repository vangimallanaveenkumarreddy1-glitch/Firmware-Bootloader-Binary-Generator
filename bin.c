#include "bin.h"
#include"header.h"
#include<stdlib.h>
#include<stdio.h>

void creat_bin(Type* mchn,char* type)
{     
    if(strcmp(type,"Smart Phone")==0)  
    {
        FILE *fp = fopen("firmware.bin", "wb");
        if(fp == NULL) 
        {
            printf("Error to creat .bin file...\n");
            return;
        }
        fwrite(&mchn->phone, 1, sizeof(Phone), fp);
        fclose(fp);
        printf("\nCreated firmware.bin.... (%zu bytes)\n", sizeof(Phone));
        return;
    }
    if(strcmp(type,"Microwave")==0)  
    {
        FILE *fp = fopen("firmware.bin", "wb");
        if(fp == NULL) 
        {
            printf("Error to creat .bin file...\n");
            return;
        }
        fwrite(&mchn->MW, 1, sizeof(Mcw), fp);
        fclose(fp);
        printf("\nCreated firmware.bin... (%zu bytes)\n", sizeof(Mcw));
        return;
    }
    if(strcmp(type,"Car")==0)  
    {
        FILE *fp = fopen("firmware.bin", "wb");
        if(fp == NULL) 
        {
            printf("Error to creat .bin file...\n");
            return;
        }
        fwrite(&mchn->car, 1, sizeof(Car), fp);
        fclose(fp);
        printf("\nCreated firmware.bin.... (%zu bytes)\n", sizeof(Car));
        return;
    }
}

