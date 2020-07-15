#include "Cell.h"

using namespace cocos2d;
using namespace DEF_SETT;



Cell* Cell::createCell(std::string aImagePath, Location aLocation, eCellTypes aType, cocos2d::Vec2 aPosition, bool aIsVisible)
{
	Cell* cell = new Cell();
	if (cell && cell->initWithFile(aImagePath))
	{
		cell->mType = aType;
		cell->mLocation = aLocation;
		cell->setPosition(aPosition);

		cell->autorelease();
	}
	else
	{
		delete cell;
		cell = nullptr;
		log("Can't init Sprite with %s", aImagePath);
	}
	return cell;	
}


const eCellTypes Cell::getType() const {
	return mType;
}




//std::vector<Location>* Figure::getPossibleMoves(std::vector < std::vector<Figure*>>* board)
//{
//	return &_possibleMoves;
//}
//
//const Color Figure::getFigureColor() const
//{
//	return _color;
//}
//
//const Type Figure::getType() const
//{
//	return _type;
//}
//
//const std::string& Figure::getFigureName() const
//{
//	return _name;
//}
//
//const Location Figure::getLocation() const
//{
//	return _location;
//}
//
//void Figure::setLocation(Location location)
//{
//	_location.x = location.x;
//	_location.y = location.y;
//}
//
//void Figure::setPassiveState()
//{
//	this->setSpriteFrame(_name + "_Pas.png");
//}
//
//void Figure::setActiveState()
//{
//	this->setSpriteFrame(_name + "_Act.png");
//}