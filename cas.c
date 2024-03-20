// Program to validate if a CAS number is valid using its last check digit
// CAS number is formatted as XXXXXXX-XX-X where the first part is 2-7 digits, the second part is 2 digits, and the last part is 1 check digit
// Can be represented as Ni ... N4 N3 - N2 N1 - R where R is the check digit
// The check digit is calculated by multiplying each digit by its position and summing them up, then taking the remainder of the sum divided by 10
// https://www.cas.org/support/documentation/chemical-substances/checkdig

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MIN_CAS_LENGTH 7
#define MAX_CAS_LENGTH 12

int validateCas(char *casNumber);

int main()
{

    printf("Enter a CAS number: ");
    char casNumber[15] = {0};
    scanf("%s", casNumber);

    printf("The CAS number is: %s\nCheck-digit: %d\n", casNumber, casNumber[strlen(casNumber) - 1] - '0');

    switch (validateCas(casNumber))
    {
    case -1:
        printf("Invalid CAS number\n");
        break;
    case 0:
        printf("Invalid CAS number (check digit mismatch)\n");
        break;
    case 1:
        printf("Valid CAS number\n");
        break;
    }

    return EXIT_SUCCESS;
}

int validateCas(char *casNumber)
{
    int casLen = strlen(casNumber);
    int checkdigit = casNumber[casLen - 1] - '0';
    if (
        casNumber[casLen - 2] != '-' || casNumber[casLen - 5] != '-' ||
        casLen < MIN_CAS_LENGTH || casLen > MAX_CAS_LENGTH ||
        checkdigit < 0 || checkdigit > 9
    )
    {
        return -1;
    }

    char strippedCas[15] = {0};
    int j = 0;
    for (int i = 0; i < casLen - 2; i++)
    {
        if (casNumber[i] != '-' && !isdigit(casNumber[i]))
        {
            return -1;
        }
        if (casNumber[i] != '-')
        {
            strippedCas[j] = casNumber[i];
            j++;
        }
    }
    strippedCas[j] = '\0';
    printf("Stripped CAS number: %s\n", strippedCas);
    int sum = 0;
    for (int i = 0; i < strlen(strippedCas); i++)
    {
        sum += (strippedCas[i] - '0') * (strlen(strippedCas) - i);
    }
    printf("Sum: %d\n", sum);

    return sum % 10 == checkdigit;
}
