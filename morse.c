#include "morse.h"
#include <stdio.h>
#include <string.h>

void text_to_morse(const char text[], char output[]);
void morse_to_text(const char morse[], char output[]);
int is_morse_code_valid(const char morse[]);

void text_to_morse(const char text[], char output[]){
    int p = 0;
    int first = 1;  

    for(int i = 0; text[i] != '\0'; i++){
        char letter = text[i];

        if (letter >= 'a' && letter <='z'){
            letter = letter - 'a' + 'A';
        }

        char *translate = "";

        switch (letter){
            case 'A': translate = ".-"; break;
            case 'B': translate = "-..."; break;
            case 'C': translate = "-.-."; break;
            case 'D': translate = "-.."; break;
            case 'E': translate = "."; break;
            case 'F': translate = "..-."; break;
            case 'G': translate = "--."; break;
            case 'H': translate = "...."; break;
            case 'I': translate = ".."; break;
            case 'J': translate = ".---"; break;
            case 'K': translate = "-.-"; break;
            case 'L': translate = ".-.."; break;
            case 'M': translate = "--"; break;
            case 'N': translate = "-."; break;
            case 'O': translate = "---"; break;
            case 'P': translate = ".--."; break;
            case 'Q': translate = "--.-"; break;
            case 'R': translate = ".-."; break;
            case 'S': translate = "..."; break;
            case 'T': translate = "-"; break;
            case 'U': translate = "..-"; break;
            case 'V': translate = "...-"; break;
            case 'W': translate = ".--"; break;
            case 'X': translate = "-..-"; break;
            case 'Y': translate = "-.--"; break;
            case 'Z': translate = "--.."; break;
            case '1': translate = ".----"; break;
            case '2': translate = "..---"; break;
            case '3': translate = "...--"; break;
            case '4': translate = "....-"; break;
            case '5': translate = "....."; break;
            case '6': translate = "-...."; break;
            case '7': translate = "--..."; break;
            case '8': translate = "---.."; break;
            case '9': translate = "----."; break;
            case '0': translate = "-----"; break;
            default: translate = "?"; break;
        }

        if (!first) {
            output[p++] = ' ';
        }
        first = 0;

        for (int a = 0; translate[a] != '\0'; a++){
            output[p++] = translate[a];
        }
    }
    
    output[p] = '\0';  
}

void morse_to_text(const char morse[], char output[]){
    int p = 0;
    char buffer[10];   
    int b = 0;

    for (int i = 0; ; i++) {
        if (morse[i] != ' ' && morse[i] != '\0') {
            buffer[b++] = morse[i];
        } 
        else {
            if (b > 0) {
                buffer[b] = '\0';  

                char letter = '?';

                if (strcmp(buffer, ".-") == 0) letter = 'A';
                else if (strcmp(buffer, "-...") == 0) letter = 'B';
                else if (strcmp(buffer, "-.-.") == 0) letter = 'C';
                else if (strcmp(buffer, "-..") == 0) letter = 'D';
                else if (strcmp(buffer, ".") == 0) letter = 'E';
                else if (strcmp(buffer, "..-.") == 0) letter = 'F';
                else if (strcmp(buffer, "--.") == 0) letter = 'G';
                else if (strcmp(buffer, "....") == 0) letter = 'H';
                else if (strcmp(buffer, "..") == 0) letter = 'I';
                else if (strcmp(buffer, ".---") == 0) letter = 'J';
                else if (strcmp(buffer, "-.-") == 0) letter = 'K';
                else if (strcmp(buffer, ".-..") == 0) letter = 'L';
                else if (strcmp(buffer, "--") == 0) letter = 'M';
                else if (strcmp(buffer, "-.") == 0) letter = 'N';
                else if (strcmp(buffer, "---") == 0) letter = 'O';
                else if (strcmp(buffer, ".--.") == 0) letter = 'P';
                else if (strcmp(buffer, "--.-") == 0) letter = 'Q';
                else if (strcmp(buffer, ".-.") == 0) letter = 'R';
                else if (strcmp(buffer, "...") == 0) letter = 'S';
                else if (strcmp(buffer, "-") == 0) letter = 'T';
                else if (strcmp(buffer, "..-") == 0) letter = 'U';
                else if (strcmp(buffer, "...-") == 0) letter = 'V';
                else if (strcmp(buffer, ".--") == 0) letter = 'W';
                else if (strcmp(buffer, "-..-") == 0) letter = 'X';
                else if (strcmp(buffer, "-.--") == 0) letter = 'Y';
                else if (strcmp(buffer, "--..") == 0) letter = 'Z';
                else if (strcmp(buffer, ".----") == 0) letter = '1';
                else if (strcmp(buffer, "..---") == 0) letter = '2';
                else if (strcmp(buffer, "...--") == 0) letter = '3';
                else if (strcmp(buffer, "....-") == 0) letter = '4';
                else if (strcmp(buffer, ".....") == 0) letter = '5';
                else if (strcmp(buffer, "-....") == 0) letter = '6';
                else if (strcmp(buffer, "--...") == 0) letter = '7';
                else if (strcmp(buffer, "---..") == 0) letter = '8';
                else if (strcmp(buffer, "----.") == 0) letter = '9';
                else if (strcmp(buffer, "-----") == 0) letter = '0';

                output[p++] = letter;
                b = 0;
            }

            if (morse[i] == '\0')
                break;
        }
    }

    output[p] = '\0';
}

