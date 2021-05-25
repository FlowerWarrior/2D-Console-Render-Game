//Made by Tomasz Piasecki
//Swimmer - The Game
//Game works by 2D rendering in a console

//Libraries
#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#include <string>
#include <stdlib.h>
#include <cstdlib>
#include <cwchar>
#include <thread>
#include <fstream>
#include <cmath>

std::ofstream file;
using namespace std;
HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
HANDLE buffer = GetStdHandle(STD_OUTPUT_HANDLE);

//Global Variables
int array_pixels[60][60] = {}; //Visible Pixels 60x25
int array_background[60][60] = {};
int screen_x = 60;
int screen_y = 25;
int int_x = 0;
int int_y = 0;
int int_x2 = 0;
int int_y2 = 0;
int int_x3 = 0;
int int_y3 = 0;
int comet_x = 4;
int comet_y = 4;
int player_x = 15;
int player_y = 8;
int player2_x = 45;
int player2_y = 8;
int player_x_new;
int player_y_new;
char char_pressed;
int bubbles_update = 0;
bool game_run = true;
int int_scene = 1;
int int_select = 1;
int background_update = 1000;
int movement_update = 0;
int movement2_update = 0;
int animation_frame = 1;
int animation_time = 0;
int bubbles_animation_frame = 1;
int bubbles_animation_time = 0;
int bubbles_x = 35;
int bubbles_y = 8;
int obstacle_x = 30;
int obstacle_y = 30;
int obstacle2_x = 15;
int obstacle2_y = 40;
int obstacle3_x = 15;
int obstacle3_y = 50;
int obstacle_update = 0;
int obstacle2_update = 0;
int obstacle3_update = 0;
int scene = 1;
int selected_option = 1;
int selected_option2 = 1;
int multiplayer = 0;
int coin_x = 25;
int coin_y = 10;
int speed = 2;
int level = 1;
int points = 0;
int highscore = 0;
int level_update = 0;
thread t2;
thread t3;
thread t4;
thread t5;
thread t6;
thread t7;
thread t8;
thread t9;
thread t10;
thread t11;
thread t12;
thread t13;
HANDLE hStdOut = ::GetStdHandle(STD_OUTPUT_HANDLE);
int digits;
LPCWSTR sound_coin_path = L"Sound_Coin.wav";
LPCWSTR sound_background_path = L"Audio\\Sound_Background.wav";

void Point(int x, int y, int type);
void Obstacle1Collision();
void Obstacle2Collision();
void Obstacle3Collision();
void GameOver();
void BackgroundMusic();

//Function Console Output
void Output(HANDLE h, SHORT x, SHORT y, const char* symbol, WORD color)
{
	COORD here;
	here.X = x;
	here.Y = y;
	WORD attribute = color;
	DWORD written;
	::WriteConsoleOutputAttribute(h, &attribute, 1, here, &written);
	::WriteConsoleOutputCharacterA(h, symbol, 1, here, &written);
}


//Function Calculate Background
void CalcBackground()
{
	while (scene == 2)
	{
		int_y2 = 25;
		while (int_y2 > 0)
		{
			int_x2 = 0;
			while (int_x2 < screen_x)
			{
				if ((rand() % 100) > 98)
				{
					array_background[int_x2][int_y2] = 1;
				}
				else if ((rand() % 50) < 2)
				{
					array_background[int_x2][int_y2] = 2;
				}
				else
				{
					array_background[int_x2][int_y2] = 0;
				}
				int_x2 = int_x2 + 1;
			}
			int_y2 = int_y2 - 1;
		}
		background_update = 0;
		this_thread::sleep_for(std::chrono::milliseconds(2000));
	}
}

//Function Fill Pixel Space
void Fill(int x1, int y1, int x2, int y2, int type)
{
	for (int i = 0; i <= y2 - y1; i++)
	{
		for (int j = 0; j <= x2 - x1; j++)
		{
			array_pixels[j + x1][i + y1] = type;
		}
	}
}

//Function Draw Bubbles
void DrawBubbles()
{
	bubbles_animation_time++;
	switch (bubbles_animation_frame)
	{
	case 1:
	{
		Point(bubbles_x - 1, bubbles_y, 9);
		//Point(bubbles_x,player_y-4,10);
		//Point(bubbles_x-1,player_y-5,9);
		//Point(bubbles_x,player_y-6,10);

		if (bubbles_animation_time >= 10)
		{
			bubbles_animation_time = 0;
			bubbles_animation_frame = 2;
		}
		break;
	}
	case 2:
	{
		Point(bubbles_x, bubbles_y, 10);
		//Point(bubbles_x-1,player_y-4,9);
		//Point(bubbles_x,player_y-5,10);
		//Point(bubbles_x-1,player_y-6,9);

		if (bubbles_animation_time >= 10)
		{
			bubbles_animation_time = 0;
			bubbles_animation_frame = 1;
		}
		break;
	}
	}
}

