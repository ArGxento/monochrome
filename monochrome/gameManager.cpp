#include "gameManager.hpp"
void GameManager::_MoveLoad(){ SetStage(Title); }
void GameManager::_MoveTitle(){ SetStage(StageSelect); }
void GameManager::_MoveStageSelect(){ SetStage(Main); }
void GameManager::_MoveMain(){

	//ƒ~ƒ‰[‚Ì“–‚½‚è”»’è
	for each (Mirror mirror in mirrorGroup){
		if (playerRay.isHittable && playerRay.isHit(mirror)){
			playerRay.vector = playerRay.getRefrectVec(mirror);
		}
	}

	//Œõ‚ğ“®‚©‚·
	playerRay.Move();

	
	if (playerRay.location.x < 0 ||
		playerRay.location.x > 640 ||
		playerRay.location.y < 0 ||
		playerRay.location.y > 480){
		SetStage(GameOver);
	}
}
void GameManager::_MoveGameOver(){ SetStage(Title); }
void GameManager::_MoveGameClear(){ SetStage(Title); }
void GameManager::_DrawLoad(){}
void GameManager::_DrawTitle(){}
void GameManager::_DrawStageSelect(){}
void GameManager::_DrawMain(){}
void GameManager::_DrawGameOver(){}
void GameManager::_DrawGameClear(){}