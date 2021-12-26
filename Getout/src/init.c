#include "init.h" // init 헤더 파일 include

/* SDL 초기화 */
void InitSDL(void) { 
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("[ERROR] in InitSDL(): %s", SDL_GetError());
        exit(1);
    }

    app.window = SDL_CreateWindow("Getout!!!", SDL_WINDOWPOS_UNDEFINED,   
                                  SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                                  SCREEN_HEIGHT, 0);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    app.renderer = SDL_CreateRenderer(app.window, -1, SDL_RENDERER_ACCELERATED);
    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);

    return;
}



/* SDL 종료 */
void QuitSDL(int flag) {
    SDL_DestroyRenderer(app.renderer);
    SDL_DestroyWindow(app.window);
    SDL_Quit();
    exit(flag);

    return;
}



/* 메모리 할당 */
void InitMemorySet(void) {

    memset(&app, 0, sizeof(App));

    memset(&background, 0,sizeof(Board));

    memset(&player, 0, sizeof(Entity));
    memset(&enemy, 0, sizeof(Entity)); 

    memset(&screw, 0, sizeof(Entity)); 
    memset(&fire, 0, sizeof(Entity));
    memset(&trap, 0, sizeof(Entity));
    memset(&cactus, 0, sizeof(Entity)); 
    memset(&spider, 0, sizeof(Entity));
    memset(&stickyfloor, 0, sizeof(Entity)); 
    memset(&shotgun, 0, sizeof(Entity)); 

    memset(&calendar,0,sizeof(Board));
    memset(&window,0,sizeof(Board));
    memset(&mark,0,sizeof(Board));
    memset(&corpse_text,0,sizeof(Board));
    memset(&power_need,0,sizeof(Board));
    memset(&tool_need,0,sizeof(Board));
    memset(&key_need,0,sizeof(Board));
    memset(&tool_get,0,sizeof(Board));
    memset(&key_get,0,sizeof(Board));

    memset(&interact_obj, 0, 11 * sizeof(Entity));

    memset(&board, 0,sizeof(Board));
    memset(&button, 0, MAX_BUTTON * sizeof(Puzzle));
    memset(&gate, 0, MAX_GATE * sizeof(Puzzle));
    memset(&slot, 0, MAX_SLOT * sizeof(Puzzle));
    memset(&receiver, 0, MAX_RECEIVER * sizeof(Receiver));

    memset(&keypad,0,sizeof(Board));
    memset(&keybutton, 0, 12 * sizeof (KeyButton));

    memset(&game_over, 0, sizeof(Entity));
    memset(&game_end, 0, sizeof(Entity));

    return;
}

/* 배경 초기화 */
void InitBackGround(int map){ // int 형식 map을 인자로 받음

    switch (map) { // 입력된 map data에 따라 다른 함수 실행

        case 1:
            background.texture = IMG_LoadTexture(app.renderer, "./gfx/Background1.png"); // 첫번째 방 
            break;

        case 2:
            background.texture = IMG_LoadTexture(app.renderer, "./gfx/Background2.png"); // 두번째 방
            break;
    }

    background.pos.x = 0; // 맵 오브젝트의 위치 설정
    background.pos.y = 0;
}


/* 플레이어 상태 초기화 */
void InitPlayer(void) {
    player.texture = IMG_LoadTexture(app.renderer, "./gfx/Player2.png");
    player.pos.x =1100;
    player.pos.y =600;
    player.health = 1;
    player.gun = 0;
    player.speed = PLAYER_SPEED;

    return;
}


/* 적 상태 초기화 */
void InitEnemy(void) {   
    enemy.texture = IMG_LoadTexture(app.renderer, "./gfx/Enemy.png");
    enemy.pos.x = SCREEN_WIDTH * 2 / 3 ;   
    enemy.pos.y = SCREEN_HEIGHT / 5 ;
    enemy.health = 4;
    enemy.burning = 0;
    enemy.speed = ENEMY_SPEED;
    return;
}

