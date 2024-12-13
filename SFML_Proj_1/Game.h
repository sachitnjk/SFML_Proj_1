#include <SFML/Graphics.hpp>

class Game
{
public:

	Game();
	~Game();

	enum GameMode
	{
		Play,
		LevelEditor
	};

	//bool Update();
	void Run();

private:

	void UpdatePlay();
	void UpdateLevelEditor();
	void Draw();

private:

	sf::RenderWindow m_Window;
	sf::Time m_DeltaTime;
	GameMode eGameMode;

	sf::Sprite player_Sprite;
	sf::Sprite enemy_Sprite;
	sf::Sprite axe_Sprite;

	sf::Texture player_Texture;
	sf::Texture enemy_Texture;
	sf::Texture axe_Texture;
};

