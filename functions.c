#include "Header.h"

char** getorder(int* i) {
	char** temp;
	*i = 0;//counter for rows of temp.
	int j = 0;//counter for columns of temp.
	char ch;
	char line[1024];
	int count = 0;//counter for line.
	scanf("%[^\n]", line);
	int size = strlen(line);
	temp = (char**)malloc(sizeof(char*));
	*temp = (char*)malloc(sizeof(char));
	int loop = 1;
	while (loop) {
		if (j != 0)
			temp[*i] = (char*)realloc(temp[*i], sizeof(char) * (j + 1));
		ch = line[count];
		if (ch == ' ') {
			temp[*i][j] = NULL;
			*i = *i + 1;
			temp = (char**)realloc(temp, sizeof(char*) * (*i + 1));
			j = 0;
			*(temp + *i) = (char*)malloc(sizeof(char) * (j + 1));
			while (ch == ' ') {
				count++;
				ch = line[count];
				if (ch != ' ')
					break;
			}
		}
		if (ch == NULL) {
			loop = 0;
		}
		temp[*i][j] = ch;
		count++;
		j++;
	}//end of while.
	return temp;
}//end of get order function.

int readgoods(struct goodnode* head) {
	char ch;
	FILE* fp;
	fp = fopen("good.txt", "r");
	if (fp == NULL)
		return -1;
	ch = fgetc(fp);
	if (ch == EOF)
		return 0;
	else
		rewind(fp);
	struct goodnode *temp;
	temp = head;
	int i = 0;
	while (1) {
		if (feof(fp))
			break;
		temp->next = (struct goodnode*)malloc(sizeof(struct goodnode));
		temp = temp->next;
		char nametemp[30];
		fscanf(fp, "%s", nametemp);
		strcpy(temp->g.name, nametemp);//name of good.
		ch=fgetc(fp);
		if (ch != ' ')
			return -1;
		fscanf(fp, "%s", nametemp);
		strcpy(temp->g.vendorname, nametemp);//name of vendor of that good.
		ch = fgetc(fp);
		if (ch != ' ')
			return -1;
		fscanf(fp, "%d", &(temp->g.unitprice));//unit price:)
		ch = fgetc(fp);
		if (ch != ' ')
			return -1;
		fscanf(fp, "%d", &(temp->g.stock));//how many do we have??!
		ch = fgetc(fp);
		if (ch != ' ')
			return -1;
		fscanf(fp, "%f", &(temp->g.rate));
		ch = fgetc(fp);
		if (ch != ' ')
			return -1;
		fscanf(fp, "%d", &(temp->g.num_of_being_rated));
		if (!feof(fp))
			ch=fgetc(fp);//going to next line:)
	}
	temp->next = NULL;//end of nodes:)
	fclose(fp);
	return 0;//everything just fine thank god.
}

int writegoods(struct goodnode* head) {
	//name vendorname unitprice stock.
	FILE* fp;
	fp = fopen("good.txt", "w");
	if (fp == NULL)
		return -1;
	struct goodnode* temp;
	temp = head;
	while (1) {
		if (temp->next == NULL)
			break;
		temp = temp->next;
		fprintf(fp, "%s", temp->g.name);
		fputc(' ', fp);
		fprintf(fp, "%s", temp->g.vendorname);
		fputc(' ', fp);
		fprintf(fp, "%d", temp->g.unitprice);
		fputc(' ', fp);
		fprintf(fp, "%d", temp->g.stock);
		fputc(' ', fp);
		fprintf(fp, "%f", temp->g.rate);
		fputc(' ', fp);
		fprintf(fp, "%d", temp->g.num_of_being_rated);
		if (temp->next != NULL)
			fputc('\n', fp);
	}
	fclose(fp);
	return 0;
}

int writevendors(struct vendorstruct* head) {
	//username password products
	FILE* fp;
	fp = fopen("vendors.txt", "w");
	if (fp == NULL)
		return -1;
	struct vendorstruct* temp;
	temp = head;
	while (1) {
		if (temp->next == NULL)
			break;
		temp = temp->next;
		fprintf(fp, "%s", temp->username);
		fputc(' ', fp);
		fprintf(fp, "%s", temp->password);
		fputc(' ', fp);
		fprintf(fp, "%d", temp->holding);
		struct goodnode* anotherhead;
		anotherhead = temp->vendorproducts_head;
		if (anotherhead->next!=NULL)
			fputc(' ', fp);
		while (1) {
			if (anotherhead->next == NULL) {
				break;
			}
			anotherhead = anotherhead->next;
			//name vendorname unitprice stock rate num_of_being_rated.
			fprintf(fp, "%s", anotherhead->g.name);
			fputc(' ', fp);
			fprintf(fp, "%s", anotherhead->g.vendorname);
			fputc(' ', fp);
			fprintf(fp, "%d", anotherhead->g.unitprice);
			fputc(' ', fp);
			fprintf(fp, "%d", anotherhead->g.stock);
			fputc(' ', fp);
			fprintf(fp, "%f", anotherhead->g.rate);
			fputc(' ', fp);
			fprintf(fp, "%d", anotherhead->g.num_of_being_rated);
			if (anotherhead->next != NULL)
				fputc(' ', fp);
		}//end of writing goods for current vendor.
		if (temp->next != NULL)
			fputc('\n', fp);
	}//end of writing vendors in file 
	//and now the most important thing 
	fclose(fp);
	return 0;
}

