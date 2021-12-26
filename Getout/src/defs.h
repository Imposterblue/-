
#ifndef DEFS_H
#define DEFS_H

#include "ctype.h"
#include "math.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "time.h"

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

/*상수 매크로 정의*/

#define SCREEN_WIDTH 1400    /**< 화면 너비(픽셀)*/
#define SCREEN_HEIGHT 800   /**< 화면 높이(픽셀)*/

#define WALL_THICKNESS1 200  /**< 첫 번째 방 벽 두께(픽셀)*/ 
#define WALL_THICKNESS2 100  /**< 두 번째 방 벽 두께(픽셀)*/

#define ENEMY_WIDTH 48      /**< 적 객체 높이(픽셀)*/
#define ENEMY_HEIGHT 48     /**< 적 객체 높이(픽셀)*/

#define PLAYER_SPEED 7      /**< 플레이어 객체 속도(단위시간당 이동량)*/   
#define ENEMY_SPEED 4       /**< 적 객체 속도(단위시간당 이동량)*/   


/* 장애물 */
#define SCREW_WIDTH 8        /**< 장애물[못] 너비*/   
#define SCREW_HEIGHT 20      /**< 장애물[못] 높이*/

#define FIRE_WIDTH 90        /**< 장애물[벽난로 불] 너비*/
#define FIRE_HEIGHT 45       /**< 장애물[벽난로 불] 높이*/

#define SPIDER_SPEED 3       /**< 장애물[거미] 속도*/


/* 샷건 */

#define SHOTGUN_TERM 30      /**< 샷건 쿨타임(프레임)*/
#define SHOTGUN_RANGE 300    /**< 샷건 범위(픽셀)*/
#define SHOTGUN_POWER 190    /**< 샷건 넉백 거리(픽셀)*/


/* 논리 게이트 퍼즐 */
#define PUZZLE_X 100      /**< 전체 화면 위 퍼즐 x좌표(픽셀)*/
#define PUZZLE_Y 100      /**< 전체 화면 위 퍼즐 y좌표(픽셀)*/

#define MAX_BUTTON 2     /**< 최대 버튼 개수*/
#define MAX_GATE 8         /**< 최대 Gate 개수*/
#define MAX_SLOT 8          /**< 최대 Slot 개수*/
#define MAX_RECEIVER 6      /**< 최대 Receiver 개수*/

#define SIGNAL_UNDEFINED 0 /**< 정의되지 않은 신호 상수*/
#define SIGNAL_0 -1         /**< 0 신호 상수*/
#define SIGNAL_1 1          /**< 1 신호 상수*/
#define SIGNAL_A 2          /**< A 신호 상수*/
#define SIGNAL_AP -2        /**< A prime 신호 상수*/
#define SIGNAL_B 3          /**< B 신호 상수*/
#define SIGNAL_BP -3        /**< B prime 신호 상수*/

/* 키패드 퍼즐 */

#define KEYPAD_X 460      /**< 전체 화면 위 키패드 x좌표(픽셀)*/
#define KEYPAD_Y 75       /**< 전체 화면 위 키패드 y좌표(픽셀)*/

#define PASSCODE 723      /**< 비밀번호*/


/* App 구조체 정의 */
typedef struct {

    SDL_Renderer *renderer; /**< 렌더링 관리를 위한 구조체*/
    SDL_Window *window;     /**< 창 관리를 위한 구조체*/

    /* 키보드 입력 */
    int key_up;             /**< 위 방향키(w)가 눌린 상태를 저장하는 변수*/
    int key_down;           /**< 아래 방향키(s)가 눌린 상태를 저장하는 변수*/
    int key_left;           /**< 왼쪽 방향키(a)가 눌린 상태를 저장하는 변수*/
    int key_right;          /**< 오른쪽 방향키(d)가 눌린 상태를 저장하는 변수*/
    int key_r;              /**< R키가 눌린 상태를 저장하는 변수*/
    int key_spacebar;       /**< 스페이스 키가 눌린 상태를 저장하는 변수*/
    int key_esc;            /**< ESC 키가 눌린 상태를 저장하는 변수*/

    int spacebar_pressed;   /**< 스페이스 바 키가 눌렸었는지 여부를 저장하는 변수*/

    /* 마우스 입력 */
    int mouse_left;         /**< 마우스 왼쪽 키가 눌린 상태를 저장하는 변수*/
    int mouse_right;        /**< 마우스 오른쪽 키가 눌린 상태를 저장하는 변수*/

    int mouse_x_before;     /**< 마우스 드래그 시 마우스 클릭 x지점을 저장하는 변수*/
    int mouse_y_before;     /**< 마우스 드래그 시 마우스 클릭 y지점을 저장하는 변수*/
    int mouse_x_current;    /**< 마우스 현재 x좌표를 저장하는 변수*/
    int mouse_y_current;    /**< 마우스 현재 y좌표를 저장하는 변수*/

    int rightcancel;        /**< 마우스 우클릭으로 인해 입력이 취소되었는지 여부를 저장하는 변수*/


    /* 논리 게이트 퍼즐 */
    int stage;              /**< 논리 게이트 퍼즐의 현재 stage를 저장하는 변수*/


    /* 키패드 퍼즐 */
    int keypad_on;          /**< 키패드 실행여부를 저장하는 변수*/
    
    int passcode[4];        /**< 키패드에 입력된 패스코드를 저장하는 변수*/


    /* 방 탐색과 전투 */
    int map;                /**< 현재 플레이어가 있는 맵 저장하는 변수*/

    int tool;               /**< 회로 수리도구 획득 여부를 저장하는 변수*/

    int fix_count;          /**< 논리게이트 퍼즐 클리어 횟수를 저장하는 변수*/
 
    int door_key;           /**< 문 열쇠 획득 여부를 저장하는 변수*/

    int shotgun_reload;     /**< 샷건의 장전 시간(프레임)을 저장하는 변수, 0일 때 발사 가능*/

    int game_clear;         /**< 전체 게임 클리어 여부를 저장하는 변수*/

} App;


