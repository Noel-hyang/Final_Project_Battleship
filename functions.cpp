#include <iostream>
#include <iomanip>
#include <vector>
#include "header.h"
using namespace std;

/****************************************************************
 * displayBoards
 * This function will display Boards
 *
 * returns - none
 *_________________________________________________________
 * PRE-CONDITIONS
 *  The following need previously defined values:
 *      your[][10]     //IN- your board
 *      enemy[][10]    //IN- enemy board
 ****************************************************************/
void displayBoards(char your[][10],     //IN- your board
                   char enemy[][10])    //IN- enemy board
{

    cout << endl << endl;
    cout << setw(28) << "Your Board";
    cout << setw(54) << "Enemy Board\n";

    //Your
    cout << setw(5) << '1';
    for(int i = 1; i < 10; i++)
    {
        cout << setw(4) << i + 1;
    }

    //Enemy
    cout << setw(17) << '1';
    for(int i = 1; i < 10; i++)
    {
        cout << setw(4) << i + 1;
    }

    cout << endl;
    cout << "  -----------------------------------------";
    cout << "            -----------------------------------------\n";

    for(int row = 0; row < 10; row++)
    {
        //Your
        cout << static_cast<char>('A' + row) << " | ";
        for(int col = 0; col < 10; col++)
        {
            cout << your[row][col] << " | ";
        }

        //Enemy
        cout << setw(10) << static_cast<char>('A' + row) << " | ";
        for(int col = 0; col < 10; col++)
        {
            cout << enemy[row][col] << " | ";
        }
        cout << endl;

        cout << "  -----------------------------------------";
        cout << "            -----------------------------------------\n";

    }

}

/****************************************************************
 * setShip
 * This function will let palyer set ship
 * The setShip function calls the getValidShipInfo function to
 * determine which spots on the board the ship will occupy.
 *
 * returns - none
 * _________________________________________________________
 * PRE-CONDITIONS
 *  The following need previously defined values:
 *      p_board           //IN&OUT- player's board
 *      ship_index        //IN- ship index
 *
 * POST-CONDITIONS
 *      p_board           //IN&OUT- player's board
 * _________________________________________________________
 * Processing:
 * temp_row               //Processing- temporary row
 * temp_col;              //Processing- temporary col
 * temp_orientation       //Processing- temporary orientation
 ****************************************************************/
void setShip(PlayerBoard &p_board,      //IN&OUT- player's board
             int ship_index)            //IN- ship index
{
    int temp_row;               //Processing- temporary row
    int temp_col;               //Processing- temporary col
    char temp_orientation;      //Processing- temporary orientation

    //Initialization
    temp_row = 0;
    temp_col = 0;

    //get ship info from user
    getValidShipInfo(temp_row, temp_col, temp_orientation, p_board, ship_index);
    //store orientation to ship
    p_board.ship_status[ship_index].orientation = temp_orientation;

    //set ship horizontal to the board
    if(temp_orientation == 'h')
    {
        for(int i = 0; i < p_board.ship_status[ship_index].size; i++)
        {
            p_board.a_board[temp_row][temp_col + i] = 's';
            p_board.ship_status[ship_index].ship_occupies.push_back({temp_row, temp_col + i});
        }
    }
    //set ship vertical to the board
    else
    {
        for(int i = 0; i < p_board.ship_status[ship_index].size; i++)
        {
            p_board.a_board[temp_row + i][temp_col] = 's';
            p_board.ship_status[ship_index].ship_occupies.push_back({temp_row + i, temp_col});
        }
    }

}

/****************************************************************
 * getValidShipInfo
 * This function will prompt the user for the starting row and column
 * coordinates of the ship which the user will enter as: letter
 * number. The function will also call the function spaceOccupied to
 * determine if any of the spaces the ship would take up if
 * placed on the board are currently occupied.
 *
 * returns - none
 * _________________________________________________________
 * PRE-CONDITIONS
 *  The following need previously defined values:
 *      row           //IN&OUT row
 *      col           //IN&OUT- col
 *      orientation   //IN&OUT- orientation
 *      p_board       //IN&OUT- player's board
 *      ship_index    //IN- ship index
 *
 * POST-CONDITIONS
 *      row           //IN&OUT row
 *      col           //IN&OUT- col
 *      orientation   //IN&OUT- orientation
 *      p_board       //IN&OUT- player's board
 * _________________________________________________________
 * Processing:
 * ship_size          //Processing- ship size
 * conversion_row     //Processing- row that need to convert to int
 * is_valid           //Processing- check all input is valid
 * valid_input        //Processing- check row and col is valid
 * valid_input2       //Processing- check orientation is valid
 ****************************************************************/
