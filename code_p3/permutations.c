/**
 *
 * Descripcion: Implementation of function that generate permutations
 *
 * File: permutations.c
 * Autor: Carlos Aguirre
 * Version: 1.1
 * Fecha: 21-09-2019
 *
 */


#include "permutations.h"
#include <stdio.h>
#include <stdlib.h>
/***************************************************/
/* Function: random_num Date:                      */
/* Authors: Marcos Alonso y Jorge Paniagua         */
/*                                                 */
/* Rutine that generates a random number           */
/* between two given numbers                       */
/*                                                 */
/* Input:                                          */
/* int inf: lower limit                            */
/* int sup: upper limit                            */
/* Output:                                         */
/* int: random number                              */
/***************************************************/
int random_num(int inf, int sup)
{
  int num;
  if (inf >= sup)
    return ERR;
  num = (rand() % (sup - inf + 1)) + inf;
  return num;
}

/***************************************************/
/* Function: generate_perm Date:                   */
/* Authors: Marcos Alonso y Jorge Paniagua         */
/*                                                 */
/* Rutine that generates a random permutation      */
/*                                                 */
/* Input:                                          */
/* int n: number of elements in the permutation    */
/* Output:                                         */
/* int *: pointer to integer array                 */
/* that contains the permitation                   */
/* or NULL in case of error                        */
/***************************************************/
int* generate_perm(int N)
{
  int i;
  int aux;
  int aux2;
  int *perm = NULL;

  if (N<=0)
    return NULL;
  i = 0;
  perm = malloc(sizeof(int) * N);
  if (!perm)
    return NULL;
  for (i = 0; i < N; i++)
    perm[i] = i;
  for (i = 0; i < N; i++)
  {
    aux2 = random_num(i, N) - 1;
    aux = perm[i];
    if (aux2 == -1)
      aux2++;
    perm[i] = perm[aux2];
    perm[aux2] = aux;
  }
  return perm;
}

/***************************************************/
/* Function: generate_permutations Date:           */
/* Authors:  Marcos Alonso y Jorge Paniagua        */
/*                                                 */
/* Function that generates n_perms random          */
/* permutations with N elements                    */
/*                                                 */
/* Input:                                          */
/* int n_perms: Number of permutations             */
/* int N: Number of elements in each permutation   */
/* Output:                                         */
/* int**: Array of pointers to integer that point  */
/* to each of the permutations                     */
/* NULL en case of error                           */
/***************************************************/
int** generate_permutations(int n_perms, int N)
{
  int **perm;
  int i;

  if (n_perms<= 0 || N<= 0)
    return NULL;
  i = 0;
  perm = malloc(sizeof(int*) * n_perms);
  if (!perm)
    return NULL;
  for(i = 0; i < n_perms; i++)
    perm[i] = generate_perm(N);
  return (perm);
}
