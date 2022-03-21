#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> 
#include "jeu.h"

/**
*** <<!!  INITIALIZING CORE   !!>>
**/
void initializeGeneralGameConfig(generalGameConfig *ggc, int x, int y)
{
    ggc->gameLenX = x;
    ggc->gameLenY = y;
    ggc->restMoves = x * y;
    ggc->lastMove = -1;
}

void initializeTerminalUserInterface(terminalUserInterface *tui)
{
    char *tmp;

    tmp = "               __________    _____     \n"
          "               \\______   \\  /  |  |  \n"
          "                |     ___/ /   |  |_   \n"
          "                |    |    /    ^   /   \n"
          "                |____|    \\____   |   \n"
          "                               |__|    \n";
    strcpy(tui->gameLogo, tmp);
    strcpy(tui->developer, " Bencheci Valentin");

    tmp = "                       ____   \n"
          "                      /_   |  \n"
          "                       |   |  \n"    
          "                       |   |  \n"
          "                       |___|  \n";
    tui->backCount[0] = tmp;

    tmp = "                    ________         \n"
          "                    \\_____  \\      \n"
          "                    /  ____/         \n"
          "                   /       \\        \n"
          "                   \\_______ \\      \n"
          "                           \\/       \n";
    tui->backCount[1] = tmp;

    tmp = "                      ________      \n"
          "                      \\_____  \\   \n"
          "                       _(__  <      \n"
          "                      /       \\    \n"
          "                     /______  /     \n"
          "                            \\/     \n";
    tui->backCount[2] = tmp;
     
    tmp = "1. Jouer PUISSANCE 4\n"
          "2. Affichage des statistiques\n"
          "3. Comment jouer";
    strcpy(tui->mainMenu, tmp);

    tmp = "1. Player VS Player\n"
          "2. Player VS AI\n"
          "3. AI VS AI\n"
          "4. Charger le dernier match";
    strcpy(tui->typePlayMenu, tmp);

    tmp = "1. Placer une jeton dans une colonne\n"
          "2. Tourner le plateau de 90 degres sur la gauche\n"
          "3. Tourner le plateau de 90 degres sur la droite\n"
          "4. Retourner le plateau\n"
          "5. Sauvegarder le jeu";
    strcpy(tui->playMenu, tmp);

    tmp = "--> Regles pour le nom du nickname : \n"
          "1. Pas plus de 10 caracteres\n"
          "2. Le 1-re caractere doit etre alpha\n"
          "3. Les nickname ne doit pas etre les memes\n\n"
          "--> Regles pour le choix du couleur : \n"
          "1. Le premier joueur peut choisir entre <X> et <O>\n";
    strcpy(tui->nicknameRule, tmp);

    tmp = "--> Regles du jeu : \n\n"
          "Le jeu de Puissance 4 est un jeu a 2 joueurs ayant pour but d'aligner 4 jetons de la meme couleur.\n"
          "a chaque tour, chaque joueur peut ajouter un jeton de sa couleur dans une colonne\n"
          "Ce jeton ira a la position la plus basse dans cette colonne.\n"
          "Si toutes les cases de la grille sont remplies et qu'aucun joueur n'a reussi a aligner 4 jetons, la partie est declaree egale.\n";
    strcpy(tui->gameRule, tmp);

    tui->allMenu[0] = tui->mainMenu;
    tui->allMenu[1] = tui->playMenu;
    tui->allMenu[2] = tui->typePlayMenu;
}

void initializePlayerConfig(playersConfig *plConf, terminalUserInterface *tui, logConfig *lgConf, int gmType)
{
    char *tmp = malloc(sizeof(char) * 150);
    int operations = -2;

    if (gmType == 0 || gmType == 1)
    {   
        printHeader(tui);
        printf("%s", tui->nicknameRule); 
        waitEnter();
    }

    if (gmType == 0 || gmType == 1)
    {
        while(operations != -1)
        {
            printHeader(tui);
            printf("Nickname_1 : ");    
            scanf("%s", tmp);
            freeBuffer(stdin);
            
            if(checkNickname(tmp))
            {  
                warnError(tui, lgConf, "101 : mauvaise nickname_1");
            }
            else
            {   
                strcpy(plConf->player1Name, tmp);
                operations = -1; 
            }  
        }
        
        while(operations != 0)
        {
            printHeader(tui);
            printf("Couleur_1 : ");
            scanf("%s", tmp);
            freeBuffer(stdin);

            if(!(strcmp(tmp, "X") == 0 || strcmp(tmp, "O") == 0))
            {
                warnError(tui, lgConf, "103 : mauvaise couleur_1"); 
            }
            else
            {
                plConf->player1Ch = tmp[0];
                operations = 0;
            }
        }
    }

    if (gmType == 0)
    {
        while (operations != 1)
        {
            printHeader(tui);
            printf("Nickname_2 : ");
            scanf("%s", tmp);
            freeBuffer(stdin);

            if(checkNickname(tmp) || strcmp(tmp, plConf->player1Name) == 0)
            {
                warnError(tui, lgConf, "102 : mauvaise nickname_2");
            }
            else
            {
                printHeader(tui);
                plConf->player2Ch = getOppositColor(plConf->player1Ch);
                strcpy(plConf->player2Name, tmp);
                printf("Couleur_2 : %c\n", plConf->player2Ch);
                waitEnter();
                operations = 1;
            }
        }
    }
    
    if (gmType == 2)
    {
        strcpy(plConf->player1Name, "AI_1");
        plConf->player1Ch = 'X';
    }

    if(gmType == 2 || gmType == 1)
    {
        strcpy(plConf->player2Name, "AI_2");
        plConf->player2Ch = getOppositColor(plConf->player1Ch);
    }

    free(tmp);
}

