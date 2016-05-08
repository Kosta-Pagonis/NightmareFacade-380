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


using namespace cocostudio::timeline;
using namespace LuaPlus;
USING_NS_CC;
#define PTM_RATIO 30

auto audioLv2 = CocosDenshion::SimpleAudioEngine::getInstance();
LuaState* luaPStateLv2 = LuaState::Create();
int resultLv2 = luaPStateLv2->DoFile("stats.lua");
LuaFunction<int> getHeldItemLv2 = luaPStateLv2->GetGlobal("getHeldItem");
LuaFunction<void> shiftInventoryRightLv2 = luaPStateLv2->GetGlobal("shiftInventoryRight");
LuaFunction<void> shiftInventoryLeftLv2 = luaPStateLv2->GetGlobal("shiftInventoryLeft");
LuaFunction<void> addItemLv2 = luaPStateLv2->GetGlobal("addItem");
LuaFunction<void> removeItemLv2 = luaPStateLv2->GetGlobal("removeItem");
LuaFunction<void> setHeldItemLv2 = luaPStateLv2->GetGlobal("setHeldItem");

Scene* level2::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = level2::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

void level2::addBoxBodyForSprite(Node * sprite)
{
	sprite->setAnchorPoint(Vec2(.5, .5));
	b2BodyDef spriteBodyDef;
	spriteBodyDef.type = b2_dynamicBody;
	spriteBodyDef.position.Set(sprite->getPositionX() / PTM_RATIO,
		sprite->getPositionY() / PTM_RATIO);
	spriteBodyDef.userData = sprite;
	spriteBody = world->CreateBody(&spriteBodyDef);

	b2PolygonShape spriteShape;
	spriteShape.SetAsBox(sprite->getContentSize().width / PTM_RATIO / 2,
		sprite->getContentSize().height / PTM_RATIO / 2);
	b2FixtureDef spriteShapeDef;
	spriteShapeDef.shape = &spriteShape;
	spriteShapeDef.density = 1.0;
	spriteShapeDef.isSensor = false;
	spriteBody->CreateFixture(&spriteShapeDef);
}

void level2::addBoxBodyForStaticWall(Node * sprite, b2Body * body)
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
void level2::addBoxBodyForGateWall(Node * sprite)
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

//-------Room 1
void level2::addBoxBodyForLeverBottom(Node * sprite)
{
	sprite->setAnchorPoint(Vec2(.5, .5));
	b2BodyDef spriteBodyDef;
	spriteBodyDef.type = b2_staticBody;
	spriteBodyDef.position.Set(sprite->getPositionX() / PTM_RATIO,
		sprite->getPositionY() / PTM_RATIO);
	spriteBodyDef.userData = sprite;
	leverBottomB = world->CreateBody(&spriteBodyDef);

	b2PolygonShape spriteShape;
	spriteShape.SetAsBox(sprite->getContentSize().width / PTM_RATIO / 2 * sprite->getScaleX(),
		sprite->getContentSize().height / PTM_RATIO / 2 * sprite->getScaleY());
	b2FixtureDef spriteShapeDef;
	spriteShapeDef.shape = &spriteShape;
	spriteShapeDef.density = 1.0;
	spriteShapeDef.isSensor = true;
	leverBottomB->CreateFixture(&spriteShapeDef);
}
void level2::addBoxBodyForDownArrowBoiler(Node * sprite)
{
	sprite->setAnchorPoint(Vec2(.5, .5));
	b2BodyDef spriteBodyDef;
	spriteBodyDef.type = b2_staticBody;
	spriteBodyDef.position.Set(sprite->getPositionX() / PTM_RATIO,
		sprite->getPositionY() / PTM_RATIO);
	spriteBodyDef.userData = sprite;
	downArrowBoilerB = world->CreateBody(&spriteBodyDef);

	b2PolygonShape spriteShape;
	spriteShape.SetAsBox(sprite->getContentSize().width / PTM_RATIO / 2 * sprite->getScaleX(),
		sprite->getContentSize().height / PTM_RATIO / 2 * sprite->getScaleY());
	b2FixtureDef spriteShapeDef;
	spriteShapeDef.shape = &spriteShape;
	spriteShapeDef.density = 1.0;
	spriteShapeDef.isSensor = true;
	downArrowBoilerB->CreateFixture(&spriteShapeDef);
}
//-------Room 2
void level2::addBoxBodyForLeverBase(Node * sprite)
{
	sprite->setAnchorPoint(Vec2(.5, .5));
	b2BodyDef spriteBodyDef;
	spriteBodyDef.type = b2_staticBody;
	spriteBodyDef.position.Set(sprite->getPositionX() / PTM_RATIO,
		sprite->getPositionY() / PTM_RATIO);
	spriteBodyDef.userData = sprite;
	leverBaseB = world->CreateBody(&spriteBodyDef);

	b2PolygonShape spriteShape;
	spriteShape.SetAsBox(sprite->getContentSize().width / PTM_RATIO / 2 * sprite->getScaleX(),
		sprite->getContentSize().height / PTM_RATIO / 2 * sprite->getScaleY());
	b2FixtureDef spriteShapeDef;
	spriteShapeDef.shape = &spriteShape;
	spriteShapeDef.density = 1.0;
	spriteShapeDef.isSensor = true;
	leverBaseB->CreateFixture(&spriteShapeDef);
}
void level2::addBoxBodyForUpArrowLibrary(Node * sprite)
{
	sprite->setAnchorPoint(Vec2(.5, .5));
	b2BodyDef spriteBodyDef;
	spriteBodyDef.type = b2_staticBody;
	spriteBodyDef.position.Set(sprite->getPositionX() / PTM_RATIO,
		sprite->getPositionY() / PTM_RATIO);
	spriteBodyDef.userData = sprite;
	upArrowLibraryB = world->CreateBody(&spriteBodyDef);

	b2PolygonShape spriteShape;
	spriteShape.SetAsBox(sprite->getContentSize().width / PTM_RATIO / 2 * sprite->getScaleX(),
		sprite->getContentSize().height / PTM_RATIO / 2 * sprite->getScaleY());
	b2FixtureDef spriteShapeDef;
	spriteShapeDef.shape = &spriteShape;
	spriteShapeDef.density = 1.0;
	spriteShapeDef.isSensor = true;
	upArrowLibraryB->CreateFixture(&spriteShapeDef);
}
void level2::addBoxBodyForBucket(Node * sprite)
{
	sprite->setAnchorPoint(Vec2(.5, .5));
	b2BodyDef spriteBodyDef;
	spriteBodyDef.type = b2_staticBody;
	spriteBodyDef.position.Set(sprite->getPositionX() / PTM_RATIO,
		sprite->getPositionY() / PTM_RATIO);
	spriteBodyDef.userData = sprite;
	bucketB = world->CreateBody(&spriteBodyDef);

	b2PolygonShape spriteShape;
	spriteShape.SetAsBox(sprite->getContentSize().width / PTM_RATIO / 2 * sprite->getScaleX(),
		sprite->getContentSize().height / PTM_RATIO / 2 * sprite->getScaleY());
	b2FixtureDef spriteShapeDef;
	spriteShapeDef.shape = &spriteShape;
	spriteShapeDef.density = 1.0;
	spriteShapeDef.isSensor = true;
	bucketB->CreateFixture(&spriteShapeDef);
}
//-------Boiler Room
void level2::addBoxBodyForStove(Node * sprite)
{
	sprite->setAnchorPoint(Vec2(.5, .5));
	b2BodyDef spriteBodyDef;
	spriteBodyDef.type = b2_staticBody;
	spriteBodyDef.position.Set(sprite->getPositionX() / PTM_RATIO,
		sprite->getPositionY() / PTM_RATIO);
	spriteBodyDef.userData = sprite;
	stoveB = world->CreateBody(&spriteBodyDef);

	b2PolygonShape spriteShape;
	spriteShape.SetAsBox(sprite->getContentSize().width / PTM_RATIO / 2 * sprite->getScaleX(),
		sprite->getContentSize().height / PTM_RATIO / 2 * sprite->getScaleY());
	b2FixtureDef spriteShapeDef;
	spriteShapeDef.shape = &spriteShape;
	spriteShapeDef.density = 1.0;
	spriteShapeDef.isSensor = true;
	stoveB->CreateFixture(&spriteShapeDef);
}
void level2::addBoxBodyForLeverTop(Node * sprite)
{
	sprite->setAnchorPoint(Vec2(.5, .5));
	b2BodyDef spriteBodyDef;
	spriteBodyDef.type = b2_staticBody;
	spriteBodyDef.position.Set(sprite->getPositionX() / PTM_RATIO,
		sprite->getPositionY() / PTM_RATIO);
	spriteBodyDef.userData = sprite;
	leverTopB = world->CreateBody(&spriteBodyDef);

	b2PolygonShape spriteShape;
	spriteShape.SetAsBox(sprite->getContentSize().width / PTM_RATIO / 2 * sprite->getScaleX(),
		sprite->getContentSize().height / PTM_RATIO / 2 * sprite->getScaleY());
	b2FixtureDef spriteShapeDef;
	spriteShapeDef.shape = &spriteShape;
	spriteShapeDef.density = 1.0;
	spriteShapeDef.isSensor = true;
	leverTopB->CreateFixture(&spriteShapeDef);
}
void level2::addBoxBodyForUpArrowBoiler(Node * sprite)
{
	sprite->setAnchorPoint(Vec2(.5, .5));
	b2BodyDef spriteBodyDef;
	spriteBodyDef.type = b2_staticBody;
	spriteBodyDef.position.Set(sprite->getPositionX() / PTM_RATIO,
		sprite->getPositionY() / PTM_RATIO);
	spriteBodyDef.userData = sprite;
	upArrowBoilerB = world->CreateBody(&spriteBodyDef);

	b2PolygonShape spriteShape;
	spriteShape.SetAsBox(sprite->getContentSize().width / PTM_RATIO / 2 * sprite->getScaleX(),
		sprite->getContentSize().height / PTM_RATIO / 2 * sprite->getScaleY());
	b2FixtureDef spriteShapeDef;
	spriteShapeDef.shape = &spriteShape;
	spriteShapeDef.density = 1.0;
	spriteShapeDef.isSensor = true;
	upArrowBoilerB->CreateFixture(&spriteShapeDef);
}

