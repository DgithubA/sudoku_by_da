//
// Created by DANA on 1/1/2023.
//



#define N 9 // row and col
#define SRN 3 // square and row


/**
 * check to num unused in box SRN*SRN when row start with rowStart and column with colStart.
 * @param rowStart start of box row.
 * @param colStart start of box column.
 * @param num number to search in box.
 * @return bool return true if is unused otherwise false.
 */
bool unUsedInBox(int rowStart, int colStart, int num) {
    for (int i = 0; i < SRN; i++)
        for (int j = 0; j < SRN; j++)
            if (def_board[rowStart + i][colStart + j] == num)
                return false;

    return true;
}

/**
 * generate random Number From 1 To `num`.
 * @param num maximum of generate random number.
 * @return int generated number.
 */
int randomGenerator(int num) {

    return (int) ( rand() % num ) + 1;//اینطوری همیشه یک عدد کوچک تر از num رو میده و برای اینکه 0 نشه و خود 9 رو هم داشته باشیم +1 داره
}

/**
 * check number `num` existence in row `i`.
 * @param i column.
 * @param num number for existence.
 * @return bool If there is a number return false otherwise true.
 */
bool unUsedInRow(int i, int num) {
    for (int j = 0; j < N; j++)
        if (def_board[i][j] == num)
            return false;
    return true;
}

/**
 * check number `num` existence in row `j`.
 * @param j row.
 * @param num number for existence.
 * @return bool If there is a number return false otherwise true.
 */
bool unUsedInCol(int j, int num) {
    for (int i = 0; i < N; i++)
        if (def_board[i][j] == num)
            return false;
    return true;
}

/**
 * Checks that the number `num` in position row `i` and column `j` follows Sudoku rules(don't break it).
 * @param i row to check.
 * @param j column to check.
 * @param num number ro check.
 * @return bool If it follows the rules return true otherwise false.
 */
bool CheckIfSafe(int i, int j, int num) {
    return (unUsedInRow(i, num) &&
            unUsedInCol(j, num) &&
            unUsedInBox(i - i % SRN, j - j % SRN, num));
}

/**
 * fill Box SRN*SRN with row `row` and column `col`.
 * @param row Box row.
 * @param col Box column.
 */
void fillBox(int row, int col) {//0,3,6
    int num;
    for (int i = 0; i < SRN; i++) {
        for (int j = 0; j < SRN; j++) {
            do {
                num = randomGenerator(N);
            }while (!unUsedInBox(row, col, num));//تا زمانی که یک عدد پیدا نکنه که در باکس نیس حلقه تکرار میشه.

            def_board[row + i][col + j] = num;
        }
    }
}

/**
 * Fill the diagonal of SRN x SRN matrices.
 */
void fillDiagonal() {
    for (int i = 0; i < N; i = i + SRN)
        fillBox(i, i);//SRN = 3 , N = 9 => i = 0 , 3 , 6
}

/**
 * fill Remaining of element and check is valid by sudoku rules.
 * @param i
 * @param j
 * @return bool true when all element is valid.
 */
bool fillRemaining(int i, int j) {//0,3 - 0,4
    //وقتی j = 9 میشه و i کوچکتر از 8 هس به i ی دونه اضاف میشه و j = 0 میشه
    if (j >= N && i < N - 1) {//false - false
        i++;;
        j = 0;
    }
    //وقتی به  i = 9 , j = 9 میرسیم دیگه ادامه نمیدیم. این آخرین مرحله هس.
    if (i >= N && j >= N)//false - false
        return true;

    if (i < SRN) {//true:i=0,1,2
        if (j < SRN)//true:j=0,1,2
            j = SRN;
    } else if (i < N - SRN) {//true:i=3,4,5
        if (j == ((int)(i / SRN)) * SRN) // true when j = 0 => i = 0,1,2 , j = 3 => i = 3,4,5 , j=6 => i=6,7,8
            j = j + SRN;//when j = 3 , i = 3,4,5 => j=6
    } else {//when i = 6,7,8
        if (j == N - SRN) {//j = 6
            i++; //when i = 6,7,8 , j = 6
            j = 0;
            if (i >= N) //true:i = 9 , j = 6
                return true;
        }
    }
    //i = 0,j = 3 - i = 0,j = 4 -
    for (int num = 1; num <= N; num++) {//1,2,3,...,9
        if (CheckIfSafe(i, j, num)) {
            def_board[i][j] = num;
            if (fillRemaining(i, j + 1))
                return true;

            def_board[i][j] = 0;
        }
    }
    return false;
}

/**
 * remove `k` index from sudoku table for solve.
 * @param k int count number to remove from table.
 */
void removeKDigits(int k) {
    int count = k;
    while (count != 0) {
        int cellId = randomGenerator(N * N);//between:1-81 ex:45,38,17

        int i = (cellId / N);//between:0-9 ex:5,4,1
        int j = cellId % 9;//between:0-9 ex:0,2,8
        if (j != 0) j--;

        if (def_board[i][j] != 0) {
            count--;
            def_board[i][j] = 0;
        }
    }
}


void fillValues(int k) {
    fillDiagonal();

    fillRemaining(0, SRN);
    memcpy(solved,def_board,sizeof(solved));
    // Remove Randomly K digits to make game
    removeKDigits(k);
}