void initializeStatisticConfig(statisticConfig *stConf)
{
    for(int i = 0; i < 3; i++)
    {
        stConf->totalPvsP[i] = 0;
        stConf->totalPvsAI[i] = 0;
        stConf->totalAIvsAI[i] = 0;
    }
}

void initializeLogConfig(logConfig *lgConf)
{
    strcpy(lgConf->errorLog, "error.log");
    strcpy(lgConf->gameLog, "gameActions.log");
}

/**
*** <<!!  MENU CORE   !!>>
**/
void mainMenu(generalGameConfig *ggc ,terminalUserInterface *tui, playersConfig *plConf, logConfig *lgConf, statisticConfig *stConf)
{
    int opt = -1;
    char *tampon;

    resetGameBoard(ggc);
    opt = printMenu(ggc, tui, 0, 3, tampon);

    switch (opt)
    {
        case 1:
            typePlayMenu(ggc, tui, plConf, lgConf, stConf);
            break;

        case 2:
            if (checkFileExists("statistics.txt") == 1)
            {
                showStatistic(stConf, tui);
                mainMenu(ggc, tui, plConf, lgConf, stConf);
            }

            printHeader(tui);
            warnError(tui, lgConf, "501: Il n'y a pas de statistique");
            mainMenu(ggc, tui, plConf, lgConf, stConf);
            break;

        case 3:
            printHeader(tui);
            printf("%s", tui->gameRule);
            waitEnter();
            mainMenu(ggc, tui, plConf, lgConf, stConf);
            break;
    }
}

void typePlayMenu(generalGameConfig *ggc ,terminalUserInterface *tui, playersConfig *plConf, logConfig *lgConf, statisticConfig *stConf)
{
    int opt = -1;
    char *tampon;

    opt = printMenu(ggc, tui, 2, 4, tampon);

    switch (opt)
    {
        case 1:
            ggc->gameType = 0;
            initializePlayerConfig(plConf, tui, lgConf, ggc->gameType); 
            startGamePvsP(ggc, tui, plConf, lgConf, stConf);
            break;

        case 2:
            ggc->gameType = 1;
            initializePlayerConfig(plConf, tui, lgConf, ggc->gameType); 
            startGamePvsAI(ggc, tui, plConf, lgConf, stConf);
            break;

        case 3:
            ggc->gameType = 2;
            initializePlayerConfig(plConf, tui, lgConf, ggc->gameType);
            startGameAIvsAI(ggc, tui, plConf, lgConf, stConf);
            break;

        case 4:
            if (checkFileExists("savedGames.txt") == 1)
            {
                loadSavedGame(ggc, plConf);

                if(ggc->gameType == 0)
                {
                   startGamePvsP(ggc, tui, plConf, lgConf, stConf); 
                }

                startGamePvsAI(ggc, tui, plConf, lgConf, stConf);
            }

            printHeader(tui);
            warnError(tui, lgConf, "401: Il n'y a pas de parties sauvegardees");
            mainMenu(ggc, tui, plConf, lgConf, stConf);
            break;
    }
}

int printMenu(generalGameConfig *ggc, terminalUserInterface *tui, int optMenu, int optMax, char *player)
{
    int opt = -1;
    char input[50];

    while(opt < 1 || opt > optMax)
    {
        printHeader(tui);
       
        switch (optMenu)
        {
            case 1:
                printGameBoard(ggc);
                printf("\nLe tour de %s : \n", player);
                break;
        }

        printLine(54);
        printf("%s\n",tui->allMenu[optMenu]);
        printLine(54);
        printf("\n%30s", ">OPTION: ");

        if(optMenu == 1 && optMax == 7)
        {
            printf("1");
            strcpy(input, "1");
        }
        else
        {
            scanf("%s", input);
            freeBuffer(stdin);
        }
        
        if (strlen(input) == 1)
        {
            opt = input[0] - '0';
        }
    }

    return opt;
}

/**
*** <<!!  PLAY CORE   !!>>
**/
void resetGameBoard(generalGameConfig *ggc)
{
    for(int i = 0; i < ggc->gameLenY; i++)
    {
        for (int j = 0; j < ggc->gameLenX; j++)
        {
            ggc->gameBoard[i][j] = ' ';
        }
    }

    ggc->restMoves = ggc->gameLenX * ggc->gameLenY;
    ggc->lastMove = -1;
}