/* Entity 구조체 정의 */
typedef struct {

    SDL_Rect pos;           /**< 직사각형 객체의 상태를 나타내기 위한 구조체, 여기에 객체의 좌표, 위치 저장*/
    SDL_Texture *texture;   /**< 텍스쳐를 담고 있는 구조체 (그림파일을 열어 텍스쳐에 저장)*/

    int health;             /**< 체력 상태를 나타내는 변수 (사망 0)*/
    int speed;              /**< 해당 Entity의 속도를 저장하는 변수*/
    double distance;        /**< [플레이어] 적과의 거리를 저장하는 변수*/
    double theta;           /**< [플레이어] 적과의 각도를 저장하는 변수*/

    int x_val;              /**< [거미] x축 이동 속도 저장하기 위한 변수*/
    int y_val;              /**< [거미] y축 이동 속도 저장하기 위한 변수*/

    int gun;                /**< [플레이어] 샷건 소유 여부 저장하기 위한 변수 */

    int burning;            /**< [적] 불타고 있음을 저장하기 위한 변수 */

} Entity;


/**
 @brief  Puzzle: 퍼즐 내 구성요소의 상태를 저장하기 위한 구조체 (논리 게이트 칩, 칩 슬롯, 버튼)
*/
typedef struct {
    SDL_Rect pos;                   /**< 직사각형 객체의 위치, 크기 저장*/
    SDL_Texture *texture;           /**< 텍스쳐를 담고 있는 구조체 (그림파일을 열어 텍스쳐에 저장)*/

    int chip_type;                  /**< 해당 칩 혹은 슬롯에 들어가 있는 칩의 종류를 저장
                                    No chip 0, AND 1 OR 2 XOR 3 BUFFER 4 NAND 5 NOR 6 XNOR 7 NOT 8 */

    int original_x, original_y;     /**< 해당 칩의 원래 위치를 저장*/
    int temporary_x, temporary_y;   /**< 해당 칩의 임시 위치(슬롯)을 저장*/
    int in_slot;                    /**< 해당 칩이 슬롯에 들어가 있는지를 저장*/

    int select;                     /**< 해당 Puzzle(버튼, 칩)이 마우스로 선택되었는지 여부를 저장*/

} Puzzle;


/**
 @brief  Board : 퍼즐 Board 및 맵 저장 위한 구조체
*/
typedef struct {
    SDL_Rect pos;               /**< 직사각형 객체의 상태를 나타내기 위한 구조체, 여기에 객체의 좌표, 위치 저장*/
    SDL_Texture *texture;       /**< 텍스쳐를 담고 있는 구조체 (그림파일을 열어 텍스쳐에 저장)*/
    
} Board;


/**
 @brief  Receiver : Receiver 저장 위한 구조체
*/
typedef struct { 
    SDL_Rect pos;           /**< 직사각형 객체의 상태를 나타내기 위한 구조체, 여기에 객체의 좌표, 위치 저장*/
    SDL_Texture *texture;   /**< 텍스쳐를 담고 있는 구조체 (그림파일을 열어 텍스쳐에 저장)*/

} Receiver;


/**
 @brief  KeyButton : Keypad 버튼 저장 위한 구조체
*/
typedef struct { 
    SDL_Rect pos;           /**< 직사각형 객체의 상태를 나타내기 위한 구조체, 여기에 객체의 좌표, 위치 저장*/
    SDL_Texture *texture;   /**< 텍스쳐를 담고 있는 구조체 (그림파일을 열어 텍스쳐에 저장)*/

    int status;             /**< 해당 Receiver의 상태 나타내기 위한 구조체
                                떼졌을 시 0, 눌렸을 시 1*/

    int select;             /**< 해당 버튼이 마우스로 선택되었는지 여부를 저장*/

} KeyButton;


#endif