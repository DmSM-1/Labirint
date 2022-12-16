#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>

#define MAX(a,b) (a>b)?a:b
#define init(ch,a,h) lab[(h-1)*W+i]=ch
#define inLab(a,b) (a<W && a>=0 && b<H && b>=0)
#define abs(a,b) ((a>b)?a-b:b-a)
#define metrixG 100
#define metrixD 144
#define trueWay(a,b) (lab[Yf*W+Xf]-lab[(Yf+(b))*W+Xf+(a)]==metrixG || (lab[Yf*W+Xf]-lab[(Yf+(b))*W+Xf+(a)])==metrixD)
#define TIME 0
#define DEBUG

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
int len=0;
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
        for (int j = 0; j<W;j++){
            ch = lab[W*i+j];
            switch (ch){
                case -1: putchar('#'); break;
                case -2: putchar('o'); break;
                case 1:  putchar('i'); break;
                case -5: putchar('*'); break;
                case 0: putchar(' '); break;
                #ifdef DEBUG
                default: putchar('.');  break;
                #else
                default: putchar(' ');  break;
                #endif
            }
        }
        printf("\n");
    }
    printf("\n");
}

int bypass(){
    int x,y;
    while(head){
        #ifdef DEBUG
        //system("clear");
        //printLab();
        //printQueue();
        usleep(TIME);
        #endif
        if (abs(x,Xf)<=1 && abs(y,Yf)<=1){
            Xf=x;
            Yf=y;
            len+=lab[W*y+x]+metrixG+(abs(x,Xf)*abs(y,Yf))*(metrixD-metrixG);
            break;
        }
        x = head->x;
        y = head->y;
        if (lab[W*y+x-1]==0 || (head->num+metrixG)<lab[W*y+x-1]){
            addQueue(x-1,y,head->num+metrixG);
            lab[W*y+x-1]=head->num+metrixG;
        }
        if (lab[W*y+x+1]==0 || (head->num+metrixG)<lab[W*y+x+1]){
            addQueue(x+1,y,head->num+metrixG);
            lab[W*y+x+1]=head->num+metrixG;
        }
        if (lab[W*(y-1)+x]==0 || (head->num+metrixG)<lab[W*(y-1)+x]){
            addQueue(x,y-1,head->num+metrixG);
            lab[W*(y-1)+x]=head->num+metrixG;
        }
        if (lab[W*(y+1)+x]==0 || (head->num+metrixG)<lab[W*(y+1)+x]){
            addQueue(x,y+1,head->num+metrixG);
            lab[W*(y+1)+x]=head->num+metrixG;
        }
        if (lab[W*(y+1)+x+1]==0 || (head->num+metrixD)<lab[W*(y+1)+x+1]){
            addQueue(x+1,y+1,head->num+metrixD);
            lab[W*(y+1)+x+1]=head->num+metrixD;
        }
        if (lab[W*(y-1)+x+1]==0 || (head->num+metrixD)<lab[W*(y-1)+x+1]){
            addQueue(x+1,y-1,head->num+metrixD);
            lab[W*(y-1)+x+1]=head->num+metrixD;
        }
        if (lab[W*(y-1)+x-1]==0 || (head->num+metrixD)<lab[W*(y-1)+x-1]){
            addQueue(x-1,y-1,head->num+metrixD);
            lab[W*(y-1)+x-1]=head->num+metrixD;
        }
        if (lab[W*(y+1)+x-1]==0 || (head->num+metrixD)<lab[W*(y+1)+x-1]){
            addQueue(x-1,y+1,head->num+metrixD);
            lab[W*(y+1)+x-1]=head->num+metrixD;
        }
        remQueue();
    }
}

int way(){
    if ((abs(Xf,Xs)+abs(Yf,Ys))==0) return 0;
    
    int x=0,y=0;
    if(trueWay(-1,-1)){ 
        x=Xf-1; y=Yf-1;
    }else if(trueWay(1,-1)){ 
        x=Xf+1; y=Yf-1;
    }else if(trueWay(-1,1)){ 
        x=Xf-1; y=Yf+1;
    }else if(trueWay(1,1)){ 
        x=Xf+1; y=Yf+1;
    }else if(trueWay(1,0)){ 
        x=Xf+1; y=Yf;
    }else if(trueWay(-1,0)){
        x=Xf-1; y=Yf;
    }else if(trueWay(0,1)){
        x=Xf; y=Yf+1;
    }else if(trueWay(0,-1)){
        x=Xf; y=Yf-1;
    }
    lab[Yf*W+Xf]=-5;
    Xf=x;
    Yf=y;

    #ifdef DEBUG
    //system("clear");
    //printLab();
    usleep(TIME);
    #endif

    way();
    
}

int main(int argc, char** argv){
    FILE* input = fopen(argv[1], "r");
    readLab(input);
    fclose(input);

    bypass();
    way();

    system("clear");
    printLab();
    printf("Lenght: %d\n", len-1);
    free(lab);
    return 0;
}
