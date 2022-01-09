#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>
//#include<pthread.h>

//vertical 186 horizontal 205 Box 219
struct times{
    int hrs, mins ,secs;
};
struct times split_time(long long int total){
    struct times a;
    long long mini=total%86400;
    a.hrs=mini/3600;
    int r1=mini%3600;
    a.mins=r1/60;
    a.secs=r1%60;

    return a;
}

typedef struct {
    char c;
    int color;
} Element;

typedef struct {
    char Name[30];
    int Score;
    int n;
} Player;

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
void GameMode(int n);
void UI(Player P1, Player P2, int p, int x,int y);
void PlayerVSPlayer(int n, int k, int v, Element arr[k][v], int score1, int score2, int b, int z,int moves[2 * n * (n + 1)][3], int y,int n1,int n2,char Pn1[30],char Pn2[30]);
void ComputerVSPlayer(int n, int k, int v, Element arr[k][v],
                      int score1, int score2, int b, int z,int moves[2 * n * (n + 1)][3], int y,int n1,int n2, char Pn[30],char Cn[30]);
int Redo(Player *P1, Player *P2, int *b, int x, int moves[2 * x * (x + 1)][3], int q, int k, int v, Element arr[k][v]);
int Undo(Player *P1, Player *P2, int *b, int x, int moves[2 * x * (x + 1)][3], int q, int k, int v, Element arr[k][v],int mode);
void SaveGame(int n, int moves[2 * n * (n + 1)][3], int y, int mode, int file,char Pn1[30] , char Pn2[30]);
void LoadGame(int file);
void Top10();
void Scores(int newScore, char newName[30]);
void Time();
int StringSize(char x[]);
void SizeChecker(char x[]);
void CharacterChecker(char x[]);
int InputHandling(char x[], int z, int y);
void PrintGrid(int x, int y, Element arr[x][y]);
void *counter(void *v){
    int y=0;
    printf("hello");
    return NULL;
}
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
            int file;
            printf("Choose Load File 1 , 2 , 3 : ");
            scanf("%d" , &file);
            LoadGame(file);
            break;
        case 3 :
            system("cls");
            Top10();
            break;
        case 4 :
            exit(0);
        default:
            break;
    }
    return NULL;
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
            GameMode(2);
            break;
        case 2 :
            system("cls");
            GameMode(5);
            break;
        default:
            break;
    }
}