void getValidShipInfo(int &row,             //IN&OUT row
                      int &col,             //IN&OUT- col
                      char &orientation,    //IN&OUT- orientation
                      PlayerBoard &p_board, //IN&OUT- player's board
                      int ship_index)       //IN- ship index
{
    int ship_size;          //Processing- ship size
    char conversion_row;    //Processing- row that need to convert to int
    int is_valid;           //Processing- check all input is valid
    int valid_input;        //Processing- check row and col is valid
    int valid_input2;       //Processing- check orientation is valid

    //Initialization
    is_valid = 0;
    valid_input = 1;
    valid_input2 = 1;

    //set ship size
    ship_size = p_board.ship_status[ship_index].size;

    do{
        is_valid = 0;
        valid_input = 1;

        cout << "Enter the starting coordinates of your ";
        cout << p_board.ship_status[ship_index].name << ": ";
        cin >> conversion_row >> col;
        //conversion: row
        row = static_cast<int>(conversion_row - 'A');
        col--;

        if((row >= 0) && (row <= 9) && (col >= 0) && (col <= 9))
        {
            do{
                valid_input2 = 1;

                cout << "\nEnter the orientation of your ";
                cout << p_board.ship_status[ship_index].name;
                cout << " (horizontal(h) or vertical(v)): ";
                cin >> orientation;

                if(orientation != 'h' && orientation != 'v')
                {
                    cout << "\nError: invalid ship orientation.\n";
                    valid_input2 = 0;
                }

            }while(valid_input2 == 0);
        }
        else
        {
            cout << "\nError: invalid ship placement.\n";
            valid_input = 0;
        }
        //check out of board
        //check row
        if(orientation == 'h' && valid_input == 1)
        {
            if((col + ship_size) > 10)
            {
                cout << "\nError: Ship placement is outside the board.\n";
                valid_input = 0;
            }

        }
        //check col
        else if(orientation == 'v' && valid_input == 1)
        {
            if((row + ship_size) > 10)
            {
                cout << "\nError: Ship placement is outside the board.\n";
                valid_input = 0;
            }
        }
        //Call spaceOccupied to check
        if(valid_input == 1 && !(spaceOccupied(p_board, row, col, orientation,
                                               ship_size)))
        {
            is_valid = 1;
        }

    }while(is_valid == 0);
}

/****************************************************************
 * spaceOccupied
 * This function will returns true if the placement of the ship
 * would overlap an already existing ship placement or false if
 * the space is not occupied.
 *
 * returns - returns true if the placement of the ship
 * would overlap an already existing ship placement
 *  false if the space is not occupied.
 * _________________________________________________________
 * PRE-CONDITIONS
 *  The following need previously defined values:
 *      p_board             //IN&OUT- player's board
 *      row                 //IN- row
 *      col                 //IN- col
 *      orientation         //IN- orientation
 *      size                //IN- size of ship
 * POST-CONDITIONS
 *      p_board             //IN&OUT- player's board
 * _________________________________________________________
 ****************************************************************/
bool spaceOccupied(PlayerBoard &p_board,    //IN&OUT- player's board
                   int row,                 //IN- row
                   int col,                 //IN- col
                   char orientation,        //IN- orientation
                   int size)                //IN- size of ship
{
    //Check row
    if(orientation == 'h')
    {
        for(int i = 0; i < size; i++)
        {
            if(p_board.a_board[row][col + i] != ' ')
            {
                cout << "\nError: Space already occupied.\n";
                return true;
            }
        }
    }
    //Check col
    else
    {
        for(int i = 0; i < size; i++)
        {
            if(p_board.a_board[row + i][col] != ' ')
            {
                cout << "\nError: Space already occupied.\n";
                return true;
            }
        }
    }

    return false;
}

/****************************************************************
 * initBoard
 * This function will calls the setShip function for each ship
 * in the fleet.  After each ship is placed on the board the
 * boards should be displayed.
 *
 * returns - none
 * _________________________________________________________
 * PRE-CONDITIONS
 *  The following need previously defined values:
 *      your           //IN&OUT- your board
 *      enemy          //IN&OUT- enemy's board
 *
 * POST-CONDITIONS
 *      your           //IN&OUT- your board
 *      enemy          //IN&OUT- enemy's board
 * _________________________________________________________
 ****************************************************************/
void initBoard(PlayerBoard &your,           //IN&OUT- your board
               PlayerBoard &enemy)          //IN&OUT- enemy's board
{
    cout << "Player 1 set your board.";
    displayBoards(your.a_board, enemy.a_board);

    for(int i = 0; i < 5; i++)
    {
        //set your ship
        setShip(your, i);
        displayBoards(your.a_board, enemy.a_board);
    }
    clear_board(your);

    cout << "\n\nPlayer 2 set your board.\n";
    for(int i = 0; i < 5; i++)
    {
        //set enemy ship
        setShip(enemy, i);
        displayBoards(enemy.a_board, your.a_board);
    }
    clear_board(enemy);
}

