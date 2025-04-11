#include <iostream>
#include <array>

char check_winner(char board[3][3]) {
    for(int i = 0; i < 3; i++){
        if(board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
            return board[i][0];   
        }
        if(board[0][i] == board[1][i] && board[1][i] == board[2][i]) {
            return board[0][i];   
        } 
    }
    if(board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        return board[0][0];   
    }
    if(board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        return board[0][2];   
    } 
    return ' ';
}  

bool is_draw(char board[3][3]) {
    for(int i = 0; i < 3; i++) {
        for(int j = 0; i < 3; j++) {
            if(board[i][j] == ' ') {
                return false;  
            }
        }
    }
    if(check_winner(board) == ' ') {
        return true;
    } else {
        return false;
    }
}

int main() {
    char board[3][3] = {
    { ' ', ' ', ' ' },
    { ' ', ' ', ' ' },
    { ' ', ' ', ' ' }};

    return 0;
}
