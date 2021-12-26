#ifndef INIT_H
#define INIT_H

#include "defs.h"
#include "utils.h"

/**
 @brief SDL 초기화

 @remark 전역변수  \ref app에 접근한다.

 @return 리턴 값 없음
 @ingroup Init
*/
void InitSDL(void);





/**
 @brief SDL 종료

 @remark 전역변수  \ref app에 접근한다.

 @return 리턴 값 없음
 @ingroup Init
*/
void QuitSDL(int flag);





/**
 @brief 구조체 용량에 맞는 메모리 할당

 게임을 구성하는 전체 구조체 용량에 맞는 메모리를 할당한다.

 @remark 전체 구조체 전역변수에 접근한다.

 @return 리턴 값 없음
 @ingroup Init
*/
void InitMemorySet(void);


/**
 @brief 배경 초기화

 \ref board 형식 배경의 위치와 텍스처를 입력된 방을 이동함에 따라 초기화한다.
 각 객체의 너비와 높이는 텍스쳐 정보를 바탕으로 \ref Draw 모듈의 함수에서 일괄
 계산하여 반영하므로 별도로 설정하지 않는다.

 @remark 전역변수  \ref app, \ref board 에 접근한다.

 @return 리턴 값 없음
 @ingroup Init
*/
void InitBackGround(int map);


/**
 @brief 플레이어 상태 초기화

 \ref Entity 형식 player의 위치와 텍스처, 체력, 총 소유 여부, 속도를 초기화한다.
 각 객체의 너비와 높이는 텍스쳐 정보를 바탕으로 \ref Draw 모듈의 함수에서 일괄
 계산하여 반영하므로 별도로 설정하지 않는다.

 @remark 전역변수 \ref app, \ref player 에 접근한다.

 @return 리턴 값 없음
 @ingroup Init
*/
void InitPlayer(void);


/**
 @brief 적 상태 초기화

 \ref Entity 형식 enemy의 위치와 텍스처, 체력, 상태이상 여부, 속도를 초기화한다.
 각 객체의 너비와 높이는 텍스쳐 정보를 바탕으로 \ref Draw 모듈의 함수에서 일괄
 계산하여 반영하므로 별도로 설정하지 않는다.

 @remark 전역변수 \ref app, \ref enemy 에 접근한다.

 @return 리턴 값 없음
 @ingroup Init
*/
void InitEnemy(void);


/**
 @brief 장애물(못) 상태 초기화

 \ref Entity 형식 screw의 위치와 텍스처, 체력을 초기화한다.
 각 객체의 너비와 높이는 텍스쳐 정보를 바탕으로 \ref Draw 모듈의 함수에서 일괄
 계산하여 반영하므로 별도로 설정하지 않는다.

 @remark 전역변수 \ref app, \ref screw 에 접근한다.

 @return 리턴 값 없음
 @ingroup Init
*/
void InitScrew(void);


/**
 @brief 장애물(벽난로 불) 상태 초기화

 \ref Entity 형식 fire의 위치와 텍스처, 체력을 초기화한다.
 각 객체의 너비와 높이는 텍스쳐 정보를 바탕으로 \ref Draw 모듈의 함수에서 일괄
 계산하여 반영하므로 별도로 설정하지 않는다.

 @remark 전역변수 \ref app, \ref fire 에 접근한다.

 @return 리턴 값 없음
 @ingroup Init
*/
void InitFire(void);


/**
 @brief 장애물(덫) 상태 초기화

 \ref Entity 형식 trap의 위치와 텍스처, 체력을 초기화한다.
 각 객체의 너비와 높이는 텍스쳐 정보를 바탕으로 \ref Draw 모듈의 함수에서 일괄
 계산하여 반영하므로 별도로 설정하지 않는다.

 @remark 전역변수 \ref app, \ref trap 에 접근한다.

 @return 리턴 값 없음
 @ingroup Init
*/
void InitTrap(void); 


