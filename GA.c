#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define Population 1000
#define Range_max 256.0f
#define Range_min 0.0f
#define rool 5
#define length 1// length of DNA.

void getError(float Peoples[][length], float *Errors);
void generatePeoples(float Peoples[][length]);
void variation(float Peoples[][length], int index);
void multiplication(float Peoples[][length], int *goods, int goodCount, int index, int BEST);
int update(float Peoples[][length], float *Errors);

void getError(float Peoples[][length], float *Errors) {
  //Your codes here.
}

void generatePeoples(float Peoples[][length]) { // generate random "peoples"
  for (int i=0; i<Population; i++) {
    for (int j=0; j<length; j++)
      Peoples[i][j] = ((rand()/(float)RAND_MAX) * (Range_max-Range_min) + Range_min); // Generate x and min<x<max
  }
}

void variation(float Peoples[][length], int index) {
  for (int i=0; i<length; i++) {
    if ((rand()/(float)RAND_MAX) >= 0.97)
      Peoples[index][i] += (int)((rand()/(float)RAND_MAX) * 10 - 5);
  }
}

void multiplication(float Peoples[][length], int *goods, int goodCount, int index, int BEST) {
  int spouse = goods[(int)((rand()/(float)RAND_MAX)*(goodCount))];
  //int spouse = BEST;
  for (int i=0; i<length; i++) {
    if ((rand()/(float)RAND_MAX) >= 0.5)
      Peoples[index][i] = Peoples[spouse][i];
  }
  variation(Peoples, index);
}

int update(float Peoples[][length], float *Errors) {
  float Error_avg = 0;
  int BEST = 0;
  int goodList[Population];
  int goodCount = 0;
  
  for (int i=0; i<Population; i++) { // Get the average of errors.
    Error_avg += Errors[i];
    if (Errors[i] < Errors[BEST])
      BEST = i;
  }
  Error_avg = (Error_avg/Population);

  for (int i=0; i<Population; i++) { //Search goods.
    if (Errors[i] < Error_avg) {
      goodList[goodCount] = i;
      goodCount += 1;
    }
  }
  
  for (int i=0; i<Population; i++) {
    if (Errors[i] >= Error_avg)
      multiplication(Peoples, goodList, goodCount, i, BEST);
  }
  return BEST;
}

int main() {
  srand(time(NULL));
  float *Peoples;
  float *Errors;
  int BEST = 100;

  Errors = (float *)malloc(sizeof(float)*Population);
  Peoples = (float *)malloc(sizeof(float)*Population*length);
  
  generatePeoples(Peoples);
  getError(Peoples, Errors);
  
  while (Errors[BEST] > 0.0f) {
    for (int i=0; i<rool; i++) {
      getError(Peoples, Errors);
      BEST = update(Peoples, Errors);
    }
    printf("Error: %d\n", Errors[BEST]);
  }
  return 0;
}
