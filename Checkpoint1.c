#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_NO_ITEMS 9
#define MAX_NO_FIRSTNAME 20
#define MAX_NO_LASTNAME 20
#define MAX_NO_FULLNAME 40
#define MAX_NO_CARDNUMBER 20
#define MAX_NO_STUDENT_ID 8
#define MAX_NO_USERS 5
#define MAX_NO_PASSWORD 10
#define MAX_NO_ITEM_NAME 10
#define STUDENT_DB_NAME "students"
#define TRANSACTION_DB_NAME "transactions"


/*******************************************************************************
 * Structs Defined Here
*******************************************************************************/
struct payment{
    char student_id[MAX_NO_STUDENT_ID];
    int card_number;
    char cardholder[MAX_NO_FULLNAME];
    int expiry;
    int CVC;
};
typedef struct payment payment_t;

struct date{
    int day;
    int month;
    int year;
};
typedef struct date date_t;

struct user{
    char first_name[MAX_NO_FIRSTNAME];
    char last_name[MAX_NO_LASTNAME];
    char user_id[MAX_NO_STUDENT_ID + 1];
    date_t birthdate;
    char password[MAX_NO_PASSWORD];
    int payment_valid;
    int is_admin;
};

typedef struct user user_t;

typedef struct admin admin_t;

struct transaction{
    int student_id;
    int transaction_id;
    date_t transaction_date;
};
typedef struct trasaction trasaction_t;

struct item{
    int item_id;
    char item_name[MAX_NO_ITEM_NAME];
    double item_price; 
    char item_size;
};
typedef struct item item_t;



/*******************************************************************************
 * Function prototypes 
*******************************************************************************/
void load_items(item_t *items);
void intro_prompt();
void login(user_t *users);
void open_user_prompt();
void open_admin_prompt();
void open_user_console(user_t user);
void register_user();
int save_db(const user_t *users_p);
int load_user(user_t *users_p);
int is_admin (int ID);
void search();
void edit();
void print();
void add ();
void encrypt ();
void compress ();


/*******************************************************************************
 * Main
 * Authors: Everyone
*******************************************************************************/
int main (void)
{
    item_t items[MAX_NO_ITEMS];
    load_items(items);
    user_t users[MAX_NO_USERS];
    load_user(users);
    

    /*menu would loop unless user enters 3 */
  
}

/*******************************************************************************
 * Function Description
 * Author: Hayeon Kim
*******************************************************************************/

void load_items(item_t *items){
    
}

/*******************************************************************************
 * Function Description
 * Author: Hayeon Kim
*******************************************************************************/
void intro_prompt(){
    printf("\n"
    "Welcome to UTS uniform order page\n"
    "1. Existing user\n"
    "2. New user\n"
    "3. Exit\n"
    "Enter choice 1 - 3>\n");
}

/*******************************************************************************
 * Function Description
 * Author: Hayeon Kim
*******************************************************************************/
void login(user_t *users) {
    char login_id[MAX_NO_STUDENT_ID]; 
    char password[MAX_NO_PASSWORD];
    int existing_user = 1;
    int i ;
    user_t user;


}
/*******************************************************************************
 * Function Description
 * Author: Hayeon Kim
*******************************************************************************/

void open_user_prompt(){
    printf("\n"
    "Welcome to UTS uniform order page\n"
    "1. Order uniform\n"
    "2. View your transaction\n"
    "3. Update my payment details\n"
    "4. Exit\n"
    "Enter choice 1 - 4>\n");
}
/*******************************************************************************
 * Function Description
 * Author: Hayeon Kim
*******************************************************************************/
void open_admin_prompt(){
    printf("\n"
    "Hello, You are in administration mode\n"
    "1. View all transactions\n"
    "2. Search for trasactions\n"
    "3. Search for student\n"
    "4. Exit\n"
    "Enter choice 1 - 4>\n");
}
/*******************************************************************************
 * Function Description
 * Author: Hayeon Kim
*******************************************************************************/

void open_user_console(user_t user){

}

/*******************************************************************************
 * Function Description
 * Author: Hayeon Kim
*******************************************************************************/
void register_user(){

}

/*******************************************************************************
 * Function Description
 * Author: Hayeon Kim
*******************************************************************************/
int save_db(const user_t *users_p){
  
}

/*******************************************************************************
 * Function Description
 * Author: Hayeon Kim
*******************************************************************************/
int load_user(user_t *users_p){
    
}
/*******************************************************************************
 * Function Description
 * Author: Hayeon Kim
*******************************************************************************/
int is_admin (int ID) {

}


/*******************************************************************************
 * Function Description
 * Author: Tom Harris
*******************************************************************************/
void search(){
    
}

/*******************************************************************************
 * Function Description
 * Author: David Bui
*******************************************************************************/
void edit_details(){
    
}

/*******************************************************************************
 * Function Description
 * Author: Mitch Winyard
*******************************************************************************/

void print_transactions(){
    
}

/*******************************************************************************
 * Function Description
 * Author: Mitch Winyard
*******************************************************************************/

void add_student (){

}

/*******************************************************************************
 * Function Description
 * Author: Joel Morrison
*******************************************************************************/

void encrypt (){
    
}

/*******************************************************************************
 * Function Description
 * Author: David Bui
*******************************************************************************/
void compress (){
    
}
