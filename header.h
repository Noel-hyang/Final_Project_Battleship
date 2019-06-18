#ifndef HEADER_H
#define HEADER_H
#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

//Global variables
const int Carrier = 5;
const int Battleship = 4;
const int Cruiser = 3;
const int Submarine = 3;
const int Destroyer = 2;
const int FLEET_SIZE = 5;

struct Point
{
    int row;
    int col;
};

struct Ship
{
    string name;
    int size;
    int hitcount;
    vector<Point> ship_occupies;
    char orientation;
};

struct PlayerBoard
{
    char a_board [10][10]{{' '}};
    Ship ship_status [FLEET_SIZE];
};

/****************************************************************
 * displayBoards
 * This function will display Boards
 *
 * returns - none
 ****************************************************************/
void displayBoards(char your[][10],     //IN- your board
                   char enemy[][10]);   //IN- enemy board

/****************************************************************
 * setShip
 * This function will let palyer set ship
 * The setShip function calls the getValidShipInfo function to
 * determine which spots on the board the ship will occupy.
 *
 * returns - none
 ****************************************************************/
void setShip(PlayerBoard &p_board,      //IN&OUT- player's board
             int ship_index);           //IN- ship index

/****************************************************************
 * getValidShipInfo
 * This function will prompt the user for the starting row and column
 * coordinates of the ship which the user will enter as: letter
 * number. The function will also call the function spaceOccupied to
 * determine if any of the spaces the ship would take up if
 * placed on the board are currently occupied.
 *
 * returns - none
 ****************************************************************/
void getValidShipInfo(int &row,             //IN&OUT row
                      int &col,             //IN&OUT- col
                      char &orientation,    //IN&OUT- orientation
                      PlayerBoard &p_board, //IN&OUT- player's board
                      int ship_index);      //IN- ship index

/****************************************************************
 * spaceOccupied
 * This function will returns true if the placement of the ship
 * would overlap an already existing ship placement or false if
 * the space is not occupied.
 *
 * returns - returns true if the placement of the ship
 * would overlap an already existing ship placement
 *  false if the space is not occupied.
 ****************************************************************/
bool spaceOccupied(PlayerBoard &p_board,    //IN&OUT- player's board
                   int row,                 //IN- row
                   int col,                 //IN- col
                   char orientation,        //IN- orientation
                   int size);               //IN- size of ship

/****************************************************************
 * initBoard
 * This function will calls the setShip function for each ship
 * in the fleet.  After each ship is placed on the board the
 * boards should be displayed.
 *
 * returns - none
 ****************************************************************/
void initBoard(PlayerBoard &your,           //IN&OUT- your board
               PlayerBoard &enemy);         //IN&OUT- enemy's board

/****************************************************************
 * initFleet
 * This function will initializes all the ships in the fleet
 * with the appropriate information.
 *
 * returns - none
 ****************************************************************/
void initFleet(PlayerBoard &p_board);       //IN&OUT- player's board

/****************************************************************
 * attack_ship_info
 * This function will prompt player to enter a location to shot
 * and place marker on board
 *
 * returns - none
 ****************************************************************/
void attack_ship_info(PlayerBoard &enemy_board, //IN&OUT- enemy's board
                      char hit_board[][10]);    //IN- attack record board

/****************************************************************
 * check_hit_ship
 * This function will check if palyer hit a ship
 *
 * returns - true if ship is hit, false when miss
 ****************************************************************/
bool check_hit_ship(PlayerBoard &enemy_board,   //IN&OUT- enemy's board
                    int row,                    //IN- row
                    int col,                    //IN- col
                    int &ship_index);           //IN&OUT- ship index

/****************************************************************
 * draw_board_with_ship
 * This function will draw all ships that AI/player placed back
 * to the board
 *
 * returns - none
 ****************************************************************/
void draw_board_with_ship(PlayerBoard &p_board);  //IN&OUT- player's board

/****************************************************************
 * all_ships_sink
 * This function will check if all ships is sink
 *
 * returns - true if all ships sink, false otherwise
 ****************************************************************/
bool all_ships_sink(PlayerBoard &you_board);    //IN&OUT- player's board

/****************************************************************
 * PVE_initBoard
 * This function will calls the setShip function for each ship
 * in the fleet(AI and player's fleet).  After each ship is
 * placed on the board the boards should be displayed(player only)
 *
 * returns - none
 ****************************************************************/
