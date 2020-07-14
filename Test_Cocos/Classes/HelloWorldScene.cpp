#include "HelloWorldScene.h"

using namespace cocos2d;
using namespace ui;
using namespace DEF_SETT;
using namespace rapidjson;

HelloWorld::HelloWorld() 
	: mSprite3(nullptr)
	, mPreviousCollidedSprite(nullptr),
	mButton1(nullptr),
	mButton2(nullptr),
	mButton3(nullptr),
	mWinSize(Director::getInstance()->getWinSize()),
	mBTN1Mode(eBtnMode::INIT_MODE),
	mBTN2Mode(eBtnMode::INIT_MODE),
	mBTN3Mode(eBtnMode::INIT_MODE),
	
	mDangerZoneMinX(0),
	mDangerZoneMinY(0),

	mDangerZoneMaxX(0),
	mDangerZoneMaxY(Director::getInstance()->getWinSize().height)
{

	mDangerZoneMaxX = Director::getInstance()->getWinSize().height;
}

Scene* HelloWorld::createScene()
{
	return HelloWorld::create();
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	bool result = false;
	
	if (Scene::init())
	{
		// Creating JSON Document for Game Settings
		std::string path = "specifications.json";
		std::string outputDataString = FileUtils::getInstance()->getStringFromFile(path.c_str());
		rapidjson::Document specifications;
		specifications.Parse<0>(outputDataString.c_str());
		
		// Actions duration
		mActionDuration = specifications["ActionDuration"].GetDouble();
		
		// Creating background
		Rect backgroundSpriteSize{ 0, 0, mWinSize.width * cTwoThird, mWinSize.height };
		auto background = Sprite::create(specifications["BackGroundImageFile"].GetString(), backgroundSpriteSize);
		background->setPosition(mWinSize.width * cOneThird, 0);
		background->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
		addChild(background);

		// Creating Sprites
		
		//// Sprite 1
		mStaticSprites.pushBack(Sprite::create(specifications["Sprite1ImageFile"].GetString()));
		////// Initializing mSpriteSize (all Sprites are equal)
		mSpriteSize = mStaticSprites.back()->getContentSize();
		Vec2 sprite1Position{ mWinSize.width * cTwoThird + mSpriteSize.width * cHalf, 
			mWinSize.height * cThreeQuaters + mSpriteSize.height * cHalf };
		mStaticSprites.back()->setPosition(sprite1Position);
		mStaticSprites.back()->setAnchorPoint(Vec2::ANCHOR_TOP_RIGHT);

		////// Creating bounding box
		auto drawNode1 = DrawNode::create();
		drawNode1->drawRect(Vec2(0, 0), Vec2(mSpriteSize.width, mSpriteSize.height), Color4F::BLUE);
		mStaticSprites.back()->addChild(drawNode1);
		addChild(mStaticSprites.back());

		////// Initializing mSprite1VertsArr
		Rect sprite1Box = mStaticSprites.back()->getBoundingBox();
		mSprite1VertsArr[static_cast<int>(eSpriteVertices::BOTT_LEFT)] = sprite1Box.origin;
		mSprite1VertsArr[static_cast<int>(eSpriteVertices::UP_LEFT)] = Vec2(sprite1Box.origin.x, sprite1Box.getMaxY());
		mSprite1VertsArr[static_cast<int>(eSpriteVertices::UP_RIGHT)] = Vec2(sprite1Box.getMaxX(), sprite1Box.getMaxY());
		mSprite1VertsArr[static_cast<int>(eSpriteVertices::BOTT_RIGHT)] = Vec2(sprite1Box.getMaxX(), sprite1Box.origin.y);
		mStaticSprites.back()->setUserData(&mSprite1VertsArr);


		//// Sprite 2
		mStaticSprites.pushBack(Sprite::create(specifications["Sprite2ImageFile"].GetString()));
		Vec2 sprite2Position{ mWinSize.width * cTwoThird, mWinSize.height * cHalf };
		mStaticSprites.back()->setPosition(sprite2Position);
		mStaticSprites.back()->setAnchorPoint(Vec2::ANCHOR_MIDDLE);

		////// Creating bounding box
		auto drawNode2 = DrawNode::create();
		drawNode2->drawRect(Vec2(0, 0), Vec2(mSpriteSize.width, mSpriteSize.height), Color4F::YELLOW);
		mStaticSprites.back()->addChild(drawNode2);
		addChild(mStaticSprites.back());

		////// Initializing mSprite1VertsArr
		Rect sprite2Box = mStaticSprites.back()->getBoundingBox();
		mSprite2VertsArr[static_cast<int>(eSpriteVertices::BOTT_LEFT)] = sprite2Box.origin;
		mSprite2VertsArr[static_cast<int>(eSpriteVertices::UP_LEFT)] = Vec2(sprite2Box.origin.x, sprite2Box.getMaxY());
		mSprite2VertsArr[static_cast<int>(eSpriteVertices::UP_RIGHT)] = Vec2(sprite2Box.getMaxX(), sprite2Box.getMaxY());
		mSprite2VertsArr[static_cast<int>(eSpriteVertices::BOTT_RIGHT)] = Vec2(sprite2Box.getMaxX(), sprite2Box.origin.y);
		mStaticSprites.back()->setUserData(&mSprite2VertsArr);

		//// Sprite 3
		mSprite3 = Sprite::create(specifications["Sprite3ImageFile"].GetString());
		Vec2 sprite3Position{ mWinSize.width * cTwoThird, mWinSize.height * cOneQuaters };
		mSprite3->setPosition(sprite3Position);
		mSprite3->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
		mSprite3->setColor(Color3B::RED);
		mSprite3->setTag(0);
		////// Creating bounding box
		auto drawNode3 = DrawNode::create();
		drawNode3->drawRect(Vec2(0, 0), Vec2(mSpriteSize.width, mSpriteSize.height), Color4F::GREEN);
		mSprite3->addChild(drawNode3);
		addChild(mSprite3);
		////// Creating touchListener for mSprite3 movement
		auto sprite3touchListener = EventListenerTouchOneByOne::create();
		sprite3touchListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::on3SpriteTouchBegan, this);
		sprite3touchListener->onTouchMoved = CC_CALLBACK_2(HelloWorld::on3SpriteTouchMoved, this);
		sprite3touchListener->onTouchEnded = CC_CALLBACK_2(HelloWorld::on3SpriteTouchEnded, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(sprite3touchListener, this);
		mVioletColor = Color3B(	specifications["VIOLET"][0u].GetInt(),
								specifications["VIOLET"][1u].GetInt(),
								specifications["VIOLET"][2u].GetInt());

		// Creating buttons
		//// QuitButton
		auto quitButton = Button::create(	specifications["QuitBTNNormalImageFile"].GetString(), 
											specifications["QuitBTNSelectedImageFile"].GetString());
		quitButton->setScale(cHalf);
		Vec2 quitButtonPosition{ mWinSize.width - quitButton->getContentSize().width * cHalf,
			mWinSize.height - quitButton->getContentSize().height * cHalf };
		quitButton->setPosition(quitButtonPosition);
		addChild(quitButton);
		quitButton->addTouchEventListener(CC_CALLBACK_2(HelloWorld::onButtonPressed, this));

		//// Button1
		auto buttonColor = Color3B(	specifications["METALLIC_GOLD"][0u].GetInt(), 
									specifications["METALLIC_GOLD"][1u].GetInt(), 
									specifications["METALLIC_GOLD"][2u].GetInt());
		mButton1 = Button::create(	specifications["BTNNormalImageFile"].GetString(), 
									specifications["BTNSelectedImageFile"].GetString());
		mButton1->setTitleText("MOVE");
		
		mButton1->setTitleColor(buttonColor);
		mButton1->setTitleFontName(specifications["Font"].GetString());
		mButton1->setTitleFontSize(specifications["FontSize"].GetDouble());
		Vec2 button1Position{ mWinSize.width * cOneSixth, mWinSize.height * cThreeQuaters };
		mButton1->setPosition(button1Position);
		addChild(mButton1);
		mButton1->addTouchEventListener(CC_CALLBACK_2(HelloWorld::onButtonPressed, this));

		//// Button2
		mButton2 = Button::create(	specifications["BTNNormalImageFile"].GetString(),
									specifications["BTNSelectedImageFile"].GetString());
		mButton2->setTitleText("TINT && FADE");
		mButton2->setTitleColor(buttonColor);
		mButton2->setTitleFontName(specifications["Font"].GetString());
		mButton2->setTitleFontSize(specifications["FontSize"].GetDouble());
		Vec2 button2Position{ mWinSize.width * cOneSixth, mWinSize.height * cHalf };
		mButton2->setPosition(button2Position);
		addChild(mButton2);
		mButton2->addTouchEventListener(CC_CALLBACK_2(HelloWorld::onButtonPressed, this));

		//// Button3
		mButton3 = Button::create(	specifications["BTNNormalImageFile"].GetString(),
									specifications["BTNSelectedImageFile"].GetString());
		mButton3->setTitleText("SIMPLE MOVEMENT");
		mButton3->setTitleColor(buttonColor);
		mButton3->setTitleFontName(specifications["Font"].GetString());
		mButton3->setTitleFontSize(specifications["FontSize"].GetDouble());
		Vec2 button3Position{ mWinSize.width * cOneSixth, mWinSize.height * cOneQuaters };
		mButton3->setPosition(button3Position);
		addChild(mButton3);
		mButton3->addTouchEventListener(CC_CALLBACK_2(HelloWorld::onButtonPressed, this));

		// Specifying coordinates of dangerZone
		mDangerZoneMinX = mSprite1VertsArr[static_cast<int>(eSpriteVertices::BOTT_LEFT)].x;
		mDangerZoneMaxX = mSprite1VertsArr[static_cast<int>(eSpriteVertices::BOTT_RIGHT)].x;
		mDangerZoneMinY = mSprite2VertsArr[static_cast<int>(eSpriteVertices::BOTT_LEFT)].y;
		mDangerZoneMaxY = mSprite1VertsArr[static_cast<int>(eSpriteVertices::UP_LEFT)].y;

		// Specifying coordinates of dangerZone considering Sprite3 dimensions
		mDangerZoneMinX -= mSpriteSize.width;
		mDangerZoneMaxX += mSpriteSize.width;
		mDangerZoneMinY -= mSpriteSize.height;
		mDangerZoneMaxY += mSpriteSize.height;
		
		result = true;
	}

	return result;
}