int is_morse_code_valid(const char morse[]) {
    char buffer[10];
    int b = 0;

    for (int i = 0; ; i++) {
        if (morse[i] != ' ' && morse[i] != '\0') {
            if (b >= 9) {
                return 0;  
            }
            
            if (morse[i] != '.' && morse[i] != '-') {
                return 0;  
            }
            
            buffer[b++] = morse[i];
        } 
        else {
            if (b > 0) {
                buffer[b] = '\0';
                b = 0;

                int ok = 0;

                if (strcmp(buffer, ".-") == 0) ok = 1;
                else if (strcmp(buffer, "-...") == 0) ok = 1;
                else if (strcmp(buffer, "-.-.") == 0) ok = 1;
                else if (strcmp(buffer, "-..") == 0) ok = 1;
                else if (strcmp(buffer, ".") == 0) ok = 1;
                else if (strcmp(buffer, "..-.") == 0) ok = 1;
                else if (strcmp(buffer, "--.") == 0) ok = 1;
                else if (strcmp(buffer, "....") == 0) ok = 1;
                else if (strcmp(buffer, "..") == 0) ok = 1;
                else if (strcmp(buffer, ".---") == 0) ok = 1;
                else if (strcmp(buffer, "-.-") == 0) ok = 1;
                else if (strcmp(buffer, ".-..") == 0) ok = 1;
                else if (strcmp(buffer, "--") == 0) ok = 1;
                else if (strcmp(buffer, "-.") == 0) ok = 1;
                else if (strcmp(buffer, "---") == 0) ok = 1;
                else if (strcmp(buffer, ".--.") == 0) ok = 1;
                else if (strcmp(buffer, "--.-") == 0) ok = 1;
                else if (strcmp(buffer, ".-.") == 0) ok = 1;
                else if (strcmp(buffer, "...") == 0) ok = 1;
                else if (strcmp(buffer, "-") == 0) ok = 1;
                else if (strcmp(buffer, "..-") == 0) ok = 1;
                else if (strcmp(buffer, "...-") == 0) ok = 1;
                else if (strcmp(buffer, ".--") == 0) ok = 1;
                else if (strcmp(buffer, "-..-") == 0) ok = 1;
                else if (strcmp(buffer, "-.--") == 0) ok = 1;
                else if (strcmp(buffer, "--..") == 0) ok = 1;
                else if (strcmp(buffer, ".----") == 0) ok = 1;
                else if (strcmp(buffer, "..---") == 0) ok = 1;
                else if (strcmp(buffer, "...--") == 0) ok = 1;
                else if (strcmp(buffer, "....-") == 0) ok = 1;
                else if (strcmp(buffer, ".....") == 0) ok = 1;
                else if (strcmp(buffer, "-....") == 0) ok = 1;
                else if (strcmp(buffer, "--...") == 0) ok = 1;
                else if (strcmp(buffer, "---..") == 0) ok = 1;
                else if (strcmp(buffer, "----.") == 0) ok = 1;
                else if (strcmp(buffer, "-----") == 0) ok = 1;

                if (!ok) return 0;
            }

            if (morse[i] == '\0')
                break;
        }
    }

    return 1;
}