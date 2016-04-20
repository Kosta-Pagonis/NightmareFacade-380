#pragma once

#include "cocos2d.h"
#include "SimpleAudioEngine.h"


class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // implement the "static create()" method manually
	virtual void onMouseUp(cocos2d::Event*);
    CREATE_FUNC(HelloWorld);

private:
	


	

};
