#include "CellsPool.h"

CellsPool::CellsPool()
{
	//mCellsPool.pushBack(createFigure(Type::KING, Color::WHITE));
	//mCellsPool.pushBack(createFigure(Type::QUEEN, Color::WHITE));
	//mCellsPool.pushBack(createFigure(Type::QUEEN, Color::WHITE)); // additional queen for promotion
	//mCellsPool.pushBack(createFigure(Type::BISHOP, Color::WHITE));
	//mCellsPool.pushBack(createFigure(Type::BISHOP, Color::WHITE));
	//mCellsPool.pushBack(createFigure(Type::KNIGHT, Color::WHITE));
	//mCellsPool.pushBack(createFigure(Type::KNIGHT, Color::WHITE));
	//mCellsPool.pushBack(createFigure(Type::ROOK, Color::WHITE));
	//mCellsPool.pushBack(createFigure(Type::ROOK, Color::WHITE));

	//mCellsPool.pushBack(createFigure(Type::KING, Color::BLACK));
	//mCellsPool.pushBack(createFigure(Type::QUEEN, Color::BLACK));
	//mCellsPool.pushBack(createFigure(Type::QUEEN, Color::BLACK)); // additional queen for promotion
	//mCellsPool.pushBack(createFigure(Type::BISHOP, Color::BLACK));
	


}
CellsPool::~CellsPool()
{
	mCellsPool.clear();
}

//Cell* CellsPool::createCell(std::string aImagePath, Location aLocation, eCellTypes aCellType,
//							eSphereTypes aSphereType, bool aIsVisible)
//{
//	/*Cell* cell = nullptr;
//
//	cell = 
//	switch (figureType) {
//	case Type::KING:
//		return F_King::createFigure(figureColor, location);
//		break;
//	case Type::QUEEN:
//		return F_Queen::createFigure(figureColor, location);
//		break;
//	case Type::BISHOP:
//		return F_Bishop::createFigure(figureColor, location);
//		break;
//	case Type::KNIGHT:
//		return F_Knight::createFigure(figureColor, location);;
//		break;
//	case Type::ROOK:
//		return F_Rook::createFigure(figureColor, location);;
//		break;
//	case Type::PAWN:
//		return F_Pawn::createFigure(figureColor, location);;
//		break;
//	default:
//		return nullptr;
//		break;
//	}*/
//}

Cell* CellsPool::getCell(	std::string aImagePath, Location aLocation, eCellTypes aCellType,
							eSphereTypes aSphereType, bool aIsVisible)
{
	Cell* cell = nullptr;


	auto  result = std::find_if(mCellsPool.begin(), mCellsPool.end(), [&aCellType, &aSphereType](const Cell* cell) {
		return cell->getCellType() == aCellType && cell->getSphereType() == aSphereType;
	});

	if (result != mCellsPool.end()) {
		cell = *result;

		cell->retain();
		mCellsPool.eraseObject(cell);

		/*figure->setLocation(location);
		figure->setPosition(static_cast<float>(BOARD_X + location.y * SQUARE_SIZE),
			static_cast<float>(BOARD_Y + location.x * SQUARE_SIZE));*/
	}
	else {
		cell = Cell::createCell(aImagePath, aLocation, aCellType, aSphereType, aIsVisible);
	}

	return cell;
}

void CellsPool::putCell(Cell* cell)
{
	mCellsPool.pushBack(cell);
}
