// Include libraries here

#include "pch.h"
#include <sstream>
#include <SFML/Graphics.hpp>

// Simplify coding by using sf namespace for sfml library calls
using namespace sf;

/*
***********************************************
Function Declarations
********************************************
*/
//takes in an int seed as a parameter
void updateBranches(int seed);
const int NUM_BRANCHES = 6;
Sprite branches[NUM_BRANCHES];
//Where is the player /branch?
//Left or Right?
enum class side {LEFT, RIGHT, NONE };
side branchPositions[NUM_BRANCHES];

/*
***********************************************
Main Loop
********************************************
*/
int main()
{
	// Low res code
	VideoMode vm(1920, 1080);

	//Create and open a window for the game
	RenderWindow window(vm, "Timber!!!", Style::Fullscreen);

	// Set the viewmode
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
	bool beeActive = false;
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


	// Variables to control time itself
	Clock clock;

	//Our current frame time passed since previous frame
	Time deltaTime;

	// Time bar
	RectangleShape timeBar;
	float timeBarStartWidth = 480;
	float timeBarHeight = 80;
	timeBar.setSize(Vector2f(timeBarStartWidth, timeBarHeight));
	timeBar.setFillColor(Color::Red);
	timeBar.setPosition((1920 / 2) - timeBarStartWidth / 2, 980);

	Time gameTimeTotal;
	float timeRemaining = 6.0f;
	float timeBarWidthPerSecond = timeBarStartWidth / timeRemaining;
	// Track whether the game is running
	bool paused = true;

	// Draw some text
	int score = 0;
	sf::Text messageText;
	sf::Text scoreText;

	//Choose a font
	Font font;
	font.loadFromFile("fonts/KOMIKAP_.ttf");

	// Set the font to our message
	messageText.setFont(font);
	scoreText.setFont(font);

	// Assign the actual message
	messageText.setString("Press Enter to start!");
	scoreText.setString("Score = 0" + score);

	// Make it really big
	messageText.setCharacterSize(75);
	scoreText.setCharacterSize(100);

	// Position the text
	FloatRect textRect = messageText.getLocalBounds();
	messageText.setOrigin(textRect.left +
		textRect.width / 2.0f,
		textRect.top +
		textRect.height / 2.0f);
	messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);
	scoreText.setPosition(20, 20);
	
	//Prepate 6 branches
	Texture textureBranch;
	textureBranch.loadFromFile("graphics/branch.png");
	// Set the texture for each branch sprite
	for (int i = 0; i < NUM_BRANCHES; i++)
	{
		branches[i].setTexture(textureBranch);
		branches[i].setPosition(-2000, -2000);
		// Set the sprite's origin to dead center
		// We can then spin it round without changing its position
		branches[i].setOrigin(220, 40);
	}

	// Prepare the player
	Texture texturePlayer;
	texturePlayer.loadFromFile("graphics/player.png");
	Sprite spritePlayer;
	spritePlayer.setTexture(texturePlayer);
	spritePlayer.setPosition(580, 720);

	// The player starts on the left
	side playerSide = side::LEFT;

	//Prepare the gravestone
	Texture textureRIP;
	textureRIP.loadFromFile("graphics/rip.png");
	Sprite spriteRIP;
	spriteRIP.setTexture(textureRIP);
	spriteRIP.setPosition(600, 860);

	//Prepare the axe
	Texture textureAxe;
	textureAxe.loadFromFile("graphics/axe.png");
	Sprite spriteAxe;
	spriteAxe.setTexture(textureAxe);
	spriteAxe.setPosition(700, 830);

	// Line the axe up with the tree
	const float AXE_POSITION_LEFT = 700;
	const float AXE_POSITION_RIGHT = 1075;

	//Prepare the flying log
	Texture textureLog;
	textureLog.loadFromFile("graphics/log.png");
	Sprite spriteLog;
	spriteLog.setTexture(textureLog);
	spriteLog.setPosition(810, 720);

	// Some other useful log related variables
	bool logActive = false;
	float logSpeedX = 1000;
	float logSpeedY = -1500;

	
	/*
	******************************************
	Active Loop
	***************************************
	*/
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
	
		// Start the game
		if (Keyboard::isKeyPressed(Keyboard::Return) && paused == true)
		{
			paused = false;

			// reset the time and the score
			score = 0;
			timeRemaining = 6.0f;

			//essentially calling to get two calls in quick succession 
			//so that we don't have a potential 10 seconds of passed time since last game ended
			deltaTime = clock.restart();
			
		}
		
		/*
		******************************
		Update the Scene
		******************************
		*/

		if (!paused) 
		{
			//Measure time since last frame
			deltaTime = clock.restart();

			// Subtract from the amount of time remaining
			timeRemaining -= deltaTime.asSeconds();
			//size up the time bar
			timeBar.setSize(Vector2f(timeBarWidthPerSecond * timeRemaining, timeBarHeight));

			if (timeRemaining <= 0.0f)
			{
				//pause the game
				paused = true;

				// Change the message shown to the player
				messageText.setString("Out of time!!");

				// Reposition the text based on its new size
				FloatRect textRect = messageText.getLocalBounds();
				messageText.setOrigin(textRect.left +
					textRect.width / 2.0f,
					textRect.top +
					textRect.height / 2.0f);
				messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);
			}
			// Setup the bee
			if (!beeActive)
			{
				//How fast is the bee?
				srand((int)time(0) * 10);
				beeSpeed = (rand() % 200) + 200;

				//How high is the bee?
				srand((int)time(0) * 10);
				float height = (rand() % 500) + 500;
				spriteBee.setPosition(2000, height);
				beeActive = true;
			}

			else
				// Move the bee
			{

				spriteBee.setPosition(
					spriteBee.getPosition().x -
					(beeSpeed * deltaTime.asSeconds()),
					spriteBee.getPosition().y);

				//Has the bee reached the left hand edge of the screen?
				if (spriteBee.getPosition().x < -100)
				{
					//Set it back to inactive so it can be reset the next frame
					beeActive = false;
				}
			}

			// Manage the clouds
			//Cloud 1
			if (!cloud1Active)
			{
				//How fast is the cloud?
				srand((int)time(0) * 10);
				cloud1Speed = (rand() % 200) + 200;

				//How high is the cloud?
				srand((int)time(0) * 10);
				float height = (rand() % 150) + 150;
				spriteCloud1.setPosition(-200, height);
				cloud1Active = true;
			}

			else
			{
				spriteCloud1.setPosition(
					spriteCloud1.getPosition().x +
					(cloud1Speed * deltaTime.asSeconds()),
					spriteCloud1.getPosition().y);

				//Has the bee reached the right hand edge of the screen?
				if (spriteCloud1.getPosition().x > 1920)
				{
					//Set it back to inactive so it can be reset the next frame
					cloud1Active = false;
				}
			}

			// Manage the clouds
			//Cloud 2
			if (!cloud2Active)
			{
				//How fast is the cloud?
				srand((int)time(0) * 20);
				cloud2Speed = (rand() % 200) + 200;

				//How high is the cloud?
				srand((int)time(0) * 20);
				float height = (rand() % 300) + 300;
				spriteCloud2.setPosition(-200, height);
				cloud2Active = true;
			}

			else
			{
				spriteCloud2.setPosition(
					spriteCloud2.getPosition().x +
					(cloud2Speed * deltaTime.asSeconds()),
					spriteCloud2.getPosition().y);

				//Has the bee reached the right hand edge of the screen?
				if (spriteCloud2.getPosition().x > 1920)
				{
					//Set it back to inactive so it can be reset the next frame
					cloud2Active = false;
				}
			}

			// Manage the clouds
			//Cloud 3
			if (!cloud3Active)
			{
				//How fast is the cloud?
				srand((int)time(0) * 30);
				cloud3Speed = (rand() % 200) + 200;

				//How high is the cloud?
				srand((int)time(0) * 30);
				float height = (rand() % 450) + 450;
				spriteCloud3.setPosition(-200, height);
				cloud3Active = true;
			}

			else
			{
				spriteCloud3.setPosition(
					spriteCloud3.getPosition().x +
					(cloud3Speed * deltaTime.asSeconds()),
					spriteCloud3.getPosition().y);

				//Has the cloud
				if (spriteCloud3.getPosition().x > 1920)
				{
					//Set it back to inactive so it can be reset the next frame
					cloud3Active = false;
				}
			}

			//Update the score text
			std::stringstream ss;
			ss << "Score = " << score;
			scoreText.setString(ss.str());
			
			// update the branch sprites
			for (int i = 0; i < NUM_BRANCHES; i++)
			{
				float height = i * 150;
				if (branchPositions[i] == side::LEFT)
				{
					// Move the sprite to the left side
					branches[i].setPosition(610, height);
					// Flip the sprite round the other way
					branches[i].setRotation(180);
				}
				else if (branchPositions[i] == side::RIGHT)
				{
					// Move the sprite to the right side
					branches[i].setPosition(1330, height);
					//set the sprite rotation to normal
					branches[i].setRotation(0);
				}
				else
				{
					// Hide the branches
					branches[i].setPosition(3000, height);
				}
			}
		} // End if(!paused)
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

		// Draw the branches
		for (int i = 0; i < NUM_BRANCHES; i++)
		{
			window.draw(branches[i]);
		}

		// Draw the tree
		window.draw(spriteTree);

		// Draw the insect
		window.draw(spriteBee);

		// Draw score
		window.draw(scoreText);

		// Draw the timebar
		window.draw(timeBar);

		if (paused)
		{
		
			//Draw our message
			window.draw(messageText);
		}

		//Show everything we just drew
		window.display();



	}//End while (window.isopen()) loop

	return 0;
}

/*
********************************
Function definitions
***********************************
*/

void updateBranches(int seed)
{
	// Move all the branches down one place
	for (int j = NUM_BRANCHES - 1; j > 0; j--)
	{
		branchPositions[j] = branchPositions[j - 1];
	}
	// Spawn a new branch at position 0
	//LEFT, RIGHT or NONE
	srand((int)time(0) + seed);
	int r = (rand()% 5);
	switch (r)
	{
	case 0:
		branchPositions[0] = side::LEFT;
		break;
	case 1:
		branchPositions[0] = side::LEFT;
		break;
	default:
		branchPositions[0] = side::NONE;
		break;
	}

		
}