//Function Animate Player 1
void PlayersAnimation()
{
	while (scene == 2)
	{
		switch (animation_frame)
		{
		case 1:
		{
			animation_frame = 2;
			break;
		}
		case 2:
		{
			animation_frame = 1;
			break;
		}
		}
		this_thread::sleep_for(std::chrono::milliseconds(200));
	}
}

//Function Draw Player
void DrawPlayer()
{
	switch (animation_frame)
	{
	case 1:
	{
		Point(player_x - 1, player_y + 1, 2);
		Point(player_x, player_y + 1, 1);

		Point(player_x - 2, player_y, 8);
		Point(player_x - 1, player_y, 4);
		Point(player_x, player_y, 3);
		Point(player_x + 1, player_y, 7);

		Point(player_x - 1, player_y - 1, 19);
		Point(player_x, player_y - 1, 18);
		break;
	}
	case 2:
	{
		Point(player_x - 1, player_y + 1, 2);
		Point(player_x, player_y + 1, 1);

		Point(player_x - 2, player_y, 19);
		Point(player_x - 1, player_y, 4);
		Point(player_x, player_y, 3);
		Point(player_x + 1, player_y, 18);

		Point(player_x - 1, player_y - 1, 8);
		Point(player_x, player_y - 1, 7);
		break;
	}
	}
}

//Function Draw Player 2
void DrawPlayer2()
{
	switch (animation_frame)
	{
	case 1:
	{
		Point(player2_x - 1, player2_y + 1, 15);
		Point(player2_x, player2_y + 1, 15);

		Point(player2_x - 2, player2_y, 8);
		Point(player2_x - 1, player2_y, 4);
		Point(player2_x, player2_y, 3);
		Point(player2_x + 1, player2_y, 7);

		Point(player2_x - 1, player2_y - 1, 19);
		Point(player2_x, player2_y - 1, 18);
		break;
	}
	case 2:
	{
		Point(player2_x - 1, player2_y + 1, 15);
		Point(player2_x, player2_y + 1, 15);

		Point(player2_x - 2, player2_y, 19);
		Point(player2_x - 1, player2_y, 4);
		Point(player2_x, player2_y, 3);
		Point(player2_x + 1, player2_y, 18);

		Point(player2_x - 1, player2_y - 1, 8);
		Point(player2_x, player2_y - 1, 7);
		break;
	}
	}

}

//Function Draw Obstacle 1
void DrawObstacle1()
{
	Point(obstacle_x - 1, obstacle_y + 3, 11);
	Point(obstacle_x, obstacle_y + 3, 11);
	Point(obstacle_x + 1, obstacle_y + 3, 11);

	Point(obstacle_x - 1, obstacle_y + 2, 5);
	Point(obstacle_x, obstacle_y + 2, 14);
	Point(obstacle_x + 1, obstacle_y + 2, 6);

	Point(obstacle_x - 1, obstacle_y + 1, 6);
	Point(obstacle_x, obstacle_y + 1, 14);
	Point(obstacle_x + 1, obstacle_y + 1, 5);

	Point(obstacle_x - 2, obstacle_y, 6);
	Point(obstacle_x - 1, obstacle_y, 14);
	Point(obstacle_x, obstacle_y, 14);
	Point(obstacle_x + 1, obstacle_y, 14);
	Point(obstacle_x + 2, obstacle_y, 5);

	Point(obstacle_x - 3, obstacle_y - 1, 13);
	Point(obstacle_x - 2, obstacle_y - 1, 14);
	Point(obstacle_x - 1, obstacle_y - 1, 14);
	Point(obstacle_x, obstacle_y - 1, 14);
	Point(obstacle_x + 1, obstacle_y - 1, 14);
	Point(obstacle_x + 2, obstacle_y - 1, 14);
	Point(obstacle_x + 3, obstacle_y - 1, 13);

	Point(obstacle_x - 3, obstacle_y - 2, 13);
	Point(obstacle_x - 2, obstacle_y - 2, 14);
	Point(obstacle_x - 1, obstacle_y - 2, 9);
	Point(obstacle_x, obstacle_y - 2, 14);
	Point(obstacle_x + 1, obstacle_y - 2, 9);
	Point(obstacle_x + 2, obstacle_y - 2, 14);
	Point(obstacle_x + 3, obstacle_y - 2, 13);

	Point(obstacle_x - 2, obstacle_y - 3, 5);
	Point(obstacle_x - 1, obstacle_y - 3, 11);
	Point(obstacle_x, obstacle_y - 3, 12);
	Point(obstacle_x + 1, obstacle_y - 3, 11);
	Point(obstacle_x + 2, obstacle_y - 3, 6);
}