int evaluate(generalGameConfig *ggc, playersConfig *plConf, statisticConfig *stConf)
{
    int score = 0;

    if (checkWinner(ggc, plConf, stConf) == 1)
    {
        score += 5;
    }
    else if (checkWinner(ggc, plConf, stConf) == 2)
    {
        score -= 5;
    } 

    return score;
}

int * minMax(generalGameConfig *ggc, playersConfig *plConf, statisticConfig *stConf, int deepth, int player)
{
    int *best = malloc(sizeof(int) * 2);
    int score[2] = {0, 0};
    int tampon;

    if (player == 1)
    {
        best[0] = -1;
        best[1] = -10000;
    }
    else
    {
        best[0] = -1;
        best[1] = 10000;
    }
    
    if (deepth == 0 || checkWinner(ggc, plConf, stConf) == 1 || checkWinner(ggc, plConf, stConf) == 2)
    {   
        score[1] = evaluate(ggc, plConf, stConf); 
        best[0] = -1;
        best[1] = score[1]; 
        return best;
    }

    for(int i = 1; i <= ggc->gameLenY; i++)
    {
        if (checkMove(ggc, i) == 1)
        {   
            setMove(ggc, i, getPlayerColor(plConf, player), &tampon);
            int *scoreTampon;
            scoreTampon = minMax(ggc, plConf, stConf, deepth - 1, getAnotherPlayer(player));
            assign2Arrays(score, scoreTampon);
            ggc->gameBoard[tampon][i - 1] = ' ';
            ggc->restMoves++;
            score[0] = i;  

            if (player == 1)
            {   
                if (score[1] > best[1])
                {  
                    assign2Arrays(best, score);
                }
            }
            else
            {
                if (score[1] < best[1])
                {   
                    assign2Arrays(best, score);
                }
            }
        }
    }

    free(best);
    return best;
}

void startGamePvsAI(generalGameConfig *ggc, terminalUserInterface *tui, playersConfig *plConf, logConfig *lgConf, statisticConfig *stConf)
{
    int opt;
    int successMove;
    int yVal;
    int coordinate;
    int currentPlayerOrder;
    char currentPlayer[11];
    char currentChar;

    int *minMaxResult = malloc(sizeof(int) * 2);

    decideFirstMove(ggc);
    printHeader(tui);

    if (ggc->firstMove == 1)
    {
        printf("%s va commencer le jeu!\n", plConf->player1Name);
        strcpy(currentPlayer, plConf->player1Name);
        currentChar = plConf->player1Ch;
        currentPlayerOrder = 1;
    }
    else
    {
        printf("%s va commencer le jeu!\n", plConf->player2Name);
        strcpy(currentPlayer, plConf->player2Name);
        currentChar = plConf->player2Ch;
        currentPlayerOrder = 2;
    }

    waitEnter();
    backCount(tui);

    while (ggc->restMoves >= 0)
    {
        if (currentPlayerOrder == 2)
        {
            printMenu(ggc, tui, 1, 7, currentPlayer);
            opt = 1;
        }
        else
        {
            opt = printMenu(ggc, tui, 1, 5, currentPlayer);
        }

        switch (opt)
        {
            case 1:
                printf("\nColonne : ");

                if (currentPlayerOrder == 2)
                {
                    minMaxResult = minMax(ggc, plConf, stConf, 4, currentPlayerOrder);
                    coordinate = minMaxResult[0];
                    printf("%d\n", minMaxResult[0]);
                    waitEnter();
                }
                else
                {
                    scanf("%d", &coordinate);
                    freeBuffer(stdin);
                }
                successMove = setMove(ggc, coordinate, currentChar, &yVal);
                break;

            case 2:
                turnLeft(ggc);
                break;

            case 3:
                turnRight(ggc);
                break; 

            case 4:
                turn180(ggc);
                break; 

            case 5:
                printf("\n-->Le jeu a ete sauvegarde!");
                waitEnter();
                ggc->lastMove = currentPlayerOrder;
                saveGame(ggc, plConf);
                mainMenu(ggc, tui, plConf, lgConf, stConf);
                break;
        }
                
        if(successMove == 1)
        {
            int chWin = checkWinner(ggc, plConf, stConf);

            if (chWin >= 1 && chWin <= 3)
            {
                showWinner(ggc, tui, plConf, stConf, chWin);
                mainMenu(ggc, tui, plConf, lgConf, stConf);
            }
        }

        if ((opt == 1 && successMove == 1) || (opt != 1))
        {
            currentChar = getOppositColor(currentChar);
            
            if(strcmp(currentPlayer, plConf->player1Name) == 0)
            {
                strcpy(currentPlayer, plConf->player2Name);
                currentPlayerOrder = 2;
            }
            else
            {
                strcpy(currentPlayer, plConf->player1Name);
                currentPlayerOrder = 1
                ;
            }
        } 
        else
        {   
            char tmp[70];
            snprintf(tmp, 70, "301 : le jeton n'a pas ete place. Player: %s", currentPlayer);
            warnError(tui, lgConf, tmp);
        } 
    }

    free(minMaxResult);
}