/* 스크류(장애물) 상태 초기화 */
void InitScrew(void) {  
    screw.texture = IMG_LoadTexture(app.renderer, "./gfx/Screw.png");
    screw.pos.x = SCREEN_WIDTH - SCREW_WIDTH - 400;
    screw.pos.y = SCREEN_HEIGHT -SCREW_HEIGHT - WALL_THICKNESS2;
    screw.health = 1;
    return;
}

/* 벽난로 불(장애물) 상태 초기화 */
void InitFire(void) {   
    fire.texture = IMG_LoadTexture(app.renderer, "./gfx/Fire.png");
    fire.pos.x = SCREEN_WIDTH - FIRE_WIDTH - 200;  
    fire.pos.y = WALL_THICKNESS2 - 40;
    fire.health = 1;
    return;
}

/* 덫(장애물) 상태 초기화 */
void InitTrap(void) {  
    trap.texture = IMG_LoadTexture(app.renderer, "./gfx/Trap.png");
    trap.pos.x = WALL_THICKNESS2 + 20;  
    trap.pos.y = WALL_THICKNESS2 + 10;  
    trap.health = 1;
    return;
}

/* 선인장(장애물) 상태 초기화 */
void InitCactus(void) {  
    cactus.texture = IMG_LoadTexture(app.renderer, "./gfx/Cactus1.png");
    cactus.pos.x = 540;
    cactus.pos.y = 380;
    cactus.health = 1;
    return;
}

/* 거미(장애물) 상태 초기화 */
void InitSpider(void) { 
    spider.texture = IMG_LoadTexture(app.renderer, "./gfx/Spider.png");
    spider.pos.x = 1000;
    spider.pos.y = 650;
    spider.health = 0;
    spider.x_val = -(int)(SPIDER_SPEED * cos(0.52));
    spider.y_val = (int)(SPIDER_SPEED * sin(0.52)); 
    return;
}

/* 끈끈한 바닥(장애물) 상태 초기화 */
void InitStickyfloor(void) { 
    stickyfloor.texture = IMG_LoadTexture(app.renderer, "./gfx/Stickyfloor.png");   
    stickyfloor.pos.x = 800;
    stickyfloor.pos.y = 220;
    return;
}

/* 샷건(아이템) 상태 초기화 */
void InitShotgun(void) {  
    shotgun.texture = IMG_LoadTexture(app.renderer, "./gfx/ShotgunBase.png");
    shotgun.pos.x = 520;
    shotgun.pos.y = 10;  
    shotgun.health = 1; 
    return;
}


