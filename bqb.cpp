#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "src/ball.hpp"
#include "src/vectcalc.hpp"
#include "src/utils.hpp"
using namespace std;

int main()
{
	float scale = 100.0f; // 1m = scale * 1pixel
	float g = scale * 9.81f;
	float ball_size = 30.0f;
	float loss = 0.8f;
	float mass = 1.0f;


	sf::RenderWindow window(sf::VideoMode(512, 512), "Balles Qui Bougent", sf::Style::Close | sf::Style::Resize);

	sf::Vector2f accel = {0.0f, g};
	sf::Vector2f speed = {scale * 5.0f, scale * 0.0f};
	sf::Vector2f pos = {50.0f, 100.0f};

	int number_balls = 2;
	Ball balls[number_balls];

	for (int i = 0; i < number_balls; i++) {
		balls[i] = Ball(ball_size, mass);
		balls[i].setAccel(accel);
		balls[i].setSpeed(speed);
		pos.x += 2 * ball_size * i + 100;
		balls[i].moveTo(pos);
	}

	sf::Clock clock;

	/*
	sf::Texture screen;
	sf::Vector2u winSize = window.getSize();
	screen.create(winSize.x, winSize.y);
	float count = 0.0f;
	float saveinterval = 0.100f;
	int images = 0;
	string name = "00000";
*/

	while(window.isOpen())
	{
		sf::Event evnt;

		while (window.pollEvent(evnt))
		{
			switch(evnt.type)
			{
				case sf::Event::Closed:
					window.close();
					break;
			}
		}

		//get the time since last frame
		float dt = clock.restart().asSeconds();
		//std::cout << dt << "s elapsed" << std::endl;
		//get screensize
		float xlimit = (float)window.getSize().x;
		float ylimit = (float)window.getSize().y;

		for (int i = 0; i < number_balls; i++) {
			balls[i].updateMov(dt);
			balls[i].checkWallCol(xlimit, ylimit, loss);
			balls[i].move();
		}

		// resolving colisions between balls
		int j = 0;
		for (j = 0; j < number_balls; j++) {
			for (int k = j+1; k < number_balls; k++) {
				sf::Vector2f ball1 = balls[j].getPos();
				sf::Vector2f ball2 = balls[k].getPos();
				float r1 = balls[j].getRadius();
				float r2 = balls[k].getRadius();

				if (dist(ball1, ball2) <= r1 + r2) {
					// get normal and tangent vectors
					sf::Vector2f n = normal(ball1, ball2);
					sf::Vector2f t = tangent(ball1, ball2);
					// get balls' speed
					sf::Vector2f v1 = balls[j].getSpeed();
					sf::Vector2f v2 = balls[k].getSpeed();
					// project onto n and t
					float v1n = dot(v1, n);
					float v1t = dot(v1, t);
					float v2n = dot(v2, n);
					float v2t = dot(v2, t);
					// compute new speeds
					float m1 = balls[j].getMass();
					float m2 = balls[k].getMass();

					float nv1n = v1n*(m1-m2) + 2*m2*v2n / (m1+m2);
					float nv2n = v2n*(m2-m1) + 2*m1*v1n / (m1+m2);
					// multiply by their vectors
					sf::Vector2f nv1, nv2;
					nv1 = add(scalx(nv1n, n), scalx(v1t, t));
					nv2 = add(scalx(nv2n, n), scalx(v2t, t));
					// set the new speeds
					balls[j].setSpeed(nv1);
					balls[k].setSpeed(nv2);
					// move balls away from each other
					sf::Vector2f pos1 = balls[j].getPos();
					sf::Vector2f pos2 = balls[k].getPos();

					float pos1n = dot(pos1, n);
					float pos2t = dot(pos2, t);

					float npos2n = pos1n + r1 + r2;

					pos2 = add(scalx(npos2n, n), scalx(pos2t, t));
					balls[k].moveTo(pos2);

				}
			}
		}

		window.clear();

		for (int i = 0; i < number_balls; i++) {
			window.draw(balls[i].ball);
		}


/*		// capturing window every 10ms
		count += dt;

		if (count >= saveinterval) {
			name = "00000";
			images++;
			string number = to_string(images);
			name = number;
			for (int i = 0; i < 5 - number.length(); i++) {
				name = "0" + name;
			}
			screen.update(window);
			//screen.copyToImage().saveToFile(name + ".jpg");
			//cout << name << ".jpg saved !" << endl;
			count = 0.0f;
		}
*/

		window.display();
	}

	return 0;
}