/****************************************************************
 * initFleet
 * This function will initializes all the ships in the fleet
 * with the appropriate information.
 *
 * returns - none
 * _________________________________________________________
 * PRE-CONDITIONS
 *  The following need previously defined values:
 *      p_board      //IN&OUT- player's board
 *
 * POST-CONDITIONS
 *      p_board      //IN&OUT- player's board
 * _________________________________________________________
 ****************************************************************/
void initFleet(PlayerBoard &p_board)       //IN&OUT- player's board
{
    //Carrier
    p_board.ship_status[0].name = "Carrier";
    p_board.ship_status[0].size = Carrier;
    p_board.ship_status[0].hitcount = Carrier;
    //Battleship
    p_board.ship_status[1].name = "Battleship";
    p_board.ship_status[1].size = Battleship;
    p_board.ship_status[1].hitcount = Battleship;
    //Cruiser
    p_board.ship_status[2].name = "Cruiser";
    p_board.ship_status[2].size = Cruiser;
    p_board.ship_status[2].hitcount = Cruiser;
    //Submarine
    p_board.ship_status[3].name = "Submarine";
    p_board.ship_status[3].size = Submarine;
    p_board.ship_status[3].hitcount = Submarine;
    //Destroyer
    p_board.ship_status[4].name = "Destroyer";
    p_board.ship_status[4].size = Destroyer;
    p_board.ship_status[4].hitcount = Destroyer;
}

/****************************************************************
 * clear_board
 * This function will clear the all cell to ' '
 *
 * returns - None
 * _________________________________________________________
 * PRE-CONDITIONS
 *  The following need previously defined values:
 *      p_board      //IN&OUT- player's board
 *
 * POST-CONDITIONS
 *      p_board      //IN&OUT- player's board
 * _________________________________________________________
 ****************************************************************/
void clear_board(PlayerBoard &p_board)     //IN&OUT- Player's board
{
    for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 10; j++)
        {
            p_board.a_board [i][j] = ' ';
        }
    }
}

/****************************************************************
 * clear_hit_board
 * This function will clear the all hit_board's cell to ' '
 *
 * returns - None
 * _________________________________________________________
 * PRE-CONDITIONS
 *  The following need previously defined values:
 *      hit_board     //IN- attack record board
 *
 * POST-CONDITIONS
 *      hit_board     //IN- attack record board
 * _________________________________________________________
 ****************************************************************/
void clear_hit_board(char hit_board[][10])     //IN- attack record board
{
    for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 10; j++)
        {
            hit_board[i][j] = ' ';
        }
    }
}

/****************************************************************
 * attack_ship_info
 * This function will prompt player to enter a location to shot
 * and place marker on board
 *
 * returns - none
 * _________________________________________________________
 * PRE-CONDITIONS
 *  The following need previously defined values:
 *      enemy_board, //IN&OUT- enemy's board
 *      hit_board        //IN- attack record board
 * POST-CONDITIONS
 *     enemy_board       //IN&OUT- enemy's board
 * _________________________________________________________
 * Processing:
 * conversion_row        //Processing- row, need to be convet to int
 * is_valid              //Processing- check input is valid
 * ship_index            //Processing- store ship index
 *
 * Input
 * row                   //IN- row
 * col                   //IN- col
 ****************************************************************/
void attack_ship_info(PlayerBoard &enemy_board, //IN&OUT- enemy's board
                      char hit_board[][10])     //IN- attack record board
{
    char conversion_row;        //Processing- row, need to be convet to int
    int row;                    //IN- row
    int col;                    //IN- col
    int is_valid;               //Processing- check input is valid
    int ship_index;             //Processing- store ship index
    //Initialization
    is_valid = 0;
    ship_index = 0;

    do{
        cout << "Fire a shot: ";
        cin >> conversion_row >> col;
        //conversion: row
        row = static_cast<int>(conversion_row - 'A');
        col--;

        if((row >= 0) && (row <= 9) && (col >= 0) && (col <= 9))
        {
            //Hit
            if(check_hit_ship(enemy_board, row, col, ship_index))
            {
                cout << "\nHit!!!\n";
                //set current row col to hit mark
                hit_board[row][col] = 'H';
                enemy_board.a_board[row][col] = 'H';
                //Got hit, lose 1 HP
                enemy_board.ship_status[ship_index].hitcount--;
                //check if this ship lost all HP
                if(enemy_board.ship_status[ship_index].hitcount == 0)
                {
                    cout << "You sunk the ";
                    cout << enemy_board.ship_status[ship_index].name;
                    cout << "!!!\n";
                }

            }
            //Miss
            else
            {               
                if(hit_board[row][col] == ' ')
                {
                    cout << "\nMiss!!!\n";
                    //set current row col to miss mark
                    hit_board[row][col] = 'M';
                    enemy_board.a_board[row][col] = 'M';
                }
                else
                {
                    cout << "\nYou already try current position, you waste a shot\n";
                }

            }
            //stop the loop
            is_valid = 1;
        }
        else
        {
            cout << "\nError: Invalid input\n";
        }
    }while(is_valid == 0);

}

