//
// Created by DANA on 1/1/2023.
//

#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <stdio.h>
#include <unistd.h>
//#include "sudoku_generator.c"
#define dif_color 6

#define K 35 //missing digits
#define def_wAtt 7
int def_board[9][9];
int solved[9][9];

#include "sudoku_generator.c"




void print_sudoku(int board[9][9]);
bool have_repeat(int select[9] ,int num);



/**
 * clear console screen.
 */
void clearScreen(){
    system("@cls||clear");
}

/**
 * log string `str` in log file.
 * @param str string text to log.
 */
void log(char *str){
    FILE *txt;
    txt = fopen("log.txt","w+");
    fprintf(txt,"\n%s",str);
    fclose(txt);
}
/**
 * check the array with 9 size have repeat with num.
 * @param select array[9].
 * @param num number to search,
 * @return if have repeate return true otherwise false.
 */
bool have_repeat(int select[9] ,int num){
    for (int i = 0; i < 9; i++) {
        if(select[i] == num) return true;
    }
    return false;
}
/**
 *
 * @param board array[9][9] of sudoku board.
 * @param i i of check number.
 * @param j j of check number.
 * @param input number to check.
 * @return if input didnt break sudoku rules return true otherwise false.
 */
bool is_valid_input(int board[9][9] , int i , int j,int input){
    int select[9];
    //check vertical
    memcpy(select,board[i],sizeof(select));
    if(have_repeat(select,input)) return false;

    //check Horizontal
    for (int k = 0; k < 9; k++) {
        select[k] = board[k][j];
    }
    if(have_repeat(select,input)) return false;

    //check in box 3*3
    int i_from , i_to;
    int j_from , j_to;
    i_from = i - i % 3;
    i_to = i_from + 3;
    j_from = j - j%3;
    j_to = j_from + 3;
    int x=0;
    for (int k = i_from; k < i_to; k++) {
        for (int l = j_from; l < j_to; l++) {
            select[x++] = (int) board[k][l];
        }
    }
    return !have_repeat(select,input);
}

/**
 * check array `board` dont have null/0 index.
 * @param board array[9][9] to check dont have null or 0 element.
 * @return bool if any of array `board` element was null/0 return false otherwise true.
 */
bool complected(int board[9][9]){
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if(board[i][j] == 0) return false;
        }
    }
    return true;
}
/**
 * make array `arr` to null all index.
 * @param arr array[9][9] to null indexes.
 */
void do_null(int arr[9][9]){
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            arr[i][j] = NULL;
        }
    }
}

/**
 * Sudoku solved or not.
 * @param arr array of sudoku index.
 * @return bool return true if resolved otherwise false.
 */
bool is_solved(int arr[9][9]){
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if(arr[i][j] != solved[i][j]) return false;
        }
    }
    return true;
}
/**
 * init
 */
