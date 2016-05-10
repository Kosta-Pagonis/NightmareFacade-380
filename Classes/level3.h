
#pragma once

#include "cocos2d.h"
#include "Box2D\Box2D.h"
#include "GLES-Render.h"
#include "SimpleAudioEngine.h"


class level3 : public cocos2d::Layer
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(level3);

	void update(float) override;
	void addBoxBodyForSprite(Node* sprite);
	void addBoxBodyForStaticWall(Node * sprite, b2Body * body);
	void addBoxBodyForCheese(Node * sprite);
	void addBoxBodyForPoison(Node * sprite);
	void addBoxBodyForPit(Node * sprite);
	void addBoxBodyForPitGhost(Node * sprite);
	void addBoxBodyForGem(Node * sprite);
	void addBoxBodyForRat(Node * sprite);
	void addBoxBodyForMagicWall(Node * sprite);

	void addBoxBodyForRatPush(Node * sprite);
	
	void addBoxBodyForDownArrowToPit(Node * sprite);
	void addBoxBodyForUpArrowFromPit(Node * sprite);
	void addBoxBodyForDownArrowFromRat(Node * sprite);
	void addBoxBodyForUpArrowToRat(Node * sprite);
	void addBoxBodyForNote(Node * sprite);

	void addBoxBodyForNote(Node * sprite, b2Body * body);

	void addBoxBodyForChanger(Node * sprite);
	
	void addBoxBodyForGhost(Node * sprite);
	void addBoxBodyForEnemy(Node * sprite);
	

	void displayInv();


	void tick();

	virtual void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags) override;

private:
	b2World* world;
	b2ContactListener *contactListener;
	b2ContactEdge* edge;


	b2Body* floorB;
	b2Body* leftWallB;
	b2Body* rightWallB;
	b2Body* ceilingB;
	b2Body* ceiling2B;
	b2Body* leftWall2B;
	b2Body* middleWallB;
	b2Body* middleWall2B;
	b2Body* gateWallB;
	Node* floor;
	Node* leftWall;
	Node* rightWall;
	Node* ceiling;
	Node* ceiling2;
	Node* leftWall2;
	Node* middleWall;
	Node* middleWall2;
	Node* gateWall;


	//-----------------------------WORLD WALLS END

	//------------PLayer
	b2Body* spriteBody;
	Node* sprite;
	Node* idleAnim;
	Node* walkAnim;

	Node* cheese;
	b2Body* cheeseB;
	Node* poison;
	b2Body* poisonB;
	
	Node* note1;
	b2Body* note1B;
	Node* note2;
	b2Body* note2B;
	
	
	Node* gem;
	b2Body* gemB;

	Node* downArrowToPit;
	Node* upArrowFromPit;
	Node* downArrowFromRat;
	Node* upArrowToRat;

	b2Body* downArrowToPitB;
	b2Body* upArrowFromPitB;
	b2Body* downArrowFromRatB;
	b2Body* upArrowToRatB;

	Node* ghost;
	b2Body* ghostB;
	Node* enemy;
	b2Body* enemyB;
	Node* changer;
	b2Body* changerB;
	Node* level3Pic;
	Node* enemyPit;
	Node* exit;
	b2Body* exitB;

	Node* pit;
	b2Body* pitB;

	Node* rat;
	b2Body* ratB;
	b2Vec2 ratPosition;

	Node* ratPush;
	b2Body* ratPushB;
	

	Node* ghostPit;
	b2Body* ghostPitB;
	b2Vec2 ghostPitPosition;

	Node* pitFire;
	Node* hung;

	Node* savedEnemy;
	Node* space;

	//--- INV
	cocos2d::Sprite* crobarPic;
	cocos2d::Sprite* axePic;
	cocos2d::Sprite* bowPic;
	cocos2d::Sprite* bowLightPic;
	cocos2d::Sprite* cheesePic;
	cocos2d::Sprite* poisonPic;
	cocos2d::Sprite* gemPic;

	cocos2d::Sprite* note1Pic;
	cocos2d::Sprite* note2Pic;
	



	//------------ BOOLS
	bool charMovingLeft;
	bool charMovingRight;
	bool charMovingUp;
	bool charMovingDown;
	bool charUsing;
	bool movedL;
	bool movedR;
	bool charRun;
	bool charSwing;
	bool invL;
	bool invR;
	bool destroyLua;
	bool inPitRoom;
	bool killedGhostPit;
	bool ratDied;
	bool pickedGhost;
	bool pickedEnemy;
	bool end;
	//----------- 
	int id;
	

	//-----------  BOSS BATTLES
	
	

};
