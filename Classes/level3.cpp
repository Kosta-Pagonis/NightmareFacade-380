#include "BasementRoom1.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h"
#include "cocostudio\CocoStudio.h"
#include "cocostudio\ActionTimeline\CCActionTimelineNode.h"
#include "2d\CCLight.h"
#include "MenuScene.h"
#include "level2.h"
#include "luaplus.h"
#include "level3.h"


using namespace cocostudio::timeline;
using namespace LuaPlus;
USING_NS_CC;
#define PTM_RATIO 30


auto audioLv3 = CocosDenshion::SimpleAudioEngine::getInstance();
LuaState* luaPStateLv3 = LuaState::Create();
int resultLv3 = luaPStateLv3->DoFile("stats.lua");
LuaFunction<int> getHeldItemLv3 = luaPStateLv3->GetGlobal("getHeldItem");
LuaFunction<void> shiftInventoryRightLv3 = luaPStateLv3->GetGlobal("shiftInventoryRight");
LuaFunction<void> shiftInventoryLeftLv3 = luaPStateLv3->GetGlobal("shiftInventoryLeft");
LuaFunction<void> addItemLv3 = luaPStateLv3->GetGlobal("addItem");
LuaFunction<void> removeItemLv3 = luaPStateLv3->GetGlobal("removeItem");
LuaFunction<void> setHeldItemLv3 = luaPStateLv3->GetGlobal("setHeldItem");

Scene* level3::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = level3::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