void PlayerVSPlayer(int n, int k, int v, Element arr[k][v], int score1, int score2, int b, int z,
                    int moves[2 * n * (n + 1)][3], int y,int n1,int n2,char Pn1[30],char Pn2[30]) {
    int r, c, p = 1, last, back = 0, file = 0;
    last = y;
    Player P1, P2;
    P1.Score = score1;
    P2.Score = score2;
    P1.n = n1;
    P2.n = n2;
    strcpy(P1.Name, Pn1);
    strcpy(P2.Name, Pn2);
    system("cls");
    clock_t begin = clock();
    PrintGrid(k, v, arr);
    UI(P1, P2, p, n, 0);

    //Gameloop

    while (1) {

        if (z % 2 == 1) {
            p = 1;
        } else {
            p = 2;
        }
        printf(MAGENTA"Enter Row ="RESET);
        scanf("%d", &r);
        printf(MAGENTA"Enter Col ="RESET);
        scanf("%d", &c);
        if (r == 1 && c == 1) {
            if (last == 0) {
                system("cls");
                printf("No Available Moves \n");
                clock_t end = clock();
                int time_spent = (end - begin) / CLOCKS_PER_SEC;
                PrintGrid(k, v, arr);
            UI(P1, P2, p, n, time_spent);
                continue;
            } else {
                z = Undo(&P1, &P2, &b, n, moves, last, k, v, arr, 1);
                if (z % 2 == 1) {
                 p = 1;
                 } else {
                p = 2;
                }
                back++;
                last--;
                system("cls");
                clock_t end = clock();
                int time_spent = (end - begin) / CLOCKS_PER_SEC;
                PrintGrid(k, v, arr);
                UI(P1, P2, p, n, time_spent);
                continue;
            }
        } else if (r == 2 && c == 2) {
            if (last < y) {
                z = Redo(&P1, &P2, &b, n, moves, last, k, v, arr);
                 if (z % 2 == 1) {
                 p = 1;
                 } else {
                p = 2;
                }
                last++;
                back--;
                system("cls");
                clock_t end = clock();
            int time_spent = (end - begin) / CLOCKS_PER_SEC;
            PrintGrid(k, v, arr);
            UI(P1, P2, p, n, time_spent);
                continue;
            } else {
                system("cls");
                printf("No Available Moves \n");
                clock_t end = clock();
            int time_spent = (end - begin) / CLOCKS_PER_SEC;
            PrintGrid(k, v, arr);
            UI(P1, P2, p, n, time_spent);
                continue;
            }
        } else if (r == 3 && c == 3) {
            printf("Choose Save file 1 , 2 , 3 : ");
            scanf("%d" , &file);
            SaveGame(n, moves, y, 1, file, Pn1 , Pn2);
            system("cls");
            printf("Game Saved\n");
            clock_t end = clock();
            int time_spent = (end - begin) / CLOCKS_PER_SEC;
            PrintGrid(k, v, arr);
            UI(P1, P2, p, n, time_spent);
            continue;

        } else if (r == 4 && c == 4) {
            system("cls");
            MainMenu();
        }
        if (r > k || 2 * c - 1 > v) {
            system("cls");
            printf("No Available Moves \n");
            clock_t end = clock();
            int time_spent = (end - begin) / CLOCKS_PER_SEC;
            PrintGrid(k, v, arr);
            UI(P1, P2, p, n, time_spent);
            continue;
        }
        if (arr[r - 1][2 * c - 2].c != ' ') {
            system("cls");
            printf("No Available Moves\n");
            clock_t end = clock();
            int time_spent = (end - begin) / CLOCKS_PER_SEC;
            PrintGrid(k, v, arr);
            UI(P1, P2, p, n,time_spent );
            continue;
        }
        if (r % 2 == 0 && c % 2 == 0) {
            system("cls");
            printf("No Available Moves\n");
            clock_t end = clock();
            int time_spent = (end - begin) / CLOCKS_PER_SEC;
            PrintGrid(k, v, arr);
            UI(P1, P2, p, n, time_spent);
            continue;
        }
        if (r % 2 == 0 && c % 2 == 1) {
            arr[r - 1][2 * c - 2].c = 186;
            arr[r - 1][2 * c - 2].color = p;
            moves[last][0] = r;
            moves[last][1] = c;
            moves[last][2] = p;
            y -= back;
            y++;
            last = y;
            back = 0;
            if (p == 1) {
                P1.n++;
            } else {
                P2.n++;
            }
            for (int i = y; i < 2 * n * (n + 1); ++i) {
                for (int j = 0; j < 3; ++j) {
                    moves[i][j] = 0;
                }
            }
        } else if (r % 2 == 1 && c % 2 == 0) {
            arr[r - 1][2 * c - 2].color = p;
            arr[r - 1][2 * c - 2].c = 205;
            arr[r - 1][2 * c - 1].color = p;
            arr[r - 1][2 * c - 1].c = 205;
            arr[r - 1][2 * c - 3].color = p;
            arr[r - 1][2 * c - 3].c = 205;
            moves[last][0] = r;
            moves[last][1] = c;
            moves[last][2] = p;
            y -= back;
            y++;
            last = y;
            back = 0;
            if (p == 1) {
                P1.n++;
            } else {
                P2.n++;
            }
            for (int i = y; i < 2 * n * (n + 1); ++i) {
                for (int j = 0; j < 3; ++j) {
                    moves[i][j] = 0;
                }
            }
        } else {
            system("cls");
            printf("No Available Moves\n");
            clock_t end = clock();
            int time_spent = (end - begin) / CLOCKS_PER_SEC;
            PrintGrid(k, v, arr);
            UI(P1, P2, p, n, time_spent);
            continue;
        }
        for (int i = 1; i < k; i += 2) {
            for (int j = 2; j < v; j += 4) {
                if (arr[i][j].c == ' ') {
                    if (arr[i][j - 2].c != ' ' && arr[i][j + 2].c != ' ' && arr[i - 1][j].c != ' ' &&
                        arr[i + 1][j].c != ' ') {
                        if (p == 1) {
                            b++;
                            z = 2;
                            P1.Score++;
                            arr[i][j].c = 219;
                            arr[i][j].color = 1;
                            arr[i][j - 1].c = 219;
                            arr[i][j - 1].color = 1;
                            arr[i][j + 1].c = 219;
                            arr[i][j + 1].color = 1;
                        } else {
                            b++;
                            z = 1;
                            P2.Score++;
                            arr[i][j].c = 219;
                            arr[i][j].color = 2;
                            arr[i][j - 1].c = 219;
                            arr[i][j - 1].color = 2;
                            arr[i][j + 1].c = 219;
                            arr[i][j + 1].color = 2;
                        }
                    }
                }
            }
        }
        z++;
        if (z % 2 == 1) {
            p = 1;
        } else {
            p = 2;
        }
        system("cls");
        clock_t end = clock();
            int time_spent = (end - begin) / CLOCKS_PER_SEC;
            PrintGrid(k, v, arr);
            UI(P1, P2, p, n, time_spent);
        if (b == n * n) {
            printf("\t \t \t \tGame Ended\n");
            if (P1.Score > P2.Score) {
                Scores(P1.Score,P1.Name);
                printf("\t \t \t \tPlayer 1 Won");
            } else if (P2.Score > P1.Score) {
                Scores(P2.Score,P2.Name);
                printf("\t \t \t \tPlayer 2 Won");
            } else {
                printf("\t \t \t \tTie");
            }
            break;
        }
    }
}

