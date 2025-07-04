#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h>
#include <time.h>

#include <Object.hpp>

int main()
{
	// window - randerTarget
	sf::RenderWindow window(sf::VideoMode(sf::Vector2u(640, 480), 24), "Title", sf::Style::Titlebar | sf::Style::Close);
	unsigned FPS = 60;
	window.setFramerateLimit(FPS);
	
	// event's and actions related
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
		
		while(std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				window.close();
				break;
			}
			// mouse actions
			if (event->is<sf::Event::MouseButtonPressed>())
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
			if (event->is<sf::Event::MouseMoved>())
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
			if (event->is<sf::Event::MouseButtonReleased>())
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
			if (const sf::Event::KeyPressed* keyboardEvent = event->getIf<sf::Event::KeyPressed>())
			{
				switch(keyboardEvent->scancode)
				{
					case sf::Keyboard::Scan::Escape: window.close(); break;
					case sf::Keyboard::Scan::Space:
					{
						if (pause == true) pause = false;
						else pause = true;
						break;
					}
					case sf::Keyboard::Scan::Right:
					{
						window.setFramerateLimit((++FPS > 5000) ? --FPS : FPS);
						std::cout << "FPS: " << FPS << "\n";
						break;
					}
					case sf::Keyboard::Scan::Left:
					{
						window.setFramerateLimit((--FPS <= 0) ? ++FPS : FPS);
						std::cout << "FPS: " << FPS << "\n";
						break;
					}
					case sf::Keyboard::Scan::Slash:
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
	
	return 0;
}