bool HelloWorld::on3SpriteTouchBegan(cocos2d::Touch* aTouch, cocos2d::Event* aEvent)
{
	bool sprite3IsTouched = mSprite3->getBoundingBox().containsPoint(aTouch->getLocation());
	
	if (sprite3IsTouched) 
	{
		if (	mSprite3->getColor() == Color3B::YELLOW
			||	mSprite3->getColor() == mVioletColor)
		{
			mSprite3->setColor(Color3B::GREEN);
		}
	}
	
	return sprite3IsTouched;
}

void HelloWorld::on3SpriteTouchMoved(cocos2d::Touch* aTouch, cocos2d::Event* aEvent)
{
	Vec2 currentSprite3Position = mSprite3->getPosition();
	Vec2 possibleSprite3Position = aTouch->getLocation();
	Rect sprite3Box = mSprite3->getBoundingBox();
	// Calculating moveVector - difference between touch position and center of mSprite3
	Vec2 moveVector{ possibleSprite3Position.x - sprite3Box.getMidX(), possibleSprite3Position.y - sprite3Box.getMidY() };

	// if mSprite3 is in Collision movement mode 
	bool sprite3InCollisionMode = static_cast<bool>(mSprite3->getTag());
	if (sprite3InCollisionMode) 
	{
		if (is3SpriteInDangerZone(currentSprite3Position, possibleSprite3Position))
		{
			// Calculating all sprite3Verts
			mSprite3VertsArr[static_cast<int>(eSpriteVertices::BOTT_LEFT)] = sprite3Box.origin;
			mSprite3VertsArr[static_cast<int>(eSpriteVertices::UP_LEFT)] = Vec2(sprite3Box.origin.x, sprite3Box.getMaxY());
			mSprite3VertsArr[static_cast<int>(eSpriteVertices::UP_RIGHT)] = Vec2(sprite3Box.getMaxX(), sprite3Box.getMaxY());
			mSprite3VertsArr[static_cast<int>(eSpriteVertices::BOTT_RIGHT)] = Vec2(sprite3Box.getMaxX(), sprite3Box.origin.y);

			// Calculating most prominent vertex of the mSprite3 in touch direction
			eSpriteVertices prominentVertex = eSpriteVertices::BOTT_LEFT;
			if (moveVector.x <= 0 && moveVector.y >= 0)
			{
				prominentVertex = eSpriteVertices::UP_LEFT;
			}
			else if (moveVector.x >= 0 && moveVector.y >= 0)
			{
				prominentVertex = eSpriteVertices::UP_RIGHT;
			}
			else if (moveVector.x >= 0 && moveVector.y <= 0)
			{
				prominentVertex = eSpriteVertices::BOTT_RIGHT;
			}
			
			bool spritesAreColliding = false;
			// Checking collision with the nearest sprite
			if (mPreviousCollidedSprite)
			{
				spritesAreColliding = processCollision(mPreviousCollidedSprite, possibleSprite3Position, moveVector, static_cast<int>(prominentVertex));
			}
			// Checking collision with the other sprites
			if (!spritesAreColliding)
			{
				for (auto staticSprite : mStaticSprites) 
				{
					if (staticSprite == mPreviousCollidedSprite) 
					{
						continue;
					}
					if (processCollision(staticSprite, possibleSprite3Position, moveVector, static_cast<int>(prominentVertex))) 
					{
						break;
					}
				}
			}

			auto size = mPreviousCollidedSprite->getContentSize();
			auto pos = mPreviousCollidedSprite->getPosition();


		}
	}

	// checking playField boundaries (including distance to sprite3 center)
	float leftEdge = (mWinSize.width * cOneThird) + mSpriteSize.width * cHalf;
	float rightEdge = mWinSize.width - mSpriteSize.width * cHalf - cOnePixel;
	float upperEdge = mWinSize.height - mSpriteSize.height * cHalf - cOnePixel;
	float bottomEdge = mSpriteSize.height * cHalf + cOnePixel;
	
	//// checking left boundary
	if (possibleSprite3Position.x < leftEdge)
	{
		possibleSprite3Position.x = leftEdge;
	}
	//// checking right boundary
	else if (possibleSprite3Position.x > rightEdge)
	{
		possibleSprite3Position.x = rightEdge;
	}

	//// checking bottom boundary
	if (possibleSprite3Position.y < bottomEdge)
	{
		possibleSprite3Position.y = bottomEdge;
	}
	//// checking upper boundary
	else if (possibleSprite3Position.y > upperEdge)
	{
		possibleSprite3Position.y = upperEdge;
	}

	mSprite3->setPosition(possibleSprite3Position);
}

