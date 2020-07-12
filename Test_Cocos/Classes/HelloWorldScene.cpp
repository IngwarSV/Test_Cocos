/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "HelloWorldScene.h"
#include "Specification.h"



using namespace cocos2d;
using namespace ui;
using namespace DEF_SETT;


Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // Getting windows size
	auto winSize = Director::getInstance()->getWinSize();
   // Vec2 center{ winSize.width / 2, winSize.height / 2};

    /////////////////////////////
    // Creating background
    auto background = Sprite::create("BG.png", Rect(origin, Size(winSize.width * 0.67f, winSize.height)));
    background->setPosition(winSize.width / 3, 0);
    background->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
    this->addChild(background);



    // Creating sprites
    _sprite1 = Sprite::create("Sprite1.png");
    _sprite1->setPosition(winSize.width * 0.67f + _sprite1->getContentSize().width / 2, 
        winSize.height * 3 / 4 + _sprite1->getContentSize().height / 2);
    _sprite1->setAnchorPoint(Point::ANCHOR_TOP_RIGHT);
    auto drawNode1 = DrawNode::create(1);
    drawNode1->drawRect(Vec2(0, 0), Vec2(_sprite1->getContentSize().width, _sprite1->getContentSize().height), Color4F::BLUE);
    _sprite1->addChild(drawNode1);
    this->addChild(_sprite1, 1);

    _sprite2 = Sprite::create("Sprite2.png");
    _sprite2->setPosition(winSize.width * 0.67f, winSize.height / 2);
    _sprite2->setAnchorPoint(Point::ANCHOR_MIDDLE);
    auto drawNode2 = DrawNode::create(1);
    drawNode2->drawRect(Vec2(0, 0), Vec2(_sprite2->getContentSize().width, _sprite2->getContentSize().height), Color4F::YELLOW);
    _sprite2->addChild(drawNode2);
    this->addChild(_sprite2, 1);

    _sprite3 = Sprite::create("Sprite3.png");
    _sprite3->setPosition(winSize.width * 0.67f, winSize.height / 4);
    _sprite3->setAnchorPoint(Point::ANCHOR_MIDDLE);
    _sprite3->setColor(Color3B::RED);
    _sprite3->setTag(0);
    auto drawNode3 = DrawNode::create(1);
    drawNode3->drawRect(Vec2(0, 0), Vec2(_sprite3->getContentSize().width, _sprite3->getContentSize().height), Color4F::GREEN);
    _sprite3->addChild(drawNode3);
    this->addChild(_sprite3, 1);

    // Adding touchListener to _sprite3
    auto sprite3touchListener = EventListenerTouchOneByOne::create();

    sprite3touchListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
    sprite3touchListener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
    sprite3touchListener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);


    _eventDispatcher->addEventListenerWithSceneGraphPriority(sprite3touchListener, this);

    _v_sprites.pushBack(_sprite1);
    _v_sprites.pushBack(_sprite2);


    // Creating buttons
    // Button1
    _button1 = Button::create("Plank1.png", "Plank2.png");

    _button1->setTitleText("MOVE");
    _button1->setTitleColor(METALLIC_GOLD);
    _button1->setTitleFontName(FONT);
    _button1->setTitleFontSize(FONT_SIZE);
    _button1->setPosition(Vec2(winSize.width / 6, winSize.height * 3 / 4));

    _button1->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
        static auto s_winSize = Director::getInstance()->getWinSize();
        static auto s_spriteSize = _sprite1->getContentSize();
        static int s_clickNumber = 0;
        Sequence* moveSequence = nullptr;
        Sequence* scaleSequence = nullptr;


        switch (type)
        {
        case ui::Widget::TouchEventType::BEGAN:
            s_clickNumber += 1;
            switch (s_clickNumber % 3) {
                case 1:
                    _button1->setTitleText("SCALE SPRITE");
                    moveSequence = Sequence::create(
                        MoveTo::create(DURATION, Vec2(s_winSize.width - 1, s_winSize.height * 3 / 4 + s_spriteSize.height / 2)),
                        MoveTo::create(DURATION, Vec2(s_winSize.width / 3 + s_spriteSize.width, s_winSize.height * 3 / 4 + s_spriteSize.height / 2)),
                        nullptr
                    );
                    _sprite1->runAction(RepeatForever::create(moveSequence));

                    break;
                case 2:
                    _button1->setTitleText("INITIAL STATE");
                    _sprite1->stopAllActions();
                    scaleSequence = Sequence::create(
                        ScaleTo::create(DURATION, 0.5f),
                        ScaleTo::create(DURATION, 1.0f), 
                        nullptr
                    );
                    _sprite1->runAction(RepeatForever::create(scaleSequence));


                    break;
                case 0:
                    _button1->setTitleText("MOVE SPRITE");
                    _sprite1->stopAllActions();
                    _sprite1->setPosition(s_winSize.width * 0.67f + s_spriteSize.width / 2,
                        s_winSize.height * 3 / 4 + s_spriteSize.height / 2);
                    _sprite1->setScale(1.0f);
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
    });

    this->addChild(_button1);

    // Button2
    _button2 = Button::create("Plank1.png", "Plank2.png");

    _button2->setTitleText("TINT && FADE");
    _button2->setTitleColor(METALLIC_GOLD);
    _button2->setTitleFontName(FONT);
    _button2->setTitleFontSize(FONT_SIZE);
    _button2->setPosition(Vec2(winSize.width / 6, winSize.height / 2));
    
    _button2->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
        static int s_clickNumber = 0;
        Spawn* tintFadeSpawn = nullptr;
        switch (type)
        {
        case ui::Widget::TouchEventType::BEGAN:
            s_clickNumber += 1;
            if (s_clickNumber % 2) {
                _button2->setTitleText("INITIAL STATE");
                _sprite2->setColor(Color3B::RED);
                tintFadeSpawn = Spawn::create(
                    Sequence::create(TintTo::create(DURATION, Color3B::GREEN),
                        TintTo::create(DURATION, Color3B::RED), nullptr),
                    Sequence::create(FadeTo::create(DURATION, 123.0f),
                        FadeTo::create(DURATION, 255.0f), nullptr),
                    nullptr
                );
                _sprite2->runAction(RepeatForever::create(tintFadeSpawn));
            }
            else {
                _button2->setTitleText("TINT && FADE");
                _sprite2->stopAllActions();
                _sprite2->setColor(Color3B(255, 255, 255));
                _sprite2->setOpacity(255.0f);
            }





            break;
        case ui::Widget::TouchEventType::ENDED:

            break;
        default:
            break;
        }
    });

    this->addChild(_button2);

    // Button3
    _button3 = Button::create("Plank1.png", "Plank2.png");

    _button3->setTitleText("SIMPLE MOVEMENT");
    _button3->setTitleColor(METALLIC_GOLD);
    _button3->setTitleFontName(FONT);
    _button3->setTitleFontSize(FONT_SIZE);
    _button3->setPosition(Vec2(winSize.width / 6, winSize.height / 4));

    _button3->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
        static int s_clickNumber = 0;
        static auto s_winSize = Director::getInstance()->getWinSize();
        switch (type)
        {
        case ui::Widget::TouchEventType::BEGAN:
            s_clickNumber += 1;
            switch (s_clickNumber % 3) {
            case 1:
                _button3->setTitleText("COLLISION MOVEMENT");
                _sprite3->setColor(Color3B::YELLOW);
                

                break;
            case 2:
                _button3->setTitleText("INITIAL STATE");
                _sprite3->setColor(VIOLET);
                _sprite3->setTag(1);


                break;
            case 0:
                _button3->setTitleText("SIMPLE MOVEMENT");
                _sprite3->setPosition(s_winSize.width * 0.67f, s_winSize.height / 4);
                _sprite3->setColor(Color3B::RED);
                _sprite3->setTag(0);
                

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
    });

    this->addChild(_button3);

    



    // QuitButton
    auto quitButton = Button::create("QuitIcon1.png", "QuitIcon2.png");
    quitButton->setScale(0.7f);
    quitButton->setPosition(Vec2(winSize.width - quitButton->getContentSize().width / 2, 
        winSize.height - quitButton->getContentSize().height / 2));

    quitButton->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
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
    });

    this->addChild(quitButton);









    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    //// add a "close" icon to exit the progress. it's an autorelease object
    //auto closeItem = MenuItemImage::create(
    //                                       "CloseNormal.png",
    //                                       "CloseSelected.png",
    //                                       CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

    //if (closeItem == nullptr ||
    //    closeItem->getContentSize().width <= 0 ||
    //    closeItem->getContentSize().height <= 0)
    //{
    //    problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    //}
    //else
    //{
    //    float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
    //    float y = origin.y + closeItem->getContentSize().height/2;
    //    closeItem->setPosition(Vec2(x,y));
    //}

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label

    //auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    //if (label == nullptr)
    //{
    //    problemLoading("'fonts/Marker Felt.ttf'");
    //}
    //else
    //{
    //    // position the label on the center of the screen
    //    label->setPosition(Vec2(origin.x + visibleSize.width/2,
    //                            origin.y + visibleSize.height - label->getContentSize().height));

    //    // add the label as a child to this layer
    //    this->addChild(label, 1);
    //}

    //// add "HelloWorld" splash screen"
    //auto sprite = Sprite::create("HelloWorld.png");
    //if (sprite == nullptr)
    //{
    //    problemLoading("'HelloWorld.png'");
    //}
    //else
    //{
    //    // position the sprite on the center of the screen
    //    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    //    // add the sprite as a child to this layer
    //    this->addChild(sprite, 0);
    //}
    return true;
}

