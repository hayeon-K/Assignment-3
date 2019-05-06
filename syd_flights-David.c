/*******************************************************************************
 * 48430 Fundamentals of C Programming - Assignment 2
 * Name:
 * Student ID:
 * Date of submission:
 * A brief statement on what you could achieve (less than 50 words):
 *
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
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*******************************************************************************
 * List preprocessing directives - you may define your own.
*******************************************************************************/
#define MAX_FLIGHTCODE_LEN 6
#define MAX_CITYCODE_LEN 3
#define MAX_NUM_FLIGHTS 5
#define DB_NAME "database"

/*******************************************************************************
 * List structs - you may define struct date_time and struct flight only. Each
 * struct definition should have only the fields mentioned in the assignment
 * description.
*******************************************************************************/
struct date_time
{
    int month;
    int day;
    int hour;
    int minute;
};
typedef struct date_time date_time_t;

struct flight
{
    char flightcode[MAX_FLIGHTCODE_LEN+1];
    date_time_t departure_dt;
    char arrival_city[MAX_CITYCODE_LEN+1];
    date_time_t arrival_dt;
};
typedef struct flight flight_t;

/*******************************************************************************
 * Function prototypes - do NOT change the given prototypes. However you may
 * define your own functions if required.
*******************************************************************************/
void print_menu (void);
int getChoice();
void inputCases (int input);
void addFlight();
void printFlights();
void saveData();
void loadData(int numFlight);
int isValid(int month, int day, int hour, int minute);
int valid_flightcode(char flightcode[]);
int is_digit(char character);


/*******************************************************************************
 * Main
*******************************************************************************/
flight_t flight, flights [MAX_NUM_FLIGHTS];
int numFlights, s = 0;

int month, day, hour, minute, i;

