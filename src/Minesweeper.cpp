/**
*
* Solution to course project # 13
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2021/2022
*
* @author Tsvetilin Tsvetilov
* @idnumber 3MI0600062
* @compiler VC
*
* Program entry point
*
*/

#include "../lib/Game.hpp"

int main()
{
    Game game(std::cin, std::cout);
    game.run();

    return 0;   
}