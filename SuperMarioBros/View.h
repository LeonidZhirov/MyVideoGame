#pragma once

sf::View view;

void setPlayerCoordinateForView(const float& x, const float& y, sf::View& view) { 
	float tempX = x; float tempY = y;

	if (x < 320)
		tempX = 320;
	if (y > 554)
		tempY = 554;

	view.setCenter(tempX, tempY); 
}

/*void viewMap(const float& time) {
	if (Keyboard::isKeyPressed(Keyboard::D)) 
		view.move(0.1 * time, 0);
	if (Keyboard::isKeyPressed(Keyboard::S)) 
		view.move(0, 0.1 * time);
	if (Keyboard::isKeyPressed(Keyboard::A)) 
		view.move(-0.1 * time, 0);
	if (Keyboard::isKeyPressed(Keyboard::W)) 
		view.move(0, -0.1 * time);
}*/
