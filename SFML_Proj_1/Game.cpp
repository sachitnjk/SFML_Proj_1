#include "Game.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <random>
#include "MathHelpers.h"

Game::Game()
	: m_Window(sf::VideoMode(1920, 1080), "First SFML Project")
	, eGameMode(Play)
{

	enemy_Texture.loadFromFile("Images/Enemy.png");
	enemy_Sprite.setTexture(enemy_Texture);
	enemy_Sprite.setScale(sf::Vector2f(10, 10));
	enemy_Sprite.setPosition(sf::Vector2f(960, 540));
	enemy_Sprite.setOrigin(sf::Vector2f(8, 8));

	player_Texture;
	player_Texture.loadFromFile("Images/Player.png");
	player_Sprite.setTexture(player_Texture);
	player_Sprite.setScale(sf::Vector2f(10, 10));
	player_Sprite.setOrigin(sf::Vector2f(8, 8));


	axe_Texture;
	axe_Texture.loadFromFile("Images/Axe.png");
	axe_Sprite.setTexture(axe_Texture);
	axe_Sprite.setScale(sf::Vector2f(10, 10));
	axe_Sprite.setOrigin(sf::Vector2f(8, 8));

}

Game::~Game()
{

}

void Game::Run()
{
	//sf::RenderWindow window;
	sf::Clock clock;
	while (m_Window.isOpen())
	{
		m_DeltaTime = clock.restart();

		switch (eGameMode)
		{
		case Play:
			UpdatePlay();
		case LevelEditor:
			UpdateLevelEditor();
		}

		Draw();

		sf::Event event;
		while (m_Window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				m_Window.close();
			}
		}

	}

}

void Game::UpdatePlay()
{
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
		player_Sprite.move(requestedPlayerMovement * m_DeltaTime.asSeconds() * fPlayerSpeed);

		//axe related movemtn asn stuff after player movemnt
		sf::Vector2f mousePosition = (sf::Vector2f)sf::Mouse::getPosition(m_Window);
		sf::Vector2f playerToMouse = mousePosition - player_Sprite.getPosition();
		sf::Vector2f playerToMouseNormalized = MathHelpers::Normalize(playerToMouse);
		axe_Sprite.setPosition(player_Sprite.getPosition() + playerToMouseNormalized * 160.0f);

		//Did axe hit enemy check
		sf::Vector2f vAxeToEnemy = enemy_Sprite.getPosition() - axe_Sprite.getPosition();
		float fLengthFromAxeToEnemy = MathHelpers::Length(vAxeToEnemy);

		if (fLengthFromAxeToEnemy < 160.0f)
		{
			//The axe hits the enemy, the enemy is moved to another(random) point (illusion of respawning enemy)
			sf::Vector2f vNewEnemyPos(std::rand() % 1920, std::rand() % 1080);
			enemy_Sprite.setPosition(vNewEnemyPos);
		}

		sf::Vector2f vEnemyToPlayer = player_Sprite.getPosition() - enemy_Sprite.getPosition();
		vEnemyToPlayer = MathHelpers::Normalize(vEnemyToPlayer);
		float fEnemySpeed = 150.0f;
		enemy_Sprite.move(vEnemyToPlayer * m_DeltaTime.asSeconds() * fEnemySpeed);

		m_Window.clear();
		m_Window.draw(enemy_Sprite);
		m_Window.draw(player_Sprite);
		m_Window.draw(axe_Sprite);
		m_Window.display();
}

void Game::UpdateLevelEditor()
{
	return;
}

void Game::Draw()
{
	m_Window.clear();
	m_Window.draw(enemy_Sprite);
	m_Window.draw(player_Sprite);
	m_Window.draw(axe_Sprite);
	m_Window.display();
}