void startGameAIvsAI(generalGameConfig *ggc, terminalUserInterface *tui, playersConfig *plConf, logConfig *lgConf, statisticConfig *stConf)
{
    int opt;
    int successMove;
    int yVal;
    int currentPlayerOrder;
    char currentPlayer[11];
    char currentChar;

    int *minMaxResult = malloc(sizeof(int) * 2);

    decideFirstMove(ggc);
    printHeader(tui);

    if (ggc->firstMove == 1)
    {
        printf("%s va commencer le jeu!\n", plConf->player1Name);
        strcpy(currentPlayer, plConf->player1Name);
        currentChar = plConf->player1Ch;
        currentPlayerOrder = 1;
    }
    else
    {
        printf("%s va commencer le jeu!\n", plConf->player2Name);
        strcpy(currentPlayer, plConf->player2Name);
        currentChar = plConf->player2Ch;
        currentPlayerOrder = 2;
    }

    waitEnter();
    backCount(tui);

    while (ggc->restMoves >= 0)
    {
        printMenu(ggc, tui, 1, 7, currentPlayer);
        minMaxResult = minMax(ggc, plConf, stConf, 4, currentPlayerOrder);
        printf("\nColonne : %d\n", minMaxResult[0]); 

        successMove = setMove(ggc, minMaxResult[0], currentChar, &yVal);
        waitEnter();

        if(successMove == 1)
        {
            int chWin = checkWinner(ggc, plConf, stConf);

            if (chWin >= 1 && chWin <= 3)
            {
                showWinner(ggc, tui, plConf, stConf, chWin);
                mainMenu(ggc, tui, plConf, lgConf, stConf);
            }

            currentChar = getOppositColor(currentChar);
            
            if(strcmp(currentPlayer, plConf->player1Name) == 0)
            {
                strcpy(currentPlayer, plConf->player2Name);
                currentPlayerOrder = 2;
            }
            else
            {
                strcpy(currentPlayer, plConf->player1Name);
                currentPlayerOrder = 1;
            }
        }
        else
        {
            char tmp[70];
            snprintf(tmp, 70, "301 : le jeton n'a pas ete place. Player: %s", currentPlayer);
            warnError(tui, lgConf, tmp);
        }

    }

    free(minMaxResult);
}

void checkScore(generalGameConfig *ggc, char gameBoard[9][9], int yCoord, int xCoord, char color, int *score)
{
    if (gameBoard[yCoord][xCoord] == color)
    {
        *score = *score + 1;
    }
    else
    {
        *score = 0;
    }
}

void showWinner(generalGameConfig *ggc, terminalUserInterface *tui, playersConfig *plConf, statisticConfig *stConf, int chWin)
{   
    printHeader(tui);
    printGameBoard(ggc);

    switch (chWin)
    {
        case 1:
            printf("\n %s a gagne le jeu!", plConf->player1Name); 
            updateStatistic(stConf, ggc->gameType, 1);
            break;

        case 2:
            printf("\n %s a gagne le jeu!", plConf->player2Name); 
            updateStatistic(stConf, ggc->gameType, 2);
            break;
        
        case 3:
            printf("\n Egalite!");
            break;
    }

    waitEnter();
}

