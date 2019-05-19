/*******************************************************************************
 * ENCRYPTION
*******************************************************************************/

/*******************************************************************************
 * This function encrypts the student database file
 * Author: Mitch Winyard
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>

FILE *open_existing_db_file ()
{
    FILE *fptr;
    
    fptr=fopen("student_database.txt", "a+"); /* Opens the student_database.txt file in read-only mode */
    if(fptr==NULL) /* If the student_database.txt file is not found, return this error message */
    {
        printf(" ERROR - File does not exist, or error in opening.\n");
        return fptr;
    }
    return fptr;
}


FILE *open_clean_db_file ()
{
    FILE *fptr;
    
    fptr=fopen("student_database.txt", "w+"); /* Opens the student_database.txt file in read-only mode */
    if(fptr==NULL) /* If the student_database.txt file is not found, return this error message */
    {
        printf(" ERROR - File does not exist, or error in opening.\n");
        return fptr;
    }
    return fptr;
}


FILE *open_db_temp_file ()
{
    FILE *fptr;
    fptr=fopen("temp.txt", "w+"); /* Creates/opens a file called temp.txt in write mode */
    if (fptr==NULL) /* If the system is unable to create a temp.txt file, return this error message */
    {
        printf(" ERROR - Error in creation of file 'temp.txt'\n");
		return fptr;
    }  
    return fptr;
}


void close_db_file (FILE *fptr)
{
    fclose(fptr);
}


void close_db_temp_file (FILE *fptr)
{
    fclose(fptr);
}


void save_temp_to_db (FILE *fptrt, FILE *fptrs)
{
    char ch;

    rewind(fptrs);
    rewind(fptrt);

	while(1)
	{
		ch=fgetc(fptrt); /* Read each char in the file including spaces and newlines */
		if(ch==EOF)  /* Stop reading at end of file */
		{
			break;
		}
		else
		{
			fputc(ch, fptrs); /* Replace each corresponding char in student_database.txt with the data from temp.txt */
		}
	}  
}

void encrypt (FILE *fptrt, FILE *fptrs)
{
    char ch, key;

    key = 'm';

    while(1)
    {
        ch=fgetc(fptrs); /* Read each char in the file including spaces and newlines */
        if(ch==EOF) /* Stop reading at end of file */
        {
            break;
        }
        else 
        {
            ch=ch ^ key;
            fputc(ch, fptrt);
        }
    }
    return;
}

void delete_temp_file ()
{
    remove("temp.txt");
}

void init_db()
{
    FILE *db_ptr, *fptrt;

    db_ptr = open_existing_db_file();
    fptrt = open_db_temp_file();
    encrypt (fptrt, db_ptr);
    close_db_file (db_ptr);
    db_ptr = open_clean_db_file ();
    save_temp_to_db (fptrt, db_ptr);
    close_db_temp_file(fptrt);
    delete_temp_file();    

}

FILE *open_db ()
{
    FILE *db_ptr, *fptrt;
    
    db_ptr = open_existing_db_file();
    fptrt = open_db_temp_file();
    encrypt (fptrt, db_ptr);
    close_db_file (db_ptr);
    db_ptr = open_clean_db_file ();
    save_temp_to_db (fptrt, db_ptr);
    close_db_temp_file(fptrt);
    delete_temp_file();
    rewind (db_ptr);
    return db_ptr;
}

void close_db (FILE *db_ptr)
{
    FILE *fptrt;

    fptrt = open_db_temp_file();
	encrypt (fptrt, db_ptr);
	close_db_file (db_ptr);
	db_ptr = open_clean_db_file ();
	save_temp_to_db (fptrt, db_ptr);
	close_db_file (db_ptr);
	close_db_temp_file (fptrt);
	delete_temp_file ();
}