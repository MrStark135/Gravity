#include <Object.hpp>

#include <iostream>

#define TRACES_LENGTH 100

Object::Object(sf::Vector2f position, sf::Vector2f initialVelocity, float mass, unsigned radius, sf::Color color, sf::RenderWindow* renderTarget, std::vector<Object*>* objects)
{
	this->position = position;
	velocity = initialVelocity;
	this->mass = mass;
	
	this->radius = radius;
	this->color = color;
	
	this->renderTarget = renderTarget;
	this->objects = objects;
	
	object.setFillColor(color);
	object.setRadius(radius);
	object.setPosition(position);
}

void Object::Update()
{
	velocity += acceleration;
	position += velocity;
	
	// acceleration must be reset
	bool myIndexSmaller = false;
	acceleration = sf::Vector2f(0, 0);
	for (Object* object : *objects)
	{
		if (object == this) { myIndexSmaller = true; continue; }
		
		// gravity calculation
		sf::Vector2f dist = (position + sf::Vector2f(radius, radius)) - (object->getPosition() + sf::Vector2f(object->getRadius(), object->getRadius()));
		float calcDist = sqrt(pow(dist.x, 2) + pow(dist.y, 2));
		float inverseDist = 1 / calcDist;
		sf::Vector2f dir = dist * inverseDist;
		
		// apply gravity
		acceleration -= dir * object->getMass() * (float) pow(inverseDist, 2);
		
		// collision handling
		float offset;
		if ((offset = calcDist - (radius + object->getRadius())) <= 0)
		{
			position -= velocity;
		}
	}
	
	object.setPosition(position);
	
	// trace related
	sf::Vertex point = sf::Vertex();
	point.position = position + sf::Vector2f(radius, radius);
	point.color = sf::Color(100, 100, 100);
	trace.push_back(point);
	if (trace.size() >= TRACES_LENGTH) trace.erase(trace.begin());
}

void Object::Render()
{
	renderTarget->draw(trace.data(), trace.size(), sf::PrimitiveType::LineStrip);
	renderTarget->draw(object);
}

float Object::calcDistance(sf::Vector2f a, sf::Vector2f b)
{
	return sqrt(pow(a.x, 2) + pow(a.y, 2));
}