int readvendors(struct vendorstruct* head){
	FILE* fp;
	char ch;
	fp = fopen("vendors.txt", "r");
	if (fp == NULL)
		return -1;
	struct vendorstruct* temp;
	temp = head;
	ch = fgetc(fp);
	if (ch == EOF)
		return 0;
	else
		rewind(fp);
	while (1) {
		if (feof(fp))
			break;
		temp->next = (vendor*)malloc(sizeof(vendor));
		temp = temp->next;
		fscanf(fp, "%s", temp->username);
		ch = fgetc(fp);
		if (ch != ' ')
			return -1;
		fscanf(fp, "%s", temp->password);
		ch = fgetc(fp);
		fscanf(fp, "%d", &temp->holding);
		ch = fgetc(fp);
		temp->vendorproducts_head = (gnode*)malloc(sizeof(gnode));
		gnode* anotherhead = temp->vendorproducts_head;// pointer to link list of goods which is belong to the current vendor.
		while (ch == ' ') {
			anotherhead->next = (gnode*)malloc(sizeof(gnode));
			anotherhead = anotherhead->next;
			//name vendorname unitprice stock.
			fscanf(fp, "%s", anotherhead->g.name);
			ch = fgetc(fp);
			if (ch != ' ')
				return -1;
			fscanf(fp, "%s", anotherhead->g.vendorname);
			ch = fgetc(fp);
			if (ch != ' ')
				return -1;
			fscanf(fp, "%d", &anotherhead->g.unitprice);
			ch = fgetc(fp);
			if (ch != ' ')
				return -1;
			fscanf(fp, "%d", &anotherhead->g.stock);
			ch = fgetc(fp);
			if (ch != ' ')
				return -1;
			fscanf(fp, "%f", &anotherhead->g.rate);
			ch = fgetc(fp);
			if (ch != ' ')
				return -1;
			fscanf(fp, "%d", &anotherhead->g.num_of_being_rated);
			ch = fgetc(fp);
		}
		//end of reading goods of a vendor.//reads the goods of the vendor
		anotherhead->next = NULL;
	}
	temp->next = NULL;
	fclose(fp);
	return 0;
}

int writebuyers(struct buyerstruct* head){
	FILE* fp;
	fp = fopen("buyers.txt", "w");
	if (fp == NULL)
		return -1;
	buyer* temp;
	temp = head;
	while (1) {
		if (temp->next == NULL)
			break;
		temp = temp->next;
		//username password products
		fprintf(fp, "%s", temp->username);
		fputc(' ',fp);
		fprintf(fp, "%s", temp->password);
		fputc(' ',fp);
		fprintf(fp, "%d", temp->holding);
		gnode* anotherhead = temp->buyerproducts_head;
		if (anotherhead->next!=NULL)
			fputc(' ', fp);
		while (1) {
			if (anotherhead->next == NULL)
				break;
			anotherhead = anotherhead->next;
			fprintf(fp, "%s", anotherhead->g.name);
			fputc(' ', fp);
			fprintf(fp, "%s", anotherhead->g.vendorname);
			fputc(' ', fp);
			fprintf(fp, "%d", anotherhead->g.unitprice);
			fputc(' ', fp);
			fprintf(fp, "%d", anotherhead->g.stock);
			fputc(' ', fp);
			fprintf(fp, "%f", anotherhead->g.rate);
			fputc(' ', fp);
			fprintf(fp, "%d", anotherhead->g.num_of_being_rated);
			fputc(' ', fp);
			fprintf(fp, "%d", anotherhead->g.buyer_rate);
			if (anotherhead->next != NULL)
				fputc(' ', fp);
		}
		if (temp->next != NULL)
			fputc('\n', fp);
	}//end of  writing buyers in file.
	fclose(fp);
	return 0;
}

