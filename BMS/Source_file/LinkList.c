//
// Created by 19030 on 2023/12/18.
//
#include "LinkList.h"

struct user* createHeadUser(){
    user *head= malloc(sizeof (user));
    memset(head,0,sizeof (user));
    head->next=NULL;
    return head;
}

user *findLastUser(user* head){
    user * lastNode=head;
    do{
        user *temNode=lastNode->next;
        if(temNode==NULL){
            break;
        }
        lastNode=temNode;
    } while (1);
    return lastNode;
}

user *createUser(char account[12],char password[12],char name[32],int flag){
    user *newNode=(user*) malloc(sizeof (user));
    memset(newNode,0,sizeof (user));
    strcpy(newNode->account,account);
    strcpy(newNode->password,password);
    strcpy(newNode->name,name);
    newNode->flag=flag;
    newNode->next=NULL;
    return newNode;
}

void appendUser(user* head,char account[12],char password[12],char name[32],int flag){
    user *newNode=(user*) malloc(sizeof (user));
    memset(newNode,0,sizeof (user));
    strcpy(newNode->account,account);
    strcpy(newNode->password,password);
    strcpy(newNode->name,name);
    newNode->flag=flag;
    findLastUser(head)->next=newNode;
    newNode->next=NULL;
}

void freeUser(user* head){
    user *currentNode=head;
    while (currentNode!=NULL){
        user* temNode=currentNode;
        currentNode=currentNode->next;
        free(temNode);
    }
}

struct book * createHeadBook(){
    book *head= malloc(sizeof (book));
    memset(head,0,sizeof (book));
    head->next=NULL;
    return head;
}

book *findLastBook(book* head){
    book * lastNode=head;
    do{
        book *temNode=lastNode->next;
        if(temNode==NULL){
            break;
        }

        lastNode=temNode;
    } while (1);
    return lastNode;
}

book *createBook(char ID[12],char name[32],char author[32],char plate[12],char publish[12],char ISBN[12],int price,int flag){
    book *newNode=(book*) malloc(sizeof (book));
    memset(newNode,0,sizeof (book));
    strcpy(newNode->ID,ID);
    strcpy(newNode->name,name);
    strcpy(newNode->author,author);
    strcpy(newNode->plate,plate);
    strcpy(newNode->publish,publish);
    strcpy(newNode->ISBN,ISBN);
    newNode->price=price;
    newNode->flag=flag;
    newNode->next=NULL;
    return newNode;
}

void appendBook(book* head,char ID[12],char name[32],char author[32],char plate[12],char publish[12],char ISBN[12],int price,int flag){
    book *newNode=(book*) malloc(sizeof (book));
    memset(newNode,0,sizeof (book));
    strcpy(newNode->ID,ID);
    strcpy(newNode->name,name);
    strcpy(newNode->author,author);
    strcpy(newNode->plate,plate);
    strcpy(newNode->publish,publish);
    strcpy(newNode->ISBN,ISBN);
    newNode->price=price;
    newNode->flag=flag;
    findLastBook(head)->next=newNode;
    newNode->next=NULL;
}

void freeBook(book* head){
    book *currentNode=head;
    while (currentNode!=NULL){
        book* temNode=currentNode;
        currentNode=currentNode->next;
        free(temNode);
    }
}

struct record * createHeadRecord(){
    record *head= malloc(sizeof (record));
    memset(head,0,sizeof (record));
    head->next=NULL;
    return head;
}

record *findLastRecord(record* head){
    record * lastNode=head;
    do{
        record *temNode=lastNode->next;
        if(temNode==NULL){
            break;
        }
        lastNode=temNode;
    } while (1);
    return lastNode;
}

record *createRecord(char user_account[12],char book_name[32],time_t borrowTime,time_t returnTime){
    record *newNode=(record*) malloc(sizeof (record));
    memset(newNode,0,sizeof (record));
    strcpy(newNode->user_account, user_account);
    strcpy(newNode->book_name, book_name);
    newNode->borrowTime=borrowTime;
    newNode->returnTime=returnTime;
    newNode->next=NULL;
    return newNode;
}

void appendRecord(record* head, char user_account[12],char book_name[32],time_t borrowTime,time_t returnTime){
    record *newNode=(record*) malloc(sizeof (record));
    memset(newNode,0,sizeof (record));
    if(strlen(user_account) > 11 || strlen(user_account) == 0) {
        perror("error user_account");
    }
    if(strlen(book_name) > 31 || strlen(book_name) == 0) {
        perror("error book_name");
    }
    if(borrowTime < 0 || returnTime  < 0) {
        perror("error borrowTime or returnTime");
    }
    strcpy(newNode->user_account, user_account);
    strcpy(newNode->book_name, book_name);
    newNode->borrowTime=borrowTime;
    newNode->returnTime=returnTime;
    newNode->next=NULL;
    findLastRecord(head)->next=newNode;
}

void freeRecord(record* head){
    record *currentNode=head;
    while (currentNode!=NULL){
        record* temNode=currentNode;
        currentNode=currentNode->next;
        free(temNode);
    }
}