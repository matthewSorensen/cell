#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define VERSION "0.9"

int message(int level,char* name){
  printf("Cell, a divertimento in C.\nV.%s, 2011 Matthew Sorensen\n", VERSION);
  if(level > 1){
    printf("usage: %s [-hv] [-r rule]\n",name);
    puts("Up/down arrow keys (or i/k) control speed, q (or ctrl-c) exits.\n\
Rules 30, 90, 110, and 165 are particularly interesting...");
  }
  exit(0);
}

unsigned char parseOpts(int count, char** args){
  unsigned char rule = 90; //Defaults to a nice pretty triangle.
  int c, hv = 0;
  while((c = getopt(count, args, "hvr:")) != -1)
    switch (c){
    case 'h':
      hv |= 2;
      break;
    case 'v':
      hv |= 1;
      break;
    case 'r':
      rule = (unsigned char) atoi(optarg);
    }
  if(hv)
    message(hv, *args);
  return rule;
}