int readbuyers(struct buyerstruct* head) {
	char ch;
	FILE *fp;
	fp = fopen("buyers.txt", "r");
	if (fp == NULL)
		return -1;
	ch = fgetc(fp);
	if (ch == EOF)
		return 0;
	else
		rewind(fp);
	buyer* temp = head;
	while (1) {
		if (feof(fp))
			break;
		temp->next = (buyer*)malloc(sizeof(buyer));
		temp = temp->next;
		fscanf(fp, "%s", temp->username);
		fscanf(fp, "%s", temp->password);
		fscanf(fp, "%d", &temp->holding);
		temp->buyerproducts_head = (gnode*)malloc(sizeof(gnode));
		gnode* anotherhead = temp->buyerproducts_head;
		ch = fgetc(fp);
		while (ch==' ') {
			anotherhead->next = (gnode*)malloc(sizeof(gnode));
			anotherhead = anotherhead->next;
			fscanf(fp, "%s", anotherhead->g.name);
			fscanf(fp, "%s", anotherhead->g.vendorname);
			fscanf(fp, "%d", &anotherhead->g.unitprice);
			fscanf(fp, "%d", &anotherhead->g.stock);
			fscanf(fp, "%f", &anotherhead->g.rate);
			fscanf(fp, "%d", &anotherhead->g.num_of_being_rated);
			fscanf(fp, "%d", &anotherhead->g.buyer_rate);
			ch = fgetc(fp);
		}
		anotherhead->next = NULL;
	}
	temp->next = NULL;
	fclose(fp);
	return 0;
}

int generateinput(int state,char **input,int numofstrings) {//i is the number of strings in char** returned.
	char* string0 = "exit";
	char *string1 = "signup";
	char* string2 = "login";
	char* string3 = "logout";
	char* string4 = "view";
	char* string5 = "show_goods";
	//special for buyers:
	char* string6 = "deposit";
	char* string7 = "buy";
	char* string11 = "rate_goods";
	char* string12 = "search";
	//special for vendors:
	char* string8 = "add_goods";
	char* string9 = "remove_goods";
	char* string10 = "change_goods_price";
	if ((strcmp(input[0], string0) == 0) && numofstrings == 0)
		return 0;
	else if ((strcmp(input[0], string1) == 0) && numofstrings == 3 && state == 0) {
		return 1;//signup
	}
	else if ((strcmp(input[0], string2) == 0) && numofstrings == 3 && state == 0 && (strcmp(input[3], "seller") == 0 || strcmp(input[3], "buyer") == 0)) {
		return 2;//login
	}
	else if ((strcmp(input[0], string3) == 0) && numofstrings == 0 && (state == 1 || state == 2))
		return 3;//logout
	else if ((strcmp(input[0], string4) == 0) && numofstrings == 0 && (state == 1 || state == 2))
		return 4;//view
	else if ((strcmp(input[0], string5) == 0) && numofstrings == 0 && (state == 1 || state == 2))
		return 5;//show_goods
	else if ((strcmp(input[0], string6) == 0) && numofstrings == 1 && state == 2)
		return 6;//deposit 
	else if ((strcmp(input[0], string7) == 0) && numofstrings == 3 && state == 2)
		return 7;//buy
	else if ((strcmp(input[0], string8) == 0) && numofstrings == 3 && state == 1)
		return 8;//add_goods.
	else if ((strcmp(input[0], string9) == 0) && numofstrings == 1 && state == 1)
		return 9;//remove_goods.
	else if ((strcmp(input[0], string10) == 0) && numofstrings == 2 && state == 1)
		return 10;//change_goods_price.
	else if ((strcmp(input[0], string11) == 0) && numofstrings == 3 && state == 2)
		return 11;//rate_goods.
	else if (strcmp(input[0], string12) == 0 && numofstrings == 1 && (state == 1 || state == 2))
		return 12;//search.
	else
		return -1;//order dosen't exist or not allowed.
	return 0;
}

int signup(char user[], char pass[], char role[],vendor* vendor_head, buyer* buyer_head) {
	char* role1 = "seller";
	char* role2 = "buyer";
	int x;
	int returnvalue=0;
	if (strcmp(role, role1) == 0)
		x = 0;//vendor case
	else if (strcmp(role, role2) == 0)
		x = 1;//buyer case
	else
		x = -1;
	switch (x)
	{
	case 0: {
		if (add_vendor(user, pass, vendor_head) == 0) {
			printf("This username already exists.\n");
			returnvalue = -1;
		}
		break;
	}
	case 1: {
		if (add_buyer(user, pass, buyer_head) == 0) {
			printf("This username already exists.\n");
			returnvalue = -1;
		}
		break;
	}


	default:
	{
		returnvalue= -1;
		break;
	}
	}
	return returnvalue;
}

int add_vendor(char user[], char pass[], vendor* vendor_head) {
	int can_create = 1;
	vendor* temp;
	temp = vendor_head;
	while (1) {
		if (temp->next == NULL)
			break;
		temp = temp->next;
		if (strcmp(user, temp->username)==0)
		{
			can_create = 0;
			break;
		}
	}//end of while 
	if (can_create) {
		temp->next = (vendor*)malloc(sizeof(vendor));
		temp = temp->next;
		temp->vendorproducts_head = (gnode*)malloc(sizeof(gnode));
		temp->vendorproducts_head->next = NULL;
		strcpy(temp->username, user);
		strcpy(temp->password, pass);
		temp->holding = 0;
		temp->next = NULL;
	}
	return can_create;
}

