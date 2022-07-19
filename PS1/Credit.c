#include <cs50.h>
#include <stdio.h>

int main(void)
{
    long userCard = get_long("Number: ");
    int cardLength = 2;
    long firstTwo = userCard;
    long luhnsCard = userCard;
    int luhnsSecondNum = 0;
    int luhnsOneDigit = 0;
    int luhnsTwoDigit = 0;
    int luhns = 0;

    //creates firstTwo
    while (firstTwo > 99) {
        cardLength++;
        firstTwo /= 10;
    }
  
    //making luhn's
    while (luhnsCard > 0) {
        //add last digit to luhns
        luhns += luhnsCard % 10;
        //get rid of last digit
        luhnsCard /= 10;
        //making sure there was a second to last digit
        if (luhnsCard > 0) {
            //go to second to last digit
            luhnsSecondNum = luhnsCard % 10;
            //get the first (and potentially second) digit
            luhnsSecondNum *= 2;
            if (luhnsSecondNum / 10 == 0) {
                luhnsOneDigit = luhnsSecondNum;
                //forgot to add this here
                luhnsTwoDigit = 0;
            }
            else {
                luhnsOneDigit = luhnsSecondNum / 10;
                luhnsTwoDigit = luhnsSecondNum % 10;
            }
            //add them to luhns
            luhns += luhnsOneDigit + luhnsTwoDigit;
            //get rid of second to last digit
            luhnsCard /= 10;
        }
    }
  
    //checking card length
    if (cardLength < 13 || cardLength > 16 || cardLength == 14) {
        printf("INVALID\n");
    }
    //VISA
    else if (cardLength == 13) {
        if (firstTwo / 10 == 4) {
            if (luhns % 10 == 0) {
                printf("VISA\n");
            }
            else {
                printf("INVALID\n");
            }
        }
        else {
            printf("INVALID\n");
        }
    }
    //AMEX
    else if (cardLength == 15) {
        if (firstTwo == 34 || firstTwo == 37) {
            if (luhns % 10 == 0) {
                printf("AMEX\n");
            }
            else {
                printf("INVALID\n");
            }
        }
        else {
            printf("INVALID\n");
        }
    }
    //MC or VISA (16)
    else {
        if (firstTwo / 10 == 4) {
            if (luhns % 10 == 0) {
                printf("VISA\n");
            }
            else {
                printf("INVALID\n");
            }
        }
        else if (
        firstTwo == 51 ||
        firstTwo == 52 ||
        firstTwo == 53 ||
        firstTwo == 54 ||
        firstTwo == 55) {
            if (luhns % 10 == 0) {
                printf("MASTERCARD\n");
            }
            else {
                printf("INVALID\n");
            }
        }
        else {
            printf("INVALID\n");
        }
    }
    //printf("%i, %li, %i\n",cardLength, firstTwo, luhns);
}
