#include <stdio.h>
#include <string.h>

struct record
{
    char firstName[20]; 
    char lastName[20]; 
    char middleName; 

    long accountNum;
    double accountBalance;
    short accountType; 

};


int main(){

    printf("short size : %lu \n", sizeof(short)); 
    printf("int size : %lu \n", sizeof(int));
    printf("long size : %lu \n", sizeof(long)); 
    printf("float size : %lu \n", sizeof(float));  
    printf("double size : %lu \n", sizeof(double)); 
    printf("char size : %lu \n", sizeof(char)); 
    printf("cpu bit width size: %lu \n", sizeof(void*)); 


    struct record personnel1;
    strcpy(personnel1.firstName, "ghassen"); 
    strcpy(personnel1.lastName, "hafsia"); 
    personnel1.middleName = 'n'; 
    personnel1.accountNum = 1234; 
    personnel1.accountType = 1; 
    personnel1.accountBalance = 1024.51;  

    printf("struct size : %lu \n", sizeof(struct record)); 

    char data_record[] =    "\x41\x64\x61\x6d\x00\x7f\x00\x00\x30"
                            "\x57\xf1\x6c\xff\x7f\x00\x00\x00\x00"
                            "\x00\x00\x41\x76\x69\x76\x00\x4b\xf1"
                            "\x6c\xff\x7f\x00\x00\x85\xb8\x7e\xc5"
                            "\xc3\x91\x98\xa0\x4a\x00\x00\x00\x00"
                            "\x00\x00\x00\x32\x79\x06\x00\x00\x00"
                            "\x00\x00\x0a\x00\x00\x00\x00\x00\x00"
                            "\x00\x8d\x97\x6e\x12\x83\x00\xa0\x40";

    struct record personnel2; 
    memcpy(personnel2.firstName, data_record, 4);
    personnel2.firstName[4] ='\0';

    memcpy(personnel2.lastName,&data_record[4], 4); 
    personnel2.lastName[8]= '\0'; 
    
    personnel2.middleName = data_record[12]; 


    memcpy(&personnel2.accountType, &data_record[30], sizeof(short)); 

    memcpy(&personnel2.accountNum, &data_record[70], sizeof(int));  

    /*when casting a variable, it does not affect the underlying data,
     the number of bytes took by the variable remains the same in the memory,
      instead the compiler interprets the data differently*/ 

}