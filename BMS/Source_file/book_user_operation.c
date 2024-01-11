//
// Created by 19030 on 2023/12/20.
//
#include <time.h>
#include <sys/stat.h>
#include "stdio.h"
#include "stdlib.h"
#include "LinkList.h"
#include "interface.h"

book* findBook(char name[32],user* current_user){
    book *required_book=(book*) malloc(sizeof (book));
    FILE *fp= fopen("C:\\Users\\19030\\CLionProjects\\BMS\\data\\books.bin","rb");
    if(fp==NULL){
        perror("failed to open");
        return 0;
    }
    while (!feof(fp)){
        memset(required_book,0,sizeof (book));
        fread(required_book,sizeof(book),1,fp);
        if(strcmp(required_book->name,name)==0){
            return required_book;
        }
    }

    return 0;
}

book* adminFindBook(char name[32],user* current_user){
    book *required_book=(book*) malloc(sizeof (book));
    FILE *fp= fopen("C:\\Users\\19030\\CLionProjects\\BMS\\data\\books.bin","rb");
    if(fp==NULL){
        perror("failed to open");
        return 0;
    }
    while (!feof(fp)){
        memset(required_book,0,sizeof (book));
        fread(required_book,sizeof(book),1,fp);
        if(strcmp(required_book->name,name)==0){
            return required_book;
            break;
        }
    }
    printf("there is no book that you need");
    system("pause");
    system("cls");
    admin_interface(current_user);
    return 0;
}

user* findUser(char account[12],user* current_user){
    user *required_user=(user*) malloc(sizeof (user));
    memset(required_user, 0, sizeof (user));
    FILE *fp= fopen("C:\\Users\\19030\\CLionProjects\\BMS\\data\\user.bin","rb");
    if(fp==NULL){
        perror("failed to open");
        return 0;
    }
    while (!feof(fp)){
        fread(required_user, sizeof(user), 1, fp);
        if(strcmp(required_user->account,account) == 0){
            return required_user;
        }
    }
    printf("there is no user_account that you need");
    system("pause");
    system("cls");
    admin_interface( current_user);
    return 0;
}

book* userFindBook(char name[32],user* current_user){
    book *required_book=(book*) malloc(sizeof (book));
    FILE *fp= fopen("C:\\Users\\19030\\CLionProjects\\BMS\\data\\books.bin","rb");
    if(fp==NULL){
        perror("failed to open");
        return 0;
    }
    while (!feof(fp)){
        memset(required_book,0,sizeof (book));
        fread(required_book,sizeof(book),1,fp);
        if(strcmp(required_book->name,name)==0){
            return required_book;
        }
    }
    printf("there is no book that you need");
    system("pause");
    system("cls");
    user_interface(current_user);
    return 0;
}

record* findRecord(char name[32],user* current_user){
    FILE *fp= fopen("C:\\Users\\19030\\CLionProjects\\BMS\\data\\record.bin","rb");
    if(fp==NULL){
        perror("failed to open");
        return 0;
    }

    while(!feof(fp)){
        record* current =(record*) malloc(sizeof (record ));
        memset(current,0,sizeof (record));
        fread(current,sizeof (record),1,fp);
        if(strcmp(current->book_name,name)==0&& strcmp(current->user_account,current_user->account)==0){
            return current;
        }
        free(current);
    }
    printf("there is no record that you need");
    system("pause");
    system("cls");
    user_interface(current_user);
    return 0;
}

