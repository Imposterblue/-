#include "action.h"
#include "draw.h"


/*----------------------------------------------ActGame--------------------------------------------- */


/* 이동 및 탐색, 전투 중일 시 필요한 액션을 순차적으로 수행 */
void ActGame(void) {

    RelativePos();      //플레이어와 적 사이의 거리와 각도 측정해 app 구조체에 저장
    ActPlayer();        //플레이어의 움직임을 실행하는 함수이다. 플레이어의 이동, 벽과의 충돌, 샷건의 발사 동작등을 시행.
    ActEnemy();         //적의 움직임을 실행하는 함수이다. 적의 사망 판정, 플레이어 추적 동작을 시행한다.

    ScrewUsed();        //적과 못의 충돌여부를 판단하는 함수이다. 충돌 시 적의 체력을 깎고 사라진다.
    FireUsed();         //적과 벽난로 불의 충돌여부를 판단하는 함수이다. 충돌 시 적의 체력과 속도를 깎고 상태를 변화시킨 뒤 사라진다.
    CactusUsed();       //적과 선인장의 충돌여부를 판단하는 함수이다. 충돌 시 적의 체력을 깎고 속도를 증가시킨 뒤 모습을 바꾼다.
    SpiderMovement();   //거미의 움직임을 제어하는 함수이다. 일정 범위 내에서 랜덤하게 움직이고 벽과 충돌하면 방향을 바꾼다.
    TrapUsed();         //적과 덫의 충돌여부를 판단하는 함수이다. 충돌 시 적의 체력을 깎은 뒤 사라진다.
    Onthefloor();       //적과 끈끈한 바닥의 충돌여부를 판단하는 함수이다. 바닥 위에 있을 시 플레이어의 속도를 느리게 한다.

    ShotgunUse();       //플레이어 오브젝트와 샷건 오브젝트의 충돌여부를 판단하고, 소지 여부를 판단하는 함수이다.

    ActCheckDeath();    //플레이어와 장애물 오브젝트의 충돌 여부를 검사하는 함수이며, 충돌 시 체력을 0으로 만든다.

    ActInteraction();   //플레이어와 상호 작용 오브젝트의 충돌 여부, 스페이스바 push 여부를 검사하여 코드를 실행하는 함수
    return;
}

/* 플레이어와 적 사이의 거리와 각도 측정해 app 구조체에 저장 하는 함수 RelativePos*/
void RelativePos(void){
    enemy.distance = Distance(player.pos.x, player.pos.y, enemy.pos.x, enemy.pos.y); // Distance 함수 를 통해 거리 구해 enemy.distance 멤버에 저장

    if (player.pos.y < enemy.pos.y){    // acos 함수 를 통해 플레이어와 적 사이의 각도 구해 enemy.theta 멤버에 저장
            enemy.theta = acos((enemy.pos.x - player.pos.x) /enemy. distance);
    }

    else{
            enemy.theta = -acos((enemy.pos.x - player.pos.x) /enemy. distance);

    }
}

/*플레이어의 움직임을 실행하는 함수이다. 플레이어의 이동, 벽과의 충돌, 샷건의 발사 동작등을 시행하는 함수 ActPlayer.*/
void ActPlayer(void) {
    if (app.key_up) {       // w 입력 시 위쪽으로 이동
        player.pos.y -= player.speed;
        if (CheckCollisionWall(&player)) { // 벽과 충돌 시 이동 취소
            player.pos.y += player.speed;
        }
    }
    if (app.key_down) {     // s 입력 시 위쪽으로 이동
        player.pos.y += player.speed;
        if (CheckCollisionWall(&player)) {  // 벽과 충돌 시 이동 취소
            player.pos.y -= player.speed;
        }
    }
    if (app.key_left) {     // a 입력 시 위쪽으로 이동
        player.texture = IMG_LoadTexture(app.renderer, "./gfx/Player2.png");
        player.pos.x -= player.speed;
        if (CheckCollisionWall(&player)) {  // 벽과 충돌 시 이동 취소
            player.pos.x += player.speed;
        }
    }
    if (app.key_right) {    // d 입력 시 위쪽으로 이동
        player.texture = IMG_LoadTexture(app.renderer, "./gfx/Player1.png");
        player.pos.x += player.speed;
        if (CheckCollisionWall(&player)) {  // 벽과 충돌 시 이동 취소
            player.pos.x -= player.speed;
        }
    }

    if (!app.spacebar_pressed && app.key_spacebar && player.gun >0 && enemy.distance < SHOTGUN_RANGE && app.shotgun_reload == 0) { //총알이 있고 사정거리 안에 있으면
        int push_x = (int)(SHOTGUN_POWER * cos(enemy.theta));  //SHOTGUN_POWER 수치만큼 밀쳐낼 거리를 할당
        int push_y = (int)(SHOTGUN_POWER * sin(enemy.theta));

        app.shotgun_reload = SHOTGUN_TERM; // app.shotgun_reload 멤버에 재장전 시간 할당
        app.spacebar_pressed = 1;   // 스페이스바 push 여부 app.spacebar_pressed 멤버에 저장

        enemy.pos.x += push_x;  // x축 방향으로 push_x만큼 적을 밀쳐냄
        enemy.pos.y += push_y;  // y축 방향으로 push_y만큼 적을 밀쳐냄
        

        /* 밀쳐낸 적이 벽에 부딪쳤을 시 위치를 벽에 맞게 조정 */
        if(enemy.pos.x < WALL_THICKNESS2){ 
            enemy.pos.x = WALL_THICKNESS2;
            }
        else if(enemy.pos.x > SCREEN_WIDTH - ENEMY_WIDTH - WALL_THICKNESS2){
            enemy.pos.x = SCREEN_WIDTH - ENEMY_WIDTH - WALL_THICKNESS2;
            }
        if(enemy.pos.y < WALL_THICKNESS2){
            enemy.pos.y = WALL_THICKNESS2;
            }
        else if(enemy.pos.y > SCREEN_HEIGHT - ENEMY_HEIGHT - WALL_THICKNESS2){
            enemy.pos.y = SCREEN_HEIGHT - ENEMY_HEIGHT - WALL_THICKNESS2;
            }

        
        /* 적과의 각도에 따라 플레이어가 가지고 있는 샷건의 모양을 변경 */
        if ((enemy.pos.x - player.pos.x) * tan (-M_PI / 8) <= enemy.pos.y - player.pos.y && enemy.pos.y - player.pos.y <= (enemy.pos.x - player.pos.x) * tan (M_PI / 8)){
            shotgun.texture = IMG_LoadTexture(app.renderer, "./gfx/ShotgunAct6.png");
        }

        else if ((enemy.pos.x - player.pos.x) * tan (M_PI / 8) < enemy.pos.y - player.pos.y && enemy.pos.y - player.pos.y <= (enemy.pos.x - player.pos.x) * tan (M_PI * 3 / 8)){
            shotgun.texture = IMG_LoadTexture(app.renderer, "./gfx/ShotgunAct9.png");
        }

        else if ((enemy.pos.x - player.pos.x) * tan (-3 * M_PI / 8) <= enemy.pos.y - player.pos.y && enemy.pos.y - player.pos.y < (enemy.pos.x - player.pos.x) * tan (- M_PI / 8)){
            shotgun.texture = IMG_LoadTexture(app.renderer, "./gfx/ShotgunAct3.png");
        }

        else if ((-enemy.pos.x + player.pos.x) * tan (-M_PI / 8) <= enemy.pos.y - player.pos.y && enemy.pos.y - player.pos.y <= (-enemy.pos.x + player.pos.x) * tan (M_PI / 8)){
            shotgun.texture = IMG_LoadTexture(app.renderer, "./gfx/ShotgunAct4.png");
        }

        else if ((-enemy.pos.x + player.pos.x) * tan (M_PI / 8) < enemy.pos.y - player.pos.y && enemy.pos.y - player.pos.y <= (-enemy.pos.x + player.pos.x) * tan (M_PI * 3 / 8)){
            shotgun.texture = IMG_LoadTexture(app.renderer, "./gfx/ShotgunAct7.png");
        }

        else if ((-enemy.pos.x + player.pos.x) * tan (-3 * M_PI / 8) <= enemy.pos.y - player.pos.y && enemy.pos.y - player.pos.y < (-enemy.pos.x + player.pos.x) * tan (- M_PI / 8)){
            shotgun.texture = IMG_LoadTexture(app.renderer, "./gfx/ShotgunAct1.png");
        }

        else if (enemy.pos.y > player.pos.y){
            shotgun.texture = IMG_LoadTexture(app.renderer, "./gfx/ShotgunAct8.png");
        }
        else{
            shotgun.texture = IMG_LoadTexture(app.renderer, "./gfx/ShotgunAct2.png");
        }
        


    }

    else{ // 샷건을 발사하는 상황이 아닐 시

        if (app.shotgun_reload > 0){ // 아직 장전이 되지 않은 상태라면 아래 코드를 실행
            if (app.shotgun_reload < SHOTGUN_TERM * 2 / 3){ // 발사 후 시간이 지나면 샷건의 각도를 원래대로 초기화
                shotgun.texture = IMG_LoadTexture(app.renderer, "./gfx/ShotgunBase.png");
            }
            --app.shotgun_reload; // 샷건 장전 변수 조정
        }
        else{ // 장전이 완료되었을 시
            app.shotgun_reload = 0;
        }

        /* 적이 사정거리 내에 있을 시 스페이스바가 떼졌다면 app.spacebar_pressed 변수를 0으로 초기화 */
        if (!app.key_spacebar && player.gun >0 && enemy.distance < SHOTGUN_RANGE){
            app.spacebar_pressed = 0;
        }

    }

    if(!app.key_spacebar){ // 스페이스바가 떼져 있다면 샷건의 각도를 원래대로 초기화
        shotgun.texture = IMG_LoadTexture(app.renderer, "./gfx/ShotgunBase.png");
    }
    return;
}

