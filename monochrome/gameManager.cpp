#include <DxLib.h>
#include "gameManager.hpp"
void GameManager::_MoveLoad(){
	imgMirror = LoadGraph("img\\mirror.bmp");
	imgRayOn = LoadGraph("img\\ray_on.bmp");
	imgRayOff = LoadGraph("img\\ray_off.bmp");

	SetStage(Title);
}
void GameManager::_MoveTitle(){
	if ((GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_1) != 0){
		SetStage(StageSelect);
	}
}
void GameManager::_MoveStageSelect(){
	//GenerateRandomMap(2, 0);

	
	//**************************
	mirrorGroup.clear();
	playerRay.isHittable = false;

	start.x = 10;
	start.y = 100;
	startRad = 0;

	playerRay.setStart(start, 0);
	Mirror tmirror;

	//正解1
	tmirror.location.x = 320;
	tmirror.location.y = 100;
	tmirror.normal.x = std::cos(2.35619449);
	tmirror.normal.y = std::sin(2.35619449);
	mirrorGroup.push_back(tmirror);

	//正解2
	tmirror.location.x = 320;
	tmirror.location.y = 320;
	tmirror.normal.x = std::cos(5.235987755983);
	tmirror.normal.y = std::sin(5.235987755983);
	mirrorGroup.push_back(tmirror);

	//正解3
	tmirror.location.x = 460;
	tmirror.location.y = 250;
	tmirror.normal.x = std::cos(5.235987755983);
	tmirror.normal.y = std::sin(5.235987755983);
	mirrorGroup.push_back(tmirror);

	//正解4
	tmirror.location.x = 460;
	tmirror.location.y = 320;
	tmirror.normal.x = std::cos(2.3561944901923);
	tmirror.normal.y = std::sin(2.3561944901923);
	mirrorGroup.push_back(tmirror);


	//ダミー1
	tmirror.location.x = 160;
	tmirror.location.y = 100;
	tmirror.normal.x = std::cos(2.35619449);
	tmirror.normal.y = std::sin(2.35619449);
	mirrorGroup.push_back(tmirror);

	//ダミー2
	tmirror.location.x = 160;
	tmirror.location.y = 320;
	tmirror.normal.x = std::cos(0.785398163);
	tmirror.normal.y = std::sin(0.785398163);
	mirrorGroup.push_back(tmirror);

	//ダミー3
	tmirror.location.x = 600;
	tmirror.location.y = 150;
	tmirror.normal.x = std::cos(2.35619449);
	tmirror.normal.y = std::sin(2.35619449);
	mirrorGroup.push_back(tmirror);

	//ダミー4
	tmirror.location.x = 390;
	tmirror.location.y = 285;
	tmirror.normal.x = std::cos(0);
	tmirror.normal.y = std::sin(0);
	mirrorGroup.push_back(tmirror);


	goal.x = 600;
	goal.y = 320;

	//***************************
	
	
	SetStage(Main); }