void ComputerVSPlayer(int n, int k, int v, Element arr[k][v], int score1, int score2, int b, int z,
                      int moves[2 * n * (n + 1)][3], int y,int n1,int n2,char Pn[30],char Cn[30]) {
    int r, c, p = 1, h, f, last, back = 0;
    last = y;
    Player P, C;
    P.Score = score1;
    C.Score = score2;
    P.n = n1;
    C.n = n2;
    strcpy(P.Name,Pn);
    strcpy(C.Name, Cn);
    system("cls");
    clock_t begin = clock();
    PrintGrid(k, v, arr);
    UI(P, C, p, n, 0);
    while (1) {
        if (z % 2 == 1) {
            p = 1;
        } else {
            p = 2;
        }
        if (p == 1) {
            printf(MAGENTA"Enter Row ="RESET);
            scanf("%d", &r);
            printf(MAGENTA"Enter Col ="RESET);
            scanf("%d", &c);
            if (r == 1 && c == 1) {
                if (last == 0) {
                    system("cls");
                    printf("No Available Moves \n");
                    clock_t end = clock();
                    int time_spent = (end - begin) / CLOCKS_PER_SEC;
                    PrintGrid(k, v, arr);
                    UI(P, C, p, n, time_spent);
                    continue;
                } else {
                    while (1) {
                        z = Undo(&P, &C, &b, n, moves, last, k, v, arr, 1);
                        back++;
                        last--;
                        if (z % 2 == 1) {
                            system("cls");
                    clock_t end = clock();
                    int time_spent = (end - begin) / CLOCKS_PER_SEC;
                    PrintGrid(k, v, arr);
                    UI(P, C, p, n, time_spent);
                            break;
                        }
                    }
                    continue;
                }
            } else if (r == 2 && c == 2) {
                if (last < y) {
                    while(1) {
                        z = Redo(&P, &C, &b, n, moves, last, k, v, arr);
                        last++;
                        back--;
                        if(z % 2 == 1){
                            system("cls");
                                                clock_t end = clock();
                    int time_spent = (end - begin) / CLOCKS_PER_SEC;
                    PrintGrid(k, v, arr);
                    UI(P, C, p, n, time_spent);
                            break;
                        }
                    }
                    continue;
                } else {
                    system("cls");
                    printf("No Available Moves \n");
                                        clock_t end = clock();
                    int time_spent = (end - begin) / CLOCKS_PER_SEC;
                    PrintGrid(k, v, arr);
                    UI(P, C, p, n, time_spent);
                    continue;
                }
            } else if (r == 3 && c == 3) {
                SaveGame(n, moves, y, 2, 2,Pn,"Computer");
                system("cls");
                printf("Game Saved\n");
                                    clock_t end = clock();
                    int time_spent = (end - begin) / CLOCKS_PER_SEC;
                    PrintGrid(k, v, arr);
                    UI(P, C, p, n, time_spent);
                continue;
            } else if (r == 4 && c == 4) {
                system("cls");
                MainMenu();
            }
            if (r > k || 2 * c - 1 > v) {
                system("cls");
                printf("No Available Moves \n");
                                    clock_t end = clock();
                    int time_spent = (end - begin) / CLOCKS_PER_SEC;
                    PrintGrid(k, v, arr);
                    UI(P, C, p, n, time_spent);
                continue;
            }
            if (arr[r - 1][2 * c - 2].c != ' ') {
                system("cls");
                printf("No Available Moves \n");
                                    clock_t end = clock();
                    int time_spent = (end - begin) / CLOCKS_PER_SEC;
                    PrintGrid(k, v, arr);
                    UI(P, C, p, n, time_spent);
                continue;
            }
            if (r % 2 == 0 && c % 2 == 0) {
                system("cls");
                printf("No Available Moves \n");
                                    clock_t end = clock();
                    int time_spent = (end - begin) / CLOCKS_PER_SEC;
                    PrintGrid(k, v, arr);
                    UI(P, C, p, n, time_spent);
                continue;
            }
            if (r % 2 == 0 && c % 2 == 1) {
                arr[r - 1][2 * c - 2].c = 186;
                arr[r - 1][2 * c - 2].color = 1;
                moves[last][0] = r;
                moves[last][1] = c;
                moves[last][2] = 1;
                y -= back;
                y++;
                last = y;
                back = 0;
            } else if (r % 2 == 1 && c % 2 == 0) {
                arr[r - 1][2 * c - 2].color = 1;
                arr[r - 1][2 * c - 2].c = 205;
                arr[r - 1][2 * c - 1].color = 1;
                arr[r - 1][2 * c - 1].c = 205;
                arr[r - 1][2 * c - 3].color = 1;
                arr[r - 1][2 * c - 3].c = 205;
                moves[last][0] = r;
                moves[last][1] = c;
                moves[last][2] = 1;
                y -= back;
                y++;
                last = y;
                back = 0;
            } else {
                system("cls");
                printf("No Available Moves\n");
                                    clock_t end = clock();
                    int time_spent = (end - begin) / CLOCKS_PER_SEC;
                    PrintGrid(k, v, arr);
                    UI(P, C, p, n, time_spent);
                continue;
            }
            for (int i = 1; i < k; i += 2) {
                for (int j = 2; j < v; j += 4) {
                    if (arr[i][j].c == ' ') {
                        if (arr[i][j - 2].c != ' ' && arr[i][j + 2].c != ' ' && arr[i - 1][j].c != ' ' &&
                            arr[i + 1][j].c != ' ') {
                            b++;
                            z = 2;
                            P.Score++;
                            arr[i][j].c = 219;
                            arr[i][j].color = 1;
                            arr[i][j - 1].c = 219;
                            arr[i][j - 1].color = 1;
                            arr[i][j + 1].c = 219;
                            arr[i][j + 1].color = 1;
                        }
                    }
                }
            }
            z++;
            system("cls");
                                clock_t end = clock();
                    int time_spent = (end - begin) / CLOCKS_PER_SEC;
                    PrintGrid(k, v, arr);
                    UI(P, C, p, n, time_spent);
            if (b == n * n) {
                printf("\t \t \t \tGame Ended\n");
                if (P.Score > C.Score) {
                    Scores(P.Score,P.Name);
                    printf("\t \t \t \tPlayer 1 Won");
                } else if (C.Score > P.Score) {
                    printf("\t \t \t \tComputer Won");
                } else {
                    printf("\t \t \t \tTie");
                }
                break;
            }
            continue;
        } else {
            int rc = c, cc = r, i = 0, j = 0;
            for (i = 1; i < k; i += 2) {
                for (j = 2; j < v; j += 4) {
                    h = 0;
                    f = 0;
                    if (arr[i][j].c == ' ') {
                        if (arr[i + 1][j].c != ' ') {
                            h++;
                        }
                        if (arr[i - 1][j].c != ' ') {
                            h++;
                        }
                        if (arr[i][j - 2].c != ' ') {
                            h++;
                        }
                        if (arr[i][j + 2].c != ' ') {
                            h++;
                        }
                        if (h == 3) {
                            f = 1;
                            break;
                        }
                    }
                }
                if (f == 1)
                    break;
            }
            if (h == 3) {
                if (arr[i + 1][j].c == ' ') {
                    arr[i + 1][j].c = 205;
                    arr[i + 1][j].color = 2;
                    arr[i + 1][j - 1].c = 205;
                    arr[i + 1][j - 1].color = 2;
                    arr[i + 1][j + 1].c = 205;
                    arr[i + 1][j + 1].color = 2;
                    moves[last][0] = i + 2;
                    moves[last][1] = (j + 2) / 2;
                    moves[last][2] = 2;
                } else if (arr[i - 1][j].c == ' ') {
                    arr[i - 1][j].c = 205;
                    arr[i - 1][j].color = 2;
                    arr[i - 1][j - 1].c = 205;
                    arr[i - 1][j - 1].color = 2;
                    arr[i - 1][j + 1].c = 205;
                    arr[i - 1][j + 1].color = 2;
                    moves[last][0] = i;
                    moves[last][1] = (j + 2) / 2;
                    moves[last][2] = 2;
                } else if (arr[i][j - 2].c == ' ') {
                    arr[i][j - 2].c = 186;
                    arr[i][j - 2].color = 2;
                    moves[last][0] = i + 1;
                    moves[last][1] = j / 2;
                    moves[last][2] = 2;
                } else if (arr[i][j + 2].c == ' ') {
                    arr[i][j + 2].c = 186;
                    arr[i][j + 2].color = 2;
                    moves[last][0] = i + 1;
                    moves[last][1] = (j + 4) / 2;
                    moves[last][2] = 2;
                }
                y -= back;
                y++;
                last = y;
                back = 0;
                for (int a = 1; a < k; a += 2) {
                    for (int d = 2; d < v; d += 4) {
                        if (arr[a][d].c == ' ') {
                            if (arr[a][d - 2].c != ' ' && arr[a][d + 2].c != ' ' && arr[a - 1][d].c != ' ' &&
                                arr[a + 1][d].c != ' ') {
                                arr[a][d].c = 219;
                                arr[a][d].color = 2;
                                arr[a][d - 1].c = 219;
                                arr[a][d - 1].color = 2;
                                arr[a][d + 1].c = 219;
                                arr[a][d + 1].color = 2;
                                b++;
                                z = 1;
                                C.Score++;
                            }
                        }
                    }
                }
                system("cls");
                z++;
                                    clock_t end = clock();
                    int time_spent = (end - begin) / CLOCKS_PER_SEC;
                    PrintGrid(k, v, arr);
                    UI(P, C, p, n, time_spent);
                continue;
            } else if (arr[rc - 1][2 * cc - 2].c == ' ') {
                if (rc % 2 == 0 && cc % 2 == 1) {
                    arr[rc - 1][2 * cc - 2].c = 186;
                    arr[rc - 1][2 * cc - 2].color = 2;
                } else if (rc % 2 == 1 && cc % 2 == 0) {
                    arr[rc - 1][2 * cc - 2].c = 205;
                    arr[rc - 1][2 * cc - 2].color = 2;
                    arr[rc - 1][2 * cc - 1].c = 205;
                    arr[rc - 1][2 * cc - 1].color = 2;
                    arr[rc - 1][2 * cc - 3].c = 205;
                    arr[rc - 1][2 * cc - 3].color = 2;
                }
                moves[last][0] = rc;
                moves[last][1] = cc;
                moves[last][2] = 2;
                y -= back;
                y++;
                last = y;
                back = 0;
                system("cls");
                z++;
                                    clock_t end = clock();
                    int time_spent = (end - begin) / CLOCKS_PER_SEC;
                    PrintGrid(k, v, arr);
                    UI(P, C, p, n, time_spent);
                continue;
            } else {
                srand(time(0));
                while (1) {
                    f = 0;
                    int Rr = (rand() % (k)) + 1;
                    int Cr = (rand() % (v)) + 1;
                    if (Rr > k || 2 * Cr - 1 > v)
                        continue;
                    if (arr[Rr - 1][2 * Cr - 2].c != ' ')
                        continue;
                    if (Rr % 2 == Cr % 2)
                        continue;
                    if (Rr % 2 == 0 && Cr % 2 == 1) {
                        arr[Rr - 1][2 * Cr - 2].c = 186;
                        arr[Rr - 1][2 * Cr - 2].color = 2;
                        f = 1;
                    } else if (Rr % 2 == 1 && Cr % 2 == 0) {
                        arr[Rr - 1][2 * Cr - 2].color = 2;
                        arr[Rr - 1][2 * Cr - 2].c = 205;
                        arr[Rr - 1][2 * Cr - 1].color = 2;
                        arr[Rr - 1][2 * Cr - 1].c = 205;
                        arr[Rr - 1][2 * Cr - 3].color = 2;
                        arr[Rr - 1][2 * Cr - 3].c = 205;
                        f = 1;
                    }
                    if (f == 1) {
                        moves[last][0] = Rr;
                        moves[last][1] = Cr;
                        moves[last][2] = 2;
                        y -= back;
                        y++;
                        last = y;
                        back = 0;
                        z++;
                        system("cls");
                                            clock_t end = clock();
                    int time_spent = (end - begin) / CLOCKS_PER_SEC;
                    PrintGrid(k, v, arr);
                    UI(P, C, p, n, time_spent);
                        break;
                    } else {
                        continue;
                    }
                }
            }
        }
        if (b == n * n) {
            printf("\t \t \t \tGame Ended\n");
            if (P.Score > C.Score) {
                Scores(P.Score,P.Name);
                printf("\t \t \t \tPlayer Won");
            } else if (C.Score > P.Score) {
                printf("\t \t \t \tComputer Won");
            } else {
                printf("\t \t \t \tTie");
            }
            break;
        }
    }
}