int add_buyer(char user[], char pass[], buyer* buyer_head) {
	int can_create = 1;
	buyer* temp;
	temp = buyer_head;
	while (1) {
		if (temp->next == NULL)
			break;
		temp = temp->next;
		if (strcmp(user, temp->username)==0)
		{
			can_create = 0;
			break;
		}
	}//end of while 
	if (can_create) {
		temp->next = (buyer*)malloc(sizeof(buyer));
		temp = temp->next;
		temp->buyerproducts_head = (gnode*)malloc(sizeof(gnode));
		temp->buyerproducts_head->next = NULL;
		strcpy(temp->username, user);
		strcpy(temp->password, pass);
		temp->holding = 0;
		temp->next = NULL;
	}
	return can_create;
}

vendor* loginvendor(char user[], char pass[], vendor* head){
	struct vendorstruct* temp = head;
	int loop = 1;
	while (loop) {
		if (temp->next == NULL)
			break;
		temp = temp->next;
		if ((strcmp(temp->username, user) == 0) && (strcmp(temp->password, pass) == 0))
			loop = 0;
	}
	if (loop == 1)
		temp = NULL;
	return temp;
}

buyer* loginbuyer(char user[], char pass[], buyer* head){
	struct buyerstruct* temp = head;
	int loop = 1;
	while (loop) {
		if (temp->next == NULL)
			break;
		temp = temp->next;
		if ((strcmp(temp->username, user) == 0) && (strcmp(temp->password, pass) == 0))
			loop = 0;
	}
	if (loop == 1)
		temp = NULL;
	return temp;
}

int free2darrayofchar(char** input, int numofrows) {
	for (int i = 0; i < numofrows; i++)
		free(input[i]);
	free(input);
	return 0;
}

void viewbuyer(buyer* temp) {
	printf("username : \"%s\"\n", temp->username);
	printf("role : \"buyer\"\n");
	printf("account balance : %d\n", temp->holding);
	if (temp->buyerproducts_head->next != NULL) {
		printf("products:\n");
	}
	gnode* anotherhead = temp->buyerproducts_head;
	while (anotherhead->next != NULL) {
		anotherhead = anotherhead->next;
		printf("name of product : %s\n", anotherhead->g.name);
		printf("product seller name : %s\n", anotherhead->g.vendorname);
		printf("unitprice : %d\n", anotherhead->g.unitprice);
		printf("Number : %d\n", anotherhead->g.stock);
		if (anotherhead->g.rate == -1)
			printf("The rate you gave : NaN\n");
		else printf("The rate you gave : %d\n", anotherhead->g.buyer_rate);
		if (anotherhead->g.buyer_rate == -1)
			printf("Not rated by you!\n");
		else printf("You have rated this good.\n");
		for (int i = 0; i < 50; i++)
			putchar('-');
		putchar('\n');
	}
}

void viewvendor(vendor* temp){
	printf("username : \"%s\"\n", temp->username);
	printf("role : \"seller\"\n");
	printf("account balance : %d\n", temp->holding);
	if (temp->vendorproducts_head->next != NULL) {
		printf("products:\n");
	}
	gnode* anotherhead = temp->vendorproducts_head;
	while (anotherhead->next != NULL) {
		anotherhead = anotherhead->next;
		printf("name of product : %s\n", anotherhead->g.name);
		printf("product seller name : %s\n", anotherhead->g.vendorname);
		printf("unitprice : %d\n", anotherhead->g.unitprice);
		printf("remaining : %d\n", anotherhead->g.stock);
		if (anotherhead->g.rate == -1)
			printf("rate : NaN\n");
		else printf("rate : %f\n", anotherhead->g.rate);
		for (int i = 0; i < 50; i++)
			putchar('-');
		putchar('\n');
	}
}

void showgoods(gnode* head) {
	gnode* temporarilylist_head;//for creating copied version of goods list.
	gnode* temp;
	temporarilylist_head = create_copied_list_of_goods(head);
	if (temporarilylist_head == NULL || temporarilylist_head->next == NULL)
		printf("Nothing to show yet.\n");
	gnode *priority;
	priority = temporarilylist_head->next;
	temp = priority->next;
	printf("Active Goods are: \n\n");
	while (temporarilylist_head->next != NULL) {
		temp = temporarilylist_head->next;
		priority = temp;
		while (temp!=NULL) {
			if (strcmp(temp->g.name, priority->g.name) < 0)
				priority = temp;
			temp = temp->next;
		}
		if (priority->g.rate >= 2 || priority->g.num_of_being_rated < 5)//Condition that good is activated.
			print_good(priority);
		delete_node_of_goods_list(temporarilylist_head,priority);
	}
	//now deleting temporarily list:
	free_tmp_list_of_goods(temporarilylist_head);
}

