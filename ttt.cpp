#include <iostream>
#include <string>
using namespace std;

char square[10] = {'o','1','2','3','4','5','6','7','8','9'};
int used_square[10]; //0 for unused , 1 for used


int checkwin();
void print_board();
void mark_square(int choice, char mark);
int& get_choice(int& num_players, const int& player, int& choice);
void start_game(int& num_players);


int main()
{
    
    // prompts users to choose one-player or two-player game
    int num_players = 0;
    start_game(num_players);
    
    // print information to let users know they can exit by entering Q and restart by entering N

    std::cout << "If you wish to quit at any time you can enter 'Q' for your move. If you wish to restart your game you can enter 'N' for your move.";

    int player = -1; // player = 1 or -1
    int if_win;
    int choice; // player's move
    char mark;
    do
    {
        print_board();
        choice = get_choice(num_players,player,choice);
        
        
        // select player's mark symbol
        if (player == -1)
            mark = 'X';
        else if (player == 1)
            mark = 'O';


        // update square array according to player's move
        mark_square(choice, mark);


        // check if game stops
        if_win=checkwin();


        // change to next player's move
        player *= -1;

    } while(if_win==-1);

    print_board();
    if (if_win==1)
        cout<< "\nPlayer " << (-player+3)/2 << " win.\n ";
    else
        cout<< "\nTie Game.\n";

    return 0;
}

/*********************************************
    FUNCTION TO RETURN GAME STATUS
    1 FOR GAME IS OVER WITH RESULT
    -1 FOR GAME IS IN PROGRESS
    O GAME IS OVER AND NO RESULT
**********************************************/

int checkwin()
{
    if (square[1] == square[2] && square[2] == square[3])
        return 1;
    else if (square[4] == square[5] && square[5] == square[6])
        return 1;
    else if (square[7] == square[8] && square[8] == square[9])
        return 1;
    else if (square[1] == square[4] && square[4] == square[7])
        return 1;
    else if (square[2] == square[5] && square[5] == square[8])
        return 1;
    else if (square[3] == square[6] && square[6] == square[9])
        return 1;
    else if (square[1] == square[5] && square[5] == square[9])
        return 1;
    else if (square[3] == square[5] && square[5] == square[7])
        return 1;
    // the board is full
    else if (   square[1] != '1' && square[2] != '2' && square[3] != '3'
             && square[4] != '4' && square[5] != '5' && square[6] != '6'
             && square[7] != '7' && square[8] != '8' && square[9] != '9')
        return 0; // tie situation
    else
        return -1; // game in progress
}


/*******************************************************************
     FUNCTION TO DRAW BOARD OF TIC TAC TOE WITH PLAYER MARKS
********************************************************************/
void print_board()
{
    cout << "\n \t Tic Tac Toe \n";
    cout << "Player 1 (X)  -  Player 2 (O)" << endl << endl;

    cout << "     |     |     " << endl;
    cout << "  " << square[1] << "  |  " << square[2] << "  |  " << square[3] << endl;

    cout << "_____|_____|_____" << endl;
    cout << "     |     |     " << endl;

    cout << "  " << square[4] << "  |  " << square[5] << "  |  " << square[6] << endl;

    cout << "_____|_____|_____" << endl;
    cout << "     |     |     " << endl;

    cout << "  " << square[7] << "  |  " << square[8] << "  |  " << square[9] << endl;

    cout << "     |     |     " << endl << endl;
}

// update the square array accoring to player's move
void mark_square(int choice, char mark)
{
    // if choice = 1, c = '1', ...
    char c = '0'+choice;
    square[choice] = mark;
    used_square[choice] = 1;
}



void end_or_restart(int& num_players,bool end = false, bool restart = false){
    if(end == true){
        std::cout << "Game terminated by user! Play again soon!\n";
        exit(1);
    }else if(restart == true){
        std :: cout << "Game restarting!\n";
        square[0] = 'o';
        for(int i = 1; i < 10; i++){
            square[i] = '0' + i;
        }
        for(auto i:used_square){
            i = 0;
        }
        start_game(num_players);
        print_board();
    }else{
        return;
    }
}

