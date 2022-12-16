#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAX(a,b) (a>b)?a:b
#define init(ch,a,h) lab[(h-1)*W+i]=ch
#define inLab(a,b) (a<W && a>=0 && b<H && b>=0)
#define abs(a,b) ((a>b)?a-b:b-a)

typedef struct _Queue{
    int num;
    int x;
    int y;
    struct _Queue* next;
}Queue;

int* lab  = NULL;
int Xf, Yf;
int Xs, Ys;
int H, W;
int x,y;
Queue* head;
Queue* tail;

int addQueue(int x, int y,int a){
    tail->next=malloc(sizeof(Queue));
    tail=tail->next;
    *tail= (Queue){a,x,y,NULL};
}

int remQueue(){
    if (head==tail){
        free(head);
        head=NULL;
        tail=NULL;
        return 0;
    }
    Queue* el = head;
    head=head->next;
    free(el);
    return 1;
}

int printQueue(){
    if (!head) return 0;
    Queue* el = head;
    while(el){
        printf("%d %d: %d\n",el->x, el->y, el->num);
        el=el->next;
    }
    printf("\n");
    return 1;
}

int readLab(FILE* input){
    char buf[1024];
    H=0;
    W=0;
    char ch;

    while(fgets(buf, 1024, input)!=0){
        W=MAX(W,strlen(buf));
        H++;
        lab=realloc(lab, W*H*sizeof(int));

        for (int i = 0; i<W;i++){
            ch = buf[i];
            switch (ch){
                case '#': init(-1,i,H); break;
                case ' ': init(0,i,H) ; break;
                case 'o': 
                    init(-2,i,H);
                    Xf = i;
                    Yf = H-1;
                    break;
                case 'i':
                    init(1,i,H);
                    head=malloc(sizeof(Queue));
                    Xs = i;
                    Ys = H-1;
                    tail=head;
                    *head= (Queue){1,i,H-1,NULL};
                    break;
                default: break;
            }
        }
    }
}

int printLab(){
    int ch = 0;
    for (int i = 0; i<H;i++){
        printf("%3d: ",i);
        for (int j = 0; j<W;j++){
            ch = lab[W*i+j];
            switch (ch){
                case -1: putchar('#'); break;
                case -2: putchar('o'); break;
                case 1:  putchar('i'); break;
                case -5: putchar('*'); break;
                default: putchar(' ');  break;
            }
        }
        printf("\n");
    }
    printf("\n");
}

int bypass(){
    int x,y;
    while(head){
        if ((abs(x,Xf)+abs(y,Yf))==1){
            Xf=x;
            Yf=y;
            break;
        }
        x = head->x;
        y = head->y;
        if (inLab(x-1,y)){
            if (lab[W*y+x-1]==0 || (head->num+1)<lab[W*y+x-1]){
                addQueue(x-1,y,head->num+1);
                lab[W*y+x-1]=head->num+1;
            }
         }
        if (inLab(x+1,y)){
            if (lab[W*y+x+1]==0 || (head->num+1)<lab[W*y+x+1]){
                addQueue(x+1,y,head->num+1);
                lab[W*y+x+1]=head->num+1;
            }
         }
        if (inLab(x,y-1)){
            if (lab[W*(y-1)+x]==0 || (head->num+1)<lab[W*(y-1)+x]){
                addQueue(x,y-1,head->num+1);
                lab[W*(y-1)+x]=head->num+1;
            }
         }
        if (inLab(x,y+1))
            if (lab[W*(y+1)+x]==0){
                addQueue(x,y+1,head->num+1);
                lab[W*(y+1)+x]=head->num+1;
            }
        remQueue();
    }
}

int way(){
    if ((abs(Xf,Xs)+abs(Yf,Ys))==0) return 0;
        
    int x=0,y=0;
    if (inLab(Xf+1,Yf) && !x)
        if((lab[Yf*W+Xf]-lab[Yf*W+Xf+1])==1){
            x=Xf+1;
            y=Yf;
        }
    if (inLab(Xf-1,Yf) && !x)
        if((lab[Yf*W+Xf]-lab[Yf*W+Xf-1])==1){
            x=Xf-1;
            y=Yf;
        }
    if (inLab(Xf,Yf+1) && !x)
        if((lab[Yf*W+Xf]-lab[(Yf+1)*W+Xf])==1){
            x=Xf;
            y=Yf+1;
        }
    if (inLab(Xf,Yf-1) && !x)
        if((lab[Yf*W+Xf]-lab[(Yf-1)*W+Xf])==1){
            x=Xf;
            y=Yf-1;
        }
    lab[Yf*W+Xf]=-5;
    Xf=x;
    Yf=y;
    way();
    
}

int main(){
    FILE* input = fopen("lab.txt", "r");
    readLab(input);
    fclose(input);

    bypass();
    printf("Lenght: %d\n", lab[Yf*W+Xf]);
    way();
    
    printLab();
    free(lab);
    return 0;
}