void level3::addBoxBodyForSprite(Node * sprite)
{
	sprite->setAnchorPoint(Vec2(.5, .5));
	b2BodyDef spriteBodyDef;
	spriteBodyDef.type = b2_dynamicBody;
	spriteBodyDef.gravityScale = 9;
	spriteBodyDef.position.Set(sprite->getPositionX() / PTM_RATIO,
		sprite->getPositionY() / PTM_RATIO);
	spriteBodyDef.userData = sprite;
	spriteBody = world->CreateBody(&spriteBodyDef);

	b2PolygonShape spriteShape;
	spriteShape.SetAsBox(sprite->getContentSize().width / PTM_RATIO / 2,
		sprite->getContentSize().height / PTM_RATIO / 2);
	b2FixtureDef spriteShapeDef;
	spriteShapeDef.shape = &spriteShape;
	spriteShapeDef.density = 4.4;
	spriteShapeDef.isSensor = false;
	spriteBody->CreateFixture(&spriteShapeDef);
}
void level3::addBoxBodyForStaticWall(Node * sprite, b2Body * body)
{
	sprite->setAnchorPoint(Vec2(.5, .5));
	b2BodyDef spriteBodyDef;
	spriteBodyDef.type = b2_staticBody;
	spriteBodyDef.position.Set(sprite->getPositionX() / PTM_RATIO,
		sprite->getPositionY() / PTM_RATIO);
	spriteBodyDef.userData = sprite;
	body = world->CreateBody(&spriteBodyDef);

	b2PolygonShape spriteShape;
	spriteShape.SetAsBox(sprite->getContentSize().width / PTM_RATIO / 2 * sprite->getScaleX(),
		sprite->getContentSize().height / PTM_RATIO / 2 * sprite->getScaleY());
	b2FixtureDef spriteShapeDef;
	spriteShapeDef.shape = &spriteShape;
	spriteShapeDef.density = 1.0;
	spriteShapeDef.isSensor = false;
	body->CreateFixture(&spriteShapeDef);
}
void level3::addBoxBodyForCheese(Node * sprite)
{
	sprite->setAnchorPoint(Vec2(.5, .5));
	b2BodyDef spriteBodyDef;
	spriteBodyDef.type = b2_staticBody;
	spriteBodyDef.position.Set(sprite->getPositionX() / PTM_RATIO,
		sprite->getPositionY() / PTM_RATIO);
	spriteBodyDef.userData = sprite;
	cheeseB = world->CreateBody(&spriteBodyDef);

	b2PolygonShape spriteShape;
	spriteShape.SetAsBox(sprite->getContentSize().width / PTM_RATIO / 2 * sprite->getScaleX(),
		sprite->getContentSize().height / PTM_RATIO / 2 * sprite->getScaleY());
	b2FixtureDef spriteShapeDef;
	spriteShapeDef.shape = &spriteShape;
	spriteShapeDef.density = 1.0;
	spriteShapeDef.isSensor = true;
	cheeseB->CreateFixture(&spriteShapeDef);
}
void level3::addBoxBodyForPoison(Node * sprite)
{
	sprite->setAnchorPoint(Vec2(.5, .5));
	b2BodyDef spriteBodyDef;
	spriteBodyDef.type = b2_staticBody;
	spriteBodyDef.position.Set(sprite->getPositionX() / PTM_RATIO,
		sprite->getPositionY() / PTM_RATIO);
	spriteBodyDef.userData = sprite;
	poisonB = world->CreateBody(&spriteBodyDef);

	b2PolygonShape spriteShape;
	spriteShape.SetAsBox(sprite->getContentSize().width / PTM_RATIO / 2 * sprite->getScaleX(),
		sprite->getContentSize().height / PTM_RATIO / 2 * sprite->getScaleY());
	b2FixtureDef spriteShapeDef;
	spriteShapeDef.shape = &spriteShape;
	spriteShapeDef.density = 1.0;
	spriteShapeDef.isSensor = true;
	poisonB->CreateFixture(&spriteShapeDef);
}
void level3::addBoxBodyForPit(Node * sprite)
{
	sprite->setAnchorPoint(Vec2(.5, .5));
	b2BodyDef spriteBodyDef;
	spriteBodyDef.type = b2_staticBody;
	spriteBodyDef.position.Set(sprite->getPositionX() / PTM_RATIO,
		sprite->getPositionY() / PTM_RATIO);
	spriteBodyDef.userData = sprite;
	pitB = world->CreateBody(&spriteBodyDef);

	b2PolygonShape spriteShape;
	spriteShape.SetAsBox(sprite->getContentSize().width / PTM_RATIO / 2 * sprite->getScaleX(),
		sprite->getContentSize().height / PTM_RATIO / 2 * sprite->getScaleY());
	b2FixtureDef spriteShapeDef;
	spriteShapeDef.shape = &spriteShape;
	spriteShapeDef.density = 1.0;
	spriteShapeDef.isSensor = true;
	pitB->CreateFixture(&spriteShapeDef);
}
void level3::addBoxBodyForPitGhost(Node * sprite)
{
	sprite->setAnchorPoint(Vec2(.5, .5));
	b2BodyDef spriteBodyDef;
	spriteBodyDef.type = b2_dynamicBody;
	//spriteBodyDef.gravityScale = 0;
	spriteBodyDef.position.Set(sprite->getPositionX() / PTM_RATIO,
		sprite->getPositionY() / PTM_RATIO);
	spriteBodyDef.userData = sprite;
	ghostPitB = world->CreateBody(&spriteBodyDef);

	b2PolygonShape spriteShape;
	spriteShape.SetAsBox(sprite->getContentSize().width / PTM_RATIO / 2 * sprite->getScaleX(),
		sprite->getContentSize().height / PTM_RATIO / 2 * sprite->getScaleY());
	b2FixtureDef spriteShapeDef;
	spriteShapeDef.shape = &spriteShape;
	spriteShapeDef.density = 5.0;
	spriteShapeDef.isSensor = false;
	ghostPitB->CreateFixture(&spriteShapeDef);
}
void level3::addBoxBodyForGem(Node * sprite)
{
	sprite->setAnchorPoint(Vec2(.5, .5));
	b2BodyDef spriteBodyDef;
	spriteBodyDef.type = b2_staticBody;
	spriteBodyDef.position.Set(sprite->getPositionX() / PTM_RATIO,
		sprite->getPositionY() / PTM_RATIO);
	spriteBodyDef.userData = sprite;
	gemB = world->CreateBody(&spriteBodyDef);

	b2PolygonShape spriteShape;
	spriteShape.SetAsBox(sprite->getContentSize().width / PTM_RATIO / 2 * sprite->getScaleX(),
		sprite->getContentSize().height / PTM_RATIO / 2 * sprite->getScaleY());
	b2FixtureDef spriteShapeDef;
	spriteShapeDef.shape = &spriteShape;
	spriteShapeDef.density = 1.0;
	spriteShapeDef.isSensor = true;
	gemB->CreateFixture(&spriteShapeDef);
}
void level3::addBoxBodyForRat(Node * sprite)
{
	sprite->setAnchorPoint(Vec2(.5, .5));
	b2BodyDef spriteBodyDef;
	spriteBodyDef.type = b2_dynamicBody;
	spriteBodyDef.gravityScale = 0;
	spriteBodyDef.position.Set(sprite->getPositionX() / PTM_RATIO,
		sprite->getPositionY() / PTM_RATIO);
	spriteBodyDef.userData = sprite;
	ratB = world->CreateBody(&spriteBodyDef);

	b2PolygonShape spriteShape;
	spriteShape.SetAsBox(sprite->getContentSize().width / PTM_RATIO / 2 * sprite->getScaleX(),
		sprite->getContentSize().height / PTM_RATIO /2 * sprite->getScaleY()+2) ;
	b2FixtureDef spriteShapeDef;
	spriteShapeDef.shape = &spriteShape;
	spriteShapeDef.density = 1.0;
	spriteShapeDef.isSensor = true;
	ratB->CreateFixture(&spriteShapeDef);
}
void level3::addBoxBodyForMagicWall(Node * sprite)
{
	sprite->setAnchorPoint(Vec2(.5, .5));
	b2BodyDef spriteBodyDef;
	spriteBodyDef.type = b2_staticBody;
	spriteBodyDef.position.Set(sprite->getPositionX() / PTM_RATIO,
		sprite->getPositionY() / PTM_RATIO);
	spriteBodyDef.userData = sprite;
	gateWallB = world->CreateBody(&spriteBodyDef);

	b2PolygonShape spriteShape;
	spriteShape.SetAsBox(sprite->getContentSize().width / PTM_RATIO / 2 * sprite->getScaleX(),
		sprite->getContentSize().height / PTM_RATIO / 2 * sprite->getScaleY());
	b2FixtureDef spriteShapeDef;
	spriteShapeDef.shape = &spriteShape;
	spriteShapeDef.density = 1.0;
	spriteShapeDef.isSensor = false;
	gateWallB->CreateFixture(&spriteShapeDef);
}
void level3::addBoxBodyForRatPush(Node * sprite)
{
	sprite->setAnchorPoint(Vec2(.5, .5));
	b2BodyDef spriteBodyDef;
	spriteBodyDef.type = b2_staticBody;
	spriteBodyDef.position.Set(sprite->getPositionX() / PTM_RATIO,
		sprite->getPositionY() / PTM_RATIO);
	spriteBodyDef.userData = sprite;
	ratPushB = world->CreateBody(&spriteBodyDef);

	b2PolygonShape spriteShape;
	spriteShape.SetAsBox(sprite->getContentSize().width / PTM_RATIO / 2 * sprite->getScaleX(),
		sprite->getContentSize().height / PTM_RATIO / 2 * sprite->getScaleY());
	b2FixtureDef spriteShapeDef;
	spriteShapeDef.shape = &spriteShape;
	spriteShapeDef.density = 1.0;
	spriteShapeDef.isSensor = true;
	ratPushB->CreateFixture(&spriteShapeDef);
}
void level3::addBoxBodyForDownArrowToPit(Node * sprite)
{
	sprite->setAnchorPoint(Vec2(.5, .5));
	b2BodyDef spriteBodyDef;
	spriteBodyDef.type = b2_staticBody;
	spriteBodyDef.position.Set(sprite->getPositionX() / PTM_RATIO,
		sprite->getPositionY() / PTM_RATIO);
	spriteBodyDef.userData = sprite;
	downArrowToPitB = world->CreateBody(&spriteBodyDef);

	b2PolygonShape spriteShape;
	spriteShape.SetAsBox(sprite->getContentSize().width / PTM_RATIO / 2 * sprite->getScaleX(),
		sprite->getContentSize().height / PTM_RATIO / 2 * sprite->getScaleY());
	b2FixtureDef spriteShapeDef;
	spriteShapeDef.shape = &spriteShape;
	spriteShapeDef.density = 1.0;
	spriteShapeDef.isSensor = true;
	downArrowToPitB->CreateFixture(&spriteShapeDef);
}