int checkWinner(generalGameConfig *ggc, playersConfig *plConf, statisticConfig *stConfig)
{
    int xqtyX = 0;
    int xqtyO = 0;

    int yqtyX = 0;
    int yqtyO = 0;

    int dqtyX = 0;
    int dqtyO = 0;

    int xWin = 0;
    int oWin = 0;

    for (int i = 0; i < ggc->gameLenY; i++)
    {
        for (int j = 0; j < ggc->gameLenX; j++)
        {   
            checkScore(ggc, ggc->gameBoard, i, j, 'X', &xqtyX);
            checkScore(ggc, ggc->gameBoard, i, j, 'O', &xqtyO);
            checkScore(ggc, ggc->gameBoard, j, i, 'X', &yqtyX);
            checkScore(ggc, ggc->gameBoard, j, i, 'O', &yqtyO);
            
            if(xqtyX >= 4)
            {   
                xWin++;
            }
            if(xqtyO >= 4)
            {
                oWin++;
            }
            if(yqtyX >= 4)
            {
                xWin++;
            }
            if(yqtyO >= 4)
            {
                oWin++; 
            }
        }
        xqtyO = 0;
        xqtyX = 0;
        yqtyO = 0;
        yqtyX = 0;
    }

    //check for all diagonal possibilities for winning | down diagonals
    for (int i = 0; i < ggc->gameLenY; i++)
    {
        for (int j = 0; j < ggc->gameLenX - i; j++)
        {
            checkScore(ggc, ggc->gameBoard, j + i, j, 'X', &dqtyX);
            checkScore(ggc, ggc->gameBoard, j + i, j, 'O', &dqtyO);
        
            if (dqtyX >= 4)
            {
                xWin++;
            }
            if (dqtyO >= 4)
            {
                oWin++; 
            }
        }
        dqtyO = 0;
        dqtyX = 0;
    }

    for (int i = 0; i < ggc->gameLenY; i++)
    {
        for (int j = 0; j < ggc->gameLenX - i; j++)
        {
            checkScore(ggc, ggc->gameBoard, j, j + i, 'X', &dqtyX);
            checkScore(ggc, ggc->gameBoard, j, j + i, 'O', &dqtyO);
        
            if (dqtyX >= 4)
            {
                xWin++;
            }
            if (dqtyO >= 4)
            {
                oWin++;
            }
        }
        dqtyO = 0;
        dqtyX = 0;
    }

    //check for all diagonal possibilities for winning | up diagonals
    dqtyO = 0;
    dqtyX = 0;

    for (int i = 0; i < ggc->gameLenY; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            checkScore(ggc, ggc->gameBoard, i - j, j, 'X', &dqtyX);
            checkScore(ggc, ggc->gameBoard, i - j, j, 'O', &dqtyO);
        
            if (dqtyX >= 4)
            {
                xWin++;
            }
            if (dqtyO >= 4)
            {
                oWin++; 
            }
        }
        dqtyO = 0;
        dqtyX = 0;
    }

    for (int i = 0; i < ggc->gameLenY; i++)
    {
        for (int j = ggc->gameLenX - 1; j >= i; j--)
        {
            checkScore(ggc, ggc->gameBoard, ggc->gameLenX - j + i - 1, j, 'X', &dqtyX);
            checkScore(ggc, ggc->gameBoard, ggc->gameLenX - j + i - 1, j, 'O', &dqtyO);
        
            if (dqtyX >= 4)
            {
                xWin++;
            }
            if (dqtyO >= 4)
            {
                oWin++; 
            }
        }
        dqtyO = 0;
        dqtyX = 0;
    }
    
    if (xWin > 0 || oWin > 0)
    {   
        if(xWin > oWin)
        {
            return getPlayerOrderWithColor(plConf, 'X');
        }
        else if(oWin > xWin)
        {
            return getPlayerOrderWithColor(plConf, 'O');
        }
        else
        {  
            return 3;
        }
    }    

    if (xWin == 0 && oWin == 0 && ggc->restMoves == 0)
    {
        return 3;
    }       

    return -1;
}

void transpose(generalGameConfig *ggc)
{
    char arrayCopy[9][9];

    for (int i = 1; i < ggc->gameLenY; i++)
    {
        for (int j = 0; j < i; j++)
        {
            char tmp = ggc->gameBoard[i][j];
            ggc->gameBoard[i][j] = ggc->gameBoard[j][i];
            ggc->gameBoard[j][i] = tmp;
        }
    }
}

void reverseRow(generalGameConfig *ggc)
{
    for (int i = 0; i < ggc->gameLenY; i++)
    {
        for (int j = 0; j < ggc->gameLenX / 2; j++)
        {
            char tmp = ggc->gameBoard[i][j];
            ggc->gameBoard[i][j] = ggc->gameBoard[i][ggc->gameLenX - 1 - j];
            ggc->gameBoard[i][ggc->gameLenX - 1 - j] = tmp;
        }
    }
}

void reverseCol(generalGameConfig *ggc)
{
    for (int i = 0; i < ggc->gameLenY; i++)
    {
        for (int j = 0; j < ggc->gameLenX / 2; j++)
        {
            char tmp = ggc->gameBoard[j][i];
            ggc->gameBoard[j][i] = ggc->gameBoard[ggc->gameLenX - 1 - j][i];
            ggc->gameBoard[ggc->gameLenX - 1 - j][i] = tmp;
        }
    }
}

void turnLeft(generalGameConfig *ggc)
{
    int pos = 0;

    for (int i = 0; i < ggc->gameLenY; i++)
    {
        for (int j = 0; j < ggc->gameLenX; j++)
        {
            if(ggc->gameBoard[i][j] == 'X' || ggc->gameBoard[i][j] == 'O')
            {
                while (pos < j && ggc->gameBoard[i][pos] != ' ')
                {
                    pos++;
                }
                if (ggc->gameBoard[i][pos] == ' ')
                {
                    ggc->gameBoard[i][pos] = ggc->gameBoard[i][j];
                    ggc->gameBoard[i][j] = ' ';
                }
            }
            pos = 0;
        }
    }

    transpose(ggc);
    reverseCol(ggc);
}

