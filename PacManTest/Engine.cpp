
#include "Engine.h"

Engine::Engine()
{

}

Engine::~Engine()
{

} 

bool Engine::Init()// It Initializes the window by 800x600 resolution with a black backgound
{
	window = new sf::RenderWindow(sf::VideoMode(800, 600, 32), "PacMan@IIITB");

	if(!window)
		return false;

	LoadImages();// The references of the images is taken up by object known as Spirite

	return true;
}

void Engine::RenderFrame()
{
	window->Clear();// Clear the Window
	testTile->Draw(0, 0, window);// Draw the window with the new configuration
	window->Display();// Display the Window 
}

void Engine::ProcessInput()
{
	sf::Event evt;

	//Looping through window events
	while(window->GetEvent(evt))
	{
		//If Close Event
		if(evt.Type == sf::Event::Closed)
			window->Close();

		//Escape pressed => Close the Window
		if(evt.Type == sf::Event::KeyPressed && evt.Key.Code == sf::Key::Escape)
			window->Close();

		if(evt.Type == sf::Event::KeyPressed && evt.Key.Code == sf::Key::Left)
		{
			int x = testTile->GetBaseSpritePos().x;
			int y = testTile->GetBaseSpritePos().y;

			testTile->Move(-imgWidth, 0, window);// When left key is Pressed move the Pacman left equal to its width
		}

		if(evt.Type == sf::Event::KeyPressed && evt.Key.Code == sf::Key::Right)
		{
			int x = testTile->GetBaseSpritePos().x;
			int y = testTile->GetBaseSpritePos().y;

			testTile->Move(imgWidth, 0, window);
		}
		//Move the Pacman up when up arrow is pressed equal to its height
		if(evt.Type == sf::Event::KeyPressed && evt.Key.Code == sf::Key::Up)
		{
			int x = testTile->GetBaseSpritePos().x;
			int y = testTile->GetBaseSpritePos().y;

			testTile->Move(0, -imgHeight, window);
		}
		// Move the PacMan down when down key is pressed equal to its height
		if(evt.Type == sf::Event::KeyPressed && evt.Key.Code == sf::Key::Down)
		{
			int x = testTile->GetBaseSpritePos().x;
			int y = testTile->GetBaseSpritePos().y;

			testTile->Move(0, imgHeight, window);
		}
	}

}

void Engine::Update()
{
	
}

void Engine::MainLoop()
{
	//Loop until the App (=>window) is closed
	while(window->IsOpened())
	{
		ProcessInput();
		Update();
		RenderFrame();
	}
}

void Engine::LoadImages()
{
	sf::Image imgRight;// Pacman with image pointing towards right
	if(!imgRight.LoadFromFile("pacman.png"))
		throw "Unable to load image";

	imgWidth = imgRight.GetWidth();// Get the width of the Pacman
	//imgWidth = imgWidth * window->GetFrameTime();
	imgHeight = imgRight.GetHeight();// Get the height of the Pacman
	//imgHeight = imgHeight * window->GetFrameTime();

	imageManager.AddImage(imgRight);// Add this image

	sf::Image imgUp; // Pacman with the image pointing upwards
	if(!imgUp.LoadFromFile("pacmanUp.png"))
		throw "Unable to load image";

	imageManager.AddImage(imgUp);

	sf::Image imgGrid;// Load the image of the Grid
	if(!imgGrid.LoadFromFile("blue.png"))
		throw "Unable to load image";

	imageManager.AddImage(imgGrid);

	sf::Image imgDotGrid;// Load the image of the Grid
	if(!imgDotGrid.LoadFromFile("dot.png"))
		throw "Unable to load image";

	imageManager.AddImage(imgDotGrid);

	sf::Image imgBlack;// Load the image of the Grid
	if(!imgBlack.LoadFromFile("black.png"))
		throw "Unable to load image";

	imageManager.AddImage(imgBlack);

	testTile = new Tile(imageManager.GetImage(0), imageManager.GetImage(1), imageManager.GetImage(2), imageManager.GetImage(3), imageManager.GetImage(4), window);
}

void Engine::Go()
{
	if(!Init())
		throw "Could not initialize Engine";
	
	MainLoop();
}