//Function Draw Obstacle 2
void DrawObstacle2()
{
	if (level > 1)
	{
		Point(obstacle2_x - 1, obstacle2_y + 3, 11);
		Point(obstacle2_x, obstacle2_y + 3, 11);
		Point(obstacle2_x + 1, obstacle2_y + 3, 11);

		Point(obstacle2_x - 1, obstacle2_y + 2, 5);
		Point(obstacle2_x, obstacle2_y + 2, 14);
		Point(obstacle2_x + 1, obstacle2_y + 2, 6);

		Point(obstacle2_x - 1, obstacle2_y + 1, 6);
		Point(obstacle2_x, obstacle2_y + 1, 14);
		Point(obstacle2_x + 1, obstacle2_y + 1, 5);

		Point(obstacle2_x - 2, obstacle2_y, 6);
		Point(obstacle2_x - 1, obstacle2_y, 14);
		Point(obstacle2_x, obstacle2_y, 14);
		Point(obstacle2_x + 1, obstacle2_y, 14);
		Point(obstacle2_x + 2, obstacle2_y, 5);

		Point(obstacle2_x - 3, obstacle2_y - 1, 13);
		Point(obstacle2_x - 2, obstacle2_y - 1, 14);
		Point(obstacle2_x - 1, obstacle2_y - 1, 14);
		Point(obstacle2_x, obstacle2_y - 1, 14);
		Point(obstacle2_x + 1, obstacle2_y - 1, 14);
		Point(obstacle2_x + 2, obstacle2_y - 1, 14);
		Point(obstacle2_x + 3, obstacle2_y - 1, 13);

		Point(obstacle2_x - 3, obstacle2_y - 2, 13);
		Point(obstacle2_x - 2, obstacle2_y - 2, 14);
		Point(obstacle2_x - 1, obstacle2_y - 2, 16);
		Point(obstacle2_x, obstacle2_y - 2, 14);
		Point(obstacle2_x + 1, obstacle2_y - 2, 16);
		Point(obstacle2_x + 2, obstacle2_y - 2, 14);
		Point(obstacle2_x + 3, obstacle2_y - 2, 13);

		Point(obstacle2_x - 2, obstacle2_y - 3, 5);
		Point(obstacle2_x - 1, obstacle2_y - 3, 11);
		Point(obstacle2_x, obstacle2_y - 3, 12);
		Point(obstacle2_x + 1, obstacle2_y - 3, 11);
		Point(obstacle2_x + 2, obstacle2_y - 3, 6);
	}
}

//Function Draw Obstacle 3
void DrawObstacle3()
{
	if (level > 2)
	{
		Point(obstacle3_x - 1, obstacle3_y + 3, 11);
		Point(obstacle3_x, obstacle3_y + 3, 11);
		Point(obstacle3_x + 1, obstacle3_y + 3, 11);

		Point(obstacle3_x - 1, obstacle3_y + 2, 5);
		Point(obstacle3_x, obstacle3_y + 2, 14);
		Point(obstacle3_x + 1, obstacle3_y + 2, 6);

		Point(obstacle3_x - 1, obstacle3_y + 1, 6);
		Point(obstacle3_x, obstacle3_y + 1, 14);
		Point(obstacle3_x + 1, obstacle3_y + 1, 5);

		Point(obstacle3_x - 2, obstacle3_y, 6);
		Point(obstacle3_x - 1, obstacle3_y, 14);
		Point(obstacle3_x, obstacle3_y, 14);
		Point(obstacle3_x + 1, obstacle3_y, 14);
		Point(obstacle3_x + 2, obstacle3_y, 5);

		Point(obstacle3_x - 3, obstacle3_y - 1, 13);
		Point(obstacle3_x - 2, obstacle3_y - 1, 14);
		Point(obstacle3_x - 1, obstacle3_y - 1, 14);
		Point(obstacle3_x, obstacle3_y - 1, 14);
		Point(obstacle3_x + 1, obstacle3_y - 1, 14);
		Point(obstacle3_x + 2, obstacle3_y - 1, 14);
		Point(obstacle3_x + 3, obstacle3_y - 1, 13);

		Point(obstacle3_x - 3, obstacle3_y - 2, 13);
		Point(obstacle3_x - 2, obstacle3_y - 2, 14);
		Point(obstacle3_x - 1, obstacle3_y - 2, 17);
		Point(obstacle3_x, obstacle3_y - 2, 14);
		Point(obstacle3_x + 1, obstacle3_y - 2, 17);
		Point(obstacle3_x + 2, obstacle3_y - 2, 14);
		Point(obstacle3_x + 3, obstacle3_y - 2, 13);

		Point(obstacle3_x - 2, obstacle3_y - 3, 5);
		Point(obstacle3_x - 1, obstacle3_y - 3, 11);
		Point(obstacle3_x, obstacle3_y - 3, 12);
		Point(obstacle3_x + 1, obstacle3_y - 3, 11);
		Point(obstacle3_x + 2, obstacle3_y - 3, 6);
	}
}