void turnRight(generalGameConfig *ggc)
{
    int pos = ggc->gameLenX - 1;

    for (int i = ggc->gameLenY - 1; i >= 0; i--)
    {
        for (int j = ggc->gameLenX - 1; j >= 0; j--)
        {
            if(ggc->gameBoard[i][j] == 'X' || ggc->gameBoard[i][j] == 'O')
            {
                while (pos > j && ggc->gameBoard[i][pos] != ' ')
                {
                    pos--;
                }
                if (ggc->gameBoard[i][pos] == ' ')
                {
                    ggc->gameBoard[i][pos] = ggc->gameBoard[i][j];
                    ggc->gameBoard[i][j] = ' ';
                }
            }
            pos = ggc->gameLenX - 1;
        }
    }

    transpose(ggc);
    reverseRow(ggc);
}

void turn180(generalGameConfig *ggc)
{
    int pos = ggc->gameLenY - 1;

    reverseCol(ggc);
    reverseRow(ggc);

    for (int i = ggc->gameLenY - 1; i >= 0; i--)
    {
        for (int j = ggc->gameLenX - 1; j >= 0; j--)
        {
            if(ggc->gameBoard[i][j] == 'X' || ggc->gameBoard[i][j] == 'O')
            {
                while (pos > i && ggc->gameBoard[pos][j] != ' ')
                {
                    pos--;
                }
                if (ggc->gameBoard[pos][j] == ' ')
                {
                    ggc->gameBoard[pos][j] = ggc->gameBoard[i][j];
                    ggc->gameBoard[i][j] = ' ';
                }
            }
            pos = ggc->gameLenY - 1;
        }
    }
}

void decideFirstMove(generalGameConfig *ggc)
{
    if(ggc->lastMove == -1)
    {
        srand(time(NULL));
        ggc->firstMove = (rand() % 2) + 1;
    }
    else
    {
        ggc->firstMove = ggc->lastMove;
    }
}

int checkMove(generalGameConfig *ggc, int coordinate)
{
    for (int i = ggc->gameLenY - 1; i >= 0 ; i--)
    {
        if (ggc->gameBoard[i][coordinate - 1] == ' ')
        {
            return 1;
        }
    }

    return 0;
}

int setMove(generalGameConfig *ggc, int coordinate, char playerColor, int *yVal)
{   
    if(coordinate >= 1 && coordinate <= ggc->gameLenX)
    {
        for (int i = ggc->gameLenY - 1; i >= 0 ; i--)
        {
            if (ggc->gameBoard[i][coordinate - 1] == ' ')
            {   
                *yVal = i;  
                ggc->gameBoard[i][coordinate - 1] = playerColor;    
                ggc->restMoves--;   
                
                return 1;
            }
        }
    }
    
    return 0;
}

void startGamePvsP(generalGameConfig *ggc, terminalUserInterface *tui, playersConfig *plConf, logConfig *lgConf, statisticConfig *stConf)
{
    int opt;
    int coordinate;
    int successMove;
    int yVal;
    int currentPlayerOrder;
    char currentPlayer[11];
    char currentChar;

    decideFirstMove(ggc);
    printHeader(tui);

    if (ggc->firstMove == 1)
    {
        printf("%s va commencer le jeu!\n", plConf->player1Name);
        strcpy(currentPlayer, plConf->player1Name);
        currentChar = plConf->player1Ch;
        currentPlayerOrder = 1;
    }
    else
    {
        printf("%s va commencer le jeu!\n", plConf->player2Name);
        strcpy(currentPlayer, plConf->player2Name);
        currentChar = plConf->player2Ch;
        currentPlayerOrder = 2;
    }

    waitEnter();
    backCount(tui);

    while (ggc->restMoves >= 0)
    {
        opt = printMenu(ggc, tui, 1, 5, currentPlayer);

        switch (opt)
        {
            case 1:
                printf("\nColonne : ");
                scanf("%d", &coordinate);
                freeBuffer(stdin);
                successMove = setMove(ggc, coordinate, currentChar, &yVal);
                break;

            case 2:
                turnLeft(ggc);
                break;

            case 3:
                turnRight(ggc);
                break; 

            case 4:
                turn180(ggc);
                break; 

            case 5:
                printf("\n-->Le jeu a ete sauvegarde!");
                waitEnter();
                ggc->lastMove = currentPlayerOrder;
                saveGame(ggc, plConf);
                mainMenu(ggc, tui, plConf, lgConf, stConf);
                break;
        }
        
        if(successMove == 1)
        {
            int chWin = checkWinner(ggc, plConf, stConf);

            if (chWin >= 1 && chWin <= 3)
            {
                showWinner(ggc, tui, plConf, stConf, chWin);
                mainMenu(ggc, tui, plConf, lgConf, stConf);
            }
        }

        if ((opt == 1 && successMove == 1) || (opt != 1))
        {
            currentChar = getOppositColor(currentChar);
            
            if(strcmp(currentPlayer, plConf->player1Name) == 0)
            {
                currentPlayerOrder = 2;
                strcpy(currentPlayer, plConf->player2Name);
            }
            else
            {
                currentPlayerOrder = 1;
                strcpy(currentPlayer, plConf->player1Name);
            }
        } 
        else
        {   
            char tmp[70];
            snprintf(tmp, 70, "301 : le jeton n'a pas ete place. Player: %s", currentPlayer);
            warnError(tui, lgConf, tmp);
        }
        
    }
}

