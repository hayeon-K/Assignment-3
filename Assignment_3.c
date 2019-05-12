// Assignment 3
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/*Insert structs here*/
struct payment{
    int card_number;
    char cardholder;
    int expiry;
    int CVC;
};
typedef struct payment payment_t;

struct date{
    int day;
    int month;
    int year;
    int hour;
    int minute;
};
typedef struct date date_t;

struct user
    char first_name;
    char last_name;
    int birthdate;
    int ID;
    char password;
    payment_t payment;
};
typedef struct user user_t;

struct transaction{
    payment_t payment;
    date_t date;

}




/*Insert function protoypes here*/
int logIn() {

}

int isAdmin (int ID) {
        if (ID[1] = 'A') {
        return 1;
    }
}

void menu(); {
    printf("1. ")
}

void search();

void edit();

void print();

void add ();

void 





/*Main boi big man fuction gonna knock it out of the park*/
int main (void)
{

    return 0;
}
