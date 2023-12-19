#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
enum class Button_state {
	main, aimed, pressed
};
class Button {
protected:
	sf::RectangleShape shape;
	Button_state state;
	Button_state prevstate;
	sf::Text text;
	sf::Color main_color;
	sf::Color aimed_color;
	sf::Color pressed_color;
	sf::Font* font;
	std::vector<sf::Keyboard::Key> binds;
	bool bindpressed();
public:
	Button(float x = 0, float y = 0, float width = 10, float height = 10, sf::Font* font = 0,
		const std::wstring& text = L"",
		unsigned int character_size = 12, std::vector<sf::Keyboard::Key> binds = {},
		const sf::Color& text_color = sf::Color::Black,
		const sf::Color& main_color = sf::Color::White, const sf::Color& aimed_color = sf::Color(160, 160, 160),
		const sf::Color& pressed_color = sf::Color(96, 96, 96)
	);
	Button& update(sf::RenderWindow& window);
	Button& render(sf::RenderWindow& window);
	bool is_pressed();
	~Button();
};