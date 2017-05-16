#pragma once
#include"List.h"
#include"MGMObject.h"
class MGMObjectsCategory
{
public:
	List<MGMObject*> allObjects;
	List<MGMObject*> groundObjects;
	List<MGMObject*> enemyObjects;
	List<MGMObject*> itemObjects;
	List<MGMObject*> stairObjects;
	List<MGMObject*> isKilledObject;

	void addObject(MGMObject* obj);
	void removeObject(MGMObject* obj);

	void clear();

	MGMObjectsCategory();
	~MGMObjectsCategory();
};

