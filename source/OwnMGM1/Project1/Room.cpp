#include "Room.h"


bool Room::isVibrate = false;
Room* Room::room = 0;
Room* Room::getInstance(){
	if (room == 0){
		room = new Room();
	}
	return room;
}
Room::Room()
{
	ax = 0;
	vx = 0;
	ay = 0;
	vy = 0;
	objectDirection = LEFT;
	ActionCount = 0;
	vibrateCount = 0;
	categoryEnemy = ROOM;
}


void Room::update()
{
	if (ActionCount <= 80) // Update Frame đủ 80 lần
	{
		MGMMovableObject::update();
		ActionCount++;
	}
	else
		curFrame = 1;
}

void Room::render()
{
	if (isVibrate == true) // Trạng thái rung = true
		if (vibrateCount <= 35) //Chỉ rung một số lần hữu hạn
		{
			MGMObject::vibrateRender();
			vibrateCount++;
		}
		else // Đã rung đủ số lần
		{
			isVibrate = false;
			vibrateCount = 0;
			MGMEnemy::render();
		}
	else
		MGMEnemy::render();
}


Room::~Room()
{
}
