--Global Variables
maxSanity = 100 --The maximum amount of sanity.
curSanity = 100 --The current amount of sanity.

maxLight = 100 --The maximum amount of light.
curLight = 100 --The current amount of light.

inventory = {-1,-1,-1,-1,-1} --We will store items using a numerical ID system. If a slot in the array does not hold an item, the value
						   --Should be -1.
inventoryPointer = 1       --We will use a pointer to point to the currently held item.
inventorySize =	5		   --A helper variable for moving around the pointer.

--Sanity & Light Functions ----------------------------------------------
--Gets the current Sanity.
function getCurSanity()
    return curSanity
end

--Gets the current light.
function getCurLight()
    return curLight
end

--Decrease sanity by an amount.
function decSanityByAmount(amount)
    curSanity = curSanity - amount
    if(curSanity < 0) then
         curSanity = 0
    end
	return curSanity
end

--Decrease light by an amount.
--Lack of light decreases sanity by 1 as well.
function decLightByOne()
        curLight = curLight - 1
		curSanity = curSanity - 1
        if(curLight == 0) then
            curLight = 0
        end
	    if(curSanity < 0) then
			curSanity = 0
		end
		return curLight
end

-- Decrease light by an amount.
function decLightByAmount(amount)
        curLight = curLight - amount
        if(curLight < 0) then
            curLight = 0
        end
		return curLight
end
       
--Restores light to it's maximum value, determined by maxLight.
function restoreLightToMax()
            curLight = maxLight
end

--Restores sanity to it's maximum value, determined by maxSanity.
function restoreSanityToMax()
			curSanity = maxSanity
end

--Inventory Functions ----------------------------------------------------

--Adds an item to the inventory. The function looks for the first -1 value and replaces it with the 
--item's id, "item"
function addItem(item)
    local i = 1
    while(i <= inventorySize) do
        if(inventory[i] == -1) then
            inventory[i] = item
            i = inventorySize
        end
		i = i+1
    end
end

--Returns the current value determined by inventoryPointer, the inventory's pointer.
function getHeldItem()
    return inventory[inventoryPointer] --lua starts indicies at 1
end

--Moves the pointer to the left of the array until a non negative-1 value is found.
function shiftInventoryLeft()
	local temp = inventoryPointer
    inventoryPointer = inventoryPointer - 1
    if(inventoryPointer <= 0) then
        inventoryPointer = inventorySize
    end
    while(inventory[inventoryPointer] == -1) do
        inventoryPointer = inventoryPointer - 1
        if(inventoryPointer <= 0) then
            inventoryPointer = inventorySize
        end
		if(inventoryPointer == temp) then
			return
		end
    end
end

--Moves the pointer to the right of the array until a non negative-1 value is found.
function shiftInventoryRight()
	local temp = inventoryPointer
    inventoryPointer = inventoryPointer + 1
    if(inventoryPointer > inventorySize) then
        inventoryPointer = 1
    end
    while(inventory[inventoryPointer] == -1) do
        inventoryPointer = inventoryPointer + 1
        if(inventoryPointer > inventorySize) then
            inventoryPointer = 1
        end
		if(inventoryPointer == temp) then
			return
		end
    end
end

--Testing

--decLight()
--print (getCurSanity())
--shiftInventoryLeft()
--shiftInventoryLeft()
--print (getHeldItem())
