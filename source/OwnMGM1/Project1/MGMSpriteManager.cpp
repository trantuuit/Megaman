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
	sprites[SPR_OCTOPUSBATTERY] = new MGMSprite();
	sprites[SPR_OCTOPUSBATTERY]->initInfo("Data\\Animation\\OctopusBattery.txt");
	sprites[SPR_OCTOPUSBATTERY]->pImage = sprites[SPR_PICKETMAN]->pImage;
	sprites[SPR_MEGAMAN] = new MGMSprite("Data\\Animation\\Rockman\\info.txt", "Data\\Animation\\Rockman\\image.png");
	sprites[SPR_BULLET] = new MGMSprite("Data\\Animation\\Rockman\\bullet-info.txt", "Data\\Animation\\Rockman\\bullet.png");
	
	//add

	sprites[SPR_BIGEYE] = new MGMSprite();
	sprites[SPR_BIGEYE]->initInfo("Data\\Animation\\BigEye.txt");
	sprites[SPR_BIGEYE]->pImage = sprites[SPR_PICKETMAN]->pImage;
}


MGMSpriteManager::~MGMSpriteManager()
{
	if (instance != 0)
		delete	instance;
}