//---Library

void level2::addBoxBodyForBookshelf(Node * sprite)
{
	sprite->setAnchorPoint(Vec2(.5, .5));
	b2BodyDef spriteBodyDef;
	spriteBodyDef.type = b2_dynamicBody;
	spriteBodyDef.position.Set(sprite->getPositionX() / PTM_RATIO,
		sprite->getPositionY() / PTM_RATIO);
	spriteBodyDef.userData = sprite;
	bookshelfB = world->CreateBody(&spriteBodyDef);

	b2PolygonShape spriteShape;
	spriteShape.SetAsBox(sprite->getContentSize().width / PTM_RATIO / 2 * sprite->getScaleX(),
		sprite->getContentSize().height / PTM_RATIO / 2 * sprite->getScaleY());
	b2FixtureDef spriteShapeDef;
	spriteShapeDef.shape = &spriteShape;
	spriteShapeDef.density = 15.0;
	spriteShapeDef.isSensor = false;
	bookshelfB->CreateFixture(&spriteShapeDef);
}
void level2::addBoxBodyForUpArrowSecretRoom(Node * sprite)
{
	sprite->setAnchorPoint(Vec2(.5, .5));
	b2BodyDef spriteBodyDef;
	spriteBodyDef.type = b2_staticBody;
	spriteBodyDef.position.Set(sprite->getPositionX() / PTM_RATIO,
		sprite->getPositionY() / PTM_RATIO);
	spriteBodyDef.userData = sprite;
	upArrowSecretRoomB = world->CreateBody(&spriteBodyDef);

	b2PolygonShape spriteShape;
	spriteShape.SetAsBox(sprite->getContentSize().width / PTM_RATIO / 2 * sprite->getScaleX(),
		sprite->getContentSize().height / PTM_RATIO / 2 * sprite->getScaleY());
	b2FixtureDef spriteShapeDef;
	spriteShapeDef.shape = &spriteShape;
	spriteShapeDef.density = 1.0;
	spriteShapeDef.isSensor = true;
	upArrowSecretRoomB->CreateFixture(&spriteShapeDef);
}
void level2::addBoxBodyForDownArrowLibrary(Node * sprite)
{
	sprite->setAnchorPoint(Vec2(.5, .5));
	b2BodyDef spriteBodyDef;
	spriteBodyDef.type = b2_staticBody;
	spriteBodyDef.position.Set(sprite->getPositionX() / PTM_RATIO,
		sprite->getPositionY() / PTM_RATIO);
	spriteBodyDef.userData = sprite;
	downArrowLibraryB = world->CreateBody(&spriteBodyDef);

	b2PolygonShape spriteShape;
	spriteShape.SetAsBox(sprite->getContentSize().width / PTM_RATIO / 2 * sprite->getScaleX(),
		sprite->getContentSize().height / PTM_RATIO / 2 * sprite->getScaleY());
	b2FixtureDef spriteShapeDef;
	spriteShapeDef.shape = &spriteShape;
	spriteShapeDef.density = 1.0;
	spriteShapeDef.isSensor = true;
	downArrowLibraryB->CreateFixture(&spriteShapeDef);
}
void level2::addBoxBodyForBench(Node * sprite)
{
	sprite->setAnchorPoint(Vec2(.5, .5));
	b2BodyDef spriteBodyDef;
	spriteBodyDef.type = b2_staticBody;
	spriteBodyDef.position.Set(sprite->getPositionX() / PTM_RATIO,
		sprite->getPositionY() / PTM_RATIO);
	spriteBodyDef.userData = sprite;
	workBenchB = world->CreateBody(&spriteBodyDef);

	b2PolygonShape spriteShape;
	spriteShape.SetAsBox(sprite->getContentSize().width / PTM_RATIO / 2 * sprite->getScaleX(),
		sprite->getContentSize().height / PTM_RATIO / 2 * sprite->getScaleY());
	b2FixtureDef spriteShapeDef;
	spriteShapeDef.shape = &spriteShape;
	spriteShapeDef.density = 1.0;
	spriteShapeDef.isSensor = true;
	workBenchB->CreateFixture(&spriteShapeDef);
}
//---- Secret Room

