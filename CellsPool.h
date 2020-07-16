#pragma once

#include "cocos2d.h"
#include <iostream>
#include <string>
#include <algorithm>

#include "Specification.h"
#include "Cell.h"


using namespace DEF_SETT;

class CellsPool {
private:
	
	CellsPool(const CellsPool& copy) = delete;
	CellsPool& operator=(const CellsPool& copy) = delete;

	// attributes
	cocos2d::Vector<Cell*> mCellsPool;
public:
	CellsPool();
	~CellsPool();
	/*Cell* createCell(	std::string aImagePath, Location aLocation, eCellTypes aCellType,
						eSphereTypes aSphereType = eSphereTypes::NONE_SPHERE, bool aIsVisible = true);*/

	Cell* getCell(	std::string aImagePath, Location aLocation, eCellTypes aCellType,
					eSphereTypes aSphereType = eSphereTypes::NONE_SPHERE, bool aIsVisible = true);

	//bool containsCell(Cell* cell);

	void putCell(Cell* cell);
};
