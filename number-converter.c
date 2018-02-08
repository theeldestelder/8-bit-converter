#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BASE_2 2
#define BASE_8 8
#define BASE_10 10
#define BASE_16 16

void printHelp() {
    printf("Commands:\n");
    printf("  quit:                         exits the program\n");
    printf("  help:                         displays this message\n");
    printf("  convert <integer> <format>:\n");
    printf("\tnumber:\tthe integer you wish to see other representations for\n");
    printf("\tformat:\tthe format of the <integer>\n");
    printf("\tpossible formats are \"bin\", \"oct\", \"dec\", \"hex\"\n");
}



// function slightly modified from
// www.geeksforgeeks.org/convert-base-decimal-vice-versa/ 
int val(char c) {
    if (c >= '0' && c <= '9') {
        return (int)c - '0'; // return 0-9 depending on character
    }
    else { //if (c >= 'A' && c <= 'F') {
        return (int) c - 'A' + 10; // return 10 - 16 depending on character
    }
    /*else {
        printf("ERROR: invalid character %c\n", c);
        return -1; // invalid character
    }*/
}

// function slightly modified from
// www.geeksforgeeks.org/convert-base-decimal-vice-versa/ 
int toBase10(char *num, int base) {
    int result = 0;
    int len = strlen(num);
    int power = 1;

    //printf("num: %s\n", num);
    //printf("base: %d\n", base);
    //printf("len: %d\n", len);

    for (int i = len - 1; i >= 0; i--) {
        if (val(num[i]) >= base ) {
            printf("ERROR: character in number exceeds base\n");
            return -1;
        }

        result += val(num[i]) * power;
        power = power * base;
    }

    return result;
}

char reVal(int num) {
    if (num >= 0 && num <= 9) {
        return (char) (num + '0');
    }
    else {
        return (char) (num - 10 + 'A');
    }
}

void reverseString(char *str) {
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
}

// result will be answer backwards
char *fromBase10(char result[], int inputNum, int base) {
    int i = 0;
    while (inputNum > 0) {
        result[i] = reVal(inputNum % base);
        inputNum /= base;    
        i++;
    }

    result[i] = '\0'; // null terminate string

    reverseString(result);

    return result;
}

// Returns the integer base based on the input format
// Returns -1 if the given format is not valid
int inputBase(char *format) {
    if (strcmp("bin", format) == 0) {
        return BASE_2;
    }
    else if (strcmp("oct", format) == 0) {
        return BASE_8;
    }
    else if (strcmp("dec", format) == 0) {
        return BASE_10;
    }
    else if (strcmp("hex", format) == 0) {
        return BASE_16;
    }
    else { // invalid option
        return -1;
    }
}

/*
    |-----------+------+-------+----------+---------|
    |           |      |       | Unsigned | Signed  |
    | Binary    | Hex  | Octal | Decimal  | Decimal |
    |-----------+------+-------+----------+---------|
    | xxxx xxxx | xxxx | xxxxx | xxxxxxxx | xxxxxxx |
    |-----------+------+-------+----------+---------|
*/

void printNum(char num[], int base, int isSigned, int base10Num) {
    if (base == BASE_2) {
        int maxSpots = 8; // 1 byte of info
        int len = strlen(num);
        char fullNum[maxSpots];

        int index = 0;
        if (len != maxSpots) { // prepend with 0s if num isn't the max length
            for (index; index < maxSpots - len; index++) {
                fullNum[index] = '0';
            }
        }
        for (int i = 0; i < len; i++) { // fill out rest of fullNum with num
            fullNum[index] = num[i];
            index++;
        }
        for (int i = 0; i < maxSpots; i++) { // print out whole number with a space in the middle
            if (i % 4 == 0 && i != 0) {
                printf(" ");
            }
            printf("%c", fullNum[i]);
        }
    }
    else if (base == BASE_8) {
        int maxSpots = 4; // max for 1 byte in octal
        int len = strlen(num);
        char fullNum[maxSpots];

        int index = 0;
        if (len != maxSpots) { // prepend with 0s if num isn't the max length
            for (index; index < maxSpots - len; index++) {
                fullNum[index] = '0';
            }
        }
        for (int i = 0; i < len; i++) { // fill out rest of fullNum with num
            fullNum[index] = num[i];
            index++;
        }
        for (int i = 0; i < maxSpots; i++) { // print out whole number with a space in the middle
            if (i % 4 == 0 && i != 0) {
                printf(" ");
            }
            printf("%c", fullNum[i]);
        }
    }
    else if (base == BASE_16) {
        printf("0x");
        int len = strlen(num);
        if (len == 1) {
            printf("0");
        }

        for (int i = 0; i < len; i++) {
            printf("%c", num[i]);
        }
    }
    else if (base == BASE_10) {
        
        if (isSigned == 1) {
            if (base10Num > 127) { // 127 is max for 1 byte signed int
                base10Num = (-1) * (base10Num + 1);
            }
        }

        printf("%8d", base10Num);
    }
}

void printOutputTable(char *num, char *format) {
    int inputFormat = inputBase(format);
    int base10Num = toBase10(num, inputFormat); 
    char result[9];

    fromBase10(result, base10Num, BASE_2);
    printf("bin: %s\n", result);
    fromBase10(result, base10Num, BASE_8);
    printf("oct: %s\n", result);
    fromBase10(result, base10Num, BASE_10);
    printf("dec: %s\n", result);
    fromBase10(result, base10Num, BASE_16);
    printf("hex: %s\n", result);

    printf("  |-----------+------+-------+----------+----------|\n");
    printf("  |           |      |       | Unsigned |  Signed  |\n");
    printf("  | Binary    | Hex  | Octal | Decimal  |  Decimal |\n");
    printf("  |-----------+------+-------+----------+----------|\n");
    printf("  | ");
    fromBase10(result, base10Num, BASE_2);
    printNum(result, BASE_2, 0, base10Num);
    printf(" | ");
    fromBase10(result, base10Num, BASE_16);
    printNum(result, BASE_16, 0, base10Num);
    printf(" |  ");
    fromBase10(result, base10Num, BASE_8);
    printNum(result, BASE_8, 0, base10Num);
    printf(" | ");
    fromBase10(result, base10Num, BASE_10);
    printNum(result, BASE_10, 0, base10Num);
    printf(" | ");
    fromBase10(result, base10Num, BASE_10);
    printNum(result, BASE_10, 1, base10Num);
    printf(" |\n");
    printf("  |-----------+------+-------+----------+----------|\n");

    if (inputFormat == -1) {
        printf("Not a valid format\n");
        return; 
    }
}

int main(int argc, char *argv[]) {
    printf("Convert numbers between bases\n");
    printHelp();

    char command[128];
    int success = 0;

    //printf("0x0A: %d", atoi("0x0A"));

    while(1) {
        printf("converter> ");
        success = fscanf(stdin, "%s", command);

        if (strcmp("quit", command) == 0) {
            printf("Exiting...\n");
            int success = 0;
            break; 
        }
        else if (strcmp("help", command) == 0) {
            printHelp();
        }
        else if (strcmp("convert", command) == 0) {
            fscanf(stdin, "%s", command); // get the number into command

            int numLength = strlen(command);
            char num[numLength]; // the char array of the number
            strcpy(num, command);
            //printf("%s\n", num);

            fscanf(stdin, "%s", command); // get the format    
            printf("%d\n", toBase10(num, inputBase(command)));

            //printf("%d\n", inputBase(command));

            //fscanf(stdin, "%s", command); // get the format    
            printOutputTable(num, command);
        }
        else { 
            printf("Unknown command\n");
        }
    }
}
