#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

View view;
/*чтобы камера не выходила за границы карты*/
View GetPlayerCoordinateFromView(float x, float y)
{
	float temp_x = x, temp_y = y;
	if (x < 320) temp_x = 320;
	if (y < 240) temp_y = 240;
	if (y > 554) temp_y = 554;
	//
	if (x > 950) temp_x = 950;
	view.setCenter(temp_x, temp_y);
	return view;
}
