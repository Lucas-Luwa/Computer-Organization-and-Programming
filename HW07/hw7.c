/**
 * @file hw7.c
 * @author Lucas Luwa
 * @brief structs, pointers, pointer arithmetic, arrays, strings, and macros
 * @date 2021-11-1
 */

// DO NOT MODIFY THE INCLUDE(S) LIST
#include <stdio.h>
#include "hw7.h"
#include "my_string.h"

// Global array of pokemon structs
struct pokemon pokedex[MAX_POKEDEX_SIZE];

int size = 0;

/** catchPokemon
 *
 * @brief creates a new pokemon struct and adds it to the array of pokemon structs, "pokedex"
 *
 *
 * @param "nickname" nickname of the pokemon being created and added
 *               NOTE: if the length of the nickname (including the null terminating character)
 *               is above MAX_NICKNAME_SIZE, truncate nickname to MAX_NICKNAME_SIZE. If the length
 *               is below MIN_NICKNAME_SIZE, return FAILURE.  
 *               
 * @param "pokedexNumber" pokedexNumber of the pokemon being created and added
 * @param "powerLevel" power level of the pokemon being created and added
 * @param "speciesName" species name of the pokemon being created and added
 * @return FAILURE on failure, SUCCESS on success
 *         Failure if any of the following are true:
 *         (1) "nickname" is less than MIN_NICKNAME_SIZE
 *         (2) a pokemon with the same nickname already exits in the array "pokedex"??
 *         (3) adding the new pokemon would cause the size of the array "pokedex" to
 *             exceed MAX_POKEDEX_SIZE
 */
int catchPokemon(const char *nickname, int pokedexNumber, double powerLevel, const char *speciesName)
{
   /* Note about UNUSED_PARAM
   *
   * UNUSED_PARAM is used to avoid compiler warnings and errors regarding unused function
   * parameters prior to implementing the function. Once you begin implementing this
   * function, you can delete the UNUSED_PARAM lines.
   */
  int cutter = 0;
  int result = FAILURE;
  int i;
  for(i = 0; i<size; i=i+1){
    if(my_strncmp(pokedex[i].nickname, nickname, my_strlen(nickname)) == 0){
      cutter = cutter + 1;
    }
  }

  if((size+1) > MAX_POKEDEX_SIZE || my_strlen(nickname)<MIN_NICKNAME_SIZE || my_strlen(speciesName) < MIN_SPECIESNAME_SIZE){
  cutter = cutter + 1;
  }
  if(cutter == 0){
  pokedex[size].pokedexNumber = pokedexNumber;
  pokedex[size].powerLevel = powerLevel;
  my_strncpy(pokedex[size].nickname, nickname, MAX_NICKNAME_SIZE-1);
  my_strncpy(pokedex[size].speciesName,speciesName, MAX_SPECIESNAME_SIZE);
  result = SUCCESS;
  size = size + 1;
  }
  return result;
}

/** updatePokemonNickname
 *
 * @brief updates the nickname of an existing pokemon in the array of pokemon structs, "pokedex"
 *
 * @param "s" pokemon struct that exists in the array "pokedex"
 * @param "nickname" new nickname of pokemon "s"
 *               NOTE: if the length of nickname (including the null terminating character)
 *               is above MAX_NICKNAME_SIZE, truncate nickname to MAX_NICKNAME_SIZE
 * @return FAILURE on failure, SUCCESS on success
 *         Failure if any of the following are true:
 *         (1) the pokemon struct "s" can not be found in the array "pokedex"
 */
int updatePokemonNickname(struct pokemon s, const char *nickname)
{
  int result = FAILURE;
  int cutter = 0;
  int i = 0;
  for(i = 0; i < size; i = i+1){
    if(my_strncmp(s.nickname, pokedex[i].nickname, MAX_NICKNAME_SIZE-1) == 0){
      cutter  = cutter + 1;
      my_strncpy(pokedex[i].nickname, nickname, MAX_NICKNAME_SIZE-1);
    }
  }
  if(cutter != 0){
    result = SUCCESS;
  }
  return result;
}

/** swapPokemon
 *
 * @brief swaps the position of two pokemon structs in the array of pokemon structs, "pokedex"
 *
 * @param "index1" index of the first pokemon struct in the array "pokedex"
 * @param "index2" index of the second pokemon struct in the array "pokedex"
 * @return FAILURE on failure, SUCCESS on success
 *         Failure if any of the following are true:
 *         (1) "index1" and/or "index2" are negative numbers
 *         (2) "index1" and/or "index2" are out of bounds of the array "pokedex"
 */
int swapPokemon(int index1, int index2)
{
  int result = FAILURE;
  int cutter = 0; 
  if(index1 < 0 || index2 < 0 || index1 >= size || index2 >= size){
    cutter = cutter + 1;
  }
  if(cutter == 0){
    struct pokemon temp = pokedex[index1];
    pokedex[index1] = pokedex[index2];
    pokedex[index2] = temp;
  result = SUCCESS;
  }
  return result;
}

/** releasePokemon
 *
 * @brief removes pokemon in the array of pokemon structs, "pokedex", that has the same nickname
 *
 * @param "s" pokemon struct that exists in the array "pokedex"
 * @return FAILURE on failure, SUCCESS on success
 *         Failure if any of the following are true:
 *         (1) the pokemon struct "s" can not be found in the array "pokedex"
 */
int releasePokemon(struct pokemon s)
{
  int cutter = 0;
  
  int i = 0;
  for(i = 0; i < size; i = i+1){
    if(my_strncmp(pokedex[i].nickname, s.nickname, my_strlen(s.nickname)) == 0){
      swapPokemon(i,i+1);
      cutter = cutter+1;
    }
  }
  if(cutter !=0){
   size = size - 1;
   return SUCCESS;
  }
  return FAILURE;
}

/** comparePokemon
 *
 * @brief compares the two pokemons' pokedex number and names (using ASCII)
 *
 * @param "s1" pokemon struct that exists in the array "pokedex"
 * @param "s2" pokemon struct that exists in the array "pokedex"
 * @return negative number if s1 is less than s2, positive number if s1 is greater
 *         than s2, and 0 if s1 is equal to s2
 */
int comparePokemon(struct pokemon s1, struct pokemon s2)
{
  int returnVal = 0;
  if(s1.pokedexNumber != s2.pokedexNumber){
    returnVal = s1.pokedexNumber - s2.pokedexNumber;
  }else{
    returnVal = *s1.nickname - *s2.nickname;
  }
  return returnVal;
}

/** sortPokemon
 *
 * @brief using the comparePokemon function, sort the pokemons in the array of
 * pokemon structs, "pokedex," by the pokedex number and nicknames
 *
 * @param void
 * @return void
 */
void sortPokemon(void)
{
  //bubble it is lol.
  //size is 'n'
  int i = 0;
  int j = 0;
  for(j = 1; j<size;j = j+1){
    for(i = 0; i<size-1;i = i+1){
      if(comparePokemon(pokedex[i],pokedex[j])>0){
        swapPokemon(i, j);
      }
    }
  }
}