#ifndef ACTION_H
#define ACTION_H

#include "init.h"
#include "defs.h"
#include "utils.h"


/*----------------------------------------------ActGame--------------------------------------------- */

/**
 @brief 이동 및 탐색, 전투 중일 시 필요한 액션을 순차적으로 수행

 이동 및 탐색, 전투 중인 경우에 수행하는 액션을 모두 모아 순차적으로 실행하는 함수이다.
 main()함수에서 호출한다.

 @return 리턴 값 없음
 @ingroup Action
*/
void ActGame(void);


/**
 @brief 플레이어와 적 사이의 거리와 각도 측정해 app 구조체에 저장

 플레이어와 적 사이의 거리와 각도를 측정해 app 구조체에 저장하는 함수이다.
 ActGame()함수에서 호출한다.

 @return 리턴 값 없음
 @ingroup Action
*/
void RelativePos(void);

/**
 @brief 플레이어의 움직임을 실행하는 함수이다. 플레이어의 이동, 벽과의 충돌, 샷건의 발사 동작등을 시행한다.

 플레이어의 움직임을 실행하는 함수이다. 플레이어의 이동, 벽과의 충돌, 샷건의 발사 동작등을 시행한다.
 ActGame()함수에서 호출한다.

 @return 리턴 값 없음
 @ingroup Action
*/
void ActPlayer(void);

/**
 @brief 적의 움직임을 실행하는 함수이다. 적의 사망 판정, 플레이어 추적 동작을 시행한다.
 
 적의 움직임을 실행하는 함수이다. 적의 사망 판정, 플레이어 추적 동작을 시행한다.
 ActGame()함수에서 호출한다.

 @return 리턴 값 없음
 @ingroup Action
*/
void ActEnemy(void);    

/**
 @brief 적과 못의 충돌여부를 판단하는 함수이다. 충돌 시 적의 체력을 깎고 사라진다.
 
 못과 적의 충돌여부를 판단하는 함수이다. 충돌 시 적의 체력을 깎고 사라진다.
 ActGame()함수에서 호출한다.

 @return 리턴 값 없음
 @ingroup Action
*/
void ScrewUsed(void);    

/**
 @brief 적과 벽난로 불의 충돌여부를 판단하는 함수이다. 충돌 시 적의 체력과 속도를 깎고 상태를 변화시킨 뒤 사라진다.
 
 적과 벽난로 불의 충돌여부를 판단하는 함수이다. 충돌 시 적의 체력과 속도를 깎고 상태를 변화시킨 뒤 사라진다.
 ActGame()함수에서 호출한다.

 @return 리턴 값 없음
 @ingroup Action
*/
void FireUsed(void);      

/**
 @brief 적과 선인장의 충돌여부를 판단하는 함수이다. 충돌 시 적의 체력을 깎고 속도를 증가시킨 뒤 모습을 바꾼다.
 
 적과 선인장의 충돌여부를 판단하는 함수이다. 충돌 시 적의 체력을 깎고 속도를 증가시킨 뒤 모습을 바꾼다.
 ActGame()함수에서 호출한다.

 @return 리턴 값 없음
 @ingroup Action
*/
void CactusUsed(void);     

/**
 @brief 거미의 움직임을 제어하는 함수이다. 일정 범위 내에서 랜덤하게 움직이고 벽과 충돌하면 방향을 바꾼다.
 
거미의 움직임을 제어하는 함수이다. 플레이어가 일정 거리 이상 다가가면 활성화되어
일정 범위 내에서 랜덤하게 움직이고 벽과 충돌하면 방향을 바꾼다.
 ActGame()함수에서 호출한다.

 @return 리턴 값 없음
 @ingroup Action
*/
void SpiderMovement(void);  

/**
 @brief 적과 덫의 충돌여부를 판단하는 함수이다. 충돌 시 적의 체력을 깎은 뒤 비활성화하고 모습을 바꾼다.
 
적과 덫의 충돌여부를 판단하는 함수이다. 충돌 시 적의 체력을 깎은 뒤 비활성화하고 모습을 바꾼다..
ActGame()함수에서 호출한다.

 @return 리턴 값 없음
 @ingroup Action
*/
void TrapUsed(void);  

/**
 @brief 적과 끈끈한 바닥의 충돌여부를 판단하는 함수이다. 바닥 위에 있을 시 플레이어의 속도를 느리게 한다.
 
적과 끈끈한 바닥의 충돌여부를 판단하는 함수이다. 충돌 시 플레이어의 속도를 느리게 하며,
바닥을 벗어날 시 원래 속도로 돌아온다.
ActGame()함수에서 호출한다.

 @return 리턴 값 없음
 @ingroup Action
*/
void Onthefloor(void);

