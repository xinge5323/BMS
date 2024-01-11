//
// Created by 19030 on 2023/12/18.
//
#include "LinkList.h"
#include "string.h"
void admin_create(){
    user newUser;
    memset(&newUser, 0, sizeof(user));
    printf("please input your account:");
    scanf("%s",newUser.account);
    printf("please input your password:");
    scanf("%s",newUser.password);
    printf("please input your name:");
    scanf("%s",newUser.name);
    user* new= createUser(newUser.account,newUser.password,newUser.name,1);
    FILE *fp1= fopen("C:\\Users\\19030\\CLionProjects\\BMS\\data\\admin.bin","rb");
    if(fp1==NULL){
        perror("failed to open ");
        return;
    }
    int t=0;
    while (!feof(fp1)){
        user currentUser;
        fread(&currentUser,sizeof (user),1,fp1);
        if(strcmp(newUser.account,currentUser.account)==0){
            t=1;
        }
    }
    FILE *fp2= fopen("C:\\Users\\19030\\CLionProjects\\BMS\\data\\user.bin","rb");
    if(fp2==NULL){
        perror("failed to open ");
        return;
    }
    while (!feof(fp2)){
        user currentUser;
        fread(&currentUser,sizeof (user),1,fp2);
        if(strcmp(newUser.account,currentUser.account)==0){
            t=1;
        }

    }
    if(t==0){
        FILE *fp= fopen("C:\\Users\\19030\\CLionProjects\\BMS\\data\\admin.bin","ab");
        if(fp==NULL){
            perror("failed to open ");
            return;
        }
        if(fwrite(new,sizeof (user),1,fp)==1){
            printf("an admin has been successfully created");
        } else{
            printf("failed to create");
        }
        system("pause");

        fclose(fp);
    }
    if(t==1){
        printf("already have the same account,please try something different\n");
        system("pause");
        system("cls");
        admin_create();
    }
    fclose(fp1);
    fclose(fp2);

}


void user_create(){
    user newUser;
    printf("please input your account:");
    scanf("%s",newUser.account);
    printf("please input your password:");
    scanf("%s",newUser.password);
    printf("please input your name:");
    scanf("%s",newUser.name);
    user* new= createUser(newUser.account,newUser.password,newUser.name,0);
    FILE *fp2= fopen("C:\\Users\\19030\\CLionProjects\\BMS\\data\\user.bin","rb");
    if(fp2==NULL){
        perror("failed to open ");
        return;
    }
    int t=0;
    while (!feof(fp2)){
        user currentUser;
        fread(&currentUser,sizeof (user),1,fp2);
        if(strcmp(newUser.account,currentUser.account)==0){
            t=1;
            break;
        }
    }
    FILE *fp1= fopen("C:\\Users\\19030\\CLionProjects\\BMS\\data\\admin.bin","rb");
    if(fp1==NULL){
        perror("failed to open ");
        return;
    }
    while (!feof(fp1)){
        user currentUser;
        fread(&currentUser,sizeof (user),1,fp1);
        if(strcmp(newUser.account,currentUser.account)==0){
            t=1;
            break;
        }
    }
    if(t==0){
        FILE *fp= fopen("C:\\Users\\19030\\CLionProjects\\BMS\\data\\user.bin","ab");
        if(fp==NULL){
            perror("failed to open ");
            return;
        }
        if(fwrite(new,sizeof (user),1,fp)==1){
            printf("a user_account has been successfully created");
        } else{
            printf("failed to create");
        }
        system("pause");

        fclose(fp);
    }
    if(t==1){
        printf("already have the same account,please try something different\n");
        system("pause");
        system("cls");
        user_create();
    }
    fclose(fp2);
    fclose(fp1);

}

