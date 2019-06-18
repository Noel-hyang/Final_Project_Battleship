// "**********************************************************\n";
//  " Programmed by: Hanran Yang\n";
//  " CS2          : MW: 10:45a - 12:10p, TTH: 10:45a - 12:50p\n";
//  " Final Project - Battleship \n";
//  "**********************************************************\n";
#include "header.h"

using namespace std;

/******************************************************************************
 *
 * Final Project - Battleship
 * ____________________________________________________________________________
 *  This program is a guessing game for two players
 *
 * It is played on ruled grids on which each player's fleet of ships are
 * marked. The locations of the fleets are concealed from the other player.
 * Players alternate turns calling "shots" at the other player's ships,
 * and the objective of the game is to destroy the opposing player's fleet.
 *
 * RULE:
 * Before play begins, each player secretly arranges their ships on their
 * primary grid. Each ship occupies a number of consecutive squares on the
 * grid, arranged either horizontally or vertically. The number of squares
 * for each ship is determined by the type of the ship. The ships cannot
 * overlap ( only one ship can occupy any given square in the grid).
 * The types and numbers of ships allowed are the same for each player.
 * (Wikipedia)
 * ____________________________________________________________________________
 * OUTPUT:
 * The game, including two board
 *
 * INPUT:
 * game_mod              //Input- game mod, 1(play), 0(end)
 *
 * ARRAY:
 * board                 //Array- board(0 is you, 1 is enemy)
 * hit_board_palyer1     //Array- Palyer1's attack record
 * hit_board_palyer2     //Array- Palyer2's attack record
 *
 * Processing:
 * game_status           //Processing- current game status
 * round                 //Processing- players round
******************************************************************************/

int main()
{
    PlayerBoard board[2];                   //Array- board(0 is you, 1 is enemy)
    char hit_board_palyer1[10][10];         //Array- Palyer1's attack record
    char hit_board_palyer2[10][10];         //Array- Palyer2's attack record

    int game_status;                        //Processing- current game status
    char game_mod;                          //Input- game mod
    int round;                              //Processing- players round

    game_status = 1;                        //Processing- 1(play), 0(end)
    round = 0;                              //0 is player1, 1 is player2          

    //initialize All cell to space
    clear_board(board[0]);
    clear_board(board[1]);
    clear_hit_board(hit_board_palyer1);
    clear_hit_board(hit_board_palyer2);

    //initialize name, size and hitcount.
    initFleet(board[0]);
    initFleet(board[1]);

    do{
        cout << "play against another player(P) or against the computer(C)?";
        cin >> game_mod;
        //Game mod, P is PVP, C is PVE
        if(game_mod == 'P')
        {
            cout << "\nYou will against another player(PVP)\n";
            //display Boards, let 2 user set ships
            initBoard(board[0] ,board[1]);
            //display a empty board
            displayBoards(board[0].a_board,board[1].a_board);

            //draw all ships back to the board
            draw_board_with_ship(board[0]);
            draw_board_with_ship(board[1]);
            //0 is player1, 1 is player2
            do{
                if(round == 0)
                {
                    cout << "Player 1:\n";
                    //attack_ship_info- get shot location from player
                    attack_ship_info(board[1], hit_board_palyer1);
                    //True when all ships hit point is zero
                    if(all_ships_sink(board[1]))
                    {
                        cout << "\nYou sunk the fleet!!! You win!!!\n";
                        game_status = 0;
                        cout << "\n Game result: \n";
                        cout << "\nPlayer2's board[left], Player2's hit board[right] ";
                        displayBoards(board[1].a_board,hit_board_palyer2);
                        cout << "\nPlayer1(Winer)'s board[left], Player1(Winer)'s hit board[right] ";
                    }
                    displayBoards(board[0].a_board,hit_board_palyer1);

                    round = 1;
                }
                else
                {
                    cout << "Player 2:\n";
                    //attack_ship_info- get shot location from player
                    attack_ship_info(board[0], hit_board_palyer2);
                    //True when all ships hit point is zero
                    if(all_ships_sink(board[0]))
                    {
                        cout << "\nYou sunk the fleet!!! You win!!!\n";
                        game_status = 0;
                        cout << "\n Game result: \n";
                        cout << "\nPlayer1's board[left], Player1's hit board[right] ";
                        displayBoards(board[0].a_board,hit_board_palyer1);
                        cout << "\nPlayer2(Winer)'s board[left], Player2(Winer)'s hit board[right] ";
                    }
                    displayBoards(board[1].a_board,hit_board_palyer2);

                    round = 0;
                }
            }while(game_status == 1);


        }
        else if(game_mod == 'C')
        {
            cout << "\nYou will against the computer(PVE)\n";
            //display Boards, let user set ships, AI will automate set ship
            PVE_initBoard(board[0] ,board[1]);

            //draw all ships back to the board
            draw_board_with_ship(board[0]);
            draw_board_with_ship(board[1]);

            do{
                if(round == 0)
                {
                    cout << "\nPlayer:\n";
                    //attack_ship_info- get shot location from player
                    attack_ship_info(board[1], hit_board_palyer1);
                    //True when all ships hit point is zero
                    if(all_ships_sink(board[1]))
                    {
                        cout << "\nPlayer sunk the fleet!!! You win!!!\n";
                        game_status = 0;
                        cout << "\n Game result: \n";
                        cout << "\nComputer's board[left], Computer's hit board[right] ";
                        displayBoards(board[1].a_board,hit_board_palyer2);
                        cout << "\nPlayer(Winer)'s board[left], Player(Winer)'s hit board[right] ";
                    }
                    displayBoards(board[0].a_board,hit_board_palyer1);

                    round = 1;
                }
                else
                {
                    cout << "Computer:\n";
                    //AI_attack_ship_info- get shot location from AI
                    AI_attack_ship_info(board[0], hit_board_palyer2);
                    //True when all ships hit point is zero
                    if(all_ships_sink(board[0]))
                    {
                        cout << "\nComputer sunk the fleet!!! Computer win!!!\n";
                        game_status = 0;
                        cout << "\n Game result: \n";
                        cout << "\nPlayer's board[left], Player's hit board[right] ";
                        displayBoards(board[0].a_board,hit_board_palyer1);
                        cout << "\nComputer(Winer)'s board[left], Computer(Winer)'s hit board[right] ";
                    }
                    displayBoards(board[1].a_board,hit_board_palyer2);

                    round = 0;
                }
            }while(game_status == 1);
        }
        else
        {
            cout << "\nError: invalid game mod";
        }
    }while(game_mod != 'P' && game_mod != 'C');

    return 0;
}




