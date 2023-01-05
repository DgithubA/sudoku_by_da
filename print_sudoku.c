//
// Created by DANA on 1/1/2023.
//

void print_sudoku(int board[9][9]) {
    HANDLE  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    char hr[] = "  +---+---+---+---+---+---+---+---+---+";
    SetConsoleTextAttribute(hConsole, dif_color);
    printf("    1   2   3   4   5   6   7   8   9");
    SetConsoleTextAttribute(hConsole, def_wAtt);
    for (int i = 0; i < 9; i++) {
        if((i % 3) == 0) {
            SetConsoleTextAttribute(hConsole, dif_color);
            printf("\n%s\n",hr);
            SetConsoleTextAttribute(hConsole, def_wAtt);
        }else printf("\n%s\n",hr);
        SetConsoleTextAttribute(hConsole, dif_color);
        printf("%d ",i+1);
        SetConsoleTextAttribute(hConsole, def_wAtt);
        for (int j = 0; j < 9; j++) {
            if((j % 3) == 0){
                SetConsoleTextAttribute(hConsole, dif_color);
                printf("|");
                SetConsoleTextAttribute(hConsole, def_wAtt);
            }else printf("|");
            if(board[i][j] != 0){
                if(def_board[i][j] == 0) {//پیشفرض خالیه
                    int prv = board[i][j];
                    board[i][j] = 0;
                    if(!is_valid_input(board , i , j,prv)){
                        SetConsoleTextAttribute(hConsole, 12);//red
                    }else {
                        SetConsoleTextAttribute(hConsole, 5);//purple
                    }
                    board[i][j] = prv;
                    printf(" %d ", board[i][j]);
                    SetConsoleTextAttribute(hConsole, def_wAtt);
                }else printf(" %d ", board[i][j]);
            }else printf("   ");
        }
        SetConsoleTextAttribute(hConsole, dif_color);
        printf("|");
        SetConsoleTextAttribute(hConsole, def_wAtt);
    }
    SetConsoleTextAttribute(hConsole, dif_color);
    printf("\n%s\n",hr);
    SetConsoleTextAttribute(hConsole, def_wAtt);
}