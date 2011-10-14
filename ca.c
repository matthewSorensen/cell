#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include "cell.h"

// On/Off may be anything, but the following conditions must hold:
//     ON & 4 == 4 ; and
//     OFF & 4 == 0
#define ON '&'
#define OFF ' '

//Calculate the next generation.
void update(char* cells, unsigned int length, unsigned char rule){
  char new = *cells;
  length -= 2; //Don't update the first and last cells.
  while(length -- > 0){//Due to the pun, this only works on little-endian machines... 
    unsigned int bits = *(unsigned int*) cells;
    bits &= 0x00040404; //We only want the third bit of the first three chars.
    bits |= (bits >> 9) | (bits >> 18);//Bit 3 stays in place, 11 becomes 2, 19 goes to 1.
    bits &= 0x07; //Take the bits 3, 2, and 1.
    *cells++ = new; //Update cells with the result of the previous iteration.
    new = (1 << bits) & rule ? ON : OFF;
  }
}

char* resizeCells (int newS, char* cells, int oldS){
  char* nCells;
  //If the old buffer won't work (ie. there isn't one, or it's too small) malloc a new one.
  if((cells == NULL) || newS > oldS){
    if(!( nCells = malloc(sizeof(char)*(newS + 1)))){
      printf("Malloc failed - this really shouldn't happen...");
      die(1);
    }
    if(cells == NULL){
      memset(nCells, OFF, newS); //Initialize with empty cells
      nCells[newS >> 1] = ON; //Provide the initial impuse
    }else{ //As it's strictly bigger, tile nCells with copies of cells
      int unfilled = newS;
      while(unfilled > 0){
        int step = oldS <= unfilled ? oldS : unfilled;
        memcpy(nCells + (newS - unfilled), cells, step);
        unfilled -= step;
      }
      free(cells); 
    }
  }else{
    nCells = cells; //Otherwise we can use the old one, but we have to null-terminate it
  }
  nCells[newS] = 0; //Null terminate at the new size.
 
  return nCells;
} 
