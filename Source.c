#include "Header.h"
int main() {
	int temporarily_return_value;
	int loopvar = 1;
	char** input;
	int switchvar;
	int i;//number of strings entered in one line.
	int state=0;//state=0 :not logged in /state=1:logged in as a vendor /state=2:logged in as a buyer.
	vendor* vendor_head=(vendor*)malloc(sizeof(vendor));
	vendor_head->next = NULL;
	vendor_head->vendorproducts_head = (gnode*)malloc(sizeof(gnode));
	vendor_head->vendorproducts_head->next = NULL;
	gnode* good_head = (gnode*)malloc(sizeof(gnode));
	good_head->next = NULL;
	buyer* buyer_head = (buyer*)malloc(sizeof(buyer));
	buyer_head->next = NULL;
	buyer_head->buyerproducts_head = (gnode*)malloc(sizeof(gnode));
	buyer_head->buyerproducts_head->next = NULL;
	readbuyers(buyer_head);
	readvendors(vendor_head);
	readgoods(good_head);
	vendor* vtemp=NULL;
	buyer* btemp=NULL;
	gnode* gtemp=NULL;
	while (loopvar) {
		input = getorder(&i);
    	switchvar = generateinput(state, input, i);
		switch (switchvar) {
		case EXIT: {
			writebuyers(buyer_head);
			writegoods(good_head);
			writevendors(vendor_head);
			loopvar = 0;
			break;
		}
		case SIGNUP: {
			if (state!=0)
			{
				printf("NOT ALLOWED!\n");
				break;
			}
			if (signup(input[1], input[2], input[3], vendor_head, buyer_head) == -1) {
				printf("Error in signup.\n");
				break;
			}
			else {
				printf("signup done successfully.\n");
				break;
			}
		}

		case LOGIN: {
			if (state != 0) {
				printf("NOT ALLOWED!\n");
				break;
			}
			if (strcmp(input[3], "seller") == 0) {
				vtemp = loginvendor(input[1], input[2],vendor_head);
				if (vtemp == NULL)
				{
					printf("Incorrect username or password.Or user dosen't exist at all.\n");
					break;
				}
				else {
					printf("Login done successfully.\n");
					state = 1;
					break;
				}
					
			}
			if (strcmp(input[3], "buyer") == 0) {
				btemp = loginbuyer(input[1], input[2],buyer_head);
				if (btemp == NULL)
				{
					printf("Incorrect username or password.Or user dosen't exist at all.\n");
					break;
				}
				else {
					printf("Login done successfully.\n");
					state = 2;
					break;
				}
			}
		}
		case LOGOUT: {
			printf("You logged out.\n");
			btemp = NULL;
			vtemp = NULL;
			state = 0;
			break;
		}
		case VIEW:{
			if (!(state == 1 || state == 2)) {
				printf("NOT ALLOWED.\n");
				break;
			}
			else if (state == 1) {//It means we are logged in as a vendor
				viewvendor(vtemp);
				break;
			}
			else if (state == 2) {//It means we are logged in as a buyer.
				viewbuyer(btemp);
				break;
			}
		}
		case SHOW_GOODS: {
			if (state == 0)
			{
				printf("NOT ALLOWED!\n");
				break;
			}
			else {
				showgoods(good_head);
				break;
			}
		}
		case DEPOSIT: {
			if (state != 2) {
				printf("NOT ALLOWED\n");
				break;
			}
			else {
				//state is 2 and we are logged in as a buyer.
				deposit(btemp,input[1]);
				break;
			}
		}
		case BUY: {
			if (state != 2) {
				printf("NOT ALLOWED!!\n");
				break;
			}
			else {
				temporarily_return_value = buy(input[1], input[2], input[3], btemp, vendor_head, good_head);
				if (temporarily_return_value ==-1) {
					printf("Insufficient credit!!\n");
					break;
				}
				else if (temporarily_return_value ==-2) {
					printf("Not enough considered goods!!\n");
					break;
				}
				else if (temporarily_return_value ==-3) {
					printf("This good dosen't exist at all!!\n");
					break;
				}
				else if (temporarily_return_value ==-4) {
					printf("please don't purchase with negative values!!.\n");
					break;
				}
				else if (temporarily_return_value == -5) {
					printf("This good cannot be selled due to low rate.\n");
					break;
				}
				else if (temporarily_return_value ==0) {
					printf("your purchase done successfully. :)\n");
					break;
				}
			}
		}
		case ADD_GOODS: {
			if (state != 1)
			{
				printf("NOT ALLWED");
				break;
			}
			temporarily_return_value = add_good(input[1], input[2], input[3], vtemp, good_head);
			if (temporarily_return_value == 0) {
				printf("Successfully done!.\n");
				break;
			}
			else if (temporarily_return_value == -1) {
				printf("Please do not enter negative values!!.\n");
				break;
			}
			else if (temporarily_return_value == -2) {
				printf("Good with this name already exists!!.\n");
				break;
			}
		}
		case REMOVE_GOODS: {
			if (remove_goods(input[1], good_head, vtemp) == -1) {
				printf("This good dosen't exist at all!\n");
				break;
			}
			else if (remove_goods(input[1], good_head, vtemp) == -2) {
				printf("This good dosen't belong to you!\n");
				break;
			}
			else {
				printf("Good \"%s\" removed successfully:)\n",input[1]);
				break;
			}
		}
		case CHANGE_GOOD_PRICE: {
			temporarily_return_value = change_good_price(input[1], input[2], good_head, vtemp);
			if (temporarily_return_value == -1)
				printf("This good dosen't exist at all!\n");
		    if (temporarily_return_value == -2)
				printf("This good dosen't belong to you!\n");
		    if (temporarily_return_value == 0)
				printf("Good price changed successfully:)\n");
			break;
		}
		case RATE_GOODS: {
			temporarily_return_value=rate_goods(input[1], input[2], input[3], good_head, vendor_head, btemp);
			if (temporarily_return_value == -1)
				printf("This seller dosen't have good that you said.\n");
			if (temporarily_return_value == -2)
				printf("You already have rated this good.\n");
			if (temporarily_return_value == -3)
				printf("Rating must be an integer between 1 to 5.\n");
			if (temporarily_return_value == -4)
				printf("You didn't purchased this good.So you can not rate it.\n");
			if (temporarily_return_value == 0)
				printf("Good rated successfully.\n");
			break;
		}
		case SEARCH: {
			search(good_head, input[1]);
			break;
		}

		default:
		{
			printf("This order dosen't exist or not allowed.\n");
			break;
		}
		}//end of switch
		free2darrayofchar(input, i);
		getchar();//for '\n'.
	}//end of while 
	return 0;
}//end of program.