/* 적의 움직임을 실행하는 함수이다. 적의 사망 판정, 플레이어 추적 동작을 시행한다. */
void ActEnemy(void) {

        if (app.map == 2 && enemy.health <= 0){ // 적의 상태를 판정하여 사망 시 그에 대한 함수를 실행한다.
            ActEnemyDie();
            return;
        }

        enemy.pos.x -= (int)(enemy.speed * cos(enemy.theta)); // 적은 자신의 속도만큼 플레이어를 추적한다.
        enemy.pos.y -= (int)(enemy.speed * sin(enemy.theta));


        if(enemy.pos.x > player.pos.x){     // 왼쪽으로 이동 시
            if (enemy.burning != 1){        // 적의 상태에 따라 다른 모습을 출력한다.
                enemy.texture = IMG_LoadTexture(app.renderer, "./gfx/Enemy2.png");
            }

            else{
                enemy.texture = IMG_LoadTexture(app.renderer, "./gfx/BurnedEnemy2.png");
            }
        }

        else{                           // 오른쪽으로 이동 시
            if (enemy.burning != 1){    // 적의 상태에 따라 다른 모습을 출력한다.
                enemy.texture = IMG_LoadTexture(app.renderer, "./gfx/Enemy1.png");
            }

            else{
                enemy.texture = IMG_LoadTexture(app.renderer, "./gfx/BurnedEnemy1.png");
            }
        }

        return;

}


/* 적과 못의 충돌여부를 판단하는 함수이다. 충돌 시 적의 체력을 깎고 사라진다. */
void ScrewUsed(void) {

    if(screw.pos.x < SCREEN_WIDTH && CheckCollisionObjects(&enemy, &screw)){ // 적과 못이 충돌했을 시 아래 함수를 실행
        enemy.health -=1;       // enemy 체력 하나 깎임
        ClearEntity(&screw);    // screw Entity Clear
    }

    return;
}

/* 적과 벽난로 불의 충돌여부를 판단하는 함수이다. 충돌 시 적의 체력과 속도를 깎고 상태를 변화시킨 뒤 사라진다. */
void FireUsed(void) {

    if(fire.pos.x < SCREEN_WIDTH && CheckCollisionObjects(&enemy, &fire)){  // 적과 벽난로 불이 충돌했을 시 아래 함수를 실행
        enemy.health -=1;   // enemy 체력 하나 깎임
        enemy.burning = 1;  // 적 상태 변경
        enemy.speed -=1;    // 적 속도 감소
        ClearEntity(&fire); //fire Entity Clear
    }

    return;
}

/* 적과 선인장의 충돌여부를 판단하는 함수이다. 충돌 시 적의 체력을 깎고 속도를 증가시킨 뒤 모습을 바꾼다. */
void CactusUsed(void) {

    if(cactus.health>0){

        if(CheckCollisionObjects(&enemy, &cactus)){ // 적과 선인장이 충돌했을 시 아래 함수를 실행
            enemy.health -=1;   // enemy 체력 하나 깎임
            enemy.speed +=1;    // 적 속도 증가
            cactus.health = 0;  // 선인장 체력 감소 (충돌 일어나지 않음)
            cactus.texture = IMG_LoadTexture(app.renderer, "./gfx/Cactus2.png"); // 선인장 모습 변경
        }

    }

    return;
}