void deposit(buyer* temp,char input[]) {
	int deposit;
	if (temp->holding < 0)
		printf("User initialized incorrectly!!\n");
	else
	{
		sscanf(input, "%d", &deposit);
		if (deposit < 0)
			printf("Please enter a positive value.\n");
		else {
			temp->holding += deposit;
			printf("Your credit has been increased successfully.\n");
		}
	}
}

int buy(char good_name[], char arr[], char vendorname[],buyer *btemp,vendor* vendor_head,gnode* good_head) {
	//0: purchase successful.
	//-1: insufficient credit.
	//-2: we don't have enough goods as many you want!!.
	//-3:This good you sayin dosen't exist at all!.
	//-4:Do not purchase with negative values !!!.
	//-5:This good cannot be selled due to low rate.
	gnode* temp;
	gnode* gtemp=good_head;
	vendor* vtemp=vendor_head;
	int exist = 0;
	while (gtemp->next != NULL) {
		gtemp = gtemp->next;
		if ((strcmp(gtemp->g.name, good_name) == 0)&&(strcmp(vendorname,gtemp->g.vendorname)==0)) {
			exist = 1;
			break;
		}
	}
	if (exist == 0)
	{
		gtemp = NULL;
		return -3;
	}
	exist = 0;
	while (vtemp->next != NULL) {
		vtemp = vtemp->next;
		if (strcmp(vtemp->username, vendorname) == 0)
		{
			exist = 1;
			break;
		}
	}
	if (exist == 0)
	{
		vtemp = NULL;
		printf("Unexpected error!!.\n");
		return -3;
	}
	int number;
	sscanf(arr, "%d", &number);
	if (number < 0)
		return -4;
	if (number > gtemp->g.stock)
		return -2;
	int totalcost = number * gtemp->g.unitprice;
	if (totalcost > btemp->holding)
		return -1;
	if (gtemp->g.rate < 2 && gtemp->g.num_of_being_rated>=5 && gtemp->g.rate != -1)
		return -5;
	//okay if we pass untill here everything is fine and we can do our purchase:)
	temp = gtemp;
	btemp->holding -= totalcost;
	vtemp->holding += totalcost;
	gtemp->g.stock -= number;
	gnode* vendorgood = vtemp->vendorproducts_head;
	while (vendorgood->next!=NULL) {
		vendorgood = vendorgood->next;
		if (strcmp(good_name, vendorgood->g.name) == 0)
		{
			break;
		}
	}
	vendorgood->g.stock -= number;
	//now adding good to buyer list of goods:
	gtemp = btemp->buyerproducts_head;
	while (gtemp->next != NULL) {
		gtemp = gtemp->next;
	}
	gtemp->next = (gnode*)malloc(sizeof(gnode));
	gtemp = gtemp->next;
	gtemp->next = NULL;
	strcpy(gtemp->g.name, good_name);
	strcpy(gtemp->g.vendorname, vendorname);
	gtemp->g.stock = number;
	gtemp->g.unitprice = vendorgood->g.unitprice;
	gtemp->g.buyer_rate = -1;//means not rated yet.
	gtemp->g.rate = temp->g.rate;
	gtemp->g.num_of_being_rated = temp->g.num_of_being_rated;
    return 0;
}