void level2::addBoxBodyForDownArrowSecretRoom(Node * sprite)
{
	sprite->setAnchorPoint(Vec2(.5, .5));
	b2BodyDef spriteBodyDef;
	spriteBodyDef.type = b2_staticBody;
	spriteBodyDef.position.Set(sprite->getPositionX() / PTM_RATIO,
		sprite->getPositionY() / PTM_RATIO);
	spriteBodyDef.userData = sprite;
	downArrowSecretRoomB = world->CreateBody(&spriteBodyDef);

	b2PolygonShape spriteShape;
	spriteShape.SetAsBox(sprite->getContentSize().width / PTM_RATIO / 2 * sprite->getScaleX(),
		sprite->getContentSize().height / PTM_RATIO / 2 * sprite->getScaleY());
	b2FixtureDef spriteShapeDef;
	spriteShapeDef.shape = &spriteShape;
	spriteShapeDef.density = 1.0;
	spriteShapeDef.isSensor = true;
	downArrowSecretRoomB->CreateFixture(&spriteShapeDef);
}
void level2::addBoxBodyForWaterBarrel(Node * sprite)
{
	sprite->setAnchorPoint(Vec2(.5, .5));
	b2BodyDef spriteBodyDef;
	spriteBodyDef.type = b2_staticBody;
	spriteBodyDef.position.Set(sprite->getPositionX() / PTM_RATIO,
		sprite->getPositionY() / PTM_RATIO);
	spriteBodyDef.userData = sprite;
	waterBarrelB = world->CreateBody(&spriteBodyDef);
	b2PolygonShape spriteShape;
	spriteShape.SetAsBox(sprite->getContentSize().width / PTM_RATIO / 2 * sprite->getScaleX(),
		sprite->getContentSize().height / PTM_RATIO / 2 * sprite->getScaleY());
	b2FixtureDef spriteShapeDef;
	spriteShapeDef.shape = &spriteShape;
	spriteShapeDef.density = 1.0;
	spriteShapeDef.isSensor = true;
	waterBarrelB->CreateFixture(&spriteShapeDef);
}
void level2::addBoxBodyForEmptyBox(Node * sprite)
{
	sprite->setAnchorPoint(Vec2(.5, .5));
	b2BodyDef spriteBodyDef;
	spriteBodyDef.type = b2_staticBody;
	spriteBodyDef.position.Set(sprite->getPositionX() / PTM_RATIO,
		sprite->getPositionY() / PTM_RATIO);
	spriteBodyDef.userData = sprite;
	emptyBoxB = world->CreateBody(&spriteBodyDef);
	b2PolygonShape spriteShape;
	spriteShape.SetAsBox(sprite->getContentSize().width / PTM_RATIO / 2 * sprite->getScaleX(),
		sprite->getContentSize().height / PTM_RATIO / 2 * sprite->getScaleY());
	b2FixtureDef spriteShapeDef;
	spriteShapeDef.shape = &spriteShape;
	spriteShapeDef.density = 1.0;
	spriteShapeDef.isSensor = true;
	emptyBoxB->CreateFixture(&spriteShapeDef);
}
void level2::addBoxBodyForLeverBox(Node * sprite)
{
	sprite->setAnchorPoint(Vec2(.5, .5));
	b2BodyDef spriteBodyDef;
	spriteBodyDef.type = b2_staticBody;
	spriteBodyDef.position.Set(sprite->getPositionX() / PTM_RATIO,
		sprite->getPositionY() / PTM_RATIO);
	spriteBodyDef.userData = sprite;
	leverBoxB = world->CreateBody(&spriteBodyDef);

	b2PolygonShape spriteShape;
	spriteShape.SetAsBox(sprite->getContentSize().width / PTM_RATIO / 2 * sprite->getScaleX(),
		sprite->getContentSize().height / PTM_RATIO / 2 * sprite->getScaleY());
	b2FixtureDef spriteShapeDef;
	spriteShapeDef.shape = &spriteShape;
	spriteShapeDef.density = 1.0;
	spriteShapeDef.isSensor = true;
	leverBoxB->CreateFixture(&spriteShapeDef);
}
void level2::addBoxBodyForEvilBox(Node * sprite)
{
	sprite->setAnchorPoint(Vec2(.5, .5));
	b2BodyDef spriteBodyDef;
	spriteBodyDef.type = b2_dynamicBody;
	spriteBodyDef.gravityScale = 0;
	spriteBodyDef.position.Set(sprite->getPositionX() / PTM_RATIO,
		sprite->getPositionY() / PTM_RATIO);
	spriteBodyDef.userData = sprite;
	evilBoxB = world->CreateBody(&spriteBodyDef);

	b2PolygonShape spriteShape;
	spriteShape.SetAsBox(sprite->getContentSize().width / PTM_RATIO / 2 * sprite->getScaleX(),
		sprite->getContentSize().height / PTM_RATIO / 2 * sprite->getScaleY());
	b2FixtureDef spriteShapeDef;
	spriteShapeDef.shape = &spriteShape;
	spriteShapeDef.density = 1.0;
	spriteShapeDef.isSensor = true;
	evilBoxB->CreateFixture(&spriteShapeDef);
}
void level2::addBoxBodyForLeverMiddle(Node * sprite)
{
	sprite->setAnchorPoint(Vec2(.5, .5));
	b2BodyDef spriteBodyDef;
	spriteBodyDef.type = b2_staticBody;
	spriteBodyDef.position.Set(sprite->getPositionX() / PTM_RATIO,
		sprite->getPositionY() / PTM_RATIO);
	spriteBodyDef.userData = sprite;
	leverMiddleB = world->CreateBody(&spriteBodyDef);

	b2PolygonShape spriteShape;
	spriteShape.SetAsBox(sprite->getContentSize().width / PTM_RATIO / 2 * sprite->getScaleX(),
		sprite->getContentSize().height / PTM_RATIO / 2 * sprite->getScaleY());
	b2FixtureDef spriteShapeDef;
	spriteShapeDef.shape = &spriteShape;
	spriteShapeDef.density = 1.0;
	spriteShapeDef.isSensor = true;
	leverMiddleB->CreateFixture(&spriteShapeDef);
}
void level2::addBoxBodyForBow(Node * sprite)
{
	sprite->setAnchorPoint(Vec2(.5, .5));
	b2BodyDef spriteBodyDef;
	spriteBodyDef.type = b2_staticBody;
	spriteBodyDef.position.Set(sprite->getPositionX() / PTM_RATIO,
		sprite->getPositionY() / PTM_RATIO);
	spriteBodyDef.userData = sprite;
	bowB = world->CreateBody(&spriteBodyDef);

	b2PolygonShape spriteShape;
	spriteShape.SetAsBox(sprite->getContentSize().width / PTM_RATIO / 2 * sprite->getScaleX(),
		sprite->getContentSize().height / PTM_RATIO / 2 * sprite->getScaleY());
	b2FixtureDef spriteShapeDef;
	spriteShapeDef.shape = &spriteShape;
	spriteShapeDef.density = 1.0;
	spriteShapeDef.isSensor = true;
	bowB->CreateFixture(&spriteShapeDef);
}
 //------FINALEE

