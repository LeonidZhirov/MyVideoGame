#include "Game.h"

/*class SpriteManager {//это задел на следующие уроки,прошу не обращать внимания на эти изменения)
public:
	sf::Image image;
	sf::Texture texture;
	sf::Sprite sprite;
	sf::String name;
	sf::String file;
	int widthOfSprite;
	int heightOfSprite;
	SpriteManager(sf::String File, sf::String Name) {
		file = File;
		name = Name;
		image.loadFromFile("images/" + file);
		texture.loadFromImage(image);
		sprite.setTexture(texture);
	}
};*/


int main()
{
	/*sf::RenderWindow window(sf::VideoMode(640, 480), "Lesson 20. kychka-pc.ru");
	view.reset(sf::FloatRect(0, 0, 640, 480));

	sf::Image map_image;
	map_image.loadFromFile("images/OverWorld.png");
	sf::Texture map;
	map.loadFromImage(map_image);
	sf::Sprite s_map;
	s_map.setTexture(map);
	s_map.setScale(2.f, 2.f);

	SpriteManager playerSprite("hero.png", "Hero");//это задел на следующие уроки,прошу не обращать внимания)

	Player player("Mario.png", 250.f, 500.f, 32.f, 32.f);

	sf::Clock clock;*/

	Game game;
	game.isWorking();

	return 0;
}