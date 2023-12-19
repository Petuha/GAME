#include "Picture.h"
using namespace std;
using namespace sf;
Picture::Picture(float x, float y, float width, float height, Texture* texture)
{
	shape.setPosition(Vector2f(x, y));
	shape.setSize(Vector2f(width, height));
	shape.setTexture(texture);
}

Picture& Picture::setPosition(float x, float y)
{
	shape.setPosition(Vector2f(x, y));
	return *this;
}

Picture& Picture::render(RenderWindow& window)
{
	window.draw(shape);
	return *this;
}
