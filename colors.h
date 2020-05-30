//colors.h, using ANSI escape codes to set the foreground and background text colors for a terminal
//Author: ShakaUVM, using code sequences found online
#pragma once
#include <string>
#include <iostream>
#include <sys/ioctl.h>
#include <utility>

//Usage:
//Echo RED as part of a cout to turn the following text red
//Echo RESET after you are done and it will go back to normal
//For example: cout << RED << "Hello World" << RESET << endl;
const std::string RESET   = "\033[0m";
const std::string BLACK   = "\033[30m";      /* Black */
const std::string RED     = "\033[31m";      /* Red */
const std::string GREEN   = "\033[32m";      /* Green */
const std::string YELLOW  = "\033[33m";      /* Yellow */
const std::string BLUE    = "\033[34m";      /* Blue */
const std::string MAGENTA = "\033[35m";      /* Magenta */
const std::string CYAN    = "\033[36m";      /* Cyan */
const std::string WHITE   = "\033[37m";      /* White */
const std::string BOLDBLACK   = "\033[1m\033[30m";      /* Bold Black */
const std::string BOLDRED     = "\033[1m\033[31m";      /* Bold Red */
const std::string BOLDGREEN   = "\033[1m\033[32m";      /* Bold Green */
const std::string BOLDYELLOW  = "\033[1m\033[33m";      /* Bold Yellow */
const std::string BOLDBLUE    = "\033[1m\033[34m";      /* Bold Blue */
const std::string BOLDMAGENTA = "\033[1m\033[35m";      /* Bold Magenta */
const std::string BOLDCYAN    = "\033[1m\033[36m";      /* Bold Cyan */
const std::string BOLDWHITE   = "\033[1m\033[37m";      /* Bold White */

//Sets the background color for all text printed from this point on
//Values range from 0 to 255 in each color channel
void setbgcolor(uint8_t R, uint8_t G, uint8_t B) {
	std::cerr << "\x1b[48;2;" << (int)R << ";" << (int)G << ";" << (int)B << "m";
}

//Sets the foreground color for all text printed from this point on
void setcolor(uint8_t R, uint8_t G, uint8_t B) {
	std::cerr << "\x1b[38;2;" << (int)R << ";" << (int)G << ";" << (int)B << "m";
}

//Sets the foreground and background colors back to the default
void resetcolor() {
	std::cerr << "\x1b[0m";
}

//These functions are like a mini NCURSES library

//Returns the ROWS and COLS of the current terminal
std::pair<int,int> get_terminal_size() { 
    struct winsize w;
    ioctl(0, TIOCGWINSZ, &w);
    return {w.ws_row-1, w.ws_col}; //Subtract 1 to give room for the UNIX prompt at the bottom of the screen
}

//Moves the cursor to the indicated row and column
void movecursor(uint32_t row, uint32_t col) {
	std::cerr << "\033[" << row << ";" << col << "H";
}

//Clears the screen
void clearscreen() {
	std::cerr << "\033[2J";
}