/****************************************************************
 * check_hit_ship
 * This function will check if palyer hit a ship
 *
 * returns - true if ship is hit, false when miss
 * _________________________________________________________
 * PRE-CONDITIONS
 *  The following need previously defined values:
 *      nemy_board       //IN&OUT- enemy's board
 *      row              //IN- row
 *      col              //IN- col
 *      ship_index       //IN&OUT- ship index
 * POST-CONDITIONS
 *      nemy_board       //IN&OUT- enemy's board
 *      ship_index       //IN&OUT- ship index
 * _________________________________________________________
 ****************************************************************/
bool check_hit_ship(PlayerBoard &enemy_board,   //IN&OUT- enemy's board
                    int row,                    //IN- row
                    int col,                    //IN- col
                    int &ship_index)            //IN&OUT- ship index
{
    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < enemy_board.ship_status[i].size; j++)
        {
            if(enemy_board.ship_status[i].ship_occupies.at(j).row == row && enemy_board.ship_status[i].ship_occupies.at(j).col == col)
            {
                ship_index = i;
                return true;
            }
        }
    }
    return false;
}

/****************************************************************
 * draw_board_with_ship
 * This function will draw all ships that AI/player placed back
 * to the board
 *
 * returns - none
 *  _________________________________________________________
 * PRE-CONDITIONS
 *  The following need previously defined values:
 *      p_board      //IN&OUT- player's board
 * POST-CONDITIONS
 *      p_board      //IN&OUT- player's board
 * _________________________________________________________
 ****************************************************************/
void draw_board_with_ship(PlayerBoard &p_board)  //IN&OUT- player's board
{
    for(int j = 0; j < 5; j++)
    {
        //Current player's board
        //set ship horizontal to the board
        if(p_board.ship_status[j].orientation == 'h')
        {
            for(int i = 0; i < p_board.ship_status[j].size; i++)
            {
//                cout << "\n\n\n\n IN the draw board " << p_board.ship_status[j].ship_occupies.size();
                p_board.a_board[p_board.ship_status[j].ship_occupies.at(i).row]
                        [p_board.ship_status[j].ship_occupies.at(i).col] = 's';
            }
        }
        //set ship vertical to the board
        else
        {
            for(int i = 0; i < p_board.ship_status[j].size; i++)
            {
                p_board.a_board[p_board.ship_status[j].ship_occupies.at(i).row]
                        [p_board.ship_status[j].ship_occupies.at(i).col] = 's';
            }
        }
    }
}

/****************************************************************
 * all_ships_sink
 * This function will check if all ships is sink
 *
 * returns - true if all ships sink, false otherwise
 * _________________________________________________________
 * PRE-CONDITIONS
 *  The following need previously defined values:
 *      you_board      //IN&OUT- player's board
 * POST-CONDITIONS
 *      you_board      //IN&OUT- player's board
 * _________________________________________________________
 * Counter
 * sunk_ship;          //Counter- amount of sunk ship
 ****************************************************************/
