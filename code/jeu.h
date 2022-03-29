#ifdef _WIN32 
    #define clrScreen() (system("cls"))
    #include <Windows.h>
#elif __APPLE__ 
    #define clrScreen() (system("clear"))
    #include <unistd.h>
#elif __linux__
    #define clrScreen() (system("clear"))
    #include <unistd.h>
#endif

typedef struct 
{
    int gameLenX;
    int gameLenY;
 
    int gameType; 
    char gameBoard[9][9];

    int firstMove; 
    int lastMove;
    int restMoves;
} generalGameConfig;

typedef struct
{
    char gameLogo[255];
    char developer[255];

    char mainMenu[255];
    char playMenu[255];
    char typePlayMenu[255];
    char *allMenu[4];

    char nicknameRule[255];
    char gameRule[510];
    char *backCount[3];
} terminalUserInterface;

typedef struct
{
    char player1Name[25];
    char player2Name[25];
    char player1Ch;
    char player2Ch;
} playersConfig;

typedef struct
{
    int totalPvsP[3];
    int totalPvsAI[3];
    int totalAIvsAI[3];
} statisticConfig;

typedef struct
{
    char errorLog[16];
    char gameLog[16];
} logConfig;

/**
*** <<!!  INITIALIZING CORE   !!>>
**/
void initializeGeneralGameConfig(generalGameConfig *ggc, int x, int y);
void initializeTerminalUserInterface(terminalUserInterface *tui);
void initializePlayerConfig(playersConfig *plConf, terminalUserInterface *tui, logConfig *lgConf, int gmType);
void initializeStatisticConfig(statisticConfig *stConf);
void initializeLogConfig(logConfig *lgConf);

/**
*** <<!!  MENU CORE   !!>>
**/
void mainMenu(generalGameConfig *ggc ,terminalUserInterface *tui, playersConfig *plConf, logConfig *lgConf, statisticConfig *stConf);
void typePlayMenu(generalGameConfig *ggc ,terminalUserInterface *tui, playersConfig *plConf, logConfig *lgConf, statisticConfig *stConf);
int printMenu(generalGameConfig *ggc, terminalUserInterface *tui, int optMenu, int optMax, char *player);

/**
*** <<!!  PLAY CORE   !!>>
**/
void resetGameBoard(generalGameConfig *ggc);
int evaluate(generalGameConfig *ggc, playersConfig *plConf, statisticConfig *stConf);
int * minMax(generalGameConfig *ggc, playersConfig *plConf, statisticConfig *stConf, int deepth, int player);
void startGamePvsAI(generalGameConfig *ggc, terminalUserInterface *tui, playersConfig *plConf, logConfig *lgConf, statisticConfig *stConf);
void startGameAIvsAI(generalGameConfig *ggc, terminalUserInterface *tui, playersConfig *plConf, logConfig *lgConf, statisticConfig *stConf);
void startGamePvsP(generalGameConfig *ggc, terminalUserInterface *tui, playersConfig *plConf, logConfig *lgConf, statisticConfig *stConf);
void checkScore(generalGameConfig *ggc, char gameBoard[9][9], int yCoord, int xCoord, char color, int *score);
void showWinner(generalGameConfig *ggc, terminalUserInterface *tui, playersConfig *plConf, statisticConfig *stConf, int chWin);
int checkWinner(generalGameConfig *ggc, playersConfig *plConf, statisticConfig *stConfig);
void transpose(generalGameConfig *ggc);
void reverseRow(generalGameConfig *ggc);
void reverseCol(generalGameConfig *ggc);
void turnLeft(generalGameConfig *ggc);
void turnRight(generalGameConfig *ggc);
void turn180(generalGameConfig *ggc);
void decideFirstMove(generalGameConfig *ggc);
int checkMove(generalGameConfig *ggc, int coordinate);
int setMove(generalGameConfig *ggc, int coordinate, char playerColor, int *yVal);
void printGameBoard(generalGameConfig *ggc);

/**
*** <<!!  USER CORE   !!>>
**/
int getPlayerOrderWithColor(playersConfig *plConf,char color);
int getAnotherPlayer(int player);
char getPlayerColor(playersConfig *plConf, int player);
int checkNickname(char input[]);
char getOppositColor(char ch);
char * getPlayerWithColor(playersConfig *plConf,char ch);

/**
*** <<!!  UTILITY CORE   !!>>
**/
void assign2Arrays(int a1[], int a2[]);
void printHeader(terminalUserInterface *tui);
void showStatistic(statisticConfig *stConf, terminalUserInterface *tui);
void loadStatistic(statisticConfig *stConf);
void updateStatistic(statisticConfig *stConf, int gmType, int playerOrder);
int checkFileExists(char fileName[]);
void loadSavedGame(generalGameConfig *ggc, playersConfig *plConf);
void saveStatistic(statisticConfig *stConf);
void saveGame(generalGameConfig *ggc, playersConfig *plConf);
void freeBuffer(FILE* f);
void waitEnter(void);
void backCount(terminalUserInterface *tui);
void logInfo(char fileNom[], char information[]);
void warnError(terminalUserInterface *tui, logConfig *lgConf, char error[]);
void printLine(int n);
void printCoordinates(int x);