bool HelloWorld::is3SpriteInDangerZone(Vec2 currentSprite3Position, Vec2 possibleSprite3Position) {
	bool inDangerZone = true;
	
	if (	( currentSprite3Position.x < mDangerZoneMinX ) 
		&&  ( possibleSprite3Position.x < mDangerZoneMinX) )
	{
		inDangerZone = false;
	}
	else if (currentSprite3Position.x > mDangerZoneMaxX && possibleSprite3Position.x > mDangerZoneMaxX)
	{
		inDangerZone = false;
	}
	else if (currentSprite3Position.y < mDangerZoneMinY && possibleSprite3Position.y < mDangerZoneMinY)
	{
		inDangerZone = false;
	}
	else if (currentSprite3Position.y > mDangerZoneMaxY && possibleSprite3Position.y > mDangerZoneMaxY)
	{
		inDangerZone = false;
	}

	return inDangerZone;
}

bool HelloWorld::processCollision(Sprite* aStaticSprite, Vec2& aPossibleSpritePosition, Vec2 aMoveVector, int aProminentVertex) 
{
	bool spritesAreColliding = false;
	/* Main idea - we have to check for intersection between:
		- one of 3 segments formed by Sprite3 Vertices + MoveVector
		- and two segments of static sprite.
		For example:
		if initial prominent vertex of Sprite3 is BOTT_LEFT(0), than opposite static vertex is UP_RIGHT(2), and we have to check for collision
		between BOTT_LEFT(0) - (BOTT_LEFT(0) + MoveVector) with static sprite segments  UP_RIGHT(2) - UP_LEFT(1) and UP_RIGHT(2) - BOTT_RIGHT(3)
		if NOT - check also for UP_LEFT(1) and BOTT_RIGHT(3) vertices of Sprite3
	*/
	// if initial prominent vertex of Sprite3 is BOTT_LEFT(0), than opposite static vertex is UP_RIGHT(2)
	int staticProminentVertex = (aProminentVertex + 2) % cVerticesAmount;
	Rect staticBox = aStaticSprite->getBoundingBox();
	auto staticSpriteVertsArr = static_cast<std::array<cocos2d::Vec2, 4>*>(aStaticSprite->getUserData());
	
	for (int counter1 = 0; counter1 < 3 && !spritesAreColliding; ++counter1)
	{
		for (int counter2 = 0, nextStaticVertex = (staticProminentVertex + 1) % 4; counter2 < 2; ++counter2) 
		{
			// Checking for intersection between 
			spritesAreColliding = Vec2::isSegmentIntersect(mSprite3VertsArr[aProminentVertex], mSprite3VertsArr[aProminentVertex] + aMoveVector,
				(*staticSpriteVertsArr)[staticProminentVertex], (*staticSpriteVertsArr)[nextStaticVertex]);
			if (spritesAreColliding)
			{
				// checking if Sprite3 is hitting vertical side of static sprite
				if ((*staticSpriteVertsArr)[staticProminentVertex].x == (*staticSpriteVertsArr)[nextStaticVertex].x)
				{
					// checking for left or right vertical side of static sprite
					eSpriteVertices sideVertex = static_cast<eSpriteVertices>(aProminentVertex);
					aPossibleSpritePosition.x = (sideVertex == eSpriteVertices::BOTT_LEFT || sideVertex == eSpriteVertices::UP_LEFT) ?
						staticBox.getMaxX() + mSpriteSize.width * cHalf + cOnePixel :
						staticBox.getMinX() - mSpriteSize.width * cHalf - cOnePixel;
				}
				// Sprite3 is hitting horizontal side of static sprite
				else 
				{
					// checking for upper or bottom horizontal side of static sprite
					eSpriteVertices sideVertex = static_cast<eSpriteVertices>(aProminentVertex);
					aPossibleSpritePosition.y = (sideVertex == eSpriteVertices::BOTT_LEFT || sideVertex == eSpriteVertices::BOTT_RIGHT) ?
						staticBox.getMaxY() + mSpriteSize.height * cHalf + cOnePixel :
						staticBox.getMinY() - mSpriteSize.height * cHalf - cOnePixel;
				}
				mPreviousCollidedSprite = aStaticSprite;
				break;
			}
			nextStaticVertex = (staticProminentVertex + 3) % 4;
		}
		/*if initial prominent vertex of Sprite3 is BOTT_LEFT(0), and we don't have collision for it,
		than we might have to check UP_LEFT(1) or BOTT_RIGHT(3) vertices of Sprite3
		for collision with two segments of static sprite*/
		aProminentVertex = (counter1 == 1) ? (aProminentVertex + 2) % 4 : (aProminentVertex + 1) % 4;
	}
	if (!spritesAreColliding) {
		mPreviousCollidedSprite = nullptr;
	}

	return spritesAreColliding;
}