//Function Move Obstacle 1
void Obstacle1Movement()
{
	while (scene == 2)
	{
		if (obstacle_y > 0)
		{
			obstacle_y = obstacle_y - speed;
		}
		else
		{
			obstacle_y = 30;
			obstacle_x = (rand() % 50) + 5;
		}
		obstacle_update = 0;
		this_thread::sleep_for(std::chrono::milliseconds(200));
	}
}

//Function Move Obstacle 2
void Obstacle2Movement()
{
	while (scene == 2)
	{
		if (obstacle2_y > 0)
		{
			obstacle2_y = obstacle2_y - speed;
		}
		else
		{
			obstacle2_x = (rand() % 50) + 5;
			obstacle2_y = 30;
		}
		obstacle2_update = 0;
		this_thread::sleep_for(std::chrono::milliseconds(200));
	}
}

//Function Move Obstacle 3
void Obstacle3Movement()
{
	while (scene == 2)
	{
		if (obstacle3_y > 0)
		{
			obstacle3_y = obstacle3_y - speed;
		}
		else
		{
			obstacle3_x = (rand() % 50) + 5;
			obstacle3_y = 30;
		}
		obstacle3_update = 0;
		this_thread::sleep_for(std::chrono::milliseconds(200));
	}
}

//Function Move Bubbles
void BubblesMovement()
{
	bubbles_update = bubbles_update + 5;
	if (bubbles_update >= 20)
	{
		bubbles_x = player_x;
		bubbles_y = player_y + 2;
		bubbles_update = 0;
	}
}

//Function Draw Coin
void DrawCoin()
{
	//Point(coin_x - 1, coin_y, 8);
	Point(coin_x, coin_y, 20);
	//Point(coin_x + 1, coin_y, 7);
}

//Function SpawnCoin
void SpawnCoin()
{
	coin_y = (rand() % 20) + 1;
	coin_x = (rand() % 50) + 5;
}

//Function Coin Collision
void CoinCollision()
{
	while (scene == 2)
	{
		if (abs(coin_y - player_y) < 2 && abs(coin_x - player_x) < 4)
		{
			points++;
			SpawnCoin();
		}
		if (abs(coin_y - player2_y) < 2 && abs(coin_x - player2_x) < 4)
		{
			points++;
			SpawnCoin();
		}
		this_thread::sleep_for(chrono::milliseconds(100));
	}
}

//Function Restart Game
void Restart()
{
	scene = 1;
	screen_x = 60;
	screen_y = 25;
	int_x = 0;
	int_y = 0;
	int_x2 = 0;
	int_y2 = 0;
	comet_x = 4;
	comet_y = 4;
	player_x = 15;
	player_y = 8;
	player2_x = 45;
	player2_y = 8;
	bubbles_update = 0;
	int_scene = 1;
	int_select = 1;
	background_update = 1000;
	movement_update = 0;
	movement2_update = 0;
	animation_frame = 1;
	animation_time = 0;
	bubbles_animation_frame = 1;
	bubbles_animation_time = 0;
	bubbles_x = 35;
	bubbles_y = 8;
	obstacle_x = 30;
	obstacle_y = 30;
	obstacle2_x = 15;
	obstacle2_y = 45;
	obstacle_update = 0;
	obstacle2_update = 0;
	selected_option = 1;
	selected_option2 = 1;
	level_update = 0;
	level = 1;
	speed = 2;
	points = 0;
}

