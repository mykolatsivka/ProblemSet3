#include <stdio.h>
#include "hangman.h"
#include "morse.h"

int main(){
    printf("%d\n", is_word_guessed("secret", "aeiou"));
    // prints: 0
    printf("%d\n", is_word_guessed("hello", "aeihoul"));
    // prints ^ 1
    char result1[30];
    get_guessed_word("container", "arpstxgoieyu", result1);
    // result = "_o_tai_er"
    char result[30];
    get_available_letters("arpstxgoieyu", result);
    // result = "bcdfhjklmnqvwz"
    printf("%s", result);
    char secret[256] = "";
    get_word(secret);
    hangman(secret);
    
    char output[150];
    text_to_morse("yell", output);
    puts(output);

    char output1[150];
    morse_to_text("-... .-. ..- ... -.... -.... .-. ---", output1);
    printf("\n");
    puts(output1);
    if(is_morse_code_valid(".... . .-.. .-.. ---")){
        printf("Code is valid! \n");
    } else {
        printf("Code is invalid! \n");
    }

    if(is_morse_code_valid(".... . .-.--. .-.. ---")){
        printf("Code is valid! \n");
    } else {
        printf("Code is invalid! \n");
    }
}
