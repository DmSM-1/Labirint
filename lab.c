#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAX(a,b) (a>b)?a:b
#define init(ch,a,h) lab[H*W+i]=ch
#define range(i,a,b) (int i = a; i<b; i++)

int* lab  = NULL;
int Xs, Ys;
int Xf, Yf;
int H, W;
int x,y;


int readLab(FILE* input){
    char buf[1024];
    H=0;
    W=0;
    char ch;
    while(fgets(buf, 1024, input)!=0){
        W=MAX(W,strlen(buf));
        H++;
        lab=realloc(lab, W*H*sizeof(int));
        //printf("eee\n");
        for range(i, 0 , W){
            ch = buf[i];
            putchar(ch);
            //printf("%d %c\n", ch, ch);
            //switch (ch){
                //case '#': init(1,i,H); break;
                //case ' ': init(0,i,H); break;
                //case 'i': init(2,i,H); Xs = i; Ys = H; break;
                //case 'o': init(3,i,H); Xf = i; Yf = H; break;
                //default: break;
            //}
        }
    }
}

int printLab(){
    for range(i,0,H){
        for range(j,0,W){
            printf("%d",lab[W*i+j]);
        }
        printf("\n");
    }
}

int main(){
    FILE* input = fopen("lab.txt", "r");
    readLab(input);
    printf("eee\n");
    free(lab);
    return 0;
}