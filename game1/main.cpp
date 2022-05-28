#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include <iostream>
using namespace sf;

int N = 30, M = 20;
int size = 16;
int w = size * N;
int h = size * M;

int dir, num = 3;

struct Snake
{
    int x, y;
} snake[100];

struct food
{
    int x, y;
} food;

void playSound()
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

void Togloom()
{
	
	
    for (int i = num; i > 0; --i)
    {
        snake[i].x = snake[i - 1].x;
        snake[i].y = snake[i - 1].y;
    }

    if (dir == 0)
        snake[0].y += 1;
    if (dir == 1)
        snake[0].x -= 1;
    if (dir == 2)
        snake[0].x += 1;
    if (dir == 3)
        snake[0].y -= 1;

    if ((snake[0].x == food.x) && (snake[0].y == food.y))
    {
        num++;
        food.x = rand() % N;
        food.y = rand() % M;
    }

    if (snake[0].x > N)
        snake[0].x = 0;
    if (snake[0].x < 0)
        snake[0].x = N;
    if (snake[0].y > M)
        snake[0].y = 0;
    if (snake[0].y < 0)
        snake[0].y = M;
        
    for (int i = 1; i < num; i++)
		if (snake[0].x == snake[i].x && snake[0].y == snake[i].y)
		{
			std::cout << "YOU LOSE!!! \n";
			std::cout << "Your score is " << num - 3;
			playSound();
//			sleep(milliseconds(1500));
			exit(1);
		}
     
}

int main()
{
    RenderWindow window(VideoMode(w +10 , h +10), "Snake");	

    Texture t1, t2;
    t1.loadFromFile("images/green.png");
    t2.loadFromFile("images/red.png");
	
    Sprite mogoi(t1);
    Sprite hool(t2);
	
    Clock clock;
    float timer = 0, delay = 0.1;

    food.x = 10;
    food.y = 10;

    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time;
		
		Event event;
        while(window.pollEvent(event))
        	if (event.type == Event::Closed)
                    window.close();

        if (Keyboard::isKeyPressed(Keyboard::Left))
            dir = 1;
        if (Keyboard::isKeyPressed(Keyboard::Right))
            dir = 2;
        if (Keyboard::isKeyPressed(Keyboard::Up))
            dir = 3;
        if (Keyboard::isKeyPressed(Keyboard::Down))
            dir = 0;
            

        if (timer > delay)
        {
            timer = 0;
            Togloom();
        }

        window.clear();


        for (int i = 0; i < num; i++)
        {
            mogoi.setPosition(snake[i].x * size, snake[i].y * size);
            window.draw(mogoi);
        }

        hool.setPosition(food.x * size, food.y * size);
        window.draw(hool);

        window.display();
    }

    return 0;
}
