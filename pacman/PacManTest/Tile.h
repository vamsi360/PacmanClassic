
#include <SFML/Graphics.hpp>

const int GRID_X = 32;
const int GRID_Y = 24;

class Tile
{
private:
	sf::Sprite mySprite;
	sf::Sprite baseSprite;
	sf::Sprite upSprite;
	sf::Sprite gridSprite; //sprite for the grid
	sf::Sprite dotSprite; //sprite for the food(dot)
	sf::Sprite arrGridSprite[GRID_Y][GRID_X]; //sprite for the entire grid
	sf::Sprite blackSprite; //sprite for the empty black image

	int** arrGrid; //for grid
	int** arrDotGrid; //for food or dot

public:
	Tile(sf::Image& image, sf::Image& imageUp, sf::Image& imageGrid, sf::Image& imageDotGrid, sf::Image& imageBlack, sf::RenderWindow *rw);
	~Tile();
	
	void Draw(int x, int y, sf::RenderWindow* rw);

	void Move(int x, int y, sf::RenderWindow* rw);

	sf::Vector2f GetBaseSpritePos();
};
