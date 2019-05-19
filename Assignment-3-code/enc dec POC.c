#include <stdio.h>
#include <stdlib.h>
#include "Lib/encfunct.c"

int main (void)
{
	FILE *db_ptr;
	char ans[20];

	/* init_db(); 
	Use this to initialse a database for first time testing. Remove or comment out function on further uses.*/

	db_ptr = open_db();
	/* Do some stuff with the database */
	printf("Are you okay?\n");
	scanf("%s", ans);
	close_db(db_ptr);
	
	return 0;
}