void level3::addBoxBodyForUpArrowFromPit(Node * sprite)
{
	sprite->setAnchorPoint(Vec2(.5, .5));
	b2BodyDef spriteBodyDef;
	spriteBodyDef.type = b2_staticBody;
	spriteBodyDef.position.Set(sprite->getPositionX() / PTM_RATIO,
		sprite->getPositionY() / PTM_RATIO);
	spriteBodyDef.userData = sprite;
	upArrowFromPitB = world->CreateBody(&spriteBodyDef);

	b2PolygonShape spriteShape;
	spriteShape.SetAsBox(sprite->getContentSize().width / PTM_RATIO / 2 * sprite->getScaleX(),
		sprite->getContentSize().height / PTM_RATIO / 2 * sprite->getScaleY());
	b2FixtureDef spriteShapeDef;
	spriteShapeDef.shape = &spriteShape;
	spriteShapeDef.density = 1.0;
	spriteShapeDef.isSensor = true;
	upArrowFromPitB->CreateFixture(&spriteShapeDef);
}

void level3::addBoxBodyForDownArrowFromRat(Node * sprite)
{
	sprite->setAnchorPoint(Vec2(.5, .5));
	b2BodyDef spriteBodyDef;
	spriteBodyDef.type = b2_staticBody;
	spriteBodyDef.position.Set(sprite->getPositionX() / PTM_RATIO,
		sprite->getPositionY() / PTM_RATIO);
	spriteBodyDef.userData = sprite;
	downArrowFromRatB = world->CreateBody(&spriteBodyDef);

	b2PolygonShape spriteShape;
	spriteShape.SetAsBox(sprite->getContentSize().width / PTM_RATIO / 2 * sprite->getScaleX(),
		sprite->getContentSize().height / PTM_RATIO / 2 * sprite->getScaleY());
	b2FixtureDef spriteShapeDef;
	spriteShapeDef.shape = &spriteShape;
	spriteShapeDef.density = 1.0;
	spriteShapeDef.isSensor = true;
	downArrowFromRatB->CreateFixture(&spriteShapeDef);
}

void level3::addBoxBodyForUpArrowToRat(Node * sprite)
{
	sprite->setAnchorPoint(Vec2(.5, .5));
	b2BodyDef spriteBodyDef;
	spriteBodyDef.type = b2_staticBody;
	spriteBodyDef.position.Set(sprite->getPositionX() / PTM_RATIO,
		sprite->getPositionY() / PTM_RATIO);
	spriteBodyDef.userData = sprite;
	upArrowToRatB = world->CreateBody(&spriteBodyDef);

	b2PolygonShape spriteShape;
	spriteShape.SetAsBox(sprite->getContentSize().width / PTM_RATIO / 2 * sprite->getScaleX(),
		sprite->getContentSize().height / PTM_RATIO / 2 * sprite->getScaleY());
	b2FixtureDef spriteShapeDef;
	spriteShapeDef.shape = &spriteShape;
	spriteShapeDef.density = 1.0;
	spriteShapeDef.isSensor = true;
	upArrowToRatB->CreateFixture(&spriteShapeDef);
}

