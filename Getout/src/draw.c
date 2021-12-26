#include "draw.h"

/* 프로그램 실행화면을 초기화 */
void ClearWindow(void) {
    SDL_SetRenderDrawColor(app.renderer, 45, 35, 45, 255);   // 회색 배경
    SDL_RenderClear(app.renderer);

    return;
}


/* 프로그램 실행화면 출력 */
void ShowWindow(void) {
    SDL_RenderPresent(app.renderer);

    return;
}

/* 렌더 우선순위에 따라 오브젝트를 렌더링 */
void DrawGame(void) {

    RenderBoard(&background);   // 배경
    RenderEntity(&stickyfloor); // 바닥

    for (int i = 0; i < 11; ++i){ // 상호작용 가능한 물체
        RenderEntity(&(interact_obj[i]));
    }

    RenderEntity(&screw);    // 장애물[못]   
    RenderEntity(&fire);     // 장애물[벽난로 불]
    RenderEntity(&trap);     // 장애물[덫]
    RenderEntity(&cactus);   // 장애물[선인장]
    RenderEntity(&spider);   // 장애물[거미]

    RenderEntity(&enemy);    // 플레이어 
    RenderEntity(&player);   // 적
    RenderEntity(&shotgun);  // 샷건

    RenderBoard(&board);     // 논리 게이트 퍼즐 보드
    RenderBoard(&keypad);    // 키패드 퍼즐 키패드

    RenderBoard(&calendar);     // 달력
    RenderBoard(&window);       // 창문
    RenderBoard(&mark);         // 낙서
    RenderBoard(&corpse_text);  // 시체
    RenderBoard(&power_need);   // 전원 필요
    RenderBoard(&tool_need);    // 도구 필요
    RenderBoard(&key_need);     // 열쇠 필요
    RenderBoard(&tool_get);     // 도구 획득
    RenderBoard(&key_get);      // 열쇠 획득


    for (int i = 0; i < 2; i++) {   //  Puzzle button(전원버튼, Reset버튼)을 Render
        RenderPuzzle(&(button[i]));
    }

    for (int i = 0; i < MAX_SLOT; i++) {    // Puzzle 칩 슬롯을 Render
        RenderPuzzle(&(slot[i]));
    }

    for (int i = 0; i < MAX_RECEIVER; i++) {    // Puzzle Receiver을 Render
        RenderReceiver(&(receiver[i]));
    }

    for (int i = 0; i < MAX_GATE; i++) {    // Puzzle 게이트 칩을 Render(선택되지 않은 게이트 칩)
        if (gate[i].select == 0){
        RenderPuzzle(&(gate[i]));
        }
    }

    for (int i = 0; i < MAX_GATE; i++) {    // Puzzle 게이트 칩을 Render(선택된 게이트 칩)
        if (gate[i].select == 1){
        RenderPuzzle(&(gate[i]));
        }
    }

    for (int i = 0; i < 12; i++) {    // Puzzle 게이트 칩을 Render(선택된 게이트 칩)
        RenderKeybutton(&(keybutton[i]));
    }

    return;
}

/* 게임 오버 화면을 렌더링 */
void DrawGameOver(void) {

    RenderEntity(&game_over);

    return;
}

/* 게임 종료(클리어) 화면을 렌더링 */
void DrawGameEnd(void) {

    RenderEntity(&game_end);

    return;
}

/* 엔티티 구조체를 렌더링 */
void RenderEntity(Entity *object) {

    SDL_QueryTexture(object->texture, NULL, NULL, &(object->pos.w),
                     &(object->pos.h));
    SDL_RenderCopy(app.renderer, object->texture, NULL, &(object->pos));

    return;
}

/* 보드 구조체를 렌더링 */
void RenderBoard(Board *object){

    SDL_QueryTexture(object->texture, NULL, NULL, &(object->pos.w),
                     &(object->pos.h));
    SDL_RenderCopy(app.renderer, object->texture, NULL, &(object->pos));

    return;

}

/* 퍼즐 구조체를 렌더링 */
void RenderPuzzle(Puzzle *object) {

    SDL_QueryTexture(object->texture, NULL, NULL, &(object->pos.w),
                     &(object->pos.h));
    SDL_RenderCopy(app.renderer, object->texture, NULL, &(object->pos));

    return;
}

/* 리시버 구조체를 렌더링 */
void RenderReceiver(Receiver *object){

    SDL_QueryTexture(object->texture, NULL, NULL, &(object->pos.w),
                     &(object->pos.h));
    SDL_RenderCopy(app.renderer, object->texture, NULL, &(object->pos));

    return;

}

/* 키 버튼[키패드 퍼즐] 구조체를 렌더링 */
void RenderKeybutton(KeyButton *object){

    SDL_QueryTexture(object->texture, NULL, NULL, &(object->pos.w),
                     &(object->pos.h));
    SDL_RenderCopy(app.renderer, object->texture, NULL, &(object->pos));

    return;

}