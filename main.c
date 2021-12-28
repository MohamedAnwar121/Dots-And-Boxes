#include <stdio.h>
#include <stdlib.h>

//vertical 186 horizontal 205 Box 219
int new_player_score;
char new_player_name[30];

typedef struct {
    char c;
    int color;
} Element;

typedef struct {
    char Name[30];
    int Score;
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

void GameMode(int z);

void UI();

void PlayerVSPlayer(int x);

void ComputerVSPlayer(int x);

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
    Scores(88,"bolbol");
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

void PlayerVSPlayer(int x) {
    int n = 2, k, v, r, c, p = 1, z = 1, b = 0;
    k = 2 * n + 1;
    v = 4 * n + 1;
    Element arr[k][v];
    Player P1, P2;
    P1.Score = 0;
    P2.Score = 0;
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
        while (r > k && 2*c - 1 > v) {
            printf("Error , Out of Bound \n");
            printf("Enter Raw =");
            scanf("%d", &r);
            printf("\nEnter Col =");
            scanf("%d", &c);
        }
        while (arr[r - 1][2*c - 2].c != ' ') {
            printf("No Available Moves\n");
            printf("Enter Raw =");
            scanf("%d", &r);
            printf("\nEnter Col =");
            scanf("%d", &c);
            while (r > k && 2 * c - 1 > v) {
                printf("Error , Out of Bound \n");
                printf("Enter Raw =");
                scanf("%d", &r);
                printf("\nEnter Col =");
                scanf("%d", &c);
            }
        }
        if (r % 2 == 0 && c % 2 == 1) {
            arr[r - 1][2 * c - 2].c = 186;
            arr[r - 1][2 * c - 2].color = p;
        } else if (r % 2 == 1 && c % 2 == 0) {
            arr[r - 1][2 * c - 2].color = p;
            arr[r - 1][2 * c - 2].c = 205;
            arr[r - 1][2 * c - 1].color = p;
            arr[r - 1][2 * c - 1].c = 205;
            arr[r - 1][2 * c - 3].color = p;
            arr[r - 1][2 * c - 3].c = 205;
        } else {
            printf("No Available Moves\n");
            continue;
        }
        for (int i = 1; i < k; i += 2) {
            for (int j = 2; j < v; j += 4) {
                if (arr[i][j].c == ' ') {
                    if (arr[i][j - 2].c != ' ' && arr[i][j + 2].c != ' ' && arr[i - 1][j].c != ' ' && arr[i + 1][j].c != ' ') {
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
        system("cls");
        PrintGrid(k, v, arr);
        if (b == n * n) {
            printf("Game Ended");
            break;
        }
    }
}

void ComputerVSPlayer(int x) {
    int k , v , n;
    n = 2;
    k = 2 * n + 1;
    v = 4 * n + 1;
    Element arr[k][v];
    Player P , C;
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

}

void SaveGame() {
    ///
}

void LoadGame() {
    ///
}

void Scores(int newScore,char newName[30]) {
    int swap,flag=0;
    char sswap[30];
    Player z[11];
     for(int i=0;i<11;i++){
        z[i].Score=0;
        z[i].Name[0]='\0';
     }
   FILE *f = fopen("scores.txt","r");
   for(int i=0;i<11;i++){
        fscanf(f,"%[^\n]",z[i].Name);
        fscanf(f,"%d\n",&z[i].Score);

     }
     fclose(f);
     for(int j=0;j<10;j++){
        if(!strcmp(z[j].Name,newName)){
            if(newScore>=z[j].Score){
                z[j].Score=newScore;
                flag=1;
                break;
            }
        }
     }
     if(flag==0){
     strcpy(z[10].Name,newName);
     z[10].Score=newScore;
     }
     for (int c = 0 ; c < 11 - 1; c++)
  {
    for (int d = 0 ; d < 11 - c - 1; d++)
    {
      if (z[d].Score < z[d+1].Score)
      {
        swap       = z[d].Score;
        strcpy(sswap,z[d].Name);
        z[d].Score   = z[d+1].Score;
        strcpy(z[d].Name,z[d+1].Name);
        z[d+1].Score = swap;
        strcpy(z[d+1].Name,sswap);
      }
    }
  }

     for(int i=0;i<10;i++){
        if(z[i].Score!=0){
            printf("%d)%s  %d\n",i+1,z[i].Name,z[i].Score);
           // fprintf(b,"%s\n%d\n",z[i].Name,z[i].Score);
        }
     }
     FILE *b =fopen("scores.txt","w");
     for(int i=0;i<10;i++){
        if(z[i].Score!=0){

            fprintf(b,"%s\n%d\n",z[i].Name,z[i].Score);
        }
     }
     fclose(b);

}

void UI(){
    //
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
            PlayerVSPlayer(z);
            break;
        case 2:
            ComputerVSPlayer(z);
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
    for (int i = 0; i < y / 2 + 1; i++) {
        printf("%d ", i + 1);
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
                printf("%c", arr[i][j].c);
            }
        }
        printf("\n");
    }
}
