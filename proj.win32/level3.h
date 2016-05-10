
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
	void addBoxBodyForLeverBottom(Node * sprite);
	void addBoxBodyForDownArrowBoiler(Node * sprite);
	void addBoxBodyForLeverBase(Node * sprite);
	void addBoxBodyForUpArrowLibrary(Node * sprite);
	void addBoxBodyForBucket(Node * sprite);
	void addBoxBodyForStove(Node * sprite);
	void addBoxBodyForLeverTop(Node * sprite);
	void addBoxBodyForBookshelf(Node * sprite);
	void addBoxBodyForUpArrowSecretRoom(Node * sprite);
	void addBoxBodyForDownArrowLibrary(Node * sprite);
	void addBoxBodyForBench(Node * sprite);
	void addBoxBodyForGhost(Node * sprite);
	void addBoxBodyForEnemy(Node * sprite);
	void addBoxBodyForDownArrowSecretRoom(Node * sprite);
	void addBoxBodyForWaterBarrel(Node * sprite);
	void addBoxBodyForEmptyBox(Node * sprite);
	void addBoxBodyForLeverBox(Node * sprite);
	void addBoxBodyForEvilBox(Node * sprite);
	void addBoxBodyForLeverMiddle(Node * sprite);
	void addBoxBodyForBow(Node * sprite);
	void addBoxBodyForGateWall(Node* sprite);
	void addBoxBodyForUpArrowBoiler(Node * sprite);

	void displayInv();

	void addBoxBodyForPower(Node * sprite);

	void addBoxBodyForLight(Node * sprite);

	void addBoxBodyForPortal(Node * sprite);

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
	b2Body* rightWall2B;
	b2Body* middleWallB;
	b2Body* middleWall2B;
	b2Body* gateWallB;
	Node* floor;
	Node* leftWall;
	Node* rightWall;
	Node* ceiling;
	Node* ceiling2;
	Node* leftWall2;
	Node* rightWall2;
	Node* middleWall;
	Node* middleWall2;
	Node* gateWall;
	Node* rain;
	Node* rainAnim;

	//-----------------------------WORLD WALLS END

	//------------PLayer
	b2Body* spriteBody;
	Node* sprite;
	Node* idleAnim;
	Node* walkAnim;

	//----Boiler Room
	Node* stove;
	b2Body* stoveB;
	Node* stoveHotColor;
	Node* leverTop;
	b2Body* leverTopB;
	Node* grateClosed;
	Node* grateOpened;
	Node* boilerRoomNote;
	b2Body* boilerRoomNoteB;
	Node* upArrowBoiler;
	b2Body* upArrowBoilerB;

	//------Library
	Node* bookshelf;
	b2Body* bookshelfB;
	Node* upArrowSecretRoom;
	b2Body* upArrowSecretRoomB;
	Node* downArrowLibrary;
	b2Body* downArrowLibraryB;
	Node* libraryNote;
	b2Body* libraryNoteB;

	//----SecretRoom
	Node* downArrowSecretRoom;
	b2Body* downArrowSecretRoomB;
	Node* secretRoomNote;
	b2Body* secretRoomNoteB;
	Node* waterBarrel;
	b2Body* waterBarrelB;
	Node* leverMiddle;
	b2Body* leverMiddleB;
	Node* emptyBox;
	b2Body* emptyBoxB;
	Node* leverBox;
	b2Body* leverBoxB;
	Node* evilBox;
	b2Body* evilBoxB;

	//------Room1
	Node* leverBottom;
	b2Body* leverBottomB;
	Node* downArrowBoiler;
	b2Body* downArrowBoilerB;

	//------Room 2
	Node* leverBase;
	b2Body* leverBaseB;
	Node* bucket;
	b2Body* bucketB;
	Node* upArrowLibrary;
	b2Body* upArrowLibraryB;
	Node* gate;

	//----Transition
	Node* bow;
	b2Body* bowB;

	//--- INV
	cocos2d::Sprite* crobarPic;
	cocos2d::Sprite* axePic;
	cocos2d::Sprite* leverBottomPic;
	cocos2d::Sprite* leverMiddlePic;
	cocos2d::Sprite* leverTopPic;
	cocos2d::Sprite* bucketEmptyPic;
	cocos2d::Sprite* bucketFullPic;
	cocos2d::Sprite* bowPic;
	cocos2d::Sprite* fullLever;



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
	bool brokeCrateLever;
	bool brokeEvilBox;
	bool chase;
	bool inLibrary;
	bool teleportedChase;
	bool inLight;
	bool ghostDied;
	bool destroyLua;
	//----------- 
	int id;
	Node* interactText;
	Node* crateAnimEmpty;
	Node* crateAnimLever;
	Node* crateAnimEvil;

	Node* workBench;
	b2Body* workBenchB;

	Node* leverBottomBench;
	Node* leverMiddleBench;
	Node* leverTopBench;

	Node* leverComplete;
	Node* leverPulled;

	//-----------  BOSS BATTLES
	Node* portal;
	b2Body* portalB;
	Node* ghost;
	Node* ghostBody;
	b2Body* ghostB;
	Node* enemy;
	b2Body* enemyB;
	Node* light;
	b2Body* lightB;
	Node* power;
	b2Body* powerB;
	Node* exit;
	b2Body* exitB;

};
