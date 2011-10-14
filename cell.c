#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <ncurses.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include "cell.h"


int resizePending = FALSE;
unsigned int delay = 125; //Number of 4000 microsecond intervals to delay between lines
char* cells = NULL;
int col = 0;
int row = 0;
unsigned char rule = 90;

void die(int _ ){
  endwin();//Make sure to restore the terminal's state.
  exit(0);
}

void resize(int _ ){
  resizePending = TRUE;
}

void initScreen(void);
//The function can safefully be called when nothing is initialized...
void printOrResize(int line){
  if(resizePending == TRUE){
    initScreen();
  }else{
    mvaddstr(line, 0, cells);
  }
}

void initScreen(){
  struct winsize size;
  int i;
  //Get the terminal dimensions:
  if(ioctl(0,TIOCGWINSZ, &size) == -1){
    die(0);//Can't do anything about it
   }
  //Reallocate (or perhaps not...) cells
  cells = resizeCells(size.ws_col, cells, col);
  col = size.ws_col;
  row = size.ws_row;
  //And off we go!
  resizePending = FALSE;
  //Clear the screen, and repaint
  wclear(stdscr);
  for(i=1;i<row-2; i++){
    printOrResize(i);
    update(cells, col, rule);
  }
  refresh();
}


void handleInput(){
  int ch = getch();
  while(ch != ERR){
    switch(ch){
    case 'k':
    case KEY_DOWN:
      delay++;
    break;
    case 'i':
    case KEY_UP:
      if(delay > 5)
        delay--;
    break;
    case 'q':
      die(0);
    }
    ch = getch();
  }
}


int main(int c,char** args){
  rule = parseOpts(c, args);
  signal(SIGINT,die);
  signal(SIGHUP,die);
  signal(SIGWINCH,resize);
  //Setup ncurses
  initscr();
  curs_set(0);
  noecho();
  scrollok(stdscr,TRUE); 
  keypad(stdscr, TRUE);
  timeout(0);
  //Start drawing
  initScreen();
  while(1){
    unsigned int iter = 0;
    while(iter++ < delay){
      usleep(4000);
      handleInput();
    }
    printOrResize(row-2);
    scroll(stdscr);
    refresh();
    update(cells, col, rule);
  }
  //Any exit is abortive, and mostly likely SIGINT - handled already...
  return 0;
}
