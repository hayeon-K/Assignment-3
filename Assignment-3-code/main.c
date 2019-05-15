/*******************************************************************************
 * MASTER
*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "admin.h"
#include "compression.h"
#include "encryption.h"
#include "interface.h"
#include "student.h"

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
void open_admin_prompt();
void open_user_console(user_t user);
void register_user();
int save_db(const user_t *users_p);
int load_user(user_t *users_p);
int is_admin (int ID);
void search_for_student();
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
    open_user_prompt
}