bool HelloWorld::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event*)
{
    if (!_sprite3->getBoundingBox().containsPoint(touch->getLocation()))
        return false;
    
    if (_sprite3->getColor() == Color3B::YELLOW || _sprite3->getColor() == VIOLET) {
        _sprite3->setColor(Color3B::GREEN);
        return true;
    }
    
    return false;
}

bool HelloWorld::checkCollision(Sprite* spriteToCheck, const std::array<cocos2d::Vec2, 4>& spriteToMoveVerts, Vec2 delta)
{
    Rect staticBox = spriteToCheck->getBoundingBox();

    std::array<Vec2, 4> staticBoxVerts;
    staticBoxVerts[0] = staticBox.origin;
    staticBoxVerts[1] = Vec2(staticBox.origin.x, staticBox.getMaxY());
    staticBoxVerts[2] = Vec2(staticBox.getMaxX(), staticBox.getMaxY());
    staticBoxVerts[3] = Vec2(staticBox.getMaxX(), staticBox.origin.y);


    for (int i = 0; i < 4; ++i) {
        for (int j = 1; j < 5; ++j) {
            if (Vec2::isSegmentIntersect(spriteToMoveVerts[i], spriteToMoveVerts[i] + delta,
                staticBoxVerts[j - 1], staticBoxVerts[j % 4])) {
                _spriteToCollide = spriteToCheck;
                return true;
            }
        }
    }
    _spriteToCollide = nullptr;

    return false;
}

