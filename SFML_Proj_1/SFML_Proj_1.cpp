#include <iostream>
#include <SFML/Graphics.hpp>

int main()
{
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "First SFML Project");

	sf::Texture playerTexture;
	sf::Texture enemyTexture;
	playerTexture.loadFromFile("Images/Player.png");
	enemyTexture.loadFromFile("Images/Enemy.png");

	sf::Sprite player(playerTexture);
	sf::Sprite enemy(enemyTexture);

	player.setScale(sf::Vector2f(10, 10));
	enemy.setScale(sf::Vector2f(10, 10));

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		window.clear();
		window.draw(player);
		window.draw(enemy);
		window.display();
	}

	return 0;
}