/* 보드 상태 초기화 */
void InitBoard(int type){ //int타입 인자 type을 입력받음

    switch (type) { // 입력받은 인자에 따라 다른 코드를 실행 (board 구조체에 다른 텍스쳐와 위치를 할당)

        case 1:
            board.texture = IMG_LoadTexture(app.renderer, "./gfx/Stage1.png"); // 논리회로퍼즐 1
            break;

        case 2:
            board.texture = IMG_LoadTexture(app.renderer, "./gfx/Stage2.png"); // 논리회로퍼즐 2
            break;

        case 3:
            board.texture = IMG_LoadTexture(app.renderer, "./gfx/Stage3.png"); // 논리회로퍼즐 3
            break;

        case 4:
            tool_get.texture = IMG_LoadTexture(app.renderer, "./gfx/Tool.png"); // 도구 획득 시 텍스트
            tool_get.pos.x = SCREEN_WIDTH / 2 - 325;
            tool_get.pos.y = SCREEN_HEIGHT / 2 - 325;
            return;

        case 5:
            keypad.texture = IMG_LoadTexture(app.renderer, "./gfx/Keypad0.png"); // 키패드 퍼즐
            keypad.pos.x = KEYPAD_X;
            keypad.pos.y = KEYPAD_Y;
            return;

        case 6:
            calendar.texture = IMG_LoadTexture(app.renderer, "./gfx/Calendar.png"); // 달력 조사 시 그림
            calendar.pos.x = SCREEN_WIDTH / 2 - 325;
            calendar.pos.y = SCREEN_HEIGHT / 2 - 325;
            return;


        case 7:
            corpse_text.texture = IMG_LoadTexture(app.renderer, "./gfx/Corpse.png"); // 시체 조사 시 텍스트
            corpse_text.pos.x = SCREEN_WIDTH / 2 - 325;
            corpse_text.pos.y = SCREEN_HEIGHT / 2 - 325;
            return;

        case 8:
            window.texture = IMG_LoadTexture(app.renderer, "./gfx/Window.png"); // 창문 조사 시 텍스트
            window.pos.x = SCREEN_WIDTH / 2 - 325;
            window.pos.y = SCREEN_HEIGHT / 2 - 325;
            return;

        case 9:
            mark.texture = IMG_LoadTexture(app.renderer, "./gfx/Mark.png"); // 낙서 조사 시 그림
            mark.pos.x = SCREEN_WIDTH / 2 - 325;
            mark.pos.y = SCREEN_HEIGHT / 2 - 325;
            return;

        case 10:
            tool_need.texture = IMG_LoadTexture(app.renderer, "./gfx/Needtool.png"); // 도구 필요 시 텍스트
            tool_need.pos.x = SCREEN_WIDTH / 2 - 325;
            tool_need.pos.y = SCREEN_HEIGHT / 2 - 325;
            return;

        case 11:
            power_need.texture = IMG_LoadTexture(app.renderer, "./gfx/Needpower.png"); // 전원 필요 시 텍스트
            power_need.pos.x = SCREEN_WIDTH / 2 - 325;
            power_need.pos.y = SCREEN_HEIGHT / 2 - 325;
            return;

        case 12:
            key_need.texture = IMG_LoadTexture(app.renderer, "./gfx/Needkey.png"); // 열쇠 필요 시 텍스트
            key_need.pos.x = SCREEN_WIDTH / 2 - 325;
            key_need.pos.y = SCREEN_HEIGHT / 2 - 325;
            return;
        
        case 13:
            key_get.texture = IMG_LoadTexture(app.renderer, "./gfx/Getkey.png"); // 열쇠 획득 시 텍스트
            key_get.pos.x = SCREEN_WIDTH / 2 - 325;
            key_get.pos.y = SCREEN_HEIGHT / 2 - 325;
            return;

    }

    board.pos.x = PUZZLE_X; // 논리회로 퍼즐 위치 초기화
    board.pos.y = PUZZLE_Y;
}


/* 상호작용 가능한 물체 상태 초기화 */
void InitInteractObj(void) {

    if (app.map == 1){ // 첫 번째 방에 있을 시

        interact_obj[0].texture = IMG_LoadTexture(app.renderer, "./gfx/Interactobj.png"); // 수리 도구
        interact_obj[0].pos.x = 456;
        interact_obj[0].pos.y = 639;

        interact_obj[1].texture = IMG_LoadTexture(app.renderer, "./gfx/Interactobj.png"); // 논리회로퍼즐 1
        interact_obj[1].pos.x = 771;
        interact_obj[1].pos.y = 633;

        interact_obj[2].texture = IMG_LoadTexture(app.renderer, "./gfx/Interactobj.png"); // 논리회로퍼즐 2
        interact_obj[2].pos.x = 771;
        interact_obj[2].pos.y = 337;

        interact_obj[3].texture = IMG_LoadTexture(app.renderer, "./gfx/Interactobj.png"); // 논리회로퍼즐 3
        interact_obj[3].pos.x = 935; 
        interact_obj[3].pos.y = 298; 

        interact_obj[4].texture = IMG_LoadTexture(app.renderer, "./gfx/Interactobj.png"); // 키패드
        interact_obj[4].pos.x = 1100; 
        interact_obj[4].pos.y = 300;

        interact_obj[5].texture = IMG_LoadTexture(app.renderer, "./gfx/Interactobj.png"); // 달력
        interact_obj[5].pos.x = 201; 
        interact_obj[5].pos.y = 342; 

        interact_obj[6].texture = IMG_LoadTexture(app.renderer, "./gfx/Interactobj.png"); // 시체
        interact_obj[6].pos.x = 395;
        interact_obj[6].pos.y = 563;

        interact_obj[7].texture = IMG_LoadTexture(app.renderer, "./gfx/Interactobj1.png"); // 창문
        interact_obj[7].pos.x = 317;
        interact_obj[7].pos.y = 298;

        interact_obj[8].texture = IMG_LoadTexture(app.renderer, "./gfx/Interactobj.png"); // 낙서
        interact_obj[8].pos.x = 1149;
        interact_obj[8].pos.y = 436;

    }

    if (app.map == 2){

        interact_obj[9].texture = IMG_LoadTexture(app.renderer, "./gfx/Interactobj.png"); // 출구
        interact_obj[9].pos.x = 100;
        interact_obj[9].pos.y = 253;

        interact_obj[10].texture = IMG_LoadTexture(app.renderer, "./gfx/DeadEnemy.png"); // 적 시체
        interact_obj[10].pos.x = SCREEN_WIDTH +1 ;
        interact_obj[10].pos.y = SCREW_HEIGHT +1 ;
    }

    return;
}

