//Shared functions:

//Cellular automaton related stuff:
void update(char*, unsigned int, unsigned char);
char* resizeCells(int, char*, int);
//Option related stuff:
unsigned char parseOpts(int,char**);
//Exit ncurses safely:
void die(int);
