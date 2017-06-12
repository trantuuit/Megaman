#include "CutmanBullet.h"
#include "BossCutMan.h"
#include "Megaman.h"

CutmanBullet* CutmanBullet::bullet = 0;

CutmanBullet* CutmanBullet::getBullet()
{
	if (bullet == 0)
	{
		bullet = new CutmanBullet();
	}
	return bullet;
}
CutmanBullet::CutmanBullet()
{
	fileLog.open("abcFileLox.txt", ios::out | ios::app);
	categoryEnemy = CUTMAN_WEAPON;
	dx = 0;
	dy = 0;
	vx = 0;
	vy = 0;
	ax = 0;
	ay = 0;
	sprite = MGMSpriteManager::getInstance()->sprites[SPR_CUTMANBULLET];
	//x = CutMan::getInstance()->x + 6;
	//y = CutMan::getInstance()->y;
	init(x, y, 14, 10);
	isThrow = false;
	isBack = false;

	if (BossCutMan::getInstance()->objectDirection == LEFT)
		x = BossCutMan::getInstance()->getXCenter();
	else
		x = BossCutMan::getInstance()->x;
	y = BossCutMan::getInstance()->y;

	bullet = this;
}

void CutmanBullet::update()
{
	CUTMAN_ACTION cutmanCurAction = BossCutMan::getInstance()->action;
	int cutmanCurFrame = BossCutMan::getInstance()->curFrame;

	if (BossCutMan::getInstance()->isThrow == true && this->isThrow == false)
	{
		// Xác định hướng bay theo phương x và y:
		directionX = (Megaman::getInstance()->x < x) ? C_LEFT : C_RIGHT;
		directionY = (Megaman::getInstance()->y < y) ? C_BOTTOM : C_TOP;
		// Đo khoảng cách giữa Megaman và Cutman
		float distanceX = abs(Megaman::getInstance()->getXCenter() - BossCutMan::getInstance()->getXCenter());
		float distanceY = abs(Megaman::getInstance()->y - y);

		if (distanceX <= 10)
		{
			dx = 0.5 * directionX;
			dy = 3 * directionY;
		}
		else
		{
			// Gán cho dx = 2
			dx = 2 * directionX;
			float a = abs(dx) / distanceX; // Tỷ số giữa dx và distanceX
			dy = (a * distanceY) * directionY; // Từ tỷ số đó tính ra dy tương ứng
											   // Fix lại nếu dy quá nhỏ hoặc quá lớn (do a quá lớn hoặc quá nhỏ)
			if (dy < -3)
				dy = -3;
			if (dy > 3)
				dy = 3;
		}

		setCurAction(1); //Set action bay cho CutmanBullet
		isThrow = true;
	}
	if (x <= 3095 || y >= 1425 || x >= 3335 || y <= 1225)
	{
		isBack = true; // Xác định việc quay trở lại
	}
	if (isBack)
	{
		// Tính quãng đường quay về tương tự như trên
		backDirectionX = (x > BossCutMan::getInstance()->x) ? C_LEFT : C_RIGHT;
		backDirectionY = (y > BossCutMan::getInstance()->y) ? C_BOTTOM : C_TOP;
		float distanceX = abs(BossCutMan::getInstance()->getXCenter() - this->getXCenter());
		float distanceY = abs(BossCutMan::getInstance()->y - y);
		dx = 2 * backDirectionX;
		float a = abs(dx) / distanceX;
		dy = (a * distanceY) * backDirectionY;
		if (dy < -3)
			dy = -3;
		if (dy > 3)
			dy = 3;
	}


	//fileLog << dx << "\t" << dy << "\t" << cutmanCurAction << "\t" << cutmanCurFrame << endl;
	MGMMovableObject::updateFrameAnimation();
}
void CutmanBullet::render()
{
	if (bullet != NULL)
		MGMEnemy::render();
}

void CutmanBullet::onCollision(MGMBox* otherObject, int nx, int ny)
{
	MGMMovableObject* m = (MGMMovableObject*)otherObject;
	if (m->id == 9)
	{
		if (isBack) //Nếu đã quay trở lại và va chạm thì set isThrow của Cutman là false
		{
			isThrow = false;
			isBack = false;
			BossCutMan::getInstance()->isThrow = false;
			BossCutMan::getInstance()->setCutmanAction(BossCutMan::getInstance()->action); //Set lại action do isThrow thay đổi

			delete bullet;
			bullet = NULL;
		}
	}

}
void CutmanBullet::onIntersectRect(MGMBox * otherObject)
{
	MGMMovableObject* m = (MGMMovableObject*)otherObject;
	if (m->id == 9 && isBack)
	{
		isThrow = false;
		isBack = false;
		BossCutMan::getInstance()->isThrow = false;
		BossCutMan::getInstance()->setCutmanAction(BossCutMan::getInstance()->action); //Set lại action do isThrow thay đổi

		delete bullet;
		bullet = NULL;
	}
}
CutmanBullet::~CutmanBullet()
{
}
