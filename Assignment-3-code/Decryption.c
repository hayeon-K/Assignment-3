/*******************************************************************************
 * DECRYPTION
*******************************************************************************/

/*******************************************************************************
 * This function decrypts the student database file
 * Author: Mitch Winyard
*******************************************************************************/

void encrypt ()
{
    ch;
    FILE *fpts, *fptt;

    fpts=fopen(student_database.txt, "r"); /* Opens the student_database.txt file in read-only mode */
    if(fpts==NULL) /* If the student_database.txt file is not found, return this error message */
    {
        printf(" ERROR - File does not exist, or error in opening.\n");
		exit(1);
    }
    fptt=fopen("temp.txt", "w"); /* Creates/opens a file called temp.txt in write mode */
    if (fptt==NULL) /* If the system is unable to create a temp.txt file, return this error message */
    {
        printf(" ERROR - Error in creation of file 'temp.txt'\n");
		fclose(fpts);
		exit(2);
    }
    while(1)
    {
        ch=fgetc(fpts); /* Read each char in the file including spaces and newlines */
        if(ch==EOF) /* Stop reading at end of file */
        {
            break;
        }
        else /* Replace ASCII value of the ciphered text with new value, thus returning it to the original plain text value */
        {
            ch=ch-(11*17);
            fputc(ch, fptt);
        }
    }
    fclose(fpts);
	fclose(fptt); /* Save and close both files */
	fpts=fopen(student_database.txt, "w"); /* Opens the student_database.txt file in write mode */
	if(fpts==NULL) /* If the student_database.txt file is not found, return this error message */
	{
		printf(" ERROR - File does not exist, or error in opening.\n");
		exit(3);
	}
	fptt=fopen("temp.txt", "r"); /* Opens the temp.txt file in read-only mode */
	if(fptt==NULL) /* If the temp.txt file is not found, return this error message */
	{
		printf(" ERROR - Error in creation of file 'temp.txt'\n");
		fclose(fpts);
		exit(4);
	}
	while(1)
	{
		ch=fgetc(fptt); /* Read each char in the file including spaces and newlines */
		if(ch==EOF)  /* Stop reading at end of file */
		{
			break;
		}
		else
		{
			fputc(ch, fpts); /* Replace each corresponding char in student_database.txt with the data from temp.txt */
		}
	}

	fclose(fpts); /* Save and close both files */
	fclose(fptt);

    return;

}
