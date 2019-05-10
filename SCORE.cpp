#include<Windows.h>
#include<SDL.h>
#include<SDL_image.h>
#include<string>
#include<time.h>
using namespace std;
const int SCREEN_WIDTH = 480;
const int SCREEN_HEIGHT = 690;
SDL_Window* g_window = NULL;
SDL_Renderer* g_renderer = NULL;
//character
SDL_Surface* charac_surface = NULL;
SDL_Texture* charac_texture[2];
//character6
SDL_Rect characDes;
SDL_Surface* bar = NULL;
SDL_Texture* barTexture = NULL;
SDL_Rect barDes;
SDL_Rect barDes2;
SDL_Rect barDes3;
SDL_Rect barDes4;
SDL_Surface* trap = NULL;
SDL_Texture* trapTexture = NULL;
SDL_Rect trapDes;
SDL_Rect trapDes2;
SDL_Rect trapDes3;
SDL_Event g_event;
SDL_Texture* numTeture[10];
SDL_Rect scoreDes;
int score = 0;
int Time = 250;
const int FPS = 60;
Uint32 frameStart;
Uint32 frameTime;
bool character = false;
bool gameEnd = false;
bool exitGame = false;
//
string intToString(int num)
{
	string rtNum = "";
	while (num != 0) {
		string tmp = " ";
		tmp[0] = num % 10+'0';
		num /= 10;
		rtNum =  tmp+rtNum ;
	}
	for (int i = rtNum.length(); i < 3; i++)
		rtNum = "0" + rtNum;
	return rtNum;
}
/////===================================================================//
void barmove(int& x, int& y) {
	y--;
	if (y == 1) {
		Time -= 1;
		score++;
		x = rand() % 340;
		y = SCREEN_HEIGHT;
	}
}//=====================================================================//
void trapmove(int& x, int& y) {
	y--;
	if (y == 1) {
		x = rand() % 340;
		y = SCREEN_HEIGHT;
	}
}

