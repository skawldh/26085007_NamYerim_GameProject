#pragma once

#include <Windows.h>
#include <cstdlib> 
#include <ctime> 
#include "glc2d.h"
#include "Piece.h"

enum class RPSChoice
{
    NONE = -1,
    SCISSORS = 0, // 가위
    ROCK = 1,     // 바위
    PAPER = 2     // 보
};

class SceneGamePlay
{
public:
    int Init();                                
    int Destroy();                               
    int Update(const KEYCODE* keys = nullptr);  
    int Render();                              

    void ResetGame();                            

private:
    bool IsKeyPressed(int key);                  // 키 입력 확인해주는 애
    void StartTurn(RPSChoice playerChoice);     // 키 눌렀을 때 3초 카운트 시작
    void FinishTurn();                           // rand() 후 승패 결과에 따라 말 이동

private:
    int m_txBackground = -1;     // 배경

    // 가위, 바위, 보 기본 버튼
    int m_txScissors = -1;
    int m_txRock = -1;
    int m_txPaper = -1;

    // 가위, 바위, 보 눌림버튼
    int m_txScissorsHover = -1;
    int m_txRockHover = -1;
    int m_txPaperHover = -1;

    // 카운트 숫자 이미지
    int m_txCount1 = -1;
    int m_txCount2 = -1;
    int m_txCount3 = -1;

    //말 이미지
    int m_txPiece = -1;
    
    Piece m_younghee;
    Piece m_cheolsoo;

    // 게임 진행 상태 변수
    bool m_isEvaluating = false;  // 카운트 진행 중인지
    bool m_isGameOver = false;    

    int m_countdown = 0;       
    int m_countdownTimer = 0;   

    RPSChoice m_playerChoice = RPSChoice::NONE; // 플레이어 선택

    // 키 중복 입력 방지
    bool m_prevKey1 = false;
    bool m_prevKey2 = false;
    bool m_prevKey3 = false;

    // 징검다리 돌 1~10번 X 좌표
    const int m_stoneX[10] = { 100, 168, 236, 304, 372, 440, 508, 576, 644, 712 };
    const int m_stoneY = 395;
};