/* 거미의 움직임을 제어하는 함수이다. 일정 범위 내에서 랜덤하게 움직이고 벽과 충돌하면 방향을 바꾼다. */
void SpiderMovement(void){ 

    if(spider.health==0){ // 거미의 체력이 0일 시(움직이지 않을 때)

        if( abs(player.pos.x-spider.pos.x)<80 && abs(player.pos.y-spider.pos.y)<80){ // 플레이어가 일정 범위 안에 들어가면 아래 코드를 실행
            spider.health =1; // 거미가 활성화된다.
        }

    }

    if(spider.health==1){   // 거미가 활성화되었다면 아래 코드를 실행

        if (CheckCollisionWall(&spider)==1) {  //   양옆 벽에 충돌 시
            spider.x_val = -spider.x_val; // x방향 속도를 반전

        }

        else if(CheckCollisionWall(&spider)==2){ //위아래 벽에 충돌 시
            spider.y_val = -spider.y_val;   // y방향 속도를 반전
        }    

        spider.pos.x += SPIDER_SPEED*spider.x_val*RandInt(1,4); // 랜덤한 값 이내로 거미의 위치를 제어
        spider.pos.y += SPIDER_SPEED*spider.y_val*RandInt(1,4);
    }

    return;
}

/* 적과 덫의 충돌여부를 판단하는 함수이다. 충돌 시 적의 체력을 깎은 뒤 비활성화하고 모습을 바꾼다. */
void TrapUsed(void) {

    if(trap.health>0){ // 덫이 활성화되어있을 시

        if(CheckCollisionObjects(&enemy, &trap)){ //적과 덫의 충돌 여부를 확인
            enemy.health -=1;   // 적의 체력을 1 감소
            trap.health = 0;    // 덫을 비활성화
            trap.texture = IMG_LoadTexture(app.renderer, "./gfx/Trapfold.png"); // 닫혀있는 모습으로 모습을 변경
        }

    }

    return;
}

/* 적과 끈끈한 바닥의 충돌여부를 판단하는 함수이다. 바닥 위에 있을 시 플레이어의 속도를 느리게 한다. */
void Onthefloor(void){

    if(CheckCollisionObjects(&player,&stickyfloor)){    //플레이어가 바닥 위에 있을 시 아래 코드를 실행
        player.speed = 2;   // 플레이어의 속도를 감소시킨다.
    }

    else{   // 바닥을 벗어났을 시 아래 코드를 실행
        player.speed = PLAYER_SPEED; // 플레이어의 속도를 원래대로 되돌린다.
    }

    return;
}

/* 플레이어 오브젝트와 샷건 오브젝트의 충돌여부를 판단하고, 소지 여부를 판단하는 함수이다. */
void ShotgunUse(void) {

    if(player.gun==0){ // 플레이어가 총을 소지하지 않고 있을 시

        if(abs(player.pos.x-(shotgun.pos.x+48)) < 30 && abs(player.pos.y-(shotgun.pos.y+48)) < 60){ // 플레이어가 맵에 있는 총에 접근하였을 시
        player.gun = 1; // 플레이어의 gun 멤버를 1로 변경한다 (총 소지)
        }

    }

    else if(player.gun ==1){ // 플레이어가 총을 소지하고 있을 시

        shotgun.pos.x = player.pos.x -48;   // 플레이어 위에 shotgun 오브젝트를 겹친다.
        shotgun.pos.y = player.pos.y -48;
    }

    return;
}


/* 플레이어와 장애물 오브젝트의 충돌 여부를 검사하는 함수이며, 충돌 시 체력을 0으로 만든다. */
void ActCheckDeath(void) {

    if(CheckCollisionObjects(&player, &enemy)) { // 적과 충돌했을 시
        player.health = 0;  // 플레이어 사망
    }
    if(CheckCollisionObjects(&player, &screw)) {// 못과 충돌했을 시
        player.health = 0;  // 플레이어 사망
    }
    if(CheckCollisionObjects(&player, &fire)) {// 벽난로 불과 충돌했을 시
        player.health = 0;  // 플레이어 사망
    }
    if(cactus.health>0 && CheckCollisionObjects(&player, &cactus)) {// 선인장과 충돌했을 시
        player.health = 0;  // 플레이어 사망        
    }
    if(CheckCollisionObjects(&player, &spider)) {// 거미와 충돌했을 시
        player.health = 0;  // 플레이어 사망
    }
    if(trap.health>0 && CheckCollisionObjects(&player, &trap)) {// 덫과 충돌했을 시
        player.health = 0;  // 플레이어 사망
    }
   
    return;
}


