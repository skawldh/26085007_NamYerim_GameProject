#pragma once

#include <Windows.h>
#include <cstdlib> 
#include <ctime> 
#include "glc2d.h"
#include "Piece.h"

enum class RPSChoice
{
    NONE = -1,
    SCISSORS = 0, 
    ROCK = 1,     
    PAPER = 2     
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

    // 가위 바위 보 마우스 클릭 
    POINT m_mousePos; 
    bool m_isLButtonDown;
    bool m_prevLButtonDown;

    RECT m_rtScissors;
    RECT m_rtRock;
    RECT m_rtPaper;

    // 카운트 숫자 이미지
    int m_txCount1 = -1;
    int m_txCount2 = -1;
    int m_txCount3 = -1;

    int m_aiChoice;        // 컴퓨터가 뽑은 카드 (0: 가위, 1: 바위, 2: 보)
    int m_txComScissors;   // 컴퓨터 가위 텍스처
    int m_txComRock;       // 컴퓨터 바위 텍스처
    int m_txComPaper;      // 컴퓨터 보 텍스처

    //말 이미지
    int m_txPiece = -1;
    
    Piece m_younghee;
    Piece m_cheolsoo;

    //영희 철수 승리 프로필 이미지
    int m_txYoungheeWin = -1;
    int m_txCheolsooWin = -1;

    int m_turnWinner = 0;   // 0: 무승부, 1: 플레이어(영희) 승, 2: 컴퓨터(철수) 승
    bool m_moved = false;   // 이번 턴에 말을 이미 움직였는지 (중복 이동 방지)


    // 게임 진행 상태 변수
    bool m_isEvaluating = false;  // 카운트 진행 중인지
    bool m_isGameOver = false;    

    int m_countdown = 0;       
    int m_countdownTimer = 0;   

    ULONGLONG m_turnStartTime = 0;

    RPSChoice m_playerChoice = RPSChoice::NONE; // 플레이어 선택

    // 키 중복 입력 방지
    bool m_prevKey1 = false;
    bool m_prevKey2 = false;
    bool m_prevKey3 = false;

 /*------------------------
    // 0번(영희 아웃)부터 10번(철수 아웃)까지 총 11개의 '돌 사이' X 좌표
    const int m_stoneX[11] = { 132, 197, 262, 327, 392, 457, 522, 587, 652, 717, 782 };
    const int m_stoneY = 400;

-------------------------
*/
    const int m_stoneX[11] = { 40, 110, 190, 260, 335, 405, 480, 550, 620, 690, 760 };
    const int m_stoneY = 390;

    //결과 화면에 승패 전달용
    bool GetPlayerWin() const 
    { 
        return m_younghee.GetPosition() >= 10; 
    }
};