//Function Level Up
void LevelUp()
{
	while (scene == 2)
	{
		this_thread::sleep_for(std::chrono::seconds(100));
		switch (level)
		{
		case 1:
		{
			if (obstacle2_y > 25)
			{
				thread t9(Obstacle2Collision);
				t9.detach();
				level++;
			}
			break;
		}
		case 2:
		{
			if (obstacle3_y > 25)
			{
				thread t10(Obstacle3Collision);
				t10.detach();
				level++;
			}
			break;
		}
		}
	}
}

//Function Collision Obstacle 1
void Obstacle1Collision()
{
	while (scene == 2)
	{
		switch (multiplayer)
		{
		case 0:
		{
			if (abs(obstacle_y - player_y) < 3 && abs(obstacle_x - player_x) < 5)
			{
				GameOver();
			}
			break;
		}
		case 1:
		{
			if (abs(obstacle_y - player_y) < 3 && abs(obstacle_x - player_x) < 5)
			{
				GameOver();
			}
			if (abs(obstacle_y - player2_y) < 3 && abs(obstacle_x - player2_x) < 5)
			{
				GameOver();
			}
			break;
		}
		}
		this_thread::sleep_for(chrono::milliseconds(100));
	}
}

//Function Collision Obstacle 2
void Obstacle2Collision()
{
	while (scene == 2)
	{
		if (level > 1)
		{
			switch (multiplayer)
			{
			case 0:
			{
				if (abs(obstacle2_y - player_y) < 3 && abs(obstacle2_x - player_x) < 5)
				{
					GameOver();
				}
				break;
			}
			case 1:
			{
				if (abs(obstacle2_y - player_y) < 3 && abs(obstacle2_x - player_x) < 5)
				{
					GameOver();
				}
				if (abs(obstacle2_y - player2_y) < 3 && abs(obstacle2_x - player2_x) < 5)
				{
					GameOver();
				}
				break;
			}
			}

		}
		this_thread::sleep_for(chrono::milliseconds(100));
	}
}

//Function Collision Obstacle 3
void Obstacle3Collision()
{
	while (scene == 2)
	{
		if (level > 2)
		{
			switch (multiplayer)
			{
			case 0:
			{
				if (abs(obstacle3_y - player_y) < 3 && abs(obstacle3_y - player_x) < 5)
				{
					GameOver();
				}
				break;
			}
			case 1:
			{
				if (abs(obstacle3_y - player_y) < 3 && abs(obstacle3_y - player_x) < 5)
				{
					GameOver();
				}
				if (abs(obstacle3_y - player2_y) < 3 && abs(obstacle3_y - player2_x) < 5)
				{
					GameOver();
				}
				break;
			}
			}
		}
		this_thread::sleep_for(chrono::milliseconds(100));
	}
}

//Function Game Over
void GameOver()
{
	ifstream file_read;
	file_read.open("Highscore.txt");
	file_read >> highscore;
	file_read.close();
	if (points > highscore)
	{
		highscore = points;
	}
	ofstream file_write;
	file_write.open("Highscore.txt");
	file_write << highscore;
	file_write.close();
	//DWORD attributes = GetFileAttributesA("highscore.txt");
	//SetFileAttributesA("highscore.txt", attributes + FILE_ATTRIBUTE_HIDDEN);
	scene = 0;
	Sleep(2000);
	Restart();
}

//Function Render Options
void RenderOptions()
{

	switch (selected_option2)
	{
	case 1:
	{
		switch (multiplayer)
		{
		case 0:
		{
			system("CLS");
			cout << "<<1 Player>> " << endl;
			cout << "   RETURN " << endl;
			char_pressed = _getch();
			if (GetKeyState('S') & 0x8000)
			{
				selected_option2 = 2;
			}
			if (GetKeyState('D') & 0x8000)
			{
				multiplayer = 1;
			}
			if (GetKeyState('A') & 0x8000)
			{
				multiplayer = 1;
			}
			break;
		}
		case 1:
		{
			system("CLS");
			cout << "<<2 Player>> " << endl;
			cout << "   RETURN " << endl;
			char_pressed = _getch();
			if (GetKeyState('S') & 0x8000)
			{
				selected_option2 = 2;
			}
			if (GetKeyState('D') & 0x8000)
			{
				multiplayer = 0;
			}
			if (GetKeyState('A') & 0x8000)
			{
				multiplayer = 0;
			}
			break;
		}
		}
		break;
	}
	case 2:
	{
		switch (multiplayer)
		{
		case 0:
		{
			system("CLS");
			cout << "  1 Player " << endl;
			cout << " <<RETURN>> " << endl;
			char_pressed = _getch();
			if (GetKeyState('W') & 0x8000)
			{
				selected_option2 = 1;
			}
			if (GetKeyState('D') & 0x8000)
			{
				scene = 1;
			}
			break;
		}
		case 1:
		{
			system("CLS");
			cout << "  2 Player " << endl;
			cout << " <<RETURN>> " << endl;
			char_pressed = _getch();
			if (GetKeyState('W') & 0x8000)
			{
				selected_option2 = 1;
			}
			if (GetKeyState('D') & 0x8000)
			{
				scene = 1;
			}
			break;
		}
		}
		break;
	}
	}
}

