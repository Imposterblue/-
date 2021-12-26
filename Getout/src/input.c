#include "input.h" // input 헤더파일 include

/* 이벤트 큐에 있는 이벤트를 가져와 마우스와 키보드로부터의 입력을 app 구조체에 기록한다. */
void GetInput(void) {
    SDL_Event event;

    SDL_GetMouseState(&app.mouse_x_current,&app.mouse_y_current);

    /*SDL_PollEvent() 함수는 이벤트 큐에 남아 있는 이벤트를 가져옴*/
    while (SDL_PollEvent(&event)) {

        switch (event.type) {

            /* 창닫기 버튼을 누른 경우 */
            case SDL_QUIT:
                QuitSDL(0);
                break;

            /* 키보드 버튼을 뗐을 경우 */
            case SDL_KEYUP:
                ResponseKeyUp(&event.key);
                break;

            /* 키보드 버튼을 눌렀을 경우 */
            case SDL_KEYDOWN:
                ResponseKeyDown(&event.key);
                break;

            /* 마우스 버튼을 눌렀을 경우 */
            case SDL_MOUSEBUTTONDOWN:
                ResponseMouseDown(&event.button);
                break;

            /* 마우스 버튼을 뗐을 경우 */
            case SDL_MOUSEBUTTONUP:
                ResponseMouseUp(&event.button);
                break;

            default:
                break;
        }
    }
    return;
}

/* 키보드 버튼을 뗐을 경우 해당 키의 app 구조체에 0을 저장 */
void ResponseKeyUp(SDL_KeyboardEvent *event) {
    if (event->repeat == 0) {
        SDL_Scancode key_input = event->keysym.scancode;
        switch (key_input) {

            /* +y방향 이동 키 */
            case SDL_SCANCODE_W:
                app.key_up = 0;
                break;

            /* -y방향 이동 키 */
            case SDL_SCANCODE_S:
                app.key_down = 0;
                break;

            /* -x방향 이동 키 */
            case SDL_SCANCODE_A:
                app.key_left = 0;
                break;

            /* +x방향 이동 키 */
            case SDL_SCANCODE_D:
                app.key_right = 0;
                break;

            /* 게임오버 시 리플레이 키 */
            case SDL_SCANCODE_R:
                app.key_r = 0;
                break;

            /* 물체와의 상호작용 및 샷건 발사 키 */
            case SDL_SCANCODE_SPACE:
                app.key_spacebar = 0;
                break;

            /* 퍼즐화면 종료 및 게임 종료 키 */
            case SDL_SCANCODE_ESCAPE:
                app.key_esc = 0;
                break;

            default:
                break;
        }
    }
    return;
}

/* 키보드 버튼을 뗐을 경우 해당 키의 app 구조체에 0을 저장, 키 역할은 위와 동일*/
void ResponseKeyDown(SDL_KeyboardEvent *event) {
    if (event->repeat == 0) {
        SDL_Scancode key_input = event->keysym.scancode;
        switch (key_input) {
            case SDL_SCANCODE_W: 
                app.key_up = 1;
                break;
            case SDL_SCANCODE_S:
                app.key_down = 1;
                break;
            case SDL_SCANCODE_A:
                app.key_left = 1;
                break;
            case SDL_SCANCODE_D:
                app.key_right = 1;
                break;
            case SDL_SCANCODE_R:
                app.key_r = 1;
                break;
            case SDL_SCANCODE_SPACE:
                app.key_spacebar = 1;
                break;
            case SDL_SCANCODE_ESCAPE:
                app.key_esc = 1;
                break;
        }
    }
    return;
}

/* 마우스 버튼을 뗐을 경우 app 구조체에 해당 상태를 저장 */
void ResponseMouseUp(SDL_MouseButtonEvent *event) {
    Uint8 mouse_input = event->button;

    /* 마우스 왼쪽 버튼을 뗀 경우 */
    if (mouse_input == SDL_BUTTON_LEFT){
        app.mouse_left = 0;
    }

    /* 마우스 오른쪽 버튼을 뗀 경우 */
    if (mouse_input == SDL_BUTTON_RIGHT){
        app.mouse_right = 0;
    }

    return;
}

/* 마우스 버튼을 눌렀을 경우 app 구조체에 해당 상태를 저장 */
void ResponseMouseDown(SDL_MouseButtonEvent *event) {
    Uint8 mouse_input = event->button;

    /* 마우스 왼쪽 버튼을 누른 경우 */
    if (mouse_input == SDL_BUTTON_LEFT)
    { 
        if (app.mouse_left == 0 ){ // 이전에 마우스 왼쪽 버튼이 떼진 상태라면(이번에 새로이 눌린 상태라면)
            SDL_GetMouseState(&app.mouse_x_before,&app.mouse_y_before); // 마우스 클릭 좌표를 app 구조체에 저장
            app.rightcancel = 0; // 우클릭 취소 여부 저장 변수를 0으로 초기화
        }
        app.mouse_left = 1; // 마우스 좌클릭 상태를 1로 저장
    }

    /* 마우스 오른쪽 버튼을 누른 경우 */
    if (mouse_input == SDL_BUTTON_RIGHT)
    {
        app.mouse_right = 1; // 마우스 우클릭 상태를 1로 저장
        app.rightcancel = 1; // 우클릭 취소 여부 저장 변수를 1로 저장
    }
        
    return;
}