/**
 @brief 장애물(선인장) 상태 초기화

 \ref Entity 형식 cactus의 위치와 텍스처, 체력을 초기화한다.
 각 객체의 너비와 높이는 텍스쳐 정보를 바탕으로 \ref Draw 모듈의 함수에서 일괄
 계산하여 반영하므로 별도로 설정하지 않는다.

 @remark 전역변수 \ref app, \ref cactus 에 접근한다.

 @return 리턴 값 없음
 @ingroup Init
*/
void InitCactus(void); 


/**
 @brief 장애물(거미) 상태 초기화

 \ref Entity 형식 spider의 위치와 텍스처, 체력, 속도를 초기화한다.
 각 객체의 너비와 높이는 텍스쳐 정보를 바탕으로 \ref Draw 모듈의 함수에서 일괄
 계산하여 반영하므로 별도로 설정하지 않는다.

 @remark 전역변수 \ref app, \ref spider 에 접근한다.

 @return 리턴 값 없음
 @ingroup Init
*/
void InitSpider(void);


/**
 @brief 장애물(끈끈한 바닥) 상태 초기화

 \ref Entity 형식 stickyfloor의 위치와 텍스처를 초기화한다.
 각 객체의 너비와 높이는 텍스쳐 정보를 바탕으로 \ref Draw 모듈의 함수에서 일괄
 계산하여 반영하므로 별도로 설정하지 않는다.

 @remark 전역변수 \ref app, \ref stickyfloor 에 접근한다.

 @return 리턴 값 없음
 @ingroup Init
*/
void InitStickyfloor(void); 


/**
 @brief 아이템(샷건) 상태 초기화

 \ref Entity 형식 shotgun의 위치와 텍스처, 체력을 초기화한다.
 각 객체의 너비와 높이는 텍스쳐 정보를 바탕으로 \ref Draw 모듈의 함수에서 일괄
 계산하여 반영하므로 별도로 설정하지 않는다.

 @remark 전역변수 \ref app, \ref shotgun 에 접근한다.

 @return 리턴 값 없음
 @ingroup Init
*/
void InitShotgun(void); 


/**
 @brief 보드 초기화

 \ref board 형식 보드의 위치와 텍스처를 입력된 정수 따라 초기화한다.
 보드는 퍼즐 보드를 출력하거나 물체와 상호작용 시 텍스트나 그림을 출력하는 데 사용된다.

 [1]: 논리회로퍼즐 1, [2]: 논리회로퍼즐 2, [3]: 논리회로퍼즐 3
 [4]: 도구 획득 시 텍스트, [5]: 키패드 퍼즐 [6]: 달력 조사 시 그림
 [7]: 시체 조사 시 텍스트, [8]: 창문 조사 시 텍스트, [9]: 낙서 조사 시 그림
 [10]: 도구 필요 시 텍스트,  [11]: 전원 필요 시 텍스트 [12]: 열쇠 필요 시 텍스트
 [13]: 열쇠 획득 시 텍스트

 각 객체의 너비와 높이는 텍스쳐 정보를 바탕으로 \ref Draw 모듈의 함수에서 일괄
 계산하여 반영하므로 별도로 설정하지 않는다.

 @remark 전역변수  \ref app, \ref board 에 접근한다.

 @return 리턴 값 없음
 @ingroup Init
*/
void InitBoard(int);


/**
 @brief 상호작용 가능한 물체 상태 초기화

 \ref 맵에 따라 Entity 형식 interactiveobj[]의 위치와 텍스처를 초기화한다.
 각 객체의 너비와 높이는 텍스쳐 정보를 바탕으로 \ref Draw 모듈의 함수에서 일괄
 계산하여 반영하므로 별도로 설정하지 않는다.
 [0]: 수리 도구, [1]: 논리회로퍼즐 1, [2]: 논리회로퍼즐 2, [3]: 논리회로퍼즐 3
 [4]: 키패드, [5]: 달력, [6]: 시체, [7]: 창문, [8]: 낙서, [9]: 출구
 [10]: 적 시체

 @remark 전역변수 \ref app, \ref interactobj 에 접근한다.

 @return 리턴 값 없음
 @ingroup Init
*/
void InitInteractObj(void); // button[0] Power button, button[1] Reset button


