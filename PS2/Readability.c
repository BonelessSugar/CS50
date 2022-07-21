#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int countLetters(string text);
int countWords(string text);
int countSentences(string text);

int main(void)
{
    string text = get_string("Text: ");
    //printf("%s\n",text);
    int totalLetters = countLetters(text);
    //printf("%i letters\n",totalLetters);
    int totalWords = countWords(text);
    //printf("%i words\n",totalWords);
    int totalSentences = countSentences(text);
    //printf("%i sentences\n",totalSentences);
    //you have to multiply before you divide... >:(
    double L = totalLetters * 100.0 / totalWords;
    double S = totalSentences * 100.0 / totalWords;
    double index = (0.0588 * L) - (0.296 * S) - 15.8;
    //printf("%.2d\n",65*100/14);
    //printf("%.2f\n",L);
    //printf("%.2f\n",S);
    //printf("%.2f\n",index);
    if (index >= 16) {
        printf("Grade 16+\n");
    }
    else if (index < 1) {
        printf("Before Grade 1\n");
    }
    else {
        printf("Grade %i\n",(int)round(index));
    }
}

int countLetters(string text) {
    int letterAmount = 0;
    for (int i = 0; i < strlen(text); i++) {
        if ((text[i] >= 65 && text[i] <= 90) || (text[i] >= 97 && text[i] <= 122)){
            letterAmount++;
        }
    }
    return letterAmount;
}

int countWords(string text) {
    int wordsAmount = 1;
    for (int i = 0; i < strlen(text); i++) {
        if (text[i] == 32) {
            //tolerates multiple spaces in a row between words
            if (text[i-1] == 32) {
            }
            else {
                wordsAmount++;
            }
        }
    }
    return wordsAmount;
}

//you should consider any sequence of characters that ends
//with a . or a ! or a ? to be a sentence
int countSentences(string text) {
    int sentenceAmount = 0;
    for (int i = 0; i < strlen(text); i++) {
        if (text[i] == 46 || text[i] == 33 || text[i] == 63) {
            sentenceAmount++;
        }
    }
    return sentenceAmount;
}
