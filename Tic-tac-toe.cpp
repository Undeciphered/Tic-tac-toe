#include <iostream>
#include <array>
#include <random>

class tic_tac_toe {
    private:
        char board[3][3];
        std::random_device rd;
        std::mt19937 g;
        
    public:
        tic_tac_toe() : g(rd()) {
            for(auto& row : board) {
                for(char& cell : row) {
                    cell = ' ';
                }
            }
        }
        
        char check_winner() {
            for(int i = 0; i < 3; i++){
                if(board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][2] != ' ') {
                    return board[i][0];   
                }
                if(board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[2][i] != ' ') {
                    return board[0][i];   
                } 
            }
            if(board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[2][2] != ' ') {
                return board[0][0];   
            }
            if(board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[2][0] != ' ') {
                return board[0][2];   
            } 
            return ' ';
        }
        
        bool is_draw() {
            for(int i = 0; i < 3; i++) {
                for(int j = 0; j < 3; j++) {
                    if(board[i][j] == ' ') {
                        return false;  
                    }
                }
            }
            if(check_winner() == ' ') {
                return true;
            } else {
                return false;
            }
            return true;
        }
        
        int minimax(bool ismaximizing) {
            char winner = check_winner();
            if(winner == 'X') {return +1;}
            if(winner == 'O') {return -1;}
            if(is_draw()) {return 0;}
            
            if(ismaximizing) {
                int best_score{-1748};
                for(int i = 0; i < 3; i++) {
                    for(int j = 0; j < 3; j++) {
                        if(board[i][j] == ' ') {
                            board[i][j] = 'X';
                            int score{minimax(false)};
                            board[i][j] = ' ';
                            best_score = std::max(best_score, score);
                        }
                    }
                }
                return best_score;
            } else {
                int best_score{1748};
                for(int i = 0; i < 3; i++) {
                    for(int j = 0; j < 3; j++) {
                        if(board[i][j] == ' ') {
                            board[i][j] = 'O';
                            int score{minimax(true)};
                            board[i][j] = ' ';
                            best_score = std::min(best_score, score);
                        }
                    }
                }
                return best_score;  
            }
        }
        
        void minimax_best_move() {
            int best_row{-1}, best_column{-1};
            int best_score{-1748};
            for(int i = 0; i < 3; i++) {
                for(int j = 0; j < 3; j++) {
                    if(board[i][j] == ' ') {
                        board[i][j] = 'X';
                        int score{minimax(false)};
                        board[i][j] = ' ';
                        if(score > best_score) {
                            best_score = score;
                            best_row = i;
                            best_column = j;
                        }
                        }
                }
            }
            if(best_row != -1 && best_column != -1) {
                board[best_row][best_column] = 'X';
            }
        }

        void random_move() {
            std::vector<char*> valid_cells;
            for(auto& row : board) {
                for(char& cell : row) {
                    if(cell == ' ') {
                        valid_cells.push_back(&cell);
                    }
                }
            }
            std::uniform_int_distribution<int> random(0, static_cast<int>(valid_cells.size()-1));
            *valid_cells[random(g)] = 'X';
        }
        
        void print_board() {
            for(int i = 0; i < 3; i++) {
                for(int j = 0; j < 3; j++) {
                   std::cout << board[i][j] << ' ';
                }        
                std::cout << '\n';
            }
        }
                
        void start() {
            while(true) {
                int row{0}, column{0};
                minimax_best_move();
                print_board();
                if(check_winner() == 'X') {
                std::cout << "X won";
                break;
                } else if(is_draw()) {
                    std::cout << "its a tie";
                    break;
                }
                std::cin >> row >> column;
                std::cout << '\n';
                board[row][column] = 'O';
            }       
        }
};

int main() {
    tic_tac_toe mygame;
    mygame.start();
}
