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