void level2::addBoxBodyForGhost(Node * sprite)
{
	sprite->setAnchorPoint(Vec2(.5, .5));
	b2BodyDef spriteBodyDef;
	spriteBodyDef.type = b2_dynamicBody;
	spriteBodyDef.gravityScale = 0;
	spriteBodyDef.position.Set(sprite->getPositionX() / PTM_RATIO,
		sprite->getPositionY() / PTM_RATIO);
	spriteBodyDef.userData = sprite;
	ghostB = world->CreateBody(&spriteBodyDef);

	b2PolygonShape spriteShape;
	spriteShape.SetAsBox(sprite->getContentSize().width / PTM_RATIO / 2 * sprite->getScaleX(),
		sprite->getContentSize().height / PTM_RATIO / 2 * sprite->getScaleY());
	b2FixtureDef spriteShapeDef;
	spriteShapeDef.shape = &spriteShape;
	spriteShapeDef.density = 1.0;
	spriteShapeDef.isSensor = true;
	ghostB->CreateFixture(&spriteShapeDef);
}
void level2::addBoxBodyForEnemy(Node * sprite)
{
	sprite->setAnchorPoint(Vec2(.5, .5));
	b2BodyDef spriteBodyDef;
	spriteBodyDef.type = b2_staticBody;
	spriteBodyDef.position.Set(sprite->getPositionX() / PTM_RATIO,
		sprite->getPositionY() / PTM_RATIO);
	spriteBodyDef.userData = sprite;
	enemyB = world->CreateBody(&spriteBodyDef);

	b2PolygonShape spriteShape;
	spriteShape.SetAsBox(sprite->getContentSize().width / PTM_RATIO /4 * sprite->getScaleX(),
		sprite->getContentSize().height / PTM_RATIO / 4* sprite->getScaleY());
	b2FixtureDef spriteShapeDef;
	spriteShapeDef.shape = &spriteShape;
	spriteShapeDef.density = 1.0;
	spriteShapeDef.isSensor = true;
	enemyB->CreateFixture(&spriteShapeDef);
}
void level2::addBoxBodyForPower(Node * sprite)
{
	sprite->setAnchorPoint(Vec2(.5, .5));
	b2BodyDef spriteBodyDef;
	spriteBodyDef.type = b2_dynamicBody;
	spriteBodyDef.gravityScale = 0;
	spriteBodyDef.position.Set(sprite->getPositionX() / PTM_RATIO,
		sprite->getPositionY() / PTM_RATIO);
	spriteBodyDef.userData = sprite;
	powerB = world->CreateBody(&spriteBodyDef);

	b2PolygonShape spriteShape;
	spriteShape.SetAsBox(sprite->getContentSize().width / PTM_RATIO / 2 * sprite->getScaleX(),
		sprite->getContentSize().height / PTM_RATIO / 2 * sprite->getScaleY());
	b2FixtureDef spriteShapeDef;
	spriteShapeDef.shape = &spriteShape;
	spriteShapeDef.density = 1.0;
	spriteShapeDef.isSensor = true;
	powerB->CreateFixture(&spriteShapeDef);
}
void level2::addBoxBodyForLight(Node * sprite)
{
	sprite->setAnchorPoint(Vec2(.5, .5));
	b2BodyDef spriteBodyDef;
	spriteBodyDef.type = b2_staticBody;
	spriteBodyDef.position.Set(sprite->getPositionX() / PTM_RATIO,
		sprite->getPositionY() / PTM_RATIO);
	spriteBodyDef.userData = sprite;
	lightB = world->CreateBody(&spriteBodyDef);

	b2PolygonShape spriteShape;
	spriteShape.SetAsBox(sprite->getContentSize().width / PTM_RATIO / 2 * sprite->getScaleX(),
		sprite->getContentSize().height / PTM_RATIO / 2 * sprite->getScaleY());
	b2FixtureDef spriteShapeDef;
	spriteShapeDef.shape = &spriteShape;
	spriteShapeDef.density = 1.0;
	spriteShapeDef.isSensor = true;
	lightB->CreateFixture(&spriteShapeDef);
}
void level2::addBoxBodyForPortal(Node * sprite)
{
	sprite->setAnchorPoint(Vec2(.5, .5));
	b2BodyDef spriteBodyDef;
	spriteBodyDef.type = b2_staticBody;
	spriteBodyDef.position.Set(sprite->getPositionX() / PTM_RATIO,
		sprite->getPositionY() / PTM_RATIO);
	spriteBodyDef.userData = sprite;
	portalB = world->CreateBody(&spriteBodyDef);

	b2PolygonShape spriteShape;
	spriteShape.SetAsBox(sprite->getContentSize().width / PTM_RATIO / 2 * sprite->getScaleX(),
		sprite->getContentSize().height / PTM_RATIO / 2 * sprite->getScaleY());
	b2FixtureDef spriteShapeDef;
	spriteShapeDef.shape = &spriteShape;
	spriteShapeDef.density = 1.0;
	spriteShapeDef.isSensor = true;
	portalB->CreateFixture(&spriteShapeDef);
}



