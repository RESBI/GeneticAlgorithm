#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define Population 1000
#define Range_max 126
#define Range_min 33
#define rool 5

void Char2ASCII(char *words, int *b, int length);
void Draw(int length, int Peoples[][length], int *Errors, int BEST);
void printPeople(int length, int Peoples[][length], int index);
void getError(int length, int Peoples[][length], int *Errors, int *Target);
void generatePeoples(int length, int Peoples[][length]);
void variation(int length, int Peoples[][length], int index);
void multiplication(int length, int Peoples[][length], int *goods, int goodCount, int index, int BEST);
int update(int length, int Peoples[][length], int *Errors);

void Char2ASCII(char *words, int *b, int length) {
  for (int i=0; i<length; i++)
    b[i] = words[i];
}

void Draw(int length, int Peoples[][length], int *Errors, int BEST) {
  int index;
  system("clear");
  for (int i=0; i<(int)(Population/5); i++) {
    for (int j=0; j<5; j++) {
      index = i*5 + j;
      printf("|\t");
      printPeople(length, Peoples, index);
      printf("\t|");
    }
    printf("\n");
  }
}

void printPeople(int length, int Peoples[][length], int index) {
  for (int i=0; i<length; i++)
    //printf("%d ", Peoples[index][i]);
    putchar(Peoples[index][i]);
}

void getError(int length, int Peoples[][length], int *Errors, int *Target) {
  for (int i=0; i<Population; i++) {
    Errors[i] = 0;
    for (int j=0; j<length; j++)
      Errors[i] += abs(Peoples[i][j]-Target[j]); // get error
  }
}

void generatePeoples(int length, int Peoples[][length]) { // generate random "peoples"
  for (int i=0; i<Population; i++) {
    for (int j=0; j<length; j++)
      Peoples[i][j] = (int)((rand()/(float)RAND_MAX) * (Range_max-Range_min) + Range_min); // Generate x and min<x<max
  }
}

void variation(int length, int Peoples[][length], int index) {
  for (int i=0; i<length; i++) {
    if ((rand()/(float)RAND_MAX) >= 0.97)
      Peoples[index][i] += (int)((rand()/(float)RAND_MAX) * 10 - 5);
  }
}

void multiplication(int length, int Peoples[][length], int *goods, int goodCount, int index, int BEST) {
  int spouse = goods[(int)((rand()/(float)RAND_MAX)*(goodCount))];
  //int spouse = BEST;
  for (int i=0; i<length; i++) {
    if ((rand()/(float)RAND_MAX) >= 0.5)
      Peoples[index][i] = Peoples[spouse][i];
  }
  variation(length, Peoples, index);
}

int update(int length, int Peoples[][length], int *Errors) {
  int Error_avg = 0;
  int BEST = 0;
  int goodList[Population];
  int goodCount = 0;
  
  for (int i=0; i<Population; i++) { // Get the average of errors.
    Error_avg += Errors[i];
    if (Errors[i] < Errors[BEST])
      BEST = i;
  }
  Error_avg = (int)(Error_avg/Population);

  for (int i=0; i<Population; i++) { //Search goods.
    if (Errors[i] < Error_avg) {
      goodList[goodCount] = i;
      goodCount += 1;
    }
  }
  
  for (int i=0; i<Population; i++) {
    if (Errors[i] >= Error_avg)
      multiplication(length, Peoples, goodList, goodCount, i, BEST);
  }
  return BEST;
}

int main() {
  srand(time(NULL));
  int length = 18;
  int *Target;
  Target = (int *)malloc(sizeof(int)*length);

  Char2ASCII("Genetic Algorithm!", Target, length);
  
  int *Peoples;
  int *Errors;
  int BEST = 100;

  Errors = (int *)malloc(sizeof(int)*Population);
  Peoples = (int *)malloc(sizeof(int)*Population*length);
  
  generatePeoples(length, Peoples);
  getError(length, Peoples, Errors, Target);
  
  while (Errors[BEST] > 0) {
    for (int i=0; i<rool; i++) {
      getError(length, Peoples, Errors, Target);
      BEST = update(length, Peoples, Errors);
    }
    //Draw(length, Peoples, Errors, BEST);
    //system("clear");
    printPeople(length, Peoples, BEST);
    printf("\n\tError: %d\n", Errors[BEST]);
    /*
    printf("Target: ");
    for (int i=0; i<length; i++)
      putchar(Target[i]);
    printf("\n");
    sleep(1);
    */
  }
  return 0;
}