void level3::addBoxBodyForNote(Node * sprite, b2Body* body)
{
	sprite->setAnchorPoint(Vec2(.5, .5));
	b2BodyDef spriteBodyDef;
	spriteBodyDef.type = b2_staticBody;
	spriteBodyDef.position.Set(sprite->getPositionX() / PTM_RATIO,
		sprite->getPositionY() / PTM_RATIO);
	spriteBodyDef.userData = sprite;
	body = world->CreateBody(&spriteBodyDef);

	b2PolygonShape spriteShape;
	spriteShape.SetAsBox(sprite->getContentSize().width / PTM_RATIO / 2 * sprite->getScaleX(),
		sprite->getContentSize().height / PTM_RATIO / 2 * sprite->getScaleY());
	b2FixtureDef spriteShapeDef;
	spriteShapeDef.shape = &spriteShape;
	spriteShapeDef.density = 1.0;
	spriteShapeDef.isSensor = true;
	body->CreateFixture(&spriteShapeDef);
}
void level3::addBoxBodyForChanger(Node * sprite)
{
	sprite->setAnchorPoint(Vec2(.5, .5));
	b2BodyDef spriteBodyDef;
	spriteBodyDef.type = b2_staticBody;
	//spriteBodyDef.gravityScale = 0;
	spriteBodyDef.position.Set(sprite->getPositionX() / PTM_RATIO,
		sprite->getPositionY() / PTM_RATIO);
	spriteBodyDef.userData = sprite;
	changerB = world->CreateBody(&spriteBodyDef);

	b2PolygonShape spriteShape;
	spriteShape.SetAsBox(sprite->getContentSize().width / PTM_RATIO / 2 * sprite->getScaleX(),
		sprite->getContentSize().height / PTM_RATIO / 2 * sprite->getScaleY());
	b2FixtureDef spriteShapeDef;
	spriteShapeDef.shape = &spriteShape;
	spriteShapeDef.density = 13.0;
	spriteShapeDef.isSensor = true;
	changerB->CreateFixture(&spriteShapeDef);
}

void level3::addBoxBodyForGhost(Node * sprite)
{
	sprite->setAnchorPoint(Vec2(.5, .5));
	b2BodyDef spriteBodyDef;
	spriteBodyDef.type = b2_staticBody;
	//spriteBodyDef.gravityScale = 0;
	spriteBodyDef.position.Set(sprite->getPositionX() / PTM_RATIO,
		sprite->getPositionY() / PTM_RATIO);
	spriteBodyDef.userData = sprite;
	ghostB = world->CreateBody(&spriteBodyDef);

	b2PolygonShape spriteShape;
	spriteShape.SetAsBox(sprite->getContentSize().width / PTM_RATIO / 2 * sprite->getScaleX(),
		sprite->getContentSize().height / PTM_RATIO / 2 * sprite->getScaleY());
	b2FixtureDef spriteShapeDef;
	spriteShapeDef.shape = &spriteShape;
	spriteShapeDef.density = 13.0;
	spriteShapeDef.isSensor = true;
	ghostB->CreateFixture(&spriteShapeDef);
}


void level3::addBoxBodyForEnemy(Node * sprite)
{
	sprite->setAnchorPoint(Vec2(.5, .5));
	b2BodyDef spriteBodyDef;
	spriteBodyDef.type = b2_staticBody;
	spriteBodyDef.position.Set(sprite->getPositionX() / PTM_RATIO,
		sprite->getPositionY() / PTM_RATIO);
	spriteBodyDef.userData = sprite;
	enemyB = world->CreateBody(&spriteBodyDef);

	b2PolygonShape spriteShape;
	spriteShape.SetAsBox(sprite->getContentSize().width / PTM_RATIO / 4 * sprite->getScaleX(),
		sprite->getContentSize().height / PTM_RATIO / 4 * sprite->getScaleY());
	b2FixtureDef spriteShapeDef;
	spriteShapeDef.shape = &spriteShape;
	spriteShapeDef.density = 1.0;
	spriteShapeDef.isSensor = true;
	enemyB->CreateFixture(&spriteShapeDef);
}

void level3::displayInv()
{
	id = getHeldItemLv3();  // displays depending on invetory item

	
	axePic->setPosition(sprite->getPositionX() - 20, sprite->getPositionY() - 20);      // sets position of the inventory image
	crobarPic->setPosition(sprite->getPositionX() - 20, sprite->getPositionY() - 20);
	bowPic->setPosition(sprite->getPositionX() - 20, sprite->getPositionY() - 20);
	bowLightPic->setPosition(sprite->getPositionX() - 20, sprite->getPositionY() - 20);
	cheesePic->setPosition(sprite->getPositionX() - 20, sprite->getPositionY() - 20);
	poisonPic->setPosition(sprite->getPositionX() - 20, sprite->getPositionY() - 20);
	gemPic->setPosition(sprite->getPositionX() - 20, sprite->getPositionY() - 20);
	note1Pic->setPosition(sprite->getPositionX() - 20, sprite->getPositionY() - 20);
	note2Pic->setPosition(sprite->getPositionX() - 20, sprite->getPositionY() - 20);
	
	if (id == 1)
	{
		crobarPic->setOpacity(155);
		axePic->setOpacity(0);
		bowPic->setOpacity(0);
		cheesePic->setOpacity(0);
		poisonPic->setOpacity(0);
		gemPic->setOpacity(0);
	}
	if (id == 2)
	{
		crobarPic->setOpacity(0);
		axePic->setOpacity(155);
		bowPic->setOpacity(0);
		cheesePic->setOpacity(0);
		poisonPic->setOpacity(0);
		gemPic->setOpacity(0);
	}
	if (id == 3)
	{
		crobarPic->setOpacity(0);
		axePic->setOpacity(0);
		bowPic->setOpacity(155);
		cheesePic->setOpacity(0);
		poisonPic->setOpacity(0);
		gemPic->setOpacity(0);
		if (inPitRoom == true)
			bowLightPic->setOpacity(155);
		else
			bowLightPic->setOpacity(0);
	}
	else
		bowLightPic->setOpacity(0);
	if (id == 4)
	{
		crobarPic->setOpacity(0);
		axePic->setOpacity(0);
		bowPic->setOpacity(0);
		cheesePic->setOpacity(155);
		poisonPic->setOpacity(0);
		gemPic->setOpacity(0);
	}
	if (id == 5)
	{
		crobarPic->setOpacity(0);
		axePic->setOpacity(0);
		bowPic->setOpacity(0);
		cheesePic->setOpacity(0);
		poisonPic->setOpacity(155);
		gemPic->setOpacity(0);
	}
	if (id == 6)
	{
		crobarPic->setOpacity(0);
		axePic->setOpacity(0);
		bowPic->setOpacity(0);
		cheesePic->setOpacity(0);
		poisonPic->setOpacity(0);
		gemPic->setOpacity(155);
	}


}

