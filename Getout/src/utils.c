
#include "utils.h" // 유틸 헤더파일 include

 /* entity가 벽과 충돌했는지를 판정하여 출돌 시 1 또는 2를 반환하는 함수 CheckCollisionWall*/
int CheckCollisionWall(Entity *object) {
    /* 맵에 따라 서로 다른 벽 위치를 설정 */
    if (app.map == 1){ 
        if (object->pos.x < WALL_THICKNESS1 || object->pos.x + object->pos.w > SCREEN_WIDTH -WALL_THICKNESS1 ||
            object->pos.y < WALL_THICKNESS1+100 || object->pos.y + object->pos.h > SCREEN_HEIGHT -WALL_THICKNESS1 + 100) {
            return 1;
        }
        else{
            return 0;
        }
    }

    else if (app.map == 2){
        if (object->pos.x < WALL_THICKNESS2 || object->pos.x + object->pos.w > SCREEN_WIDTH -WALL_THICKNESS2){
            return 1;
        }
        else if(object->pos.y < WALL_THICKNESS2 || object->pos.y + object->pos.h > SCREEN_HEIGHT -WALL_THICKNESS2) {
            return 2;
        }
        else{
            return 0;
        }
    }

    else {
        return 0;
    }
}

/* 두 개의 물체가 서로 충돌했는지 여부를 검사하여 충돌 시 1을 return하는 함수 CheckCollisionObjects */
int CheckCollisionObjects(Entity *object_a, Entity *object_b) {

    if (SDL_HasIntersection(&(object_a->pos), &(object_b->pos))) {
        return 1;
    }

    else {
        return 0;
    }
}

/* 주어진 두 정수값 사이 랜덤한 정수값을 return하는 RandInt 함수 */
int RandInt(int min_val, int max_val) {
    if (min_val >= max_val) {
        return 0;
    }
    else {
        int ranval;
        ranval = rand() % (max_val - min_val);
        ranval += min_val;

        return ranval;
    }
}

/* 주어진 두 실수값 사이 랜덤한 실수값을 return하는 RandDouble함수 */
double RandDouble(double min_val, double max_val) {

    if (min_val >= max_val) {
        return 0.0;
    }
    else {
        double ranval;
        ranval = (double)rand() / (double)RAND_MAX;
        ranval = ranval * (max_val - min_val) + min_val;

        return ranval;
    }
}

/* 두 개의 2차원 좌표를 입력받아 두 지점 사이의 거리를 실수값으로 출력하는 함수 Distance */
double Distance (double x1, double y1, double x2, double y2){
    return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}