void printGameBoard(generalGameConfig *ggc)
{
    printf("%*c", 17, ' ');
    printLine(2 * ggc->gameLenX + 1);

    for (int i = 0; i < ggc->gameLenY; i++)
    {
        printf("%*c", 17, ' ');

        for (int j = 0; j < ggc->gameLenX; j++)
        {
            printf("|%c", ggc->gameBoard[i][j]);
        }
        printf("|\n");
    }

    printf("%*c", 17, ' ');
    printLine(2 * ggc->gameLenX + 1);
    printf("%*c", 17, ' ');
    printCoordinates(ggc->gameLenX);
}

/**
*** <<!!  USER CORE   !!>>
**/
int getPlayerOrderWithColor(playersConfig *plConf,char color)
{
    if (plConf->player1Ch == color)
    {
        return 1;
    }
    else
    {
        return 2;
    }
}

int getAnotherPlayer(int player)
{
    if (player == 1)
    {
        return 2;
    }
    else
    {
        return 1;
    }
}

char getPlayerColor(playersConfig *plConf, int player)
{
    if (player == 1)
    {
        return plConf->player1Ch;
    } 
    else
    {
        return plConf->player2Ch;
    }
    
    return 'X';
}

int checkNickname(char input[])
{
    return (strlen(input) > 10 || strlen(input) == 0 || input[0] <= 65 || (input[0] >=91 && input[0] <= 96) || input[0] >= 123);
}

char getOppositColor(char ch)
{
    if (ch == 'O')
    {
        return 'X';
    }
    else
    {
        return 'O';
    }

    return 'O';
}

char * getPlayerWithColor(playersConfig *plConf, char ch)
{
    if (plConf->player1Ch == ch)
    {
        return plConf->player1Name;
    }
    else
    {
        return plConf->player2Name;
    }

    return plConf->player1Name;
}

/**
*** <<!!  UTILITY CORE   !!>>
**/
void assign2Arrays(int a1[], int a2[])
{
    a1[0] = a2[0];
    a1[1] = a2[1];
}

void printHeader(terminalUserInterface *tui)
{
    clrScreen();
    printf("%s", tui->gameLogo);
    printf("%54s\n\n", tui->developer);
}

void showStatistic(statisticConfig *stConf, terminalUserInterface *tui)
{
    loadStatistic(stConf);
    printHeader(tui);
    printf("---> Statistiques\n\n");
    printLine(118);
    printf("%-35s%-4d%-35s%-4d%-35s%-4d%s\n", "| Total jeux player VS player : ", stConf->totalPvsP[0], "| Victoires player1 : ", stConf->totalPvsP[1], "| Victoires player2 : ", stConf->totalPvsP[2], "|");
    printf("%-35s%-4d%-35s%-4d%-35s%-4d%s\n", "| Total jeux player VS AI : ", stConf->totalPvsAI[0], "| Victoires player1 : ", stConf->totalPvsAI[1], "| Victoires player2 : ", stConf->totalPvsAI[2], "|");
    printf("%-35s%-4d%-35s%-4d%-35s%-4d%s\n", "| Total jeux AI VS AI : ", stConf->totalAIvsAI[0], "| Victoires player1 : ", stConf->totalAIvsAI[1], "| Victoires player2 : ", stConf->totalAIvsAI[2], "|");
    printLine(118);
    waitEnter();
}

void loadStatistic(statisticConfig *stConf)
{
    FILE *fptr;
    char fileNom[] = "statistics.txt"; 
    char tmp[25];
    int tmpInt;
    fptr = fopen(fileNom, "r");

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (j == 0)
            {   
                fscanf(fptr, "%s", tmp); 
            }
            else
            {
                fscanf(fptr, "%d", &tmpInt);

                switch (i)
                {
                    case 0:
                        stConf->totalPvsP[j - 1] = tmpInt;
                        break;
                    case 1:
                        stConf->totalPvsAI[j - 1] = tmpInt;
                        break;
                    case 2:
                        stConf->totalAIvsAI[j - 1] = tmpInt;
                        break;
                }
            }  
        } 
    }

    fclose(fptr);
}

void updateStatistic(statisticConfig *stConf, int gmType, int playerOrder)
{
    if (checkFileExists("statistics.txt") == 1)
    {
        loadStatistic(stConf);
    }

    switch (gmType)
    {
        case 0:
            stConf->totalPvsP[0]++;
            stConf->totalPvsP[playerOrder]++;
            break;
        case 1:
            stConf->totalPvsAI[0]++;
            stConf->totalPvsAI[playerOrder]++;
            break;
        case 2:
            stConf->totalAIvsAI[0]++;
            stConf->totalAIvsAI[playerOrder]++;
            break;
    }
    saveStatistic(stConf);
}

int checkFileExists(char fileName[])
{
    FILE *fptr;
    if((fptr = fopen(fileName, "r")) != NULL)
    {
        fclose(fptr);
        return 1;
    }
    else
    {
        return 0;
    }
}