//Function Movement2
void Movement2()
{
	while (scene == 2 && multiplayer > 0)
	{
		//Pressed RIGHT
		if (GetKeyState(VK_RIGHT) & 0x8000)
		{
			if (player2_x < screen_x - 4)
			{
				player2_x = player2_x + speed;
			}
		}
		//Pressed LEFT
		if (GetKeyState(VK_LEFT) & 0x8000)
		{
			if (player2_x > 3)
			{
				player2_x = player2_x - speed;
			}
		}
		//Pressed UP
		if (GetKeyState(VK_UP) & 0x8000)
		{
			if (player2_y < screen_y - 2)
			{
				player2_y = player2_y + speed / 2;
			}
		}
		//Pressed DOWN
		if (GetKeyState(VK_DOWN) & 0x8000)
		{
			if (player2_y > 2)
			{
				player2_y = player2_y - speed / 2;
			}
		}
		this_thread::sleep_for(chrono::milliseconds(60));
	}
}

//Function Movement
void Movement()
{
	while (scene == 2)
	{
		//Pressed D
		if (GetKeyState('D') & 0x8000)
		{
			if (player_x < screen_x - 4)
			{
				player_x = player_x + 2;
			}
		}
		//Pressed A
		if (GetKeyState('A') & 0x8000)
		{
			if (player_x > 3)
			{
				player_x = player_x - 2;
			}
		}
		//Pressed W
		if (GetKeyState('W') & 0x8000)
		{
			if (player_y < screen_y - 2)
			{
				player_y = player_y + 1;
			}
		}
		//Pressed S
		if (GetKeyState('S') & 0x8000)
		{
			if (player_y > 2)
			{
				player_y = player_y - 1;
			}
		}
		this_thread::sleep_for(chrono::milliseconds(60));
	}
}

//Function Color Pixel
void Point(int x, int y, int type)
{
	array_pixels[x][y] = type;
}

