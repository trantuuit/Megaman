#include "MGMSpriteManager.h"


MGMSpriteManager* MGMSpriteManager::instance = 0;
MGMSpriteManager* MGMSpriteManager::getInstance()
{
	if (instance == 0)
		instance = new MGMSpriteManager();

	return instance;
}

MGMSpriteManager::MGMSpriteManager()
{
	sprites = new MGMSprite*[SPR_COUNT];
	sprites[SPR_PICKETMAN] = new MGMSprite("Data\\Animation\\PicketMan.txt", "Data\\Animation\\Enemies.png");
	//@Tu-Add
	sprites[SPR_OCTOPUSBATTERY] = new MGMSprite();
	sprites[SPR_OCTOPUSBATTERY]->initInfo("Data\\Animation\\OctopusBattery.txt");
	sprites[SPR_OCTOPUSBATTERY]->pImage = sprites[SPR_PICKETMAN]->pImage;

	sprites[SPR_MEGAMAN] = new MGMSprite("Data\\Animation\\Rockman\\info.txt", "Data\\Animation\\Rockman\\image.png");
	sprites[SPR_BULLET] = new MGMSprite("Data\\Animation\\Rockman\\bullet-info.txt", "Data\\Animation\\Rockman\\bullet.png");
	
	sprites[SPR_FLEA] = new MGMSprite();
	sprites[SPR_FLEA]->initInfo("Data\\Animation\\Flea.txt");
	sprites[SPR_FLEA]->pImage = sprites[SPR_PICKETMAN]->pImage;

	sprites
	//add

	sprites[SPR_BIGEYE] = new MGMSprite();
	sprites[SPR_BIGEYE]->initInfo("Data\\Animation\\BigEye.txt");
	sprites[SPR_BIGEYE]->pImage = sprites[SPR_PICKETMAN]->pImage;

	//@Tu-Add enemy Blader
	sprites[SPR_BLADER] = new MGMSprite();
	sprites[SPR_BLADER]->initInfo("Data\\Animation\\Blader.txt");
	sprites[SPR_BLADER]->pImage = sprites[SPR_PICKETMAN]->pImage;

	//@Tu-Add Flying Shell
	sprites[SPR_FLYING_SHELL] = new MGMSprite();
	sprites[SPR_FLYING_SHELL]->initInfo("Data\\Animation\\FlyingShell.txt");
	sprites[SPR_FLYING_SHELL]->pImage = sprites[SPR_PICKETMAN]->pImage;

	//@Dung - Add:
	sprites[SPR_BEAK] = new MGMSprite();
	sprites[SPR_BEAK]->initInfo("Data\\Animation\\Beak.txt");
	sprites[SPR_BEAK]->pImage = sprites[SPR_PICKETMAN]->pImage;
	sprites[SPR_BEAK_BULLET] = new MGMSprite("Data\\Animation\\Enemy Bullet\\beak-bullet-info.txt", "Data\\Animation\\Enemy Bullet\\Beak Bullet.png");
	//add
	//your code
}


MGMSpriteManager::~MGMSpriteManager()
{
	if (instance != 0)
		delete	instance;
}
