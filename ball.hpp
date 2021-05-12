#pragma once
using namespace std;

class Ball
{
	public:

		sf::CircleShape ball;

		Ball() {}

		Ball(float Radius, float Mass)
		{
			radius = Radius;
			mass = Mass;
			ball.setRadius(radius);
			ball.setFillColor(sf::Color::Magenta);
			setColor(ball);
			ball.setOrigin(radius, radius);
		}

		void setColor(sf::CircleShape ball)
		{
			ball.setFillColor(sf::Color::Magenta);
				// add color choice
		}

		void moveTo(sf::Vector2f position)
		{
			ball.setPosition(position);
			setPos(position);
		}

		void move()
		{
			ball.setPosition(pos);
		}

		void setAccel(sf::Vector2f acc)
		{
			accel = acc;
		}

		void setSpeed(sf::Vector2f spe)
		{
			speed = spe;
		}

		void setPos(sf::Vector2f position)
		{
			pos = position;
		}

		sf::Vector2f getPos()
		{
			return pos;
		}

		float getRadius()
		{
			return radius;
		}

		sf::Vector2f getSpeed()
		{
			return speed;
		}

		float getMass()
		{
			return mass;
		}

		void updateMov(float dt)
		{
			//update speed from accel
			speed.x += accel.x * dt;
			speed.y += accel.y * dt;

			//update pos from speed
			pos.x += accel.x/2 * dt * dt + speed.x * dt;
			pos.y += accel.y/2 * dt * dt + speed.y * dt;
		}

		void checkWallCol(float xlimit, float ylimit, float loss)
		{
			if (pos.x - radius <= 0) {
				pos.x = radius;
				speed.x = -speed.x * loss;
			}
			if (pos.y - radius <= 0) {
				pos.y = radius;
				speed.y = -speed.y * loss;
			}
			if (pos.x + radius >= xlimit) {
				pos.x = xlimit - radius;
				speed.x = -speed.x * loss;
			}
			if (pos.y + radius >= ylimit) {
				pos.y = ylimit - radius;
				speed.y = -speed.y * loss;
			}
		}


	private:
		float radius;
		float mass;

		sf::Vector2f accel;
		sf::Vector2f speed;
		sf::Vector2f pos;
};
