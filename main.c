//
// Created by DANA on 1/1/2023.
//

#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <conio.h>

#include <stdio.h>
#include <unistd.h>


#ifdef _WIN32 //OS is windows
#include <windows.h>
#define color 1
#else
#define color 0
#endif
#define dif_color 6
#define def_wAtt 7
#include "w_console.c"

void MySetTextColor(int colorcode) {
    SetConsoleTextAttribute(hConsole, colorcode);//bold text
}

#define K 35 //missing digits.

int def_board[9][9];
int solved[9][9];

#include "sudoku_generator.c"


void print_sudoku(int board[9][9]);

/**
 * clear console screen.
 */
void clearScreen() {
    system("@cls||clear");
}

/**
 * log string `str` in log file.
 * @param str string text to log.
 */
void log(char *str) {
    FILE *txt;
    txt = fopen("log.txt", "w+");
    fprintf(txt, "\n%s", str);
    fclose(txt);
}
/**
 * check the array with 9 size have repeat with num.
 * @param select array[9].
 * @param num number to search,
 * @return if have repeate return true otherwise false.
 */
bool have_repeat(int select[9], int num) {
    for (int i = 0; i < 9; i++) {
        if (select[i] == num) return true;
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
bool is_valid_input(int board[9][9], int i, int j, int input) {
    int select[9];
    //check vertical
    memcpy(select, board[i], sizeof(select));
    if (have_repeat(select, input)) return false;

    //check Horizontal
    for (int k = 0; k < 9; k++) {
        select[k] = board[k][j];
    }
    if (have_repeat(select, input)) return false;

    //check in box 3*3
    int i_from, i_to;
    int j_from, j_to;
    i_from = i - i % 3;
    i_to = i_from + 3;
    j_from = j - j % 3;
    j_to = j_from + 3;
    int x = 0;
    for (int k = i_from; k < i_to; k++) {
        for (int l = j_from; l < j_to; l++) {
            select[x++] = (int) board[k][l];
        }
    }
    return !have_repeat(select, input);
}

/**
 * check array `board` dont have null/0 index.
 * @param board array[9][9] to check dont have null or 0 element.
 * @return bool if any of array `board` element was null/0 return false otherwise true.
 */
bool complected(int board[9][9]) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (board[i][j] == 0) return false;
        }
    }
    return true;
}

/**
 * make array `arr` to null all index.
 * @param arr array[9][9] to null indexes.
 */
void do_null(int arr[9][9]) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            arr[i][j] = (int) NULL;
        }
    }
}

/**
 * Sudoku solved or not.
 * @param arr array of sudoku index.
 * @return bool return true if resolved otherwise false.
 */
bool is_solved(int arr[9][9]) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (arr[i][j] != solved[i][j]) return false;
        }
    }
    return true;
}

/**
 * clean white spaces from start and end of string.
 * @param str string for trim.
 * @return char* trimmed string.
 */
char *trim(char *str){
    char *end;

    // Trim leading space
    while(isspace((unsigned char)*str)) str++;

    if(*str == 0)  // All spaces?
        return str;

    // Trim trailing space
    end = str + strlen(str) - 1;
    while(end > str && isspace((unsigned char)*end)) end--;

    // Write new null terminator character
    end[1] = '\0';

    return str;
}

/**
 * init
 */
