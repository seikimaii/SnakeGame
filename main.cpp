#include <SFML/Graphics.hpp>
#include <iostream>
#include <string> 

void changefood(sf::Vector2i& food , int x,int y) {
	food = sf::Vector2i(rand() % x, rand() % y);
}

int main() {
	sf::Font font;
	if (!font.loadFromFile("calibri.ttf")) {
		return EXIT_FAILURE;
	}
	sf::Text point("Point:", font);
	int counter = 0;
	float speed = 0.6f;
	sf::Texture texture;
	if (!texture.loadFromFile("block.png")) {
		return EXIT_FAILURE;
	}
	sf::Sprite block(texture); 
	
	sf::Vector2i G_windowSize(20, 20);
	sf::Vector2f blockSize(block.getLocalBounds().width, block.getLocalBounds().height);
	

	std::vector<sf::Vector2i> snake = { sf::Vector2i(4, 6) };
	srand((unsigned int)time(NULL));
	sf::Vector2i food(rand() % G_windowSize.x, rand() % G_windowSize.y);

	
	
	sf::VideoMode mode(
		unsigned int(G_windowSize.x * blockSize.x), 
		unsigned int(G_windowSize.y * blockSize.y));
	sf::RenderWindow window(mode, L"³g­¹³D");

	enum class Direction { left, right, up, down };
	Direction direction = Direction::right;
	
	sf::Clock clock;
	sf::Event evt;
	bool isDead = false;
	while (window.isOpen()) {

		if (window.pollEvent(evt)) {
			if (evt.type == sf::Event::Closed) {
				window.close();
			}
			if (evt.type == sf::Event::KeyPressed) {
				if (evt.key.code == 71) {
					direction = Direction::left;
				}
				else if (evt.key.code == 72) {
					direction = Direction::right;
				}
				else if (evt.key.code == 73) {
					direction = Direction::up;
				}
				else if (evt.key.code == 74) {
					direction = Direction::down;
				}
			}
		}
		if (counter > 3) {
			speed = 0.5f;
		}
		if (counter > 6) {
			speed = 0.4f;
		}
		if (counter > 9) {
			speed = 0.3f;
		}
		if (clock.getElapsedTime().asSeconds() > speed) {
			sf::Vector2i snake_head = snake[0];

			if (direction == Direction::left) {
				snake_head.x--;
			}
			else if (direction == Direction::right) {
				snake_head.x++;
			}
			else if (direction == Direction::up) {
				snake_head.y--;
			}
			else if (direction == Direction::down) {
				snake_head.y++;
			}
			if (snake_head.x < 0 || snake_head.x >= G_windowSize.x ||
				snake_head.y < 0 || snake_head.y >= G_windowSize.y) {
				isDead = true;
			}
			if (!isDead) {
				if (snake_head == food) {
					changefood(food, G_windowSize.x, G_windowSize.y);
					counter++;
				}
				else {
					snake.pop_back();
				}
				snake.insert(snake.begin(), snake_head);
			}
		clock.restart();
		}
		if (isDead) {
			window.clear(sf::Color::Red);
			if (evt.type == sf::Event::KeyPressed) {
				isDead = false;
				changefood(food, G_windowSize.x, G_windowSize.y);
				snake = { sf::Vector2i(4, 6) };
				counter = 0;
				direction = Direction::right;
			}

		}
		else {
			window.clear();
		}
		
		for (const auto& body : snake) {
			sf::Vector2f snakepos(
				body.x* blockSize.x, 
				body.y* blockSize.y);
			block.setPosition(snakepos);
			window.draw(block);
		}
		sf::Text point_value(std::to_string(counter), font);
		point_value.setPosition(point.getLocalBounds().width+5, 0.f);
		window.draw(point);
		window.draw(point_value);
		
		sf::Vector2f foodpos(food.x* blockSize.x, food.y* blockSize.y);
		block.setPosition(foodpos);

		window.draw(block);
		window.display();
	}
	return EXIT_SUCCESS;
}