int main(void)
{
    print_menu();
    int selection = getChoice();
    if(selection == -1)
    {
        main();
    }
    inputCases(selection);
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
 * This function checks whether the input integer is between 1 to 5 and is a
 * number
 * inputs:
 * - choice
 * outputs:
 * - switch case
*******************************************************************************/
int getChoice(){
  int choice = 0;

  if (scanf("%d", &choice) == 1)
  {
    if(choice < 1 || choice > 5) {
      printf("Invalid choice\n");
      return -1;
    }

    else {
      return choice;
    }
  }

  else return -1;
}
/*******************************************************************************
 * This function reads the choice of the user and runs the case that corresponds
 to the user input.
 * outputs:
 * - cases
*******************************************************************************/
void inputCases (int input)
{
    switch(input) {
      case 1: addFlight(); break;
      case 2: printFlights(); break;
      case 3: saveData(); break;
      case 4: loadData(numFlights); break;
      case 5: exit(0); break;
    }
}

/*******************************************************************************
 * This function reads the choice of the user and runs the case that corresponds
 to the user input.
 * inputs:
 * - month, day, hour, minute
 * - flightcode, citycode
 * outputs:
 * - saves input
*******************************************************************************/

void addFlight() {
    if(numFlights < MAX_NUM_FLIGHTS)
    {
      int validFlag = 0;

      while(validFlag == 0) {
        printf("Enter flight code>\n");
        scanf("%s", flight.flightcode);

        validFlag = valid_flightcode(flight.flightcode);
      }
      printf("Enter departure info for the flight leaving SYD.\n");

      validFlag = 0;
      while(validFlag == 0)
      {
        printf("Enter month, date, hour and minute separated by spaces>\n");
        scanf("%d %d %d %d", &month, &day, &hour, &minute);
        validFlag = isValid(month, day, hour, minute);
      }
      flight.departure_dt.month = month;
      flight.departure_dt.day = day;
      flight.departure_dt.hour = hour;
      flight.departure_dt.minute = minute;

      printf("Enter arrival city code>\n");
      scanf("%s", flight.arrival_city);
      flight.arrival_city[3] = 0;
      printf("Enter arrival info.\n");
      validFlag = 0;
      while(validFlag == 0)
      {
        printf("Enter month, date, hour and minute separated by spaces>\n");
        scanf("%d %d %d %d", &month, &day, &hour, &minute);
        validFlag = isValid(month, day, hour, minute);
      }
      flight.arrival_dt.month = month;
      flight.arrival_dt.day = day;
      flight.arrival_dt.hour = hour;
      flight.arrival_dt.minute = minute;

      flights[numFlights] = flight;
      numFlights=numFlights+1;
    }

    else {
      printf("Cannot add more flights - memory full\n");
    }

    main();
}

/*******************************************************************************
 * This function prints flights
 * inputs:
 * - city code or *
 * outputs:
 * - destinations
*******************************************************************************/

void printFlights() {
  char arrival_city[MAX_CITYCODE_LEN+1];

  printf("Enter arrival city code or enter * to show all destinations>\n");
  scanf("%s", arrival_city);

  if(strcmp(arrival_city, "*" ) == 0) {
    if(numFlights == 0) {
      printf("No flights\n");
    }

    else {
      printf("Flight Origin          Destination\n");
      printf("------ --------------- ---------------\n");

      for (i = 0; i < numFlights; i++) {
        printf("%-6s SYD %02d-%02d %02d:%02d %-3s %02d-%02d %02d:%02d\n",
        flights[i].flightcode, flights[i].departure_dt.month,
        flights[i].departure_dt.day, flights[i].departure_dt.hour,
        flights[i].departure_dt.minute, flights[i].arrival_city,
        flights[i].arrival_dt.month, flights[i].arrival_dt.day,
        flights[i].arrival_dt.hour, flights[i].arrival_dt.minute);
      }
    }
  }

  else {
    int inputCode = 0;

    for (i=0; i<numFlights; i++) {
        if(strcmp(arrival_city, flights[i].arrival_city) == 0) {
          inputCode++;
        }
    }

    if(inputCode == 0) {
        printf("No flights\n");
    }

    else {
        printf("Flight Origin          Destination\n");
        printf("------ --------------- ---------------\n");

        for(i = 0; i < numFlights; i++) {
          if(strcmp(arrival_city, flights[i].arrival_city) == 0) {
            printf("%-6s SYD %02d-%02d %02d:%02d %-3s %02d-%02d %02d:%02d\n",
            flights[i].flightcode,flights[i].departure_dt.month,
            flights[i].departure_dt.day, flights[i].departure_dt.hour,
            flights[i].departure_dt.minute, flights[i].arrival_city,
            flights[i].arrival_dt.month, flights[i].arrival_dt.day,
            flights[i].arrival_dt.hour, flights[i].arrival_dt.minute);
          }
        }
    }
  }
  main();
}

void saveData() {
  FILE *fptr;
  fptr = fopen(DB_NAME, "w");

  if (numFlights == 0) {
    printf("Read Error\n");
  }

  for (i = 0; i < numFlights; i++) {
    fprintf(fptr, "%s\n%02d\n%02d\n%02d\n%02d\n%s\n%02d\n%02d\n%02d\n%02d\n",
    flights[i].flightcode, flights[i].departure_dt.month,
    flights[i].departure_dt.day, flights[i].departure_dt.hour,
    flights[i].departure_dt.minute, flights[i].arrival_city,
    flights[i].arrival_dt.month, flights[i].arrival_dt.day,
    flights[i].arrival_dt.hour, flights[i].arrival_dt.minute);
  }

  fclose(fptr);

  main();
}

void loadData(int numFlight) {
  FILE *fp;
  fp = fopen(DB_NAME, "r");

  int ch = getc(fp);

  if (fp) {
    while (ch != EOF) {
      
    }
  }

  else {
    printf("Read error \n");
    main();
  }

  fclose(fp);
  main();
}


int isValid(int month, int day, int hour, int minute) {
  if(month < 1 || month > 12 || day < 1 || day > 31 || hour < 0 || hour > 23 ||
    minute < 0 || minute > 59) {
    printf("Invalid input\n");
    return 0;
  }
  return 1;
}

int valid_flightcode(char flightcode[])
{
  if (strlen(flightcode) < 7) {
    if (strlen(flightcode) < 2 || !(flightcode[0] >= 'A' && flightcode[0] <= 'Z')
    || !(flightcode[1] >= 'A' && flightcode[1] <= 'Z')) {
      printf("Invalid input\n");
      return 0;
    }

    for (i = 2; i < strlen(flightcode); i++) {
      if (!is_digit(flightcode[i])) {
        printf("Invalid input2\n");
      }
    }

    return 1;
  }

  else {
    printf("Invalid input3\n");
    flightcode = 0;
    return 0;
  }
}

int is_digit(char character) {
  return character >= '0' && character <= '9';
}