void level2::tick()
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
	
	
	while (edge != NULL && edge->contact != NULL)
	{
		if (edge->contact->GetFixtureB()->GetBody() == downArrowBoilerB)
		{
			downArrowBoiler->setOpacity(20);
			if (charMovingDown)
			{
				spriteBody->SetTransform(b2Vec2(20, 27), 0);
			}
		}

		if (edge->contact->GetFixtureB()->GetBody() == upArrowBoilerB)
		{
			upArrowBoiler->setOpacity(20);
			if (charMovingUp)
			{
				spriteBody->SetTransform(b2Vec2(32, 5), 0);

			}
		}
		
		if (edge->contact->GetFixtureB()->GetBody() == upArrowLibraryB)
		{
			upArrowLibrary->setOpacity(20);
			if (charMovingUp)
			{
				spriteBody->SetTransform(b2Vec2(59, 27), 0);
				if (chase == true)
				{
					inLibrary = true;
					world->DestroyBody(upArrowLibraryB);
					world->DestroyBody(downArrowLibraryB);
					world->DestroyBody(downArrowSecretRoomB);
				}
			}
		}
			
		
		if (edge->contact->GetFixtureB()->GetBody() == downArrowLibraryB)
		{
			downArrowLibrary->setOpacity(20);
			if (charMovingDown)
			{
				spriteBody->SetTransform(b2Vec2(50, 5), 0);
			}
		}
		
		if (edge->contact->GetFixtureB()->GetBody() == upArrowSecretRoomB)
		{
			upArrowSecretRoom->setOpacity(20);
			if (charMovingUp)
			{
				spriteBody->SetTransform(b2Vec2(74, 27), 0);
			}
		}
		
		if (edge->contact->GetFixtureB()->GetBody() == downArrowSecretRoomB)
		{
			downArrowSecretRoom->setOpacity(20);
			if (charMovingDown)
			{
				spriteBody->SetTransform(b2Vec2(46, 27), 0);
			}
		}
		
		if (edge->contact->GetFixtureB()->GetBody() == leverTopB)
		{
			if (charUsing)
			{
				audioLv2->playEffect("pickup.wav");
				leverTop->setOpacity(0);
				world->DestroyBody(leverTopB);
				addItemLv2(5);
				setHeldItemLv2(5);
			}
		}
		if (edge->contact->GetFixtureB()->GetBody() == bucketB)
		{
			if (charUsing)
			{
				audioLv2->playEffect("pickup.wav");
				bucket->setOpacity(0);
				world->DestroyBody(bucketB);
				addItemLv2(6);
				setHeldItemLv2(6);
			}
		}
		if (edge->contact->GetFixtureB()->GetBody() == waterBarrelB)
		{
			if (charUsing && id == 6)
			{
				audioLv2->playEffect("pickup.wav");
				world->DestroyBody(waterBarrelB);
				addItemLv2(7);
				shiftInventoryRightLv2();
				removeItemLv2(6);
				setHeldItemLv2(7);

				bucketEmptyPic->setOpacity(0);
			}
		}
		
		if (edge->contact->GetFixtureB()->GetBody() == stoveB)
		{
			if (charUsing && id == 7)
			{
				audioLv2->playEffect("waterCool.wav");
				stoveHotColor->setOpacity(0);
				removeItemLv2(7);
				bucketFullPic->setOpacity(0);
				addItemLv2(6);
				
				
			}
			if (charUsing && stoveHotColor->getOpacity() == 0)
			{
				grateClosed->setOpacity(0);
				grateOpened->setOpacity(255);
				//addBoxBodyForLeverBottom(leverBottom);
				world->DestroyBody(stoveB);
			}
			
		}
		if (edge->contact->GetFixtureB()->GetBody() == leverBottomB)
		{
			if (charUsing && grateOpened->getOpacity() == 255)
			{
				audioLv2->playEffect("pickup.wav");
				leverBottom->setOpacity(0);
				world->DestroyBody(leverBottomB);
				addItemLv2(3);
				setHeldItemLv2(3);
				
			}
		}
		
		if (edge->contact->GetFixtureB()->GetBody() == emptyBoxB)
		{
			if (charUsing && (id == 1 || id == 2))
			{
				audioLv2->playEffect("crateBreak.wav");
				emptyBox->setOpacity(0);
				world->DestroyBody(emptyBoxB);
				crateAnimEmpty->setOpacity(255);
				auto action = FadeOut::create(1);
				crateAnimEmpty->runAction(action);
				cocostudio::timeline::ActionTimeline *timeLine = CSLoader::createTimeline("crateAnim.csb");
				timeLine->retain(); //released later on
				crateAnimEmpty->runAction(timeLine);
				timeLine->gotoFrameAndPlay(0, 20, false);
				
			}
		}
		
		if (edge->contact->GetFixtureB()->GetBody() == leverBoxB)
		{
			if (charUsing && (id == 1 || id == 2) )
			{
				audioLv2->playEffect("crateBreak.wav");
				leverBox->setOpacity(0);
				world->DestroyBody(leverBoxB);
				crateAnimLever->setOpacity(255);
				auto action = FadeOut::create(1);
				crateAnimLever->runAction(action);
				cocostudio::timeline::ActionTimeline *timeLine = CSLoader::createTimeline("crateAnim.csb");
				timeLine->retain(); //released later on
				crateAnimLever->runAction(timeLine);
				timeLine->gotoFrameAndPlay(0, 20, false);
				//addBoxBodyForLeverMiddle(leverMiddle);
				brokeCrateLever = true;
			}
		}
		if (edge->contact->GetFixtureB()->GetBody() == evilBoxB)
		{
			if (charUsing && (id == 1 || id == 2))
			{
				audioLv2->playEffect("crateBreak.wav");
				evilBox->setOpacity(0);
				world->DestroyBody(evilBoxB);
				crateAnimEvil->setOpacity(255);
				auto action = FadeOut::create(1);
				crateAnimEvil->runAction(action);
				cocostudio::timeline::ActionTimeline *timeLine = CSLoader::createTimeline("crateAnim.csb");
				timeLine->retain(); //released later on
				crateAnimEvil->runAction(timeLine);
				timeLine->gotoFrameAndPlay(0, 20, false);
				//addBoxBodyForLeverMiddle(leverMiddle);
				brokeEvilBox = true;
				portal->setOpacity(255);
			}
		}
		if (edge->contact->GetFixtureB()->GetBody() == portalB)
		{
			if (brokeEvilBox == true)
			{
				spriteBody->SetTransform(b2Vec2(12, 5), 0);
				audioLv2->playEffect("tele.wav");
				if (inLibrary == true)
				{
					enemy->setOpacity(0);
					world->DestroyBody(enemyB);
					ghostB->SetTransform(b2Vec2(30, 6), 0);
					ghostB->SetLinearVelocity(b2Vec2(-2, 0));
					teleportedChase = true;
				}
			}
			
		}
		if (edge->contact->GetFixtureB()->GetBody() == lightB)
		{
			if (teleportedChase == true)
			{
				power->setVisible(true);
				inLight = true;
			}
			
		}
		if (edge->contact->GetFixtureB()->GetBody() == ghostB)
		{
			if (inLight == true)
			{
				ghostDied = true;
				ghostB->SetLinearVelocity(b2Vec2(15, 0));
				auto action = FadeOut::create(2);
				ghost->runAction(action);
				audioLv2->playBackgroundMusic("ambience.wav");
				//world->DestroyBody(ghostB);
			}
			else
			{
				audioLv2->stopAllEffects();
				auto scene = NFMenu::createScene();
				Director::getInstance()->replaceScene(TransitionFade::create(0.5, scene, Color3B(0, 0, 0)));
			}

		}
		if (edge->contact->GetFixtureB()->GetBody() == leverMiddleB)
		{
			if (charUsing && brokeCrateLever == true)
			{
				audioLv2->playEffect("pickup.wav");
				leverMiddle->setOpacity(0);
				world->DestroyBody(leverMiddleB);
				addItemLv2(4);
				setHeldItemLv2(4);
				
			}
		}
		if (edge->contact->GetFixtureB()->GetBody() == workBenchB)
		{
			if (charUsing && id == 3)
			{
				leverBottomBench->setOpacity(255);
				leverBottomPic->setOpacity(0);
				removeItemLv2(3);
			}
			if (charUsing && id == 4)
			{
				leverMiddleBench->setOpacity(255);
				leverMiddlePic->setOpacity(0);
				removeItemLv2(4);
			}
			if (charUsing && id == 5)
			{
				leverTopBench->setOpacity(255);
				leverTopPic->setOpacity(0);
				removeItemLv2(5);
			}
			if (leverBottomBench->getOpacity() == 255 && leverMiddleBench->getOpacity() == 255 && leverTopBench->getOpacity() == 255)
			{
				addItemLv2(9);
				setHeldItemLv2(9);
				audioLv2->playEffect("buildSound.wav");
				leverBottomBench->setOpacity(0);
				leverMiddleBench->setOpacity(0);
				leverTopBench->setOpacity(0);
				world->DestroyBody(workBenchB);
			}
		}
		if (edge->contact->GetFixtureB()->GetBody() == leverBaseB)
		{
			if (charUsing && id == 9)
			{
				
				removeItemLv2(9);
				fullLever->setOpacity(0);
				leverComplete->setOpacity(255);
			}
			if (charUsing && leverComplete->getOpacity() == 255)
			{
				leverComplete->setOpacity(0);
				leverPulled->setOpacity(255);
				world->DestroyBody(gateWallB);
				world->DestroyBody(leverBaseB);
				gate->setOpacity(0);
				audioLv2->playEffect("buildSound.wav");
			}
		}
		if (edge->contact->GetFixtureB()->GetBody() == bowB)
		{
			if (charUsing)
			{
				audioLv2->playEffect("pickup.wav");
				bow->setOpacity(0);
				world->DestroyBody(bowB);
				addItemLv2(8);
				setHeldItemLv2(8);
				chase = true;
				audioLv2->playBackgroundMusic("Horror.wav");
				ghost->setOpacity(200);
				enemy->setOpacity(255);
				light->setOpacity(30);
				ghostB->SetLinearVelocity(b2Vec2(-4, 0));

			}
		}
		
		edge = edge->next;
	}
}

