#include "GameCore.h"

using namespace cocos2d;
using namespace cocos2d::experimental;


bool GameCore::init() {
	//// creating Board[8][8] with nullptrs
	//for (int i = 0; i < BOARD_SIZE; ++i) {
	//	_board.push_back(std::vector<Figure*>(BOARD_SIZE));
	//}

	//// initializing figures' pool 
	////_figuresPool = FiguresPool::getBarracks();

	

	return true;
}

void GameCore::initialSetup()
{
	//// Creating armies with figures 
	////// White Army
	//_WKing = _figuresPool->getFigure(Type::KING, Color::WHITE, WK_INIT_POS);
	//_whiteArmy.pushBack(_WKing);
	//_whiteArmy.pushBack(_figuresPool->getFigure(Type::QUEEN, Color::WHITE, WQ_INIT_POS));
	//_whiteArmy.pushBack(_figuresPool->getFigure(Type::BISHOP, Color::WHITE, WB_INIT_POS1));
	//_whiteArmy.pushBack(_figuresPool->getFigure(Type::BISHOP, Color::WHITE, WB_INIT_POS2));
	//_whiteArmy.pushBack(_figuresPool->getFigure(Type::KNIGHT, Color::WHITE, WN_INIT_POS1));
	//_whiteArmy.pushBack(_figuresPool->getFigure(Type::KNIGHT, Color::WHITE, WN_INIT_POS2));
	//_whiteArmy.pushBack(_figuresPool->getFigure(Type::ROOK, Color::WHITE, WR_INIT_POS1));
	//_whiteArmy.pushBack(_figuresPool->getFigure(Type::ROOK, Color::WHITE, WR_INIT_POS2));

	////// Black Army
	//_BKing = _figuresPool->getFigure(Type::KING, Color::BLACK, BK_INIT_POS);
	//_blackArmy.pushBack(_BKing);
	//_blackArmy.pushBack(_figuresPool->getFigure(Type::QUEEN, Color::BLACK, BQ_INIT_POS));
	//_blackArmy.pushBack(_figuresPool->getFigure(Type::BISHOP, Color::BLACK, BB_INIT_POS1));
	//_blackArmy.pushBack(_figuresPool->getFigure(Type::BISHOP, Color::BLACK, BB_INIT_POS2));
	//_blackArmy.pushBack(_figuresPool->getFigure(Type::KNIGHT, Color::BLACK, BN_INIT_POS1));
	//_blackArmy.pushBack(_figuresPool->getFigure(Type::KNIGHT, Color::BLACK, BN_INIT_POS2));
	//_blackArmy.pushBack(_figuresPool->getFigure(Type::ROOK, Color::BLACK, BR_INIT_POS1));
	//_blackArmy.pushBack(_figuresPool->getFigure(Type::ROOK, Color::BLACK, BR_INIT_POS2));

	//// Pawns
	//_pawnQuantity = PAWN_QUANTITY;

	//for (int i = 0; i < BOARD_SIZE; ++i) {
	//	Location tempWhite = WP_INIT_POS1;
	//	Location tempBlack = BP_INIT_POS1;
	//	tempWhite.y += i;
	//	tempBlack.y += i;

	//	_whiteArmy.pushBack(_figuresPool->getFigure(Type::PAWN, Color::WHITE, tempWhite));
	//	_blackArmy.pushBack(_figuresPool->getFigure(Type::PAWN, Color::BLACK, tempBlack));
	//}

	//// updating board's situation considering figures' positions
	//for (auto figure : _whiteArmy) {
	//	Location location = figure->getLocation();
	//	_board[location.x][location.y] = figure;
	//}

	//for (Figure* figure : _blackArmy) {
	//	Location location = figure->getLocation();
	//	_board[location.x][location.y] = figure;
	//}

	//// assigning values to the rest of the attributes
	//_currentArmy = &_whiteArmy;
	//_enemyArmy = &_blackArmy;
	//_activeKing = _WKing;
	//_figureToMove = nullptr;
	//_enPassantFigure = nullptr;
	//_figureToPromote = nullptr;
	//_tempLocation = Location{ BOARD_SIZE, BOARD_SIZE };
	//_halfTurn = 1;
	//_CHECK = false;
	//_gameOver = false;
	//_turnDuration = time(NULL);
	//_p1GameDuration = 0.0;
	//_p2GameDuration = 0.0;
	//_logMessage = NewGameString;
}

GameCore* GameCore::sharedCore()
{
	static bool s_firstRun = true;
	static GameCore s_sharedCore;

	if (s_firstRun) {
		s_sharedCore.init();
		s_firstRun = false;
	}

	return &s_sharedCore;
}






int GameCore::getStageNumber() const
{
	return mStageNumber;
}