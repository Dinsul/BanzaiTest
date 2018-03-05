#ifndef MyRandom_H
#define MyRandom_H

#define URANDOM_PATH "/dev/urandom"

int getRandom();

int getRandomPositive();

int getRandomRange(int min, int max);


#endif // MyRandom_H
