#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h>
#include <time.h>

#include <Object.hpp>

int main()
{
	// window - randerTarget
	sf::RenderWindow window(sf::VideoMode(640, 480), "Title", sf::Style::Titlebar | sf::Style::Close);
	unsigned FPS = 60;
	window.setFramerateLimit(FPS);
	
	// event's and actions related
	sf::Event event;
	bool pause = false;
	bool mouseClicked = false;
	bool radiusSet = false;
	sf::Vector2f oldPosition;
	sf::CircleShape tmpObject = sf::CircleShape(0);
	srand(time(NULL));
	
	// all the objects on the scene
	std::vector<Object*> objects;
	
	// objects.push_back(new Object(sf::Vector2f(100, 100), sf::Vector2f(2, 0), 300, 30, sf::Color(0, 255, 0), &window, &objects));
	// objects.push_back(new Object(sf::Vector2f(300, 300), sf::Vector2f(-0.3f, 0), 300, 30, sf::Color(0, 255, 0), &window, &objects));
	// objects.push_back(new Object(sf::Vector2f(100, 300), sf::Vector2f(0, -1), 300, 30, sf::Color(0, 255, 0), &window, &objects));
	
	// system
	objects.push_back(new Object(sf::Vector2f(390, 300), sf::Vector2f(0, 2.4f), 0.0025f, 10, sf::Color(0, 255, 0), &window, &objects));
	objects.push_back(new Object(sf::Vector2f(350, 300), sf::Vector2f(0, -3.5f), 0.0025f, 10, sf::Color(0, 255, 255), &window, &objects));
	objects.push_back(new Object(sf::Vector2f(190, 300), sf::Vector2f(0, 2.031f), 0.5f, 10, sf::Color(255, 255, 0), &window, &objects));
	objects.push_back(new Object(sf::Vector2f(480, 300), sf::Vector2f(0, 1.8f), 3.0f, 10, sf::Color(0, 0, 255), &window, &objects));
	objects.push_back(new Object(sf::Vector2f(300, 300), sf::Vector2f(0, 0), 500, 20, sf::Color(255, 255, 255), &window, &objects));
	
	while(window.isOpen())
	{
		while(window.pollEvent(event))
		{
			switch (event.type)
			{
				case sf::Event::Closed:
				{
					window.close();
					break;
				}
				// mouse actions
				case sf::Event::MouseButtonPressed:
				{
					mouseClicked = true;
					if (!radiusSet)
					{
						oldPosition = (sf::Vector2f) sf::Mouse::getPosition(window);
						tmpObject.setPosition(oldPosition);
						tmpObject.setFillColor(sf::Color(rand() % 255, rand() % 255, rand() % 255));
					}
					break;
				}
				case sf::Event::MouseMoved:
				{
					if (mouseClicked)
					{
						if (!radiusSet)
						{
							sf::Vector2f diff = (sf::Vector2f) sf::Mouse::getPosition(window) - oldPosition;
							tmpObject.setRadius(sqrt(pow(diff.x, 2) + pow(diff.y, 2)));
							tmpObject.setPosition(oldPosition - sf::Vector2f(tmpObject.getRadius(), tmpObject.getRadius()));
						}
					}
					break;
				}
				case sf::Event::MouseButtonReleased:
				{
					mouseClicked = false;
					if (!radiusSet)
					{
						sf::Vector2f diff = (sf::Vector2f) sf::Mouse::getPosition(window) - oldPosition;
						tmpObject.setRadius(sqrt(pow(diff.x, 2) + pow(diff.y, 2)));
						tmpObject.setPosition(oldPosition - sf::Vector2f(tmpObject.getRadius(), tmpObject.getRadius()));
						radiusSet = true;
					}
					else
					{
						sf::Vector2f dragDiff = oldPosition - (sf::Vector2f) sf::Mouse::getPosition(window);
						objects.push_back(new Object(oldPosition, 0.1f * dragDiff, 0.5f, tmpObject.getRadius(), tmpObject.getFillColor(), &window, &objects));
						tmpObject.setRadius(0); // to make it invisible
						radiusSet = false;
					}
					break;
				}
				// keyboard actions
				case sf::Event::KeyPressed:
				{
					switch(event.key.code)
					{
						case sf::Keyboard::Escape: window.close(); break;
						case sf::Keyboard::Space:
						{
							if (pause == true) pause = false;
							else pause = true;
							break;
						}
						case sf::Keyboard::Right:
						{
							window.setFramerateLimit((++FPS > 5000) ? --FPS : FPS);
							std::cout << "FPS: " << FPS << "\n";
							break;
						}
						case sf::Keyboard::Left:
						{
							window.setFramerateLimit((--FPS <= 0) ? ++FPS : FPS);
							std::cout << "FPS: " << FPS << "\n";
							break;
						}
						case sf::Keyboard::Slash:
						{
							for(int i = 0; i < objects.size(); i++)
							{
								Object* object = objects[i];
								std::cout << "Object " << i << ": " << object->getPosition().x << " " << object->getPosition().y << "\n";
							}
						}
					}
					break;
				}
				default:
					break;
			}
		}
		
		if (pause == false)
		{
			for (int i = 0; i < objects.size(); i++)
			{
				Object* object = objects[i];
				object->Update();
			}
			
			window.clear(sf::Color(20, 20, 20));
			
			// draw all the objects
			for (Object* object : objects)
			{
				object->Render();
			}
			window.draw(tmpObject);
			
			window.display();
		}
	}
}