

#include <SFML/Graphics.hpp>

#include "ImageManager.h"
#include "Tile.h"

class Engine
{
private:
	//SFML Render Window
	sf::RenderWindow* window;

	//ImageManager
	ImageManager imageManager;

	//Image width, height;
	int imgWidth, imgHeight;

	//Create a Tile
	Tile* testTile;

	//Initialize the Game Engine
	bool Init();

	//Game Loop
	void MainLoop();

	//Render one frame
	void RenderFrame();

	//Process user Input
	void ProcessInput();

	//Update Engine
	void Update();

	//Load Images
	void LoadImages();

public:
	Engine();
	~Engine();

	//Start the Engine
	void Go();
};