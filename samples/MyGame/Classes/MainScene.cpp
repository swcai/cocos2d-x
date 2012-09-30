#include "MainScene.h"
#include "GameOverScene.h" // reuse GameOverScene

using namespace cocos2d;

MainScene::MainScene() {
}

MainScene::~MainScene() {
}

CCScene* MainScene::scene() {
	CCScene* scene = NULL;
	scene = CCScene::create();
	if (!scene) break;

	MainScene *layer = MainScene::create();
	if (!layer) break;

	scene->addChild(layer);
	return scene;
}