void SaveGame(int n, int moves[2 * n * (n + 1)][3], int y,int mode, int file, char Pn1[30] , char Pn2[30]) {
    FILE *s1;
    switch (file) {
        case 1: s1 = fopen("gameone.txt", "w");break;
        case 2: s1 = fopen("gametwo.txt", "w");break;
        case 3: s1 = fopen("gamethree.txt", "w");break;
        default: break;
    }
    fprintf(s1,"%s\n" , Pn1);
    fprintf(s1,"%s\n" , Pn2);
    fprintf(s1, "%d\n", mode);
    fprintf(s1, "%d\n", n);
    fprintf(s1, "%d\n", y);
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < 3; j++) {
            fprintf(s1, "%d ", moves[i][j]);
        }
        fprintf(s1, "\n");
    }
    fclose(s1);
}

void LoadGame(int file) {
    int b = 0, score1 = 0, score2 = 0, r, c, p, z = 1, n1 = 0 , n2 = 0;
    char Pn1[30] ,Pn2[30];
    FILE *L1;
    switch (file) {
        case 1: L1 = fopen("gameone.txt", "r");break;
        case 2: L1 = fopen("gametwo.txt", "r");break;
        case 3: L1 = fopen("gamethree.txt", "r");break;
        default: break;
    }
    int y, n, mode;
    fscanf(L1,"%s\n", Pn1);
    fscanf(L1, "%s\n", Pn2);
    fscanf(L1,"%d\n", &mode);
    fscanf(L1, "%d\n", &n);
    fscanf(L1, "%d\n", &y);
    int k = 2 * n + 1;
    int v = 4 * n + 1;
    Element arr1[k][v];
    int moves[2 * n * (n + 1)][3];
    for (int i = 0; i < 2 * n * (n + 1); ++i) {
        for (int j = 0; j < 3; ++j) {
            moves[i][j] = 0;
        }
    }
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < 3; j++) {
            fscanf(L1, "%d%*c", &moves[i][j]);
        }
        fscanf(L1, "%*c");
    }
    fclose(L1);
    for (int i = 0; i < k; ++i) {
        for (int j = 0; j < v; ++j) {
            arr1[i][j].color = 0;
            arr1[i][j].c = ' ';
        }
    }
    for (int i = 0; i < k; i += 2) {
        for (int j = 0; j < v; j += 4) {
            arr1[i][j].c = 254;
        }
    }
    for (int u = 0; u < y; u++) {
        r = moves[u][0];
        c = moves[u][1];
        p = moves[u][2];
        if (r % 2 == 0 && c % 2 == 1) {
            arr1[r - 1][2 * c - 2].c = 186;
            arr1[r - 1][2 * c - 2].color = p;
            if (p == 1) {
                n1++;
            } else {
                n2++;
            }
        } else if (r % 2 == 1 && c % 2 == 0) {
            arr1[r - 1][2 * c - 2].color = p;
            arr1[r - 1][2 * c - 2].c = 205;
            arr1[r - 1][2 * c - 1].color = p;
            arr1[r - 1][2 * c - 1].c = 205;
            arr1[r - 1][2 * c - 3].color = p;
            arr1[r - 1][2 * c - 3].c = 205;
            if (p == 1) {
                n1++;
            } else {
                n2++;
            }
        }
        for (int i = 1; i < k; i += 2) {
            for (int j = 2; j < v; j += 4) {
                if (arr1[i][j].c == ' ') {
                    if (arr1[i][j - 2].c != ' ' && arr1[i][j + 2].c != ' ' && arr1[i - 1][j].c != ' ' &&
                        arr1[i + 1][j].c != ' ') {
                        if (p == 1) {
                            b++;
                            score1++;
                            z = 2;
                            arr1[i][j].c = 219;
                            arr1[i][j].color = 1;
                            arr1[i][j - 1].c = 219;
                            arr1[i][j - 1].color = 1;
                            arr1[i][j + 1].c = 219;
                            arr1[i][j + 1].color = 1;
                        } else {
                            b++;
                            score2++;
                            z = 1;
                            arr1[i][j].c = 219;
                            arr1[i][j].color = 2;
                            arr1[i][j - 1].c = 219;
                            arr1[i][j - 1].color = 2;
                            arr1[i][j + 1].c = 219;
                            arr1[i][j + 1].color = 2;
                        }
                    }
                }
            }
        }
        z++;
    }
    if (mode == 1){
        PlayerVSPlayer(n, k, v, arr1, score1, score2, b, z, moves, y, n1 , n2, Pn1, Pn2);
    }else{
        ComputerVSPlayer(n, k, v, arr1, score1, score2, b, z, moves, y, n1 , n2,Pn1, Pn2);
    }
}

