#pragma once

#include "cocos2d.h"

class BasementR1 : public cocos2d::Layer
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(BasementR1);

	void update(float) override;

private:
	bool charMovingLeft;
	bool charMovingRight;
	Node* player;
	Node* leftarrow;
	Node* downarrow;
	Node* crowbar;
};