/* gate 종류와 입력신호를 입력받아 출력신호를 출력하는 함수 Logic, 신호목록은 defs.h 참조 */
int Logic (int gate, int input1, int input2, int input3){ //gate 종류와 입력신호를 입력, input이 2개일 경우 input1, input2를 사용, input이 1개일 경우 input3을 사용
    switch(gate){ // gate 종류에 따라 다른 함수 실행

        case 1: // AND 게이트의 경우
            if (input1 == SIGNAL_0 || input2 == SIGNAL_0){ // 둘 중 어떤 신호가 0일 시 신호 0을 return
                return SIGNAL_0;
            }
            else if (input1 == SIGNAL_1){ // 둘 중 어떤 신호가 1일 시 나머지 신호를 return
                return input2;
            }
            else if (input2 == SIGNAL_1){ // 둘 중 어떤 신호가 1일 시 나머지 신호를 return
                return input1;
            }
            else if (input1 == input2){ // 입력된 신호가 동일할 시 신호를 그대로 return
                return input1;
            }
            else if (input1 != 0 && input1 == -input2){ // 입력된 신호가 반대일 시 신호 0을 return
                return SIGNAL_0;
            }
            else{
                return SIGNAL_UNDEFINED;
            }
            break;

        case 2: // OR 게이트의 경우
            if (input1 == SIGNAL_1 || input2 == SIGNAL_1){// 둘 중 어떤 신호가 1일 시 신호 1을 return
                return SIGNAL_1;
            }
            else if (input1 == SIGNAL_0){ // 둘 중 어떤 신호가 0일 시 나머지 신호를 return
                return input2;
            }
            else if (input2 == SIGNAL_0){ // 둘 중 어떤 신호가 0일 시 나머지 신호를 return
                return input1;
            }
            else if (input1 == input2){ // 입력된 신호가 동일할 시 신호를 그대로 return
                return input1;
            }
            else if (input1 != 0 && input1 == -input2){ // 입력된 신호가 보수일 시 신호 1을 return
                return SIGNAL_1;
            }
            else{
                return SIGNAL_UNDEFINED;
            }
            break;

        case 3: // XOR 게이트의 경우
            if (input1 == SIGNAL_0){ // 둘 중 어떤 신호가 0일 시 나머지 신호를 return
                return input2;
            }
            else if (input1 == SIGNAL_1){ // 둘 중 어떤 신호가 1일 시 나머지 신호의 보수신호를 return
                return -input2;
            }
            else if (input2 == SIGNAL_0){ // 둘 중 어떤 신호가 0일 시 나머지 신호를 return
                return input1;
            }
            else if (input2 == SIGNAL_1){ // 둘 중 어떤 신호가 1일 시 나머지 신호의 보수신호를 return
                return -input1;
            }
            else if (input1 != 0 && input1 == input2){  // 입력된 신호가 동일할 시 신호 0을 return
                return SIGNAL_0;
            }
            else if (input1 != 0 && input1 == -input2){ //// 입력된 신호가 보수일 시 신호 1을 return
                return SIGNAL_1;
            }
            else{
                return SIGNAL_UNDEFINED;
            }
            break;

        case 4: // BUFFER 게이트의 경우
            return input3; // 입력된 신호를 그대로 return
            break;

        case 5: // NAND 게이트의 경우
            return -(Logic(1,input1,input2,input3)); // AND 게이트 출력값의 보수값을 return
            break;

        case 6: // NOR 게이트의 경우
            return -(Logic(2,input1,input2,input3)); // OR 게이트 출력값의 보수값을 return
            break;

        case 7: // XNOR 게이트의 경우
            return -(Logic(3,input1,input2,input3)); // XOR 게이트 출력값의 보수값을 return
            break;

        case 8: // NOT 게이트의 경우
            return -(Logic(4,input1,input2,input3)); // BUFFER 게이트 출력값의 보수값을 return
            break;

        default:
            return SIGNAL_UNDEFINED;
            break;

    }
}


/* 입력받을 Entity를 화면 밖으로 치우는 함수 ClearEntity */
void ClearEntity(Entity* entity){
    entity->pos.x = SCREEN_WIDTH + 1;
    entity->pos.y = SCREEN_HEIGHT + 1;
}

/* 입력받을 Board를 화면 밖으로 치우는 함수 ClearBoard */
void ClearBoard(Board* board){
    board->pos.x = SCREEN_WIDTH + 1;
    board->pos.y = SCREEN_HEIGHT + 1;
}


/* 퍼즐 구성요소를 화면 밖으로 치우는 함수 ClearPuzzle */
void ClearPuzzle(void){

    board.pos.x = SCREEN_WIDTH + 1;
    board.pos.y = SCREEN_HEIGHT +1;

    for (int i = 0; i < MAX_BUTTON; ++i){
        button[i].pos.x = SCREEN_WIDTH + 1;
        button[i].pos.y = SCREEN_HEIGHT +1;
    }

    for (int i = 0; i < MAX_SLOT; ++i){
        slot[i].pos.x = SCREEN_WIDTH + 1;
        slot[i].pos.y = SCREEN_HEIGHT +1;
    }

    for (int i = 0; i < MAX_GATE; ++i){
        gate[i].pos.x = SCREEN_WIDTH + 1;
        gate[i].pos.y = SCREEN_HEIGHT +1;
    }

    for (int i = 0; i < MAX_RECEIVER; ++i){
        receiver[i].pos.x = SCREEN_WIDTH + 1;
        receiver[i].pos.y = SCREEN_HEIGHT +1;
    }

}

/* keypad 구성요소를 화면 밖으로 치우는 함수 ClearKeypad */
void ClearKeypad(void){
    keypad.pos.x = SCREEN_WIDTH + 1;
    keypad.pos.y = SCREEN_HEIGHT + 1;
    
    for (int i = 0; i < 12; ++i){
        keybutton[i].pos.x = SCREEN_WIDTH +1;
        keybutton[i].pos.y = SCREEN_HEIGHT +1;
    }
}