void enter_book(user* current_user){
    book newBook;
    memset(&newBook,0,sizeof (book));
    printf("please enter ID:");
    scanf("%s",newBook.ID);
    printf("please enter book_name:");
    scanf("%s",newBook.name);
    printf("please enter author:");
    scanf("%s",newBook.author);
    printf("please enter plate:");
    scanf("%s",newBook.plate);
    printf("please enter publish:");
    scanf("%s",newBook.publish);
    printf("please enter ISBN:");
    scanf("%s",newBook.ISBN);
    printf("please enter price:");
    scanf("%d",&newBook.price);
    newBook.flag=0;
    FILE *fp= fopen("C:\\Users\\19030\\CLionProjects\\BMS\\data\\books.bin","ab");
    if(fp==NULL){
        perror("failed to open");
        return;
    }
    FILE *fp1= fopen("C:\\Users\\19030\\CLionProjects\\BMS\\data\\books.bin","rb");
    if(fp1==NULL){
        perror("failed to open");
        return;
    }

    while (!feof(fp1)){//判断是否有相同的书
        book* current=(book*) malloc(sizeof (book));
        memset(current,0,sizeof (book));

        fread(current,sizeof (book),1,fp1);
        if(strcmp(current->plate,newBook.plate)==0){
            printf("already have a same book");
            system("pause");
            system("cls");
            admin_interface(current_user);
            break;
        }
        free(current);
    }
    fclose(fp1);
    if(fwrite(&newBook,sizeof (book),1,fp)==1){
        printf("successfully enter");
    } else{
        printf("failed to enter");
    }
    fflush(fp);
    fclose(fp);
    system("pause");
    system("cls");
    admin_interface(current_user);
}

void delete_book(char name[32],user* current_user){
    book* require_book= adminFindBook(name,current_user);
    FILE *fp= fopen("C:\\Users\\19030\\CLionProjects\\BMS\\data\\books.bin","rb");
    if(fp==NULL){
        perror("failed to open");
        return;
    }
    book* head=createHeadBook();
    while (!feof(fp)){
        book *current=(book*) malloc(sizeof (book));
        fread(current,sizeof (book),1,fp);
        if(strcmp(current->plate,require_book->plate)!=0){
            appendBook(head,current->ID,current->name,current->author,current->plate,current->publish,current->ISBN,current->price,current->flag);
        }
        free(current);
    }
    fclose(fp);
    FILE *fp1= fopen("C:\\Users\\19030\\CLionProjects\\BMS\\data\\books.bin","wb");
    if(fp1==NULL){
        perror("failed to open");
        return;
    }
    book* current=head->next;
    while (current!=NULL){
        fwrite(current,sizeof (book),1,fp1);
        current=current->next;
    }
    printf("successfully deleted");
    fclose(fp1);


}

void revise_book(char name[32],user* current_user){
    book* require_book= adminFindBook(name,current_user);

    book newBook;
    printf("please enter ID:");
    scanf("%s",newBook.ID);
    printf("please enter book_name:");
    scanf("%s",newBook.name);
    printf("please enter author:");
    scanf("%s",newBook.author);
    printf("please enter plate:");
    scanf("%s",newBook.plate);
    printf("please enter publish:");
    scanf("%s",newBook.publish);
    printf("please enter ISBN:");
    scanf("%s",newBook.ISBN);
    printf("please enter price:");
    scanf("%d",&newBook.price);

    FILE *fp= fopen("C:\\Users\\19030\\CLionProjects\\BMS\\data\\books.bin","rb");
    if(fp==NULL){
        perror("failed to open");
        return;
    }
    book* head=createHeadBook();
    while (!feof(fp)){
        book *current=(book*) malloc(sizeof (book));
        fread(current,sizeof (book),1,fp);
        if(strcmp(current->plate,require_book->plate)!=0){
            appendBook(head,current->ID,current->name,current->author,current->plate,current->publish,current->ISBN,current->price,current->flag);
        } else{
            appendBook(head,newBook.ID,newBook.name,newBook.author,newBook.plate,newBook.publish,newBook.ISBN,newBook.price,current->flag);
        }
        free(current);
    }
    fclose(fp);
    FILE *fp1= fopen("C:\\Users\\19030\\CLionProjects\\BMS\\data\\books.bin","wb");
    if(fp1==NULL){
        perror("failed to open");
        return;
    }
    book* current=head->next;
    while (current!=NULL){
        fwrite(current,sizeof (book),1,fp1);
        current=current->next;
    }
    fclose(fp1);
}