int Undo(Player *P1, Player *P2, int *b, int x, int moves[2 * x * (x + 1)][3], int q, int k, int v, Element arr[k][v],
         int mode) {
    int r, c, p, z;
    *b = 0;
    P1->Score = 0;
    P2->Score = 0;
    P1->n = 0;
    P2->n = 0;
    for (int i = 0; i < k; ++i) {
        for (int j = 0; j < v; ++j) {
            arr[i][j].color = 0;
            arr[i][j].c = ' ';
        }
    }

    for (int i = 0; i < k; i += 2) {
        for (int j = 0; j < v; j += 4) {
            arr[i][j].c = 254;
        }
    }
    for (int u = 0; u < q - 1; u++) {
        r = moves[u][0];
        c = moves[u][1];
        p = moves[u][2];
        if (r % 2 == 0 && c % 2 == 1) {
            arr[r - 1][2 * c - 2].c = 186;
            arr[r - 1][2 * c - 2].color = p;
            if (p == 1) {
                P1->n++;
            } else {
                P2->n++;
            }
        } else if (r % 2 == 1 && c % 2 == 0) {
            arr[r - 1][2 * c - 2].color = p;
            arr[r - 1][2 * c - 2].c = 205;
            arr[r - 1][2 * c - 1].color = p;
            arr[r - 1][2 * c - 1].c = 205;
            arr[r - 1][2 * c - 3].color = p;
            arr[r - 1][2 * c - 3].c = 205;
            if (p == 1) {
                P1->n++;
            } else {
                P2->n++;
            }
        }
        for (int i = 1; i < k; i += 2) {
            for (int j = 2; j < v; j += 4) {
                if (arr[i][j].c == ' ') {
                    if (arr[i][j - 2].c != ' ' && arr[i][j + 2].c != ' ' && arr[i - 1][j].c != ' ' &&
                        arr[i + 1][j].c != ' ') {
                        if (p == 1) {
                            *b = *b + 1;
                            P1->Score++;
                            arr[i][j].c = 219;
                            arr[i][j].color = 1;
                            arr[i][j - 1].c = 219;
                            arr[i][j - 1].color = 1;
                            arr[i][j + 1].c = 219;
                            arr[i][j + 1].color = 1;
                        } else {
                            *b = *b + 1;
                            P2->Score++;
                            arr[i][j].c = 219;
                            arr[i][j].color = 2;
                            arr[i][j - 1].c = 219;
                            arr[i][j - 1].color = 2;
                            arr[i][j + 1].c = 219;
                            arr[i][j + 1].color = 2;
                        }
                    }
                }
            }
        }
    }
    return moves[q - 1][2];
}