int add_good(char good_name[], char arr1[], char arr2[], vendor* vtemp, gnode* good_head) {
	//-1: good_count or good_price is negative.
	//-2: good with the name entered belongs to the other seller.
	//0: good added successfully.
	gnode* anotherhead;//we can use this to navigate into seller products list.
	int good_count, good_price;
	sscanf(arr1, "%d", &good_price);
	sscanf(arr2, "%d", &good_count);
	if (good_price < 0 || good_count < 0)
		return -1;
	gnode* gtemp;
	gtemp = good_head;
	int check1, check2;
	int can_create = 1;
	int can_add = 0;
	while (gtemp->next != NULL) {
		gtemp = gtemp->next;
		check1 = strcmp(good_name, gtemp->g.name);
		check2 = strcmp(vtemp->username, gtemp->g.vendorname);
		if (check1==0 && check2==0) {//good is exist and it belongs to the seller that already logged in.
			can_add = 1;
			can_create = 0;
			break;
		}
		if (check1 == 0 && check2 != 0) {//good is exist but it dosen't belong to the seller that logged in.
			can_create = 0;
			can_add = 0;
			break;
		}	
	}
	//good dosen't exist at all and we have to create it:
	if (can_create && !can_add) {
		gtemp->next = (gnode*)malloc(sizeof(gnode));//adding good into general list of goods.
		gtemp = gtemp->next;
		gtemp->next = NULL;
		strcpy(gtemp->g.name, good_name);
		strcpy(gtemp->g.vendorname, vtemp->username);
		gtemp->g.stock = good_count;
		gtemp->g.unitprice = good_price;
		gtemp->g.num_of_being_rated = 0;
		gtemp->g.rate = -1;
		anotherhead = vtemp->vendorproducts_head;
		while (anotherhead->next != NULL)
			anotherhead = anotherhead->next;
		anotherhead->next = (gnode*)malloc(sizeof(gnode));//adding good into seller products...
		anotherhead = anotherhead->next;
		anotherhead->next = NULL;
		strcpy(anotherhead->g.name, good_name);
		strcpy(anotherhead->g.vendorname,vtemp->username);
		anotherhead->g.stock = good_count;
		anotherhead->g.unitprice = good_price;
		anotherhead->g.num_of_being_rated = 0;
		anotherhead->g.rate = -1;//not rated yet.
	}
	//good with the name entered belongs to the other seller:
	if (!can_create && !can_add)
		return -2;
	//good already exists and we have to add to it:)
	if (!can_create && can_add)
	{
		gtemp->g.stock += good_count;
		gtemp->g.unitprice = good_price;
		anotherhead = vtemp->vendorproducts_head;
		while (strcmp(anotherhead->g.name, good_name) != 0)
			anotherhead = anotherhead->next;
		anotherhead->g.stock += good_count;
		anotherhead->g.unitprice = good_price;
	}
	return 0;
}

int remove_goods(char* good_name, gnode* good_head, vendor* vtemp) {
	//0 : everything is ok:)
	//-1: this good dosen't exist at all!!
	//-2: this good belogns to the other seller!!
	int returnvalue=-1;
	gnode* gtemp;
	gtemp = good_head;
	while (gtemp->next != NULL) {
		if ((strcmp(gtemp->next->g.name, good_name) == 0) && !(strcmp(gtemp->next->g.vendorname, vtemp->username)==0) )
		{
			returnvalue = -2;
			break;
		}
		else if ((strcmp(gtemp->next->g.name, good_name) == 0)&&(strcmp(gtemp->next->g.vendorname,vtemp->username)==0))
		{
			returnvalue = 0;
			break;
		}
		gtemp = gtemp->next;
	}
	if (returnvalue != 0)
		return returnvalue;
	gnode* vendorproducts;
	vendorproducts = vtemp->vendorproducts_head;
	while (vendorproducts->next != NULL)
	{
		if (strcmp(vendorproducts->next->g.name, good_name) == 0)
			break;
		vendorproducts = vendorproducts->next;
	}
	//now deleting:
	//from list of goods:
	gnode* temp;
	temp = gtemp->next;
	gtemp->next = temp->next;
	free(temp);
	//from list of vendorproducts :
	temp = vendorproducts->next;
	vendorproducts->next = temp->next;
	free(temp);
	//done:)
	return returnvalue;
}

int change_good_price(char* good_name, char* price, gnode* good_head, vendor* vtemp) {
	//0:Done successfully.
	//-1:Good dosen't exist!
	//-2:Good dosen't belong to you!
	int returnvalue = -1;
	int unitprice;
	sscanf(price, "%d", &unitprice);
	gnode* gtemp;
	gtemp = good_head;
	while (gtemp->next != NULL) {
		if ((strcmp(gtemp->next->g.name, good_name) == 0) && !(strcmp(gtemp->next->g.vendorname, vtemp->username) == 0))
		{
			returnvalue = -2;
			break;
		}
		else if ((strcmp(gtemp->next->g.name, good_name) == 0) && (strcmp(gtemp->next->g.vendorname, vtemp->username) == 0))
		{
			returnvalue = 0;
			break;
		}
		gtemp = gtemp->next;
	}
	if (returnvalue != 0)
		return returnvalue;
	//changing price in list of goods:
	gtemp = gtemp->next;
	gtemp->g.unitprice = unitprice;
	//changing price in list of vendorgoods:
	gtemp = vtemp->vendorproducts_head;
	while (gtemp->next != NULL)
	{
		gtemp = gtemp->next;
		if (strcmp(gtemp->g.name, good_name) == 0)
			break;
	}
	gtemp->g.unitprice = unitprice;
	//finished:))
	return returnvalue;
}

