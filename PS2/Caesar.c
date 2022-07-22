#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    //if no command line argument or more than one
    if (argc != 2) {
        printf("Usage ./caesar key\n");
        return 1;
    }
    //if input != 48 - 57
    for (int i = 0; i < strlen(argv[1]); i++) {
        if (argv[1][i] < 48 || argv[1][i] > 57) {
            printf("Usage ./caesar key\n");
            return 1;
        }
    }
    //start accepting input
    int key = atoi(argv[1]) % 26;
    string userIn = get_string("plaintext:  ");
    for (int i = 0; i < strlen(userIn); i++) {
        //capitalized 65-90
        if (userIn[i] >= 65 && userIn[i] <= 90) {
            if (userIn[i] + key > 90) {
                userIn[i] = userIn[i] - 26 + key;
            }
            else {
                userIn[i] += key;
            }
        }
        //lowercase 97-122
        else if (userIn[i] >= 97 && userIn[i] <= 122) {
            if (userIn[i] + key > 122) {
                userIn[i] = userIn[i] - 26 + key;
            }
            else {
                userIn[i] += key;
            }
        }
        //non-alpha should output unchanged
    }
    printf("ciphertext: %s", userIn);
    printf("\n");
    return 0;
}
