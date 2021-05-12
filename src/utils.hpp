#pragma once

void ballColisions(Ball balls, int number_balls)
{
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
