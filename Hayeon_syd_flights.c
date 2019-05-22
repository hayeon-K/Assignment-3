/*******************************************************************************
 * 48430 Fundamentals of C Programming - Assignment 2
 * Name: Hayeon Kim
 * Student ID: 12690273
 * Date of submission:
 * A brief statement on what you could achieve (less than 50 words):
 * All functionality tests
 * 
 * A brief statement on what you could NOT achieve (less than 50 words):
 * 
 * 
*******************************************************************************/

/*******************************************************************************
 * List header files - do NOT use any other header files. Note that stdlib.h is
 * included in case you want to use any of the functions in there. However the
 * task can be achieved with stdio.h and string.h only.
*******************************************************************************/
#include <stdio.h> /* printf, scanf, fclose, feof, fopen, fprintf, fscanf,
                              fgets, getchar, */
#include <string.h> /* strcmp, strncpy, strcpy, strlen */
#include <stdlib.h> 
/*******************************************************************************
 * List preprocessing directives - you may define your own.
*******************************************************************************/
#define MAX_FLIGHTCODE_LEN 6
#define MAX_CITYCODE_LEN 3
#define MAX_NUM_FLIGHTS 5
#define DB_NAME "database"
#define DEPARTING_CITY "SYD"
/*******************************************************************************
 * List structs - you may define struct date_time and struct flight only. Each
 * struct definition should have only the fields mentioned in the assignment
 * description.
*******************************************************************************/
struct date_time{
    int month;
    int day;
    int hour;
    int minute; 
};
typedef struct date_time date_time_t;

struct flight{
    char flightcode[MAX_FLIGHTCODE_LEN +1]; 
    char arrival_city[MAX_CITYCODE_LEN+1];
    date_time_t departure_dt; 
    date_time_t arrival_dt; 
};
typedef struct flight flight_t;
/*******************************************************************************
 * Function prototypes - do NOT change the given prototypes. However you may
 * define your own functions if required.
*******************************************************************************/
void print_menu (void);
int add_flight (flight_t *flights_p, int *flight_no_p);
void display_flight(const flight_t* flights, int flight_no);
int check_flightcode_format(const char *entered_flightcode_p, char *flightcode_p);
int check_number_format(int month, int day, int hour, int minute);
int save_db(const flight_t *flights_p, int flight_no);
int load_db(flight_t *flights_p, int *flight_no_p, int no_of_lines);
int is_capital(char c);
int is_right_format_number(char c);
int is_right_format_trailing_number(char c);
int no_of_lines();
/*******************************************************************************
 * Main
*******************************************************************************/
int main(void)
{
    /*Array of flights_t containing flight*/
    flight_t flights[MAX_NUM_FLIGHTS]={};

    /*int variable that would store number of flight*/
    int flight_no = 0;

    /*int variable that would store user input for menu*/
    int choice;

    /*menu would loop unless user enters 5 */
    while(choice != 5){ 
        print_menu();    /* print menu */
        if(scanf("%d", &choice) != 1){     /* if user input is NOT digit */    
            while ((getchar()) != '\n');      /* flush input buffer */
            printf("Invalid choice \n");      /* prints error message */
        } else {     /* if user input is digit */
            switch(choice){
                case 1: 
                    add_flight(flights, &flight_no);
                    break;
                case 2: 
                    display_flight(flights, flight_no);
                    break;
                case 3:
                    save_db(flights, flight_no);
                    break;
                case 4:
                    load_db(flights, &flight_no, no_of_lines());
                    break;
                case 5: 
                    break;
                default:      /* when user input is digit but not 1-5 */
                    printf("Invalid choice \n"); 
                    break;
            }    
        }
    }
    return 0;
}

/*******************************************************************************
 * This function prints the initial menu with all instructions on how to use
 * this program.
 * inputs:
 * - none
 * outputs:
 * - none
*******************************************************************************/
void print_menu (void)
{
    printf("\n"
    "1. add a flight\n"
    "2. display all flights to a destination\n"
    "3. save the flights to the database file\n"
    "4. load the flights from the database file\n"
    "5. exit the program\n"
    "Enter choice (number between 1-5)>\n");
}