int Redo(Player *P1, Player *P2, int *b, int x, int moves[2 * x * (x + 1)][3], int q, int k, int v, Element arr[k][v]) {
    int r, c, p, z = 1;
    *b = 0;
    P1->n = 0;
    P2->n = 0;
    P1->Score = 0;
    P2->Score = 0;
    for (int i = 0; i < k; ++i) {
        for (int j = 0; j < v; ++j) {
            arr[i][j].color = 0;
            arr[i][j].c = ' ';
        }
    }
    for (int i = 0; i < k; i += 2) {
        for (int j = 0; j < v; j += 4) {
            arr[i][j].c = 254;
        }
    }
    for (int u = 0; u < q + 1; u++) {
        r = moves[u][0];
        c = moves[u][1];
        p = moves[u][2];
        if (r % 2 == 0 && c % 2 == 1) {
            arr[r - 1][2 * c - 2].c = 186;
            arr[r - 1][2 * c - 2].color = p;
            if (p == 1) {
                P1->n++;
            } else {
                P2->n++;
            }
        } else if (r % 2 == 1 && c % 2 == 0) {
            arr[r - 1][2 * c - 2].color = p;
            arr[r - 1][2 * c - 2].c = 205;
            arr[r - 1][2 * c - 1].color = p;
            arr[r - 1][2 * c - 1].c = 205;
            arr[r - 1][2 * c - 3].color = p;
            arr[r - 1][2 * c - 3].c = 205;
            if (p == 1) {
                P1->n++;
            } else {
                P2->n++;
            }
        }
        for (int i = 1; i < k; i += 2) {
            for (int j = 2; j < v; j += 4) {
                if (arr[i][j].c == ' ') {
                    if (arr[i][j - 2].c != ' ' && arr[i][j + 2].c != ' ' && arr[i - 1][j].c != ' ' &&
                        arr[i + 1][j].c != ' ') {
                        if (p == 1) {
                            *b = *b + 1;
                            P1->Score++;
                            z = 2;
                            arr[i][j].c = 219;
                            arr[i][j].color = 1;
                            arr[i][j - 1].c = 219;
                            arr[i][j - 1].color = 1;
                            arr[i][j + 1].c = 219;
                            arr[i][j + 1].color = 1;
                        } else {
                            *b = *b + 1;
                            P2->Score++;
                            z = 1;
                            arr[i][j].c = 219;
                            arr[i][j].color = 2;
                            arr[i][j - 1].c = 219;
                            arr[i][j - 1].color = 2;
                            arr[i][j + 1].c = 219;
                            arr[i][j + 1].color = 2;
                        }
                    }
                }
            }
        }
        z++;
    }
    return z;
}

