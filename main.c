#include "jeu.c"

int main()
{
    generalGameConfig ggc;
    terminalUserInterface tui;
    playersConfig plConf;
    statisticConfig stConf;
    logConfig lgConf;

    initializeLogConfig(&lgConf);
    initializeGeneralGameConfig(&ggc, 7, 7); 
    initializeTerminalUserInterface(&tui);
    initializeStatisticConfig(&stConf);
    
    mainMenu(&ggc, &tui, &plConf, &lgConf, &stConf);

    return 0;
}