package.path = "./?.lua;"..package.path

local cclog = function(...)
	print(string.format(...))
end

collectgarbage("setpause", 100)
collectgarbage("setstepmul", 5000)

local winSize = CCDirector:sharedDirector():getWinSize()

local function createGameLayer()
	local layer = CCLayer:create()
	local sprite0 = CCSprite:create("background.png")
	local sprite1 = CCSprite:create("background.png")
	layer:addChild(sprite0)
	layer:addChild(sprite1)
	sprite0:setPosition(CCPointMake(sprite0:getContentSize().width / 2, winSize.height/2))
	sprite1:setPosition(CCPointMake(sprite1:getContentSize().width * 3 / 2, winSize.height/2))

	local firstmove = CCMoveBy:create(10, CCPointMake(- sprite0:getContentSize().width, 0))
	-- assume the same width of sprite 0 as sprite1
	local place = CCPlace:create(CCPointMake(sprite0:getContentSize().width * 3 / 2, winSize.height/2))
	local move = CCMoveBy:create(20, CCPointMake(- sprite0:getContentSize().width * 2, 0))
	local array = CCArray:create()
	array:addObject(firstmove)
	array:addObject(place)
	array:addObject(move)
	local seq = CCSequence:create(array)
	local action0 = sprite0:runAction(CCSequence:createWithTwoActions(firstmove0, CCRepeatForever:create(seq)))
	action0:setTag(0)
	local seq = CCSequence:create(array)
	local action0 = sprite0:runAction(CCSequence:createWithTwoActions(firstmove0, CCRepeatForever:create(seq)))
	action0:setTag(0)
	local action1 = sprite1:runAction(CCRepeatForever:create(seq))
	action1:setTag(1)

	return layer
end

local function createMainScene()
	local scene = CCScene:create()
	-- scene:addChild(createBackgroundLayer())
	scene:addChild(createGameLayer())
	-- scene:addChild(createFrontLayer())
	-- scene:addChild(createControlLayer())
	return scene
end

-- run
local scene = createMainScene()
CCDirector:sharedDirector():runWithScene(scene)
