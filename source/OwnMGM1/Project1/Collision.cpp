#include "Collision.h"
#include <iostream>     // std::cout
#include <limits>       // std::numeric_limits
#include <algorithm>
#include "MGMMovableObject.h"



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
	// Code mới
	return ((M->getLeft() <= S->getRight() && M->getRight() >= S->getLeft()) &&
		(M->getBottom() <= S->getTop() && M->getTop() >= S->getBottom()));

	//Code cũ:
	/*return ((M->x < S->x + S->width && M->x + M->width > S->x) &&
		(M->y - M->height < S->y && M->y > S->y - S->height));*/
}

float sweptTime;
float nx, ny;
void Collision::checkCollision(MGMBox*M, MGMBox*S)
{
	int oldDx = M->dx;
	int oldDy = M->dy;
	/*float oldDx = M->dx;
	float oldDy = M->dy;*/
	M->dx -= S->dx;
	M->dy -= S->dy;
	MGMBox* broadPhaseBox = GetSweptBroadphaseBox(M);
	if (AABBCheck(broadPhaseBox, S))
	{
		delete broadPhaseBox;
		broadPhaseBox = NULL;
		if (AABBCheck(S, M))
		{
			
			M->dx = oldDx;
			M->dy = oldDy;
			S->onIntersectRect(M);
			M->onIntersectRect(S);
			return;
		}
		float nx, ny;

		float sweptTime = SweptAABB(M, S, nx, ny);
		M->dx = oldDx;
		M->dy = oldDy;
		if (sweptTime < 1.0)
		{
			//chac chan co va cham
			M->isCollision = true;
			bool nyCheck = M->getLeft() <= S->getRight() && M->getRight() >= S->getLeft();  //Kiểm tra có giao nhau theo phương x
			if (!nyCheck)
				ny = 0;     // Va chạm theo phương y nhưng ko giao nhau theo phương x thì nx=0

			//bool nxCheck = M->getBottom() <= S->getTop() && M->getTop() >= S->getBottom();  //Kiểm tra có giao nhau theo phương y
			//if (!nxCheck) nx = 0;     // Va chạm theo  phương x nhưng không giao nhau theo phương y thì ny=0( cái này ko cần thiết trong game này)
			M->onCollision(S, nx, ny);
			S->onCollision(M, -nx, -ny);
		}
		return;
	}
	else {
		M->dx = oldDx;
		M->dy = oldDy;
	}
	if (broadPhaseBox != NULL) delete broadPhaseBox;

}

void Collision::preventMove(MGMBox*M, MGMBox*S, int nx, int ny)
{
	M->isPreventMove = false;

	if (nx == -1)
	{
		M->dx = S->getLeft() - M->getRight() - 1;
		M->isPreventMove = true;
	}
	else if (nx == 1)
	{
		M->dx = S->getRight() - M->getLeft() + 1;
		M->isPreventMove = true;
	}

	if (ny == -1)
	{
		M->dy = S->getBottom() - M->getTop() - 1;
		M->isPreventMove = true;
	}
	else if (ny == 1)
	{
		M->dy = S->getTop() - M->getBottom() + 1;
		M->isPreventMove = true;

	}
}



float Collision::SweptAABB(MGMBox* M, MGMBox* S, float & normalx, float & normaly)
{
	//code mới:
	float xInvEntry, yInvEntry;
	float xInvExit, yInvExit;

	// Tính khoảng cách cần để xảy ra va chạm (InvEntry) và khoảng cách để ra khỏi va chạm (InvExit):
	if (M->dx > 0.0f)
	{
		xInvEntry = S->x - M->getRight() - 1;
		xInvExit = S->getRight() - M->x;
	}
	else
	{
		xInvEntry = S->getRight() - M->x + 1;
		xInvExit = S->x - M->getRight();
	}

	if (M->dy < 0.0f)
	{
		yInvEntry = S->y - M->getBottom() + 1;
		yInvExit = S->getBottom() - M->y;
	}
	else
	{
		yInvEntry = S->getBottom() - M->y - 1;
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
	//--------------------

	//Code cũ:
	//float xInvEntry, yInvEntry;
	//float xInvExit, yInvExit;

	//// Tính khoảng cách cần để xảy ra va chạm (InvEntry) và khoảng cách để ra khỏi va chạm (InvExit):
	//if (M->dx > 0.0f)
	//{
	//	xInvEntry = S->x - (M->x + M->width);
	//	xInvExit = (S->x + S->width) - M->x;
	//}
	//else
	//{
	//	xInvEntry = (S->x + S->width) - M->x;
	//	xInvExit = S->x - (M->x + M->width);
	//}

	//if (M->dy > 0.0f)
	//{
	//	yInvEntry = S->y - S->height - M->y;
	//	yInvExit = S->y - (M->y - M->height);
	//}
	//else
	//{
	//	yInvEntry = S->y - (M->y - M->height);
	//	yInvExit = (S->y - S->height) - M->y;
	//}

	//// Tính thời gian để bắt đầu và chạm và thời gian để kết thúc va chạm theo mỗi phương:
	//float xEntry, yEntry;
	//float xExit, yExit;

	//if (M->dx == 0.0f)
	//{
	//	xEntry = -std::numeric_limits<float>::infinity();
	//	xExit = std::numeric_limits<float>::infinity();
	//}
	//else
	//{
	//	xEntry = xInvEntry / (float)M->dx;
	//	xExit = xInvExit / (float)M->dx;
	//}

	//if (M->dy == 0.0f)
	//{
	//	yEntry = -std::numeric_limits<float>::infinity();
	//	yExit = std::numeric_limits<float>::infinity();
	//}
	//else
	//{
	//	yEntry = yInvEntry / (float)M->dy;
	//	yExit = yInvExit / (float)M->dy;
	//}

	//// Thời gian để Box bắt đầu va chạm và thời gian để kết thúc va chạm:
	//float entryTime = MAX(xEntry, yEntry);
	//float exitTime = MIN(xExit, yExit);

	//// Trường hợp không xảy ra va chạm:
	////Logger::getInstance()->write_text_to_log_file(std::to_string(GetVy()));
	//if (entryTime > exitTime || xEntry < 0.0f && yEntry < 0.0f || xEntry > 1.0f || yEntry > 1.0f)
	//{
	//	normalx = 0.0f;
	//	normaly = 0.0f;
	//	return 1.0f;
	//}

	//else // Trường hợp xảy ra va chạm:
	//{
	//	// Xác định hướng của pháp tuyến khi va chạm:
	//	if (xEntry > yEntry)
	//	{
	//		if (M->dx < 0.0f) // Chạm vào bề mặt bên phải của block:
	//		{
	//			normalx = 1.0f;
	//			normaly = 0.0f;
	//		}
	//		else					// Chạm vào bề mặt bên trái của block:
	//		{
	//			normalx = -1.0f;
	//			normaly = 0.0f;
	//		}
	//	}
	//	else
	//	{
	//		if (M->dy < 0.0f) // Chạm vào bề mặt phía trên của block:
	//		{
	//			normalx = 0.0f;
	//			normaly = 1.0f;
	//		}
	//		else					// Chạm vào bề mặt phía dưới của block:
	//		{
	//			normalx = 0.0f;
	//			normaly = -1.0f;
	//		}
	//	}

	//	// Trả về khoảng thời gian cần thiết để bắt đầu xảy ra va chạm:
	//	return entryTime;
	//}
}