/* 플레이어와 상호 작용 오브젝트의 충돌 여부, 스페이스바 push 여부를 검사하여 코드를 실행하는 함수 */
void ActInteraction(void){

    if (app.key_spacebar && CheckCollisionObjects(&interact_obj[0],&player)){ // 도구 오브젝트와 상호작용할 시
        InitBoard(4);       // 도구 획득 보드 출력
        DrawGame();         // 화면 렌더링
        ShowWindow();       // 화면 출력
        SDL_Delay(1000);    // 대기
        app.tool = 1;       // 도구 획득

        return;
    }

    else if (app.tool == 1){  // 도구를 이미 획득하였을 시
        interact_obj[0].pos.x = SCREEN_WIDTH +1;    // 도구 오브젝트를 Clear
        interact_obj[0].pos.y = SCREEN_HEIGHT +1;
        ClearBoard(&tool_get);   // 도구 획득 보드를 Clear
    }

    if (app.fix_count == 0 && app.key_spacebar && CheckCollisionObjects(&interact_obj[1],&player)){ // 회로 1 오브젝트와 상호작용할 시

        if (app.tool){  // 도구를 가지고 있을 시 아래 코드를 실행

            app.map = 0; // app.map 멤버를 초기화
            app.stage = 1;  //  app.stage 변수를 1로 설정
            ActInitstage(app.stage);    // app.stage에 해당하는 스테이지 init

            return;
        }

        else{   // 도구를 가지고 있지 않을 시 아래 코드를 실행
            InitBoard(10);  // 도구 필요 보드 출력
        }

    }

    else{   // 회로 1 오브젝트와 상호작용하지 않을 시

        ClearBoard(&tool_need); // 도구 필요 보드를 Clear
    }


    if (app.key_spacebar && CheckCollisionObjects(&interact_obj[2],&player)){   // 회로 2 오브젝트와 상호작용할 시

        if (app.fix_count == 1){    // fix_count가 1일 시 아래 코드를 실행

            app.map = 0;    // app.map 멤버를 초기화
            app.stage = 2;  //  app.stage 변수를 2로 설정
            ActInitstage(app.stage);    // app.stage에 해당하는 스테이지 init

            return;
        }

        else{   // fix_count가 1이 아닐 시 아래 코드를 실행
            InitBoard(11);  // 전원 필요 보드 출력
        }

    }

    else if (app.key_spacebar && CheckCollisionObjects(&interact_obj[3],&player)){   // 회로 3 오브젝트와 상호작용할 시

        if (app.fix_count == 2){    // fix_count가 2일 시 아래 코드를 실행

            app.map = 0;   // app.map 멤버를 초기화
            app.stage = 3;  //  app.stage 변수를 3으로 설정
            ActInitstage(app.stage);    // app.stage에 해당하는 스테이지 init

            return;
        }

        else{   // fix_count가 2가 아닐 시 아래 코드를 실행
            InitBoard(11); // 전원 필요 보드 출력
        }

    }

    else if (app.key_spacebar && CheckCollisionObjects(&interact_obj[4],&player)){   // 키패드 오브젝트와 상호작용할 시

        if (app.fix_count ==3){    // fix_count가 3일 시 아래 코드를 실행

            app.keypad_on = 1;  // app.keypad_on 변수를 1로 설정
            ActInitkeypad();    // 키패드 init

            return;
        }

        else{   // fix_count가 3가 아닐 시 아래 코드를 실행
            InitBoard(11);  // 전원 필요 보드 출력
        }

    }

    else{   // 회로 2, 3, 키패드 오브젝트와 상호작용하지 않을 시
        ClearBoard(&power_need);    // 전원 필요 보드 Clear
    }


    if (app.key_spacebar && CheckCollisionObjects(&interact_obj[5],&player)){   // 달력 오브젝트와 상호작용할 시

        InitBoard(6);   // 달력 보드 출력
        return;
    }

    else{   // 달력 오브젝트와 상호작용하지 않을 시
        ClearBoard(&calendar);  // 달력 보드 Clear
    }


    if (app.key_spacebar && CheckCollisionObjects(&interact_obj[6],&player)){   // 시체 오브젝트와 상호작용할 시
        InitBoard(7);   // 시체 텍스트 보드 출력
        return;
    }

    else{  // 시체 오브젝트와 상호작용하지 않을 시
        ClearBoard(&corpse_text);   // 시체 텍스트 보드 Clear
    }

    if (app.key_spacebar && CheckCollisionObjects(&interact_obj[7],&player)){   // 창문 오브젝트와 상호작용할 시
        InitBoard(8);   // 창문 보드 출력
        return;
    }

    else{
        ClearBoard(&window);    // 창문 보드 Clear
    }


    if (app.key_spacebar && CheckCollisionObjects(&interact_obj[8],&player)){   // 낙서 오브젝트와 상호작용할 시
        InitBoard(9);   // 낙서 보드 출력
        return;
    }

    else{
        ClearBoard(&mark);  // 낙서 보드 Clear
    }

    if (app.key_spacebar && CheckCollisionObjects(&interact_obj[9],&player)){   // 문 오브젝트와 상호작용할 시

        if (app.door_key == 1){ // 열쇠를 가지고 있다면 아래 코드를 실행
            app.game_clear = 1; // app.game_clear 멤버 1로 변경 (게임 클리어 여부 저장)
            return;
        }

        InitBoard(12);  // 열쇠 필요 보드 출력
        return;
    }

    else{
        ClearBoard(&key_need);  // 열쇠 필요 보드 Clear
    }

    if (!app.door_key && app.key_spacebar && CheckCollisionObjects(&interact_obj[10],&player)){   // 적 시체 오브젝트와 상호작용할 시
        InitBoard(13);      // 열쇠 획득 보드 출력
        DrawGame();         // 화면 렌더링
        ShowWindow();       // 화면 출력
        SDL_Delay(1000);    // 딜레이
        app.door_key = 1;   // 열쇠 소유 여부 변경
        return;
    }

    else if (app.door_key == 1){    // 열쇠를 가지고 있을 시
        ClearBoard(&key_get);    // 열쇠 획득 보드 Clear
    }

}

/*************ActGame+***************/

/* 외부로부터 int값으로 맵을 받아 해당 맵의 오브젝트를 init하고, 전역변수를 초기화한다. */
void ActInitmap(int map){
    app.stage = 0;  // 논리회로 퍼즐 스테이지를 초기화

    switch(map){ // map에 따라 다른 코드 실행

        case 1: // map1일 시 1번 맵 오브젝트를 init

            InitBackGround(1); // 1번 배경 init
            InitPlayer();       // 플레이어 init
            InitInteractObj();  // 상호작용 오브젝트 init

            app.tool = 0;       // 수리 도구 소유여부 초기화
            app.fix_count = 0;  // 회로 수리 카운트 초기화

            ClearEntity(&shotgun);  // 샷건 구조체를 clear
            ClearEntity(&enemy);    // 적 구조체를 clear

            break;

        case 2:// map2일 시 2번 맵 오브젝트를 init

            InitBackGround(2);  // 2번 배경 init
            InitPlayer();       // 플레이어 init
            InitEnemy();        // 적 init
            InitScrew();        // 못(장애물) init
            InitFire();         // 벽난로 불(장애물) init
            InitCactus();       // 선인장(장애물) init
            InitSpider();       // 거미(장애물) init
            InitStickyfloor();  // 끈끈한 바닥(장애물) init
            InitTrap();         // 덫(장애물) init
            InitShotgun();      // 샷건(아이템) init

            for (int i = 0; i < 9; ++i){    // 상호작용 오브젝트 Clear
                ClearEntity(&interact_obj[i]);
            }

            InitInteractObj();  // 상호작용 오브젝트 배치
            
            app.door_key = 0;   // 열쇠 소유 여부 초기화

            break;

        default:
            break;

    }
}

