/**
AGP Assignment
GameScene.cpp
Purpose: Main Scene for the Game

@author Marcel Zobus
*/
#include "GameScene.h"
#include "Player.h"

GameScene::~GameScene()
{
	if (mUpDownFlag) delete mUpDownFlag;
	if (mUpDownFlag2) delete mUpDownFlag2;
	if (mUpDownVelocity) delete mUpDownVelocity;
	if (mUpDownVelocity2) delete mUpDownVelocity2;
	if (mRootNodeLevel) delete mRootNodeLevel;
}

bool GameScene::Init()
{
	mSceneData = SceneData::GetInstance();
	mD3DDevice = mSceneData->GetDevice();
	mImmediateContext = mSceneData->GetImmediateContext();
	
	mLight = mSceneData->GetLight();

	//initPlayer();
	mUpDownFlag = new bool();
	mUpDownFlag2 = new bool();
	mUpDownVelocity = new float();
	mUpDownVelocity2 = new float();
	*mUpDownFlag = true;
	*mUpDownFlag2 = false;
	*mUpDownVelocity = 10;
	*mUpDownVelocity2 = -6;

	initLevel();

	return true;
}


void GameScene::RenderScene(float dt)
{
	moveGameObjectUpAndDown(mMovingChild, mUpDownVelocity, mUpDownFlag, 8, dt);
	moveGameObjectUpAndDown(mMovingChild2, mUpDownVelocity2, mUpDownFlag2, 10, dt);

	mRootNodeLevel->execute(&XMMatrixIdentity(), mSceneData->GetView(), mSceneData->GetProjection());
}

void GameScene::initLevel()
{
	Model* mCube = new Model(mD3DDevice, mImmediateContext);

	//textrue
	D3DX11CreateShaderResourceViewFromFile(mD3DDevice, "assets/stone.jpg", NULL, NULL, &mTexture, NULL);
	mCube->LoadObjModel("assets/cube.obj", mTexture);
	mCube->SetLightData(mLight);

	Model* mCube2 = new Model(mD3DDevice, mImmediateContext);

	//textrue
	D3DX11CreateShaderResourceViewFromFile(mD3DDevice, "assets/metal.jpg", NULL, NULL, &mTexture, NULL);
	mCube2->LoadObjModel("assets/cube.obj", mTexture);
	mCube2->SetLightData(mLight);

	mRootNodeLevel = new SceneNode();

	LevelGenerator* levelGenerator = new LevelGenerator();
	levelGenerator->GetSeed()->SetLevelElements(5);
	mRootNodeLevel = levelGenerator->Generate(mCube, mCube2);

	mMovingChild = mRootNodeLevel->GetChildren().at(2);
	mMovingChild2 = mRootNodeLevel->GetChildren().at(4);

}


void GameScene::moveGameObjectUpAndDown(SceneNode* movingChild, float* velocity, bool* updownflag, float maxPos, float dt)
{
	movingChild->SetYPos(movingChild->GetYPos() + (*velocity*dt));

	if (*updownflag && movingChild->GetYPos() >= maxPos)
	{
		*velocity *= -1;
		*updownflag = false;
	}
	if (*updownflag && movingChild->GetYPos() <= -maxPos)
	{
		*velocity *= -1;
		*updownflag = false;
	}

	if (movingChild->GetYPos() < maxPos && movingChild->GetYPos() > -maxPos)
		*updownflag = true;
}