void level3::tick()
{
	world->Step(1.0f / 60.0f, 10, 10);
	idleAnim->setPosition(sprite->getPosition());
	walkAnim->setPosition(sprite->getPosition());
	for (b2Body *b = world->GetBodyList(); b; b = b->GetNext()) {
		if (b->GetUserData() != NULL) {
			CCSprite *sprite = (CCSprite *)b->GetUserData();
			sprite->setPosition(ccp(b->GetPosition().x * PTM_RATIO,
				b->GetPosition().y * PTM_RATIO));
			sprite->setRotation(-1 * CC_RADIANS_TO_DEGREES(b->GetAngle()));
		}
	}

	edge = spriteBody->GetContactList();


	while (edge != NULL && edge->contact != NULL && destroyLua == false)
	{
		if (edge->contact->GetFixtureB()->GetBody()->GetUserData() == downArrowToPit)
		{
			downArrowToPit->setOpacity(20);
			if (charMovingDown)
			{
				spriteBody->SetTransform(b2Vec2(20, 24), 0);
				inPitRoom = true;
				if (killedGhostPit == false)
				{
					audioLv3->playBackgroundMusic("Horror.wav");
					audioLv3->playEffect("mouse.wav");
				}
			}
			
		}

		if (edge->contact->GetFixtureB()->GetBody()->GetUserData() == upArrowFromPit)
		{
			upArrowFromPit->setOpacity(20);
			if (charMovingUp)
			{
				spriteBody->SetTransform(b2Vec2(28, 5), 0);
				inPitRoom = false;
				if (killedGhostPit == false)
				{
					ghostPitB->SetLinearVelocity(b2Vec2(0, 0));
					ghostPitB->SetTransform(ghostPitPosition, 0);
					audioLv3->playBackgroundMusic("ambience.wav");
				}
			}
			
		}

		if (edge->contact->GetFixtureB()->GetBody()->GetUserData()== upArrowToRat)
		{
			upArrowToRat->setOpacity(20);
			if (charMovingUp)
			{
				spriteBody->SetTransform(b2Vec2(40, 27), 0);

				if (ratDied == false)
				{
					ratB->SetLinearVelocity(b2Vec2(-5, 0));
					audioLv3->playBackgroundMusic("Horror.wav");
					audioLv3->playEffect("mouse.wav");
				}
			}
		}

		if (edge->contact->GetFixtureB()->GetBody()->GetUserData() == downArrowFromRat)
		{
			downArrowFromRat->setOpacity(20);
			if (charMovingDown)
			{
				spriteBody->SetTransform(b2Vec2(50, 5), 0);
				if (ratDied == false)
				{
					ratB->SetLinearVelocity(b2Vec2(0, 0));
					ratB->SetTransform(ratPosition, 0);
					audioLv3->playBackgroundMusic("ambience.wav",true);
				}
			}
		}

		if (edge->contact->GetFixtureB()->GetBody() == cheeseB)
		{
			if (charUsing && id == 5)
			{
				audioLv3->playEffect("pickup.wav");
				cheese->setOpacity(0);
				world->DestroyBody(cheeseB);
				removeItemLv3(5);
				addItemLv3(4);
				setHeldItemLv3(4);
			}
		}
		if (edge->contact->GetFixtureB()->GetBody() == poisonB)
		{
			if (charUsing)
			{
				audioLv3->playEffect("pickup.wav");
				poison->setOpacity(0);
				world->DestroyBody(poisonB);
				addItemLv3(5);
				setHeldItemLv3(5);
			}
		}
		if (edge->contact->GetFixtureB()->GetBody() == gemB)
		{
			if (charUsing)
			{
				audioLv3->playEffect("pickup.wav");
				gem->setOpacity(0);
				world->DestroyBody(gemB);
				addItemLv3(6);
				setHeldItemLv3(6);
				world->DestroyBody(gateWallB);
			}
			
		}
		if (edge->contact->GetFixtureB()->GetBody() == ratPushB)
		{
			ghostPitB->SetLinearVelocity(b2Vec2(-5, 0));
		}
		if (edge->contact->GetFixtureB()->GetBody() == pitB)
		{
			if (bowLightPic->getOpacity() == 155)
			{
				pitFire->setVisible(false);
				enemyPit->setOpacity(200);
				world->DestroyBody(pitB);
				world->DestroyBody(ratPushB);
				world->DestroyBody(ghostPitB);
				killedGhostPit = true;
				audioLv3->playEffect("scary1.wav");
				removeItemLv3(3);
				bowPic->setOpacity(0);
				audioLv3->playBackgroundMusic("ambience.wav",true);

			}
			else
			{
				audioLv3->stopAllEffects();
				audioLv3->pauseBackgroundMusic();
				removeItemLv3(1);
				removeItemLv3(2);
				removeItemLv3(3);
				removeItemLv3(5);
				auto scene = NFMenu::createScene();
				Director::getInstance()->replaceScene(TransitionFade::create(0.5, scene, Color3B(0, 0, 0)));
			}
		}
		if (edge->contact->GetFixtureB()->GetBody() == ratB)
		{
			if (id == 4)
			{
				rat->setScaleX(-1);
				world->DestroyBody(ratB);
				ratDied = true;
				removeItemLv3(4);
				cheesePic->setOpacity(0);
				audioLv3->playBackgroundMusic("ambience.wav",true);
			}
			else
			{
				audioLv3->stopAllEffects();
				audioLv3->pauseBackgroundMusic();
				removeItemLv3(1);
				removeItemLv3(2);
				removeItemLv3(3);
				removeItemLv3(4);
				auto scene = NFMenu::createScene();
				Director::getInstance()->replaceScene(TransitionFade::create(0.5, scene, Color3B(0, 0, 0)));
			}
		}
		if (edge->contact->GetFixtureB()->GetBody() == changerB)
		{
			level3Pic->setOpacity(0);
			audioLv3->playEffect("tele.wav");
			addBoxBodyForMagicWall(gateWall);
			world->DestroyBody(changerB);
			enemy->setOpacity(255);
			ghost->setOpacity(255);
			audioLv3->playEffect("give.wav", true);
			end = true;
		}
		if (edge->contact->GetFixtureB()->GetBody() == ghostB && id == 6)
		{
			
			audioLv3->stopAllEffects();
			audioLv3->playEffect("girl1.wav");
			pickedGhost = true;
			if (pickedGhost)
			{
				world->DestroyBody(spriteBody);
				world->DestroyBody(enemyB);
				world->DestroyBody(ghostB);
				enemy->setOpacity(0);
				space->setOpacity(200);
				auto action2 = FadeIn::create(4);
				audioLv3->playEffect("girl1.wav");
				hung->runAction(action2);
				
			}

		}
		if (edge->contact->GetFixtureB()->GetBody() == enemyB && id ==6)
		{
			if (end)
			{
				audioLv3->stopAllEffects();
				audioLv3->playEffect("save.wav");
				pickedEnemy = true;
				if (pickedEnemy)
				{
					world->DestroyBody(spriteBody);
					world->DestroyBody(enemyB);
					world->DestroyBody(ghostB);
					enemy->setOpacity(0);
					ghost->setOpacity(0);
					savedEnemy->setOpacity(255);
					space->setOpacity(200);

				}
			}

		}
		if (edge->contact->GetFixtureB()->GetBody()->GetUserData() == note1)
		{
			if (charUsing && charMovingLeft == false && charMovingRight == false)
			{
				note1Pic->setOpacity(255);
			}
			else
				note1Pic->setOpacity(0);

		}
		
		if (edge->contact->GetFixtureB()->GetBody()->GetUserData() == note2)
		{
			if (charUsing && charMovingLeft == false && charMovingRight == false)
			{
				note2Pic->setOpacity(255);
			}
			else
				note2Pic->setOpacity(0);

		}
		

		edge = edge->next;
	}
}

