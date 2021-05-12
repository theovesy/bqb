#include <cmath>

float norm(sf::Vector2f vect)
{
	return sqrt(vect.x*vect.x + vect.y*vect.y);
}

float dist(sf::Vector2f vect1, sf::Vector2f vect2)
{
	sf::Vector2f distance(abs(vect2.x - vect1.x), abs(vect2.y - vect1.y));
	return norm(distance);
}

float dot(sf::Vector2f vect1, sf::Vector2f vect2)
{
	return vect1.x * vect2.x + vect1.y * vect2.y;
}

sf::Vector2f scalx(float u, sf::Vector2f vect)
{
	sf::Vector2f nvect;
	nvect.x = u * vect.x;
	nvect.y = u * vect.y;
	return nvect;
}

sf::Vector2f add(sf::Vector2f vect1, sf::Vector2f vect2)
{
	sf::Vector2f nvect;
	nvect.x = vect1.x * vect2.x;
	nvect.y = vect1.y * vect2.y;
	return nvect;
}


// Returns unite normal vector from 2 vectors
sf::Vector2f normal(sf::Vector2f vect1, sf::Vector2f vect2)
{
	sf::Vector2f vectnorm(abs(vect2.x - vect1.x), abs(vect2.y - vect1.y));
	float Norm = norm(vectnorm);
	vectnorm.x = vectnorm.x/Norm;
	vectnorm.y = vectnorm.y/Norm;
	return vectnorm;
}

// Returns tangential vector from 2 vectors
sf::Vector2f tangent(sf::Vector2f vect1, sf::Vector2f vect2)
{
	sf::Vector2f vecttan(abs(vect1.y - vect2.y), abs(vect2.x - vect1.x));
	float Norm = norm(vecttan);
	vecttan.x = vecttan.x/Norm;
	vecttan.y = vecttan.y/Norm;
	return vecttan;
}