void loadSavedGame(generalGameConfig *ggc, playersConfig *plConf)
{
    FILE *fptr;
    char tmp[25];
    char tmpCh;
    int tmpInt;
    char fileNom[] = "savedGames.txt"; 
    fptr = fopen(fileNom, "r");
    
    for(int i = 0; i < 14; i++)
    {
        if (i <= 7 || i == 8 || i == 10 || i == 12)
        {
            fscanf(fptr, "%s", tmp);
        }
        else
        {
            fscanf(fptr, "%d", &tmpInt);

            if(i == 9)
            {
                ggc->lastMove = tmpInt;
            }
            else if(i == 11)
            {
                ggc->gameType = tmpInt;
            }
            else
            {
                ggc->restMoves = tmpInt;
            }
        }
        
        switch (i)
        {
            case 1:
                strcpy(plConf->player1Name, tmp);
                break;

            case 3:
                plConf->player1Ch = tmp[0];
                break;
            
            case 5:
                strcpy(plConf->player2Name, tmp);
                break;

            case 7:
                plConf->player2Ch = tmp[0];
                break;
        }
    }

    for(int i = 0; i < ggc->gameLenY; i++)
    {
        for(int j = 0; j < ggc->gameLenX; j++)
        {
            fscanf(fptr, " %c", &tmpCh);

            if(tmpCh == 'X' || tmpCh == 'O')
            {
                ggc->gameBoard[i][j] = tmpCh;
            }
        }
    }

    fclose(fptr);
}

void saveStatistic(statisticConfig *stConf)
{
    FILE *fptr;
    char fileNom[] = "statistics.txt";

    fclose(fopen(fileNom,"w+"));
    fptr = fopen(fileNom,"a");
    fprintf(fptr, "totalGamesPvsP: %5d %5d %5d\n", stConf->totalPvsP[0], stConf->totalPvsP[1], stConf->totalPvsP[2]);
    fprintf(fptr, "totalGamesPvsAI: %5d %5d %5d\n", stConf->totalPvsAI[0], stConf->totalPvsAI[1], stConf->totalPvsAI[2]);
    fprintf(fptr, "totalGamesAIvsAI: %5d %5d %5d\n", stConf->totalAIvsAI[0], stConf->totalAIvsAI[1], stConf->totalAIvsAI[2]);

    fclose(fptr);
}

void saveGame(generalGameConfig *ggc, playersConfig *plConf)
{
    FILE *fptr;
    char fileNom[] = "savedGames.txt";

    fclose(fopen(fileNom,"w+"));
    fptr = fopen(fileNom,"a");
    fprintf(fptr, "player1_name: %10s  player1_color: %3c\n", plConf->player1Name, plConf->player1Ch);
    fprintf(fptr, "player2_name: %10s  player2_color: %3c\n\n", plConf->player2Name, plConf->player2Ch);
    fprintf(fptr, "lastMove: %d   \ngameType: %d   \nrestMoves: %d\n\n", ggc->lastMove, ggc->gameType, ggc->restMoves);

    for(int i = 0; i < ggc->gameLenY; i++)
    {
        for(int j = 0; j < ggc->gameLenX; j++)
        {
            if (ggc->gameBoard[i][j] == ' ')
            {
                fprintf(fptr, ".");
            }
            else
            {
                fprintf(fptr, "%c", ggc->gameBoard[i][j]); 
            }
            
            if (j != ggc->gameLenX - 1)
            {
                fprintf(fptr, " ");
            }
        }
        fprintf(fptr, "\n");
    }

    fclose(fptr);
}

void freeBuffer(FILE* f)
{  
    int c;
    while((c=fgetc(f)) != '\n' && c != EOF); 
}

void waitEnter(void)
{
    char c;
    printf("\n\n                  [Presse ENTER]\n");
    while((c = getc(stdin)) != '\n');
}

void backCount(terminalUserInterface *tui)
{
    for (int i = 2; i >= 0; i--)
    {
        printHeader(tui);
        printf("%s", tui->backCount[i]);
        waitEnter();
    }
}

void logInfo(char fileNom[], char information[])
{
    FILE *fptr;
    time_t rawtime = time(NULL);
    struct tm *ptm = localtime(&rawtime);
    fptr = fopen(fileNom,"a");
    fprintf(fptr,"%d:%d:%d -> %s\n", ptm->tm_hour, ptm->tm_min, ptm->tm_sec, information);
    fclose(fptr);
}

void warnError(terminalUserInterface *tui, logConfig *lgConf, char error[])
{
    printHeader(tui);
    printf("ERROR %s\n", error);
    logInfo(lgConf->errorLog, error);
    waitEnter();
}

void printLine(int n)
{
    for(int i = 0; i < n; i++)
    {
        printf("_");
    }
    printf("\n");
}

void printCoordinates(int x)
{
    for (int i = 1; i <= x; i++)
    {
        printf(" %d", i);
    }
    printf("\n");
}