/**
 @brief 플레이어 오브젝트와 샷건 오브젝트의 충돌여부를 판단하고, 소지 여부를 판단하는 함수이다.
 
플레이어 오브젝트와 샷건 오브젝트의 충돌여부를 판단하고, 소지 여부를 판단하는 함수이다.
상자 안에 있는 샷건에 접근할 시, player 변수 안의 gun 멤버를 1로 설정하고, 총이 플레이어를 따라다니도록 한다.
ActGame()함수에서 호출한다.

 @return 리턴 값 없음
 @ingroup Action
*/
void ShotgunUse(void);   

/**
 @brief 플레이어와 장애물 오브젝트의 충돌 여부를 검사하는 함수이며, 충돌 시 체력을 0으로 만든다.
 
플레이어와 장애물 오브젝트의 충돌 여부를 검사하는 함수이며, 충돌 시 player.health 멤버를 0으로 만든다.
ActGame()함수에서 호출한다.

 @return 리턴 값 없음
 @ingroup Action
*/
void ActCheckDeath(void);

/**
 @brief 플레이어와 상호 작용 오브젝트의 충돌 여부, 스페이스바 push 여부를 검사하여 코드를 실행하는 함수
 
플레이어와 상호 작용 오브젝트의 충돌 여부, 스페이스바 push 여부를 검사하여 코드를 실행하는 함수이다.
두 조건을 모두 만족할 때 상호작용하는 오브젝트에 따라 아이템 획득, 힌트 제공 등 각기 다른 코드를 실행한다.
 [0]: 수리 도구, [1]: 논리회로퍼즐 1, [2]: 논리회로퍼즐 2, [3]: 논리회로퍼즐 3
 [4]: 키패드, [5]: 달력, [6]: 시체, [7]: 창문, [8]: 낙서, [9]: 출구
 [10]: 적 시체
 [0],[10]은 보드 출력과 아이템 획득, [1]~[3]는 조건에 따라 논리 회로 퍼즐 시작, [4]는 키패드 퍼즐 시작,
 [5]~[8]은 보드 출력, [9]는 조건에 따라 탈출 코드를 실행한다.
ActGame()함수에서 호출한다.

 @return 리턴 값 없음
 @ingroup Action
*/
void ActInteraction(void);

/*************ActGame+***************/

/**
 @brief 외부로부터 int값으로 맵을 받아 해당 맵의 오브젝트를 init하고, 전역변수를 초기화한다.
 
퍼즐 실행여부가 저장되어있는 app.stage 멤버를 0으로 초기화하고, 입력받은 map에 따라 다음 함수를 실행한다.

map == 1
배경 init, 플레이어 init, 상호작용 object init, tool 소유 여부 및 수리 진행도 초기화

map == 2
배경 init, 플레이어 init, 적 init, 장애물 init, 상호작용 object clear, 열쇠 소유여부 초기화

main(), ActGameOverScreen(), ActKeypress() 함수에서 호출한다.

 @return 리턴 값 없음
 @ingroup Action
*/
void ActInitmap(int map);


/**
 @brief 적 사망 시 적을 상호작용 가능한 적 시체로 대체한다.
 
적 사망 시 적을 상호작용 가능한 적 시체로 대체한다.
ActEnemy() 함수에서 호출한다.

 @return 리턴 값 없음
 @ingroup Action
*/
void ActEnemyDie(void);


/*----------------------------------------------ActPuzzle--------------------------------------------- */

/**
 @brief 퍼즐 진행 중일 시 필요한 액션을 순차적으로 수행

 퍼즐이 진행 중인 경우에 수행하는 액션을 모두 모아 순차적으로 실행하는 함수이다.
 main()함수에서 호출한다.

 @return 리턴 값 없음
 @ingroup Action
*/
void ActPuzzle(void);

/**
 @brief 퍼즐 진행 중 리셋버튼 클릭 시 액션

 퍼즐이 진행 중인 경우에 리셋버튼을 클릭했을 시 스테이지를 재시작하는 함수이다.
 ActPuzzle()함수에서 호출한다.

 @return 리턴 값 없음
 @ingroup Action
*/
void ActReset(void);

/**
 @brief 퍼즐 진행 중 마우스 이용 게이트 조작

 퍼즐이 진행 중인 경우에 게이트 칩을 좌클릭 및 드래그하여 이동 및 슬롯에 배치, 우클릭 시 이동을 취소하는 함수이다.
 ActPuzzle()함수에서 호출한다.

 @return 리턴 값 없음
 @ingroup Action
*/
void ActPickGate(void);