/* 적 사망 시 적을 상호작용 가능한 적 시체로 대체한다. */
void ActEnemyDie(void){

        if (enemy.pos.x < SCREEN_WIDTH){    // 적이 화면 안에 있을 시
            interact_obj[10].pos.x = enemy.pos.x;   // 적 위치에 상호작용 가능한 오브젝트를 배치한다.
            interact_obj[10].pos.y = enemy.pos.y;
        }

        enemy.pos.x = SCREEN_WIDTH + 100;   // 플레이어의 샷건과 상호작용하지 않도록 충분히 먼 위치에 적을 clear
        enemy.pos.y = SCREEN_HEIGHT +100;
}

/*----------------------------------------------ActPuzzle--------------------------------------------- */

/* Puzzle 실행 시 main loop를 통해 실행할 퍼즐 함수 ActPuzzle */
void ActPuzzle(void) { 

    ActReset(); // 리셋버튼이 눌렸는지 여부를 판단해 스테이지를 다시 시작하는 함수 ActReset
    ActPickGate(); // 플레이어가 게이트를 집어들고 제자리에, 혹은 잘못된 자리에 놓기까지 게이트의 위치를 제어하는 함수 ActPickGate
    ActPower(); // 파워버튼이 눌렸는지 여부를 판단해 해당 퍼즐의 정/오답 여부를 판단하는 함수 ActPower
    ActEsc(); //  퍼즐 실행 중 ESC 키 입력 시 퍼즐을 종료하는 함수

    return;
}

/* 리셋버튼이 눌렸는지 여부를 판단해 스테이지를 다시 시작하는 함수 ActReset */
void ActReset(void) { 

    if (app.mouse_left){ // 마우스 왼쪽버튼이 리셋버튼 위에서 눌려있으며 이전에 우클릭으로 입력을 취소하지 않은 경우 button의 select 멤버를 1로 설정
        if (app.rightcancel == 0 && button[1].pos.x <= app.mouse_x_before && app.mouse_x_before <= button[1].pos.x + button[1].pos.w  && button[1].pos.y <= app.mouse_y_before && app.mouse_y_before <= button[1].pos.y + button[1].pos.h){
            button[1].select = 1; // 해당 버튼이 선택되었음을 구조체에 저장
        }
    }

    else{ // 마우스 왼쪽버튼이 버튼 위에서 떼진 경우 button의 select 멤버가 1이라면 ActInitstage 함수를 실행하여 스테이지를 Init, 이후 button의 select 멤버를 0으로 초기화
        if (button[1].pos.x <= app.mouse_x_current && app.mouse_x_current <= button[1].pos.x + button[1].pos.w  && button[1].pos.y <= app.mouse_y_current && app.mouse_y_current <= button[1].pos.y + button[1].pos.h){
            if (button[1].select == 1){
                ActInitstage(app.stage); // 스테이지를 불러옴
            }
        }
        button[1].select = 0; // 마우스 왼쪽버튼을 뗐으므로 해당 버튼의 선택을 취소
    }

    if (app.mouse_right){ // 우클릭을 입력했을 시 해당 버튼의 선택을 취소
        button[1].select = 0;
    }
}

/* 플레이어가 게이트를 집어들고 제자리에, 혹은 잘못된 자리에 놓기까지 게이트의 위치를 제어하는 함수 ActPickGate */
void ActPickGate(void) { 

    for (int i = 0; i < MAX_GATE; ++i){ // Gate 칩을 순회하며 게이트의 위치를 제어

        if (app.mouse_left){ // 게이트 위에서 좌클릭이 입력되었으며 우클릭으로 취소되지 않았을 시 아래 함수를 실행 (게이트 클릭 및 드래그에 해당)
            if (app.rightcancel == 0 && gate[i].temporary_x <= app.mouse_x_before && app.mouse_x_before <= gate[i].temporary_x + gate[i].pos.w  && gate[i].temporary_y <= app.mouse_y_before && app.mouse_y_before <= gate[i].temporary_y + gate[i].pos.h){
                gate[i].select = 1; // 해당 Gate의 select 멤버를 1로 설정
                gate[i].pos.x = app.mouse_x_current - gate[i].pos.w / 2; // 마우스 위치로 Gate의 중앙을 이동시킴
                gate[i].pos.y = app.mouse_y_current - gate[i].pos.h / 2;
                gate[i].in_slot = 0; // gate가 slot에 들어가 있는지 여부를 0으로 초기화

                for (int j = 0; j < MAX_SLOT ; ++j){ // chip slot을 순회하며 slot에 gate를 장착시키고 Gate 및 Slot 위치와 상태를 업데이트, 마우스가 slot 위에 있을 시 실행
                    if (slot[j].pos.x < app.mouse_x_current && app.mouse_x_current < slot[j].pos.x + slot[j].pos.w && slot[j].pos.y < app.mouse_y_current && app.mouse_y_current < slot[j].pos.y + slot[j].pos.h){
                        if (slot[j].chip_type && (gate[i].chip_type != slot[j].chip_type)){ // 해당 슬롯에 다른 칩이 이미 들어가 있을 시 칩 배치 skip
                            continue;
                        }
                        
                        gate[i].pos.x = slot[j].pos.x + 5; // 선택된 gate의 위치를 마우스 아래 해당 slot에 배치
                        gate[i].pos.y = slot[j].pos.y + 5;

                        gate[i].temporary_x = gate[i].pos.x; // 선택된 gate의 임시 위치를 할당 (현재 선택된 slot 위치)
                        gate[i].temporary_y = gate[i].pos.y;

                        app.mouse_x_before = gate[i].pos.x; // gate가 slot에 들어간 뒤에도 드래그가 가능하도록 mouse의 before 좌표를 초기화
                        app.mouse_y_before = gate[i].pos.y;

                        gate[i].in_slot = 1; // 해당 gate가 슬롯 안에 들어가 있는지 여부를 저장
                        slot[j].chip_type = gate[i].chip_type; // 해당 slot의 chip_type 멤버에 해당 gate의 chip_type 멤버를 저장


                    }
                }

            }
        }

        else{ // 마우스 왼쪽버튼이 떼졌을 시 아래 함수를 실행
            if (gate[i].select == 1 && gate[i].in_slot == 0 && !app.rightcancel){ // 게이트가 선택되었으나 슬롯에 들어가지 않은 채로 마우스 왼쪽버튼이 떼진 경우 아래 함수를 실행 (우클릭 취소가 아닌 경우)
                gate[i].temporary_x = gate[i].original_x; // gate의 임시 위치를 gate가 있던 원래 위치로 초기화
                gate[i].temporary_y = gate[i].original_y;

                gate[i].pos.x = gate[i].temporary_x; // gate의 위치를 gate가 원래 있던 위치로 초기화
                gate[i].pos.y = gate[i].temporary_y;
                

            }

            for (int j = 0; j < MAX_SLOT; ++j){ // slot을 순회하며 아래 코드를 실행
                if (gate[slot[j].chip_type - 1].pos.y != slot[j].pos.y + 5){ // 슬롯의 chip_type에 해당하는 Gate가 다른 곳에 있을 시 슬롯의 chip_type을 초기화
                    slot[j].chip_type = 0;
                }
            }

            gate[i].select = 0; // 마우스 왼쪽 버튼이 떼졌으므로 gate의 선택 여부를 초기화
        }

        if (app.mouse_right){ // 마우스 우클릭 시
            app.rightcancel = 1; // 우클릭 취소 여부를 저장
            gate[i].pos.x = gate[i].temporary_x; // gate 위치를 임시 위치로 이동
            gate[i].pos.y = gate[i].temporary_y;
        }

    }
}

