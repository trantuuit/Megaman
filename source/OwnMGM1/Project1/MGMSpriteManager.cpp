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
	sprites[SPR_PKM_WEAPON] = new MGMSprite();
	sprites[SPR_PKM_WEAPON]->initInfoFromPath("Data\\Animation\\PKMweapon.txt");
	sprites[SPR_PKM_WEAPON]->pImage = sprites[SPR_PICKETMAN]->pImage;
	//@Tu-Add
	sprites[SPR_OCTOPUSBATTERY] = new MGMSprite();
	sprites[SPR_OCTOPUSBATTERY]->initInfoFromPath("Data\\Animation\\OctopusBattery.txt");
	sprites[SPR_OCTOPUSBATTERY]->pImage = sprites[SPR_PICKETMAN]->pImage;

	sprites[SPR_MEGAMAN] = new MGMSprite("Data\\Animation\\Rockman\\info.txt", "Data\\Animation\\Rockman\\image.png");
	sprites[SPR_BULLET] = new MGMSprite("Data\\Animation\\Rockman\\bullet-info.txt", "Data\\Animation\\Rockman\\bullet.png");

	sprites[SPR_ITEM_EFFECT] = new MGMSprite();
	sprites[SPR_ITEM_EFFECT]->initInfoFromPath("Data\\Animation\\Effect\\itemEffect.txt");
	sprites[SPR_ITEM_EFFECT]->pImage = sprites[SPR_BULLET]->pImage;

	sprites[SPR_FLEA] = new MGMSprite();
	sprites[SPR_FLEA]->initInfoFromPath("Data\\Animation\\Flea.txt");
	sprites[SPR_FLEA]->pImage = sprites[SPR_PICKETMAN]->pImage;

	sprites[SPR_MET] = new MGMSprite();
	sprites[SPR_MET]->initInfoFromPath("Data\\Animation\\Met.txt");
	sprites[SPR_MET]->pImage = sprites[SPR_PICKETMAN]->pImage;

	sprites[SPR_SCREWBOMBER] = new MGMSprite();
	sprites[SPR_SCREWBOMBER]->initInfoFromPath("Data\\Animation\\ScrewBomber.txt");
	sprites[SPR_SCREWBOMBER]->pImage = sprites[SPR_PICKETMAN]->pImage;

	sprites[SPR_DOOR] = new MGMSprite("Data\\Animation\\Door\\Door.txt", "Data\\Animation\\Door\\Door.png");
	//add
	//@Tu-Add enemy Blader
	sprites[SPR_BLADER] = new MGMSprite();
	sprites[SPR_BLADER]->initInfoFromPath("Data\\Animation\\Blader.txt");
	sprites[SPR_BLADER]->pImage = sprites[SPR_PICKETMAN]->pImage;

	//@Tu-Add Flying Shell
	sprites[SPR_FLYING_SHELL] = new MGMSprite();
	sprites[SPR_FLYING_SHELL]->initInfoFromPath("Data\\Animation\\FlyingShell.txt");
	sprites[SPR_FLYING_SHELL]->pImage = sprites[SPR_PICKETMAN]->pImage;

	//@Dung - Add:
	sprites[SPR_BEAK] = new MGMSprite();
	sprites[SPR_BEAK]->initInfoFromPath("Data\\Animation\\Beak.txt");
	sprites[SPR_BEAK]->pImage = sprites[SPR_PICKETMAN]->pImage;
	sprites[SPR_BEAK_BULLET] = new MGMSprite("Data\\Animation\\Enemy Bullet\\beak-bullet-info.txt", "Data\\Animation\\Enemy Bullet\\Beak Bullet.png");

	//@Dung - BigEye
	sprites[SPR_BIGEYE] = new MGMSprite();
	sprites[SPR_BIGEYE]->initInfoFromPath("Data\\Animation\\BigEye Pink.txt");
	sprites[SPR_BIGEYE]->pImage = sprites[SPR_PICKETMAN]->pImage;

	//@Dung - SuperCutter
	sprites[SPR_SUPER_CUTTER] = new MGMSprite("Data\\Animation\\Super Cutter\\Super Cutter.txt", "Data\\Animation\\Super Cutter\\Super Cutter.png");

	//@Tu-bullet cut man
	sprites[SPR_CUTMANBULLET] = new MGMSprite();
	sprites[SPR_CUTMANBULLET]->initInfoFromPath("Data\\Animation\\CutmanBullet.txt");
	sprites[SPR_CUTMANBULLET]->pImage = sprites[SPR_PICKETMAN]->pImage;

	//@Tu-cut man
	sprites[SPR_CUTMAN] = new MGMSprite();
	sprites[SPR_CUTMAN]->initInfoFromPath("Data\\Animation\\cutman.txt");
	sprites[SPR_CUTMAN]->pImage = sprites[SPR_PICKETMAN]->pImage;
	//add
	//@Tu-Khoi tao sprite cho item
	//@item bonus ball
	sprites[SPR_ITEM_BONUS_BALL] = new MGMSprite("Data\\Item\\bonus_ball.txt", "Data\\Item\\Items.png");

	//@item life energy big
	sprites[SPR_ITEM_LIFE_ENERGY_BIG] = new MGMSprite();
	sprites[SPR_ITEM_LIFE_ENERGY_BIG]->initInfoFromPath("Data\\Item\\life_energy_big.txt");
	sprites[SPR_ITEM_LIFE_ENERGY_BIG]->pImage = sprites[SPR_ITEM_BONUS_BALL]->pImage;

	//@item life energy small
	sprites[SPR_ITEM_LIFE_ENERGY_SMALL] = new MGMSprite();
	sprites[SPR_ITEM_LIFE_ENERGY_SMALL]->initInfoFromPath("Data\\Item\\life_energy_small.txt");
	sprites[SPR_ITEM_LIFE_ENERGY_SMALL]->pImage = sprites[SPR_ITEM_BONUS_BALL]->pImage;

	//@item weapon energy big
	sprites[SPR_ITEM_WEAPON_ENERGY_BIG] = new MGMSprite();
	sprites[SPR_ITEM_WEAPON_ENERGY_BIG]->initInfoFromPath("Data\\Item\\weapon_energy_big.txt");
	sprites[SPR_ITEM_WEAPON_ENERGY_BIG]->pImage = sprites[SPR_ITEM_BONUS_BALL]->pImage;

	//@item weapon energy small
	sprites[SPR_ITEM_WEAPON_ENERGY_SMALL] = new MGMSprite();
	sprites[SPR_ITEM_WEAPON_ENERGY_SMALL]->initInfoFromPath("Data\\Item\\weapon_energy_small.txt");
	sprites[SPR_ITEM_WEAPON_ENERGY_SMALL]->pImage = sprites[SPR_ITEM_BONUS_BALL]->pImage;

	//@item up
	sprites[SPR_ITEM_UP] = new MGMSprite();
	sprites[SPR_ITEM_UP]->initInfoFromPath("Data\\Item\\up.txt");
	sprites[SPR_ITEM_UP]->pImage = sprites[SPR_ITEM_BONUS_BALL]->pImage;

	//@item weapon energy small
	sprites[SPR_ITEM_YASHICHI] = new MGMSprite();
	sprites[SPR_ITEM_YASHICHI]->initInfoFromPath("Data\\Item\\yashichi.txt");
	sprites[SPR_ITEM_YASHICHI]->pImage = sprites[SPR_ITEM_BONUS_BALL]->pImage;

	//@Item medal
	sprites[SPR_ITEM_MEDAL] = new MGMSprite();
	sprites[SPR_ITEM_MEDAL]->initInfoFromPath("Data\\Item\\medal.txt");
	sprites[SPR_ITEM_MEDAL]->pImage = sprites[SPR_ITEM_BONUS_BALL]->pImage;
	////@score
	sprites[SPR_SCORE] = new MGMSprite("Data\\Animation\\Score\\score.txt", "Data\\Animation\\Score\\score.png");
	//@hp
	sprites[SPR_HP_MEGAMAN] = new MGMSprite("Data\\Animation\\HP\\megaman.txt", "Data\\Animation\\HP\\hp.png");
	
	sprites[SPR_HP_BOSS] = new MGMSprite();
	sprites[SPR_HP_BOSS]->initInfoFromPath("Data\\Animation\\HP\\boss.txt");
	sprites[SPR_HP_BOSS]->pImage = sprites[SPR_HP_MEGAMAN]->pImage;

	//@board
	sprites[SPR_BOARD] = new MGMSprite("Data\\Animation\\Board\\board.txt", "Data\\Animation\\Board\\board.png");
	//@game over menu
	sprites[SPR_ARROW] = new MGMSprite("Data\\Animation\\Gameover\\arrow.txt", "Data\\Animation\\Gameover\\arrow.png");
	//@effect megaman die
	sprites[SPR_DIE_AFFECT] = new MGMSprite("Data\\Animation\\Effect\\dieAffect.txt", "Data\\Animation\\Effect\\dieAffect.png");

	// Room
	sprites[SPR_ROOM] = new MGMSprite();
	sprites[SPR_ROOM]->initInfoFromPath("Data\\Animation\\Room.txt");
	sprites[SPR_ROOM]->pImage = sprites[SPR_PICKETMAN]->pImage;

	// Boss Gutsman
	sprites[SPR_BOSS_GUTSMAN] = new MGMSprite();
	sprites[SPR_BOSS_GUTSMAN]->initInfoFromPath("Data\\Animation\\BossGutsman.txt");
	sprites[SPR_BOSS_GUTSMAN]->pImage = sprites[SPR_PICKETMAN]->pImage;

	// BigRock
	sprites[SPR_BIGROCK] = new MGMSprite();
	sprites[SPR_BIGROCK]->initInfoFromPath("Data\\Animation\\BigRock.txt");
	sprites[SPR_BIGROCK]->pImage = sprites[SPR_PICKETMAN]->pImage;

	sprites[SPR_SMALLROCK] = new MGMSprite("Data\\Animation\\Enemy Bullet\\small-rock-info.txt", "Data\\Animation\\Enemy Bullet\\Small Rock.png");

	// GreenBar
	sprites[SPR_GREENBAR] = new MGMSprite();
	sprites[SPR_GREENBAR]->initInfoFromPath("Data\\Animation\\GreenBar.txt");
	sprites[SPR_GREENBAR]->pImage = sprites[SPR_PICKETMAN]->pImage;

	// Blink
	sprites[SPR_BLINK] = new MGMSprite();
	sprites[SPR_BLINK]->initInfoFromPath("Data\\Animation\\Blink.txt");
	sprites[SPR_BLINK]->pImage = sprites[SPR_PICKETMAN]->pImage;

	// CutMan_Room
	sprites[SPR_CUTMAN_ROOM] = new MGMSprite();
	sprites[SPR_CUTMAN_ROOM]->initInfoFromPath("Data\\Animation\\CutmanRoom.txt");
	sprites[SPR_CUTMAN_ROOM]->pImage = sprites[SPR_PICKETMAN]->pImage;
	//your code
}


MGMSpriteManager::~MGMSpriteManager()
{
	for (int i = 0; i < SPR_COUNT; i++)
	{
		if (sprites[i] != 0) delete sprites[i];
	}
	if (sprites != 0) delete[] sprites;

	if (instance != 0)
		delete	instance;
}
