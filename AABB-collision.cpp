#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include<math.h>
#define screenHeight 800
#define screenWidth 800
sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "AABB", sf::Style::Close | sf::Style::Resize);
using namespace std;
using namespace sf;
int main()
{
	sf::Font font;
	font.loadFromFile("Pangolin.ttf");
	sf::Clock clock;
	float deltaTime;
	RectangleShape Ox;
	RectangleShape Oy;
	RectangleShape block1(Vector2f(100, 200));
	block1.setOrigin(block1.getSize() / 2.0f);
	block1.setOutlineColor(Color::White);
	block1.setOutlineThickness(2.0f);
	block1.setFillColor(Color::Red);

	RectangleShape block2(Vector2f(200, 100));
	block2.setOrigin(block2.getSize() / 2.0f);
	block2.setOutlineColor(Color::White);
	block2.setOutlineThickness(2.0f);
	block2.setFillColor(Color::Blue);

	float deltaX,deltaY,distanceX,distanceY;
	Vector2f mouse;
	while (window.isOpen())
	{
		mouse = (Vector2f)Mouse::getPosition(window);
		deltaTime = clock.restart().asSeconds();
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		//update

		//Ox
		deltaX =abs(block1.getPosition().x - block2.getPosition().x) - block1.getSize().x / 2 - block2.getSize().x / 2;
		distanceX = abs(deltaX);
		Ox.setSize(Vector2f(deltaX,5.0f));
		Ox.setOrigin(Ox.getSize() / 2.0f);

		if(min(block1.getPosition().x, block2.getPosition().x)== block1.getPosition().x)
		Ox.setPosition(distanceX / 2+block1.getPosition().x+block1.getSize().x/2.0f, 50);
		else
		Ox.setPosition(distanceX / 2 +block2.getPosition().x + block2.getSize().x / 2.0f, 50);
		
		if (deltaX <= 0) Ox.setFillColor(Color::Red);
		else Ox.setFillColor(Color::Green);

		//Oy
		deltaY = abs(block1.getPosition().y - block2.getPosition().y) - block1.getSize().y / 2 - block2.getSize().y / 2;
		distanceY = abs(deltaY);
		Oy.setSize(Vector2f( 5.0f,deltaY));
		Oy.setOrigin(Oy.getSize() / 2.0f);

		if (min(block1.getPosition().y, block2.getPosition().y) == block1.getPosition().y)
			Oy.setPosition(50,distanceY / 2 + block1.getPosition().y + block1.getSize().y / 2.0f);
		else
			Oy.setPosition(50,distanceY / 2 + block2.getPosition().y + block2.getSize().y / 2.0f);

		if (deltaY <= 0) Oy.setFillColor(Color::Red);
		else Oy.setFillColor(Color::Green);

		//Block	
		if (block1.getGlobalBounds().contains(mouse))
		{

			if (Mouse::isButtonPressed(Mouse::Left))
			{
				block1.setFillColor(Color(255, 46, 46));
				block1.move(10*deltaTime*(mouse - block1.getPosition()));
			}
			else block1.setFillColor(Color::Red);
		}
		if (block2.getGlobalBounds().contains(mouse))
		{
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				block2.setFillColor(Color(46, 46, 255));
				block2.move(10*deltaTime*(mouse - block2.getPosition()));
			}
			else block2.setFillColor(Color::Blue);
		}
		//draw
		window.clear();
		window.draw(block1);
		window.draw(block2);
		window.draw(Ox);
		window.draw(Oy);
		window.display();
	}

	return 0;
}