//=====================================================================//
void characmove(int& x, int& y, int& z, int& t, int& z2, int& t2, int& z3, int& t3, int& p, int& q, int& p1, int& q1) {

	if(g_event.type==SDL_KEYDOWN)
	switch (g_event.key.keysym.sym) {
	case SDLK_LEFT:
		x-=5-Time/FPS;
		character = false;
		break;
	case SDLK_RIGHT:
		x+=5-Time/FPS;
		character = true;
		break;
	default:
		break;
	}
	if (x >= z-7&&x <= z + 94 && y >= t - 30 && y <= t) {
		y = t -40;
	}
	else
		if (x >= z2-7&&x <= z2 + 94 && y >= t2 - 30 && y <= t2) {
			y = t2 - 40;
		}
		else
			if (x >= z3-7&&x <= z3 + 94 && y >= t3 - 30 && y <= t3) {
				y = t3 - 40;
			}
			else
				if (x >= p&&x <= p + 64 && y >= q - 30 && y <= q) {
					//SDL_Delay(1000);
					gameEnd = true;
				}
				else
					if (x > p1&&x <= p1 + 64 && y >= q1 - 30 && y <= q1) {
						//SDL_Delay(1000);
						gameEnd = true;
					}
					else
						y++;
	if (y == SCREEN_HEIGHT || y == 0) {
		//SDL_Delay(1000);
		gameEnd = true;
	}
	if (x == 446) {
		x = 445;
	}
	if (x == -4) {
		x = -3;
	}
}//======================================================================================//
bool init() {
	bool success = false;
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		return 1;
	}
	else {
		g_window = SDL_CreateWindow("Ahihi", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
	}
	return success;
}
//=================================================================================//
void gameOver() {
	Time = 250;
	SDL_Surface* gameOverpic = IMG_Load("gameOver.png");
	SDL_Texture* gameOverTexture = SDL_CreateTextureFromSurface(g_renderer, gameOverpic);
	SDL_FreeSurface(gameOverpic);
	SDL_RenderCopy(g_renderer, gameOverTexture, NULL, NULL);
	SDL_RenderPresent(g_renderer);
	SDL_Delay(2000);
	gameEnd = false;
	SDL_DestroyWindow(g_window);
	SDL_Quit();
	score = 0;
}//============================================================================================//
void startGame() {
	bool beginer = true;
	if (!init()) {
		int charac = rand() % 5;
		string link = "./";
		string tmp = " ";
		tmp[0] = charac + '0';
		link += tmp;
		string left = link + "left.png", right = link + "right.png";
		charac_surface = IMG_Load(left.c_str());
		SDL_SetColorKey(charac_surface, SDL_TRUE, SDL_MapRGB(charac_surface->format, 255, 255, 255));
		charac_texture[0] = SDL_CreateTextureFromSurface(g_renderer, charac_surface);
		charac_surface = IMG_Load(right.c_str());
		SDL_SetColorKey(charac_surface, SDL_TRUE, SDL_MapRGB(charac_surface->format, 255, 255, 255));
		charac_texture[1] = SDL_CreateTextureFromSurface(g_renderer, charac_surface);
		SDL_FreeSurface(charac_surface);

		for (int i = 0; i < 10; i++)
		{
			string tmp = " ";
			string link = "score/";
			tmp[0] = (char)(i + '0');
			link += tmp;
			link += ".png";
			SDL_Surface* tmpSurface = IMG_Load(link.c_str());
			SDL_SetColorKey(tmpSurface, SDL_TRUE, SDL_MapRGB(tmpSurface->format, 255, 255, 255));
			numTeture[i] = SDL_CreateTextureFromSurface(g_renderer, tmpSurface);
			SDL_FreeSurface(tmpSurface);
		}
		scoreDes.h = scoreDes.w = 30;

		SDL_Texture* background = IMG_LoadTexture(g_renderer, "bg.png");//background
		SDL_Texture* beginTextue = IMG_LoadTexture(g_renderer, "start.png");
		//SDL_Surface* picture = IMG_Load("begin.png");
		//SDL_SetColorKey(picture, SDL_TRUE, SDL_MapRGB(picture->format, 255, 255, 255));
		SDL_Texture*picturebegin = NULL;
		//picturebegin = SDL_CreateTextureFromSurface(g_renderer, picture);
		//SDL_FreeSurface(picture);
		SDL_Rect picDes;
		SDL_Rect picDes2;
		SDL_QueryTexture(picturebegin, NULL, NULL, &picDes.w, &picDes.h);
		picDes.x = 130;
		picDes.y = 20;
		picDes.w = 250;
		picDes.h = 250;
		SDL_QueryTexture(picturebegin, NULL, NULL, &picDes2.w, &picDes2.h);
		picDes2.x = 120;
		picDes2.y = 10;
		picDes2.w = 250;
		picDes2.h = 250;
		SDL_Rect beginDes;
		SDL_QueryTexture(beginTextue, NULL, NULL, &beginDes.w, &beginDes.h);
		beginDes.x = 100;
		beginDes.y = 445;
		beginDes.w = 300;
		beginDes.h = 250;
		int i = 0;
		while (beginer) {
			SDL_RenderClear(g_renderer);//clear render
			while (SDL_PollEvent(&g_event)) {
				if (g_event.type == SDL_QUIT) {
					SDL_DestroyWindow(g_window);
					SDL_Quit();
					exit(0);
					break;
				}
				else
				if (g_event.key.keysym.sym == SDLK_RETURN) {
					beginer = false;
					break;

				}
				else
				{
					if (g_event.key.keysym.sym == SDLK_ESCAPE)
					{
						SDL_DestroyWindow(g_window);
						SDL_Quit();
						exit(0);
						break;
					}
				}

			}
			if (i % 2 == 0) {
				SDL_RenderCopy(g_renderer, background, NULL, NULL);
				SDL_RenderCopy(g_renderer, beginTextue, NULL, &beginDes);
				SDL_RenderCopy(g_renderer, charac_texture[1], NULL, &picDes);
				SDL_RenderPresent(g_renderer);
			}
			else if (i % 2 == 1) {
				SDL_RenderCopy(g_renderer, background, NULL, NULL);
				SDL_RenderCopy(g_renderer, charac_texture[1], NULL, &picDes2);
				SDL_RenderPresent(g_renderer);
			}
			SDL_Delay(300);
			i++;
			if (i == 100) {
				i = 1;
			}
		}
		//===========================================================================//



		characDes.w = characDes.h = 50;
		characDes.x = 250;
		characDes.y = 120;////////////<====
		bar = IMG_Load("bar.png");//////////=>bar
		SDL_SetColorKey(bar, SDL_TRUE, SDL_MapRGB(bar->format, 255, 255, 255));
		barTexture = SDL_CreateTextureFromSurface(g_renderer, bar);
		SDL_QueryTexture(barTexture, NULL, NULL, &barDes.w, &barDes.h);
		barDes.x = rand() % 340;
		barDes.y = 400;
		barDes.w = 100;
		barDes.h = 30;
		SDL_QueryTexture(barTexture, NULL, NULL, &barDes2.w, &barDes2.h);
		barDes2.x = rand() % 340;
		barDes2.y = 600;
		barDes2.w = 100;
		barDes2.h = 30;
		SDL_QueryTexture(barTexture, NULL, NULL, &barDes3.w, &barDes3.h);
		barDes3.x = rand() % 340;
		barDes3.y = 900;
		barDes3.w = 100;
		barDes3.h = 30;
		SDL_QueryTexture(barTexture, NULL, NULL, &barDes.w, &barDes.h);
		barDes.x = rand() % 340;
		barDes.y = 780;
		barDes.w = 100;
		barDes.h = 30; ////////<===
					   //====================================================================================//
		trap = IMG_Load("trap.png");//=>trap
		SDL_SetColorKey(trap, SDL_TRUE, SDL_MapRGB(trap->format, 255, 255, 255));
		trapTexture = SDL_CreateTextureFromSurface(g_renderer, trap);
		SDL_QueryTexture(trapTexture, NULL, NULL, &trapDes.w, &trapDes.h);
		trapDes.x = rand() % 380;
		trapDes.y = rand() % 900+70;
		trapDes.w = 70;
		trapDes.h = 20;
		SDL_QueryTexture(trapTexture, NULL, NULL, &trapDes2.w, &trapDes2.h);
		trapDes2.x = rand() % 380;
		trapDes.y = rand() % 900+70;
		trapDes2.w = 70;
		trapDes2.h = 20;
		SDL_QueryTexture(trapTexture, NULL, NULL, &trapDes.w, &trapDes.h);
		trapDes3.x = rand() % 380;
		trapDes3.y = 700;
		trapDes3.w = 70;
		trapDes3.h = 20;
		while (!gameEnd) {//==>loop
			frameStart = SDL_GetTicks();//fps
			barmove(barDes.x, barDes.y);//move bar
			barmove(barDes2.x, barDes2.y);//move bar 2
			barmove(barDes3.x, barDes3.y);//move bar 3
			trapmove(trapDes.x, trapDes.y);
			trapmove(trapDes2.x, trapDes2.y);
			SDL_RenderCopy(g_renderer, background, NULL, NULL);/////
			string scoreTmp = intToString(score);
			for (int i = 0; i < scoreTmp.length(); i++)
			{
				scoreDes.x = 360 + i * 41;
				scoreDes.y = 0;
				switch (scoreTmp[i])
				{
				case '0':
					SDL_RenderCopy(g_renderer, numTeture[0], NULL, &scoreDes);
					break;
				case '1':
					SDL_RenderCopy(g_renderer, numTeture[1], NULL, &scoreDes);
					break;
				case '2':
					SDL_RenderCopy(g_renderer, numTeture[2], NULL, &scoreDes);
					break;
				case '3':
					SDL_RenderCopy(g_renderer, numTeture[3], NULL, &scoreDes);
					break;
				case '4':
					SDL_RenderCopy(g_renderer, numTeture[4], NULL, &scoreDes);
					break;
				case '5':
					SDL_RenderCopy(g_renderer, numTeture[5], NULL, &scoreDes);
					break;
				case '6':
					SDL_RenderCopy(g_renderer, numTeture[6], NULL, &scoreDes);
					break;
				case '7':
					SDL_RenderCopy(g_renderer, numTeture[7], NULL, &scoreDes);
					break;
				case '8':
					SDL_RenderCopy(g_renderer, numTeture[8], NULL, &scoreDes);
					break;
				case '9':
					SDL_RenderCopy(g_renderer, numTeture[9], NULL, &scoreDes);
					break;
				default:
					break;
				}
			}
			if (character)
			{
				SDL_RenderCopy(g_renderer, charac_texture[1], NULL, &characDes);///////print character
			}
			else
			{
				SDL_RenderCopy(g_renderer, charac_texture[0], NULL, &characDes);
			}
			SDL_RenderCopy(g_renderer, barTexture, NULL, &barDes);//////print bar 1
			SDL_RenderCopy(g_renderer, barTexture, NULL, &barDes2);//////print bar 2
			SDL_RenderCopy(g_renderer, barTexture, NULL, &barDes3);//////print bar 3
			SDL_RenderCopy(g_renderer, trapTexture, NULL, &trapDes);//////print trap 1
			SDL_RenderCopy(g_renderer, trapTexture, NULL, &trapDes2);//////print trap 2
			characmove(characDes.x, characDes.y, barDes.x, barDes.y, barDes2.x, barDes2.y, barDes3.x, barDes3.y, trapDes.x, trapDes.y, trapDes2.x, trapDes2.y);/////move character
			SDL_RenderPresent(g_renderer);///////update render
			frameTime = SDL_GetTicks() - frameStart;/////set fps
			if (frameTime < Time/FPS) {
				SDL_Delay((Time/FPS) - frameTime);
			}/////////<===EndLoop
			while (SDL_PollEvent(&g_event)) {
				switch (g_event.type)                         //
				{                                             //
				case SDL_QUIT: {
					exitGame = true;
					SDL_DestroyWindow(g_window);
					SDL_Quit();
					break;
				}
				default:                                      //
					break;                                    //
				}
			}
		}
	}//============================================================================================================//
}
int main(int arc, char* argv[]) {
	srand(time(0));

	while (!exitGame) {
		startGame();
		gameOver();
	}
	SDL_DestroyWindow(g_window);
	SDL_Quit();
	return 0;
}