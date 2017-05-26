#include "MGMObjectsCategory.h"



void MGMObjectsCategory::addObject(MGMObject * obj)
{
	switch (obj->collisionCategory)
	{
	case CC_ENEMY:			  
		enemyObjects._Add(obj);
		break;
	case CC_GROUND:			  
		groundObjects._Add(obj);
		break;
	case CC_BIGROCK:
		bigRockObjects._Add(obj);
		break;
	case CC_ITEM:	
		itemObjects._Add(obj);
		break;
	case CC_STAIRS:
		stairObjects._Add(obj);
		break;
		//add
	default:
		break;
	}
	allObjects._Add(obj);
}

void MGMObjectsCategory::removeObject(MGMObject * obj)
{
	switch (obj->collisionCategory)
	{
	case CC_ENEMY:
		enemyObjects._Remove(obj);
		break;
	case CC_GROUND:
		groundObjects._Remove(obj);
		break;
	case CC_BIGROCK:
		bigRockObjects._Remove(obj);
		break;
	case CC_ITEM:
		itemObjects._Remove(obj);
		break;
	case CC_STAIRS:
		stairObjects._Remove(obj);
		break;
	default:
		break;
	}
	allObjects._Remove(obj);
}

void MGMObjectsCategory::clear()
{
	enemyObjects.Clear();
	allObjects.Clear();
	groundObjects.Clear();
	itemObjects.Clear();
	stairObjects.Clear();
}

MGMObjectsCategory::MGMObjectsCategory()
{
}


MGMObjectsCategory::~MGMObjectsCategory()
{
}