int rate_goods(char* good_name,char* vendor_name,char* rating,gnode* good_head,vendor* vendor_head,buyer* btemp){
	//return values:
	//0  :Done successfully.
	//-1 : This seller dosen't have good that you said.
	//-2 : You already have rated this good.
	//-3 : Rating must be an integer between 1 to 5.
	//-4 : You didn't purchased this good.

	int rate;
	sscanf(rating, "%d", &rate);
	if (1 > rate || rate > 5)
		return -3;
	int ability_to_rate = 0;
	vendor* vtemp;
	gnode* lg_temp;//list of goods temporarily pointer.
	gnode* lbg_temp;//list of buyer's goods temporarily pointer.
	gnode* lvg_temp;//list of vendor's goods temporarily pointer.
	lg_temp = good_head;
	while (lg_temp != NULL) {
		if ((strcmp(lg_temp->g.name, good_name) == 0) && (strcmp(lg_temp->g.vendorname, vendor_name) == 0)) {
			ability_to_rate = 1;
			break;
		}
		lg_temp = lg_temp->next;
	}
	if (!ability_to_rate)
		return -1;
	ability_to_rate = 0;
	lbg_temp = btemp->buyerproducts_head;
	while (lbg_temp->next != NULL) {
		lbg_temp = lbg_temp->next;
		if (strcmp(lbg_temp->g.name, good_name) == 0){
			if (lbg_temp->g.buyer_rate != -1)
				return -2;
			ability_to_rate = 1;
			break;
		}
	}
	if (!ability_to_rate)
		return -4;
	//now rating:
	//must be done in :
	//1) list of goods.
	//2) list of buyer products.
	//3) list of vendor products.
	vtemp = vendor_head;
	while (vtemp->next != NULL)
	{
		vtemp = vtemp->next;
		if (strcmp(vtemp->username, vendor_name) == 0)
			break;
	}
	lvg_temp = vtemp->vendorproducts_head;
	while (lvg_temp->next != NULL)
	{
		lvg_temp = lvg_temp->next;
		if (strcmp(lvg_temp->g.name, good_name) == 0) {
			if (lvg_temp->g.rate == -1)
			{
				lvg_temp->g.rate =rate;
				lvg_temp->g.buyer_rate = rate;
				lvg_temp->g.num_of_being_rated++;
			}
			else {
				lvg_temp->g.rate = lvg_temp->g.rate * lvg_temp->g.num_of_being_rated;
				lvg_temp->g.rate += rate;
				lvg_temp->g.num_of_being_rated++;
				lvg_temp->g.rate = lvg_temp->g.rate / lvg_temp->g.num_of_being_rated;
			}
		}
	}

	if (lbg_temp->g.rate == -1)
	{
		lbg_temp->g.rate = rate;
		lbg_temp->g.buyer_rate = rate;
		lbg_temp->g.num_of_being_rated++;
	}
	else {
		lbg_temp->g.rate = lbg_temp->g.rate * lbg_temp->g.num_of_being_rated;
		lbg_temp->g.rate += rate;
		lbg_temp->g.num_of_being_rated++;
		lbg_temp->g.rate = lbg_temp->g.rate / lbg_temp->g.num_of_being_rated;
		lbg_temp->g.buyer_rate = rate;
	}


	if (lg_temp->g.rate == -1)
	{
		lg_temp->g.rate = rate;
		lg_temp->g.buyer_rate = rate;
		lg_temp->g.num_of_being_rated++;
	}
	else {
		lg_temp->g.rate = lg_temp->g.rate * lg_temp->g.num_of_being_rated;
		lg_temp->g.rate += rate;
		lg_temp->g.num_of_being_rated++;
		lg_temp->g.rate = lg_temp->g.rate / lg_temp->g.num_of_being_rated;
	}
	return 0;
}

void free_tmp_list_of_goods(gnode* head) {
	gnode* current, * before;
	current = head;
	while (current != NULL)
	{
		before = current;
		current = current->next;
		free(before);
	}
}

void delete_node_of_goods_list(gnode* head, gnode* temp) {
	gnode* gtemp;
	gtemp = head;
	while (gtemp != NULL)
	{
		if (gtemp->next == temp)
			break;
		gtemp = gtemp->next;
	}
	gtemp->next = temp->next;
	free(temp);
	//done:)
}

void print_good(gnode* temp) {
	printf("Name : %s\n", temp->g.name);
	printf("seller name : %s\n", temp->g.vendorname);
	printf("unitprice : %d\n", temp->g.unitprice);
	printf("remaining : %d\n", temp->g.stock);
	if (temp->g.rate == -1)
		printf("rate : NaN\n");
	else
		printf("rate : %f\n", temp->g.rate);
	for (int i = 0; i < 20; i++)
		putchar('-');
	putchar('\n');
}

gnode* create_copied_list_of_goods(gnode* head) {

	gnode* temporarilylist_head;//for creating copied version of goods list.
	gnode* temporarilylist;
	temporarilylist_head = NULL;
	if (head->next == NULL) {
		return NULL;
	}
	gnode* temp = head;
	if (temp != NULL) {
		temporarilylist_head = (gnode*)malloc(sizeof(gnode));
		temporarilylist = temporarilylist_head;
	}
	else {
		return NULL;
	}
	//creating copied list:
	while (temp->next != NULL)
	{
		temp = temp->next;
		temporarilylist->next = (gnode*)malloc(sizeof(gnode));
		temporarilylist = temporarilylist->next;
		strcpy(temporarilylist->g.name, temp->g.name);
		strcpy(temporarilylist->g.vendorname, temp->g.vendorname);
		temporarilylist->g.unitprice = temp->g.unitprice;
		temporarilylist->g.stock = temp->g.stock;
		temporarilylist->g.rate = temp->g.rate;
		temporarilylist->g.num_of_being_rated = temp->g.num_of_being_rated;
	}
	temporarilylist->next = NULL;
	return temporarilylist_head;
}

