#pragma once

#include "cocos2d.h"
#include <string>



namespace DEF_SETT {
	// Main fonts
	const std::string FONT{ "fonts/arial.ttf" };

	// Actions duration
	constexpr float DURATION = 2.0f;
	
	// Labels' font size and distance between
	constexpr float FONT_SIZE = 18.0f;
	
	// Labels color
	const cocos2d::Color3B METALLIC_GOLD{ 212, 175, 55 };
	const cocos2d::Color3B VIOLET{ 131, 55, 127 };



	//// Side to move first
	const cocos2d::Vec2 WHITE_SIDE_POS{ 790.0f, 550.0f };
	const cocos2d::Vec2 BLACK_SIDE_POS{ 941.0f, 550.0f };
	
	// Log Messages
	//// Game
	const std::string NewGameString{ "New Game!" };
	const std::string CastlingPerfomed{ "Castling is done: " };
	const std::string CastlingShort{ "O-O  " };
	
}
