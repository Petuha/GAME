#pragma once
#include <SFML/Graphics.hpp>
class Picture
{
private:
	sf::RectangleShape shape;
public:
	Picture(float x = 0, float y = 0, float width = 0, float height = 0, sf::Texture* texture = 0);
	Picture& setPosition(float x, float y);
	Picture& render(sf::RenderWindow& window);
};