#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "compression.c"

#define MAX_NO_ITEMS 6
#define MAX_NO_FIRSTNAME 15
#define MAX_NO_LASTNAME 15
#define MAX_NO_CARDNUMBER 20
#define MAX_NUM_TRANSACTIONS 20
#define MAX_NO_STUDENT_ID 8
#define MAX_NO_USERS 20
#define MAX_NO_PASSWORD 20
#define MAX_NO_ITEM_NAME 10
#define MAX_NO_CARD 17
#define MAX_NO_CVC 4
#define MAX_NO_PHONE 11
#define STUDENT_DB_NAME "students"
#define TRANSACTION_DB_NAME "transactions"

/*Insert structs here*/
struct payment{
    char card_number[MAX_NO_CARD];
    int month;
    int year;
    char cvc[MAX_NO_CVC];
};
typedef struct payment payment_t;

struct user{
    char first_name[MAX_NO_FIRSTNAME];
    char last_name[MAX_NO_LASTNAME];
    int user_id;
    char password[MAX_NO_PASSWORD];
    char phone[MAX_NO_PHONE];
    payment_t payment; 
};
typedef struct user user_t;

/*functions*/
void login(user_t *users);
void login_as_admin(user_t *users, int * no_of_user);
void intro_prompt();
void item_prompt();
int load_user(user_t *users_p, int * no_of_user);
void open_user_console(user_t user);
void open_admin_console(user_t *users, int * no_of_user);
void order_uniform(user_t user);
void view_my_transaction(user_t user);
void update_payment(user_t user);
void view_transactions();
void search_transaction();
void search_student(user_t *users);
void update_prompt();
int load_payments(payment_t * payments);
int has_transaction(user_t user);
int check_user_input(const char *entered_id, int * login_id);
int is_right_format_number(char c);
int existing_student(int id, user_t * users);
int check_user_name(char * user_input, char * name);
void add_student(user_t *users, int * no_of_user);
int no_of_lines();
int save_db(const user_t *users_p, int * no_of_user);

int main (void)
{

    user_t users[MAX_NO_USERS];
    int no_of_user;
    load_user(users, &no_of_user);

    /*int variable that would store user input for menu*/
    int choice;

    /*menu would loop unless user enters 3 */
    while(choice != 3) { 
        intro_prompt();    /* print login prompt */
        if(scanf("%d", &choice) != 1){     /* if user input is NOT digit */    
            while ((getchar()) != '\n');      /* flush input buffer */
            printf("Invalid choice \n");      /* prints error message */
        } else {     /* if user input is digit */
            switch(choice){
                case 1: 
                    login(users);
                    break;
                case 2:
                    login_as_admin(users, &no_of_user);
                    break;
                case 3:
                    break;
                default:      /* when user input is digit but not 1-5 */
                    printf("Invalid choice \n"); 
                    break;
            }    
        }
    }
    return 0;
}


void intro_prompt(){
    printf("\n"
    "Welcome to UTS uniform order page\n"
    "1. Login as STUDENT\n"
    "2. Login as ADMIN\n"
    "3. Exit\n"
    "Enter choice 1 - 3>\n");
}

int check_user_id_input(const char *entered_id, int * login_id){
    /* if user input is too long, format test fails */
    if(strlen(entered_id) > MAX_NO_STUDENT_ID + 1){ 
        return 0; 
    }
    int i;
    char temp[MAX_NO_STUDENT_ID + 1];
    for(i = 0; i < MAX_NO_STUDENT_ID + 1; i++){
        temp[i] = entered_id[i];
    }
    for(i = 0; i < MAX_NO_STUDENT_ID ; i++){
        if(!is_right_format_number(temp[i])){
            return 0;
        }
    }
    sscanf(temp, "%d", login_id);
    return 1;
}

int is_right_format_number(char c){
    if((c >= '0' && c <= '9')){
       return 1;
    }
    return 0;
}

/*Insert function protoypes here*/
void login_as_admin(user_t *users, int *no_of_user) {
    char login_id[5]; 
    char password[MAX_NO_PASSWORD];
    int is_admin = 1;

    while(is_admin){
        printf("Enter your id \n");
        scanf("%s", login_id);
        if(!strcmp(login_id, "admin")) { is_admin = 0; } 
        else { printf("Invalid admin username. Please check again! \n"); }
    }
    int right_password = 1;
    while(right_password){
        printf("Enter your password \n");
        scanf("%s", password); 
        if(!strcmp(password, "admin")){
            printf("Welcome, %s \n", "ADMIN");
            open_admin_console(users, no_of_user);
            right_password = 0;
        } else {
            printf("Invalid password. Please check again! \n");
        }
    }
}

