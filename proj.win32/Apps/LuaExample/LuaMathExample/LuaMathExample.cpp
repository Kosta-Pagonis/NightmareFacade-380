#include <iostream>

#include "LuaPlus.h"
using namespace LuaPlus;
#include "stdio.h"
using namespace std;

/* The main idea:
- We store stats and inventory in a lua file. Whenever we want a stat or change/access the inventory, we'll do so from the lua file.
- Since this is a little slow (from what the Internet says), we won't do this too often.
*/

int main()
{
	// Init Lua
	LuaState* luaPState = LuaState::Create();
	//Until the lua file is closed, any changes we make to the lua file should stay.
	//When the lua file is closed, any changes made should revert to their original values.

	// Open the Lua Script File
	int result = luaPState->DoFile("stats.lua");

	
	// Get the current sanity and current light.
	LuaFunction<int> getCurSanity = luaPState->GetGlobal("getCurSanity"); //getCurSanity returns an int.
	int sanity = getCurSanity();
	LuaFunction<int> getCurLight = luaPState->GetGlobal("getCurLight"); //getCurLight returns an int.
	int light = getCurLight();

	cout << "Current Sanity: " + sanity << endl;
	cout << "Current Light: " + light << endl;
	//These don't print to the console properly, but nevertheless are correctly calculated.

	// Let's call the stats.lua's decSanityByAmount function
	LuaFunction<float> decSanityByAmount = luaPState->GetGlobal("decSanityByAmount");
	sanity = decSanityByAmount(50); //Sanity is now 50.
	sanity = decSanityByAmount(50); //Sanity is now 0.
	//Restore sanity
	LuaFunction<void> restoreSanityToMax = luaPState->GetGlobal("restoreSanityToMax");
	restoreSanityToMax(); //Sanity is now 100.
	sanity = getCurSanity(); //Get the current sanity.
	cout << sanity << endl;
	//100

	//Let's decrease the light and sanity through the decLightByOne fucntion
	LuaFunction<void> decLightByOne = luaPState->GetGlobal("decLightByOne"); //Decreases the light by 1, and by extension the sanity by 1.
	decLightByOne(); 
	light = getCurLight(); //99
	sanity = getCurSanity(); //99
	cout << "Current Sanity: " + sanity << endl;
	cout << "Current Light: " + light << endl;
	//These don't print to the console properly, but nevertheless are correctly calculated.

	//Let's print out the currently held item from the inventory.
	LuaFunction<int> getHeldItem = luaPState->GetGlobal("getHeldItem");  //Returns an int.
	LuaFunction<void> shiftInventoryRight = luaPState->GetGlobal("shiftInventoryRight"); //Shifts the inventory to the right.
	LuaFunction<void> shiftInventoryLeft = luaPState->GetGlobal("shiftInventoryLeft"); //Shifts the inventory to the left.
	shiftInventoryLeft(); //Moves the pointer left until it finds a non negative-1 value.
	shiftInventoryRight(); //Moves the pointer right until it finds a non negative-1 value.
	cout << getHeldItem() << endl;

	//Closes the lua file.
	LuaState::Destroy(luaPState);
	//End of main.
	return 0;
}

