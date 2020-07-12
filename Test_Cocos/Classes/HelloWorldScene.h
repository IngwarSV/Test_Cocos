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

#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

#include <array>


class HelloWorld : public cocos2d::Scene
{
private:
	cocos2d::Sprite* _sprite1 = nullptr;
	cocos2d::Sprite* _sprite2 = nullptr;
	cocos2d::Sprite* _sprite3 = nullptr;
    cocos2d::Sprite* _spriteToCollide = nullptr;

	cocos2d::Vector<cocos2d::Sprite*> _v_sprites = cocos2d::Vector<cocos2d::Sprite*>(2);

	cocos2d::ui::Button* _button1 = nullptr;
	cocos2d::ui::Button* _button2 = nullptr;
	cocos2d::ui::Button* _button3 = nullptr;


public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    

    bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);
    void onTouchEnded(cocos2d::Touch*, cocos2d::Event*);
    void onTouchMoved(cocos2d::Touch*, cocos2d::Event*);

    bool calculateCollision(cocos2d::Sprite* spriteToMove, cocos2d::Sprite* spriteToCheck, cocos2d::Vec2& newPosition,
        const std::array<cocos2d::Vec2, 4>& spriteToMoveVerts, cocos2d::Vec2 delta, int vertexToMove);
    cocos2d::Vec2 checkCollision(cocos2d::Sprite* spriteToMove, cocos2d::Vec2 newPosition);






    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
