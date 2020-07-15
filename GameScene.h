#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "../cocos2d/external/json/document.h"
//#include "../cocos2d/external/json/filestream.h"
//#include "../cocos2d/external/json/stringbuffer.h"

#include <array>
#include <vector>
#include <string>

#include "Specifications.h"
#include "GameCore.h"



class GameScene : public cocos2d::Scene
{
private:
	GameCore* mGameCore = GameCore::sharedCore();
	float mCellSize;
	cocos2d::Rect mBoardRect;
	std::vector<std::vector<cocos2d::Sprite*>> mBoard;

	// GameLabels
	cocos2d::Label* mCurrStageLabel;

	// Sprites
	cocos2d::Vector<cocos2d::Sprite*> mStatSprites = cocos2d::Vector<cocos2d::Sprite*>(2);
	std::array<cocos2d::Rect, 2> mStatSprBoxes;
	cocos2d::Sprite* mSprite3;
	cocos2d::Sprite* mPreviousCollidedSprite;

	// Buttons
	cocos2d::ui::Button* mNextStageBtn;
	cocos2d::ui::Button* mPrevStageBtn;
	cocos2d::ui::Button* mButton3;

	bool mMoveIsCompleted = true;
	cocos2d::Vec2 mNewDynamSprPos;


	// Sprites vertices 
	std::array<std::array<cocos2d::Vec2, 4>, 2> mStatSprVertices;
	/*std::array<cocos2d::Vec2, 4> mSprite2VertsArr;
	std::array<cocos2d::Vec2, 4> mSprite3VertsArr;*/

	// Windows size
	cocos2d::Size mWinSize;
	// Sprite size
	cocos2d::Size mSpriteSize;
	// Actions duration
	float mActionDuration;
	// Labels' font size
	cocos2d::Color3B mVioletColor;

	// Buttons' click numbers
	eBtnMode mBTN1Mode;
	eBtnMode mBTN2Mode;
	eBtnMode mBTN3Mode;

	// ctor
	GameScene();

public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	void update(float deltaTime);

	void onButtonPressed(cocos2d::Ref* aSender, cocos2d::ui::Widget::TouchEventType aType);

	void on1ButtonPressed(cocos2d::Ref* aSender, cocos2d::ui::Widget::TouchEventType aType);
	void on2ButtonPressed(cocos2d::Ref* aSender, cocos2d::ui::Widget::TouchEventType aType);
	void on3ButtonPressed(cocos2d::Ref* aSender, cocos2d::ui::Widget::TouchEventType aType);
	void onQuitButtonPressed(cocos2d::Ref* aSender, cocos2d::ui::Widget::TouchEventType aType);

	bool on3SpriteTouchBegan(cocos2d::Touch* aTouch, cocos2d::Event* aEvent);
	void on3SpriteTouchMoved(cocos2d::Touch* aTouch, cocos2d::Event* aEvent);
	void on3SpriteTouchEnded(cocos2d::Touch* aTouch, cocos2d::Event* aEvent);

	void moveSprite(cocos2d::Vec2 newDynamSprPos);

	bool processCollision(cocos2d::Sprite* aStaticSprite, cocos2d::Vec2& aPossibleSpritePosition,
		cocos2d::Vec2 aMoveVector, int aProminentVertex);


	CREATE_FUNC(GameScene);
};

#endif // __HELLOWORLD_SCENE_H__