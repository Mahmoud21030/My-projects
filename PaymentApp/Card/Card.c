#define _CRT_SECURE_NO_WARNINGS

#include "Card.h"
///////////////////////////////////////////////////////////////////////////
/////////////getCardHolderName////////////////////////////////////////////
/**
 * It takes the card data adress and gets the card holder name.
 *  cardData is a pointer to a structure of type ST_cardData_t.
 */
EN_cardError_t getCardHolderName(ST_cardData_t* cardData)
{
	uint8_t temp[50]; // more space for avoiding crash in large input
	printf("\n	Please Enter The CardHolder Name: ");
	gets(temp);

	/* Checking if the length of the string is between 19 and 25 characters and
	if all the characters in the string are alphabetic .If it is, it assigns the
	adress of temp to cardData->cardHolderName. */
	if (strlen((char *)temp) > 19 && strlen((char*)temp) < 25 && s_isalpha((char*)temp))
	{
		strcpy((char*)cardData->cardHolderName, (char*)temp);
		printf("\n	Printing %s\n", cardData->cardHolderName);
		return OK;
	}
	else
	{
		return WRONG_NAME;
	}
}

/*
*It returns 1 if all the characters in the string are alphabetic, and 0 otherwise
*
*( string ) The string to be checked.
*/
bool s_isalpha(char* string)
{
	int n = strlen(string);
	int counter = 0;
	for (int i = 0; i < n; i++)
	{
		if (isalpha(string[i]) != 0 || string[i] == ' ') //check alpha and space
			counter++;
	}
	return counter == n;
}
//////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
/////////////////////////////////getCardPAN/////////////////////////////////

//same idea of cardholdername
EN_cardError_t getCardPAN(ST_cardData_t* cardData)
{
	uint8_t temp[50]; // more space for avoiding crash in large input
	uint8_t*ptr = CardGenerator();

	printf("\nGenetrated Luhn(Valid Credit card number): %s\n You could use if you need it.\n",ptr);
	printf("\n	Please Enter Your PAN: ");
	gets((char*)temp);

	/* Checking if the length of the string is between 16 and 19 characters and
	if all the characters in the string are numbers .If it is, it assigns the
	adress of temp to cardData->primaryAccountNumber. */
	if (strlen((char*)temp) > 15 && strlen((char*)temp) < 20
	&& s_isdigit((char*)temp) && isValidCard((char*)temp)==0)
	{
		strcpy((char*)cardData->primaryAccountNumber, (char*)temp); //saving into the struct
		printf("\n	Print %s\n", (char*)cardData->primaryAccountNumber);
		return OK;
	}
	else
	{
		return WRONG_PAN;
	}

}

bool s_isdigit(char* string)
{
	int n = strlen(string);
	int counter = 0;
	for (int i = 0; i < n; i++)
	{
		if (isdigit(string[i]) != 0) //check if it is digit
			counter++;
	}
	return counter == n;
}
/**
 * The function checks if the credit card number is valid or not.
 *
 * @param string a string of numbers
 *
 * return The function isValidCard() returns the first digit of the sum of the digits of the card
 * number.
 *if it is 0 then it's valid otherwise notvalid
 */
uint8_t isValidCard(char* string)
{
	int n = strlen(string);

	uint8_t* array = calloc(4, n);
	for (int i = 0; i < n; i++) //convert from string to array of uint8_t
	{
		array[i] = string[i] - '0';
	}
	int sum = 0;
	for (int i = n - 1; i >= 0; i -= 2) // sum of number start from the last index and step 2
		sum += array[i];
	for (int i = n - 2; i >= 0; i -= 2)
		/* sum of 2 * number start from the digit next to the last
		index and step 2*/
	{
		if ((2 * array[i]) > 9)
		{
			sum += (2 * array[i]) % 10 + (2 * array[i]) / 10;
		}
		else
		{
			sum += 2 * array[i];
		}
	}
	free(array);
	return (sum % 10); /*if the frist digit of sum is 0 then output is 0 value otherwise non zero number*/
}
/**
 * It generates a random number, then checks if it's a valid credit card number, and if it is, it
 * returns it
 *
 * @param n+x the number of digits you want to generate
 *
 * @return A pointer to a string of characters.
 */
uint8_t* CardGenerator(void)
{
	//unsigned long long card to store
	//array to Arithmetic operation it's easier to handle thing with array
	int n =15+rand()%3; //random length max 3 cz tha card max lenght is 19
	time_t t;
	srand((unsigned)time(&t));
	unsigned long long card = 1;

	for (int i = 0; i < n; i++) //It generates a random number
	{
		int r = (rand() % 9);//max number is 9 min number is 0
		card += r;
		card *= 10;
	}
	n++;
	uint8_t* final = calloc(1, n+1);
	sprintf(final, "%llu%i", card,0);//adding 0 @the end of the number //printf("\n%s  %i\n", final, (10-isValidCard(final))%10);
	sprintf(&final[n], "%i", (10 - isValidCard(final)) % 10); //printf("\nfinal%s ", final);


	return final;
}

///////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData)
{
	uint8_t temp[10]; // more space for avoiding crash in large input
	printf("\n	Please Enter Your Card Expiry Date e.g: 05/22: ");
	gets(temp);

	/* Checking if the length of the string is between 16 and 19 characters and
	if all the characters in the string are numbers .If it is, it assigns the
	adress of temp to cardData->primaryAccountNumber. */
	if (strlen((char*)temp) == 5 && s_isdate((char*)temp))
	{
		strcpy((char*)cardData->cardExpirationDate, (char*)temp);
		printf("\n\n	Printing %s\n",(char*)cardData->cardExpirationDate);
		return OK;
	}
	else
	{
		return WRONG_EXP_DATE;
	}
	return OK;
}

/**
*It checks if the string is a date in the format  mm / yy
*
*@param string The string to be checked.
*
*@return 1 if the format is correct, 0 if not
*/
bool s_isdate(char* string)
{
	int n = strlen(string);
	int counter = 0;
	int month = atoi(string); //taking month to integer
	for (int i = 0; i < n; i++) //checking the format
	{
		if (isdigit(string[i]) != 0)
			counter++; //counter is the number of digits in format
	}
	if (counter == 4 && string[2] == '/' && month < 13)
		return true;

	return false;
}



