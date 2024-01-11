//
// Created by 19030 on 2023/12/20.
//

#ifndef BMS_BOOK_USER_OPERATION_H
#define BMS_BOOK_USER_OPERATION_H

#include "LinkList.h"

book* findBook(char name[32],user* current_user);

book* adminFindBook(char name[32],user* current_user);

book* userFindBook(char name[32],user* current_user);

user* findUser(char account[12],user* current_user);

record* findRecord(char name[32],user* current_user);

void enter_book(user* current_user);

void delete_book(char name[32],user* current_user);

void revise_book(char name[32],user* current_user);

void delete_user(char account[12],user* current_user);

void revise_user(char account[12],user* current_user);

void borrow_book(char name[32],user* current_user);

void return_book(char name[32],user* current_user);

void renew(char name[32],user* current_user,int day);

void search_history(char account[12],user* current_user);

#endif //BMS_BOOK_USER_OPERATION_H
