#include <stdio.h>
#include <stdlib.h>

//finals
#define ROWS 3
#define COLS 3
#define SIZE 50

//prototypes
void getMatrix(int *arr, int rows, int cols);
void printMat(int *arr, int rows, int cols);
void mySum(int *mat, int rows, int cols);
char* myStrcat(char* strDest, const char* strSrc);
int strSpecialCmp(const char *str , const char *strSearch);
char *myStrstr(const char *str, const char *strSearch, int *index);

void main()
{
	//general variables
	char exit;
	int choice, fContinue = 1;
	do//loop for repeating menu
	{
		printf("Press any key to enter the menu. Press 'e' or 'E' to exit...\n");
		flushall();//clearing buffer
		scanf("%c", &exit);
		if(exit == 'E' || exit == 'e')//if input is e then exit loop
		{
			break;
		}
		//menu
		printf("Press 1 for question 1...\n");
		printf("Press 2 for question 2...\n");
		printf("Press 3 for question 3...\n");
		scanf("%d", &choice);
		
		switch(choice)//switch for different cases
		{
			case 1:
			{
				int mat[ROWS][COLS];
				getMatrix((int*)mat, ROWS, COLS);	
				printf("\nMatrix from user:\n\n");
				printMat((int*)mat, ROWS, COLS);
				printf("\n\nmySum:\n");
				mySum((int*)mat, ROWS, COLS);
				break;		
			}

			case 2:
			{
				char strSrc[SIZE], strDest[SIZE], *p; 		
				printf("Please enter strDestination:\n");
				scanf("%s", strDest);
				printf("Please enter strSource:\n");
				scanf("%s", strSrc);
				p = myStrcat(strDest, strSrc);
				printf("p = %s\n\n", p);
				break;
			}

			case 3:
			{
				char str[SIZE], strSearch[SIZE], *p; 
				int index = 0;
				printf("Please enter the first string (str):\n");
				scanf("%s", str);
				printf("Please enter the substring to search for (strSearch):\n");
				scanf("%s", strSearch);
				p = myStrstr(str, strSearch, &index);
				if(p != NULL)//if p is not null then it points to the start of the correct string
				{
					printf("Location found, char %c, idx: %d\n", *p, index);
				}
				else//if p is null 
				{
					printf("strSearch is not a substring of Str\n");
				}
				break;
				
			}
		}	 

 	}while(fContinue);
		printf("Goodbye!\n");//display exit message
		system("pause");//pausing to see console
}


void getMatrix(int *arr, int rows, int cols)
{
	int *p, *i, j = 0;
	for(p = arr; p < arr+(rows*cols); p+=cols)//p goes from first address to last, and advances each time to the begining of the following row.
	{
		printf("Please enter %d numbers for row #%d --> ",cols, j+1);
		for(i = p; i < p+cols; i++)//i points to the start of a specific row and goes untill the end
		{
			scanf("%d", i);
		}
		j++;//advancing j for num of row
	}
}


void printMat(int *arr, int rows, int cols)
{
	int *p, *i;
	for(i = arr; i < arr + (rows*cols); i += cols)//nested loops to print matrix. i goes from first address to last address and advances to the begining of the following row. p goes from start to end of row, all the while pointing to the right address.
	{
		for(p = i; p < i+cols; p++)
		{
			printf("%d ", *p);
		}
		printf("\n");
	}
}


void mySum(int *mat, int rows, int cols)
{
	int *p, *temp, sum = 0;
	for(p = mat; p < mat+cols; p++)//first row from left to right
	{
		printf("%d ", *p);
		sum += *p;//starting sum	
	}

	p--;//returning p to upper right value
	p += cols;//advancing p to point one value below upper right value

	while(p < mat + (rows*cols))//right column
	{
		printf("%d ", *p); 
		sum += *p;//cont sum
		p += cols;//advancing p to point to one value below
	}

	p -= cols;//returning p to last value in matrix	
	temp = p;//dont want to ruin p so temp is used
	p--;//p now points to the value left of the last value

	while(p > temp - cols)//bottom line
	{
		printf("%d ", *p);
		sum += *p;//cont sum
		p--;//p points to the left of last value
	}

	p++;//returning p to lower left value
	p -= cols;//p now points to the value above the lower left value

	while(p > mat)//left column
	{
		printf("%d ", *p);
		sum += *p;//cont sum
		p -= cols;//p points to the value above the last value
	}

	printf("\n\nsum = %d\n\n", sum);//printing sum
}


char* myStrcat(char* strDest, const char* strSrc)
{
	char *p, *i;//variables
	int length1 = 0, length2 = 0;
	p = strDest;

	while(*p != '\0')//at the end of this loop p is pointing to the end of the first string + computing length of the first string
	{
		length1++;
		p++;
	}

	while(*strSrc != '\0')//connecting the second string to the first while also computing the length of the second string
	{
		*p = *strSrc;
		p++;//advancing p
		strSrc++;//advancing str source
		length2++;
	}

	*p = '\0';//ending string with a 0
	p -= (length1+length2);//this forces p to point to the start of the string

	return p;//returning pointer
}


int strSpecialCmp(const char *str , const char *strSearch)
{
	if(*strSearch == '\0')//if strsearch ended
	{
		return 1;
	}
	if(*strSearch == *str)//checking if chars match
	{
		strSpecialCmp(++str, ++strSearch);//advancing pointers and calling function again
	}
	else
	{
		return 0;//stop if no match is found
	}
}


char *myStrstr(const char *str, const char *strSearch, int *index)
{
	char *p;
	if(strSpecialCmp(str, strSearch) == 1)//if theres a match
	{
		return (char*)str;//returning a pointer to the first char of substring in original string
	}
	else if(*(str+1) != '\0')//if the next char in the original string is not 0
	{
		(*index)++;//advancing index according to strSpecialCmp failures
		myStrstr(++str, strSearch, index);//calling function while advancing original str
	}
	else//if the code reaches here then there is no match between str and strsearch and thus returning null
	{
		p = NULL;
		return p;
	}
}
