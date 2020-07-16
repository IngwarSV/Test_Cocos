#pragma once

#include "cocos2d.h"
#include <string>
#include <vector>

#include "Specifications.h"


class Cell : public cocos2d::Sprite
{
private:
	// attributes
	cocos2d::Sprite* mCellSprite;
	eCellTypes mCellType;
	eSphereTypes mSphereType;
	Location mLocation;

public:
	//bool init();
	static Cell* createCell(std::string aImagePath, Location aLocation, eCellTypes aCellType, 
							eSphereTypes aSphereType = eSphereTypes::NONE_SPHERE, bool aIsVisible = true);

	//CREATE_FUNC(Cell);

	// attributes


	// methods
	


	//getters
	const eCellTypes getCellType() const;
	const eSphereTypes getSphereType() const;
	/*const Color getFigureColor() const;
	const Type getType() const;
	const std::string& getFigureName() const;
	const Location getLocation() const;*/

	//setters
	/*void setLocation(Location location);
	void setActiveState();
	void setPassiveState();*/
};