void start_game(int& num_players){
    try{
        std::cout << "Do you want to play a 1-player or 2-player game? Please enter 1 or 2.\n";
        string input;
        getline(cin, input, '\n');
        
        
        if(input == "Q"){
            end_or_restart(num_players,true,false);
        }
        if(input == "N"){
            end_or_restart(num_players,false,true);
        }
        if(input != "1" && input != "2"){
            logic_error description("Illegal move! Only 1 or 2 accepted.");
            throw(description);
        }
        
        num_players = stoi(input);
    }catch(logic_error& e){
        std::cout << e.what() << std::endl;
        string input = "";
        while(true){
            if(input != "1" && input != "2"){
                std::cout << "Please enter 1 or 2.\n";
                getline(cin, input, '\n');
            }else{
                num_players = stoi(input);
                break;
            }
        }
    }
}



int& get_choice(int& num_players, const int& player, int& choice){
    
    if(num_players == 2){
        try{
            logic_error description("Illegal move! Only 1-9,N, or Q allowed for input!");
            
            string input;
            cout << "Player " << (player+3)/2 << ", enter a number:  ";
            getline(cin,input,'\n');
            if(used_square[stoi(input)] == 1){
                std::cout << "Illegal Move! Please select an unselected square!";
                throw(description);
            }
            else if(input == "Q"){
                end_or_restart(num_players,true,false);
            }else if(input == "N"){
                end_or_restart(num_players,false,true);
            }else if(input != "1" && input != "2" && input != "3"
                     && input != "4" && input != "5" && input != "6"
                     && input != "7" && input != "8" && input != "9"){
                throw(description);
            }
            choice = stoi(input);
            return choice;
        }catch(logic_error& e){
            std::cout << e.what() << std::endl << "Please enter a valid input:";
            string input;
            getline(cin,input,'\n');
            while(input != "1" && input != "2" && input != "3"
                  && input != "4" && input != "5" && input != "6"
                  && input != "7" && input != "8" && input != "9"
                  && used_square[stoi(input)] == 1){
                std::cout << "Enter a valid input: ";
                std::cout << std::endl;
                getline(cin,input,'\n');
                if(used_square[stoi(input)] == 1){
                    std::cout << "Please select an unused square.";
                }
                if(input == "Q"){
                    end_or_restart(num_players,true,false);
                }
                if(input == "N"){
                    end_or_restart(num_players,false,true);
                }
            }
            
            choice = stoi(input);
            return choice;
        }
    }else{
        if(player == -1){
            try{
                logic_error description("Illegal move!");
                
                
                string input;
                cout << "Player " << (player+3)/2 << ", enter a number: ";
                getline(cin,input,'\n');
                
                if(used_square[stoi(input)] == 1){
                    std::cout << "Please select an unselected square!\n";
                    throw(description);
                }
                else if(input == "Q"){
                    end_or_restart(num_players,true,false);
                }else if(input == "N"){
                    end_or_restart(num_players,false,true);
                }else if(input != "1" && input != "2" && input != "3"
                         && input != "4" && input != "5" && input != "6"
                         && input != "7" && input != "8" && input != "9"){
                    throw(description);
                }
                choice = stoi(input);
                return choice;
            }catch(logic_error& e){
                std::cout << e.what() << std::endl << "Please enter a valid input:";
                string input;
                getline(cin,input,'\n');
                while(input != "1" && input != "2" && input != "3"
                      && input != "4" && input != "5" && input != "6"
                      && input != "7" && input != "8" && input != "9"
                      && used_square[stoi(input)] == 1){
                    std::cout << "Enter a valid input (1-9,Q,N): ";
                    std::cout << std::endl;
                    getline(cin,input,'\n');
                    if(used_square[stoi(input)] == 1){
                        std::cout << "Please select an unused square.";
                    }
                    if(input == "Q"){
                        end_or_restart(num_players,true,false);
                    }
                    if(input == "N"){
                        end_or_restart(num_players,false,true);
                    }
                }
                choice = stoi(input);
                return choice;
            }
                
        }else{
            while(true){
                choice = (rand() % 9) + 1;
                if(used_square[choice]==0)
                    break;
                
            }
        }

        return choice;
    }
}
