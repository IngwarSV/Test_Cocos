#pragma once

#include "cocos2d.h"
#include <string>


// for buttonsCreation by parsing
struct ButtonAttributes {
	std::string normFilePath;
	std::string selectFilePath;
	float contentScale;
	std::string titleFont;
	float titleFontSize;
	cocos2d::Color3B titleColor;
	std::string titleText;
};

enum class eBtnMode {
	INIT_MODE = 0,
	FIRST_MODE,
	SECOND_MODE,
};

enum class eSpriteVertices {
	BOTT_LEFT = 0,
	UP_LEFT,
	UP_RIGHT,
	BOTT_RIGHT,
};

enum class eCellTypes {
	DESK_CELL = 0,
	BLOCK_CELL,
	MAIN_CELL,
	SPHERE_CELL,
};

struct Location {
	int x = 0, y = 0;

	bool operator==(const Location& other) const {
		return this->x == other.x && this->y == other.y;
	}

	bool operator!=(const Location& other) const {
		return this->x != other.x || this->y != other.y;
	}
};







namespace DEF_SETT {
	// Ratio
	const float cHalf = 0.5f;
	const float cOneThird = 1.0f / 3.0f;
	const float cTwoThird = 2.0f / 3.0f;
	const float cOneQuaters = 1.0f / 4.0f;
	const float cThreeQuaters = 3.0f / 4.0f;
	const float cOneSixth = 1.0f / 6.0f;
	const float cFullOpacity = 255.0f;
	const float cFullSize = 1.0f;
	const float cOnePixel = 1.0f;

	const float maxSpeedX = 5.0f;
	const float maxSpeedY = 5.0f;

	const int cVerticesAmount = 4;
}