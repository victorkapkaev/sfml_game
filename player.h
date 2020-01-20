#pragma once
#include <SFML/Graphics.hpp>
#include <Windows.h>
#include "map.h"
using namespace sf;

class Player
{
private: float pos_x, pos_y;
public:
	float width, high, a_x, a_y, speed = 0;
	int direction = 0, health = 100; // направление движения игрока
	bool life = true;
	bool is_win = false;
	String File;
	Image image;
	Texture texture;
	Sprite sprite;
	
	Player(String F, float x, float y, float w, float h)
	{
		File = F;
		a_x = 0; a_y = 0; speed = 0; direction = 0;
		width = w ; high = h;
		image.loadFromFile("sources/" + File);
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		pos_x = x; pos_y = y;
		sprite.setTextureRect(IntRect(0, 0, width , high));
		sprite.setScale(0.15f, 0.2f);
	}
	void update(float time)
	{
		switch (direction)
		{
		case 0:
		{
			a_x = speed; a_y = 0; break;
		}
		case 1:
		{
			a_x = -speed; a_y = 0; break;
		}
		case 2:
		{
			a_x = 0; a_y = speed; break;
		}
		case 3:
		{
			a_x = 0; a_y = -speed; break;
		}
		}
		pos_x += a_x * time;
		pos_y += a_y * time;

		speed = 0; // для остановки
		sprite.setPosition(pos_x, pos_y);
		InteractionWithMap();
	}

	/*получаем координаты*/
	float GetPlayerCordX()
	{
		return pos_x;
	}
	float GetPlayerCordY()
	{
		return pos_y;
	}
	/*взаимодействие с картой*/
	void InteractionWithMap()
	{
		for (int i = pos_y / 32; i < (pos_y + high * 0.2) / 32; i++)
		{
			for (int j = pos_x / 32; j < (pos_x + width * 0.15) / 32; j++)
			{
				if (tileMap[i][j] == '0') // если стена
				{
					if (a_y > 0) // шли вниз
					{
						pos_y = i * 32 - high * 0.2 - 1; // стоп
					}
					if (a_y < 0)
					{
						pos_y = i * 32 + 32;
					}
					if (a_x > 0)
					{
						pos_x = j * 32 - width * 0.15 - 1;
					}
					if (a_x < 0)
					{
						pos_x = j * 32 + 32;
					}
				}

				else if (tileMap[i][j] == 'm')
				{
					tileMap[i][j] = ' ';
					sprite.setColor(Color::Red);
					health -= 50;
				}
				else if (tileMap[i][j] == 's')
				{
					is_win = true;
				}
			}

		}
	}
};