void login(user_t *users) {
    char user_input[1000] = {};
    int login_id, i; 
    char password[MAX_NO_PASSWORD];
    int existing_user = 1;
    user_t user;
    while ((getchar()) != '\n'); 
    while(existing_user){
        printf("Enter your id: \n");
        fgets(user_input, 10000 ,stdin); 
        if(check_user_id_input(user_input, &login_id) == 1){
            for(i = 0; i < MAX_NO_USERS; i++){
                if(login_id == users[i].user_id){
                    user = users[i];
                    existing_user = 0; 
                } 
            }
            if(user.user_id == '\0') {
                printf("Invalid user! \n");
            }
        } else {
            printf("Invalid ID");
        }
    }
    int right_password = 1;
    while(right_password){
        printf("Enter your password \n");
        scanf("%s", password); 
        if(!strcmp(password, user.password)){
            printf("Welcome, %s \n", user.first_name);
            open_user_console(user);
            right_password = 0;
        } else {
            printf("Invalid password. Please check again! \n");
        }
    }
}


void open_user_prompt(){
    printf("\n"
    "Welcome to UTS uniform order page\n"
    "1. Order uniform\n"
    "2. View your transaction\n"
    "3. Update my payment details\n"
    "4. Exit\n"
    "Enter choice 1 - 4>\n");
}

void open_admin_prompt(){
    printf("\n"
    "Hello, You are in administration mode\n"
    "1. View all transactions\n"
    "2. Search for trasactions\n"
    "3. Search for student\n"
    "4. Exit\n"
    "Enter choice 1 - 5>\n");
}

void open_user_console(user_t user){
    int choice;
    while(choice != 4){ 
        open_user_prompt();    /* print login prompt */
        if(scanf("%d", &choice) != 1){     /* if user input is NOT digit */    
            while ((getchar()) != '\n');      /* flush input buffer */
            printf("Invalid choice \n");      /* prints error message */
        } else {     /* if user input is digit */
            switch(choice){
                case 1: 
                    order_uniform(user);
                    break;
                case 2:
                    view_my_transaction(user);
                    break;
                case 3:
                    break;
                case 4:
                    break;
                default:      /* when user input is digit but not 1-5 */
                    printf("Invalid choice \n"); 
                    break;
            }    
        }
    }
}

void open_admin_console(user_t *users, int *no_of_user){
    int choice;
    while(choice != 5){ 
        open_admin_prompt();    /* print login prompt */
        if(scanf("%d", &choice) != 1){     /* if user input is NOT digit */    
            while ((getchar()) != '\n');      /* flush input buffer */
            printf("Invalid choice \n");      /* prints error message */
        } else {     /* if user input is digit */
            switch(choice){
                case 1: 
                    view_transactions();
                    break;
                case 2:
                    search_transaction();
                    break;
                case 3:
                    search_student(users);
                    break;
                case 4:
                    add_student(users, no_of_user);
                    break;
                case 5:
                    break;
                default:      /* when user input is digit but not 1-5 */
                    printf("Invalid choice \n"); 
                    break;
            }    
        }
    } 
}

/*****************************************************************************/
int save_db(const user_t *users_p, int * no_of_user){
     /* Pointer to the file */
    FILE *fp;

     /* Opening a file in w mode*/
    fp = fopen(STUDENT_DB_NAME, "w");

    /* If there is issue opening file, print error message and finish */
    if(fp == NULL){
        printf("Write error\n");
        return 1;
    } 

    /* int variable for for loop */
    int i;

    /* loop the number of flights and write to file in certain format, 
        changing line with each flight  */
    for(i = 0; i < MAX_NO_USERS; i++){
        fprintf(fp, "%s %s %d %s %s %s %d %d %s\n",
               users_p[i].first_name, users_p[i].last_name, users_p[i].user_id,
               users_p[i].password, users_p[i].phone, users_p[i].payment.card_number, users_p[i].payment.month,
               users_p[i].payment.year, users_p[i].payment.cvc);
    }

    /* close file */
    fclose(fp);
    return 0;
}
/*****************************************************************************/
int load_user(user_t *users_p, int * no_of_user){
     /* Pointer to the file */
    FILE *fp;

     /* Opening a file in r mode */
    fp = fopen(STUDENT_DB_NAME, "r");

    /* If fp is NULL, print error message and finish */ 
    if(fp == NULL){
        printf("Students not loaded. Is database in right folder? \n");
        return 1;
    } 

    /* variable for while loop */
    int i = 0;

    /* while incrementing i is not equal to no_of_lines which 
        stores the number of new lines (=flights) in text file,
        read from file and store that into flights array */
    while(i != no_of_lines()){
        fscanf(fp, "%s %s %d %s %s %s %d %d %s",
               users_p[i].first_name, users_p[i].last_name, &users_p[i].user_id, users_p[i].password, users_p[i].phone,
               users_p[i].payment.card_number, &users_p[i].payment.month, &users_p[i].payment.year, 
               users_p[i].payment.cvc);
        i++;
    }
    printf("%d %d", no_of_lines(), i);
    *no_of_user = i;
    /* close file */
    fclose(fp);
    return 0;
}