/**
 @brief 퍼즐 버튼 초기화

 \ref Puzzle타입 power 버튼과 Reset 버튼 의 텍스쳐를 불러오고 위치를 초기화한다.
 각 객체의 너비와 높이는 텍스쳐 정보를 바탕으로 \ref Draw 모듈의 함수에서 일괄
 계산하여 반영하므로 별도로 설정하지 않는다.

 @remark 전역변수  \ref app, \ref button 에 접근한다.

 @return 리턴 값 없음
 @ingroup Init
*/
void InitButton(void);


/**
 @brief 퍼즐 게이트 칩 초기화

 \ref Puzzle타입 게이트 칩의 텍스쳐를 불러오고 게이트의 위치와 원래 위치, 종류를 초기화한다.
 각 객체의 너비와 높이는 텍스쳐 정보를 바탕으로 \ref Draw 모듈의 함수에서 일괄
 계산하여 반영하므로 별도로 설정하지 않는다.
 [0]: Andgate,  [1]: Orgate,  [2]: Xorgate,  [3]: Buffergate
 [4]: Nandgate, [5]: Norgate, [6]: Xnorgate, [7]: Notgate

 @remark 전역변수  \ref app, \ref puzzle 에 접근한다.

 @return 리턴 값 없음
 @ingroup Init
*/
void InitGate(void);


/**
 @brief 퍼즐 게이트 슬롯 초기화

 \ref 정수를 입력받아 해당 stage에 맞는 Puzzle타입 슬롯의 텍스쳐를 불러오고 위치를 초기화한다.
 각 객체의 너비와 높이는 텍스쳐 정보를 바탕으로 \ref Draw 모듈의 함수에서 일괄
 계산하여 반영하므로 별도로 설정하지 않는다.

 @remark 전역변수  \ref app, \ref puzzle 에 접근한다.

 @return 리턴 값 없음
 @ingroup Init
*/
void InitSlot(int stage);


/**
 @brief 퍼즐 리시버 초기화

 \ref Receiver타입 리시버의 상태와 위치를 입력받아 텍스쳐를 불러오고 위치를 초기화한다.
 status1 : right, status2 : wrong
 각 객체의 너비와 높이는 텍스쳐 정보를 바탕으로 \ref Draw 모듈의 함수에서 일괄
 계산하여 반영하므로 별도로 설정하지 않는다.

 @remark 전역변수  \ref app, \ref receiver 에 접근한다.

 @return 리턴 값 없음
 @ingroup Init
*/
void InitReceiver(int status,int index,int x,int y);


/**
 @brief 키패드 퍼즐 keybutton 초기화

 \ref App 타입 app의 패스코드를 -1로 초기화한 뒤
 \ref KeyButton 타입 keybutton의 텍스쳐를 불러오고 위치를 초기화한다.
keybutton[0]~[9] : 0~9, keybutton[10] : 입력 취소, keybutton[11] : 입력
 각 객체의 너비와 높이는 텍스쳐 정보를 바탕으로 \ref Draw 모듈의 함수에서 일괄
 계산하여 반영하므로 별도로 설정하지 않는다.

 @remark 전역변수  \ref app, \ref keybutton 에 접근한다.

 @return 리턴 값 없음
 @ingroup Init
*/
void InitKeyButton(void);

/**
 @brief 게임 오버 화면 상태 초기화

 \ref Entity 타입 game_over의 텍스쳐를 불러오고 위치를 초기화한다.
 각 객체의 너비와 높이는 텍스쳐 정보를 바탕으로 \ref Draw 모듈의 함수에서 일괄
 계산하여 반영하므로 별도로 설정하지 않는다.

 @remark 전역변수  \ref app, \ref game_over 에 접근한다.

 @return 리턴 값 없음
 @ingroup Init
*/
void InitGameOver(void);


/**
 @brief 게임 엔드 화면 상태 초기화

 \ref Entity 타입 game_end의 텍스쳐를 불러오고 위치를 초기화한다.
 각 객체의 너비와 높이는 텍스쳐 정보를 바탕으로 \ref Draw 모듈의 함수에서 일괄
 계산하여 반영하므로 별도로 설정하지 않는다.

 @remark 전역변수  \ref app, \ref game_end 에 접근한다.

 @return 리턴 값 없음
 @ingroup Init
*/
void InitGameEnd(void);



#endif