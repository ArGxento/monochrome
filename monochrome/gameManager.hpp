#pragma once
#include<vector>
#include "object.hpp"
class GameManager{
public:
	enum Stage{
		Load,
		Title,
		StageSelect,
		Main,
		GameOver,
		GameClear
	};
	std::vector<Mirror> mirrorGroup;
	Ray playerRay;
	std::vector<Ray> recordRay;
	std::vector<Ray> replayRay;
	Vector start;
	double startRad;
	Vector goal;
	//bool isRayEnable = true; //Œõ‚ª”½ŽË‚·‚é‚©”Û‚©‚Ì‘®«

	int imgRayOn;
	int imgRayOff;
	int imgMirror;

private:
	Stage _nowStage;
	int _frame;
	void _MoveLoad();
	void _MoveTitle();
	void _MoveStageSelect();
	void _MoveMain();
	void _MoveGameOver();
	void _MoveGameClear();
	void _DrawLoad();
	void _DrawTitle();
	void _DrawStageSelect();
	void _DrawMain();
	void _DrawGameOver();
	void _DrawGameClear();
public:
	void Move(){
		switch (_nowStage){
		case Load:
			_MoveLoad();
			break;
		case Title:
			_MoveTitle();
			break;
		case StageSelect:
			_MoveStageSelect();
			break;
		case Main:
			_MoveMain();
			break;
		case GameOver:
			_MoveGameOver();
			break;
		case GameClear:
			_MoveGameClear();
			break;
		default:
			_MoveLoad();
			break;
		}
		_frame++;
	}
	void Draw(){
		switch (_nowStage){
		case Load:
			_DrawLoad();
			break;
		case Title:
			_DrawTitle();
			break;
		case StageSelect:
			_DrawStageSelect();
			break;
		case Main:
			_DrawMain();
			break;
		case GameOver:
			_DrawGameOver();
			break;
		case GameClear:
			_DrawGameClear();
			break;
		default:
			_DrawLoad();
			break;
		}
	}
	void SetStage(Stage stage){
		_nowStage = stage;
		_frame = 0;
	}
	GameManager(){
		SetStage(Load);
	}
	Vector GenerateRandomPos(int restrictArea);
	bool IsInScreen(Vector pos , int restrictArea = 64){
		if (pos.x >= restrictArea &&
			pos.x <= 640 - restrictArea &&
			pos.y >= restrictArea &&
			pos.y <= 480 - restrictArea){
			return true;
		}
		else{
			return false;
		}
	}
	void GenerateRandomMap(int correctMirrorNum, int DummyMirrorNum);
};