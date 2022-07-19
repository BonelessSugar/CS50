#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height = 0;
    while (height < 1 || height > 8) {
        height = get_int("Height :");
    }
    int addPound = 0;
    while (height > 0) {
        string block = "#";
        printf("%*s",height,"#");
        for (int i = addPound; i > 0; i--) {
            printf("#");
        }
        printf("  #");
        for (int i = addPound; i > 0; i--) {
            printf("#");
        }
        printf("\n");
        addPound++;
        height--;
    }
}
