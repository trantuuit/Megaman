#include "CutmanBullet.h"
#include "CutMan.h"
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
	//fileLog.open("abcFileLox.txt", ios::out | ios::app);
	dx = 0;
	dy = 0;
	vx = 0;
	vy = 0;
	ax = 0;
	ay = 0;
	sprite = MGMSpriteManager::getInstance()->sprites[SPR_CUTMANBULLET];
	x = CutMan::getInstance()->x + 6;
	y = CutMan::getInstance()->y;
	init(x, y, 14, 10);
	isThrow = false;
	isBack = false;
}

void CutmanBullet::update()
{
	CUTMAN_ACTION cutmanCurAction = CutMan::getInstance()->action;
	int cutmanCurFrame = CutMan::getInstance()->curFrame;
	if (CutMan::getInstance()->isThrow == false) // Chưa ném
	{
		if (CutMan::getInstance()->objectDirection == LEFT)
			x = CutMan::getInstance()->getXCenter();
		else
			x = CutMan::getInstance()->x;
		y = CutMan::getInstance()->y;
		dx = 0;
		dy = 0;
	}

	if (cutmanCurAction == CM_ATTACK && cutmanCurFrame == 1 && isThrow == false) // Frame[1] của attack
	{
		// Xác định hướng bay theo phương x và y:
		directionX = (Megaman::getInstance()->x < x) ? C_LEFT : C_RIGHT;
		directionY = (Megaman::getInstance()->y < y) ? C_BOTTOM : C_TOP;
		// Đo khoảng cách giữa Megaman và Cutman
		float distanceX = abs(Megaman::getInstance()->getXCenter() - CutMan::getInstance()->getXCenter());
		float distanceY = abs(Megaman::getInstance()->y - y);

		// Gán cho dx = 2
		dx = 2 * directionX;
		float a = abs(dx) / distanceX; // Tỷ số giữa dx và distanceX
		dy = (a * distanceY) * directionY; // Từ tỷ số đó tính ra dy tương ứng
										   // Fix lại nếu dy quá nhỏ hoặc quá lớn (do a quá lớn hoặc quá nhỏ)
		if (dy < -3)
			dy = -3;
		if (dy > 3)
			dy = 3;
		//fileLog << dx << "\t" << a << "\t" << dy << endl;

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
		backDirectionX = (x > CutMan::getInstance()->x) ? C_LEFT : C_RIGHT;
		backDirectionY = (y > CutMan::getInstance()->y) ? C_BOTTOM : C_TOP;
		float distanceX = abs(CutMan::getInstance()->getXCenter() - this->getXCenter());
		float distanceY = abs(CutMan::getInstance()->y - y);
		dx = 2 * backDirectionX;
		float a = abs(dx) / distanceX;
		dy = (a * distanceY) * backDirectionY;
		if (dy < -3)
			dy = -3;
		if (dy > 3)
			dy = 3;
	}


	MGMMovableObject::updateFrameAnimation();
}
void CutmanBullet::render()
{
	if (isThrow)
		MGMEnemy::render();
}

void CutmanBullet::onCollision(MGMBox* otherObject, int nx, int ny)
{
	MGMMovableObject* m = (MGMMovableObject*)otherObject;
	if (m->id == 9)
	{
		if (isBack) //Nếu đã quay trở lại và va chạm thì set isThrow của Cutman là false
		{
			CutMan::getInstance()->isThrow = false;
			CutMan::getInstance()->setCutmanAction(CutMan::getInstance()->action); //Set lại action do isThrow thay đổi
		}
		isThrow = false;
		isBack = false;
	}

}
void CutmanBullet::onIntersectRect(MGMBox * otherObject)
{
	MGMMovableObject* m = (MGMMovableObject*)otherObject;
	if (m->id == 9 && isBack)
	{
		isThrow = false;
		isBack = false;
		CutMan::getInstance()->isThrow = false;
		CutMan::getInstance()->setCutmanAction(CutMan::getInstance()->action); //Set lại action do isThrow thay đổi
	}
}
CutmanBullet::~CutmanBullet()
{
}
