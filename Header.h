#pragma once
#define _CRT_SECURE_NO_WARNINGS 
#define EXIT 0
#define SIGNUP 1
#define LOGIN 2
#define LOGOUT 3
#define VIEW 4
#define SHOW_GOODS 5
#define DEPOSIT 6
#define BUY 7
#define ADD_GOODS 8
#define REMOVE_GOODS 9
#define CHANGE_GOOD_PRICE 10
#define RATE_GOODS 11
#define SEARCH 12

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>


typedef struct vendorstruct vendor;
typedef struct goodnode gnode;
typedef struct buyerstruct buyer;



char** getorder(int*);
int readgoods(struct goodnode* head);
int writegoods(struct goodnode* head);
int writevendors(struct vendorstruct* );
int readvendors(struct vendorstruct* head);
int writebuyers(struct buyerstruct*);
int readbuyers(struct buyerstruct*);
int generateinput(int state,char **input,int numofstrings);
int signup(char user[], char pass[], char role[],vendor* vendor_head,buyer* buyer_head);
int add_vendor(char user[], char pass[],vendor* vendor_head);
int add_buyer(char user[], char pass[], buyer* buyer_head);
int free2darrayofchar(char** input,int numofrows);
vendor* loginvendor(char user[], char pass[], vendor* head);
buyer* loginbuyer(char user[], char pass[], buyer* head);
void viewvendor(vendor*);
void viewbuyer(buyer*);
void showgoods(gnode* head);
void deposit(buyer* temp, char input[]);
int buy(char good_name[], char arr[], char vendorname[],buyer*,vendor*,gnode*);//return values descripted inside function.
int add_good(char good_name[], char arr1[], char arr2[], vendor* vtemp, gnode* good_head);//return values descripted inside function.
int remove_goods(char* good_name, gnode* good_head, vendor* vtemp);
int change_good_price(char* good_name, char* price, gnode* good_head, vendor* vtemp);
int rate_goods(char* good_name, char* vendor_name, char* rating, gnode* good_head,vendor* vendor_head, buyer* btemp);
void free_tmp_list_of_goods(gnode* head);
void delete_node_of_goods_list(gnode* head, gnode* temp);
void print_good(gnode* good);
gnode* create_copied_list_of_goods(gnode* head);
void search(gnode* good_head, char* attribute_value);
gnode* filter_by_max_price(gnode* head,int max_price);
gnode* filter_by_min_price(gnode* head, int min_price);
gnode* filter_by_name(gnode* head, char* good_name);
gnode* filter_by_seller_username(gnode* head, char* seller_username);

struct buyerstruct {
	char username[30];
	char password[30];
	int holding;
	struct goodnode* buyerproducts_head;
	struct buyerstruct* next;
};

struct vendorstruct {
	char username[30];
	char password[30];
	int holding;
	struct goodnode *vendorproducts_head;
	struct vendorstruct* next;
};
struct goodstruct {
	char name[30];
	char vendorname[30];
	int unitprice;
	int stock;
	float rate;
	int buyer_rate;
	int num_of_being_rated;
};
struct goodnode {
	struct goodstruct g;
	struct goodnode* next;
};


typedef struct vendorstruct vendor;
typedef struct goodnode gnode;