//
// Created by 19030 on 2023/12/15.
//

#ifndef BMS_LINKLIST_H
#define BMS_LINKLIST_H
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "time.h"
struct user{
    char account[12];
    char password[12];
    char name[32];
    int flag;
    struct user* next;
};

struct book{
    char ID[12];
    char name[32];
    char author[32];
    char plate[12];
    char publish[12];
    char ISBN[12];
    int price;
    int flag;
    struct book* next;
};

struct record{
    char user_account[12];
    char book_name[32];
    time_t borrowTime;
    time_t returnTime;
    struct record *next;
};

typedef struct user user;

typedef struct book book;

typedef struct record record;

struct user* createHeadUser();

user *findLastUser(user* head);

user *createUser(char account[12],char password[12],char name[32],int flag);

void appendUser(user* head,char account[12],char password[12],char name[32],int flag);

void freeUser(user* head);

struct book * createHeadBook();

book *findLastBook(book* head);

book *createBook(char ID[12],char name[32],char author[32],char plate[12],char publish[12],char ISBN[12],int price,int flag);

void appendBook(book* head,char ID[12],char name[32],char author[32],char plate[12],char publish[12],char ISBN[12],int price,int flag);

void freeBook(book* head);

struct record * createHeadRecord();

record *findLastRecord(record* head);

record *createRecord(char user[12],char name[32],time_t borrowTime,time_t returnTime);

void appendRecord(record* head, char user[12],char name[32],time_t borrowTime,time_t returnTime);

void freeRecord(record* head);


#endif //BMS_LINKLIST_H


