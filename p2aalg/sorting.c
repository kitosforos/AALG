/**
 *
 * Descripcion: Implementation of sorting functions
 *
 * Fichero: sorting.c
 * Autor: Carlos Aguirre
 * Version: 1.0
 * Fecha: 16-09-2019
 *
 */


#include "sorting.h"
#include <stdio.h>
#include <stdlib.h>

/***************************************************/
/* Function: SelectSort                            */
/* Authors:  Marcos Alonso y Jorge Paniagua        */
/*                                                 */
/* Function that put an array in increasing order  */
/*                                                 */
/* Input:                                          */
/* int *array: array to order                      */
/* int ip: index of the first element              */
/* int iu: index of the last element               */
/* Output:                                         */
/* int count: number of OBs                        */
/***************************************************/
int SelectSort(int* array, int ip, int iu)
{
  int i;
  int minim;
  int aux;
  int count;
  int N = iu-ip +1;

  count = N*(N-1)/2;
  if (!array || ip<0 || iu<0)
    return ERR;
  i = ip;
  while (i < iu)
  {
    minim = min(array, i, iu);
    if (minim != i)
    {
      aux = array[i];
      array[i] = array[minim];
      array[minim] = aux;
    }
    i++;
  }
  return count;
}

/***************************************************/
/* Function: SelectSortInv                         */
/* Authors:  Marcos Alonso y Jorge Paniagua        */
/*                                                 */
/* Function that put an array in decreasing order  */
/*                                                 */
/* Input:                                          */
/* int *array: array to order                      */
/* int ip: index of the first element              */
/* int iu: index of the last element               */
/* Output:                                         */
/* int count: number of OBs                        */
/***************************************************/

int SelectSortInv(int* array, int ip, int iu)
{
  int i;
  int minim;
  int aux;
  int count;
  int N = iu-ip + 1;

  if (!array || ip<0 || iu<0)
    return ERR;
  i = iu;
  count = N*(N-1)/2;
  while (i > ip)
  {
    minim = min(array, ip, i);
    if (minim != i)
    {
      aux = array[i];
      array[i] = array[minim];
      array[minim] = aux;
    }
    i--;
  }
  return count;
}



/***************************************************/
/* Function: min                                   */
/* Authors:  Marcos Alonso y Jorge Paniagua        */
/*                                                 */
/* Function that finds the min element             */
/*                                                 */
/* Input:                                          */
/* int *array: array to order                      */
/* int ip: index of the first element              */
/* int iu: index of the last element               */
/* Output:                                         */
/* int minim: minim number                         */
/***************************************************/

int min(int* array, int ip, int iu)
{
  int j;
  int minim;

  if (!array || ip<0 || iu<0)
    return ERR;
  minim = ip;
  for (j = ip + 1; j <= iu; j++)
    {
      if (array[j] < array[minim])
        minim = j;
    }
  return (minim);
}

int MergeSort(int* array, int ip, int iu)
{
  int M;
  int count = 0;

  if (!array || ip > iu || ip < 0)
    return ERR;
  if (ip == iu)
    return 0;

  M = (iu + ip)/2;
  count += MergeSort(array, ip, M);
  count += MergeSort(array, M + 1, iu);
  count += merge(array, ip, iu, M);
  return (count);
}

int merge(int* tabla, int ip, int iu, int imedio)
{
  int *tablaAux;
  int i = ip;
  int j = imedio + 1;
  int k = 0;
  int z = 0;
  int count = 0;

  if (!tabla || ip > iu || ip < 0 || imedio < 0)
    return ERR;

  tablaAux = malloc(sizeof(int*) * (iu - ip) + 1);
  if (!tablaAux)
    return ERR;

  while (i <= imedio && j <= iu)
  {
    if (tabla[i] < tabla[j])
    {
      tablaAux[k] = tabla[i];
      i++;
    }
    else
    {
      tablaAux[k] = tabla[j];
      j++;
    }
    k++;
    count++;
  }

  if (i > imedio)
  {
    while (j <= iu)
    {
      tablaAux[k] = tabla[j];
      k++;
      j++;
    }
  }
  else if (j > iu)
  {
    while (i <= imedio)
    {
      tablaAux[k] = tabla[i];
      k++;
      i++;
    }
  }
  while(ip <= iu)
  {
    tabla[ip] = tablaAux[z];
    z++;
    ip++;
  }
  free(tablaAux);
  return count;
}

int quicksort(int* tabla, int ip, int iu)
{
  int pos = 0;
  int count = 0;

  if (!tabla || ip > iu || ip < 0)
    return ERR;
  if (ip == iu)
    return 0;
  
  count += partition(tabla, ip, iu, &pos);
  
  if (ip < pos)
    count += quicksort(tabla, ip, pos - 1);
  if (pos + 1 < iu)
    count += quicksort(tabla, pos + 1, iu);
  printf("%d-----\n", count);
  return count;
}

int partition(int* tabla, int ip, int iu,int *pos)
{
  int k;
  int aux;
  int i;
  int count = 0;

  if (!tabla || ip > iu || ip < 0 || !pos)
    return ERR;
  
  median(tabla, ip, iu, pos);
  k = tabla[*pos];
  aux = tabla[ip];
  tabla[ip] = k;
  tabla[*pos] = aux;
  *pos = ip;
  for (i = ip + 1;i <= iu;i++)
  {
    if (tabla[i] < k)
    {
      (*pos)++;
      aux = tabla[i];
      tabla[i] = tabla[*pos];
      tabla[*pos] = aux;
    }
    printf("OB\n");
    count++;
  }
  aux = tabla[ip];
  tabla[ip] = tabla[*pos];
  tabla[*pos] = aux;
  return count;
}

int median(int *tabla, int ip, int iu,int *pos)
{
  if (!tabla || !pos)
    return ERR;
  *pos = ip;
  return 0;
}