void delete_user(char account[12],user* current_user){
    user* require_user= findUser(account,current_user);
    FILE *fp= fopen("C:\\Users\\19030\\CLionProjects\\BMS\\data\\user.bin","rb");
    if(fp==NULL){
        perror("failed to open");
        return;
    }
    user* head=createHeadUser();
    while (!feof(fp)){
        user *current=(user*) malloc(sizeof (user));
        fread(current,sizeof (user),1,fp);
        if(strcmp(current->account,require_user->account)!=0){
            appendUser(head,current->account,current->password,current->name,current->flag);
        }
        free(current);
    }
    fclose(fp);
    FILE *fp1= fopen("C:\\Users\\19030\\CLionProjects\\BMS\\data\\user.bin","wb");
    if(fp1==NULL){
        perror("failed to open");
        return;
    }
    user* current=head->next;
    while (current!=NULL){
        fwrite(current,sizeof (user),1,fp1);
        current=current->next;
    }

    fclose(fp1);
}

void revise_user(char account[12],user* current_user){
    user* require_user= findUser(account,current_user);
    user newUser;
    printf("please enter account:");
    scanf("%s",newUser.account);
    printf("please enter password:");
    scanf("%s",newUser.password);
    printf("please enter book_name:");
    scanf("%s",newUser.name);
    printf("please enter flag:");
    scanf("%d",&newUser.flag);

    FILE *fp= fopen("C:\\Users\\19030\\CLionProjects\\BMS\\data\\user.bin","rb");
    if(fp==NULL){
        perror("failed to open");
        return;
    }
    user* head=createHeadUser();
    while (!feof(fp)){
        user *current=(user*) malloc(sizeof (user));
        fread(current,sizeof (user),1,fp);
        if(strcmp(current->account,require_user->account)!=0){
            appendUser(head,current->account,current->password,current->name,current->flag);
        } else{
            appendUser(head,newUser.account,newUser.password,newUser.name,current->flag);
        }
        free(current);
    }
    fclose(fp);
    FILE *fp1= fopen("C:\\Users\\19030\\CLionProjects\\BMS\\data\\books.bin","wb");
    if(fp1==NULL){
        perror("failed to open");
        return;
    }
    user* current=head->next;
    while (current!=NULL){
        fwrite(current,sizeof (user),1,fp1);
        current=current->next;
    }
    fclose(fp1);
}

void borrow_book(char name[32],user* current_user){
    book* require_book= userFindBook(name,current_user);
    record *new_record=(record*) malloc(sizeof (record));
    memset(new_record,0,sizeof (record));
    time_t t = time(NULL);
    FILE *fp= fopen("C:\\Users\\19030\\CLionProjects\\BMS\\data\\books.bin","rb");
    if(fp==NULL){
        perror("1");
        return;
    }
    while (!feof(fp)){//判断该函数是否已被借出
        book *current_book=(book*) malloc(sizeof (book));
        memset(current_book,0,sizeof (book));
        fread(current_book,sizeof (book),1,fp);
        if(strcmp(current_book->name,name)==0&&current_book->flag==1){
            free(current_book);
            printf("this book already had been taken");
            system("pause");
            system("cls");
            user_interface(current_user);
            break;
        } else{
            free(current_book);
        }
    }
    fclose(fp);
    FILE *fp1= fopen("C:\\Users\\19030\\CLionProjects\\BMS\\data\\record.bin","ab");//录入借书人和借书时间
    if(fp1==NULL){
        perror("1");
        return;
    }
    strcpy(new_record->user_account,current_user->account);
    strcpy(new_record->book_name,name);
    new_record->borrowTime=t;
    new_record->returnTime=t+7*24*60*60;
    if(fwrite(new_record,sizeof (record),1,fp1)==1){//修改书的
        system("cls");
        printf("successfully borrowed");
    } else{
        printf("fail to borrow");
    }
    free(new_record);
    fclose(fp1);

    FILE *fp2= fopen("C:\\Users\\19030\\CLionProjects\\BMS\\data\\books.bin","rb");
    if(fp2==NULL){
        perror("failed to open");
        return;
    }
    book* head=createHeadBook();
    while (!feof(fp2)){
        book *current=(book*) malloc(sizeof (book));
        memset(current,0,sizeof (book));
        fread(current,sizeof (book),1,fp2);
        if(strcmp(current->plate,require_book->plate)!=0){
            appendBook(head,current->ID,current->name,current->author,current->plate,current->publish,current->ISBN,current->price,current->flag);
        } else{
            appendBook(head,current->ID,current->name,current->author,current->plate,current->publish,current->ISBN,current->price,1);
        }
        free(current);
    }
    fclose(fp2);
    FILE *fp3= fopen("C:\\Users\\19030\\CLionProjects\\BMS\\data\\books.bin","wb");
    if(fp3==NULL){
        perror("failed to open");
        return;
    }
    book* current=head->next;
    while (current!=NULL){
        fwrite(current,sizeof (book),1,fp3);
        current=current->next;
    }
    fclose(fp3);
    system("pause");
    system("cls");
    user_interface(current_user);
}


