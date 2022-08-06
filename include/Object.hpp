#include <SFML/Graphics.hpp>

#include <cmath>

class Object
{
public:
	Object(sf::Vector2f position, sf::Vector2f initialVelocity, float mass, unsigned radius, sf::Color color, sf::RenderWindow* renderTarget, std::vector<Object*>* objects);
	
	void Update();
	void Render();
	
	float getMass() { return mass; }
	float getRadius() { return radius; }
	sf::Vector2f& getPosition() { return position; }
	sf::Vector2f getVelocity() { return velocity; }
	
	// utils
	float calcDistance(sf::Vector2f a, sf::Vector2f b);
	
private:
	// rendering characteristics
	sf::CircleShape object;
	unsigned radius;
	sf::Color color;
	// for the traces
	std::vector<sf::Vertex> trace;
	
	// physics related
	sf::Vector2f position;
	sf::Vector2f velocity;
	sf::Vector2f acceleration;
	float mass;
	
	// ptrs
	sf::RenderWindow* renderTarget;
	std::vector<Object*>* objects;
};