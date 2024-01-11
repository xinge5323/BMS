//
// Created by 19030 on 2023/12/20.
//

#include <stdio.h>
#include "LinkList.h"
#include "account_create.h"
#include "stdlib.h"
#include "string.h"
#include "login.h"
#include "book_user_operation.h"
#include "interface.h"

void loading(){
    printf("*********************************\n");
    printf("* press 0 to create a account   *\n");
    printf("* press 1 to input your account *\n");
    printf("* press 2 to quit               *\n");
    printf("*********************************\n");
    printf("please input a number:");
    int flag;
    scanf("%d",&flag);
    system("cls");
    if(flag==0){

        int flag1;
        a:
        printf("********************************************\n");
        printf("* press 0 to create an admin account       *\n");
        printf("* press 1 to create a user_account account *\n");
        printf("* press 2 to return to superior directory  *\n");
        printf("********************************************\n");
        printf("please input a number:");
        scanf("%d",&flag1);
        system("cls");
        if(flag1==0){
            admin_create();
            system("cls");
            loading();
        }else if(flag1==1){
            user_create();
            system("cls");
            loading();
        } else if(flag1==2){
            loading();
        }
        else if(flag1!=0&&flag1!=1&&flag1!=2){
            printf("please input a right number");
            system("pause");
            system("cls");
            goto a;
        }
    }else if(flag==1){

        user* current_user=login();
        if(current_user->flag==1){
            system("cls");
            admin_interface(current_user);
        }else if(current_user->flag==0){
            system("cls");
            user_interface(current_user);
        }
    } else if(flag==2){
        exit(0);
    }else if(flag!=0&&flag!=1&&flag!=2){
        printf("please input a right number");
        system("pause");
        system("cls");
        loading();
    }
}