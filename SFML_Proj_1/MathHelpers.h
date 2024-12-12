#include <SFML/Graphics.hpp>

namespace MathHelpers
{
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
}

