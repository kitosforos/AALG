/**
 *
 * Description: Implementation of functions for search
 *
 * File: search.c
 * Author: Carlos Aguirre and Javier Sanz-Cruzado
 * Version: 1.0
 * Date: 14-11-2016
 *
 */

#include "search.h"

#include <stdlib.h>
#include <math.h>

/**
 *  Key generation functions
 *
 *  Description: Receives the number of keys to generate in the n_keys
 *               parameter. The generated keys go from 1 to max. The
 * 				 keys are returned in the keys parameter which must be 
 *				 allocated externally to the function.
 */
  
/**
 *  Function: uniform_key_generator
 *               This function generates all keys from 1 to max in a sequential
 *               manner. If n_keys == max, each key will just be generated once.
 */
void uniform_key_generator(int *keys, int n_keys, int max)
{
  int i;

  for(i = 0; i < n_keys; i++) keys[i] = 1 + (i % max);

  return;
}

/**
 *  Function: potential_key_generator
 *               This function generates keys following an approximately
 *               potential distribution. The smaller values are much more 
 *               likely than the bigger ones. Value 1 has a 50%
 *               probability, value 2 a 17%, value 3 the 9%, etc.
 */
void potential_key_generator(int *keys, int n_keys, int max)
{
  int i;

  for(i = 0; i < n_keys; i++) 
  {
    keys[i] = .5+max/(1 + max*((double)rand()/(RAND_MAX)));
  }

  return;
}

PDICT init_dictionary (int size, char order)
{
  PDICT dict;

  if (size <= 0)
    return NULL;
  dict = malloc(sizeof(DICT));
  if (!dict)
    return NULL;
  dict->table = malloc(sizeof(int) * size);
  if (!dict->table)
    return NULL;
  dict->order = order;
  dict->size = size;
  return dict;
}

void free_dictionary(PDICT pdict)
{
  if (!pdict)
    return ;
  free(pdict->table);
  free(pdict);
}

int insert_dictionary(PDICT pdict, int key)
{
	int i;
  
  if (!pdict)
    return ERR;
  
  if (pdict->order == NOT_SORTED)
  {
    pdict->table[pdict->n_data] = key;
    pdict->n_data++;
    return OK;
  }
  else if (pdict->order == SORTED)
  {
    i = pdict->n_data - 1;
    pdict->table[pdict->n_data] = key;
    while (i >= 0 && pdict->table[i] > key)
    {
      pdict->table[i + 1] = pdict->table[i];
      i--;
    }
    pdict->table[i + 1] = key;
    pdict->n_data++;
    return OK;
  }
  return ERR;
}

int massive_insertion_dictionary (PDICT pdict,int *keys, int n_keys)
{
  int i;

  i = 0;
	if (!pdict || n_keys < 1)
    return ERR;
  while (i < n_keys)
    insert_dictionary(pdict, keys[i++]);
  pdict->n_data += n_keys;
  return OK;
}

int search_dictionary(PDICT pdict, int key, int *ppos, pfunc_search method)
{
  int nob;

  nob = 0;
  if (!pdict || !ppos)
    return ERR;

  nob = method(pdict->table, 0, pdict->n_data - 1, key ,ppos);
  if (nob == ERR)
    return ERR;
  return nob;
}


/* Search functions of the Dictionary ADT */
int bin_search(int *table,int F,int L,int key, int *ppos)
{
	int m;
  int nob;

  nob = 0;
  if (!table || F < 0 || L < F || !ppos)
    return ERR;
  while (F <= L)
  {
    m = (F + L)/2;
    nob++;
    if (table[m] == key)
    {
      *ppos = m;
      return nob;
    }
    else if (table[m] < key)
      F = m + 1;
    else
      L = m - 1;
  }
  return ERR;
}

int lin_search(int *table,int F,int L,int key, int *ppos)
{
  int nob;

  nob = 0;
	if (!table || F < 0 || L < F || !ppos)
    return ERR;
  
  while (F <= L)
  {
    nob++;
    if (table[F] == key)
    {
      *ppos = F;
      return nob;
    }
    F++;
  }
  return ERR;
}

int lin_auto_search(int *table,int F,int L,int key, int *ppos)
{
  int aux;
  int nob;

  nob = 0;
	if (!table || F < 0 || L < F || !ppos)
    return ERR;

  while (F <= L)
  {
    nob++;
    if (table[F] == key)
    {
      *ppos = F;
      if (F != 0)
      {
        aux = table[F];
        table[F] = table[F - 1];
        table[F - 1] = aux;
      }
      return nob;
    }
    F++;
  }
  return ERR;
}


