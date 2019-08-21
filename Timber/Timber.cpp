// Include libraries here

#include "pch.h"
#include <SFML/Graphics.hpp>

// Simplify coding by using sf namespace for sfml library calls
using namespace sf;


//main loop
int main()
{
	// Create a video mode object
	VideoMode vm(1920, 1080);

	//Create and open a window for the game
	RenderWindow window(vm, "Timber!!!", Style::Fullscreen);
	return 0;
}