int no_of_lines(){
     /* Pointer to the file */
    FILE *fp;

     /* Opening a file in r mode */
    fp = fopen(STUDENT_DB_NAME, "r"); 

    /* If no file is found, return 0 */
    if(fp == NULL){
        return 0;
    } 
 
    /* int variable to count number of lines in textfile */
    int count_lines = 0;

    /* char variable to store char from file */
    char chr = getc(fp);

   /* while chr variable is not at end of file, count all new line by
       counting '\n' and increment int variable count_lines by 1 
       and reassign chr with next char */
    while (chr != EOF){
        if (chr == '\n'){
            count_lines++;
        }
        chr = getc(fp);
    }

    return count_lines;
}

void item_prompt(){
    printf("\n"
    "Choose from options below\n"
    "1. Shirt-L\n"
    "2. Shirt-M\n"
    "3. Shirt-S\n"
    "4. Shorts-L\n"
    "5. Shorts-M\n"
    "6. Shorts-S\n"
    "Enter choice 1 - 6>\n");
}

void order_uniform(user_t user){
    if(has_transaction(user)){
        printf("Cannot make another transaction. You already made one transaction.");
        return;
    }
    char * item_name;
    int choice;
    item_prompt();
    scanf("%d", &choice);
    switch(choice){
        case 1:
            item_name = (char*)malloc(sizeof(char) * 7); 
            strcpy(item_name, "Shirt-L");
            break;
        case 2: 
            item_name = (char*)malloc(sizeof(char) * 7); 
            strcpy(item_name, "Shirt-M");
            break;
        case 3:
            item_name = (char*)malloc(sizeof(char) * 7); 
            strcpy(item_name, "Shirt-S");
            break;
        case 4:
            item_name = (char*)malloc(sizeof(char) * 8); 
            strcpy(item_name, "Shorts-L");
            break;
        case 5: 
            item_name = (char*)malloc(sizeof(char) * 8); 
            strcpy(item_name, "Shorts-M");
            break;
        case 6:
            item_name = (char*)malloc(sizeof(char) * 8); 
            strcpy(item_name, "Shorts-S");
            break;
        default:      /* when user input is digit but not 1-5 */
            printf("Invalid choice \n"); 
            break;
    }    

    int i, size = 0 ; 
    transaction_t * transactions;
    transaction_t * temp;
    temp = read_database(&size);
    transactions = (transaction_t*) malloc (sizeof(transaction_t) * (size + 1));
    for(i = 0 ; i < size; i++){
        transactions[i]= temp[i];
    }

    transaction_t transaction; 
    transaction.user_id=  user.user_id;
    strcpy(transaction.item_name, item_name);
    transaction.quantity = 1;
    transactions[size] = transaction; 

    code_t code[22];
    huffman(code);
    create_compression(code, transactions, size + 1);
}

void view_my_transaction(user_t user){
    if(!has_transaction(user)){
        printf("You have NO transaction yet.");
        return;
    }
    transaction_t * transactions; 
    int i, size = 0;
    decompress_to_file();
    transactions = read_database(&size);
    transaction_t transaction; 
    for(i = 0 ; i < size; i++){
        if(user.user_id == transactions[i].user_id){
	    transaction = transactions[i];    
        }
    }
    printf("Item purchased  Quantity\n");
    printf("--------------- ---------------\n");
    printf("%-15s %-15d\n",  transaction.item_name, transaction.quantity);
}

int has_transaction(user_t user){
    transaction_t * transactions; 
    int i, size = 0;
    decompress_to_file();
    transactions = read_database(&size);
    for(i = 0 ; i < size; i++){
        if(user.user_id == transactions[i].user_id){
	    return 1;
        }
    }
    return 0;
}

void view_transactions(){
    transaction_t * transactions; 
    int i, size = 0;
    decompress_to_file();
    transactions = read_database(&size);
    printf("Transaction User ID  Item purchased  Quantity\n");
    printf("-------------------- --------------- ---------------\n");
    for(i = 0 ; i < size; i++){
       printf("%-20d %-15s %-15d\n", transactions[i].user_id, transactions[i].item_name,
            transactions[i].quantity);    
    }
}


