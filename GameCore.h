#pragma once
/* 
*/
#include "cocos2d.h"
#include "audio/include/AudioEngine.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <bitset>

#include "Specifications.h"
//#include "Figure.h"
//#include "Units.h"
//#include "FiguresPool.h"

using namespace DEF_SETT;

class GameCore {
private:
	GameCore() {};
	GameCore(const GameCore& copy) = delete;
	GameCore& operator=(const GameCore& copy) = delete;
	// attributes

	int mStageNumber = 1;


	// Board[SIZE][SIZE], BOARD_SIZE = 8;
	//std::vector < std::vector<Figure*>> _board;

	//FiguresPool* _figuresPool = nullptr;

	//AudioController* _audioController = nullptr;

	// sets for "White" and "Black" armies and pointers on them
	//cocos2d::Vector<Figure*> _whiteArmy = cocos2d::Vector<Figure*>(16);
	

	bool _gameOver;
	
	// methods
	bool init();

	//cocos2d::Vec2 convertCoord(Location location);

	

public:

	// attributes
	
	// methods
	void initialSetup();

	static GameCore* sharedCore();

	// deleting existing game data to load saved game / customize new game
	void clearData();

	// main logic block
	//bool processEvent(Location newLocation);

	

	// getters
	int getStageNumber() const;
	//const cocos2d::Vector<Figure*>* getWhiteArmy() const;
	

	//setters
	//void setLogMessage(std::string logMessage);
	
};


