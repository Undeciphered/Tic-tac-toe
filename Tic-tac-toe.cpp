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
        
        bool take_or_win(char to_complete) {
            for(int i = 0; i < 3; i++) {
                if(((board[0][i] == to_complete) + (board[1][i] == to_complete) + (board[2][i] == to_complete)) == 2) {
                    for(int j = 0; j < 3; j++) {
                        if(board[j][i] == ' ') {
                            board[j][i] = 'X';
                            return true;
                        }
                    }
                }
                if(((board[i][0] == to_complete) + (board[i][1] == to_complete) + (board[i][2] == to_complete)) == 2) {
                    for(int j = 0; j < 3; j++) {
                        if(board[i][j] == ' ') {
                            board[i][j] = 'X';
                            return true;
                        }
                    }
                }  
            }
            if(((board[0][0] == to_complete) + (board[1][1] == to_complete) + (board[2][2] == to_complete)) == 2) {
                for(int i = 0, j = 0; i < 3; i++,j++) {
                    if(board[i][j] == ' ') {
                        board[i][j] = 'X';
                        return true;
                    }
                }
            }
            if(((board[0][2] == to_complete) + (board[1][1] == to_complete) + (board[2][0] == to_complete)) == 2) {
                for(int i = 0, j = 2; i < 3; i++,j--) {
                    if(board[i][j] == ' ') {
                        board[i][j] = 'X';
                        return true;
                    }
                }
            } 
            return false;
        }
        
        void educated_move() {
            if(take_or_win('X')) {return;}
            if(take_or_win('O')) {return;}
            if(board[1][1] == ' ') {
                board[1][1] = 'X';
                return;
            }
            std::uniform_int_distribution<int> random(0, 3);
            std::vector<std::pair<int, int>> corners = {{0,0}, {0,2}, {2,2}, {2,0}};
            while(true) {
                int temp{random(g)};
                if(board[corners[temp].first][corners[temp].second] == ' ') {
                    board[corners[temp].first][corners[temp].second] = 'X';
                    return;
                }
            }
            std::vector<std::pair<int, int>> edges = {{0,1}, {1,2}, {2,1}, {1,0}};
            while(true) {
                int temp{random(g)};
                if(board[corners[temp].first][corners[temp].second] == ' ') {
                    board[corners[temp].first][corners[temp].second] = 'X';
                    return;
                }
            }
            
        }
        
        void player_turn(char player) {
            int row{0}, column{0};
            while(true) {
                std::cin >> row >> column;
                std::cout << '\n';
                if(board[row][column] == ' ') {
                    board[row][column] = player;
                    return;
                }
            }
        }
        
        void print_board() {
            bool first_row{true};
            for(int i = 0; i < 3; i++) {
                if(!first_row) {std::cout << "-----\n";}
                bool first{true};
                for(int j = 0; j < 3; j++) {
                    if(!first) {std::cout << '|';}
                    std::cout << board[i][j];
                    first = false;
                }        
                std::cout << '\n';
                first_row = false;
            }
            std::cout << '\n';
        }
                
        void start() {
            int choice{0};
            std::cout << "1.ai-imposible\n2.ai-medium\n3.ai-random\n4.player\nchose your oponent: "; 
            std::cin >> choice;
            while(true) {
                print_board();
                if(check_winner() == 'X') {std::cout << "X wins!"; return;}
                if(is_draw()) {std::cout << "its a draw!"; return;}
                player_turn('O');
                print_board();
                if(check_winner() == 'O') {std::cout << "O wins!"; return;}
                if(is_draw()) {std::cout << "its a draw!"; return;}
                if(choice == 1) {minimax_best_move();}
                else if(choice == 2) {educated_move();}
                else if(choice == 3) {random_move();}
                else if(choice == 4) {player_turn('X');}
            }
        }
};

int main() {
    tic_tac_toe mygame;
    mygame.start();
}
