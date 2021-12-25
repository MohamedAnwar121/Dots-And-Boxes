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

char s[100];

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
int StringSize(char x[]);
void SizeChecker(char x[]);
void CharacterChecker(char x[]);
int InputHandling(char x[] , int z, int y);
void PrintGrid(int x, int y, char arr[x][y]);

int main(){
    BeginnerUI();
    return 0;
}

void MainMenu(){
    printf(" \t \t \t \t \t \t \t \tStart Game     ---> enter (1) \n");
    printf(" \t \t \t \t \t \t \t \tLoad Game      ---> enter (2) \n");
    printf(" \t \t \t \t \t \t \t \ttop 10 Players ---> enter (3) \n");
    printf(" \t \t \t \t \t \t \t \tExit           ---> enter (4) \n");
    printf(" \t \t \t \t \t \t \t \tChoose An Option = \n");
    int x = InputHandling(s , 1 , 4);
    switch (x) {
        case 1 : GameDifficulty();break;
        case 2 : LoadGame();break;
        case 3 : Scores();break;
        case 4 : Exit();break;
        default: break;
    }
}

void GameDifficulty(){
    printf(" \t \t \t \t \t \t \t \tChoose Difficulty : \n");
    printf(" \t \t \t \t \t \t \t \tBeginner (2 x 2) ---> enter (1) \n");
    printf(" \t \t \t \t \t \t \t \tExpert   (5 x 5  ---> enter (2) \n");
    printf(" \t \t \t \t \t \t \t \tChoose An Option = \n");
    int x = InputHandling(s , 1 , 2);
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
    printf(" \t \t \t \t \t \t \t \tChoose GameMode : \n");
    printf(" \t \t \t \t \t \t \t \tPlayer vs Player   ---> enter (1) \n");
    printf(" \t \t \t \t \t \t \t \tPlayer vs Computer ---> enter (2) \n");
    int x = InputHandling(s , 1 , 2);
    switch (x) {
        case 1: GameLoop(z , x);break;
        case 2: GameLoop(z , x);break;
        default:break;
    }
}

void ExpertUI(){
    ///
}

void BeginnerUI (){
    int n = 2 , m = 2 ,k ,v;
    k = 2*n + 1;
    v = 4*m + 1;
    char arr[k][v];
    for (int i = 0; i < k; ++i) {
        for (int j = 0; j < v; ++j) {
            arr[i][j] = ' ';
        }
    }
    for (int i = 0; i < k; i += 2) {
        for (int j = 0; j < v; j += 4) {
            arr[i][j] = 254;
        }
    }
    PrintGrid(k , v , arr);
}

int InputHandling(char x[] , int z, int y){
    SizeChecker(x);
    CharacterChecker(x);
    while (!(x[0] >= z + 48 && x[0] <= y + 48)){
        printf("Error,Enter A Number Btw %d And %d = \n" , z , y);
        SizeChecker(x);
        CharacterChecker(x);
    }
    return x[0] - 48;
}

int StringSize(char x[]) {
    int c = 0;
    for (int i = 0; x[i] != '\0'; ++i) {
        c++;
    }
    return c;
}

void SizeChecker(char x[]) {
    int c = 0;
    while (c != 1) {
        gets(x);
        c = StringSize(x);
        if (c != 1) printf("Error,Enter A Valid Number = \n");
    }
}

void CharacterChecker(char x[]){
    while(!(x[0] >= 48 && x[0] <= 57)){
        printf("Error,Enter A Valid Number = \n");
        SizeChecker(x);
    }
}

void PrintGrid(int x , int y , char arr[x][y]){
    printf(" \t \t \t \t \t \t \t \t \t  ");
    for (int i = 0; i < y / 2 + 1; ++i) {
        printf("%d ",i + 1);
    }
    printf("\n");
    for (int i = 0; i < x; ++i) {
        printf(" \t \t \t \t \t \t \t \t \t%d " , i + 1);
        for (int j = 0; j < y; ++j) {
                printf("%c", arr[i][j]);
        }
        printf("\n");
    }
}