void level3::draw(cocos2d::Renderer * renderer, const cocos2d::Mat4 & transform, uint32_t flags)
{
	kmGLPushMatrix();
	world->DrawDebugData();
	kmGLPopMatrix();
}

void level3::update(float)
{
	tick(); // runs physics and collissions

	this->runAction(CCFollow::create(sprite, Rect(0, 0, 3000, 1200))); // camera follows player 

	displayInv();

	if (invR)
	{
		shiftInventoryRightLv3();
		invR = false;
	}

	if (invL)
	{
		shiftInventoryLeftLv3();
		invL = false;
	}

	if (killedGhostPit)
	{
		auto action = FadeOut::create(2);
		auto action2 = MoveBy::create(3, Vec2(100, 50));
		enemyPit->runAction(action);
		enemyPit->runAction(action2);
		ghostPit->setPosition(enemyPit->getPosition());
		ghostPit->runAction(action);
	}
	if (ratDied)
	{
		auto action = FadeOut::create(2);
		auto action2 = MoveBy::create(2, Vec2(100, 0));
		auto action3 = RotateBy::create(2.0f, 0);
		auto seq = Sequence::create(action2,action3, action, nullptr);
		
		rat->runAction(seq);
	}
	if (pickedGhost)
	{
		idleAnim->setOpacity(0);
		walkAnim->setOpacity(0);
	}
	if (pickedGhost && charSwing)
	{
		destroyLua = true;
		pickedGhost = false;
		audioLv3->stopAllEffects();
		audioLv3->pauseBackgroundMusic();
		removeItemLv3(1);
		removeItemLv3(2);
		removeItemLv3(6);
		space->setOpacity(0);
		auto scene = NFMenu::createScene();
		Director::getInstance()->replaceScene(TransitionFade::create(0.5, scene, Color3B(0, 0, 0)));

	}
	if (pickedEnemy && charSwing)
	{
		destroyLua = true;
		pickedEnemy = false;
		audioLv3->stopAllEffects();
		audioLv3->pauseBackgroundMusic();
		removeItemLv3(1);
		removeItemLv3(2);
		removeItemLv3(6);
		space->setOpacity(0);
		auto scene = NFMenu::createScene();
		Director::getInstance()->replaceScene(TransitionFade::create(0.5, scene, Color3B(0, 0, 0)));

	}
	if (spriteBody != NULL)
	{
		if (!((charMovingLeft && charMovingRight) || (!charMovingLeft && !charMovingRight))) {

			if (charMovingLeft) {
				//audio->playEffect("footsteps.wav");
				spriteBody->SetLinearVelocity(b2Vec2(-4.5, 0));
				walkAnim->setOpacity(255);
				walkAnim->setScaleX(1);
				idleAnim->setOpacity(0);
				idleAnim->setScaleX(1);
				sprite->setOpacity(0);
				movedL = true;
				movedR = false;
			}
			if (charMovingRight) {
				//audio->playEffect("footsteps.wav");
				spriteBody->SetLinearVelocity(b2Vec2(4.5, 0));
				idleAnim->setOpacity(0);
				idleAnim->setScaleX(-1);
				sprite->setOpacity(0);
				walkAnim->setOpacity(255);
				walkAnim->setScaleX(-1);
				movedL = false;
				movedR = true;

			}
		}
		else
		{
			spriteBody->SetLinearVelocity(b2Vec2(0, 0));
			walkAnim->setOpacity(0);
			sprite->setOpacity(0);

			if (movedL)
			{
				idleAnim->setOpacity(255);
				idleAnim->setScaleX(1);
			}
			if (movedR)
			{
				idleAnim->setOpacity(255);
				idleAnim->setScaleX(-1);
			}
		}
	}
}

