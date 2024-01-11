//
// Created by 19030 on 2023/12/19.
//
#include "stdlib.h"
#include "stdio.h"
#include "book_user_operation.h"
#include "loading.h"

void admin_interface(user* current_user){
    int a;
    printf("hello %s\n",current_user->name);
    printf("\n");
    printf("************************************************\n");
    printf("*  press 1 to enter the book into system       *\n");
    printf("*  press 2 to delete the book                  *\n");
    printf("*  press 3 to revise the book                  *\n");
    printf("*  press 4 to delete the user_account          *\n");
    printf("*  press 5 to revise the user_account          *\n");
    printf("*  press 6 to search history                   *\n");
    printf("*  press 7 to log out                          *\n");
    printf("************************************************\n");
    printf("please input a number:");
    scanf("%d",&a);
    system("cls");
    switch (a) {
        case 1:
            enter_book(current_user);
            break;
        case 2: {
            char name[32];
            printf("input the book_name that you need to delete:");
            scanf("%s", name);
            delete_book(name,current_user);
            break;
        }
        case 3:{
            char name[32];
            printf("input the book_name that you need to revise:");
            scanf("%s", name);
            system("cls");
            revise_book(name,current_user);
            break;
        }
        case 4:{
            char account[12];
            printf("input the account that you need to delete:");
            scanf("%s", account);
            delete_user(account,current_user);
        }
        case 5:{
            char account[12];
            printf("input the account that you need to revise:");
            scanf("%s", account);
            system("cls");
            revise_user(account,current_user);
        }
        case 6:{
            char account[12];
            printf("input the account that you need to search:");
            scanf("%s", account);
            system("cls");
            search_history(account,current_user);
        }
        case 7:
            system("cls");
            loading();
        default:
            printf("input a wrong number");
    }
    system("pause");
    system("cls");
    admin_interface(current_user);
}

void user_interface(user* current_user){

    FILE *fp5= fopen("C:\\Users\\19030\\CLionProjects\\BMS\\data\\record.bin","rb");
    if(fp5==NULL){
        perror("failed to open");
        return;
    }
    record* head=createHeadRecord();
    while (!feof(fp5)){
        record *current_record=(record*) malloc(sizeof (record));
        memset(current_record,0,sizeof (record));
        fread(current_record,sizeof (record ),1,fp5);
        if(strcmp(current_record->user_account,current_user->account)==0){
            appendRecord(head,current_record->user_account,current_record->book_name,current_record->borrowTime,current_record->returnTime);
        }
        free(current_record);
    }
    head=head->next;
    while (head!=NULL){

        time_t current_time=time(NULL);
        if(current_time>head->returnTime){
            time_t x=current_time-head->returnTime;

            int day =  x/(60*60*24);


            printf("%d already overdue\n", day);
            printf("\n");
        }
        head=head->next;
    }


    FILE *fp= fopen("C:\\Users\\19030\\CLionProjects\\BMS\\data\\record.bin","rb");
    if(fp==NULL){
        perror("failed to open");
        return;
    }
    record* temporary_head=createHeadRecord();
    record* current_record =(record*) malloc(sizeof (record));
    while(!feof(fp)){
        memset(current_record,0,sizeof (record));
        fread(current_record, sizeof (record), 1, fp);
        if(strcmp(current_record->user_account, current_user->account) == 0&& findBook(current_record->book_name,current_user)->flag==1){
            appendRecord(temporary_head,current_record->user_account,current_record->book_name,current_record->borrowTime,current_record->returnTime);
        }
    }
    free(current_record);
    printf("hello %s\n",current_user->name);
    printf("\n");

    record *tem=temporary_head->next;
    while (tem!=NULL){
        time_t t = tem->returnTime;
        time_t current_time=time(NULL);
        if(current_time<tem->returnTime){
            printf("*you should return %s before %s\n",tem->book_name, ctime(&t));
        }
        tem=tem->next;
    }

    int a;

    printf("***********************************\n");
    printf("*   press 1 to borrow books       *\n");
    printf("*   press 2 to return books       *\n");
    printf("*   press 3 to renew books        *\n");
    printf("*   press 4 to search books       *\n");
    printf("*   press 5 to log out            *\n");
    printf("***********************************\n");
    printf("please input a number:");
    scanf("%d",&a);
    system("cls");
    switch (a) {
        case 1:{
            char name[32];
            printf("input the book_name that you need to borrow:");
            scanf("%s", name);
            system("cls");
            borrow_book(name,current_user);
            break;
        }
        case 2:{
            char name[32];
            printf("input the book_name that you need to return:");
            scanf("%s", name);
            return_book(name,current_user);
            break;
        }
        case 3:{
            char name[32];
            int day;
            printf("input the book_name that you need to renew:");
            scanf("%s", name);
            printf("input the day that you need to renew:");
            scanf("%d", &day);
            renew(name,current_user,day);
            break;
        }
        case 4:{
            FILE *fp1= fopen("C:\\Users\\19030\\CLionProjects\\BMS\\data\\books.bin","rb");
            while (!feof(fp1)){
                book *current_book=(book*) malloc(sizeof (book));
                memset(current_book,0,sizeof (book));
                fread(current_book,sizeof (book),1,fp1);
                if(strcmp(current_book->name,"\0")!=0&&strcmp(current_book->author,"\0")!=0&&strcmp(current_book->publish,"\0")!=0){
                    printf("name:%s author:%s publish:%s plate:%s price:%d\n",current_book->name,current_book->author,current_book->publish,current_book->plate,current_book->price);
                }
                free(current_book);
            }
            system("pause");
            system("cls");
            user_interface(current_user);
            break;
        }
        case 5:{
            system("cls");
            loading();
        }
        default:
            printf("input a wrong number");
            system("pause");
            system("cls");
            user_interface(current_user);
    }
}