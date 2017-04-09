#include "Collision.h"
#include <iostream>     // std::cout
#include <limits>       // std::numeric_limits
#include <algorithm>



Collision::Collision()
{
}


Collision::~Collision()
{
}

MGMBox* Collision::GetSweptBroadphaseBox(MGMBox* box)
{
	MGMBox* bigBox = new MGMBox();
	bigBox->x = (box->dx > 0 ? box->x : (box->x + box->dx));
	bigBox->y = (box->dy > 0 ? (box->y + box->dy) : box->y);
	bigBox->width = (box->dx > 0 ? (box->width + box->dx) : (box->width - box->dx));
	bigBox->height = (box->dy > 0 ? (box->height + box->dy) : (box->height - box->dy));
	return bigBox;
}

bool Collision::AABBCheck(MGMRectangle* M, MGMRectangle* S)
{
	return ((M->getLeft() <= S->getRight()  && M->getRight()  >= S->getLeft()) &&
		(M->getBottom()  <= S->getTop() && M->getTop() >= S->getBottom() ));
}

void Collision::checkCollision(MGMBox*M, MGMBox*S)
{
	// + them van toc de S->dx va dy hoan toan bang 0
	//float oldDx = M->dx;
	//float oldDy = M->dy;
	//M->dx -= S->dx;
	//M->dy -= S->dy;
	MGMBox* broadPhaseBox = GetSweptBroadphaseBox(M);
	//M->dx = oldDx;
	//M->dy = oldDy;
	if (AABBCheck(broadPhaseBox, S))
	{
		delete broadPhaseBox;
		broadPhaseBox = NULL;
		if (AABBCheck(S, M))
		{
			S->onInterserct(M);
			M->onInterserct(S);
			return;
		}
		float nx, ny;

		float sweptTime = SweptAABB(M, S, nx, ny);
		if (sweptTime < 1.0)
		{
			//chac chan co va cham
			M->isCollision = true;
			nx = 0;
			ny = 0;
			if (M->getLeft() <= S->getRight() && M->getRight() >= S->getLeft())
			{
				if (M->dy > 0)
					ny = -1;
				else
					ny = 1;
			}
			else
			{
				if (M->dx > 0)
					nx = -1;
				else
					nx = 1;
			}
			M->onCollision(S, nx, ny);
			S->onCollision(M, nx, ny);
		}
		return;
	}
	if (broadPhaseBox != NULL) delete broadPhaseBox;

}

void Collision::preventMove(MGMBox*M, MGMBox*S)
{
	M->isChangeDelta = false;
	if (M->getTop() >= S->getBottom()  && M->getBottom()  <= S->getTop())
	{
		if (M->dx > 0)
		{
			M->dx = S->getLeft() - M->getRight()-1;
		}
		else
		{
			M->dx = S->getRight() - M->getLeft()+1;
		}
		M->isChangeDelta = true;
	}

	if (M->getRight() >= S->getLeft() && M->getLeft() <= S->getRight())
	{
		if (M->dy > 0)
		{
			M->dy = S->getBottom()  - M->getTop()-1;
		}
		else
		{
			M->dy = S->getTop() - M->getBottom()+1 ;
		}
		M->isChangeDelta = true;
	}
	/*if (!M->isChangeDelta)
	{
		if (M->dx > 0)
		{
			M->dx = S->getLeft() - M->getRight() - 1;
		}
		else
		{
			M->dx = S->getRight() - M->getLeft() + 1;
		}
		M->isChangeDelta = true;
		if (M->dy > 0)
		{
			M->dy = S->getBottom() - M->getTop() - 1;
		}
		else
		{
			M->dy = S->getTop() - M->getBottom() + 1;
		}
	}
*/
	/*float nx, ny;
	float sweptTime = SweptAABB(M, S, nx, ny);


	if (nx != 0) M->dx = int(sweptTime*M->dx);
	else if (ny != 0) M->dy = int(sweptTime*M->dy);
	if (nx != 0 || ny != 0) M->isChangeDelta = true;*/
	/*if (nx == -1)
	{
		M->dx = S->getLeft() - M->getRight();
	}
	else if (nx == 1)
	{
		M->dx = S->getRight() - M->getLeft();
	}
	if (ny == -1)
	{
		M->dy = S->getBottom() - M->getTop();
	}
	else if (ny == 1)
	{
		M->dy = S->getTop() - M->getBottom();
	}
	if (nx != 0 || ny != 0) M->isChangeDelta = true;*/

}



float Collision::SweptAABB(MGMBox* M, MGMBox* S, float & normalx, float & normaly)
{
	float xInvEntry, yInvEntry;
	float xInvExit, yInvExit;

	// Tính khoảng cách cần để xảy ra va chạm (InvEntry) và khoảng cách để ra khỏi va chạm (InvExit):
	if (M->dx > 0.0f)
	{
		xInvEntry = S->x - M->getRight()-1;
		xInvExit = S->getRight() - M->x;
	}
	else
	{
		xInvEntry = S->getRight() - M->x+1;
		xInvExit = S->x - M->getRight();
	}

	if (M->dy < 0.0f)
	{
		yInvEntry = S->y - M->getBottom()+1; 
		yInvExit = S->getBottom() - M->y;
	}
	else
	{
		yInvEntry = S->getBottom() - M->y-1;
		yInvExit = S->y - M->getBottom();
	}

	// Tính thời gian để bắt đầu và chạm và thời gian để kết thúc va chạm theo mỗi phương:
	float xEntry, yEntry;
	float xExit, yExit;

	if (M->dx == 0.0f)
	{
		xEntry = -std::numeric_limits<float>::infinity();
		xExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		xEntry = xInvEntry / (float)M->dx;
		xExit = xInvExit / (float)M->dx;
	}

	if (M->dy == 0.0f)
	{
		yEntry = -std::numeric_limits<float>::infinity();
		yExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		yEntry = yInvEntry / (float)M->dy;
		yExit = yInvExit / (float)M->dy;
	}

	// Thời gian để Box bắt đầu va chạm và thời gian để kết thúc va chạm:
	float entryTime = max(xEntry, yEntry);
	float exitTime = min(xExit, yExit);

	// Trường hợp không xảy ra va chạm:
	//Logger::getInstance()->write_text_to_log_file(std::to_string(GetVy()));
	if (entryTime > exitTime || xEntry < 0.0f && yEntry < 0.0f || xEntry > 1.0f || yEntry > 1.0f)
	{
		normalx = 0.0f;
		normaly = 0.0f;
		return 1.0f;
	}

	else // Trường hợp xảy ra va chạm:
	{
		// Xác định hướng của pháp tuyến khi va chạm:
		if (xEntry > yEntry)
		{
			if (M->dx < 0.0f) // Chạm vào bề mặt bên phải của block:
			{
				normalx = 1.0f;
				normaly = 0.0f;
			}
			else					// Chạm vào bề mặt bên trái của block:
			{
				normalx = -1.0f;
				normaly = 0.0f;
			}
		}
		else
		{
			if (M->dy < 0.0f) // Chạm vào bề mặt phía trên của block:
			{
				normalx = 0.0f;
				normaly = 1.0f;
			}
			else					// Chạm vào bề mặt phía dưới của block:
			{
				normalx = 0.0f;
				normaly = -1.0f;
			}
		}

		// Trả về khoảng thời gian cần thiết để bắt đầu xảy ra va chạm:
		return entryTime;
	}
}