void HelloWorld::on3SpriteTouchEnded(cocos2d::Touch* aTouch, cocos2d::Event* aEvent)
{
	bool sprite3InCollisionMode = static_cast<bool>(mSprite3->getTag());
	
	(sprite3InCollisionMode) ? mSprite3->setColor(mVioletColor) : mSprite3->setColor(Color3B::YELLOW);
}

void HelloWorld::onButtonPressed(cocos2d::Ref* aSender, cocos2d::ui::Widget::TouchEventType aType) {
	auto button = static_cast<Button*>(aSender);
	
	if (button == mButton1)
	{
		on1ButtonPressed(aSender, aType);
	}
	else if (button == mButton2)
	{
		on2ButtonPressed(aSender, aType);
	}
	else if (button == mButton3)
	{
		on3ButtonPressed(aSender, aType);
	}
	else {
		onQuitButtonPressed(aSender, aType);
	}
}


void HelloWorld::on1ButtonPressed(cocos2d::Ref* aSender, cocos2d::ui::Widget::TouchEventType aType) {
	Sequence* moveSequence = nullptr;
	Vec2 rightEdge{ mWinSize.width - 1, mWinSize.height * cThreeQuaters + (mSpriteSize.height * cHalf) };
	Vec2 leftEdge{ (mWinSize.width * cOneThird) + mSpriteSize.width, mWinSize.height * cThreeQuaters + (mSpriteSize.height * cHalf) };
	Vec2 sprite1InitPosition{ (mWinSize.width * cTwoThird) + (mSpriteSize.width * cHalf), 
		mWinSize.height * cThreeQuaters + (mSpriteSize.height * cHalf) };

	Sequence* scaleSequence = nullptr;

	switch (aType)
	{
	case ui::Widget::TouchEventType::BEGAN:
		mBTN1Mode = static_cast<eBtnMode>((static_cast<int>(mBTN1Mode)+1) % 3);
		switch (mBTN1Mode)
		{
		case eBtnMode::FIRST_MODE:
			static_cast<cocos2d::ui::Button*>(aSender)->setTitleText("SCALE SPRITE");
			moveSequence = Sequence::create(
				MoveTo::create(mActionDuration, rightEdge),
				MoveTo::create(mActionDuration, leftEdge),
				nullptr
			);
			mStaticSprites.at(0)->runAction(RepeatForever::create(moveSequence));
			break;

		case eBtnMode::SECOND_MODE:
			static_cast<cocos2d::ui::Button*>(aSender)->setTitleText("INITIAL STATE");
			mStaticSprites.at(0)->stopAllActions();
			scaleSequence = Sequence::create(
				ScaleTo::create(mActionDuration, cHalf),
				ScaleTo::create(mActionDuration, cFullSize),
				nullptr
			);
			mStaticSprites.at(0)->runAction(RepeatForever::create(scaleSequence));
			break;

		case eBtnMode::INIT_MODE:
			static_cast<cocos2d::ui::Button*>(aSender)->setTitleText("MOVE SPRITE");
			mStaticSprites.at(0)->stopAllActions();
			mStaticSprites.at(0)->setPosition(sprite1InitPosition);
			mStaticSprites.at(0)->setScale(cFullSize);
			break;
		default:
			break;
		}
		break;

	case ui::Widget::TouchEventType::ENDED:
		break;
	default:
		break;
	}
}
void HelloWorld::on2ButtonPressed(cocos2d::Ref* aSender, cocos2d::ui::Widget::TouchEventType aType) {
	Spawn* tintFadeSpawn = nullptr;

	switch (aType)
	{
	case ui::Widget::TouchEventType::BEGAN:
		mBTN2Mode = static_cast<eBtnMode>((static_cast<int>(mBTN2Mode)+1) % 2);
		switch (mBTN2Mode)
		{
		case eBtnMode::FIRST_MODE:
			static_cast<cocos2d::ui::Button*>(aSender)->setTitleText("INITIAL STATE");
			mStaticSprites.at(1)->setColor(Color3B::RED);
			tintFadeSpawn = Spawn::create(
				Sequence::create(TintTo::create(mActionDuration, Color3B::GREEN),
				TintTo::create(mActionDuration, Color3B::RED), nullptr),
				Sequence::create(FadeTo::create(mActionDuration, cFullOpacity * cHalf),
				FadeTo::create(mActionDuration, cFullOpacity), nullptr),
				nullptr
				);
			mStaticSprites.at(1)->runAction(RepeatForever::create(tintFadeSpawn));
			break;
		case eBtnMode::INIT_MODE:
			static_cast<cocos2d::ui::Button*>(aSender)->setTitleText("TINT && FADE");
			mStaticSprites.at(1)->stopAllActions();
			mStaticSprites.at(1)->setColor(Color3B::WHITE);
			mStaticSprites.at(1)->setOpacity(cFullOpacity);
			break;
		default:
			break;
		}
	case ui::Widget::TouchEventType::ENDED:
		break;
	default:
		break;
	}
}
void HelloWorld::on3ButtonPressed(cocos2d::Ref* aSender, cocos2d::ui::Widget::TouchEventType aType) {
		
	switch (aType)
	{
	case ui::Widget::TouchEventType::BEGAN:
		mBTN3Mode = static_cast<eBtnMode>((static_cast<int>(mBTN3Mode)+1) % 3);
		switch (mBTN3Mode)
		{
		case eBtnMode::FIRST_MODE:
			static_cast<cocos2d::ui::Button*>(aSender)->setTitleText("COLLISION MOVEMENT");
			mSprite3->setColor(Color3B::YELLOW);
			break;

		case eBtnMode::SECOND_MODE:
			static_cast<cocos2d::ui::Button*>(aSender)->setTitleText("INITIAL STATE");
			mSprite3->setColor(mVioletColor);
			mSprite3->setTag(1);
			break;

		case eBtnMode::INIT_MODE:
			static_cast<cocos2d::ui::Button*>(aSender)->setTitleText("SIMPLE MOVEMENT");
			mSprite3->setPosition(mWinSize.width * cTwoThird, mWinSize.height * cOneQuaters);
			mSprite3->setColor(Color3B::RED);
			mSprite3->setTag(0);
			break;

		default:
			break;
		}
		break;

	case ui::Widget::TouchEventType::ENDED:
		break;
	default:
		break;
	}
}

void HelloWorld::onQuitButtonPressed(Ref* sender, ui::Widget::TouchEventType type)
{
	switch (type)
	{
	case ui::Widget::TouchEventType::BEGAN:
		break;

	case ui::Widget::TouchEventType::ENDED:
		Director::getInstance()->end();
		break;

	default:
		break;
	}
}
