#pragma once


#include "cocos2d.h"
#include "Box2D\Box2D.h"
#include "GLES-Render.h"
#include "SimpleAudioEngine.h"



class Basement : public cocos2d::Layer
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(Basement);

	void update(float) override;
	void addBoxBodyForSprite(Node* sprite);
	void addBoxBodyForStatic(Node * sprite, b2Body * body);
	void addBoxBodyForDynamicBottle(Node * sprite);
	void addBoxBodyForDynamicBottleT(Node * sprite);
	void addBoxBodyForKey(Node * sprite);
	void addBoxBodyForStaticNonWall(Node * sprite, b2Body * body);
	void addBoxBodyForStaticWALL(Node* sprite);
	void addBoxBodyForStaticArrow(Node* sprite);
	void addBoxBodyForEnemy(Node* sprite);

	void addBoxBodyForNote(Node * sprite, b2Body * body);
	
	void tick();

	virtual void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags) override;

private:
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
	bool glassBroken = false;
	bool thrownBottle = false;
	bool thrownBottleT = false;
	bool hasKey = false;
	bool win = false;
	bool kill = false;
	bool leaveGame = false;
	bool destroyLUA = false;
	Node* sprite;
	Node* heal;
	Node* upArrow;
	Node* downArrow;
	Node* downArrow2;
	Node* doorUp;
	Node* doorDown;
	Node* fire;
	Node* light;
	Node* enemyDying;

	Node* crowbar;
	Node* axe;
	Node* bottle;
	Node* glass;
	Node* keyBottle;
	Node* key;
	Node* gasCan;
	Node* keyBottleT;
	Node* logs;
	Node* logsEXP;
	Node* wallFire;
	Node* gasCanEXP;
	Node* idleAnim;
	Node* walkAnim;
	Node* swingAnim;

	Node* floor;
	Node* leftwall;
	Node* rightwall;
	Node* ceiling;
	Node* floor2;
	Node* leftwall2;
	Node* rightwall2;
	Node* ceiling2;
	Node* lockedwall;
	Node* leftwall3;
	Node* rightwall3;
	Node* map2;
	Node* explosion;
	Node* explosionFire;
	Node* bottleT;
	Node* enemyIdle;

	Node* girl1;
	Node* girl2;
	Node* girl3;

	Node* leave;
	b2Body* leaveB;

	Node* enemy;
	Node* lightWin;
	b2Body* enemyB;
	b2World* world;
	GLESDebugDraw *_debugDraw;

	b2Body *floorB;
	b2Body *floor2B;
	b2Body *leftwallB;
	b2Body *leftwall2B;
	b2Body *leftwall3B;
	b2Body *rightwallB;
	b2Body *rightwall2B;
	b2Body *rightwall3B;
	b2Body *ceilingB;
	b2Body *ceiling2B;
	b2Body *lockedwallB;
	b2Body * bottleTB;

	b2Body *spriteBody;
	b2Body *downArrowB;
	b2Body *upArrowB;
	b2Body *doorDownB;
	b2Body *doorUpB;
	b2Body * arrowDownB2;
	b2Body* crowbarB;
	b2Body* logsB;
	b2Body* wallfireB;
	b2Body* axeB;
	b2Body* bottleB;
	b2Body* glassB;
	b2Body* keyBottleB;
	b2Body* keyB;
	b2Body* gasCanB;
	b2Body* keyBottleBT;
	b2Body* lightB;
	b2ContactListener *contactListener;
	b2ContactEdge* edge;
	b2ContactEdge* edge2;
	int id;
	int opacityBottle = 50;
	b2Vec2 enemyP;

	cocos2d::Sprite* display;
	cocos2d::Sprite* display2;
	cocos2d::Sprite* display3;
	cocos2d::Sprite* display4;
	cocos2d::Sprite* display5;
	cocos2d::Sprite* display6;
	cocos2d::Sprite* display7;

	Node* note1;
	b2Body* note1B;
	Node* note2;
	b2Body* note2B;
	Node* note3;
	b2Body* note3B;
	

	cocos2d::Sprite* note1Pic;
	cocos2d::Sprite* note2Pic;
	cocos2d::Sprite* note3Pic;
	
};