void return_book(char name[32],user* current_user){
    book* require_book= userFindBook(name,current_user);

    record *new_record= findRecord(name,current_user);
    FILE *fp= fopen("C:\\Users\\19030\\CLionProjects\\BMS\\data\\record.bin","rb");
    if(fp==NULL){
        perror("failed to open");
        return;
    }
    memset(new_record,0,sizeof (record));
    fread(new_record,sizeof (record),1,fp);
    FILE *fp1= fopen("C:\\Users\\19030\\CLionProjects\\BMS\\data\\history.bin","ab");
    if(fp1==NULL){
        perror("1");
        return;
    }
    new_record->returnTime=time(NULL);
    if(fwrite(new_record,sizeof (record),1,fp1)==1){
        system("cls");
        printf("successfully returned");
    } else{
        printf("fail to return");
    }
    fclose(fp1);

    FILE *fp4= fopen("C:\\Users\\19030\\CLionProjects\\BMS\\data\\record.bin","rb");
    if(fp4==NULL){
        perror("failed to open");
        return;
    }
    record *temporary_record=(record*) malloc(sizeof (record ));
    record *head_record=createHeadRecord();
    while(!feof(fp4)){
        memset(temporary_record,0,sizeof (record));
        fread(temporary_record,sizeof (record ),1,fp4);
        if(strcmp(temporary_record->user_account,current_user->account)==0&& strcmp(temporary_record->book_name,require_book->name)!=0){
            appendRecord(head_record,temporary_record->user_account,temporary_record->book_name,temporary_record->borrowTime,temporary_record->returnTime);
        }
    }
    fclose(fp4);

    FILE *fp5= fopen("C:\\Users\\19030\\CLionProjects\\BMS\\data\\record.bin","wb");//重新读入record数据
    head_record=head_record->next;
    while (head_record!=NULL){
        fwrite(head_record,sizeof (record ),1,fp5);
        head_record=head_record->next;
    }
    fclose(fp5);


    FILE *fp2= fopen("C:\\Users\\19030\\CLionProjects\\BMS\\data\\books.bin","rb");
    if(fp2==NULL){
        perror("failed to open");
        return;
    }
    book* head=createHeadBook();
    while (!feof(fp2)){
        book *current=(book*) malloc(sizeof (book));
        memset(current,0,sizeof (book));
        fread(current,sizeof (book),1,fp2);
        if(strcmp(current->plate,require_book->plate)!=0){
            appendBook(head,current->ID,current->name,current->author,current->plate,current->publish,current->ISBN,current->price,current->flag);
        } else{
            appendBook(head,current->ID,current->name,current->author,current->plate,current->publish,current->ISBN,current->price,0);
        }
        free(current);
    }
    fclose(fp2);

    FILE *fp3= fopen("C:\\Users\\19030\\CLionProjects\\BMS\\data\\books.bin","wb");
    if(fp3==NULL){
        perror("failed to open");
        return;
    }
    book* current=head->next;
    while (current!=NULL){
        fwrite(current,sizeof (book),1,fp3);
        current=current->next;
    }
    fclose(fp3);
    system("pause");
    system("cls");
    user_interface(current_user);
}

