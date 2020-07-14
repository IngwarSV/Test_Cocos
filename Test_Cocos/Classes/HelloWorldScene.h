#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "../cocos2d/external/json/document.h"
#include "../cocos2d/external/json/filestream.h"
#include "../cocos2d/external/json/stringbuffer.h"

#include <array>
#include <string>

#include "Specifications.h"

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

class HelloWorld : public cocos2d::Scene
{
private:
	// Sprites
	cocos2d::Vector<cocos2d::Sprite*> mStaticSprites = cocos2d::Vector<cocos2d::Sprite*>(2);
	cocos2d::Sprite* mSprite3;
	cocos2d::Sprite* mPreviousCollidedSprite;

	// Buttons
	cocos2d::ui::Button* mButton1;
	cocos2d::ui::Button* mButton2;
	cocos2d::ui::Button* mButton3;

	// Sprites vertices 
	std::array<cocos2d::Vec2, 4> mSprite1VertsArr;
	std::array<cocos2d::Vec2, 4> mSprite2VertsArr;
	std::array<cocos2d::Vec2, 4> mSprite3VertsArr;

	// Windows size
	cocos2d::Size mWinSize;
	// Sprite size
	cocos2d::Size mSpriteSize;
	// Actions duration
	float mActionDuration;
	// Labels' font size
	cocos2d::Color3B mVioletColor;

	// Coordinates of zone for additional position calculations
	float mDangerZoneMinX;
	float mDangerZoneMaxX;
	float mDangerZoneMinY;
	float mDangerZoneMaxY;

	// Buttons' click numbers
	eBtnMode mBTN1Mode;
	eBtnMode mBTN2Mode;
	eBtnMode mBTN3Mode;
	
	// ctor
	HelloWorld();

public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	void onButtonPressed(cocos2d::Ref* aSender, cocos2d::ui::Widget::TouchEventType aType);

	void on1ButtonPressed(cocos2d::Ref* aSender, cocos2d::ui::Widget::TouchEventType aType);
	void on2ButtonPressed(cocos2d::Ref* aSender, cocos2d::ui::Widget::TouchEventType aType);
	void on3ButtonPressed(cocos2d::Ref* aSender, cocos2d::ui::Widget::TouchEventType aType);
	void onQuitButtonPressed(cocos2d::Ref* aSender, cocos2d::ui::Widget::TouchEventType aType);

	bool on3SpriteTouchBegan(cocos2d::Touch* aTouch, cocos2d::Event* aEvent);
	void on3SpriteTouchMoved(cocos2d::Touch* aTouch, cocos2d::Event* aEvent);
	void on3SpriteTouchEnded(cocos2d::Touch* aTouch, cocos2d::Event* aEvent);

	bool is3SpriteInDangerZone(cocos2d::Vec2 currentSprite3Position, cocos2d::Vec2 possibleSprite3Position);
	bool processCollision(cocos2d::Sprite* aStaticSprite, cocos2d::Vec2& aPossibleSpritePosition, 
		cocos2d::Vec2 aMoveVector, int aProminentVertex);
	

	CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
