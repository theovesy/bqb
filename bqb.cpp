#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "ball.hpp"
#include "vectcalc.hpp"
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

	int number_balls = 10;
	Ball balls[number_balls];

	for (int i = 0; i < number_balls; i++) {
		balls[i] = Ball(ball_size, mass);
		balls[i].setAccel(accel);
		balls[i].setSpeed(speed);
		pos.x += 2 * ball_size * i + 50;
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
