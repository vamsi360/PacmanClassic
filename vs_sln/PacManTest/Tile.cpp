
#include "Tile.h"

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>

#include <SFML/Graphics.hpp>

Tile::Tile(sf::Image& image, sf::Image& imageUp, sf::Image& imageGrid, sf::Image& imageDotGrid, sf::Image& imageBlack, sf::RenderWindow* rw)
{
	baseSprite.SetImage(image);// ImageRight of the PacMan
	upSprite.SetImage(imageUp);// ImageUp of the PacMan
	gridSprite.SetImage(imageGrid);// Image of the Grid
	dotSprite.SetImage(imageDotGrid); //Image of the dot, food
	blackSprite.SetImage(imageBlack); //Image of empty after food is taken

	mySprite = baseSprite;// ImageRight of the PacMan
	mySprite.SetPosition(800-75, 600-75);// Set the initial position of the PacMan
	rw->Draw(mySprite);

	arrGrid = (int**)malloc(sizeof(int)*GRID_Y);// 2-Dimension Array to form the Grid
	arrDotGrid = (int**)malloc(sizeof(int)*GRID_Y);

	for(int i=0; i<GRID_Y; i++)
	{
		arrGrid[i] = (int*)malloc(sizeof(int)*GRID_X);
		arrDotGrid[i] = (int*)malloc(sizeof(int)*GRID_X);
	}

	// 0 stands for empty slot of the grid and 1 stands for Grid present in that Slot
	int i, j;
	i = 0, j = 0;
	std::string line;
	std::ifstream myFile("grid.txt");// 0 and 1 which essentially fills the 2-Dimension array
	if(myFile.is_open())
	{
		while(myFile.good())
		{
			getline(myFile, line);
			for(j=0; j<GRID_X; j++)
			{
				arrGrid[i][j] = (int)line[j] - 48;
			}
			i++;
		}
	}

	for(i=0; i<GRID_Y; i++)
	{
		for(j=0; j<GRID_X; j++)
		{
			if(arrGrid[i][j] == 1)
			{
				arrDotGrid[i][j] = 0;
				arrGridSprite[i][j] = gridSprite;
			}
			else 
			{
				arrDotGrid[i][j] = 1;
				arrGridSprite[i][j] = dotSprite;
			}
					
			std::cout<<arrGrid[i][j]<<" ";
		}		
		std::cout<<std::endl;
	}

	for(i=0; i<GRID_Y; i++)
	{
		for(j=0; j<GRID_X; j++) 
		{
			arrGridSprite[i][j].SetPosition(j*25, i*25);
			if(arrGrid[i][j] == 1)
			{
				gridSprite.SetPosition(j*25, i* 25);// Draw the Grid
				arrGridSprite[i][j] = gridSprite;

				arrDotGrid[i][j] = 0; //when there is a grid, there is no dot
			}
			else 
			{
				dotSprite.SetPosition(j*25, i*25);
				arrGridSprite[i][j] = dotSprite;
				arrDotGrid[i][j] = 1; //when there is no grid, there is a dot
			}

			rw->Draw(arrGridSprite[i][j]);
		}
	}

	mySprite = baseSprite;// ImageRight of the PacMan
	mySprite.SetPosition(800-75, 600-75);// Set the initial position of the PacMan
	arrGridSprite[525/25][725/25] = mySprite;
	rw->Draw(arrGridSprite[525/25][725/25]);
}

Tile::~Tile()
{
	baseSprite.SetPosition(50, 50);
	upSprite.SetPosition(50, 50);
}

void Tile::Draw(int x, int y, sf::RenderWindow* rw)
{
	//baseSprite.SetPosition(x, y);
	//rw->Draw(mySprite);
	int i, j;
	for(i=0; i<GRID_Y; i++)// 
	{
		for(j=0; j<GRID_X; j++)
		{
			rw->Draw(arrGridSprite[i][j]);
		}
	}	

}

void Tile::Move(int x, int y, sf::RenderWindow* rw)
{	
	if(x > 0) 
	{
		baseSprite.SetPosition(mySprite.GetPosition());
		mySprite = baseSprite;
		//baseSprite.FlipX(true);// Rotate the baseSprite
	}
	else if(x < 0) 
	{
		baseSprite.SetPosition(mySprite.GetPosition());
		mySprite = baseSprite;
		mySprite.FlipX(true);// Don't rotate the baseSprite because initially the baseSprite is RightPacMan
	}
	else if(y < 0) 
	{
		upSprite.SetPosition(mySprite.GetPosition());
		mySprite = upSprite;
	}
	else 
	{
		upSprite.SetPosition(mySprite.GetPosition());
		mySprite = upSprite;
		mySprite.FlipY(true);
	}

	int xpos, ypos;
	xpos = mySprite.GetPosition().x + x;// New x position of the PacMan to be moved
	ypos = mySprite.GetPosition().y + y;// New y position of the PacMan to be moved

	int xval, yval;
	int xprev, yprev;
	int xPrevPos, yPrevPos;
	xPrevPos = mySprite.GetPosition().x;
	yPrevPos = mySprite.GetPosition().y;

	int xset, yset; //temporary x, y values of the moved position.
	bool flagMove = false; //flag for setting if pacman moved
	bool flagStuck = false; //flag when pacman is stuck with grid border

	if(xpos < GRID_X * 25) {// 32*24=768
		if(ypos < GRID_Y * 25) {// 24*25=600
			if(xpos >= 0) {// The range of x and y should be within the dimension of 768*600
				if(ypos >= 0) {					
					xval = (xpos)/25;
					yval = (ypos)/25;
					xprev = xPrevPos/25;
					yprev = yPrevPos/25;

					if(arrGrid[yval][xval] != 1)// If there is no Grid Move the PacMan
					{
						blackSprite.SetPosition(xPrevPos, yPrevPos);
						arrGridSprite[yprev][xprev] = blackSprite;
						rw->Draw(arrGridSprite[yprev][xprev]);
						flagMove = true;
						mySprite.Move(x, y);
			
						xset = xpos;
						yset = ypos;
						
						std::cout <<  "=> " << xpos/25 << " " << ypos/25 <<std::endl;
					}
					else 
					{
						flagStuck = true;
						xset = xprev;
						yset = yprev;
					}
				}
				else {
					xset = xpos;
					yset = 0;					
				}
			}
			else {
				if(ypos >=0)// PacMan is moving beyond x position and there is no grid so PacMan can come from the right
				{
					xset = (GRID_X-1)*25;
					yset = ypos;					
				}
				else 
				{
					xset = 0;
					yset = 0;					
				}
			}
		}
		else {
			if(xpos >= 0)
			{
				xset = xpos;
				yset = (GRID_Y-1)*25;				
			}
			else 
			{
				xset = 0;
				yset = (GRID_Y-1)*25;				
			}
		}
	}
	else {
		if(ypos < GRID_Y * 25)
		{
			xset = 0;
			yset = ypos;			
		}
		else 
		{
			xset = (GRID_X-1)*25;
			yset = (GRID_Y-1)*25;			
		}
	}

	
	if(!flagStuck) 
	{
		if(!flagMove) mySprite.SetPosition(xset, yset);
		arrGridSprite[yset/25][xset/25] = mySprite;
		arrDotGrid[yset/25][xset/25] = 0;
		rw->Draw(arrGridSprite[yset/25][xset/25]);
	}
	
}

sf::Vector2f Tile::GetBaseSpritePos()
{
	return baseSprite.GetPosition();
}