/* 논리회로퍼즐 전원 및 리셋 버튼 초기화 */
void InitButton(void) { // button[0] Power button, button[1] Reset button
    button[0].texture = IMG_LoadTexture(app.renderer, "./gfx/Power.png");
    button[0].pos.x = PUZZLE_X + 280;
    button[0].pos.y = PUZZLE_Y + 20;

    button[1].texture = IMG_LoadTexture(app.renderer, "./gfx/Resetbutton.png");
    button[1].pos.x = PUZZLE_X + 40;
    button[1].pos.y = PUZZLE_Y + 476;
    
    return;
}

/* 논리회로퍼즐 게이트 상태 초기화 */
void InitGate(void) {
    gate[0].texture = IMG_LoadTexture(app.renderer, "./gfx/Andgate.png");
    gate[0].pos.x = PUZZLE_X + 13 + 5;
    gate[0].pos.y = PUZZLE_Y + 33 + 5;

    gate[1].texture = IMG_LoadTexture(app.renderer, "./gfx/Orgate.png");
    gate[1].pos.x = PUZZLE_X + 13+ 5;
    gate[1].pos.y = PUZZLE_Y + 144+ 5;

    gate[2].texture = IMG_LoadTexture(app.renderer, "./gfx/Xorgate.png");
    gate[2].pos.x = PUZZLE_X + 13+ 5;
    gate[2].pos.y = PUZZLE_Y + 255+ 5;

    gate[3].texture = IMG_LoadTexture(app.renderer, "./gfx/Buffergate.png");
    gate[3].pos.x = PUZZLE_X + 13+ 5;
    gate[3].pos.y = PUZZLE_Y + 366+ 5;

    gate[4].texture = IMG_LoadTexture(app.renderer, "./gfx/Nandgate.png");
    gate[4].pos.x = PUZZLE_X + 128+ 5;
    gate[4].pos.y = PUZZLE_Y + 33+ 5;

    gate[5].texture = IMG_LoadTexture(app.renderer, "./gfx/Norgate.png");
    gate[5].pos.x = PUZZLE_X + 128+ 5;
    gate[5].pos.y = PUZZLE_Y + 144+ 5;

    gate[6].texture = IMG_LoadTexture(app.renderer, "./gfx/Xnorgate.png");
    gate[6].pos.x = PUZZLE_X + 128+ 5;
    gate[6].pos.y = PUZZLE_Y + 255+ 5;

    gate[7].texture = IMG_LoadTexture(app.renderer, "./gfx/Notgate.png");
    gate[7].pos.x = PUZZLE_X + 128+ 5;
    gate[7].pos.y = PUZZLE_Y + 366+ 5;

    for (int i = 0; i< MAX_GATE; ++i){
    gate[i].original_x = gate[i].pos.x; // 게이트 삽입 취소 위한 초기위치 저장
    gate[i].original_y = gate[i].pos.y;

    gate[i].temporary_x = gate[i].pos.x; // 우클릭 취소 위한 임시위치 저장
    gate[i].temporary_y = gate[i].pos.y;

    gate[i].chip_type = i + 1; // 게이트 종류 저장 (chip_type 1:Andgate, 2:Orgate, 3:Xorgate, 4:Buffergate, 5:Nandgate, 6:Norgate, 7:Xnorgate, 8:Notgate)

    }
    
    return;
}

