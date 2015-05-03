#include "gameManager.hpp"
void GameManager::_MoveLoad(){ SetStage(Title); }
void GameManager::_MoveTitle(){ SetStage(StageSelect); }
void GameManager::_MoveStageSelect(){ SetStage(Main); }
void GameManager::_MoveMain(){ SetStage(GameOver); }
void GameManager::_MoveGameOver(){ SetStage(Title); }
void GameManager::_MoveGameClear(){ SetStage(Title); }
void GameManager::_DrawLoad(){}
void GameManager::_DrawTitle(){}
void GameManager::_DrawStageSelect(){}
void GameManager::_DrawMain(){}
void GameManager::_DrawGameOver(){}
void GameManager::_DrawGameClear(){}