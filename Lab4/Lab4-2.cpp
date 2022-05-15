#include <conio.h>
#include <dos.h>
#include <stdio.h>
#include <stdlib.h>
#include <bios.h>


#define LEFT_ARROW 75
#define RIGHT_ARROW 77
#define ESC 27

const int x1 = 10;
const int y1 = 10;
const int x2 = 70;
const int y2 = 20;

class Slider
{
private:
	int x, y;
public:
	Slider();
	void moveLeft();
	void moveRight();
	int getX();
	int getY();
} slider;

int Slider::getX()
{
	return x;
}

int Slider::getY()
{
	return y;
}

Slider::Slider()
{
	x = 0;
	y = 0;
}

void Slider::moveLeft()
{
	if(x>0)
		x--;
	else if(y>0)
	{
		x = 59;
		y--;
	}
}

void Slider::moveRight()
{
	if((y < 10 && x < 60) || (y == 10 && x < 59))
		x++;
	else if(y<10)
	{
		x = 0;
		y++;
	}
}

class Scene
{
private:
	int width, height;
	char* screen;
public:
	Scene(int, int, int, int);
	void render(Slider);
} scene = Scene(x1,y1,x2,y2);

Scene::Scene(int x1, int y1, int x2, int y2)
{
	width = x2 - x1 + 1;
	height = y2 - y1 + 1;
	screen = new char[width * height];
	screen[width * height - 1] = '\0';
}

void Scene::render(Slider slider)
{
	clrscr();
	for(int i = 0; i < width; i++)
		for(int j = 0; j < height; j++)
		{
			char texel = ' ';
			if(slider.getX() == i && slider.getY() == j)
				texel = '*';
			screen[i + j * width] = texel;
		}
		screen[width * height - 1] = '\0';
	cprintf(screen);
}

enum Side
{
LEFT, RIGHT, HOLD
};

void outputGreeting()
{
	printf("Program allows to move character using left and right arrows.\n");
	printf("Motion is permanent.\n");
	printf("Use ESC button to stop program.\n");
}

void goToNextLine()
{
	cprintf("\r\n");
}

char getKey()
{
	union REGS r;
	r.h.ah = 0x6;
	r.h.dl = 0xff;
	int86(0x21,&r,&r);
	return r.h.al;
}

void loop()
{
	int state = 1;
	Side side = HOLD;
	char lastKey;

	while(state)
	{
		delay(30);
		lastKey = getKey();
		switch(lastKey)
		{
			case RIGHT_ARROW:
				side = RIGHT;
			break;
			case LEFT_ARROW:
				side = LEFT;
			break;
			case ESC:
				state = 0;
			break;
		}
		switch(side)
		{
			case RIGHT:
				slider.moveRight();
			break;
			case LEFT:
				slider.moveLeft();
			break;
		}
		scene.render(slider);
	}
}

void main()
{
	clrscr();
	outputGreeting();
	system("PAUSE");

	window(x1,y1,x2,y2);
	scene.render(slider);

	loop();

	goToNextLine();
	system("PAUSE");
	clrscr();
}