/* 파워버튼이 눌렸는지 여부를 판단해 해당 퍼즐의 정/오답 여부를 판단하는 함수 ActPower */
void ActPower(void) { 

    if (app.mouse_left){ // 마우스 왼쪽버튼이 파워버튼 위에서 눌려있으며 이전에 우클릭으로 입력을 취소하지 않은 경우 button의 select 멤버를 1로 설정 
        if (app.rightcancel == 0 && button[0].pos.x <= app.mouse_x_before && app.mouse_x_before <= button[0].pos.x + button[0].pos.w  && button[0].pos.y <= app.mouse_y_before && app.mouse_y_before <= button[0].pos.y + button[0].pos.h){
            button[0].select = 1;
        }
    }

    else{ // 마우스 왼쪽버튼이 버튼 위에서 떼진 경우 button의 select 멤버가 1이라면 PowerOn 함수를 실행, 이후 button의 select 멤버를 0으로 초기화
        if (button[0].pos.x <= app.mouse_x_current && app.mouse_x_current <= button[0].pos.x + button[0].pos.w  && button[0].pos.y <= app.mouse_y_current && app.mouse_y_current <= button[0].pos.y + button[0].pos.h){
            if (button[0].select == 1){

                PowerOn(app.stage); // stage를 입력받아 해당 stage의 gate 배치를 검사해 정/오답 여부를 판단하는 함수 PowerOn 실행
            }
        }
        
        button[0].select = 0; // select 멩버 초기화
    }

    if (app.mouse_right){ // 우클릭을 입력했을 시 해당 버튼의 선택을 취소
        button[0].select = 0;
    }
}

/* 논리 회로 또는 키패드 퍼즐 실행 중 ESC 키 입력 시 퍼즐을 종료하는 함수 */
void ActEsc(void){
    if (app.key_esc){   // esc 키가 눌려 있을 시

        ClearPuzzle();  // 논리 회로 퍼즐을 Clear
        ClearKeypad();  // 키패드 퍼즐을 Clear

        app.stage = 0;  // 논리회로 퍼즐 스테이지 초기화
        app.keypad_on = 0;  // 키패드 퍼즐 실행여부 초기화
        app.map = 1;    // app.map 구조체 1 할당하여 퍼즐을 빠져나옴
    }
}

/*************ActPuzzle+***************/

/* 함수 호출 또는 reset버튼 클릭 시 입력된 스테이지를 시작 */
void ActInitstage(int stage){ 

    switch(stage){ // stage에 따라 다른 코드 실행
        case 1: // stage1일 시 1번 퍼즐 배경과 파워버튼, 리셋버튼, gate와 stage에 맞는 slot을 init
            InitBoard(1);
            InitButton();
            InitGate();
            InitSlot(1);
            break;

        case 2: // stage2일 시 2번 퍼즐 배경과 파워버튼, 리셋버튼, gate와 stage에 맞는 slot을 init
            InitBoard(2);
            InitButton();
            InitGate();
            InitSlot(2);
            break;

        case 3: // stage3일 시 3번 퍼즐 배경과 파워버튼, 리셋버튼, gate와 stage에 맞는 slot을 init
            InitBoard(3);
            InitButton();
            InitGate();
            InitSlot(3);
            break;

        default:
            break;

    }
}

