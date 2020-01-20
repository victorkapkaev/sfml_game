#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <iostream>
#include "player.h"
#include "map.h"
#include "view.h"

using namespace sf;

int main()
{
	RenderWindow window(VideoMode(640, 480), "SFML works!");

	view.reset(FloatRect(0, 0, 640, 480)); // настройка камеры
	float current_frame = 0; // текущий кадр
	short seconds_remains = 31;

	/*блок загрузки музыки*/
	Music music_loser, music_victory, music;
	music_loser.openFromFile("sources/loser.wav");
	music_victory.openFromFile("sources/aplodist.wav");
	music.openFromFile("sources/music.wav");

	/*блок загрузки карты*/
	Image map_image;
	map_image.loadFromFile("sources/map.png");
	Texture map;
	map.loadFromImage(map_image);
	Sprite map_sprite;
	map_sprite.setTexture(map);

	Player p("hero3.png", 32, 325, 189, 267); // создаем персонажа

	Clock clock;
	Clock remain;
	remain.restart();

	/*блок загрузки шрифта и текста*/
	Font font;
	font.loadFromFile("sources/CyrilicOld.ttf");
	Text hp(" ", font, 40);
	Text over(" ", font, 80);
	Text remains(" ", font, 40);
	over.setStyle(Text::Bold);
	hp.setFillColor(Color::Yellow);
	over.setFillColor(Color::Red);
	remains.setFillColor(Color::Blue);
	
	while (window.isOpen())
	{
		
		/*время для плавности движения*/
		float time = clock.getElapsedTime().asMicroseconds();
		int timer = remain.getElapsedTime().asSeconds();
		clock.restart();
		time /= 1000;
		
		/*блок управления*/
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		if (p.life)
		{
			if (music.getStatus() == false)
			{
				music.play();
			}

			if (Keyboard::isKeyPressed(Keyboard::A))
			{
				p.direction = 1; p.speed = 0.2;
				current_frame += 0.005 * time;
				if (current_frame > 3)
					current_frame -= 3;
				p.sprite.setTextureRect(IntRect(255 * int(current_frame), 580, 189, 267));
			};
			if (Keyboard::isKeyPressed(Keyboard::D))
			{
				p.direction = 0; p.speed = 0.2;
				current_frame += 0.005 * time;
				if (current_frame > 3)
					current_frame -= 3;
				p.sprite.setTextureRect(IntRect(255 * int(current_frame), 870, 189, 267));
			};
			if (Keyboard::isKeyPressed(Keyboard::W))
			{
				p.direction = 3; p.speed = 0.2;
				current_frame += 0.005 * time;
				if (current_frame > 3)
					current_frame -= 3;
				p.sprite.setTextureRect(IntRect(255 * int(current_frame), 296, 189, 267));
			};
			if (Keyboard::isKeyPressed(Keyboard::S))
			{
				p.direction = 2; p.speed = 0.2;
				current_frame += 0.005 * time;
				if (current_frame > 3)
					current_frame -= 3;
				p.sprite.setTextureRect(IntRect(255 * int(current_frame), 0, 189, 267));
			};
			if (timer > 0)
			{
				seconds_remains--;
				remains.setString("Time: " + std::to_string(seconds_remains));
				if (seconds_remains <= 0)
				{
					remains.setString("Time: 0");
				}
				remain.restart();
			}
		}

		GetPlayerCoordinateFromView(p.GetPlayerCordX(), p.GetPlayerCordY()); // получаем координаты для камеры
		p.update(time);
		window.setView(view);
		window.clear();

		/*блок рисовки карты*/
		for (int i = 0; i < height_map; i++)
		{
			for (int j = 0; j < width_map; j++)
			{
				if (tileMap[i][j] == ' ')
					map_sprite.setTextureRect(IntRect(0, 0, 32, 32));
				if (tileMap[i][j] == 's')
					map_sprite.setTextureRect(IntRect(32, 0, 32, 32));
				if (tileMap[i][j] == '0')
					map_sprite.setTextureRect(IntRect(64, 0, 32, 32));
				if (tileMap[i][j] == 'g')
					map_sprite.setTextureRect(IntRect(96, 0, 32, 32));
				if (tileMap[i][j] == 'm')
				{
					map_sprite.setTextureRect(IntRect(128, 0, 32, 32));
				}

				map_sprite.setPosition(j * 32, i * 32);
				window.draw(map_sprite);
			}
		}
		window.draw(p.sprite);
		/*победа*/
		if (p.is_win) // победа
		{
			over.setFillColor(Color::Red);
			over.setScale(2.f, 2.f);
			over.setString("You Win!");
			over.setPosition(view.getCenter().x - 80, view.getCenter().y - 10);
			window.draw(over);
			p.life = false;
			music.stop();
			if (music_victory.getStatus() == false)
			{
				music_victory.play();
			}
		}

		/*поражение*/
		if ((p.health <= 0 || music.getStatus() == false) && !p.is_win)
		{
			p.life = false;
			p.sprite.setColor(Color::Black);
			over.setString("Game Over");
			over.setPosition(view.getCenter().x - 175, view.getCenter().y - 50);
			window.draw(over);
			music.stop();
			if (music_loser.getStatus() == false)
			{
				music_loser.play();
			}
		}
		
		/*рисуем текст*/
		hp.setString("HP: " + std::to_string(p.health));
		hp.setPosition(view.getCenter().x - 320, view.getCenter().y - 250);
		window.draw(hp);
		remains.setPosition(view.getCenter().x + 165, view.getCenter().y - 250);
		window.draw(remains);

		/*рисуем персонажа*/
		
		window.display();
	}
	return 0;
}