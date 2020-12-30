#include <stdio.h>
#include <unistd.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <math.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>

#define bool int
#define false 0
#define true 1


struct InputFlags
{
    bool Confirmed;
    bool Death;
    bool Recovered;
    bool Active;
    char* Date;
};

void toLower(int argc, char* argv[])
{
    int j;

    for (int i = 0; i < argc; i++)
    {
        j = 0;

        while (argv[i][j] != '\0')
        {
            argv[i][j] = argv[i][j] >= 'A' && argv[i][j] <= 'Z' ? argv[i][j] + 32 : argv[i][j];
            j++;
        }
    }
}

void parseArgs(int argc, char* argv[],struct InputFlags* inputFlags)
{
    for (int i = 0; i < argc; i++)
    {
        toLower(argc,argv);

        if (strcmp(argv[i], "--date") == 0)
        {
            inputFlags->Date = argv[i + 1];
        }
        else if (strcmp(argv[i], "--key") == 0)
        {
            for (int j = i; j < argc; j++)
            {
            if (strcmp(argv[j], "confirmed") == 0)
                inputFlags->Confirmed = true;
            else if (strcmp(argv[j], "deaths") == 0)
                inputFlags->Death = true;
            else if (strcmp(argv[j], "recoverd") == 0)
                inputFlags->Recovered = true;
            else if (strcmp(argv[j], "active") == 0)
                inputFlags->Active = true;
            }
        }
    }
}

void initInputFlags(struct InputFlags* inputFlags)
{
    inputFlags->Confirmed = false;
    inputFlags->Death = false;
    inputFlags->Recovered = false;
    inputFlags->Active = false;
    inputFlags->Date = NULL;
}