void level2::displayInv()
{
	id = getHeldItemLv2();  // displays depending on invetory item
	
	interactText->setPosition(sprite->getPositionX() + 20, sprite->getPositionY() + 20);
	axePic->setPosition(sprite->getPositionX() - 20, sprite->getPositionY() - 20);      // sets position of the inventory image
	crobarPic->setPosition(sprite->getPositionX() - 20, sprite->getPositionY() - 20);
	leverBottomPic->setPosition(sprite->getPositionX() - 20, sprite->getPositionY() - 20);
	leverMiddlePic->setPosition(sprite->getPositionX() - 20, sprite->getPositionY() - 20);
	leverTopPic->setPosition(sprite->getPositionX() - 20, sprite->getPositionY() - 20);
	bucketEmptyPic->setPosition(sprite->getPositionX() - 20, sprite->getPositionY() - 20);
	bucketFullPic->setPosition(sprite->getPositionX() - 20, sprite->getPositionY() - 20);
	bowPic->setPosition(sprite->getPositionX() - 20, sprite->getPositionY() - 20);
	fullLever->setPosition(sprite->getPositionX() - 20, sprite->getPositionY() - 20);

	

	if (id == 1)
	{
		crobarPic->setOpacity(155);
		axePic->setOpacity(0);
		leverBottomPic->setOpacity(0);
		leverMiddlePic->setOpacity(0);
		leverTopPic->setOpacity(0);
		bucketEmptyPic->setOpacity(0);
		bucketFullPic->setOpacity(0);
		bowPic->setOpacity(0);
		fullLever->setOpacity(0);
	}
	if (id == 2)
	{
		crobarPic->setOpacity(0);
		axePic->setOpacity(155);
		leverBottomPic->setOpacity(0);
		leverMiddlePic->setOpacity(0);
		leverTopPic->setOpacity(0);
		bucketEmptyPic->setOpacity(0);
		bucketFullPic->setOpacity(0);
		bowPic->setOpacity(0);
		fullLever->setOpacity(0);
	}
	if (id == 3)
	{
		crobarPic->setOpacity(9);
		axePic->setOpacity(0);
		leverBottomPic->setOpacity(155);
		leverMiddlePic->setOpacity(0);
		leverTopPic->setOpacity(0);
		bucketEmptyPic->setOpacity(0);
		bucketFullPic->setOpacity(0);
		bowPic->setOpacity(0);
		fullLever->setOpacity(0);
	}
	if (id == 4)
	{
		crobarPic->setOpacity(0);
		axePic->setOpacity(0);
		leverBottomPic->setOpacity(0);
		leverMiddlePic->setOpacity(155);
		leverTopPic->setOpacity(0);
		bucketEmptyPic->setOpacity(0);
		bucketFullPic->setOpacity(0);
		bowPic->setOpacity(0);
		fullLever->setOpacity(0);
	}
	if (id == 5)
	{
		crobarPic->setOpacity(0);
		axePic->setOpacity(0);
		leverBottomPic->setOpacity(0);
		leverMiddlePic->setOpacity(0);
		leverTopPic->setOpacity(155);
		bucketEmptyPic->setOpacity(0);
		bucketFullPic->setOpacity(0);
		bowPic->setOpacity(0);
		fullLever->setOpacity(0);
	}
	if (id == 6)
	{
		crobarPic->setOpacity(0);
		axePic->setOpacity(0);
		leverBottomPic->setOpacity(0);
		leverMiddlePic->setOpacity(0);
		leverTopPic->setOpacity(0);
		bucketEmptyPic->setOpacity(155);
		bucketFullPic->setOpacity(0);
		bowPic->setOpacity(0);
		fullLever->setOpacity(0);
	}
	if (id == 7)
	{
		crobarPic->setOpacity(0);
		axePic->setOpacity(0);
		leverBottomPic->setOpacity(0);
		leverMiddlePic->setOpacity(0);
		leverTopPic->setOpacity(0);
		bucketEmptyPic->setOpacity(0);
		bucketFullPic->setOpacity(155);
		bowPic->setOpacity(0);
		fullLever->setOpacity(0);
	}
	if (id == 8)
	{
		crobarPic->setOpacity(0);
		axePic->setOpacity(0);
		leverBottomPic->setOpacity(0);
		leverMiddlePic->setOpacity(0);
		leverTopPic->setOpacity(0);
		bucketEmptyPic->setOpacity(0);
		bucketFullPic->setOpacity(0);
		bowPic->setOpacity(155);
		fullLever->setOpacity(0);
	}
	if (id == 9)
	{
		crobarPic->setOpacity(0);
		axePic->setOpacity(0);
		leverBottomPic->setOpacity(0);
		leverMiddlePic->setOpacity(0);
		leverTopPic->setOpacity(0);
		bucketEmptyPic->setOpacity(0);
		bucketFullPic->setOpacity(0);
		bowPic->setOpacity(0);
		fullLever->setOpacity(155);
	}

}