void renew(char name[32],user* current_user,int day){
    FILE *fp0= fopen("C:\\Users\\19030\\CLionProjects\\BMS\\data\\record.bin","rb");
    if(fp0==NULL){
        perror("failed to open");
        return;
    }
    int t=0;
    while (!feof(fp0)){
        record *current_record=(record*) malloc(sizeof (record));
        memset(current_record,0,sizeof (record));
        fread(current_record,sizeof (record),1,fp0);
        if(strcmp(current_record->user_account, current_user->account) == 0&&strcmp(current_record->book_name,name)==0){
            t=1;
        }
        free(current_record);
    }
    if(t==0){
        printf("there is no book that you had borrowed");
        system("pause");
        system("cls");
        user_interface(current_user);
    }
    FILE *fp= fopen("C:\\Users\\19030\\CLionProjects\\BMS\\data\\record.bin","rb");
    if(fp==NULL){
        perror("failed to open");
        return;
    }


    struct stat statStruct;
    stat("C:\\Users\\19030\\CLionProjects\\BMS\\data\\record.bin", &statStruct);
    size_t filesSize = statStruct.st_size;

    record* temporary_head=createHeadRecord();
    for (int i=0;i<(filesSize / sizeof(record));i++) {
        record *current_record=(record*) malloc(sizeof (record));
        memset(current_record,0,sizeof (record));
        fread(current_record,sizeof (record ),1,fp);
        if(strcmp(current_record->user_account, current_user->account) == 0&&strcmp(current_record->book_name,name)==0){
            appendRecord(temporary_head,current_record->user_account,current_record->book_name,current_record->borrowTime,current_record->returnTime+day*24*60*60);
        } else{
            appendRecord(temporary_head,current_record->user_account,current_record->book_name,current_record->borrowTime,current_record->returnTime);
        }
        free(current_record);
    }
    fclose(fp);
    FILE *fp1= fopen("C:\\Users\\19030\\CLionProjects\\BMS\\data\\record.bin","wb");
    if(fp1==NULL){
        perror("failed to open");
        return;
    }
    temporary_head=temporary_head->next;
    while (temporary_head!=NULL){
        fwrite(temporary_head,sizeof (record),1,fp1);
        temporary_head=temporary_head->next;
    }
    fclose(fp1);
    printf("successfully renewed");
    system("pause");
    system("cls");
    user_interface(current_user);
}

void search_history(char account[12],user* current_user){
    FILE *fp= fopen("C:\\Users\\19030\\CLionProjects\\BMS\\data\\history.bin","rb");
    if(fp==NULL){
        perror("failed to open");
        return;
    }
    char t1[128], t2[128], *tmp;
    while (!feof(fp)){
        record *current_record=(record*) malloc(sizeof (record));
        memset(current_record,0,sizeof (record));
        fread(current_record,sizeof (record ),1,fp);
        if(strcmp(current_record->user_account,account)==0){
            tmp = ctime(&current_record->borrowTime);
            strcpy(t1, tmp);
            tmp = ctime(&current_record->returnTime);
            strcpy(t2, tmp);
            printf("account:%s book_name:%s\n borrow_time:%s\n return_time:%s\n",current_record->user_account,current_record->book_name,t1,(t2));
        }
        free(current_record);
    }
    fclose(fp);
    system("pause");
    system("cls");
    admin_interface(current_user);
}