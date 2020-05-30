//This program will use xterm to display an image on the screen in 24 bit color
#define cimg_display 0 //Stop CImg from trying to use X
#include "CImg.h" //CImg.h handles opening the image files
#include "colors.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <cassert>
using namespace std;
using namespace cimg_library;

#define R(i,j) (j*WIDTH+i)
#define G(i,j) (STRIDE+j*WIDTH+i)
#define B(i,j) (STRIDE+STRIDE+j*WIDTH+i)

void usage() {
	cout << "Error: this program needs to be called with a command line parameter indicating what file to open.\n";
	cout << "For example, aseity kyoto.jpg\n";
	exit (1);
}


int main(int argc, char **argv) {
	const bool ANTIALIAS = true;
	const bool DEBUG = false;
	const double PIXEL_GEOMETRY_Y = 1; //Adjust this for non-square pixels
	const double PIXEL_GEOMETRY_X = 1.65; //Adjust this for non-square pixels

	//Parse command line parameters
	if (argc != 2) usage(); 
	string filename = argv[1];
	if (filename == "") {
		cout << "Invalid filename.\n";
		exit(1);
	}
	//Clear the screen, which makes rasterizing faster without scrolling
	cout << '';
	resetcolor();

	//Get the terminal size
	const auto [ROWS,COLS] = get_terminal_size();

	//Load the image
	try { 
		CImg<unsigned char> image (filename.c_str());
		const int WIDTH = image.width(), HEIGHT = image.height();
		const int STRIDE = WIDTH * HEIGHT;
		unsigned char *in = image; //I do this so I can optimize compile time at a later date by passing out a pointer. CImg = slow compiles.

		//We will rasterize every pixel if it is smaller than the screen, or skip every X pixels if it is X times bigger
		int i_step = HEIGHT > ROWS ? (ceil((PIXEL_GEOMETRY_Y*HEIGHT)/ROWS)) : 1;
		int j_step = WIDTH > COLS ?  (ceil((PIXEL_GEOMETRY_X*WIDTH) /COLS)) : 1;
		if constexpr (DEBUG) {
			cout << "WIDTH: " << WIDTH << " COLS: " << COLS << " HEIGHT: " << HEIGHT << " ROWS: " << ROWS << endl;
			cout << "i_step: " << i_step << " j_step: " << j_step << endl;
		}

		//Rasterize the image to the terminal
		for (int i = 0; i < HEIGHT; i += i_step) { //From (0,0), the top left, sweep left to right and top to down
			for (int j = 0; j < WIDTH; j += j_step) {
				if (ANTIALIAS) {
					int v_dist = (HEIGHT - i > i_step) ? i_step : (HEIGHT-i); //How many pixels to alias down
					int h_dist = (WIDTH - j > j_step)  ? j_step : (WIDTH-j); //How many pixels to alias to the right
					assert(v_dist and h_dist); //They should always be >= 1, so die if they're not
					uint64_t r_sum = 0, b_sum = 0, g_sum = 0;
					//Average all pixels in this block together
					for (int y = 0; y < v_dist; y++) {
						for (int x = 0; x < h_dist; x++) {
							r_sum += in[R(x+j,y+i)];
							g_sum += in[G(x+j,y+i)];
							b_sum += in[B(x+j,y+i)];
						}
					}
					r_sum /= v_dist*h_dist;
					g_sum /= v_dist*h_dist;
					b_sum /= v_dist*h_dist;
					//Set the output to the average of all the values
					setbgcolor(r_sum,g_sum,b_sum);
					cout << " ";
				}
				else { //No antialiasing, just grab every Xth pixel
					setbgcolor(in[R(j,i)],in[G(j,i)], in[B(j,i)]);
					cout << " "; //TODO: use the foreground color and write over the background color for more detail
				}
			}
			resetcolor();
			cout << endl;
		}
	} catch (...) {
		cout << "Error parsing file: "s + filename << endl;
		exit(1);
	}
}

