#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    //check command line arguments
    if (argc != 2) {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    //check 26 characters in key
    if (strlen(argv[1]) != 26) {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    //check key
    //instantiate key letter duplicate checking char array
    char upperKey[27] = "";
    for (int i = 0; i < strlen(argv[1]); i++) {
        //check that key only contains letters
        if (islower(argv[1][i]) || isupper(argv[1][i])) {
        }
        else {
            printf("Key can only contain letters.\n");
            return 1;
        }
        //check that key has no duplicate letters
        //instantiate lookup char
        string ret;
        //turn agrv[1][i] char into uppercase (so can see dup btw upper and lower)
        //turn argv[1][i] char into char + null pointer (\0)
        char ch[2] = {toupper(argv[1][i])};
        //checks myAlpha to see if the letter exists already
        ret = strchr(upperKey, ch[0]);
        if (ret == NULL) {
            //add letter to myAlpha if not found
            strcat(upperKey, ch);
        }
        else {
            printf("Key cannot have duplicate letters.\n");
            return 1;
        }
    }

    //prompt user
    string userIn = get_string("plaintext:  ");

    //convert plaintext to ciphertext
    //creates a char array instead of a string (instead of userIn)
    //which allows assigning at indexes
    char replacedUser[strlen(userIn)];
    //goes through each character in userIn
    for (int i = 0; i < strlen(userIn); i++) {
        if (islower(userIn[i])) {
            //keeps original casing
            replacedUser[i] = tolower(upperKey[userIn[i] - 97]);
        }
        else if (isupper(userIn[i])) {
            replacedUser[i] = toupper(upperKey[userIn[i] - 65]);
        }
        else {
            replacedUser[i] = userIn[i];
        }
    }
    //adds a null pointer to the end of the char array
    replacedUser[strlen(userIn)] = '\0';

    //output ciphertext
    printf("ciphertext: %s\n",replacedUser);
}