/* 논리회로퍼즐 슬롯 상태 초기화 */
void InitSlot(int stage) { // 스테이지를 입력

    switch (stage){ // 스테이지에 따라 서로 다른 코드 실행 (서로 다른 위치에 슬롯 할당)

        case 1:
            for (int i = 0; i < 4; ++i){
                slot[i].texture = IMG_LoadTexture(app.renderer, "./gfx/Chipslot.png");
                slot[i].pos.x = PUZZLE_X + 702;
                slot[i].pos.y = PUZZLE_Y + 120 + 90 * i;
            }

            break;

        case 2:
            for (int i = 0; i < 4; ++i){
                slot[i].texture = IMG_LoadTexture(app.renderer, "./gfx/Chipslot.png");
            }

            slot[0].pos.x = PUZZLE_X + 719;
            slot[0].pos.y = PUZZLE_Y + 133;

            slot[1].pos.x = PUZZLE_X + 589;
            slot[1].pos.y = PUZZLE_Y + 288;

            slot[2].pos.x = PUZZLE_X + 673;
            slot[2].pos.y = PUZZLE_Y + 404;

            slot[3].pos.x = PUZZLE_X + 812;
            slot[3].pos.y = PUZZLE_Y + 493;

            break;

        case 3:
            for (int i = 0; i < 8; ++i){
                slot[i].texture = IMG_LoadTexture(app.renderer, "./gfx/Chipslot.png");
            }

            slot[0].pos.x = PUZZLE_X + 657;
            slot[0].pos.y = PUZZLE_Y + 17;

            slot[1].pos.x = PUZZLE_X + 657;
            slot[1].pos.y = PUZZLE_Y + 109;

            slot[2].pos.x = PUZZLE_X + 582;
            slot[2].pos.y = PUZZLE_Y + 352;

            slot[3].pos.x = PUZZLE_X + 449;
            slot[3].pos.y = PUZZLE_Y + 506;

            slot[4].pos.x = PUZZLE_X + 922;
            slot[4].pos.y = PUZZLE_Y + 30;

            slot[5].pos.x = PUZZLE_X + 922;
            slot[5].pos.y = PUZZLE_Y + 120;

            slot[6].pos.x = PUZZLE_X + 922;
            slot[6].pos.y = PUZZLE_Y + 210;

            slot[7].pos.x = PUZZLE_X + 922;
            slot[7].pos.y = PUZZLE_Y + 300;

        default:
            break;

    }
    return;
}

/* 논리회로퍼즐 리시버 상태 초기화 */
void InitReceiver(int status, int index, int x, int y) { // 리시버 각각의 상태, 번호, x좌표, y좌표를 입력받음

    if (status == 1){ // 입력이 올바른 경우
        receiver[index].texture = IMG_LoadTexture(app.renderer, "./gfx/Receiverright.png");;
    }

    else if (status == 2){ // 입력이 올바르지 않은 경우
        receiver[index].texture = IMG_LoadTexture(app.renderer, "./gfx/Receiverwrong.png");;
    }

    receiver[index].pos.x = x; // 입력된 좌표에 리시버를 배치
    receiver[index].pos.y = y;
    
    return;
}