//Function Render Engine
void Render()
{
	while (scene == 2)
	{
		DrawObstacle1();
		DrawObstacle2();
		DrawObstacle3();
		DrawCoin();
		DrawPlayer();
		if (multiplayer > 0)
		{
			DrawPlayer2();
		}
		//system("CLS");
		int_y = screen_y + 1;
		int_y3 = 0;
		Output(hStdOut, 0, 0, "P", 7 | FOREGROUND_INTENSITY);
		Output(hStdOut, 1, 0, "o", 7 | FOREGROUND_INTENSITY);
		Output(hStdOut, 2, 0, "i", 7 | FOREGROUND_INTENSITY);
		Output(hStdOut, 3, 0, "n", 7 | FOREGROUND_INTENSITY);
		Output(hStdOut, 4, 0, "t", 7 | FOREGROUND_INTENSITY);
		Output(hStdOut, 5, 0, "s", 7 | FOREGROUND_INTENSITY);
		Output(hStdOut, 6, 0, ":", 7 | FOREGROUND_INTENSITY);
		Output(hStdOut, 7, 0, " ", 7 | FOREGROUND_INTENSITY);
		digits = trunc(log10(points)) + 1;
		char buf[256];
		sprintf_s(buf, "%d", points);
		switch (digits)
		{
		case 1:
		{
			Output(hStdOut, 8, 0, buf, 7 | FOREGROUND_INTENSITY);
			break;
		}
		case 2:
		{
			Output(hStdOut, 8, 0, buf, 7 | FOREGROUND_INTENSITY);
			Output(hStdOut, 9, 0, "0", 7 | FOREGROUND_INTENSITY);
			Output(hStdOut, 10, 0, "+", 7 | FOREGROUND_INTENSITY);
			break;
		}
		case 3:
		{
			Output(hStdOut, 8, 0, buf, 7 | FOREGROUND_INTENSITY);
			Output(hStdOut, 9, 0, "0", 7 | FOREGROUND_INTENSITY);
			Output(hStdOut, 10, 0, "0", 7 | FOREGROUND_INTENSITY);
			Output(hStdOut, 11, 0, "+", 7 | FOREGROUND_INTENSITY);
			break;
		}
		}

		while (int_y > 1)
		{
			int_x = 0;
			while (int_x < screen_x)
			{
				switch (array_pixels[int_x][int_y3]) {
				case 0:
				{
					switch (array_background[int_x][int_y3])
					{
					case 0: {
						Output(hStdOut, int_x, int_y, " ", 3 | FOREGROUND_INTENSITY);
						break;
					}
					case 1: {
						Output(hStdOut, int_x, int_y, "`", 3 | FOREGROUND_INTENSITY);
						break;
					}
					case 2: {
						Output(hStdOut, int_x, int_y, ".", 3 | FOREGROUND_INTENSITY);
						break;
					}
					}
					break;
				}
				case 1:
				{
					Output(hStdOut, int_x, int_y, ">", FOREGROUND_RED | FOREGROUND_INTENSITY);
					break;
				}
				case 2:
				{
					Output(hStdOut, int_x, int_y, "<", FOREGROUND_RED | FOREGROUND_INTENSITY);
					break;
				}
				case 3:
				{
					Output(hStdOut, int_x, int_y, "]", FOREGROUND_RED | FOREGROUND_INTENSITY);
					break;
				}
				case 4:
				{
					Output(hStdOut, int_x, int_y, "[", FOREGROUND_RED | FOREGROUND_INTENSITY);
					break;
				}
				case 5:
				{
					Output(hStdOut, int_x, int_y, "\\", 6 | FOREGROUND_INTENSITY);
					break;
				}
				case 6:
				{
					Output(hStdOut, int_x, int_y, "/", 6 | FOREGROUND_INTENSITY);
					break;
				}
				case 7:
				{
					Output(hStdOut, int_x, int_y, ")", FOREGROUND_RED | FOREGROUND_INTENSITY);
					break;
				}
				case 8:
				{
					Output(hStdOut, int_x, int_y, "(", FOREGROUND_RED | FOREGROUND_INTENSITY);
					break;
				}
				case 9:
				{
					Output(hStdOut, int_x, int_y, "o", 6 | FOREGROUND_INTENSITY);
					break;
				}
				case 10:
				{
					Output(hStdOut, int_x, int_y, "O", 6 | FOREGROUND_INTENSITY);
					break;
				}
				case 11:
				{
					Output(hStdOut, int_x, int_y, "_", 6 | FOREGROUND_INTENSITY);
					break;
				}
				case 12:
				{
					Output(hStdOut, int_x, int_y, ".", 6 | FOREGROUND_INTENSITY);
					break;
				}
				case 13:
				{
					Output(hStdOut, int_x, int_y, "|", 6 | FOREGROUND_INTENSITY);
					break;
				}
				case 14:
				{
					Output(hStdOut, int_x, int_y, " ", FOREGROUND_RED | FOREGROUND_INTENSITY);
					break;
				}
				case 15:
				{
					Output(hStdOut, int_x, int_y, "#", FOREGROUND_RED | FOREGROUND_INTENSITY);
					break;
				}
				case 16:
				{
					Output(hStdOut, int_x, int_y, "u", 6 | FOREGROUND_INTENSITY);
					break;
				}
				case 17:
				{
					Output(hStdOut, int_x, int_y, "w", 6 | FOREGROUND_INTENSITY);
					break;
				}
				case 18:
				{
					Output(hStdOut, int_x, int_y, "\\", FOREGROUND_RED | FOREGROUND_INTENSITY);
					break;
				}
				case 19:
				{
					Output(hStdOut, int_x, int_y, "/", FOREGROUND_RED | FOREGROUND_INTENSITY);
					break;
				}
				case 20:
				{
					Output(hStdOut, int_x, int_y, "@", 15 | FOREGROUND_INTENSITY);
					break;
				}
				}
				array_pixels[int_x][int_y3] = 0;
				int_x = int_x + 1;
			}
			int_y -= 1;
			int_y3 += 1;
		}
		this_thread::sleep_for(std::chrono::milliseconds(20));
	}
}