void GameManager::_MoveMain(){
	if (_frame == 0){
		playerRay.setStart(start, startRad);
		recordRay.clear();
		replayRay.clear();
	}

	//キー操作判定
	if ((GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_1) != 0){
		playerRay.isHittable = true;
	}
	else{
		playerRay.isHittable = false;
	}

	//ミラーの当たり判定
	for each (Mirror mirror in mirrorGroup){
		if (playerRay.isHittable && playerRay.isHit(mirror)){
			//printfDx("hit");
			playerRay.vector = playerRay.getRefrectVec(mirror);
		}
	}

	//光を動かす
	playerRay.Move();

	if (_frame % 10 == 0){
		recordRay.push_back(playerRay);
	}

	if (playerRay.location.x < 0 ||
		playerRay.location.x > 640 ||
		playerRay.location.y < 0 ||
		playerRay.location.y > 480){

		playerRay.setStart(start, startRad);
		replayRay = recordRay;
		recordRay.clear();

		//SetStage(GameOver);
	}

	//ゴール地点到達判定
	double tx = playerRay.location.x - goal.x;
	double ty = playerRay.location.y - goal.y;
	if (tx * tx + ty * ty <= 32*32){
		recordRay.clear();
		replayRay.clear();

		SetStage(GameClear);
	}
}
void GameManager::_MoveGameOver(){ SetStage(Title); }
void GameManager::_MoveGameClear(){
	//if ((GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_1) != 0){
	if (_frame>180){
		SetStage(Title);
	}
}
void GameManager::_DrawLoad(){}
void GameManager::_DrawTitle(){
	DrawString(400, 230, "Press Z key to start.", GetColor(255, 255, 255));
}
void GameManager::_DrawStageSelect(){}
void GameManager::_DrawMain(){

	SetDrawBlendMode(DX_BLENDMODE_ADD, 64);
	for each (Ray i in replayRay){
		DrawRotaGraph(i.location.x, i.location.y, 1.0, 0, (i.isHittable) ? imgRayOn : imgRayOff, TRUE);
	}
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);

	DrawString(start.x, start.y, "S", GetColor(255,255,255));
	DrawString(goal.x, goal.y, "G", GetColor(255, 255, 255));
	for each (Mirror mirror in mirrorGroup){
		DrawRotaGraph(mirror.location.x,
			mirror.location.y,
			1.0, mirror.normal.rad(),imgMirror,TRUE);
	}

	DrawRotaGraph(playerRay.location.x, playerRay.location.y,1.0,0, (playerRay.isHittable) ? imgRayOn : imgRayOff,TRUE);
}
void GameManager::_DrawGameOver(){
	DrawString(400, 230, "Game Over.", GetColor(255, 255, 255));

}
void GameManager::_DrawGameClear(){
	DrawString(400, 230, "Stage Cleared!", GetColor(255, 255, 255));

}

Vector GameManager::GenerateRandomPos(int restrictArea){
	return Vector(
		GetRand(640 - restrictArea * 2) + restrictArea,
		GetRand(480 - restrictArea * 2) + restrictArea);
}
void GameManager::GenerateRandomMap(int correctMirrorNum, int DummyMirrorNum){
	mirrorGroup.clear();

	static const int restrictArea = 64;

	start = GenerateRandomPos(restrictArea);

	double rad;
	int dist;
	for (;;){
		rad = GetRand(359) * 3.14159265 / 180.0;
		dist = GetRand(300) + 64;
		if (IsInScreen(Vector(start.x+std::cos(rad)*dist, start.y+std::sin(rad)*dist))){
			break;
		}
	}
	startRad = rad;
	playerRay.setStart(start, startRad);

	Mirror m;
	m.location = Vector(start.x + std::cos(rad)*dist, start.y + std::sin(rad)*dist);
	Vector nextPos;
	Vector nextRay;

	for (;;){
		rad = GetRand(359) * 3.14159265 / 180.0;
		m.normal.x = cos(rad);
		m.normal.y = sin(rad);
		dist = GetRand(300) + 64;
		Ray r;
		r.vector = Vector(std::cos(startRad), std::sin(startRad));
		nextPos = Vector(m.location.x + r.getRefrectVec(m).x*dist, m.location.y + r.getRefrectVec(m).y*dist);
		nextRay = Vector(r.getRefrectVec(m).x, r.getRefrectVec(m).y);
		if (IsInScreen(nextPos)){
			break;
		}
	}
	mirrorGroup.push_back(m);


	for (int i = 1; i < correctMirrorNum; i++){
		m.location = nextPos;
		for (;;){
			rad = GetRand(359) * 3.14159265 / 180.0;
			m.normal.x = cos(rad);
			m.normal.y = sin(rad);
			dist = GetRand(300) + 64;
			Ray r;
			r.vector = nextRay;
			nextPos = Vector(m.location.x + r.getRefrectVec(m).x*dist, m.location.y + r.getRefrectVec(m).y*dist);
			nextRay = Vector(r.getRefrectVec(m).x, r.getRefrectVec(m).y);
			if (IsInScreen(nextPos)){
				break;
			}
		}
		mirrorGroup.push_back(m);
	}

	goal = nextPos;

}
