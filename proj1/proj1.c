/*
 *	VUT FIT
 *	IZP 2017/2018
 *	Projekt 1 - Prace s textem
 *	Autor: Adam Abrahám
 *	Datum: 5.11.2017
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_CHARS 26
#define MAX_LOC 101

void noArg(char *city, char *charArray, int *duplicate, int *charInArray);

void checkArg(char *arg);

void readFile(char *argument, char *city, char *foundCity, char *lastKnownCity, char *charArray, int *duplicate, int *charInArray);

void addChar(char *charArray, char letter, int **duplicate, int **charInArray);

void printEnable(char* charArray);

int main(int argc, char *argv[]) {

    char charArray[MAX_CHARS] = {0};
    char city[MAX_LOC] = {0};
    char foundCity[MAX_LOC] = {0};
    char lastKnownCity[MAX_LOC] = {0};
    int charInArray = 0;
    int duplicate = 0;

    /*
     * If the number of arguments is equal to 1 (( ./proj1 only ))
     * run function noArg()
     */
    if (argc == 1) {
        noArg(city, charArray, &duplicate, &charInArray);
    }else{
        for(int i=1; i < argc;i++){
            if((int)strlen(argv[i]) > 20){
                puts("Argument is too long !\n");
                return 0;
            }
        }
    }

    // Append a copy of the first argument to a variable
    char argument[42] = {0};
    strcat(argument, argv[1]);

    /*
     * At multiple arguments
     * append the rest of them to the previous variable
     */
    if(argc > 2){
        for(int i=0; i < (argc - 2); i++){
            strcat(argument, argv[i+2]);
        }
    }

    //Check the final argument for invalid characters
    checkArg(argument);

    //Read from stdin
    readFile(argument, city, foundCity, lastKnownCity, charArray, &duplicate, &charInArray);

    //Print out the result
    if(foundCity[0] == '\0' && charInArray == 1) {
        if(duplicate == 0){
            printf("FOUND: %s\n", lastKnownCity);
        }else {
            printEnable(charArray);
        }
    } else if(foundCity[0] != '\0' && charInArray == 0 && duplicate == 0){
        printf("FOUND: %s\n", foundCity);
    }else if(foundCity[0] != '\0' && charInArray != 0){
        printf("FOUND: %s\n", foundCity);
        printEnable(charArray);
    } else if(charInArray == 0 && foundCity[0] == '\0'){
        puts("Not found!");
    } else {
        printEnable(charArray);
    }

    return 0;
}

void noArg(char *city, char *charArray, int *duplicate, int *charInArray) {
    int c, i = 0;
    while (i <= MAX_LOC - 1 && (c = getchar()) != EOF) {
        if (c != '\n' && isalpha(c)) {
            city[i++] = (char) (toupper(c));
        } else if(c == '\n'){
            addChar(charArray, city[0], &duplicate, &charInArray);
            memset(city, 0, MAX_LOC);
            i = 0;
        }
    }
    if(i <= MAX_LOC - 1){
        printEnable(charArray);
    }else{
        printf("The address is too long!\n");
    }
    exit(1);
}

void checkArg(char *arg) {
    //If the character is invalid close the program, else convert it to uppercase
    for (int i = 0; i < (int)strlen(arg); i++) {
        if (isalpha(arg[i]) == 0 && arg[i] != ' ') {
            puts("ERROR: Invalid character in the argument!\nValid characters: A-Z, a-z and 'space'");
            exit(1);
        }else{
            arg[i] = (char)toupper(arg[i]);
        }
    }
}

void readFile(char *argument, char *city, char *foundCity, char *lastKnownCity, char *charArray, int *duplicate, int *charInArray){
    /*
     * Read characters from stdin (( <adresy.txt ))
     * While the char. ISN'T 'ENTER' and is alphabetic, save the char. to an array (( city ))
     * If the char. IS 'ENTER':
     *   -Check If the array and the argument are equal
     *   YES:
     *     -If the argument and array length are the same,
     *      copy the array and reset the loop.
     *     -Else append the unmatching character to an array
     *      and copy the array
     *
     *  -Empty the array
     *  -Reset the loop
     */
    int c;
    int i = 0;
    while ( i <= MAX_LOC - 1 && (c = getchar()) != EOF ) {
        if (c != '\n' && isalpha(c)) {
            city[i++] = (char)toupper(c);
        } else if(c == '\n'){
            if (memcmp(argument, city, strlen(argument)) == 0) {
                if((int)strlen(argument) == i){
                    memcpy(foundCity, city, MAX_LOC);
                    memset(city, 0, MAX_LOC);
                    i = 0;
                    continue;
                }else if (strcmp(city, lastKnownCity) != 0){
                    addChar(charArray, city[strlen(argument)], &duplicate, &charInArray);
                    memcpy(lastKnownCity, city, MAX_LOC);
                }
            }
            memset(city, 0, MAX_LOC);
            i = 0;
        }
    }
    if(i > MAX_LOC-1){
        printf("The address is too long!\n");
        exit(1);
    }

}

void addChar(char *charArray, char letter, int **duplicate, int **charInArray) {
    //Check the array for duplicates
    for (int i = 0; i < MAX_CHARS; i++) {
        if (toupper(letter) == toupper(charArray[i])) {
            **duplicate += 1;
            return;
        }
    }
    charArray[toupper(letter) - 'A'] = (char) toupper(letter);
    **charInArray += 1;
}

void printEnable(char* charArray){
    printf("ENABLE: ");
    for(int i=0; i < MAX_CHARS; i++){
        if(charArray[i] != '\0'){
            putchar(charArray[i]);
        }
    }
    putchar('\n');
}