void PVE_initBoard(PlayerBoard &your,       //IN&OUT- your board
                   PlayerBoard &enemy);     //IN&OUT- enemy's board

/****************************************************************
 * AI_setShip
 * This function will let AI set ship(random)
 * The setShip function calls the getValidShipInfo function to
 * determine which spots on the board the ship will occupy.
 *
 * returns - none
 ****************************************************************/
void AI_setShip(PlayerBoard &p_board,       //IN&OUT- player's board
                int ship_index);            //IN- ship index

/****************************************************************
 * AI_getValidShipInfo
 * This function will let AI randomly get a location and
 * call the function spaceOccupied to determine if any of the
 * spaces the ship would take up if placed on the board are
 * currently occupied.
 *
 * returns - none
 ****************************************************************/
void AI_getValidShipInfo(int &row,              //IN&OUT- row
                         int &col,              //IN&OUT- col
                         char &orientation,     //IN&OUT- orientation
                         PlayerBoard &p_board,  //IN&OUT- player's board
                         int ship_index);       //IN- ship index

/****************************************************************
 * AI_getValidShipInfo
 * This function will returns true if the placement of the ship
 * would overlap an already existing ship placement or false if
 * the space is not occupied.
 *
 * returns - returns true if the placement of the ship
 * would overlap an already existing ship placement
 *  false if the space is not occupied.
 ****************************************************************/
bool AI_spaceOccupied(PlayerBoard &p_board,     //IN&OUT- player's board
                      int row,                  //IN- row
                      int col,                  //IN- col
                      char orientation,         //IN- orientation
                      int size);                //IN- size

/****************************************************************
 * AI_attack_ship_info
 * This function will let AI get a location by algorithm to shot
 * Once AI get hit, it will trun on target mod and hit the
 * surrounding area.
 * Algorithm: Every time AI get hit, it will store this postion
 * into two parallel vector. It will go back and hit around thoses
 * point at most 4 time, or go the next position, or turn hunt
 * mod on
 *
 * returns - none
 ****************************************************************/
void AI_attack_ship_info(PlayerBoard &enemy_board,  //IN&OUT- enemy's board
                         char hit_board[][10]);     //IN- attack record board

/****************************************************************
 * count_empty_space
 * This function will count empty space (' ') around a location
 *
 * returns - amount of empty space
 ****************************************************************/
int count_empty_space(vector<Point> &hit_point,     //IN&OUT- center point
                      char hit_board[][10],         //IN- attack record board
                      int &wait_list);              //IN&OUT- wait list

/****************************************************************
 * AI_fire_position
 * This function will fire postions that around the center point
 * iff that point is inside boundary and empty. Otherwise, it will
 * change the next center point and fire again.
 *
 * returns - None
 ****************************************************************/
void AI_fire_position(vector<Point> &hit_point,     //IN&OUT- center point
                      char hit_board[][10],         //IN- attack record board
                      int &wait_list,               //IN&OUT- wait list
                      int &row,                     //IN&OUT- row
                      int &col,                     //IN&OUT- col
                      int &AI_attack_mod);          //IN&OUT- AI attack mod

/****************************************************************
 * AI_boundary_check
 * This function will check the boundary
 * for funtion- AI_fire_position
 * It will change each cases that in the AI_fire_position to false
 * if that postion is not in the boundary
 *
 * returns - None
 ****************************************************************/
void AI_boundary_check(vector<Point> &hit_point,    //IN&OUT- center point
                       int &wait_list,              //IN&OUT- wait list
                       bool &case1,                 //IN&OUT- case 1
                       bool &case2,                 //IN&OUT- case 2
                       bool &case3,                 //IN&OUT- case 3
                       bool &case4);                //IN&OUT- case 4

/****************************************************************
 * clear_board
 * This function will clear the all cell to ' '
 *
 * returns - None
 ****************************************************************/
void clear_board(PlayerBoard &p_board);     //IN&OUT- Player's board

/****************************************************************
 * clear_hit_board
 * This function will clear the all hit_board's cell to ' '
 *
 * returns - None
 ****************************************************************/
void clear_hit_board(char hit_board[][10]);     //IN- attack record board

#endif // HEADER_H
