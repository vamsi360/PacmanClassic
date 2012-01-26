
#include <vector>
#include <SFML/Graphics.hpp>

class ImageManager
{
private:
	std::vector<sf::Image> imageList;

public:
	ImageManager();
	~ImageManager();

	void AddImage(sf::Image& image);
	sf::Image& GetImage(int index);
};
