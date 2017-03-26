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
	bigBox->x = box->dx > 0 ? box->x : (box->x + box->dx);
	bigBox->y = box->dy > 0 ? (box->y + box->dy) : box->y;
	bigBox->width = box->dx > 0 ? (box->width + box->dx) : (box->width - box->dx);
	bigBox->height = box->dy > 0 ? (box->height + box->dy) : (box->height - box->dy);
	return bigBox;
}

bool Collision::AABBCheck(MGMRectangle* M, MGMRectangle* S)
{
	return ((M->getLeft() < S->getRight() && M->getRight() > S->getLeft()) &&
		(M->getBottom() < S->getTop() && M->getTop() > S->getBottom()));
}

void Collision::checkCollision(MGMBox*M, MGMBox*S)
{
	MGMBox* broadPhaseBox = GetSweptBroadphaseBox(M);

	if (AABBCheck(broadPhaseBox, S))
	{
		delete broadPhaseBox;
		if (AABBCheck(S, M))
		{
			S->onInterserct(M);
			M->onInterserct(S);
			return;
		}
		float nx, ny;

		//float sweptTime = SweptAABB(M, S, nx, ny);
		//if (sweptTime < 1.0)
		{
			//chac chan co va cham
			M->isCollision = true;
			nx = 0;
			ny = 0;
			if (M->getLeft() < S->getRight() && M->getRight() > S->getLeft())
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
			//S->onCollision(M, nx, ny);
			return;
		}
	}
	delete broadPhaseBox;

}

void Collision::preventMove(MGMBox*M, MGMBox*S)
{
	if (M->getTop() > S->getBottom() && M->getBottom() < S->getTop())
	{
		if (M->dx > 0)
		{
			M->dx = S->getLeft() - M->getRight();
		}
		else
		{
			M->dx = S->getRight() - M->getLeft();
		}
		M->isChangeDelta = true;
	}

	if (M->getRight() > S->getLeft() && M->getLeft() < S->getRight())
	{
		if (M->dy > 0)
		{
			M->dy = S->getBottom() - M->getTop();
		}
		else
		{
			M->dy = S->getTop() - M->getBottom();
		}
		M->isChangeDelta = true;
	}
}



float Collision::SweptAABB(MGMBox* M, MGMBox* S, float & normalx, float & normaly)
{
	normalx = 0.0f;
	normaly = 0.0f;
	float xInvEntry, yInvEntry;
	float xInvExit, yInvExit;

	if (M->dx > 0.0f)
	{
		xInvEntry = S->x - (M->x + M->width);
		xInvExit = (S->x + S->width) - M->x;
	}
	else
	{
		xInvEntry = (S->x + S->width) - M->x;
		xInvExit = S->x - (M->x + M->width);
	}

	if (M->dy > 0.0f)
	{
		yInvEntry = S->y - (M->y + M->height);
		yInvExit = (S->y + S->height) - M->y;
	}
	else
	{
		yInvEntry = (S->y + S->height) - M->y;
		yInvExit = S->y - (M->y + M->height);
	}

	float xEntry, yEntry;
	float xExit, yExit;

	if (M->dx == 0.0f)
	{
		xEntry = -std::numeric_limits<float>::infinity();
		xExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		xEntry = xInvEntry / M->dx;
		xExit = xInvExit / M->dx;
	}

	if (M->dy == 0.0f)
	{
		yEntry = -std::numeric_limits<float>::infinity();
		yExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		yEntry = yInvEntry / M->dy;
		yExit = yInvExit / M->dy;
	}

	float entryTime = MAX(xEntry, yEntry);
	float exitTime = MIN(xExit, yExit);

	//if (entryTime > exitTime || xEntry < 0.0f && yEntry < 0.0f || xEntry > 1.0f || yEntry > 1.0f)
	if (entryTime > exitTime || xEntry > 1.0f || yEntry > 1.0f)
	{
		normalx = 0.0f;
		normaly = 0.0f;
		return 1.0f;
	}
	else
	{
		if (M->getLeft() < S->getRight() && M->getRight() > S->getLeft())
		{
			if (M->dy > 0)
				normaly = -1;
			else
				normaly = 1;
			normalx = 0;
			return entryTime;
		}

		if (M->getTop() < S->getBottom() && M->getBottom() > S->getTop())
		{
			if (M->dx > 0)
				normalx = -1;
			else
				normalx = 1;
			normaly = 0;
		}
		return entryTime;
	}
}
