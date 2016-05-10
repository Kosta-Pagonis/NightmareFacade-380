#pragma once

#include "cocos2d.h"
#include "Box2D\Box2D.h"
#include "GLES-Render.h"
#include "SimpleAudioEngine.h"

class NFMenu : public cocos2d::Layer
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(NFMenu);

	void update(float) override;
	void addBoxBodyForSprite(Node* sprite);
	void addBoxBodyForStatic(Node * sprite, b2Body * body);
	void tick();
	
	virtual void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags) override;

private:
	bool charMovingLeft;
	bool charMovingRight;
	bool playLit;
	bool helpLit;
	bool quitLit;
	
	Node* sprite;
	Node* play;
	Node* help;
	Node* quit;
	Node* bed;
	Node* desk;
	Node* door;
	Node* tips;

	Node* idleAnim;
	Node* leftAnim;
	Node* rightAnim;

	b2World* world;
	GLESDebugDraw *_debugDraw;
	
	b2Body *_groundBody;
	b2Fixture *_bottomFixture;
	
	b2Body *spriteBody;
	
	b2Body * bedBody;
	b2Body * deskBody;
	b2Body * doorBody;
	
	b2ContactListener *contactListener;
	
	
};