void init() {
    int i, j;
    int nums[3], k = K;
    int board[9][9];
    bool table_made = false, validNumbers = false;


    int bold_Watt = 15;
    while (1) {
        char user_input[10];
        validNumbers = false;
        printf("\nplease select:");
        printf("\n%s", (!table_made ? "play," : "new game,reset,solve,unsolve,help me,(i,j,number),"));
        printf("help,quit:");
        fgets(user_input, 10, stdin);

        for (i = 0; i < strlen(user_input) - 1; i++)
            user_input[i] = tolower(user_input[i]);
        strcpy(user_input , trim(user_input));

        if (user_input[1] == ',' && user_input[3] == ',') {//6,7,8
            validNumbers = true;
            for (int i = 0; i < 5; i += 2) {//i=0,2,4
                j = (int) (user_input[i] - '0');
                if (j < 10 && j > 0) {
                    nums[(i / 2)] = j;
                } else validNumbers = false;
            }
        }
        if ((!strcmp(user_input, "play") && !table_made) || (!strcmp(user_input, "new game") && table_made)) {
            do_null(def_board);
            do_null(board);
            do_null(solved);
            fillValues(k);
            table_made = true;
            memcpy(board, def_board, sizeof(board));
            clearScreen();
            print_sudoku(board);
        } else if (user_input[0] == 'k' && user_input[1] == '=' &&
                   (strlen(user_input) == 3 || strlen(user_input) == 4)) {
            //i = strtoint(user_input);
            i = 0;
            for (j = 2; j < strlen(user_input); j++)
                i = 10 * i + (int) (user_input[j] - '0');

            if (i < 81 && i != 0) {
                k = i;
                if (table_made) {
                    printf("\nNew setting save. reload...(%d)",i);
                    sleep(1);
                    do_null(def_board);
                    do_null(board);
                    do_null(solved);
                    fillValues(k);
                    table_made = true;
                    memcpy(board, def_board, sizeof(board));
                    clearScreen();
                    print_sudoku(board);
                } else printf("\nNew setting save.(%d)",i);
            } else printf("\nk must be less than 81.(%d)",i);
        } else if (validNumbers && table_made) {
            if (def_board[nums[0] - 1][nums[1] - 1] == 0) {//
                (board[nums[0] - 1][nums[1] - 1]) = nums[2];
                clearScreen();
                print_sudoku(board);
                if (complected(board)) {
                    if (is_solved(board)) {
                        if (color) MySetTextColor(160);//background:green , text:black.
                        printf("\a\namazing u solved sudoku.!!!\n");
                        if (color) MySetTextColor(def_wAtt);
                        do_null(def_board);
                        do_null(board);
                        do_null(solved);
                        table_made = false;
                    }
                }
            } else printf("u can't change this.(i=%d,j=%d,number=%d)", nums[0], nums[1],def_board[nums[0] - 1][nums[1] - 1]);
        } else if (!strcmp(user_input, "help me") && table_made) {
            clearScreen();
            print_sudoku(solved);
            for (i = 3; i > 0; i--) {
                printf("%d\r", i);
                sleep(1);
            }
            clearScreen();
            print_sudoku(board);
        } else if (!strcmp(user_input, "solve") && table_made) {
            clearScreen();
            print_sudoku(solved);
        } else if (!strcmp(user_input, "unsolve") && table_made) {
            clearScreen();
            print_sudoku(board);
        } else if (!strcmp(user_input, "reset") && table_made) {
            memcpy(board, def_board, sizeof(board));
            clearScreen();
            print_sudoku(board);
        } else if (!strcmp(user_input, "help")) {
            if (color) MySetTextColor(bold_Watt);//bold text
            printf("\nThis is the help menu. Available commands:\n\n");
            if (color) MySetTextColor(def_wAtt);//default
            printf("-set K (missing digits for make game) with: k=(number between 1 to 81) default:%d.\n", K);
            if (table_made) {
                if (color) MySetTextColor(bold_Watt);
                printf("-new game:");
                if (color) MySetTextColor(def_wAtt);//default
                printf("change sudoku table.\n");
                if (color) MySetTextColor(bold_Watt);//bold text
                printf("-reset: ");
                if (color) MySetTextColor(def_wAtt);//default
                printf("resets the board.\n");
                if (color) MySetTextColor(bold_Watt);//bold text
                printf("-solve: ");
                if (color) MySetTextColor(def_wAtt);//default
                printf("solves the entered sudoku problem.\n");
                if (color) MySetTextColor(bold_Watt);//bold text
                printf("-unsolve: ");
                if (color) MySetTextColor(def_wAtt);//default
                printf("unsolves the recently solved sudoku problem.\n");
                if (color) MySetTextColor(bold_Watt);//bold text
                printf("-help me: ");
                if (color) MySetTextColor(def_wAtt);//default
                printf("little help to solve,show solved sudoku for 3 second.\n");
                if (color) MySetTextColor(bold_Watt);//bold text
                printf("-Entering a number, then a comma, then another number, then another comma, then a final number - marks that square with the final number.ex(2,4,6)\n");
                if (color) MySetTextColor(def_wAtt);//default
            } else {
                if (color) MySetTextColor(bold_Watt);//bold text
                printf("-play: ");
                if (color) MySetTextColor(def_wAtt);//default
                printf("make sudoku.\n");
            }
            if (color) MySetTextColor(bold_Watt);//bold text
            printf("-quit: ");
            if (color) MySetTextColor(def_wAtt);//default
            printf("exit the program.\n");
        } else if (!strcmp(user_input, "quit")) {
            printf("thanks for ur time ;)");
            sleep(2);
            exit(1);
        } else printf("choose valid command.(%s)\n", user_input);
    }
}


int main() {
    srand(time(0));
    setupConsole();
    printf("made by D.a\n");
    init();
    return 1;
}

#include "print_sudoku.c"