void level2::update(float)
{
	tick(); // runs physics and collissions

	this->runAction(CCFollow::create(sprite, Rect(0, 0, 3000, 1200))); // camera follows player 

	displayInv();

	if (invR)
	{
		shiftInventoryRightLv2();
		invR = false;
	}
	if (ghostDied == true)
	{
		power->setPosition(ghost->getPosition());
	}
	else
		power->setPosition(sprite->getPosition());

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

void level2::draw(cocos2d::Renderer * renderer, const cocos2d::Mat4 & transform, uint32_t flags)
{
	kmGLPushMatrix();
	world->DrawDebugData();
	kmGLPopMatrix();
}

bool level2::init()
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

	auto rootNode = CSLoader::createNode("level2.csb");
	audioLv2->playBackgroundMusic("ambience.wav", true);
	
	//---world

	//--------------WALLS
	 floor = rootNode->getChildByName("floor");
	 leftWall = rootNode->getChildByName("leftWall");
	 rightWall = rootNode->getChildByName("rightWall");
	 ceiling = rootNode->getChildByName("ceiling");
	 ceiling2 = rootNode->getChildByName("ceiling2");
	 leftWall2 = rootNode->getChildByName("leftWall2");
	 rightWall2 = rootNode->getChildByName("rightWall2");
	 middleWall = rootNode->getChildByName("middleWall");
	 middleWall2 = rootNode->getChildByName("middleWall2");
	 gateWall = rootNode->getChildByName("gateWall");
	
	 rain = rootNode->getChildByName("rainPNG");
	 rainAnim = rootNode->getChildByName("rainAnim");
	 cocostudio::timeline::ActionTimeline *timeLine3 = CSLoader::createTimeline("rainAnim.csb");
	 timeLine3->retain(); //released later on
	 rainAnim->runAction(timeLine3);
	 timeLine3->gotoFrameAndPlay(0, 29, true);

	 addBoxBodyForStaticWall(floor,floorB);
	 addBoxBodyForStaticWall(leftWall, leftWallB);
	 addBoxBodyForStaticWall(rightWall, rightWallB);
	 addBoxBodyForStaticWall(ceiling, ceilingB);
	 addBoxBodyForStaticWall(ceiling2, ceiling2B);
	 addBoxBodyForStaticWall(leftWall2, leftWall2B);
	 addBoxBodyForStaticWall(middleWall, middleWallB);
	 addBoxBodyForStaticWall(middleWall2, middleWall2B);
	 addBoxBodyForStaticWall(rightWall2, rightWall2B);
	 

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
	
	//----------------------Room 1
	leverBottom = rootNode->getChildByName("leverBottom");
	addBoxBodyForLeverBottom(leverBottom);
	downArrowBoiler = rootNode->getChildByName("downArrowBoiler");
	downArrowBoiler->setOpacity(0);
	addBoxBodyForDownArrowBoiler(downArrowBoiler);

	//-----------ROOM 2
	leverBase = rootNode->getChildByName("leverBase");
	addBoxBodyForLeverBase(leverBase);
	upArrowLibrary = rootNode->getChildByName("upArrowLibrary");
	upArrowLibrary->setOpacity(0);
	addBoxBodyForUpArrowLibrary(upArrowLibrary);
	bucket = rootNode->getChildByName("bucket");
	addBoxBodyForBucket(bucket);
	gate = rootNode->getChildByName("gate");
	addBoxBodyForGateWall(gateWall);
	leverComplete = rootNode->getChildByName("leverComplete");
	leverPulled = rootNode->getChildByName("leverPulled");

	//-----Boiler
	stove = rootNode->getChildByName("stove");
	addBoxBodyForStove(stove);
	grateOpened = rootNode->getChildByName("grateOpened");
	grateClosed = rootNode->getChildByName("grateClosed");
	leverTop = rootNode->getChildByName("leverTop");
	addBoxBodyForLeverTop(leverTop);
	stoveHotColor = rootNode->getChildByName("hotStoveColor");
	//boilerRoomNote = rootNode->getChildByName("leverBottom");
	upArrowBoiler = rootNode->getChildByName("upArrowBoiler");
	upArrowBoiler->setOpacity(0);
	addBoxBodyForUpArrowBoiler(upArrowBoiler);

	//---Library
	bookshelf = rootNode->getChildByName("bookshelf");
	addBoxBodyForBookshelf(bookshelf);
	upArrowSecretRoom = rootNode->getChildByName("upArrowSecretRoom");
	upArrowSecretRoom->setOpacity(0);
	addBoxBodyForUpArrowSecretRoom(upArrowSecretRoom);
	downArrowLibrary = rootNode->getChildByName("downArrowLibrary");
	downArrowLibrary->setOpacity(0);
	addBoxBodyForDownArrowLibrary(downArrowLibrary);
	workBench = rootNode->getChildByName("workbench");
	addBoxBodyForBench(workBench);
	leverBottomBench = rootNode->getChildByName("leverBottomBench");
	leverMiddleBench = rootNode->getChildByName("leverMiddleBench");
	leverTopBench = rootNode->getChildByName("leverTopBench");

	//-----SecretRoom
	downArrowSecretRoom = rootNode->getChildByName("downArrowSecretRoom");
	downArrowSecretRoom->setOpacity(0);
	addBoxBodyForDownArrowSecretRoom(downArrowSecretRoom);
	waterBarrel = rootNode->getChildByName("waterBarrel");
	addBoxBodyForWaterBarrel(waterBarrel);
	emptyBox = rootNode->getChildByName("emptyBox");
	addBoxBodyForEmptyBox(emptyBox);
	leverBox = rootNode->getChildByName("leverBox");
	addBoxBodyForLeverBox(leverBox);
	evilBox= rootNode->getChildByName("evilBox");
	addBoxBodyForEvilBox(evilBox);
	leverMiddle = rootNode->getChildByName("leverMiddle");
	addBoxBodyForLeverMiddle(leverMiddle);

	//---Transition

	bow = rootNode->getChildByName("bow");
	addBoxBodyForBow(bow);
	
	//----CRATES
	crateAnimEmpty = rootNode->getChildByName("crateAnimEmpty");
	crateAnimLever = rootNode->getChildByName("crateAnimLever");
	crateAnimEvil = rootNode->getChildByName("crateAnimEvil");
	evilBoxB->ApplyLinearImpulse(b2Vec2(.1, 0), evilBoxB->GetLocalCenter(), true);


	//----INV
	crobarPic = cocos2d::Sprite::create("crobar.png");
	axePic = cocos2d::Sprite::create("axe.png");
	leverBottomPic = cocos2d::Sprite::create("Bottom Lever Rod.png");
	leverMiddlePic = cocos2d::Sprite::create("Middle Lever Rod.png");
	leverTopPic = cocos2d::Sprite::create("Top Lever Rod.png");
	bucketEmptyPic = cocos2d::Sprite::create("Empty Water Bucket.png");
	bucketFullPic = cocos2d::Sprite::create("Filled Water Bucket.png");
	bowPic = cocos2d::Sprite::create("bow.png");
	fullLever = cocos2d::Sprite::create("fullLever.png");
	interactText = rootNode->getChildByTag(132);
	interactText->setOpacity(0);
	
	addItemLv2(1);
	addItemLv2(2);
	
	fullLever->setOpacity(0);
	crobarPic->setOpacity(0);
	axePic->setOpacity(0);
	leverBottomPic->setOpacity(0);
	leverMiddlePic->setOpacity(0);
	leverTopPic->setOpacity(0);
	bucketEmptyPic->setOpacity(0);
	bucketFullPic->setOpacity(0);
	bowPic->setOpacity(0);

	//-------BOSS
	portal = rootNode->getChildByName("portal");
	addBoxBodyForPortal(portal);
	ghost = rootNode->getChildByName("ghost");
	addBoxBodyForGhost(ghost);
	enemy = rootNode->getChildByName("enemy");
	addBoxBodyForEnemy(enemy);
	light = rootNode->getChildByName("light");
	addBoxBodyForLight(light);
	power = rootNode->getChildByName("power");
	power->setVisible(false);
	
	//addBoxBodyForPower(power);


	rootNode->setOpacity(255);
	
	this->addChild(rootNode);
	this->addChild(fullLever);
	this->addChild(axePic);
	this->addChild(crobarPic);
	this->addChild(leverBottomPic);
	this->addChild(leverMiddlePic);
	this->addChild(leverTopPic);
	this->addChild(bucketEmptyPic);
	this->addChild(bucketFullPic);
	this->addChild(bowPic);
	
	
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
		//case EventKeyboard::KeyCode::KEY_Z:
		//	invL = true;
		//	break;
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