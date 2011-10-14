char p,q,r,w[151];

int main(int c,char**v){
short int i=151;
r=2^c?0:atoi(v[1]);
while(--i>0)
  w[i]=i==75;
 while(i++<40){
   for(p=c=0;c<150;){
     q=w[c];
     w[c]=r&(p?240:15)&(w[c]?204:51)&(w[++c]?170:85);
     putchar((p=q)?35:32);
   }
   puts("");
 }
}
