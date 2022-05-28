#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include <iostream>
using namespace sf;

void winSound()
{
	SoundBuffer buffer;
	buffer.loadFromFile("sound/music1.wav");
	Sound sound(buffer);
	sound.play();

	while (sound.getStatus() == Sound::Playing)
	{
		sleep(milliseconds(0));
	}
}

void loseSound()
{
	SoundBuffer buffer;
	buffer.loadFromFile("sound/music.wav");
	Sound sound(buffer);
	sound.play();

	while (sound.getStatus() == Sound::Playing)
	{
		sleep(milliseconds(0));
	}
}

int main()
{
	RenderWindow game(VideoMode(515, 460), "Togloom2!");
	game.setFramerateLimit(55);
	RectangleShape paddle(Vector2f(100, 10));
	Texture t1, t2;
	t1.loadFromFile("images/block04.png");
	t2.loadFromFile("images/ball.png");

	Sprite sBall(t2);
	paddle.setPosition(300, 430);

	Sprite block[1000];

	int n = 0, count = 0;
	for (int i = 1; i <= 10; i++)
		for (int j = 1; j <= 10; j++)
		{
			block[n].setTexture(t1);
			block[n].setPosition(i * 43, j * 20);
			n++;
			count++;
		}

	float dx = 6, dy = 5;
	float x = 300, y = 300;

	while (game.isOpen())
	{
		Event event;
		while (game.pollEvent(event))
			if (event.type == Event::Closed)
				game.close();

		x += dx;
		for (int i = 0; i < n; i++)
			if (FloatRect(x + 3, y + 3, 6, 6).intersects(block[i].getGlobalBounds()))
			{
				block[i].setPosition(-100, 0);
				dx = -dx;
				count--;
			}

		y += dy;
		for (int i = 0; i < n; i++)
			if (FloatRect(x + 3, y + 3, 6, 6).intersects(block[i].getGlobalBounds()))
			{
				block[i].setPosition(-100, 0);
				dy = -dy;
				count--;
			}

		if (x < 0 || x > 520)
			dx = -dx;
		if (y < 0 || y > 450)
			dy = -dy;

		if (Keyboard::isKeyPressed(Keyboard::Right) && paddle.getPosition().x <= 415)
			paddle.move(8, 0);
		if (Keyboard::isKeyPressed(Keyboard::Left) && paddle.getPosition().x >= 0)
			paddle.move(-8, 0);

		if (FloatRect(x, y, 12, 12).intersects(paddle.getGlobalBounds()))
			dy = -(rand() % 5 + 2);

		if (count == 0)
		{
			std::cout << "YOU WIN!!!\n";
			std::cout << "Your score is " << 100 - count;
			winSound();
			exit(1);
		}
		if (y == 450)
		{
			std::cout << "YOU LOSE!!!\n";
			std::cout << "Your score is " << 100 - count;
			loseSound();
			exit(1);
		}

		sBall.setPosition(x, y);
		game.clear();
		game.draw(sBall);
		game.draw(paddle);

		for (int i = 0; i < n; i++)
			game.draw(block[i]);

		game.display();
	}

	return 0;
}