//Function Create Threads
void CreateThreads()
{
	thread t2(Obstacle1Movement);
	t2.detach();
	thread t3(Obstacle2Movement);
	t3.detach();
	thread t4(Obstacle3Movement);
	t4.detach();
	thread t5(CalcBackground);
	t5.detach();
	thread t6(Movement);
	t6.detach();
	thread t7(Movement2);
	t7.detach();
	thread t8(Obstacle1Collision);
	t8.detach();
	thread t10(CoinCollision);
	t10.detach();
	thread t11(LevelUp);
	t11.detach();
	thread t12(Render);
	t12.detach();
	thread t13(PlayersAnimation);
	t13.detach();
}

//Function Play
void Play()
{
	scene = 2;
	system("CLS");
	CreateThreads();
}

//Function Render Menu
void RenderMenu()
{
	switch (selected_option)
	{
	case 1:
	{
		system("CLS");
		cout << "  <<PLAY>> " << endl;
		cout << "  SETTINGS " << endl;
		cout << "    QUIT   " << endl;
		cout << "" << endl;
		ifstream file;
		file.open("Highscore.txt");
		file >> highscore;
		file.close();
		cout << "Highscore: " << highscore << endl;
		cout << "" << endl;
		cout << "Controls: A-Left W-Up S-Down D-Right" << endl;
		char_pressed = _getch();
		if (GetKeyState('S') & 0x8000)
		{
			selected_option = 2;
		}
		if (GetKeyState('D') & 0x8000)
		{
			Play();
		}
		break;
	}
	case 2:
	{
		system("CLS");
		cout << "    PLAY " << endl;
		cout << "<<SETTINGS>> " << endl;
		cout << "    QUIT   " << endl;
		cout << "" << endl;
		ifstream file;
		file.open("Highscore.txt");
		file >> highscore;
		file.close();
		cout << "Highscore: " << highscore << endl;
		cout << "" << endl;
		cout << "Controls: A-Left W-Up S-Down D-Right" << endl;
		char_pressed = _getch();
		if (GetKeyState('S') & 0x8000)
		{
			selected_option = 3;
		}
		else if (GetKeyState('W') & 0x8000)
		{
			selected_option = 1;
		}
		if (GetKeyState('D') & 0x8000)
		{
			RenderOptions();
			scene = 3;
		}
		break;
	}
	case 3:
	{
		system("CLS");
		cout << "    PLAY " << endl;
		cout << "  SETTINGS   " << endl;
		cout << "  <<QUIT>> " << endl;
		cout << "" << endl;
		ifstream file;
		file.open("Highscore.txt");
		file >> highscore;
		file.close();
		cout << "Highscore: " << highscore << endl;
		cout << "" << endl;
		cout << "Controls: A-Left W-Up S-Down D-Right" << endl;
		char_pressed = _getch();
		if (GetKeyState('W') & 0x8000)
		{
			selected_option = 2;
		}
		if (GetKeyState('D') & 0x8000)
		{
			exit(1);
		}
		break;
	}
	}
	Sleep(3);

}

//Function Background Music
void BackgroundMusic()
{
	// PlaySoundW(sound_background_path, NULL, SND_ASYNC | SND_LOOP | SND_NOSTOP);
}

//Core Function
int main(int argc, char** argv)
{
	//Optimize cout (print whole lines)
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	//Reset Pixels Array
	for (int y = 0; y < screen_x; y++)
	{
		for (int x = 0; x < screen_y - 1; x++)
		{
			array_pixels[x][y] = 0;
		}
	}

	//Set Console Font
	PCONSOLE_FONT_INFOEX lpConsoleCurrentFontEx = new CONSOLE_FONT_INFOEX();
	lpConsoleCurrentFontEx->cbSize = sizeof(CONSOLE_FONT_INFOEX);
	GetCurrentConsoleFontEx(out, 0, lpConsoleCurrentFontEx);
	lpConsoleCurrentFontEx->dwFontSize.X = 25;
	lpConsoleCurrentFontEx->dwFontSize.Y = 25;
	SetCurrentConsoleFontEx(out, 0, lpConsoleCurrentFontEx);

	//Set Console Title
	LPCSTR Title = "Swimmer - The Game";
	SetConsoleTitle(Title);

	//Set Console Size
	HWND console = GetConsoleWindow();
	RECT ConsoleRect;
	GetWindowRect(console, &ConsoleRect);
	MoveWindow(console, ConsoleRect.left, ConsoleRect.top, 800, 800, TRUE);

	BackgroundMusic();

	while (true) {
		switch (scene)
		{
		case 1:
		{
			RenderMenu();
			break;
		}
		case 2:
		{
			//Functions in threads
			break;
		}
		case 3:
		{
			RenderOptions();
			break;
		}
		}
	}
	return 0;
}
