#include <cmath>

float norm(sf::Vector2f vect)
{
	return sqrt(vect.x*vect.x + vect.y*vect.y);
}

float dist(sf::Vector2f vect1, sf::Vector2f vect2)
{
	sf::Vector2f distance(vect2.x - vect1.x, vect2.y - vect1.y);
	return norm(distance);
}

float dot(sf::Vector2f vect1, sf::Vector2f vect2)
{
	return vect1.x * vect2.x + vect1.y * vect2.y;
}