Vec2 HelloWorld::calculateCollision(Sprite* spriteToMove, Vec2 newPosition)
{
    Rect boxToMove = spriteToMove->getBoundingBox();
    Vec2 delta{ newPosition.x - boxToMove.getMidX(), newPosition.y - boxToMove.getMidY() };

    std::array<Vec2, 4> boxToMoveVerts;
    boxToMoveVerts[0] = boxToMove.origin;
    boxToMoveVerts[1] = Vec2(boxToMove.origin.x, boxToMove.getMaxY());
    boxToMoveVerts[2] = Vec2(boxToMove.getMaxX(), boxToMove.getMaxY());
    boxToMoveVerts[3] = Vec2(boxToMove.getMaxX(), boxToMove.origin.y);

    bool isColliding = false;
    if (_spriteToCollide) {
        isColliding = checkCollision(_spriteToCollide, boxToMoveVerts, delta);
    }

    if (!isColliding) {
        for (auto staticSprite : _v_sprites) {
            if (staticSprite == _spriteToCollide)
                continue;
            if (checkCollision(staticSprite, boxToMoveVerts, delta)) {
                isColliding = true;
                break;
            }
        }
    }

    if (!isColliding)
        return newPosition;
    
    
    auto a = spriteToMove->getPosition();
    
    Rect staticBox = _spriteToCollide->getBoundingBox();
   
    /*if (delta.y == 0 && delta.x < 0) {
        newPosition.x = staticBox.getMaxX() + boxToMove.size.width / 2 + 10;
        return newPosition;
    }
    if (delta.y == 0 && delta.x > 0) {
        newPosition.x = staticBox.getMinX() - boxToMove.size.width / 2 - 1;
        return newPosition;
    }
    if (delta.x == 0 && delta.y < 0) {
        newPosition.y = staticBox.getMaxY() + boxToMove.size.height / 2 + 1;
        return newPosition;
    }
    if (delta.x == 0 && delta.y > 0) {
        newPosition.y = staticBox.getMinY() - boxToMove.size.height / 2 - 1;
        return newPosition;
    }*/

    //Rect staticBox = spriteToCheck->getBoundingBox();

    std::array<Vec2, 4> staticBoxVerts;
    staticBoxVerts[0] = staticBox.origin;
    staticBoxVerts[1] = Vec2(staticBox.origin.x, staticBox.getMaxY());
    staticBoxVerts[2] = Vec2(staticBox.getMaxX(), staticBox.getMaxY());
    staticBoxVerts[3] = Vec2(staticBox.getMaxX(), staticBox.origin.y);

    int vertexToMove = 0;
    int staticVertex = 2;
    if (delta.x <= 0 && delta.y >= 0) {
        vertexToMove = 1;

    } else if (delta.x >= 0 && delta.y >= 0) {
        vertexToMove = 2;
    }
    else if (delta.x >= 0 && delta.y <= 0) {
        vertexToMove = 3;
    }
    staticVertex = (vertexToMove + 2) % 4;

    for (int counter1 = 0; counter1 < 3; ++counter1) {
        for (int counter2 = 0, nextStaticVertex = (staticVertex + 1) % 4; counter2 < 2; ++counter2) {
            if (Vec2::isSegmentIntersect(boxToMoveVerts[vertexToMove], boxToMoveVerts[vertexToMove] + delta,
                staticBoxVerts[staticVertex], staticBoxVerts[nextStaticVertex])) {
                if (staticBoxVerts[staticVertex].x == staticBoxVerts[nextStaticVertex].x) {
                    newPosition.x = (vertexToMove < 2) ? 
                            staticBox.getMaxX() + boxToMove.size.width / 2 + 1 :
                            staticBox.getMinX() - boxToMove.size.width / 2 - 1;
                }
                else {
                    newPosition.y = (vertexToMove == 0 || vertexToMove == 3) ?
                        staticBox.getMaxY() + boxToMove.size.height / 2 + 1 :
                        staticBox.getMinY() - boxToMove.size.height / 2 - 1;
                }
                return newPosition;
            }
            nextStaticVertex = (staticVertex + 3) % 4;
        }
        vertexToMove = (counter1 == 1) ? (vertexToMove + 2) % 4 : (vertexToMove + 1) % 4;
    }
   // _spriteToCollide = nullptr;

    










    return newPosition;
}