/*******************************************************************************
 * This function adds new flight to the array of flights if all inputs are in correct 
 * format
 * inputs:
 *   flights_p - memory address of a flights
 *   flight_no_p - memory address of number of flights in the flights array
 * outputs:
 *   0 - success
 *   1 - failed to add flights
*******************************************************************************/
int add_flight (flight_t *flights_p , int *flight_no_p){
    /* flush input buffer */
    while ((getchar()) != '\n'); 

    /* if number of flights saved in array is 5, print error message */
    if(*flight_no_p == 5){
        printf("Cannot add more flights - memory full\n");
        return 1;
    }

    /* new instance of flight_t that would be added to flights */
    flight_t new_flight = {}; 

    /* array of char that would store flightcode */
    char flightcode[MAX_FLIGHTCODE_LEN +1];

    /* int variable that would be used as boolean function to check for flightcode format */
    int is_flightcode_correct = 0;

    /* int variable that would be used as boolean function to check for number format for dates */
    int is_number_correct = 0;

    /* while is_flightcode_correct is 0, keep looping */
    while(is_flightcode_correct == 0){
        char entered_flightcode[1000] = {};     /* array of char that would store user input */
        printf("Enter flight code>\n");
        fgets(entered_flightcode, 10000 ,stdin);     /* store user input into entered_flightcode */
        /* if user input passes format test */
        if(check_flightcode_format(entered_flightcode, flightcode)){
            /* replace last char '\n' with '\0' to avoid line change */ 
            flightcode[strlen(flightcode)-1] ='\0'; 
            /* set flightcode of new flight with entered user input */ 
            strcpy(new_flight.flightcode, flightcode);
            /* set is_flightcode_correct as 1 to break loop */ 
            is_flightcode_correct = 1;
        } else {
            /* print error message when format test fails */ 
            printf("Invalid input\n");
        }
    } 

   
    printf("Enter departure info for the flight leaving %s.\n", DEPARTING_CITY);
    /* while is_number_correct is 0, keep looping */
    while (is_number_correct == 0) {
        int month, day, hour, minute;   /* 4 int variables to store month, day, hour, minute */
        printf("Enter month, date, hour and minute separated by spaces>\n");
        /* assign user input separated by space to month, day, hour, minute */
        scanf("%d %d %d %d", &month, &day, &hour, &minute);
        /* if all inputl passes format test assign them to respective variables of new flight*/
        if(check_number_format(month, day, hour, minute)) {
            new_flight.departure_dt.month = month;
            new_flight.departure_dt.day = day;
            new_flight.departure_dt.hour = hour;
            new_flight.departure_dt.minute = minute;
            /* set is_number_correct as 1 to break loop */ 
            is_number_correct = 1;
        } else {
            /* print error message when format test fails */ 
            printf("Invalid input\n");
        }
    }
    while ((getchar()) != '\n');    /* flush input buffer */ 
    is_number_correct = 0;    /* reset is_number_correct as 0 to be used again*/

    /*Array of char that would store user input for arrival city */   
    char arrival_city_input[MAX_CITYCODE_LEN +1];
    printf("Enter arrival city code>\n");
    scanf("%s", arrival_city_input);
    /* truncate user input with MAX_CITYCODE_LEN */
    strncpy(new_flight.arrival_city, arrival_city_input, MAX_CITYCODE_LEN);
    while ((getchar()) != '\n');    /* flush input buffer */

    printf("Enter arrival info.\n");
    /* while is_number_correct is 0, keep looping */
    while (is_number_correct == 0) {
        int arrival_month, arrival_day, arrival_hour, arrival_minute;
        printf("Enter month, date, hour and minute separated by spaces>\n");
        scanf("%d %d %d %d", &arrival_month, &arrival_day, &arrival_hour, 
    &arrival_minute);
        /* if all input passes format test assign them to respective variables of new flight*/
        if(check_number_format(arrival_month, arrival_day, arrival_hour, 
    arrival_minute)) {
            new_flight.arrival_dt.month = arrival_month;
            new_flight.arrival_dt.day = arrival_day;
            new_flight.arrival_dt.hour = arrival_hour;
            new_flight.arrival_dt.minute = arrival_minute;
            is_number_correct = 1;
        } else {
            printf("Invalid input\n");
        }
    } 
    while ((getchar()) != '\n');    /* flush input buffer */

    /*save new flight to flights using int value stored in memory address of flight_no_p as index*/
    flights_p[*flight_no_p] = new_flight;
    /*increment int value stored in flight_no_p by 1*/
    *flight_no_p += 1;

    return 0;   
}


