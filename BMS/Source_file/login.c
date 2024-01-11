//
// Created by 19030 on 2023/12/20.
//
#include <stdio.h>
#include "LinkList.h"
#include "account_create.h"
#include "stdlib.h"
#include "string.h"

#include "book_user_operation.h"
#include "interface.h"
#include "loading.h"
user* login(){

    user newUser;
    label:
    memset(&newUser, 0, sizeof(user));
    printf("please input your account:");
    scanf("%s",newUser.account);
    printf("please input your password:");
    scanf("%s",newUser.password);
    FILE *fp1= fopen("C:\\Users\\19030\\CLionProjects\\BMS\\data\\admin.bin","rb");
    if(fp1==NULL){
        perror("failed to open1");
        return 0;
    }
    FILE *fp2= fopen("C:\\Users\\19030\\CLionProjects\\BMS\\data\\user.bin","rb");
    if(fp2==NULL){
        perror("failed to open2");
        return 0;
    }
    while (!feof(fp1)){
        user* currentUser= (user*)malloc(sizeof (user));
        fread(currentUser,sizeof (user),1,fp1);
        if(strcmp(newUser.account,currentUser->account)==0&& strcmp(newUser.password,currentUser->password)==0){
            printf("Hello%s\n",currentUser->name);
            printf(" %d\n",currentUser->flag);
            return currentUser;
        }
        free(currentUser);
    }
    while (!feof(fp2)){
        user* currentUser= (user*)malloc(sizeof (user));
        fread(currentUser,sizeof (user),1,fp2);
        if(strcmp(newUser.account,currentUser->account)==0&& strcmp(newUser.password,currentUser->password)==0){
            printf("Hello %s",currentUser->name);
            printf(" %d\n",currentUser->flag);
            return currentUser;
        }
        free(currentUser);

    }
    printf("account or password maybe wrong,please try again");
    system("pause");
    system("cls");
    goto label;
    return 0;
}