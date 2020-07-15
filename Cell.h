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
	eCellTypes mType;
	Location mLocation;

public:
	bool init();
	static Cell* createCell(std::string aImagePath, Location aLocation, eCellTypes aType, cocos2d::Vec2 aPosition, bool aIsVisible = true);

	CREATE_FUNC(Cell);

	// attributes
	

	// methods
	const eCellTypes getType() const;
	

	//getters

	/*const Color getFigureColor() const;
	const Type getType() const;
	const std::string& getFigureName() const;
	const Location getLocation() const;*/

	//setters
	/*void setLocation(Location location);
	void setActiveState();
	void setPassiveState();*/
};