/* 키버튼퍼즐 키 상태 초기화 */
void InitKeyButton(void) {

    for (int i = 0; i < 4; ++i){ // app의 패스코드 초기화(입력되지 않은 초기상태)
        app.passcode[i] = -1;
    }

    keybutton[1].texture = IMG_LoadTexture(app.renderer, "./gfx/Keybuttonset.png"); // 버튼 1
    keybutton[1].pos.x = KEYPAD_X + 72;
    keybutton[1].pos.y = KEYPAD_Y + 157;

    keybutton[2].texture = IMG_LoadTexture(app.renderer, "./gfx/Keybuttonset.png"); // 버튼 2
    keybutton[2].pos.x = KEYPAD_X + 187;
    keybutton[2].pos.y = KEYPAD_Y + 157;

    keybutton[3].texture = IMG_LoadTexture(app.renderer, "./gfx/Keybuttonset.png"); // 버튼 3
    keybutton[3].pos.x = KEYPAD_X + 302;
    keybutton[3].pos.y = KEYPAD_Y + 157;

    keybutton[4].texture = IMG_LoadTexture(app.renderer, "./gfx/Keybuttonset.png"); // 버튼 4
    keybutton[4].pos.x = KEYPAD_X + 72;
    keybutton[4].pos.y = KEYPAD_Y + 274;

    keybutton[5].texture = IMG_LoadTexture(app.renderer, "./gfx/Keybuttonset.png"); // 버튼 5
    keybutton[5].pos.x = KEYPAD_X + 187;
    keybutton[5].pos.y = KEYPAD_Y + 274;

    keybutton[6].texture = IMG_LoadTexture(app.renderer, "./gfx/Keybuttonset.png"); // 버튼 6
    keybutton[6].pos.x = KEYPAD_X + 302;
    keybutton[6].pos.y = KEYPAD_Y + 274;

    keybutton[7].texture = IMG_LoadTexture(app.renderer, "./gfx/Keybuttonset.png"); // 버튼 7
    keybutton[7].pos.x = KEYPAD_X + 72;
    keybutton[7].pos.y = KEYPAD_Y + 391;

    keybutton[8].texture = IMG_LoadTexture(app.renderer, "./gfx/Keybuttonset.png"); // 버튼 8
    keybutton[8].pos.x = KEYPAD_X + 187;
    keybutton[8].pos.y = KEYPAD_Y + 391;

    keybutton[9].texture = IMG_LoadTexture(app.renderer, "./gfx/Keybuttonset.png"); // 버튼 9
    keybutton[9].pos.x = KEYPAD_X + 302;
    keybutton[9].pos.y = KEYPAD_Y + 391;

    keybutton[10].texture = IMG_LoadTexture(app.renderer, "./gfx/Keybuttonset.png"); // 입력 취소 버튼
    keybutton[10].pos.x = KEYPAD_X + 72;
    keybutton[10].pos.y = KEYPAD_Y + 508;

    keybutton[0].texture = IMG_LoadTexture(app.renderer, "./gfx/Keybuttonset.png"); // 버튼 0
    keybutton[0].pos.x = KEYPAD_X + 187;
    keybutton[0].pos.y = KEYPAD_Y + 508;

    keybutton[11].texture = IMG_LoadTexture(app.renderer, "./gfx/Keybuttonset.png"); // 입력 버튼
    keybutton[11].pos.x = KEYPAD_X + 302;
    keybutton[11].pos.y = KEYPAD_Y + 508;
    
    return;
}

/* 게임 오버 화면 상태 초기화 */
void InitGameOver(void) {
    game_over.texture = IMG_LoadTexture(app.renderer, "./gfx/GameOver.png");
    game_over.pos.x = 0;
    game_over.pos.y = 0;
}

/* 게임 엔드 화면 상태 초기화 */
void InitGameEnd(void) {
    game_end.texture = IMG_LoadTexture(app.renderer, "./gfx/GameClear.png");
    game_end.pos.x = 0;
    game_end.pos.y = 0;
}