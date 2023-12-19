#include "button.h"
#include <stdexcept>
#include <iostream>
using namespace std;
using namespace sf;

Button::Button(float x, float y, float width, float height, Font* font, const wstring& text,
	unsigned int character_size, vector<Keyboard::Key> binds, const Color& text_color,
	const Color& main_color, const Color& aimed_color, const Color& pressed_color) {
	state = Button_state::main;
	prevstate = state;
	this->binds = std::move(binds);
	shape.setPosition(Vector2f(x, y));
	shape.setSize(Vector2f(width, height));
	shape.setFillColor(main_color);
	this->font = font;
	this->text.setFont(*font);
	this->text.setString(text);
	this->text.setFillColor(text_color);
	this->text.setCharacterSize(character_size);
	this->text.setPosition(Vector2f(
		x + (width - this->text.getGlobalBounds().width) / 2.f,
		y + (height - this->text.getGlobalBounds().height) / 2.5f
	));
	this->main_color = main_color;
	this->aimed_color = aimed_color;
	this->pressed_color = pressed_color;
}


bool Button::bindpressed()
{
	if (!binds.size()) return 0;
	for (auto& now : binds) {
		if (!Keyboard::isKeyPressed(now)) return 0;
	}
	return 1;
}

Button& Button::update(RenderWindow& window) {
	prevstate = state;
	state = Button_state::main;
	Vector2i vi = Mouse::getPosition(window);
	Vector2f vf(static_cast<float>(vi.x), static_cast<float>(vi.y));
	if (shape.getGlobalBounds().contains(vf)) {
		state = Button_state::aimed;
		if (Mouse::isButtonPressed(Mouse::Left)) {
			state = Button_state::pressed;
		}
	}
	if (bindpressed()) state = Button_state::pressed;
	switch (state) {
	case Button_state::main:
		shape.setFillColor(main_color);
		break;
	case Button_state::aimed:
		shape.setFillColor(aimed_color);
		break;
	case Button_state::pressed:
		shape.setFillColor(pressed_color);
		break;
	default:
		break;
	}
	return *this;
}

Button& Button::render(RenderWindow& window) {
	window.draw(shape);
	window.draw(text);
	return *this;
}

bool Button::is_pressed() {
	return state != Button_state::pressed && prevstate == Button_state::pressed;
}
Button::~Button() {

}