#include <stdio.h>
#include <stdlib.h>

//vertical 186 horizontal 205 Box 219

typedef struct {
    char c;
    int color;
} Element;

typedef struct {
    char Name[30];
    int Score;
    int Wins;
}Player;

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
void GameLoop(int x, int y);
void ComputerTurn();
void SaveGame();
void LoadGame();
void Scores();
void Time();
int StringSize(char x[]);
void SizeChecker(char x[]);
void CharacterChecker(char x[]);
int InputHandling(char x[], int z, int y);
void PrintGrid(int x, int y, Element arr[x][y]);

int main() {
    system("");
    MainMenu();
    return 0;
}

void MainMenu() {
    printf(" \t \t \t \t \t Start Game     ---> enter (1) \n");
    printf(" \t \t \t \t \t Load Game      ---> enter (2) \n");
    printf(" \t \t \t \t \t top 10 Players ---> enter (3) \n");
    printf(" \t \t \t \t \t Exit           ---> enter (4) \n");
    printf(" \t \t \t \t \t Choose An Option = ");
    int x = InputHandling(s, 1, 4);
    switch (x) {
        case 1 :
            system("cls");
            GameDifficulty();
            break;
        case 2 :
            system("cls");
            LoadGame();
            break;
        case 3 :
            system("cls");
            Scores();
            break;
        case 4 :
            exit(0);
        default:
            break;
    }
}

void GameDifficulty() {
    system("cls");
    printf(" \t \t \t \t \t Choose Difficulty : \n");
    printf(" \t \t \t \t \t Beginner (2 x 2) ---> enter (1) \n");
    printf(" \t \t \t \t \t Expert   (5 x 5)  ---> enter (2) \n");
    printf(" \t \t \t \t \t Choose An Option = ");
    int x = InputHandling(s, 1, 2);
    switch (x) {
        case 1 :
            system("cls");
            GameMode(x);
            break;
        case 2 :
            system("cls");
            GameMode(x);
            break;
        default:
            break;
    }
}

void GameLoop(int x, int y) {
    int n = 2, k, v, r, c, p = 1, z = 1 , b = 0;
    k = 2 * n + 1;
    v = 2 * n + 1;
    Element arr[k][v];
    Player P1 , P2;
    P1.Score = 0;
    P2.Score = 0;
    for (int i = 0; i < k; ++i) {
        for (int j = 0; j < v; ++j) {
            arr[i][j].color = 0;
            arr[i][j].c = ' ';
        }
    }
    for (int i = 0; i < k; i += 2) {
        for (int j = 0; j < v; j += 2) {
            arr[i][j].c = 254;
        }
    }
    PrintGrid(k, v, arr);
    while (1) {
        if (z % 2 == 1) {
            p = 1;
        } else {
            p = 2;
        }
        printf("Enter Raw =");
        scanf("%d", &r);
        printf("\nEnter Col =");
        scanf("%d", &c);
        while (r > k && c > v) {
            printf("Error , Out of Bound \n");
            printf("Enter Raw =");
            scanf("%d", &r);
            printf("\nEnter Col =");
            scanf("%d", &c);
        }
        while(arr[r - 1][c - 1].c != ' ' ){
            printf("No Available Moves\n");
            printf("Enter Raw =");
            scanf("%d", &r);
            printf("\nEnter Col =");
            scanf("%d", &c);
            while (r > k && c > v) {
                printf("Error , Out of Bound \n");
                printf("Enter Raw =");
                scanf("%d", &r);
                printf("\nEnter Col =");
                scanf("%d", &c);
            }
        }
        if (r % 2 == 0 && c % 2 == 1) {
            arr[r - 1][c - 1].c = 186;
            arr[r - 1][c - 1].color = p;
        } else if (r % 2 == 1 && c % 2 == 0) {
            arr[r - 1][c - 1].c = 205;
            arr[r - 1][c - 1].color = p;
        } else {
            printf("No Available Moves\n");
            continue;
        }
        for (int i = 1; i < k; i += 2) {
            for (int j = 1; j < v; j += 2) {
                if(arr[i][j].c == ' '){
                    if(arr[i - 1][j].c != ' ' && arr[i + 1][j].c != ' ' && arr[i][j + 1].c != ' ' && arr[i][j - 1].c != ' '){
                        if(p == 1){
                            b++;
                            z = 2;
                            P1.Score++;
                            arr[i][j].c = 219;
                            arr[i][j].color = 1;
                        }else {
                            b++;
                            z = 1;
                            P2.Score++;
                            arr[i][j].c = 219;
                            arr[i][j].color = 2;
                        }
                    }
                }
            }
        }
        z++;
        system("cls");
        PrintGrid(k, v, arr);
        if(b == n * n){
            printf("Game Ended");
            break;
        }
    }
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

void Time() {
    ///
}

void GameMode(int z) {
    system("cls");
    printf(" \t \t \t \t \t Choose GameMode : \n");
    printf(" \t \t \t \t \t Player vs Player   ---> enter (1) \n");
    printf(" \t \t \t \t \t Player vs Computer ---> enter (2) \n");
    printf(" \t \t \t \t \t Choose An Option = ");
    int x = InputHandling(s, 1, 2);
    switch (x) {
        case 1:
            GameLoop(z, x);
            break;
        case 2:
            GameLoop(z, x);
            break;
        default:
            break;
    }
}

int InputHandling(char x[], int z, int y) {
    SizeChecker(x);
    CharacterChecker(x);
    while (!(x[0] >= z + 48 && x[0] <= y + 48)) {
        printf("Error,Enter A Number Btw %d And %d = \n", z, y);
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
        if (c != 1) {
            printf("Error,Enter A Valid Number = \n");
        }
    }
}

void CharacterChecker(char x[]) {
    while (!(x[0] >= 48 && x[0] <= 57)) {
        printf("Error,Enter A Valid Number = \n");
        SizeChecker(x);
    }
}

void PrintGrid(int x, int y, Element arr[x][y]) {
    printf(" \t \t \t \t \t   ");
    for (int i = 0; i < y; ++i) {
        printf("%d", i + 1);
    }
    printf("\n");
    for (int i = 0; i < x; ++i) {
        printf(" \t \t \t \t \t %d ", i + 1);
        for (int j = 0; j < y; ++j) {
            if (arr[i][j].color == 1) {
                printf(RED"%c"RESET, arr[i][j].c);
            } else if (arr[i][j].color == 2) {
                printf(BLUE"%c"RESET, arr[i][j].c);
            } else {
                printf("%c" , arr[i][j].c);
            }
        }
        printf("\n");
    }
}
