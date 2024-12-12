#include <iostream>
#include <SFML/Graphics.hpp>
#include <random>

float Length(const sf::Vector2f& rVector)
{
	float fLength = sqrt(rVector.x * rVector.x + rVector.y * rVector.y);
	return fLength;
}

sf::Vector2f Normalize(const sf::Vector2f& rVector)
{
	float vectorLength = Length(rVector);
	sf::Vector2f normalizedVector(rVector.x / vectorLength, rVector.y / vectorLength);
	return normalizedVector;
}


int main()
{
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "First SFML Project");

	sf::Texture enemyTexture;
	enemyTexture.loadFromFile("Images/Enemy.png");
	sf::Sprite enemy(enemyTexture);
	enemy.setScale(sf::Vector2f(10, 10));
	enemy.setPosition(sf::Vector2f(960, 540));
	enemy.setOrigin(sf::Vector2f(8, 8));

	sf::Texture playerTexture;
	playerTexture.loadFromFile("Images/Player.png");
	sf::Sprite player(playerTexture);
	player.setScale(sf::Vector2f(10, 10));
	player.setOrigin(sf::Vector2f(8, 8));


	sf::Texture axeTexture;
	axeTexture.loadFromFile("Images/Axe.png");
	sf::Sprite axe(axeTexture);
	axe.setScale(sf::Vector2f(10, 10));
	axe.setOrigin(sf::Vector2f(8, 8));

	sf::Clock clock;

	while (window.isOpen())
	{
		sf::Time timeSincelastFrame = clock.restart();

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}


		sf::Vector2f requestedPlayerMovement(0.0f, 0.0f);
		float fPlayerSpeed = 200;
		//Player Input detection
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			requestedPlayerMovement += sf::Vector2f(0.0f, -1.0f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			requestedPlayerMovement += sf::Vector2f(-1.0f, 0.0f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			requestedPlayerMovement += sf::Vector2f(0.0f, 1.0f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			requestedPlayerMovement += sf::Vector2f(1.0f, 0.0f);
		}
		
		//PlayerMovement
		player.move(requestedPlayerMovement * timeSincelastFrame.asSeconds() * fPlayerSpeed);

		//axe related movemtn asn stuff after player movemnt
		sf::Vector2f mousePosition = (sf::Vector2f)sf::Mouse::getPosition(window);
		sf::Vector2f playerToMouse = mousePosition - player.getPosition();
		sf::Vector2f playerToMouseNormalized = Normalize(playerToMouse);
		axe.setPosition(player.getPosition() + playerToMouseNormalized * 160.0f);

		//Did axe hit enemy check
		sf::Vector2f vAxeToEnemy = enemy.getPosition() - axe.getPosition();
		float fLengthFromAxeToEnemy = Length(vAxeToEnemy);

		if (fLengthFromAxeToEnemy < 160.0f)
		{
			//The axe hits the enemy, the enemy is moved to another(random) point (illusion of respawning enemy)
			sf::Vector2f vNewEnemyPos(std::rand() % 1920, std::rand() % 1080);
			enemy.setPosition(vNewEnemyPos);
		}

		window.clear();
		window.draw(enemy);
		window.draw(player);
		window.draw(axe);
		window.display();
	}

	return 0;
}