bool level3::init()
{
	if (!Layer::init())
	{
		return false;
	}

	//---Creates World
	b2Vec2 gravity = b2Vec2(0.0f, -9.0f);
	world = new b2World(gravity);
	world->SetAllowSleeping(false);
	world->SetContinuousPhysics(true);
	contactListener = new b2ContactListener();
	world->SetContactListener(contactListener);

	auto rootNode = CSLoader::createNode("level3.csb");
	audioLv3->playBackgroundMusic("ambience.wav", true);

	//---world

	//--------------WALLS
	floor = rootNode->getChildByName("floor");
	leftWall = rootNode->getChildByName("leftWall");
	rightWall = rootNode->getChildByName("rightWall");
	ceiling = rootNode->getChildByName("ceiling");
	ceiling2 = rootNode->getChildByName("ceiling2");
	leftWall2 = rootNode->getChildByName("leftWall2");
	middleWall = rootNode->getChildByName("middleWall");
	middleWall2 = rootNode->getChildByName("middleWall2");
	gateWall = rootNode->getChildByName("gateWall");

	addBoxBodyForStaticWall(floor, floorB);
	addBoxBodyForStaticWall(leftWall, leftWallB);
	addBoxBodyForStaticWall(rightWall, rightWallB);
	addBoxBodyForStaticWall(ceiling, ceilingB);
	addBoxBodyForStaticWall(ceiling2, ceiling2B);
	addBoxBodyForStaticWall(leftWall2, leftWall2B);
	addBoxBodyForStaticWall(middleWall, middleWallB);
	addBoxBodyForStaticWall(middleWall2, middleWall2B);

	addBoxBodyForMagicWall(gateWall);
	
	//----------------------WALLS END

	//----PLAYER
	sprite = rootNode->getChildByName("player");
	idleAnim = rootNode->getChildByName("playerIdle");
	walkAnim = rootNode->getChildByName("playerWalk");

	cocostudio::timeline::ActionTimeline *timeLine = CSLoader::createTimeline("detectiveIdle.csb");
	timeLine->retain(); //released later on
	idleAnim->runAction(timeLine);
	timeLine->gotoFrameAndPlay(0, 33, true);

	cocostudio::timeline::ActionTimeline *timeLine2 = CSLoader::createTimeline("detectiveWalk.csb");
	timeLine2->retain(); //released later on
	walkAnim->runAction(timeLine2);
	timeLine2->gotoFrameAndPlay(0, 19, true);

	addBoxBodyForSprite(sprite);

	//-------------------
	cheese = rootNode->getChildByName("cheese");
	addBoxBodyForCheese(cheese);
	poison = rootNode->getChildByName("poison");
	addBoxBodyForPoison(poison);
	gem = rootNode->getChildByName("gem");
	addBoxBodyForGem(gem);
	note1 = rootNode->getChildByName("note1");
	addBoxBodyForNote(note1,note1B);
	note2 = rootNode->getChildByName("note2");
	addBoxBodyForNote(note2, note2B);

	
	downArrowToPit = rootNode->getChildByName("downArrowToPit");
	downArrowToPit->setOpacity(0);
	addBoxBodyForDownArrowToPit(downArrowToPit);

	upArrowFromPit = rootNode->getChildByName("upArrowFromPit");
	upArrowFromPit->setOpacity(0);
	addBoxBodyForDownArrowToPit(upArrowFromPit);

	upArrowToRat = rootNode->getChildByName("upArrowToRat");
	upArrowToRat->setOpacity(0);
	addBoxBodyForDownArrowToPit(upArrowToRat);

	downArrowFromRat = rootNode->getChildByName("downArrowFromRat");
	downArrowFromRat->setOpacity(0);
	addBoxBodyForDownArrowToPit(downArrowFromRat);

	

	//----INV
	crobarPic = cocos2d::Sprite::create("crobar.png");
	axePic = cocos2d::Sprite::create("axe.png");
	cheesePic = cocos2d::Sprite::create("cheese.png");
	gemPic = cocos2d::Sprite::create("gem.png");
	poisonPic = cocos2d::Sprite::create("poison.png");
	bowPic = cocos2d::Sprite::create("bow.png");
	bowLightPic = cocos2d::Sprite::create("bowLight.png");
	note1Pic = cocos2d::Sprite::create("note1level3.png");
	note2Pic = cocos2d::Sprite::create("note3level3.png");
	
	

	addItemLv3(1);
	addItemLv3(2);
	addItemLv3(3);

	
	crobarPic->setOpacity(0);
	axePic->setOpacity(0);
	cheesePic->setOpacity(0);
	gemPic->setOpacity(0);
	poisonPic->setOpacity(0);
	bowPic->setOpacity(0);
	bowLightPic->setOpacity(0);
	note1Pic->setOpacity(0);
	note2Pic->setOpacity(0);
	//-------PIT
	ghostPit = rootNode->getChildByName("ghostPit");
	addBoxBodyForPitGhost(ghostPit);
	ghostPitPosition = ghostPitB->GetPosition();
	ratPush = rootNode->getChildByName("ratPush");
	addBoxBodyForRatPush(ratPush);
	pit = rootNode->getChildByName("pit");
	addBoxBodyForPit(pit);
	enemyPit = rootNode->getChildByName("enemyPit");
	enemyPit->setOpacity(0);
	pitFire = rootNode->getChildByName("pitFire");
	
	//RAT ROOM
	rat = rootNode->getChildByName("rat");
	addBoxBodyForRat(rat);
	ratPosition = ratB->GetPosition();
	//enemy = rootNode->getChildByName("enemy");
	//addBoxBodyForEnemy(enemy);
	//finalleee
	enemy = rootNode->getChildByName("enemy");
	addBoxBodyForEnemy(enemy);
	ghost = rootNode->getChildByName("ghost");
	addBoxBodyForGhost(ghost);
	changer = rootNode->getChildByName("changer");
	addBoxBodyForChanger(changer);
	level3Pic = rootNode->getChildByName("level3");
	hung = rootNode->getChildByName("hung");

	savedEnemy = rootNode->getChildByName("savedEnemy");
	space = rootNode->getChildByName("space");

	rootNode->setOpacity(255);

	this->addChild(rootNode);
	this->addChild(crobarPic);
	this->addChild(axePic);
	this->addChild(gemPic);
	this->addChild(cheesePic);
	this->addChild(poisonPic);
	this->addChild(bowPic);
	this->addChild(bowLightPic);
	this->addChild(note1Pic);
	this->addChild(note2Pic);


	//------------------------DEBUGGER
	b2Draw *m_debugDraw = new  GLESDebugDraw(PTM_RATIO);
	uint32 flags = 0;
	flags += b2Draw::e_shapeBit;
	flags += b2Draw::e_jointBit;
	flags += b2Draw::e_aabbBit;
	flags += b2Draw::e_pairBit;
	flags += b2Draw::e_centerOfMassBit;
	m_debugDraw->SetFlags(flags);
	world->SetDebugDraw(m_debugDraw);
	//-------------------------------DEBUGGER END

	//------------------------MOUSE
	auto eventListener = EventListenerKeyboard::create();

	eventListener->onKeyPressed = [this](EventKeyboard::KeyCode keyCode, Event* event) {

		switch (keyCode) {
		case EventKeyboard::KeyCode::KEY_A:
			charMovingLeft = true;
			break;
		case EventKeyboard::KeyCode::KEY_D:
			charMovingRight = true;
			break;
		case EventKeyboard::KeyCode::KEY_W:
			charMovingUp = true;
			break;
		case EventKeyboard::KeyCode::KEY_S:
			charMovingDown = true;
			break;
		case EventKeyboard::KeyCode::KEY_E:
			charUsing = true;
			break;
		case EventKeyboard::KeyCode::KEY_LEFT_SHIFT:
			charRun = true;
			break;
		case EventKeyboard::KeyCode::KEY_SPACE:
			charSwing = true;
			break;
		case EventKeyboard::KeyCode::KEY_Z:
			invL = true;
			break;
		case EventKeyboard::KeyCode::KEY_X:
			invR = true;
			break;

		}

	};

	eventListener->onKeyReleased = [this](EventKeyboard::KeyCode keyCode, Event* event) {

		switch (keyCode) {
		case EventKeyboard::KeyCode::KEY_A:
			charMovingLeft = false;
			break;
		case EventKeyboard::KeyCode::KEY_D:
			charMovingRight = false;
			break;
		case EventKeyboard::KeyCode::KEY_W:
			charMovingUp = false;
			break;
		case EventKeyboard::KeyCode::KEY_S:
			charMovingDown = false;
			break;
		case EventKeyboard::KeyCode::KEY_E:
			charUsing = false;
			break;
		case EventKeyboard::KeyCode::KEY_LEFT_SHIFT:
			charRun = false;
			break;
		case EventKeyboard::KeyCode::KEY_SPACE:
			charSwing = false;
			break;
		}
	};
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, sprite);
	//----------------------MOUSE END


	this->scheduleUpdate();
	return true;
}