void search_transaction(){
    printf("Enter the student ID:\n");
    int login_id; 
    scanf("%d", &login_id); 

    transaction_t * transactions; 
    int i, size = 0;
    decompress_to_file();
    int has_item = 0;
    transactions = read_database(&size);
    transaction_t transaction; 
    for(i = 0 ; i < size; i++){
        if(login_id == transactions[i].user_id){
	    transaction = transactions[i];   
            has_item = 1; 
        }
    }
    if(has_item){
        printf("Transaction User ID  Item purchased  Quantity\n");
        printf("-------------------- --------------- ---------------\n");
        printf("%-20d %-15s %-15d\n", transaction.user_id, transaction.item_name,
            transaction.quantity);
    } else {
        printf("No transaction made by that student\n");
    }
}

void search_student(user_t *users){
    int search_id; 
    int existing_user = 0;
    int i;
    user_t user;

    printf("Enter the student id:\n");
    scanf("%d", &search_id); 
    for(i = 0 ; i < MAX_NO_USERS; i++){
        if(search_id == users[i].user_id){
            user = users[i];
            existing_user = 1; 
        } 
    }
    if(existing_user){
        printf("First Name      Last Name       Student ID      Phone Number \n");
        printf("--------------- --------------- --------------- --------------- \n");
        printf("%-15s %-15s %-15d %-15s\n", user.first_name, user.last_name, user.user_id, user.phone);
    } else {
        printf("No students in database");
    }
}

int existing_student(int id, user_t * users){
    int i;
    for(i = 0 ; i < MAX_NO_USERS; i++){
        if(id == users[i].user_id){
            return 1;
        } 
    }
    return 0;
}

void add_student(user_t *users, int * no_of_user) {
    user_t new;
    int valid_id = 1;
    int valid_lastname = 1;
    int valid_firstname = 1;
    char user_input[1000] = {};
    int signup_id;
    char first_name[MAX_NO_FIRSTNAME];
    char last_name[MAX_NO_LASTNAME];
    printf("%d", no_of_lines());
    printf("no of user: %d ", *no_of_user);
    while ((getchar()) != '\n'); 
    while(valid_id){
        printf("Enter new student id:\n");
        fgets(user_input, 10000 ,stdin); 
        if(check_user_id_input(user_input, &signup_id)){
            if(existing_student(signup_id, users)){
                printf("You already have that student in the database\n");
            } else {
                new.user_id = signup_id;
                valid_id = 0; 
            }
        } else {
            printf("Your input is not valid");
        }
    }

    while(valid_firstname){
        printf("Enter first name:\n");
        fgets(user_input, 10000 ,stdin); 
        if(check_user_name(user_input, first_name)){
            first_name[strlen(first_name)-1] ='\0';
            strcpy(new.first_name, first_name); 
            valid_firstname = 0;
        }
    }
    while(valid_lastname){
        printf("Enter last name:\n");
        fgets(user_input, 10000 ,stdin); 
        if(check_user_name(user_input, last_name)){
            last_name[strlen(last_name)-1] ='\0';
            strcpy(new.last_name, last_name); 
            valid_lastname = 0;
        }
    }

    strcpy(new.phone, "0000000000");
    strcpy(new.payment.card_number, "0000000000000000");
    strcpy(new.payment.cvc, "000");
    new.payment.month = 0;
    new.payment.year = 0; 
    strcpy(new.password, new.first_name);
    users[*no_of_user] = new; 
    *no_of_user += 1;
    printf("%s %s", new.first_name, new.last_name);
    for(valid_id = 0; valid_id < *no_of_user; valid_id ++){
       printf("%-15s %-15s %-15d %-15s\n", users[valid_id].first_name, users[valid_id].last_name, users[valid_id].user_id, users[valid_id].phone);
    }
    save_db(users, no_of_user);
}

int check_user_name(char * user_input,char * name){
    if(strlen(user_input) > MAX_NO_LASTNAME + 1){ 
        return 0; 
    }
    int i;
    if(user_input[0] >= 65 && user_input[0] <= 90){
        name[0] = user_input[0];
    } else if (user_input[0] >= 97 && user_input[0] <= 122){
        name[0] = user_input[0] - 32;
    } else {
       return 0;
    }

    for(i = 1; i < strlen(user_input) + 1; i++){ 
        if(user_input[i] >= 'A' && user_input[i] <= 'Z'){
            name[i] = user_input[i] + 32;
        } else if (user_input[i] >= 'a' && user_input[i] <= 'z'){
            name[i] = user_input[i];
        } else {
        }
    }

    return 1;
}