void Scores(int newScore, char newName[30]) {
    int swap, flag = 0;
    char sswap[30];
    Player z[11];
    for (int i = 0; i < 11; i++) {
        z[i].Score = 0;
        z[i].Name[0] = '\0';
    }
    FILE *f = fopen("scores.txt", "r");
    for (int i = 0; i < 11; i++) {
        fscanf(f, "%[^\n]", z[i].Name);
        fscanf(f, "%d\n", &z[i].Score);

    }
    fclose(f);
    for (int j = 0; j < 10; j++) {
        if (!strcmp(z[j].Name, newName)) {
            if (newScore >= z[j].Score) {
                z[j].Score = newScore;
                flag = 1;
                break;
            }
        }
    }
    if (flag == 0) {
        strcpy(z[10].Name, newName);
        z[10].Score = newScore;
    }
    for (int c = 0; c < 11 - 1; c++) {
        for (int d = 0; d < 11 - c - 1; d++) {
            if (z[d].Score < z[d + 1].Score) {
                swap = z[d].Score;
                strcpy(sswap, z[d].Name);
                z[d].Score = z[d + 1].Score;
                strcpy(z[d].Name, z[d + 1].Name);
                z[d + 1].Score = swap;
                strcpy(z[d + 1].Name, sswap);
            }
        }
    }


    FILE *b = fopen("scores.txt", "w");
    for (int i = 0; i < 10; i++) {
        if (z[i].Score != 0) {

            fprintf(b, "%s\n%d\n", z[i].Name, z[i].Score);
        }
    }
    fclose(b);

}

void Top10(){
    int swap, flag = 0;
    char sswap[30];
    Player z[11];
    for (int i = 0; i < 11; i++) {
        z[i].Score = 0;
        z[i].Name[0] = '\0';
    }
    FILE *f = fopen("scores.txt", "r");
    for (int i = 0; i < 11; i++) {
        fscanf(f, "%[^\n]", z[i].Name);
        fscanf(f, "%d\n", &z[i].Score);
    }
    for (int i = 0; i < 10; i++) {
        if (z[i].Score != 0) {
            printf("%d)%s  %d\n", i + 1, z[i].Name, z[i].Score);
        }
    }
    fclose(f);
}