void search(gnode* good_head, char* number_of_conditions) {
	//-1: attribute_value is negative or isn't integer between 1 to 4.
	gnode* head = create_copied_list_of_goods(good_head);
	int switchvar;//1:max_price  2:min_price  3:name  4:seller_username
	int num_of_words;
	int attribute_value;
	int check_input;
	char** temp;
	char** specification_max_price = NULL;
	char** specification_min_price = NULL;
	char** specification_name = NULL;
	char** specification_seller_username = NULL;
	int num_of_specifications;
	sscanf(number_of_conditions, "%d", &num_of_specifications);
	if (!(1 <= num_of_specifications && num_of_specifications <= 4)) {
		printf("Number of conditions must be an integer between 1 to 4.\n");
		return ;
	}
	while (num_of_specifications!=0) {
		getchar();
		temp = getorder(&num_of_words);
		check_input = sscanf(temp[1], "%d", &attribute_value);
		if (num_of_words != 1)
		{
			printf("Wrong input.Try again.\n");
			free2darrayofchar(temp, num_of_words);
			continue;
		}
		if (strcmp(temp[0], "max_price") == 0 && specification_max_price == NULL) {
			specification_max_price = temp;
			switchvar = 1;
		}
		else if (strcmp(temp[0], "min_price") == 0 && specification_min_price == NULL) {
			specification_min_price = temp;
			switchvar = 2;
		}
		else if (strcmp(temp[0], "name") == 0 && specification_name == NULL) {
			specification_name = temp;
			switchvar = 3;
		}
		else if (strcmp(temp[0], "seller_username") == 0 && specification_seller_username == NULL) {
			specification_seller_username = temp;
			switchvar = 4;
		}
		else {
			printf("Wrong input.Try again.\n");
			free2darrayofchar(temp, num_of_words);
			continue;
		}
		switch (switchvar) {
		case 1: {
			if (attribute_value < 0 || check_input == 0)
			{
				printf("Wrong input.Try again.\n");
				free2darrayofchar(temp, num_of_words);
				specification_max_price = NULL;
				continue;
			}
			else {
				//filtering :
				filter_by_max_price(head, attribute_value);
				num_of_specifications--;
			}
			break;
		}
		case 2: {
			if (attribute_value < 0 || check_input == 0)
			{
				printf("Wrong input.Try again.\n");
				free2darrayofchar(temp, num_of_words);
				specification_min_price = NULL;
				continue;
			}
			else {
				//filtering :
				filter_by_min_price(head, attribute_value);
				num_of_specifications--;
			}
			break;
		}
		case 3: {
			//filtering :
			filter_by_name(head, specification_name[1]);
			num_of_specifications--;
			break;
		}
		case 4: {
			//filtering : 
			filter_by_seller_username(head, specification_seller_username[1]);
			num_of_specifications--;
			break;
		}
		}
		free2darrayofchar(temp, num_of_words);
	}
	//now representing result to the user :
	showgoods(head);
	free_tmp_list_of_goods(head);
}

gnode* filter_by_max_price(gnode* head, int max_price) {
	gnode* temp = head;
	while (temp->next != NULL)
	{
		temp = temp->next;
		if (temp->g.unitprice > max_price) {
			delete_node_of_goods_list(head, temp);
			temp = head;
		}
	}
	return head;
}

gnode* filter_by_min_price(gnode* head, int min_price) {
	gnode* temp = head;
	while (temp->next != NULL)
	{
		temp = temp->next;
		if (temp->g.unitprice < min_price) {
			delete_node_of_goods_list(head, temp);
			temp = head;
		}
	}
	return head;
}

gnode* filter_by_name(gnode* head, char* good_name) {
	gnode* temp;
	temp = head;
	while (temp->next != NULL) {
		temp = temp->next;
		if (!(strcmp(temp->g.name, good_name) == 0))
		{
			delete_node_of_goods_list(head, temp);
			temp = head;
		}
	}
	return head;
}

gnode* filter_by_seller_username(gnode* head, char* seller_username) {
	gnode* temp;
	temp = head;
	while (temp->next != NULL) {
		temp = temp->next;
		if (!(strcmp(temp->g.vendorname, seller_username) == 0))
		{
			delete_node_of_goods_list(head, temp);
			temp = head;
		}
	}
	return head;
}
