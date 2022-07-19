#include <stdio.h>

int main(void) {
    //prompt user for their name
    printf("What's your name? ");
    char str[2];
    scanf("%s",str);
    //print "hello, " + name
    printf("Hello, %s.\n", str);
}
