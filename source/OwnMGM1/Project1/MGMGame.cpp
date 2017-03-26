#include "MGMGame.h"
#include"Keyboard.h"
#include"MGMDirectXTool.h"
#include"KEY.h"
MGMGame::MGMGame()
{
}
MGMGame* MGMGame::instance = 0;
MGMGame *MGMGame::getInstance()
{
	if (instance == 0) instance = new MGMGame();
	return instance;
}

MGMGame::~MGMGame()
{

}
void MGMGame::init()
{
	
	Megaman::getInstance()->x = 84;
	Megaman::getInstance()->y = 111;

	MGMCamera::getInstance()->init(0, 206, BACKBUFFER_WIDTH, BACKBUFFER_HEIGHT);
	MGMCamera::getInstance()->dx = 0;
	MGMCamera::getInstance()->dy = 0;
	//Khoi tao map
	map = new MGMMap("Data\\TileMap\\objects.txt", "Data\\TileMap\\tileSheet.png", "Data\\TileMap\\quadtree.txt", "Data\\TileMap\\matrix.txt",
		"Data\\TileMap\\stage.txt");
}
void MGMGame::render()
{

	map->draw();
	Megaman::getInstance()->render();
	
}
void MGMGame::update(DWORD timesleep)
{

	Megaman::getInstance()->update(); // Cap nhat van toc cua MGM
	map->update();
	MGMCamera::getInstance()->update(); 
	Megaman::getInstance()->updateLocation(); // Cap nhat toa do cua MGM
}