void HelloWorld::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event*)
{
    static Size s_spriteSize = _sprite3->getContentSize();
    static Size s_winSize = Director::getInstance()->getWinSize();

    Vec2 newPosition = touch->getLocation();

   

    if (_sprite3->getTag()) {
        newPosition = calculateCollision(_sprite3, newPosition);
    }

    if (newPosition.x < s_winSize.width / 3 + s_spriteSize.width / 2)
        newPosition.x = s_winSize.width / 3 + s_spriteSize.width / 2;
    if (newPosition.x > s_winSize.width - s_spriteSize.width / 2 - 1)
        newPosition.x = s_winSize.width - s_spriteSize.width / 2 - 1;
    if (newPosition.y < s_spriteSize.height / 2 + 1)
        newPosition.y = s_spriteSize.height / 2 + 1;
    if (newPosition.y > s_winSize.height - s_spriteSize.height / 2 - 1)
        newPosition.y = s_winSize.height - s_spriteSize.height / 2 - 1;

    _sprite3->setPosition(newPosition);









}



void HelloWorld::onTouchEnded(cocos2d::Touch*, cocos2d::Event*)
{
    (_sprite3->getTag()) ? _sprite3->setColor(VIOLET) : _sprite3->setColor(Color3B::YELLOW);
}




void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}
