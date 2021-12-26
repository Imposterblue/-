
#ifndef MAIN_H
#define MAIN_H

#include "defs.h"
#include "init.h"
#include "input.h"
#include "action.h"
#include "draw.h"


/*사용하는 전역 변수*/
/// @ingroup GlobalVariables
App app;                        /**< 프로그램 전체 단위로 관리하는 전역 객체 모음 */


/* 플레이어와 적 */
/// @ingroup GlobalVariables
Entity player;                  /**< 주인공의 속성과 상태를 설명하는 Entity형 구조체 */
/// @ingroup GlobalVariables
Entity enemy;                   /**< 적의 속성과 상태를 설명하는 Entity형 구조체 */


/* 장애물 */
/// @ingroup GlobalVariables
Entity screw;                   /**< 벽에 박힌 못 설명하는 Entity형 구조체 */
/// @ingroup GlobalVariables
Entity fire;                    /**< 벽난로의 불꽃 설명하는 Entity형 구조체 */
/// @ingroup GlobalVariables
Entity cactus;                  /**< 선인장 설명하는 Entity형 구조체 */
/// @ingroup GlobalVariables
Entity spider;                  /**< 거미 설명하는 Entity형 구조체 */
/// @ingroup GlobalVariables
Entity stickyfloor;             /**< 속도 줄이는 바닥 설명하는 Entity형 구조체 */
/// @ingroup GlobalVariables
Entity trap;                    /**< 덫 설명하는 Entity형 구조체 */

/* 무기 */
/// @ingroup GlobalVariables
Entity shotgun;                 /**< 샷건 설명하는 Entity형 구조체 */


/* 상호작용하는 물체 */
/// @ingroup GlobalVariables
Entity interact_obj[11];        /**< 상호작용 가능한 물체 설명하는 Entity형 구조체 */


/* 힌트 메시지 */
/// @ingroup GlobalVariables
Board calendar;                 /**< 달력 이미지 설명하는 Board형 구조체 */
/// @ingroup GlobalVariables
Board window;                   /**< 창문 메시지 설명하는 Board형 구조체 */
/// @ingroup GlobalVariables
Board mark;                     /**< 낙서 메시지 설명하는 Board형 구조체 */
/// @ingroup GlobalVariables
Board corpse_text;              /**< 주검 메시지 설명하는 Board형 구조체 */
/// @ingroup GlobalVariables
Board tool_get;                 /**< 도구 획득 메시지 설명하는 Board형 구조체 */
/// @ingroup GlobalVariables
Board key_get;                  /**< 열쇠 획득 메시지 설명하는 Board형 구조체 */
/// @ingroup GlobalVariables
Board power_need;               /**< 전원 필요 메시지 설명하는 Board형 구조체 */
/// @ingroup GlobalVariables
Board tool_need;                /**< 도구 필요 메시지 설명하는 Board형 구조체 */
/// @ingroup GlobalVariables
Board key_need;                  /**< 열쇠 필요 메시지 설명하는 Board형 구조체 */

/* 논리회로 퍼즐 */
/// @ingroup GlobalVariables
Board board;                        /**< Puzzle 내 background를 설명하는 Board형 구조체 */
/// @ingroup GlobalVariables
Puzzle button[MAX_BUTTON];          /**< Puzzle 내 각종 버튼을 설명하는 Puzzle형 구조체 */
/// @ingroup GlobalVariables
Puzzle gate[MAX_GATE];              /**< Puzzle 내 논리 게이트 칩을 설명하는 Puzzle형 구조체 */
/// @ingroup GlobalVariables
Puzzle slot[MAX_SLOT];              /**< Puzzle 내 논리 게이트 칩 슬롯을 설명하는 Puzzle형 구조체 */
/// @ingroup GlobalVariables
Receiver receiver[MAX_RECEIVER];    /**< 게임 내 코드 입력부를 설명하는 Receiver형 구조체 */


/* 키패드 퍼즐 */
/// @ingroup GlobalVariables
Board keypad;                       /**< 키패드 상태 설명하는 Board형 구조체 */
/// @ingroup GlobalVariables
KeyButton keybutton[12];            /**< 키패드 버튼 설명하는 KeyButton형 구조체 */


/* 이외의 전역변수들 */
/// @ingroup GlobalVariables
Entity game_over;                   /**< 게임오버 화면의 속성을 설명하는 Entity형 구조체 */
/// @ingroup GlobalVariables
Entity game_end;                   /**< 게임종료 화면의 속성을 설명하는 Entity형 구조체 */
/// @ingroup GlobalVariables
Board background;                   /**< 게임 뒷배경 설명하는 Board형 구조체 */

#endif