/*******************************************************************************
 * This function checks for the length and format of flight code entered  
 * 
 * inputs:
 *   entered_flightcode_p - memory address of a flightcode entered by user
 *   flightcode_p - memory address of flightcode 
 * outputs:
 *   0 - otherwise
 *   1 - format of flight code correct
*******************************************************************************/
int check_flightcode_format(const char *entered_flightcode_p, char *flightcode_p){
    /* if user input is too long, format test fails */
    if(strlen(entered_flightcode_p) > MAX_FLIGHTCODE_LEN+1){ 
        return 0; 
    }

    /*int variable for for loop*/
    int i;

    /*when length of user input is correct, assign its value to flightcode variable */
    for(i = 0; i < MAX_FLIGHTCODE_LEN+1; i++){
        flightcode_p[i] = entered_flightcode_p[i];
    }
 
    /*check for the format of flightcode and return 1 if everything is right*/
    if(is_capital(flightcode_p[0]) && is_capital(flightcode_p[1]) && 
      is_right_format_number(flightcode_p[2]) &&
      is_right_format_trailing_number(flightcode_p[3]) && 
      is_right_format_trailing_number(flightcode_p[4]) &&
      is_right_format_trailing_number(flightcode_p[5])){
        return 1;
    }
    return 0;
}

/*******************************************************************************
 * This function checks for capital letter
 * inputs:
 *   c - char variable to be checked
 * outputs:
 *   0 - otherwise
 *   1 - c is in right format
*******************************************************************************/
int is_capital(char c){
   if(c >= 65 && c <= 90) {
       return 1;
   }
   return 0;
}

/*******************************************************************************
 * This function checks for digit
 * inputs:
 *   c - char variable to be checked
 * outputs:
 *   0 - otherwise
 *   1 - c is in right format
*******************************************************************************/
int is_right_format_number(char c){
    if((c >= '0' && c <= '9')){
       return 1;
    }
    return 0;
}

/*******************************************************************************
 * This function checks for digit for trailing number that could be empty or digits
 * inputs:
 *   c - char variable to be checked
 * outputs:
 *   0 - otherwise
 *   1 - c is in right format
*******************************************************************************/
int is_right_format_trailing_number(char c){
    if(c >= '0' && c <= '9'){
       return 1;
    } else if (c == '\n' || c == '\0'){ 
       return 1;
    }
    return 0;
}

/*******************************************************************************
 * This function checks for digit
 * inputs:
 *   month - int month variable to be checked
 *   day - int day variable to be checked
 *   hour - int hour variable to be checked
 *   minute - int minute variable to be checked
 * outputs:
 *   0 - otherwise
 *   1 - dates are in right formate
*******************************************************************************/
int check_number_format(int month, int day, int hour, int minute) {
    if(month >= 1 && month <= 12 && day >= 1 && day <= 31 && 
       hour >= 0 && hour <= 23 && minute >= 0 && minute <= 59) {
        return 1;
    }
    return 0;
}

/*******************************************************************************
 * This function displays all the flights or flights with same destination
 * depending on user input
 * inputs:
 *   flights_p - memory address of flights
 *   flight_no - number of flight in flights 
 * outputs:
 * - none
*******************************************************************************/
void display_flight(const flight_t *flights_p, int flight_no){

    /* array of char that would store user input */
    char choice[MAX_CITYCODE_LEN+1];

    /* int variable for for-loop  */
    int i;

    /* array of flight_t that would temporarily store all fights with same destination*/
    flight_t same_arrival_flights[MAX_NUM_FLIGHTS];

   /* number of flight_t that matches user input destination */
    int checked = 0;

    printf("Enter arrival city code or enter * to show all destinations>\n");
    scanf("%s", choice); 
    while ((getchar()) != '\n');    /* flush input buffer */

    /* when number of flights saved in flights is 0, prints message */
    if(flight_no == 0){
        printf("No flights\n");
    } else if(strcmp(choice, "*") == 0) {    /* if user input is "*" */
        /* print every single flight in array of flights in format */
        printf("Flight Origin          Destination\n");
        printf("------ --------------- ---------------\n");
        for(i = 0; i < flight_no; i++){
            printf("%-6s %s %02d-%02d %02d:%02d %-3s %02d-%02d %02d:%02d\n",
                    flights_p[i].flightcode, DEPARTING_CITY, 
                    flights_p[i].departure_dt.month, flights_p[i].departure_dt.day,
                    flights_p[i].departure_dt.hour, flights_p[i].departure_dt.minute,
                    flights_p[i].arrival_city, flights_p[i].arrival_dt.month, 
                    flights_p[i].arrival_dt.day, flights_p[i].arrival_dt.hour,
                    flights_p[i].arrival_dt.minute);
        }
    } else {    /* if user input is not "*" */
        /* go trhough every flight in flights with input as its destination and 
            save it to same_arrival_flights */
        for(i = 0; i < flight_no; i++){
            if(strcmp(choice, flights_p[i].arrival_city) == 0){
                same_arrival_flights[checked++] = flights_p[i]; 
            }
        }
        if(checked >= 1){    /* if number of flights with same destination is more than 1 */
            /* print every single flight in same_arrival_flights in format */
            printf("Flight Origin          Destination\n");
            printf("------ --------------- ---------------\n");
            for(i = 0; i < checked; i++){
            printf("%-6s %s %02d-%02d %02d:%02d %-3s %02d-%02d %02d:%02d\n",
                    same_arrival_flights[i].flightcode, DEPARTING_CITY, 
                    same_arrival_flights[i].departure_dt.month,
                    same_arrival_flights[i].departure_dt.day, 
                    same_arrival_flights[i].departure_dt.hour, 
                    same_arrival_flights[i].departure_dt.minute, 
                    same_arrival_flights[i].arrival_city, 
                    same_arrival_flights[i].arrival_dt.month, 
                    same_arrival_flights[i].arrival_dt.day, 
                    same_arrival_flights[i].arrival_dt.hour, 
                    same_arrival_flights[i].arrival_dt.minute);
            } 
        } else {   /* if there is no matching arrival flight, print error message */
            printf("No flights\n");
        }
    }
}

