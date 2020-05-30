# aseity
Have you ever wanted to view an image inside a text-based interface, and were irritated when you had to use a separate program to view it?

Aseity is a simple tool that will render full color (24-bit) images inside any terminal that supports 24-bit color escape codes (https://en.wikipedia.org/wiki/ANSI_escape_code#24-bit), such as PuTTY. The resolution you get depends entirely on how many rows and columns of text you have your terminal set to. If you want to get a high fidelity rendering of your image, turn down your font size as much as possible. If not, you'll get a blocky low-res raster of the image, which often times is all you really need.

Compilation instructions:
1) Install CImg if you don't have it already via: **sudo apt-get install cimg-dev** (if you use Ubuntu) or by following the installation steps here: http://www.cimg.eu/
2) Clone this repository into a new directory
3) cd into the new directory and type: **make**. This will build an executable in the directory named "aseity".

How to run the code:
**./aseity filename** (for example, "./aseity kyoto.jpg")

This will rasterize the image found in filename to the terminal, using the maximum screen size if the image is bigger than the number of columns x rows you have on the screen. It will anti-alias the pixels if it has to rasterize at a lower resolution. If you set your font size to be smaller, you'll get better resolution from the image.

Be aware, terminals were not written with bitmap rasterization in mind, so performance can be slow. Don't rely on this to do anything in real time, and be ready to clear your screen (with ctrl-l) after rasterizing an image. It's also not a faithful rasterization due to terminals having non-square pixels. The code adjusts for this a bit, but it's not perfect.

Here is a rendering of a Monet artwork from entirely within a text-based terminal: 
![Monet in a terminal](https://i.imgur.com/B3pATa0.png?raw=true)

This album shows the original artwork and what the art looks like when rasterized at different resolutions: https://imgur.com/a/lAd6unY

The header file in this project, colors.h, can be used in any C++ project that you'd like to add colors to. If you want colored text, once you include it you can do something like this: **cout << RED << "Hello " << BLUE << "World!\n" << RESET;** to output Hello in red, World in blue, and then resetting the colors back to default after this.

colors.h also functions as a very simple NCURSES-esque library that lets you get the current terminal size, move the cursor to an arbitrary row and column, and change the foreground/background color to any 24-bit value. Basically everything I typically use NCURSES for but without the overhead.
