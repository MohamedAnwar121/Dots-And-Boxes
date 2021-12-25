#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <math.h>

#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"

void MainMenu();
void GameDifficulty();
void GameMode(int z);
void BeginnerUI ();
void ExpertUI();
void GameLoop(int x , int y);
void ComputerTurn();
void SaveGame();
void LoadGame();
void Scores();
void Exit();

int main(){
    system("");
    MainMenu();
    return 0;
}

void MainMenu(){
    printf("Start Game ---> enter (1) \n");
    printf("Load Game ---> enter (2) \n");
    printf("top 10 Players ---> enter (3) \n");
    printf("Exit ---> enter (4) \n");
    printf("Choose An Option = \n");
    int x;scanf("%d", &x);
    while (!(x >= 1 && x <= 4)){
        printf("Error,Please enter A number between 1 And 4 = \n" );
        scanf("%d" , &x);
    }
    switch (x) {
        case 1 : GameDifficulty();break;
        case 2 : LoadGame();break;
        case 3 : Scores();break;
        case 4 : Exit();break;
        default: break;
    }
}

void GameDifficulty(){
    printf("Choose Difficulty : \n");
    printf("Beginner (2 x 2) ---> enter (1) \n");
    printf("Expert (5 x 5) ---> enter (2) \n");
    printf("Choose An Option = \n");
    int x; scanf("%d" , &x);
    while(x != 1 && x != 2){
        printf("Error,Please enter 1 or 2 = \n");
        scanf("%d" , &x);
    }
    switch (x) {
        case 1 : GameMode(x);break;
        case 2 : GameMode(x);break;
        default: break;
    }

}

void GameLoop(int x , int y){
    ///
}

void ComputerTurn() {
    ///
}

void SaveGame() {
    ///
}

void LoadGame() {
    ///
}

void Scores() {
    ///
}

void Exit() {
    ///
}

void GameMode(int z){
    printf("Choose GameMode : \n");
    printf("Player vs Player ---> enter (1) \n");
    printf("Player vs Computer ---> enter (2) \n");
    int x;scanf("%d" , &x);
    while (x != 1 && x != 2){
        printf("Error,Please enter 1 or 2 = \n");
        scanf("%d" , &x);
    }
    switch (x) {
        case 1: GameLoop(z , x);break;
        case 2:
    }
}

void ExpertUI(){
    ///
}

void BeginnerUI (){
    ///
}