bool all_ships_sink(PlayerBoard &you_board)    //IN&OUT- player's board
{
    int sunk_ship;          //Counter- amount of sunk ship
    //initialization
    sunk_ship = 0;

    for(int i = 0; i < 5; i++)
    {
        if(you_board.ship_status[i].hitcount == 0)
        {
            sunk_ship++;
        }
    }
    //if all 5 ship sink
    if(sunk_ship == 5)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/****************************************************************
 * PVE_initBoard
 * This function will calls the setShip function for each ship
 * in the fleet(AI and player's fleet).  After each ship is
 * placed on the board the boards should be displayed(player only)
 *
 * returns - none
 * _________________________________________________________
 * PRE-CONDITIONS
 *  The following need previously defined values:
 *      your      //IN&OUT- your board
 *      enemy     //IN&OUT- enemy's board
 * POST-CONDITIONS
 *      your      //IN&OUT- your board
 *      enemy     //IN&OUT- enemy's board
 * _________________________________________________________
 ****************************************************************/
void PVE_initBoard(PlayerBoard &your,       //IN&OUT- your board
                   PlayerBoard &enemy)      //IN&OUT- enemy's board
{
    cout << "Player 1 set your board.";
    displayBoards(your.a_board, enemy.a_board);

    for(int i = 0; i < 5; i++)
    {
        //get info from user
        setShip(your, i);
        displayBoards(your.a_board, enemy.a_board);
    }
    clear_board(your);

    cout << "AI is setting board.";
    for(int i = 0; i < 5; i++)
    {
        //get info by AI
        AI_setShip(enemy, i);
        //displayBoards(enemy.a_board, your.a_board);
    }
    cout << "\n\nAI is all set!\n";
    clear_board(enemy);

}

/****************************************************************
 * AI_setShip
 * This function will let AI set ship(random)
 * The setShip function calls the getValidShipInfo function to
 * determine which spots on the board the ship will occupy.
 *
 * returns - none
 * _________________________________________________________
 * PRE-CONDITIONS
 *  The following need previously defined values:
 *      p_board           //IN&OUT- player's board
 *      ship_index        //IN- ship index
 * POST-CONDITIONS
 *      p_board           //IN&OUT- player's board
 * _________________________________________________________
 * Processing:
 * temp_row               //Processing- temporary row
 * temp_col               //Processing- temporary col
 * temp_orientation       //Processing- temporary orientation
 ****************************************************************/
void AI_setShip(PlayerBoard &p_board,       //IN&OUT- player's board
                int ship_index)             //IN- ship index
{
    int temp_row;               //Processing- temporary row
    int temp_col;               //Processing- temporary col
    char temp_orientation;      //Processing- temporary orientation
    //initialization
    temp_row = 0;
    temp_col = 0;

    //get ship info for AI
    AI_getValidShipInfo(temp_row, temp_col, temp_orientation, p_board, ship_index);
    //set orientation for current ship
    p_board.ship_status[ship_index].orientation = temp_orientation;

    //set ship horizontal to the board
    if(temp_orientation == 'h')
    {
        for(int i = 0; i < p_board.ship_status[ship_index].size; i++)
        {
            p_board.a_board[temp_row][temp_col + i] = 's';
            p_board.ship_status[ship_index].ship_occupies.push_back({temp_row, temp_col + i});
        }
    }
    //set ship vertical to the board
    else
    {
        for(int i = 0; i < p_board.ship_status[ship_index].size; i++)
        {
            p_board.a_board[temp_row + i][temp_col] = 's';
            p_board.ship_status[ship_index].ship_occupies.push_back({temp_row + i, temp_col});
        }
    }
}

/****************************************************************
 * AI_getValidShipInfo
 * This function will let AI randomly get a location and
 * call the function spaceOccupied to determine if any of the
 * spaces the ship would take up if placed on the board are
 * currently occupied.
 *
 * returns - none
 * _________________________________________________________
 * PRE-CONDITIONS
 *  The following need previously defined values:
 *      row                 //IN&OUT- row
 *      col                 //IN&OUT- col
 *      p_board             //IN&OUT- player's board
 *      ship_index          //IN- ship index
 * POST-CONDITIONS
 *      row                 //IN&OUT- row
 *      col                 //IN&OUT- col
 *      p_board             //IN&OUT- player's board
 * _________________________________________________________
 * Processing:
 * ship_size;               //Processing- ship size
 * is_valid;                //Processing- check all input is valid
 * valid_input;             //Processing- check row and col is valid
 * valid_input2;            //Processing- check orientation is valid
 * orientation_in_number;   //Processing- orientation in number,
 *                                                 //0(h),1(v)
 ****************************************************************/
void AI_getValidShipInfo(int &row,              //IN&OUT- row
                         int &col,              //IN&OUT- col
                         char &orientation,     //IN&OUT- orientation
                         PlayerBoard &p_board,  //IN&OUT- player's board
                         int ship_index)        //IN- ship index
{
    int ship_size;                  //Processing- ship size
    int is_valid;                   //Processing- check all input is valid
    int valid_input;                //Processing- check row and col is valid
    int valid_input2;               //Processing- check orientation is valid
    int orientation_in_number;      //Processing- orientation in number,
                                                                //0(h),1(v)
    //Initialization
    is_valid = 0;
    valid_input = 1;
    valid_input2 = 1;

    //set ship size
    ship_size = p_board.ship_status[ship_index].size;
    srand(654);
    do{
        is_valid = 0;
        valid_input = 1;

        //Get row and col for AI
        row = rand() % 10;
        col = rand() % 10;

        if((row >= 0) && (row <= 9) && (col >= 0) && (col <= 9))
        {
            do{
                valid_input2 = 1;

                //0 is horizontal, 1 is vertical
                orientation_in_number = rand() % 2;
                if(orientation_in_number == 0)
                {
                    orientation = 'h';
                }
                else
                {
                    orientation = 'v';
                }

                if(orientation != 'h' && orientation != 'v')
                {
                    //"\nAI Error: invalid ship orientation.\n";
                    valid_input2 = 0;
                }

            }while(valid_input2 == 0);
        }
        else
        {
            //"\nAI Error: invalid ship placement.\n";
            valid_input = 0;
        }
        //check out of board
        //check row
        if(orientation == 'h' && valid_input == 1)
        {
            if((col + ship_size) > 10)
            {
                //"\nError: Ship placement is outside the board.\n";
                valid_input = 0;
            }

        }
        //check col
        else if(orientation == 'v' && valid_input == 1)
        {
            if((row + ship_size) > 10)
            {
                //"\nError: Ship placement is outside the board.\n";
                valid_input = 0;
            }
        }
        //Call spaceOccupied to check
        if(valid_input == 1 && !(AI_spaceOccupied(p_board, row, col, orientation, ship_size)))
        {
            is_valid = 1;
        }

    }while(is_valid == 0);
}

/****************************************************************
 * AI_getValidShipInfo
 * This function will returns true if the placement of the ship
 * would overlap an already existing ship placement or false if
 * the space is not occupied.
 *
 * returns - returns true if the placement of the ship
 * would overlap an already existing ship placement
 *  False if the space is not occupied.
 *  _________________________________________________________
 * PRE-CONDITIONS
 *  The following need previously defined values:
 *      p_board      //IN&OUT- player's board
 *      row          //IN- row
 *      col          //IN- col
 *      orientation  //IN- orientation
 *      size         //IN- size
 * POST-CONDITIONS
 *     p_board       //IN&OUT- player's board
 * _________________________________________________________
 ****************************************************************/
bool AI_spaceOccupied(PlayerBoard &p_board,     //IN&OUT- player's board
                      int row,                  //IN- row
                      int col,                  //IN- col
                      char orientation,         //IN- orientation
                      int size)                 //IN- size
{
    //Check row
    if(orientation == 'h')
    {
        for(int i = 0; i < size; i++)
        {
            if(p_board.a_board[row][col + i] != ' ')
            {
                return true;
            }
        }
    }
    //Check col
    else
    {
        for(int i = 0; i < size; i++)
        {
            if(p_board.a_board[row + i][col] != ' ')
            {
                return true;
            }
        }
    }

    return false;
}

/****************************************************************
 * AI_attack_ship_info
 * This function will let AI get a location by algorithm to shot
 * Once AI get hit, it will trun on target mod and hit the
 * surrounding area.
 *
 * Algorithm: Every time AI get hit, it will store this postion
 * into two parallel vector. It will go back and hit around thoses
 * point at most 4 time, or go the next position, or turn hunt
 * mod on
 *
 * returns - none
 * _________________________________________________________
 * PRE-CONDITIONS
 *  The following need previously defined values:
 *      enemy_board        //IN&OUT- enemy's board
 *      hit_board          //IN- attack record board
 * POST-CONDITIONS
 *      enemy_board        //IN&OUT- enemy's board
 * _________________________________________________________
 * Processing:
 * ship_index              //Processing- ship index
 *
 * static:
 * row                     //Static- current row
 * col                     //Static- current col
 * AI_shot_count           //Static- current AI shot count
 * AI_miss_count           //Static- current AI miss count
 * AI_attack_mod           //Static- attack_mod,
 *                               //0 is Hunt mod, 1 is Target mod
 * hit_point               //Static-Vector- point that get hit
 * empty_space             //Static-Vector- empty_space around hit_point
 * wait_list               //Static- index of current list
 ****************************************************************/
void AI_attack_ship_info(PlayerBoard &enemy_board,  //IN&OUT- enemy's board
                         char hit_board[][10])      //IN- attack record board
{
    static int row;                     //Static- current row
    static int col;                     //Static- current col
    static int AI_shot_count;           //Static- current AI shot count
    static int AI_miss_count;           //Static- current AI miss count
    static int AI_attack_mod;           //Static- attack_mod,
                                             //0 is Hunt mod, 1 is Target mod

    static vector<Point> hit_point;     //Static-Vector- point that get hit
    static vector<int> empty_space;     //Static-Vector- empty_space
                                             //around hit_point
    static int wait_list;               //Static- index of current list

    int ship_index;                     //Processing- ship index

    //initialization
    ship_index = 0;

    cout << "Computer Fire a shot: ";
    //Get row and col for AI
    if(AI_attack_mod == 0)
    {
        do{
            row = rand() % 10;
            col = rand() % 10;
            //loop stop when current point is space
        }while(hit_board[row][col] == 'H' || hit_board[row][col] == 'M');
    }
    //AI_attack_mod == 1, target mod
    else
    {             
        //AI_attack_mod 1
        //true when total shot is equal to total empty space
        //true when AI finished current list
        if( ((AI_miss_count + AI_shot_count) == empty_space[wait_list]) && (empty_space[wait_list] != 0))
        {
            //Go to the next list
            if((wait_list + 1) < hit_point.size())
            {
                //next wait list
                wait_list++;   

                //recount empty space
                empty_space.at(wait_list) = count_empty_space(hit_point, hit_board, wait_list);

                //True when there is no empty space to shot
                if(empty_space.at(wait_list) == 0)
                {
                    wait_list++;

                    //reset hit/miss count
                    AI_miss_count = 0;
                    AI_shot_count = 0;

                    AI_fire_position(hit_point, hit_board, wait_list, row, col, AI_attack_mod);
                }

                //reset hit/miss count
                AI_miss_count = 0;
                AI_shot_count = 0;
            }
            else
            {
                //when all wait list is done, turn off target mod
                AI_attack_mod = 0;
            }
            //AI shot
            AI_fire_position(hit_point, hit_board, wait_list, row, col, AI_attack_mod);

        }
        //keep target mod on to hit around
        else
        {
            AI_fire_position(hit_point, hit_board, wait_list, row, col, AI_attack_mod);

        }
    }
    //if no empty space around center, get a random place
    if(AI_attack_mod == 0)
    {
        //cout << "AI_attack_mod 0  no empty space around center\n";
        do{
            row = rand() % 10;
            col = rand() % 10;
            //loop stop when current point is space
        }while(hit_board[row][col] == 'H' || hit_board[row][col] == 'M');
    }

        //Hit
        if(check_hit_ship(enemy_board, row, col, ship_index) && hit_board[row][col] == ' ')
        {
            //set hit position to hit mark
            hit_board[row][col] = 'H';
            enemy_board.a_board[row][col] = 'H';

            if(AI_attack_mod == 1)
            {
                AI_shot_count++;
            }

            AI_attack_mod = 1;  

            //save hit point as center
            hit_point.push_back({row, col});
            //let empty_space's index parallel to hit_point
            empty_space.push_back(count_empty_space(hit_point, hit_board, wait_list));

            //Got hit, lose 1 HP
            enemy_board.ship_status[ship_index].hitcount--;
            //check if this ship lost all HP
            if(enemy_board.ship_status[ship_index].hitcount == 0)
            {
                cout << "\nComputer sunk your ";
                cout << enemy_board.ship_status[ship_index].name;
                cout << "!!!\n";
            }

        }
        //Miss
        else
        {
            if(hit_board[row][col] == ' ')
            {
                cout << "\nMiss!!!\n";
                //set current postion to miss mark
                hit_board[row][col] = 'M';
                enemy_board.a_board[row][col] = 'M';

                if(AI_attack_mod == 1)
                {
                    AI_miss_count++;
                }
            }
        }
}

/****************************************************************
 * count_empty_space
 * This function will count empty space (' ') around a location
 *
 * returns - amount of empty space
 * _________________________________________________________
 * PRE-CONDITIONS
 *  The following need previously defined values:
 *      hit_point      //IN&OUT- center point
 *      hit_board      //IN- attack record board
 *      wait_list      //IN&OUT- wait list
 * POST-CONDITIONS
 *      hit_point      //IN&OUT- center point
 *      wait_list      //IN&OUT- wait list
 * _________________________________________________________
 * Bool
 * case1               //Bool- case1 can be use
 * case2               //Bool- case2 can be use
 * case3               //Bool- case3 can be use
 * case4               //Bool- case4 can be use
 *
 * Processing
 * space_amount        //processing- amount of empty space
 ****************************************************************/
int count_empty_space(vector<Point> &hit_point,     //IN&OUT- center point
                      char hit_board[][10],         //IN- attack record board
                      int &wait_list)               //IN&OUT- wait list
{
    int space_amount;       //processing- amount of empty space
    bool case1;             //Bool- case1 can be use
    bool case2;             //Bool- case2 can be use
    bool case3;             //Bool- case3 can be use
    bool case4;             //Bool- case4 can be use
    //initialization
    space_amount = 0;
    case1 = false;
    case2 = false;
    case3 = false;
    case4 = false;

    //boundary check
    AI_boundary_check(hit_point, wait_list, case1, case2, case3, case4);

    //check every case(4 time), each case can only run once
    for(int i = 0; i < 4; i++)
    {
        if(hit_board[hit_point.at(wait_list).row + 1][hit_point.at(wait_list).col] == ' ' && case1)
        {
            space_amount++;
            case1 = false;
        }
        else if(hit_board[hit_point.at(wait_list).row - 1][hit_point.at(wait_list).col] == ' ' && case2)
        {
            space_amount++;
            case2 = false;
        }
        else if(hit_board[hit_point.at(wait_list).row][hit_point.at(wait_list).col + 1] == ' ' && case3)
        {
            space_amount++;
            case3 = false;
        }
        else if(hit_board[hit_point.at(wait_list).row][hit_point.at(wait_list).col - 1] == ' ' && case4)
        {
            space_amount++;
            case4 = false;
        }
    }

    return space_amount;
}
/****************************************************************
 * AI_fire_position
 * This function will fire postions that around the center point
 * iff that point is inside boundary and empty. Otherwise, it will
 * change the next center point and fire again.
 *
 * returns - None
 * _________________________________________________________
 * PRE-CONDITIONS
 *  The following need previously defined values:
 *      hit_point      //IN&OUT- center point
 *      hit_board      //IN- attack record board
 *      wait_list      //IN&OUT- wait list
 *      row            //IN&OUT- row
 *      col            //IN&OUT- col
 *      AI_attack_mod  //IN&OUT- AI attack mod
 * POST-CONDITIONS
 *      hit_point      //IN&OUT- center point
 *      wait_list      //IN&OUT- wait list
 *      row            //IN&OUT- row
 *      col            //IN&OUT- col
 *      AI_attack_mod  //IN&OUT- AI attack mod
 * _________________________________________________________
 * Bool
 * case1               //Bool- case1 can be use
 * case2               //Bool- case2 can be use
 * case3               //Bool- case3 can be use
 * case4               //Bool- case4 can be use
 * again               //Bool- try to fire again
 ****************************************************************/
void AI_fire_position(vector<Point> &hit_point,     //IN&OUT- center point
                      char hit_board[][10],         //IN- attack record board
                      int &wait_list,               //IN&OUT- wait list
                      int &row,                     //IN&OUT- row
                      int &col,                     //IN&OUT- col
                      int &AI_attack_mod)           //IN&OUT- AI attack mod
{

    bool case1;             //Bool- case1 can be use
    bool case2;             //Bool- case2 can be use
    bool case3;             //Bool- case3 can be use
    bool case4;             //Bool- case4 can be use

    bool again;             //Bool- try to fire again
    //initialization
    again = false;
    case1 = false;
    case2 = false;
    case3 = false;
    case4 = false;

    do{
        //boundary check
        AI_boundary_check(hit_point, wait_list, case1, case2, case3, case4);
        //check every case(4 time), each case can only run once
        if(hit_board[hit_point.at(wait_list).row + 1][hit_point.at(wait_list).col] == ' ' && case1)
        {
            row = hit_point.at(wait_list).row + 1;
            col = hit_point.at(wait_list).col;
            again = false;
        }
        else if(hit_board[hit_point.at(wait_list).row - 1][hit_point.at(wait_list).col] == ' ' && case2)
        {
            row = hit_point.at(wait_list).row - 1;
            col = hit_point.at(wait_list).col;
            again = false;
        }
        else if(hit_board[hit_point.at(wait_list).row][hit_point.at(wait_list).col + 1] == ' ' && case3)
        {
            row = hit_point.at(wait_list).row;
            col = hit_point.at(wait_list).col + 1;
            again = false;
        }
        else if(hit_board[hit_point.at(wait_list).row][hit_point.at(wait_list).col - 1] == ' ' && case4)
        {
            row = hit_point.at(wait_list).row;
            col = hit_point.at(wait_list).col - 1;
            again = false;
        }
        //Run when none of the case fit
        else {
            //force go to the next wait list and try it again
            //False if all list is done
            if((wait_list + 1) < hit_point.size())
            {
                wait_list++;
                again = true;
            }
            //if all wait list is done, turn off target mod
            else
            {
                again = false;
                AI_attack_mod = 0;
            }
        }
    }while(again);

}

/****************************************************************
 * AI_boundary_check
 * This function will check the boundary
 * for funtion- AI_fire_position
 * It will change each cases that in the AI_fire_position to false
 * if that postion is not in the boundary
 *
 * returns - None
 *  PRE-CONDITIONS
 *  The following need previously defined values:
 *      hit_point      //IN&OUT- center point
 *      wait_list      //IN&OUT- wait list
 *      case1          //IN&OUT- case 1
 *      case2          //IN&OUT- case 2
 *      case3          //IN&OUT- case 3
 *      case4          //IN&OUT- case 4
 *
 * POST-CONDITIONS
 *      hit_point      //IN&OUT- center point
 *      wait_list      //IN&OUT- wait list
 *      case1          //IN&OUT- case 1
 *      case2          //IN&OUT- case 2
 *      case3          //IN&OUT- case 3
 *      case4          //IN&OUT- case 4
 * _________________________________________________________
 ****************************************************************/
void AI_boundary_check(vector<Point> &hit_point,    //IN&OUT- center point
                       int &wait_list,              //IN&OUT- wait list
                       bool &case1,                 //IN&OUT- case 1
                       bool &case2,                 //IN&OUT- case 2
                       bool &case3,                 //IN&OUT- case 3
                       bool &case4)                 //IN&OUT- case 4
{
    //Case will be true if attack is in boundary
    if((hit_point.at(wait_list).row + 1 >= 0 && hit_point.at(wait_list).row + 1 <= 9) &&
            (hit_point.at(wait_list).col >= 0 && hit_point.at(wait_list).col <= 9))
    {
        case1 = true;
    }

    if((hit_point.at(wait_list).row - 1 >= 0 && hit_point.at(wait_list).row - 1 <= 9) &&
            (hit_point.at(wait_list).col >= 0 && hit_point.at(wait_list).col <= 9))
    {
        case2 = true;
    }

    if((hit_point.at(wait_list).row >= 0 && hit_point.at(wait_list).row<= 9) &&
            (hit_point.at(wait_list).col + 1 >= 0 && hit_point.at(wait_list).col + 1 <= 9))
    {
        case3 = true;
    }

    if((hit_point.at(wait_list).row >= 0 && hit_point.at(wait_list).row <= 9) &&
            (hit_point.at(wait_list).col - 1 >= 0 && hit_point.at(wait_list).col - 1 <= 9))
    {
        case4 = true;
    }

}