void UI(Player P1, Player P2, int p, int x,int y) {
    int compare = strcmp(P2.Name, "Computer");
    char s1[30], s2[30];
    struct times b;
    b=split_time(y);
    if (compare == 0) {
        strcpy(s1, "Player");
        strcpy(s2, "Computer");
    } else {
        strcpy(s1, "Player 1");
        strcpy(s2, "Player 2");
    }
    printf("\n");
    printf(RED"Player 1 Name : %s"RESET, P1.Name);
    printf(BLUE"\t \t \t \t \t \t \tPlayer 2 Name : %s\n"RESET, P2.Name);
    printf(RED"Number of %s Moves : %d"RESET, s1, P1.n);
    printf(BLUE"\t \t \t \t \t \tNumber of %s Moves : %d\n"RESET, s2, P2.n);
    printf(RED"%s Score : %d"RESET, s1, P1.Score);
    printf(BLUE"\t \t \t \t \t \t \t%s Score : %d\n"RESET, s2, P2.Score);
    printf(GREEN"Number of Remaining Moves : %d"RESET, 2 * x * (x + 1) - P1.n - P2.n);
    printf(YELLOW"\t \t \t \t \t \tTime Passed : %d : %d : %d"RESET,b.hrs,b.mins,b.secs);

    printf("\n");
    printf("\t Undo Enter 1 , 1\t \t \t \t \t Redo     Enter 2 , 2\n"
           "\t Save Enter 3 , 3\t \t \t \t \t MainMenu Enter 4 , 4\n");
    printf("\t \t \t Enter Raw And Column Number For The line\n");
    if (compare == 0) {
        printf(RED"\t \t \t \t \tPlayer Turn\n"RESET);
    } else {
        if (p == 1) {
            printf(RED"\t \t \t \t \tPLAYER 1 Turn\n"RESET);
        } else if(p == 2) {
            printf(BLUE"\t \t \t \t \tPLAYER 2 Turn\n"RESET);
        }
    }
}


void Time() {
    ///
}

void GameMode(int n) {
    system("cls");
    printf(" \t \t \t \t \t Choose GameMode : \n");
    printf(" \t \t \t \t \t Player vs Player   ---> enter (1) \n");
    printf(" \t \t \t \t \t Player vs Computer ---> enter (2) \n");
    printf(" \t \t \t \t \t Choose An Option = ");
    int x = InputHandling(s, 1, 2);
    int moves[2 * n * (n + 1)][3];
    Player P1 ,P2;
    Element arr1[2 * n + 1][4 * n + 1];
    for (int i = 0; i < 2 * n + 1; ++i) {
        for (int j = 0; j < 4 * n + 1; ++j) {
            arr1[i][j].color = 0;
            arr1[i][j].c = ' ';
        }
    }
    for (int i = 0; i < 2 * n + 1; i += 2) {
        for (int j = 0; j < 4 * n + 1; j += 4) {
            arr1[i][j].c = 254;
        }
    }
    for (int i = 0; i < 2 * n * (n + 1); ++i) {
        for (int j = 0; j < 3; ++j) {
            moves[i][j] = 0;
        }
    }
    switch (x) {
        case 1:
            system("cls");
            printf(RED"Enter Player 1 Name : "RESET);
            gets(P1.Name);
            system("cls");
            printf(BLUE"Enter Player 2 Name : "RESET);
            gets(P2.Name);
            system("cls");
            PlayerVSPlayer(n, 2 * n + 1, 4 * n + 1, arr1, 0, 0, 0, 1, moves, 0, 0, 0, P1.Name, P2.Name);
            break;
        case 2:
            system("cls");
            printf(RED"Enter Player Name : "RESET);
            gets(P1.Name);
            ComputerVSPlayer(n, 2 * n + 1, 4 * n + 1, arr1, 0, 0, 0, 1, moves, 0,0,0,P1.Name,"Computer");
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
    int D[y / 2 + 1], C[y / 2 + 1];
    printf("  \t \t \t \t \t    ");
    for (int i = 0; i < y / 2 + 1; ++i) {
        if (i + 1 > 9) {
            D[i] = (i + 1) / 10;
            printf("%d ", D[i]);
        } else {
            D[i] = i + 1;
            printf("%d ", D[i]);
        }
    }
    if (((y - 1) / 2 + 1) > 9) {
        printf("\n");
        printf("  \t \t \t \t \t    ");
        for (int i = 0; i < y / 2 + 1; ++i) {
            if (i + 1 > 9) {
                C[i] = (i + 1) % 10;
                printf("%d ", C[i]);
            } else {
                printf("  ");
            }
        }
    }
    printf("\n");
    for (int i = 0; i < x; ++i) {
        if (i >= 9) {
            printf(" \t \t \t \t \t %d ", i + 1);
        } else {
            printf(" \t \t \t \t \t %d  ", i + 1);
        }
        for (int j = 0; j < y; ++j) {
            if (arr[i][j].color == 1) {
                printf(RED"%c"RESET, arr[i][j].c);
            } else if (arr[i][j].color == 2) {
                printf(BLUE"%c"RESET, arr[i][j].c);
            } else {
                printf("%c", arr[i][j].c);
            }
        }
        printf("\n");
    }
}
