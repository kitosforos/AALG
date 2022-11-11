/**
 *
 * Descripcion: Implementation of time measurement functions
 *
 * Fichero: times.c
 * Autor: Carlos Aguirre Maeso
 * Version: 1.0
 * Fecha: 16-09-2019
 *
 */

#include "times.h"
#include "permutations.h"
#include "sorting.h"
#include <stdlib.h>

/***************************************************/
/* Function: average_sorting_time Date:            */
/* Authors:  Marcos Alonso y Jorge Paniagua        */
/*                                                 */
/* Function that save average times of a function  */
/* with N size as input                            */
/*                                                 */
/* Input:                                          */
/* char *file: outfile name                        */
/* pfunc_sort method: function to study            */
/* int N: size of the function input               */
/* PTIME_AA ptime: structure to save times and data*/
/* each iteration                                  */
/* int n_perms: number of permutations to pass to  */
/* the function                                    */
/* Output:                                         */
/* short: OK in case of success                    */
/* ERR en case of error                            */
/***************************************************/
short average_sorting_time(pfunc_sort metodo, 
                              int n_perms,
                              int N, 
                              PTIME_AA ptime)
{
  int **perms;
  int i = 0;
  clock_t start, end;
  double media = 0;
  int OBaux = 0;
  double mediaOB = 0;
  int OBlow = 0;
  int OBhigh = 0;

  if (!metodo || !ptime || N<=0 || n_perms<=0)
    return ERR;
  perms = generate_permutations(n_perms, N);
  if (!perms)
    return ERR;
  while (i < n_perms)
  {
    start = clock();
    OBaux = metodo(perms[i], 0, N - 1);
    end = clock();
    if (OBaux < OBlow || OBlow == 0)
      OBlow = OBaux;
    if (OBhigh < OBaux || OBhigh == 0)
      OBhigh = OBaux;
    media += (double)(end - start);
    mediaOB += OBaux;
    i++;
  }
  for(i=0;i<n_perms;i++)
    free(perms[i]);
  free(perms);
  media /= (double)n_perms;
  mediaOB /= n_perms;
  ptime->time = media;
  ptime->N = N;
  ptime->n_elems = n_perms;
  ptime->average_ob = mediaOB;
  ptime->min_ob = OBlow;
  ptime->max_ob = OBhigh;
  return OK;
}

/***************************************************/
/* Function: generate_sorting_times Date:          */
/* Authors:  Marcos Alonso y Jorge Paniagua        */
/*                                                 */
/* Function that generate an array of structures   */
/* with the times saved using average_sorting_time */
/*                                                 */
/* Input:                                          */
/* char *file: outfile name                        */
/* pfunc_sort method: function to study            */
/* int num_min: minimum number of elements as input*/
/* int num_max: max number of elements as input    */
/* int incr: increment of size of the input in     */
/* each iteration                                  */
/* int n_perms: number of permutations of each     */
/* iteration                                       */
/* Output:                                         */
/* short: OK in case of success                    */
/* ERR en case of error                            */
/***************************************************/
short generate_sorting_times(pfunc_sort method, char* file, 
                                int num_min, int num_max, 
                                int incr, int n_perms)
{
  int i = num_min;
  int j = 0;
  PTIME_AA ptime;
  if (!method || !file || num_min<=0 || num_max< num_min || incr <= 0 || n_perms<=0)
  return ERR;
  ptime = malloc(sizeof(TIME_AA) * ((num_max - num_min)/incr + 1));
  if (!ptime)
    return ERR;
  j = 0;
  while(j < (num_max - num_min)/incr + 1)
  {
    if (average_sorting_time(method, n_perms, i, &ptime[j]) == ERR)
      return ERR;
    i+=incr;
    j++;
  }
  if (save_time_table(file, ptime, j - 1) == ERR)
    return ERR;
  free(ptime);
  return OK;
}

/***************************************************/
/* Function: save_time_table Date:                 */
/* Authors:  Marcos Alonso y Jorge Paniagua        */
/*                                                 */
/* Function that write the data of ptime into      */
/* an outfile                                      */
/*                                                 */
/* Input:                                          */
/* char *file: outfile name                        */
/* PTIME_AA ptime: array of structures where times */
/* are save                                        */
/* int n_times: size of structure                  */
/* Output:                                         */
/* short: OK in case of success                    */
/* ERR en case of error                            */
/***************************************************/
short save_time_table(char* file, PTIME_AA ptime, int n_times)
{
  FILE *fd;
  int i = 0;

  if (!file || !ptime || n_times<=0)
    return ERR;
  fd = fopen(file, "w");
  if (!fd)
    return ERR;
  while (i <= n_times)
  {
    fprintf(fd, "| size: %d | average time: %f | average OB: %f | max OB: %d | min OB: %d |\n", ptime[i].N, ptime[i].time, ptime[i].average_ob, ptime[i].max_ob, ptime[i].min_ob);
    i++;
  }
  fclose(fd);
  return OK;
}
