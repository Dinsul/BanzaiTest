#include "myrandom.h"

#ifdef WIN32
#include <QTime>
#else
#include <cstdio>
#endif


int getRandomPositive()
{
    int retVal = getRandom();
    return (retVal > 0) ? retVal : -retVal;
}

int getRandom()
{
    int retVal;
#ifdef WIN32
    static int seed;

    seed += QTime::currentTime().msec();

    qsrand(seed);

    retVal = qrand();
#else
    FILE *devRandom;

    devRandom = fopen(URANDOM_PATH, "r");

    if (!devRandom)
    {
        fprintf(stderr, "Can not open file\n");
        return 0;
    }

    fread(&retVal, sizeof(int), 1, devRandom);

    fclose(devRandom);
#endif

    return retVal;
}


int getRandomRange(int min, int max)
{
    return (getRandomPositive() % (max - min + 1)) + min;
}
