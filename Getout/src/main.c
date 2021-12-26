#include "main.h" // 메인 헤더파일 include

int main(void) { // main 함수 실행
    clock_t startTime; // 프레임 조정 위한 루프 시작시각 startTime 선언
    clock_t endTime; // 프레임 조정 위한 루프 종료시각 endTime 선언

    srand(time(NULL)); // 랜덤 시드 생성

    /* 1. 초기화 */
    InitMemorySet(); // 메모리 초기화
    InitSDL(); // SDL 초기화

    app.map = 1; // app 구조체에 저장된 map 수치 1로 설정
    ActInitmap(app.map); // 맵을 초기화


    app.game_clear = 0; // 게임 종료 트리거 app.game_clear 변수 초기화

    /* 2. 프로그램 무한 루프 */
    for (;;) {

        /* 루프 시작 시 startTime 변수에 시작 시각을 저장 */
        startTime = clock();

        /* (1) 빈 화면 만들기 */
        ClearWindow();

        /* (2) 키보드 입력 받기*/
        GetInput();

        /* (3) 메인 로직 수행 후 객체들 화면에 그리기 */
        if (player.health && !app.game_clear) {   //player 생존 및 게임 클리어되기 전 상태
            
            /* 논리회로 퍼즐 푸는 중일 시 */
            if (app.stage){
                ActPuzzle(); // 퍼즐 실행 루프 함수 ActPuzzle
            }

            /* 키패드 입력 중일 시 */
            else if (app.keypad_on){
                ActKeypad(); // 키패드 실행 루프 함수 ActKeypad
            }

            /* 이동 및 탐색, 전투 중일 시 */
            else{
                ActGame(); // 이동, 탐색, 전투 실행 루프 함수 ActGame
            }

            /* 화면 구성요소 렌더링 */
            DrawGame();

        } 
        
        else if (!player.health) {
            /* 게임 오버일 시 (게임 오버 화면 출력) */
            ActGameOver();
            DrawGameOver();
        }

        else if (app.game_clear){
            ActGameEnd();
            DrawGameEnd();
        }


        /* (4) 화면 보여주기 */
        ShowWindow();

        /* 루프 종료 후 endTime 변수에 종료시각을 저장, 루프 실행에 걸린 시간을 elapsed 변수에 저장 */
        endTime = clock();
        int elapsed = (int)(endTime - startTime);

        /* 일정 시간 대기 (60FPS 기준 한 프레임에 16ms) */
        if (0 <= elapsed && elapsed <= 16000){
            SDL_Delay(16-elapsed/1000);
        }
    }

    /* 프로그램 종료 */
    return 0;
}