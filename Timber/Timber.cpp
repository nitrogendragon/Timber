// Include libraries here

#include "pch.h"
#include <SFML/Graphics.hpp>

// Simplify coding by using sf namespace for sfml library calls
using namespace sf;


//main loop
int main()
{
	// Low res code
	VideoMode vm(1920, 1080);

	//Create and open a window for the game
	RenderWindow window(vm, "Timber!!!", Style::Fullscreen);
	View view(FloatRect(0, 0, 1920, 1080));
	window.setView(view);
	//End of low res code

	//Create a texture to load and store on the GPU
	Texture textureBackground;

	//Load a graphic into the texture
	textureBackground.loadFromFile("graphics/background.png");

	//Create a sprite
	Sprite spriteBackground;

	// Attach the texture to the sprite
	spriteBackground.setTexture(textureBackground);

	// Set the spriteBackground to cover the screen
	spriteBackground.setPosition(0, 0);

	//Make a tree sprite
	Texture textureTree;
	textureTree.loadFromFile("graphics/tree.png");
	Sprite spriteTree;
	spriteTree.setTexture(textureTree);
	spriteTree.setPosition(810, 0);

	// Make the bee sprite and prep variables...this is really bad code but we will go with it for now
	Texture textureBee;
	textureBee.loadFromFile("graphics/insect.png");
	Sprite spriteBee;
	spriteBee.setTexture(textureBee);
	spriteBee.setPosition(0, 800);
	//is the bee currently moving?
	bool beeACtive = false;
	// How fast can the bee fly
	float beeSpeed = 0.0f;

	// make 3 cloud sprites from 1 texture
	Texture textureCloud;
	//Load 1 new texture
	textureCloud.loadFromFile("graphics/cloud.png");
	// 3 New sprites with the same texture
	Sprite spriteCloud1;
	Sprite spriteCloud2;
	Sprite spriteCloud3;
	spriteCloud1.setTexture(textureCloud);
	spriteCloud2.setTexture(textureCloud);
	spriteCloud3.setTexture(textureCloud);
	//Position the clouds off screen
	spriteCloud1.setPosition(0, 0);
	spriteCloud2.setPosition(0, 250);
	spriteCloud3.setPosition(0, 500);
	//are the clouds currently on screen
	bool cloud1Active = false;
	bool cloud2Active = false;
	bool cloud3Active = false;
	//How fast is  each cloud?
	float cloud1Speed = 0.0f;
	float cloud2Speed = 0.0f;
	float cloud3Speed = 0.0f;

	while (window.isOpen())
	{
		/*
		******************************
		Handle the players input
		******************************
		*/
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}
		/*
		******************************
		Update the Scene
		******************************
		*/



		/*
		******************************
		Draw the scene
		******************************
		*/

		// Clear everything from the last frame
		window.clear();

		//Draw our game scene here
		window.draw(spriteBackground);

		//Draw the coulds
		window.draw(spriteCloud1);
		window.draw(spriteCloud2);
		window.draw(spriteCloud3);

		// Draw the tree
		window.draw(spriteTree);

		// Draw the insect
		window.draw(spriteBee);

		//Show everything we just drew
		window.display();



	}

	return 0;
}