void init(){
    int i, commandposition, commandpos2, invalidNumber = 1;
    int num1, num2, num3;
    int board[9][9];
    bool table_made = false;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int bold_Watt = 15;
    while (1){
        char user_input[10];
        printf("\nplease select:");
        printf("\n%s" ,(!table_made  ? "play," : "new game,reset,solve,unsolve,(i,j,number),"));
        printf("help,quit:");
        fgets(user_input, 10, stdin);
        invalidNumber = 1;
        num1 = 0;
        num2 = 0;
        num3 = 0;

        for (commandposition = 0; commandposition < strlen(user_input); commandposition++) {
            if (user_input[commandposition] == ',') {
                for (commandpos2 = commandposition + 1; commandpos2 < strlen(user_input); commandpos2++) {
                    if (user_input[commandpos2] == ',') {
                        invalidNumber = 0;
                        break;
                    }
                }
                break;
            }
        }
        for (i = 0; i < strlen(user_input)-1; i++)
            user_input[i] = tolower(user_input[i]);

        user_input[strlen(user_input)-1] = NULL;

        if((!strcmp(user_input , "play") && !table_made) || (!strcmp(user_input , "new game") && table_made)){
            do_null(def_board);
            do_null(board);
            do_null(solved);
            fillValues(K);
            table_made = true;
            memcpy(board,def_board,sizeof(board));
            clearScreen();
            print_sudoku(board);
        }else if(invalidNumber == 0  && table_made){
            for (i = 0; i < commandposition; i++)
                num1 = 10 * num1 + (user_input[i] - '0');

            for (i = commandposition + 1; i < commandpos2; i++)
                num2 = 10 * num2 + (user_input[i] - '0');

            for (i = commandpos2 + 1; i < strlen(user_input); i++)
                num3 = 10 * num3 + (user_input[i] - '0');

            if(num1 <= 0 || num2 <= 0 || num3 < 0 || num1 >9 || num2 >9 || num3 >9 ){
                printf("invalid numbers.!");
            }else{

                    if(def_board[num1 - 1][num2 - 1] == 0){
                        (board[num1 - 1][num2 - 1]) = num3;
                        clearScreen();
                        print_sudoku(board);

                        if(complected(board)){
                            if(is_solved(board)) {
                                SetConsoleTextAttribute(hConsole, 160);//background:green , text:black.
                                printf("\a\namazing u solved sudoku.!!!\n");
                                SetConsoleTextAttribute(hConsole, def_wAtt);
                                do_null(def_board);
                                do_null(board);
                                do_null(solved);
                                table_made = false;
                            }
                        }
                    }else printf("u cant change this.(i=%d,j=%d,number=%d)",num1,num2,def_board[num1 - 1][num2 - 1]);

            }
        }else if(!strcmp(user_input , "help me") && table_made){
            clearScreen();
            print_sudoku(solved);
            for (i = 3; i > 0; i--) {
                printf("%d\r",i);
                sleep(1);
            }
            clearScreen();
            print_sudoku(board);
        }else if(!strcmp(user_input , "solve") && table_made){
            clearScreen();
            print_sudoku(solved);
        }else if(!strcmp(user_input , "unsolve") && table_made){
            clearScreen();
            print_sudoku(board);
        }else if(!strcmp(user_input , "reset") && table_made){
            memcpy(board,def_board,sizeof(board));
            clearScreen();
            print_sudoku(board);
        }else if(!strcmp(user_input , "help")){
            SetConsoleTextAttribute(hConsole, bold_Watt);//bold text
            printf("\nThis is the help menu. Available commands:\n\n");
            SetConsoleTextAttribute(hConsole, def_wAtt);//default
            printf("Entering a number, then a comma, then another number, then another comma, then a final number - marks that square with the final number.ex(2,4,6)\n");
            SetConsoleTextAttribute(hConsole, bold_Watt);//bold text
            printf("play: ");
            SetConsoleTextAttribute(hConsole, def_wAtt);//default
            printf("make sudoku.\n");
            SetConsoleTextAttribute(hConsole, bold_Watt);//bold text
            printf("reset: ");
            SetConsoleTextAttribute(hConsole, def_wAtt);//default
            printf("resets the board\n");
            SetConsoleTextAttribute(hConsole, bold_Watt);//bold text
            printf("solve: ");
            SetConsoleTextAttribute(hConsole, def_wAtt);//default
            printf("solves the entered sudoku problem.\n");
            SetConsoleTextAttribute(hConsole, bold_Watt);//bold text
            printf("unsolve: ");
            SetConsoleTextAttribute(hConsole, def_wAtt);//default
            printf("unsolves the recently solved sudoku problem.\n");
            SetConsoleTextAttribute(hConsole, bold_Watt);//bold text
            printf("quit: ");
            SetConsoleTextAttribute(hConsole, def_wAtt);//default
            printf("exits the program.\n");
        }else if(!strcmp(user_input , "quit")){
            printf("thanks for ur time ;)");
            sleep(2);
            exit(1);
        }else printf("choose valid command.(%s)\n",user_input);
    }
}

int main(){
    srand(time(0));
    printf("made by D.a\n");
    init();
    return 1;
}
#include "print_sudoku.c"
