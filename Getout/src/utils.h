#ifndef UTILS_H
#define UTILS_H

#include "defs.h"

/* main.h에 정의된 전역 변수 사용 */
extern App app;

extern Board background;

extern Entity player;
extern Entity enemy;

extern Entity screw;
extern Entity fire;
extern Entity trap;
extern Entity cactus;
extern Entity spider;
extern Entity stickyfloor;
extern Entity shotgun;;

extern Board calendar;
extern Board window;
extern Board mark;
extern Board corpse_text;
extern Board power_need;
extern Board tool_need;
extern Board key_need;
extern Board tool_get;
extern Board key_get;

extern Entity interact_obj[11];

extern Board board;
extern Puzzle button[MAX_BUTTON];
extern Puzzle gate[MAX_GATE];
extern Puzzle slot[MAX_SLOT];
extern Receiver receiver[MAX_RECEIVER];

extern Board keypad;
extern KeyButton keybutton[12];

extern Entity game_over;
extern Entity game_end;


/**
 @brief Entity 포인터를 입력받아 해당 Entity가 벽에 충돌했는지 여부를 검사하는 함수.

 @param[in] object 벽과의 충돌을 검사할 Entity

 @return 0 (충돌안함), 1, 2(충돌함)
 @ingroup Utils
*/
int CheckCollisionWall(Entity *object);

/**
 @brief 두 개의 Entity 포인터를 입력받아 해당 Entity가 서로 충돌했는지 여부를 검사하는 함수.

 @param[in] object_a 충돌을 검사할 Entity

 @param[in] object_b 충돌을 검사할 Entity

 @return 0 (충돌안함), 1(충돌함)
 @ingroup Utils
*/
int CheckCollisionObjects(Entity *object_a, Entity *object_b);

/**
 @brief 두 개의 정수를 입력받아 그 사이의 랜덤 정수값을 return하는 함수

 @param[in] min_val return할 최소값

 @param[in] object_b return할 최대값

 @return 랜덤한 정수값
 @ingroup Utils
*/
int RandInt(int min_val, int max_val);

/**
 @brief 두 개의 실수를 입력받아 그 사이의 랜덤 실수값을 return하는 함수

 @param[in] min_val return할 최소값

 @param[in] object_b return할 최대값

 @return 랜덤한 실수값
 @ingroup Utils
*/
double RandDouble(double min_val, double max_val);

/**
 @brief 두 개의 이차원 좌표를 입력받아 그 사이의 거리값을 실수형태로 return하는 함수

 @param[in] x1 첫번째 지점 x좌표
 @param[in] y1 첫번째 지점 y좌표

 @param[in] x2 두번째 지점 x좌표
 @param[in] y2 두번째 지점 y좌표

 @return 두 지점 사이의 거리 실수값
 @ingroup Utils
*/
double Distance (double x1, double y1, double x2, double y2);

/**
 @brief gate 종류와 입력신호를 받아 출력신호를 출력하는 함수. 신호목록은 defs.h 참조.

 @param[in] gate 논리게이트 종류. 1:AND, 2:OR, 3:XOR, 4:Buffer, 5:NAND, 6:NOR, 7:XNOR, 8:NOT
 
 @param[in] input1 input신호가 2개인 게이트의 첫번째 입력
 @param[in] input2 input신호가 2개인 게이트의 두번째 입력

 @param[in] input3 input신호가 1개인 게이트(Buffer, Not)의 입력

 @return 출력신호
 @ingroup Utils
*/
int Logic (int gate, int input1, int input2, int input3);


/**
 @brief Entity 포인터를 입력받아 해당 엔티티를 화면에서 없애는 함수

 @param[in] entity 없애고자 하는 entity

 @return void
 @ingroup Utils
*/
void ClearEntity(Entity* entity);

/**
 @brief Board 포인터를 입력받아 해당 보드를 화면에서 없애는 함수

 @param[in] board 없애고자 하는 board

 @return void
 @ingroup Utils
*/
void ClearBoard(Board* board);

/**
 @brief 퍼즐 구성요소들을 화면에서 없애는 함수

 @param[in] void

 @return void
 @ingroup Utils
*/
void ClearPuzzle(void);

/**
 @brief Keypad를 화면에서 없애는 함수

 @param[in] void

 @return void
 @ingroup Utils
*/
void ClearKeypad(void);


#endif