/*******************************************************************************
 * This function saves array of flight into textfile 
 * inputs:
 *   flights_p - memory address of flights
 *   flight_no - number of flight in flights 
 * outputs:
 *   0 - successfully saved to database
 *   1 - unable to save to database
*******************************************************************************/
int save_db(const flight_t *flights_p, int flight_no){
     /* Pointer to the file */
    FILE *fp;

     /* Opening a file in w mode*/
    fp = fopen(DB_NAME, "w");

    /* If there is issue opening file, print error message and finish */
    if(fp == NULL){
        printf("Write error\n");
        return 1;
    } 

    /* int variable for for loop */
    int i;

    /* loop the number of flights and write to file in certain format, 
        changing line with each flight  */
    for(i = 0; i < flight_no; i++){
        fprintf(fp, "%s %d %d %d %d %s %d %d %d %d\n",
                    flights_p[i].flightcode, flights_p[i].departure_dt.month,
                    flights_p[i].departure_dt.day, flights_p[i].departure_dt.hour, 
                    flights_p[i].departure_dt.minute, flights_p[i].arrival_city, 
                    flights_p[i].arrival_dt.month, flights_p[i].arrival_dt.day, 
                    flights_p[i].arrival_dt.hour, flights_p[i].arrival_dt.minute);
    }

    /* close file */
    fclose(fp);
    return 0;
}

/*******************************************************************************
 * This function loads array of flight from textfile 
 * inputs:
 *   flights_p - memory address of flights
 *   flight_no_p - memory address of number of flight in flights 
 *   no_of_lines - no of lines in textfile (= no of flight in file) 
 * outputs:
 *   0 - successfully loaded database
 *   1 - unable to load database
*******************************************************************************/
int load_db(flight_t *flights_p, int *flight_no_p,int no_of_lines){
     /* Pointer to the file */
    FILE *fp;

     /* Opening a file in r mode */
    fp = fopen(DB_NAME, "r");

    /* If fp is NULL, print error message and finish */ 
    if(fp == NULL){
        printf("Read error\n");
        return 1;
    } 

    /* variable for while loop */
    int i = 0;

    /* while incrementing i is not equal to no_of_lines which 
        stores the number of new lines (=flights) in text file,
        read from file and store that into flights array */
    while(i != no_of_lines){
        fscanf(fp, " %s %d %d %d %d %s %d %d %d %d",
               flights_p[i].flightcode, &flights_p[i].departure_dt.month,
               &flights_p[i].departure_dt.day, &flights_p[i].departure_dt.hour, 
               &flights_p[i].departure_dt.minute, flights_p[i].arrival_city, 
               &flights_p[i].arrival_dt.month, &flights_p[i].arrival_dt.day, 
               &flights_p[i].arrival_dt.hour, &flights_p[i].arrival_dt.minute);
        i++;
    }

    /* assign number of flight in flights in main with no_of_lines  */
    *flight_no_p = no_of_lines;

    /* close file */
    fclose(fp);
    return 0;
}

/*******************************************************************************
 * This function counts the number of lines in textfile
 * inputs:
 * - none
 * outputs:
 *   0 - unable to read file / if there is no flight saved in textfile
 *   count_lines - no of lines in textfiles 
*******************************************************************************/
int no_of_lines(){
     /* Pointer to the file */
    FILE *fp;

     /* Opening a file in r mode */
    fp = fopen(DB_NAME, "r"); 

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