/* stage를 입력받아 해당 stage의 gate 배치를 검사해 정/오답 여부를 판단하는 함수 PowerOn */
void PowerOn(int stage){ 

    int tmp1 = 0, tmp2 = 0, tmp3 = 0, tmp4 = 0, tmp5 = 0, tmp6 = 0, tmp7 = 0, tmp8 = 0; // Gate의 출력신호를 저장할 변수 tmp 1~8

    int correct = 1; // 퍼즐의 정답 여부를 저장할 변수 correct. 전부 정답 시 1, 오답시 0

    switch (stage){ // stage에 따라 다른 코드 실행
        case 1: // stage 1인 경우

            // Gate에 신호 입력 및 tmp 변수에 출력신호 저장
            tmp1 = Logic(slot[0].chip_type, SIGNAL_0, SIGNAL_1,SIGNAL_UNDEFINED); 
            tmp2 = Logic(slot[1].chip_type, SIGNAL_0, SIGNAL_1,SIGNAL_UNDEFINED);
            tmp3 = Logic(slot[2].chip_type, SIGNAL_UNDEFINED, SIGNAL_UNDEFINED,SIGNAL_A);
            tmp4 = Logic(slot[3].chip_type, SIGNAL_UNDEFINED, SIGNAL_UNDEFINED,SIGNAL_B);


            // 정답 여부를 판별해 Receiver의 상태 변환

            if (tmp1 == SIGNAL_0){
                InitReceiver(1, 0, PUZZLE_X + 1036,PUZZLE_Y + 125);
            }
            else{
                InitReceiver(2, 0, PUZZLE_X + 1036,PUZZLE_Y + 125);
                correct = 0;
            }

            if (tmp2 == SIGNAL_1){
                InitReceiver(1, 1, PUZZLE_X + 1036,PUZZLE_Y + 215);
            }
            else{
                InitReceiver(2, 1, PUZZLE_X + 1036,PUZZLE_Y + 215);
                correct = 0;
            }

            if (tmp3 == SIGNAL_A){
                InitReceiver(1, 2, PUZZLE_X + 1036,PUZZLE_Y + 305);
            }
            else{
                InitReceiver(2, 2, PUZZLE_X + 1036,PUZZLE_Y + 305);
                correct = 0;
            }

            if (tmp4 == SIGNAL_BP){
                InitReceiver(1, 3, PUZZLE_X + 1036,PUZZLE_Y + 395);
            }
            else{
                InitReceiver(2, 3, PUZZLE_X + 1036,PUZZLE_Y + 395);
                correct = 0;
            }

            break;

        case 2: // stage 2인 경우

            // Gate에 신호 입력 및 tmp 변수에 출력신호 저장
            tmp1 = Logic(slot[0].chip_type, SIGNAL_UNDEFINED, SIGNAL_UNDEFINED, SIGNAL_1);
            tmp2 = Logic(slot[1].chip_type, SIGNAL_0, SIGNAL_A, SIGNAL_UNDEFINED);
            tmp3 = Logic(slot[2].chip_type, SIGNAL_1, SIGNAL_B, SIGNAL_UNDEFINED);
            tmp4 = Logic(slot[3].chip_type, SIGNAL_B, SIGNAL_BP, SIGNAL_UNDEFINED);

            // 정답 여부를 판별해 Receiver의 상태 변환
            if (Logic(2, tmp1, tmp2, SIGNAL_UNDEFINED) == SIGNAL_0){
                InitReceiver(1, 0, PUZZLE_X + 1036, PUZZLE_Y + 216);
            }
            else{
                InitReceiver(2, 0, PUZZLE_X + 1036, PUZZLE_Y + 216);
                correct = 0;
            }

            if (Logic(3, tmp2, tmp3, SIGNAL_UNDEFINED) == SIGNAL_0){
                InitReceiver(1, 1, PUZZLE_X + 1036, PUZZLE_Y + 305);
            }
            else{
                InitReceiver(2, 1, PUZZLE_X + 1036, PUZZLE_Y + 305);
                correct = 0;
            }

            if (tmp4 == SIGNAL_1){
                InitReceiver(1, 2, PUZZLE_X + 1036, PUZZLE_Y + 395);
            }
            else{
                InitReceiver(2, 2, PUZZLE_X + 1036, PUZZLE_Y + 395);
                correct = 0;
            }

            break;


        case 3: // stage 3인 경우

            // Gate에 신호 입력 및 tmp 변수에 출력신호 저장
            tmp1 = Logic(slot[0].chip_type, SIGNAL_UNDEFINED, SIGNAL_UNDEFINED, SIGNAL_B);
            tmp2 = Logic(slot[1].chip_type, SIGNAL_UNDEFINED, SIGNAL_UNDEFINED, SIGNAL_B);
            tmp4 = Logic(slot[3].chip_type, SIGNAL_1, SIGNAL_A, SIGNAL_UNDEFINED);
            tmp3 = Logic(slot[2].chip_type, SIGNAL_0, tmp4, SIGNAL_UNDEFINED);
            tmp5 = Logic(slot[4].chip_type, tmp1, tmp2, SIGNAL_UNDEFINED);
            tmp6 = Logic(slot[5].chip_type, tmp1, tmp2, SIGNAL_UNDEFINED);
            tmp7 = Logic(slot[6].chip_type, tmp1, tmp2, SIGNAL_UNDEFINED);
            tmp8 = Logic(slot[7].chip_type, Logic(6,SIGNAL_1,Logic(1,SIGNAL_1,tmp3,SIGNAL_UNDEFINED),SIGNAL_UNDEFINED), Logic(3,tmp3,tmp4,SIGNAL_UNDEFINED), SIGNAL_UNDEFINED);

            // 정답 여부를 판별해 Receiver의 상태 변환
            if (tmp5 == SIGNAL_0){
                InitReceiver(1, 0, PUZZLE_X + 1036, PUZZLE_Y + 35);
            }
            else{
                InitReceiver(2, 0, PUZZLE_X + 1036, PUZZLE_Y + 35);
                correct = 0;
            }

            if (tmp6 == SIGNAL_0){
                InitReceiver(1, 1, PUZZLE_X + 1036, PUZZLE_Y + 125);
            }
            else{
                InitReceiver(2, 1, PUZZLE_X + 1036, PUZZLE_Y + 125);
                correct = 0;
            }

            if (tmp7 == SIGNAL_0){
                InitReceiver(1, 2, PUZZLE_X + 1036, PUZZLE_Y + 215);
            }
            else{
                InitReceiver(2, 2, PUZZLE_X + 1036, PUZZLE_Y + 215);
                correct = 0;
            }

            if (tmp8 == SIGNAL_1){
                InitReceiver(1, 3, PUZZLE_X + 1036, PUZZLE_Y + 305);
            }
            else{
                InitReceiver(2, 3, PUZZLE_X + 1036, PUZZLE_Y + 305);
                correct = 0;
            }

            if (Logic(1,SIGNAL_1,tmp3,SIGNAL_UNDEFINED) == SIGNAL_AP){
                InitReceiver(1, 4, PUZZLE_X + 1036, PUZZLE_Y + 395);
            }
            else{
                InitReceiver(2, 4, PUZZLE_X + 1036, PUZZLE_Y + 395);
                correct = 0;
            }

            if (Logic(3,tmp3,tmp4,SIGNAL_UNDEFINED) == SIGNAL_0){
                InitReceiver(1, 5, PUZZLE_X + 1036, PUZZLE_Y + 485);
            }
            else{
                InitReceiver(2, 5, PUZZLE_X + 1036, PUZZLE_Y + 485);
                correct = 0;
            }

            break;

        default:
            break;

    }

    if (correct == 1){  // 모든 리시버의 상태가 correct일 시

        DrawGame();     // 화면 렌더링
        ShowWindow();   // 화면 출력

        SDL_Delay(1000);    // 딜레이

        ClearPuzzle();  // 논리 회로 퍼즐 Clear

        app.stage = 0;  // 논리 회로 스테이지 변수 초기화
        app.map = 1;    // app.map 멤버를 바꿔 퍼즐에서 빠져나옴
        app.fix_count ++ ;  // app.fix_count 멤버를 1 증가

        ClearEntity(&interact_obj[stage]);  // 스테이지에 해당하는 상호작용 오브젝트 clear
    }
}



/*----------------------------------------------ActKeypad--------------------------------------------- */

