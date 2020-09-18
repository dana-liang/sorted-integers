/*  dliang26-proj1.c
 *
 *      Written 5/20/20 by Dana Liang for CS 211, Summer 2020
 *
 *      This program reads in a given list of integers and a target integer, and
 *      checks if the target integer is in the correct location to match a sorted
 *      version of the input list.
 */

#include <stdio.h>
#include <stdlib.h>

/* FUNCTION PROTOTYPES */

void copyArray ( int fromArray[], int toArray[], int size);

void myFavoriteSort ( int arr[], int size);

int countMatches (int arr[], int sorted[], int size);

int findInList (int arr[], int sorted[], int size, int target, int* nFound, int* index);

/* MAIN-------------------------------------------------------------------*/

int main (int argc, char** argv) 
{
 int val;
 int *list;
 int size = 100;
 list = (int *) malloc (size * sizeof(int) );

 /* prompt the user for input */
 printf ("Enter in a list of numbers to be stored in a dynamic array.\n");
 printf ("End the list with the terminal value of -999\n");
 
 /* loop until the user enters -999 */
 scanf ("%d", &val);

 int i = 0; // to keep track of array indices and # of elements in the array
 while (val != -999)
 {
  /* store the value into an array, growing array if needed. */
  list[i] = val;
  i = i + 1;

  /* if the number of elements in the array reach the amount of memory allocated,
   * double the size of the array */
  if ( (i+1) == size ) 
  {
   int *temp = list;
   list = (int * ) malloc (size * 2 * sizeof(int) );
   int j; 
   for ( j = 0; j < size; j++) 
	   list[j] = temp[j];
   free(temp);
   size = size * 2;
  } 

  /* get next value */
  scanf("%d", &val);
 }

 size = i; // size is now the # of elements in list

 /* Make a copy of the array of values to sort. */
 int sorted[size]; // size of this new array is the number of elements in the original list
 copyArray( list, sorted, size);

 /* Sort the copied array. */
 myFavoriteSort( sorted, size );

 /* Call function to count matches, and report results. */
 int matches = countMatches( list, sorted, size );
 double percentage = ( (double)matches / (double)size ) * 100;
 printf("\nNumber already in sorted order = %d / %d = %.1f%%	\n", matches, size, percentage);

 /* loop until the user enters -999 */
 printf ("\nEnter in a list of numbers to use for searching.  \n");
 printf ("End the list with a terminal value of -999\n");
 scanf ("%d", &val);


 printf ("\nSearch Results: (Position begins at 0)\n");
 
 int numFound, index;
 int* nFound = &numFound, *iptr = &index;

 while (val != -999)
   {
    /* call function to perform target search operation */
    int result = findInList( list, sorted, size, val, nFound, iptr );

    /* print out info about the target search results. 
     * if the result is 0 or -1, the position will be -1 since there is no position where the target is 
     * present in the sorted list and matches the element in the same position in the unsorted list */
    if (result == 1)
	    printf ("\nTarget = %d, Yes, in order! Appearances: %d, Position: %d", val, numFound, index);
    else if (result == 0)
	    printf ("\nTarget = %d, No, present but out of order! Appearances: %d, Position: -1", val, numFound);
    else if (result == -1)
	    printf ("\nTarget = %d, Not even in the list! Appearances: 0, Position: -1", val);

    /* get next value */
    scanf("%d", &val);
   }

 printf ("\n\nGood bye\n");

 free(list); //free the allocated memory at the end of the program.
 return 0;
}


/* FUNCTION DEFINITIONS */

/* Copy the elements from fromArray to toArray */
void copyArray ( int fromArray[], int toArray[], int size) {
	int i;
	for (i = 0; i < size; i++){
		toArray[i] = fromArray[i];
	}
}

/* Sort the elements in arr in ascending order (bubble sort) */
void myFavoriteSort ( int arr[], int size)
{
 int i, j, temp;
 for ( i = 0; i < size; i++ )
 {
  for ( j = 0; j < size-i-1; j++)
  {
   if ( arr[j] > arr[j+1] )
   {
    temp = arr[j];
    arr[j] = arr[j+1];
    arr[j+1] = temp;
   }
  }
 }
}

/* Count the number of pairs where matching elements are in the same indices of arr and sorted */
int countMatches (int arr[], int sorted[], int size) 
{
 int* lPtr = arr;
 int* sPtr = sorted;
 int i, total = 0;

 for ( i = 0; i < size; i++)
 {
  if ( *lPtr == *sPtr )
	  total++;
  lPtr++;
  sPtr++;
 }

 return total;
}


/* Search the lists for the target:
 * Return 1 if the target is in the list and in the correct position
 * Return 0 if the target is in the list but in an incorrect position
 * Return -1 if the target is not in the list
 * Count number of occurrences of the target in the list
 * Set index to the first location where the target matches in the sorted and unsorted lists
 */
int findInList (int arr[], int sorted[], int size, int target, int* nFound, int* index) 
{
 int* lPtr = arr, *sPtr = sorted;
 int* lEnd = lPtr + size;
 int* sEnd = sPtr + size;
 int result = -1;
 int i;
 *nFound = 0; // reset nFound count to 0 for every new target

 /* Search list backwards so that the correct index is returned */
 for ( i = size-1; i >= 0; i-- )
 {
  /* If target is in the sorted list */
  if ( target == *sEnd ) 
  { 
   (*nFound)++;
   if (result != 1)
	   result = 0;

   /* If target is in the sorted list and matches the unsorted list */
   if ( *sEnd == *lEnd ) 
   {
    *index = i+1;
    result = 1;
   }
  }

  lEnd--;
  sEnd--;
  }

  if ( (target == *lPtr) && (*lPtr == *sPtr) )
	  result = 1;

 return result;
 
}