/**
 @brief 퍼즐 진행 중 파워버튼 클릭 시 액션

 퍼즐이 진행 중인 경우에 파워버튼을 클릭했을 시 스테이지와 슬롯에 배치된 게이트에 따른 정답 여부를 화면에 출력하는 함수이다.
 ActPuzzle()함수에서 호출한다.

 @return 리턴 값 없음
 @ingroup Action
*/
void ActPower(void);


/**
 @brief 논리 회로 또는 키패드 퍼즐 실행 중 ESC 키 입력 시 퍼즐을 종료하는 함수

논리 회로 또는 키패드 퍼즐 실행 중 ESC 키 입력 시 해당 퍼즐을 종료한다.
퍼즐에 해당하는 object를 clear하고, 맵 1으로 다시 돌아간다.
ActPuzzle(), ActKeypad() 함수에서 호출한다.

 @return 리턴 값 없음
 @ingroup Action
*/
void ActEsc(void);

/*************ActPuzzle+***************/


/**
 @brief  입력된 스테이지를 시작

 함수 호출 또는 reset버튼 클릭 시 입력된 스테이지를 시작, Init 함수를 통해 보드, 파워버튼, 리셋버튼, 게이트, 슬롯을 init하는 함수이다.
 ActInteraction(), ActReset()함수에서 호출한다.

 @return 리턴 값 없음
 @ingroup Action
*/
void ActInitstage(int stage);


/**
 @brief 파워버튼 클릭 시 정답판별

 퍼즐이 진행 중인 경우에 파워버튼이 눌렸을 시 실행되어 인자로 받은 스테이지와 슬롯 상태에 따라 InitReceiver 함수를 통해 정답 여부를 화면에 출력하는 함수이다.
 ActPower()함수에서 호출한다.

 @return 리턴 값 없음
 @ingroup Action
*/
void PowerOn(int stage);


/*----------------------------------------------ActKeypad--------------------------------------------- */

/**
 @brief 마우스로 키패드 번호 입력받는 함수 ActKeypad

 마우스로 키패드 번호 입력받는 함수 ActKeypad이다. ActKeypad에서 클릭 여부를 판정하고 번호를 입력한다.
 esc 입력 시 퍼즐을 종료한다.
 main() 함수에서 호출한다.

 @return 리턴 값 없음
 @ingroup Action
*/
void ActKeypad(void);

/**
 @brief 마우스로 키패드 번호 입력받는 함수 ActKeypad

 마우스로 키패드 번호 입력받는 함수 ActKeypad이다. ActKeypad에서 클릭 여부를 판정하고 번호를 입력한다.
 esc 입력 시 퍼즐을 종료한다.
 ActKeypad()함수에서 호출한다.

 @return 리턴 값 없음
 @ingroup Action
*/
void ActKeypress(int key);


/*************ActKeypad+***************/

/**
 @brief 키패드와 버튼을 초기화하는 함수이다.

 키패드와 버튼을 초기화하는 함수이다.
 ActInteraction()함수에서 호출한다.

 @return 리턴 값 없음
 @ingroup Action
*/
void ActInitkeypad(void);



/*----------------------------------------------GameOver/End--------------------------------------------- */

/**
 @brief 게임오버 시의 코드를 실행하는 함수이다.

 게임오버 시의 코드를 실행하는 함수이다.
 게임오버 화면을 출력하고, 사용자로부터 재실행에 대한 입력을 받는다.
 main()함수에서 호출한다.

 @return 리턴 값 없음
 @ingroup Action
*/
void ActGameOver(void);

/**
 @brief 게임오버 시에 사용자로부터 입력을 받아 맵을 재실행하는 함수이다.

 게임오버 시에 사용자로부터 입력을 받아 맵을 재실행하는 함수이다.
 r 입력 시 두번째 맵을 초기화하여 다시 실행한다.
 ActGameOver()함수에서 호출한다.

 @return 리턴 값 없음
 @ingroup Action
*/
void ActGameOverScreen(void);


/**
 @brief 게임클리어 시의 코드를 실행하는 함수이다.

 게임클리어 시의 코드를 실행하는 함수이다.
 게임클리어 화면을 출력하고, 사용자로부터 프로그램 종료 대한 입력을 받는다.
 main()함수에서 호출한다.

 @return 리턴 값 없음
 @ingroup Action
*/
void ActGameEnd(void);


/**
 @brief 게임클리어 시에 사용자로부터 입력을 받아 프로그램을 종료하는 함수이다.

 게임클리어 시에 사용자로부터 입력을 받아 프로그램을 종료하는 함수이다.
 ESC 입력을 받아 SDL_Quit(),  exit(0) 코드를 통해 프로그램을 종료한다.
 ActGameEnd()함수에서 호출한다.

 @return 리턴 값 없음
 @ingroup Action
*/
void ActGameEndScreen(void);



#endif