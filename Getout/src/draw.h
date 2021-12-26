
#ifndef DRAW_H
#define DRAW_H

#include "defs.h"
#include "utils.h"


/**
 @brief 프로그램 실행화면 초기화

 프로그램 실행화면을 초기화한다. 대상 Renderer은 app 구조체에 저장되어 있다.

 @remark 전역변수 \ref app 에 접근한다.

 @return 리턴 값 없음
 @ingroup Draw
*/
void ClearWindow(void); 


/**
 @brief 프로그램 실행화면 출력

 프로그램 실행화면을 출력한다. 대상 Renderer은 app 구조체에 저장되어 있다.

 @remark 전역변수 \ref app 에 접근한다.

 @return 리턴 값 없음
 @ingroup Draw
*/
void ShowWindow(void);


/**
 @brief 렌더 우선순위에 따라 오브젝트를 렌더링

렌더 우선순위에 따라 오브젝트를 렌더링한다.

 @return 리턴 값 없음
 @ingroup Draw
*/
void DrawGame(void);


/**
 @brief 게임 오버 화면을 렌더링한다.

 게임 오버 화면을 렌더링한다. 대상 오브젝트는 Entity 구조체의 game_over 변수에 저장되어 있다.

 @remark 전역변수 \ref Entity game_over 에 접근한다.

 @return 리턴 값 없음
 @ingroup Draw
*/
void DrawGameOver(void);


/**
 @brief 게임 종료(클리어) 화면을 렌더링한다.

 게임 종료 화면을 렌더링한다. 대상 오브젝트는 Entity 구조체의 game_end 변수에 저장되어 있다.

 @remark 전역변수 \ref Entity game_end 에 접근한다.

 @return 리턴 값 없음
 @ingroup Draw
*/
void DrawGameEnd(void);


/**
 @brief 입력받은 Entity를 렌더링한다.

 입력받은 Entity 구조체 를 렌더링한다. 대상 Entity 는 적절하게 초기화되어 \ref Entity.texture 와 \ref
 Entity.pos 의 위치 (x, y)가 설정되어 있어야 한다.
 SDL_QueryTexture 함수에서는 texture의 정보를 바탕으로 너비와 높이를 자동으로
 계산하여 \ref App.pos 에 반영한다.

 @param[in] object 렌더링 대상 Entity 구조체

 @remark 전역변수 \ref app 에 접근한다.

 @return 리턴 값 없음
 @ingroup Draw
*/
void RenderEntity(Entity *object);


/**
 @brief Puzzle 구조체 렌더링

 Puzzle을 렌더링한다. 대상 Puzzle은 적절하게 초기화되어 \ref Puzzle.texture 와
 \ref Puzzle.pos 의 위치 (x, y)가 설정되어 있어야 한다.
 SDL_QueryTexture 함수에서는 texture의 정보를 바탕으로 너비와 높이를 자동으로
 계산하여 \ref App.pos 에 반영한다.

 @param[in] object 렌더링 대상 Puzzle 구조체

 @remark 전역변수 \ref app 에 접근한다.

 @return 리턴 값 없음
 @ingroup Draw
*/
void RenderPuzzle(Puzzle *object);


/**
 @brief Board 구조체 렌더링 (퍼즐 배경)

 Board 구조체 를 렌더링한다. 대상 Board 는 적절하게 초기화되어 \ref Board.texture 와 \ref
 Board.pos 의 위치 (x, y)가 설정되어 있어야 한다.
 SDL_QueryTexture 함수에서는 texture의 정보를 바탕으로 너비와 높이를 자동으로
 계산하여 \ref App.pos 에 반영한다.

 @param[in] object 렌더링 대상 Board 구조체

 @remark 전역변수 \ref app 에 접근한다.

 @return 리턴 값 없음
 @ingroup Draw
*/
void RenderBoard(Board *object);


/**
 @brief Receiver 구조체 렌더링

 Receiver 구조체 를 렌더링한다. 대상 Receiver 은 적절하게 초기화되어 \ref Receiver.texture 와 \ref
 Receiver.pos 의 위치 (x, y)가 설정되어 있어야 한다.
 SDL_QueryTexture 함수에서는 texture의 정보를 바탕으로 너비와 높이를 자동으로
 계산하여 \ref App.pos 에 반영한다.

 @param[in] object 렌더링 대상 Receiver 구조체

 @remark 전역변수 \ref app 에 접근한다.

 @return 리턴 값 없음
 @ingroup Draw
*/
void RenderReceiver(Receiver *object);


/**
 @brief KeyButton 구조체 렌더링

 KeyButton 구조체 를 렌더링한다. 대상 KeyButton 은 적절하게 초기화되어 \ref KeyButton.texture 와 \ref
 KeyButton.pos 의 위치 (x, y)가 설정되어 있어야 한다.
 SDL_QueryTexture 함수에서는 texture의 정보를 바탕으로 너비와 높이를 자동으로
 계산하여 \ref App.pos 에 반영한다.

 @param[in] object 렌더링 대상 KeyButton 구조체

 @remark 전역변수 \ref app 에 접근한다.

 @return 리턴 값 없음
 @ingroup Draw
*/
void RenderKeybutton(KeyButton *object);


#endif