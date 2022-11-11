/***********************************************/
/* Program: exercise1     Date:                */
/* Authors:                                    */
/*                                             */
/* Program that generates two random nunmbers  */
/* between two given numbers                   */
/*                                             */
/* Input: Command Line                         */
/* -limInf: lower limit                        */
/* -limSup: upper limit                        */
/* -numN: ammount of numbers                   */
/* Output: 0: OK, -1: ERR                      */
/***********************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "permutations.h"

int main(int argc, char** argv)
{
  int i;
  int z = 0;
  unsigned int inf, sup, num, j;
  int *tabla;

  srand(time(NULL));

  if (argc != 7) {
    fprintf(stderr, "Input parameter error:\n\n");
    fprintf(stderr, "%s -limInf <int> -limSup <int> -numN <int>\n", argv[0]);
    fprintf(stderr, "Where:\n");
    fprintf(stderr, " -limInf : Lower limit.\n");
    fprintf(stderr, " -limSup : Upper limit.\n");
    fprintf(stderr, " -numN : ammout of mumbers to generate.\n");
    exit(-1);
  }

  /* check command line */
  for(i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-limInf") == 0) {
      inf = atoi(argv[++i]);
    } else if (strcmp(argv[i], "-limSup") == 0) {
      sup = atoi(argv[++i]);
    } else if (strcmp(argv[i], "-numN") == 0) {
      num = atoi(argv[++i]);
    } else {
      fprintf(stderr, "Wrong Parameter %s \n", argv[i]);
    }
  }

  tabla = malloc(sizeof(int) * num);
  if(!tabla)
    return -1;
  /* print data */
  for(j = 0; j < num; j++) { 
    tabla[j] = random_num(inf, sup);
  }
  printf("Veces que sale cada número:\n");
  for(j = inf; j <= sup; j++)
  {
    for (i = 0; i < num; i++)
    {
      if (tabla[i] == j)
        z++;
    }
    printf("%d: %d\n", j, z);
    z = 0;
  }
  free(tabla);
  return 0;
}