/* 마우스로 키패드 번호 입력받는 함수 ActKeypad */
void ActKeypad(void){

    int code = -1;  // 입력받는 코드값 초기화

    /* 마우스가 키패드 위에 있을 시 해당 키 값을 code변수에 저장 */
    if (keybutton[1].pos.x <= app.mouse_x_current && app.mouse_x_current <= keybutton[3].pos.x + 108 && keybutton[1].pos.y <= app.mouse_y_current && app.mouse_y_current <= keybutton[10].pos.y + 108){
    
        for (int i = 0; i < 12; ++i){

            if (keybutton[i].pos.x <= app.mouse_x_current && app.mouse_x_current <= keybutton[i].pos.x + 108 && keybutton[i].pos.y <= app.mouse_y_current && app.mouse_y_current <= keybutton[i].pos.y + 108){
                code = i;
                break;
            }
        }
    }
    
    /* 마우스 아래 있는 키 값을 ActKeypress 함수로 전달 */
    if (code != -1){
        ActKeypress(code);
    }

    /* esc 입력 여부 검사 */
    ActEsc();

    return;
}

 /* 리셋버튼이 눌렸는지 여부를 판단해 스테이지를 다시 시작하는 함수 ActReset */
void ActKeypress(int key) {

    if (app.mouse_left){ // 마우스 왼쪽버튼이 키 버튼 위에서 눌려있으며 이전에 우클릭으로 입력을 취소하지 않은 경우 button의 select 멤버를 1로 설정
        if (app.rightcancel == 0 && keybutton[key].pos.x <= app.mouse_x_before && app.mouse_x_before <= keybutton[key].pos.x + keybutton[key].pos.w  && keybutton[key].pos.y <= app.mouse_y_before && app.mouse_y_before <= keybutton[key].pos.y + keybutton[key].pos.h){
            keybutton[key].select = 1; // 해당 버튼이 선택되었음을 버튼의 구조체에 저장
        }
    }

    else{ // 마우스 왼쪽버튼이 버튼 위에서 떼진 경우 button의 select 멤버가 1이라면 그에 맞는 코드 실행, 이후 button의 select 멤버를 0으로 초기화
        if (keybutton[key].pos.x <= app.mouse_x_current && app.mouse_x_current <= keybutton[key].pos.x + keybutton[key].pos.w  && keybutton[key].pos.y <= app.mouse_y_current && app.mouse_y_current <= keybutton[key].pos.y + keybutton[key].pos.h){
            if (keybutton[key].select == 1){ // 버튼이 선택된 경우
                if (0 <= key && key <= 9){  // 선택된 버튼이 0~9라면
                    for (int i = 0; i < 4; ++i){    // 4번 반복하여 아래 코드를 실행
                        if (app.passcode[i] == -1){ // 아직 번호가 할당되지 않은 위치가 있을 시 아래 코드를 실행
                            app.passcode[i] = key;  // 해당 위치에 번호를 입력

                            switch (i){ // 할당된 번호 갯수에 따라 키패드 모습을 변경
                                case 0:
                                    keypad.texture = IMG_LoadTexture(app.renderer, "./gfx/Keypad1.png");
                                    break;
                                case 1:
                                    keypad.texture = IMG_LoadTexture(app.renderer, "./gfx/Keypad2.png");
                                    break;
                                case 2:
                                    keypad.texture = IMG_LoadTexture(app.renderer, "./gfx/Keypad3.png");
                                    break;
                                case 3:
                                    keypad.texture = IMG_LoadTexture(app.renderer, "./gfx/Keypad4.png");
                                    break;
                            }

                            break;
                        }
                    }
                }

                else if (key == 10){    // 입력받은 키 값이 10일 때 (x버튼)

                    for (int i = 0; i < 4; ++i){    // 4번 순회하며 아래 코드를 실행
                        app.passcode[i] = -1;   // 할당된 키 값을 전부 -1로 초기화
                    }
                    keypad.texture = IMG_LoadTexture(app.renderer, "./gfx/Keypad0.png");   // 키패드 모습을 초기화

                }

                else if (key == 11){    // 입력받은 키 값이 11일 때 (체크 버튼)

                    int inputpw = 0;    // 입력받을 패스워드 변수를 0으로 초기화
                    for (int i = 0; i < 4; ++i){ // 4번 순회하며 아래 코드를 실행

                        if (app.passcode[i] != -1){ // 해당 위치의 패스코드가 초기상태가 아닐 시 아래 코드를 실행
                            inputpw *= 10;  // 패스워드를 한 자리 올림
                            inputpw += app.passcode[i]; // 패스워드의 1의 자리에 해당 위치의 패스코드를 할당
                        }

                        else{   // 패스코드가 -1일 시 (비어있는 패스코드 값이 존재할 시)
                            inputpw = 0;    // 입력할 패스워드를 초기화
                        }
                    }
                    if (inputpw == PASSCODE){   // 입력받은 패스워드와 패스코드가 동일할 시
                        ClearKeypad();  // 키패드 오브젝트 Clear

                        app.map = 2;    // 맵 변경
                        app.keypad_on = 0;  // 키패드 퍼즐 종료
                        ActInitmap(app.map);   // 2번 map으로 초기화

                    }
                }

            }
        }

        keybutton[key].select = 0; // 마우스 왼쪽버튼을 뗐으므로 해당 버튼의 선택을 취소
    }

    if (app.mouse_right){ // 우클릭을 입력했을 시 해당 버튼의 선택을 취소
        keybutton[key].select = 0;
    }
}

/*************ActKeypad+***************/

/* 키패드 퍼즐 Init */
void ActInitkeypad(void){
    InitBoard(5);   // 키패드 보드 init
    InitKeyButton();    // 키패드 버튼 init
}


/*----------------------------------------------GameOver/End--------------------------------------------- */

/* 게임오버 시의 코드를 실행하는 함수이다. */
void ActGameOver(void) {
    InitGameOver(); // 게임오버 화면 출력
    ActGameOverScreen();    // 사용자로부터 재실행에 대한 입력을 받음

    return;
}

/* 게임오버 시에 사용자로부터 입력을 받아 맵을 재실행하는 함수이다. */
void ActGameOverScreen(void) {
    if (app.key_r) {    // 키보드 r 키가 입력되었을 시

        ActInitmap(2);  // 2번째 맵을 init
    }
    return;
}

/* 게임클리어 시의 코드를 실행하는 함수이다. */
void ActGameEnd(void) {
    InitGameEnd();  // 게임클리어 화면 출력
    ActGameEndScreen(); // 사용자로부터 프로그램 종료에 대한 입력을 받음

    return;
}

/* 게임클리어 시에 사용자로부터 입력을 받아 프로그램을 종료하는 함수이다. */
void ActGameEndScreen(void) { 
    if (app.key_esc) {  // 키보드 esc 키가 입력되었을 시
        SDL_Quit(); // 프로그램 종료
        exit(0);    // 프로그램 종료
    }
    return;
}