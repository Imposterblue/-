#ifndef INPUT_H
#define INPUT_H

#include "init.h"
#include "defs.h"
#include "utils.h"

/**
 @brief 이벤트 큐에 있는 이벤트를 가져와 마우스와 키보드로부터의 입력을 response 함수와 Get Mouse state 함수를 통해 app에 상태를 기록한다.

SDL_GetMouseState 함수를 통해 마우스의 현재 위치를, ResponseKeyUp, ResponseKeyDown 함수를 통해 키가 눌리고 떼진 상태를,
ResponseMouseDown, ResponseMouseUp 함수를 통해 마우스 버튼이 눌리고 떼진 상태를 app 구조체에 기록한다.

 @remark 전역변수 App app 구조체에 접근한다.
 
 @return 리턴 값 없음
 @ingroup Input
*/
void GetInput(void);


/**
 @brief 키보드가 떼진 상태를 app 구조체에 기록한다.

 이벤트에 따라 키보드 입력을 스캔해 특정 키에 해당하는 app 변수를 0으로 저장한다.

 @param[in] event 이벤트 내용을 담고 있는 구조체

 @remark 전역변수 App app 구조체에 접근한다.
 
 @return 리턴 값 없음
 @ingroup Input
*/
void ResponseKeyUp(SDL_KeyboardEvent *event);


/**
 @brief 키보드가 떼진 상태를 app 구조체에 기록한다.

 이벤트에 따라 키보드 입력을 스캔해 특정 키에 해당하는 app 변수를 0으로 저장한다.

 @param[in] event 이벤트 내용을 담고 있는 구조체

 @remark 전역변수 App app 구조체에 접근한다.
 
 @return 리턴 값 없음
 @ingroup Input
*/
void ResponseKeyDown(SDL_KeyboardEvent *event);


/**
 @brief 마우스의 좌표와 마우스 좌/우 버튼을 눌렀을 때 상태를 기록한다.

 \ref app의 멤버 \ref app.mouse_x_before, \ref &app.mouse_y_before은 마우스 클릭 좌표를 기록하는 변수이다.
 \ref app.mouse_left, \ref &app.mouse_right 는 마우스 좌/우 버튼이 눌린 상태를 기록하는 변수이다.
 \ref app.rightcancel 는 마우스 우클릭으로 선택을 취소했는지 여부를 기록하는 변수이다.
 이벤트에 따라 버튼이 눌린 시점의 변수를 저장한다.

 @param[in] event 이벤트 내용을 담고 있는 구조체

 @remark 전역변수 App app 구조체에 접근한다.
 
 @return 리턴 값 없음
 @ingroup Input
*/
void ResponseMouseUp(SDL_MouseButtonEvent *event);


/**
 @brief 마우스의 좌표와 마우스 좌/우 버튼을 눌렀을 때 상태를 기록한다.

 \ref app.mouse_left, \ref &app.mouse_right 는 마우스 좌/우 버튼이 눌린 상태를 기록하는 변수이다.
이벤트에 따라 떼진 버튼에 대한 변수를 0으로 설정한다.

 @param[in] event 이벤트 내용을 담고 있는 구조체

 @remark 전역변수 App app 구조체에 접근한다.
 
 @return 리턴 값 없음
 @ingroup Input
*/
void ResponseMouseDown(SDL_MouseButtonEvent *event);


#endif