#include <iostream>
#include "Structs.h"
#define InitSize 10

void InitSqlist(Sqlist&L){
    L.data =new int[InitSize];
    L.length=0;
    L.MaxSize=InitSize;
}
void IncreaseSize(Sqlist&L,int l){
    int *p=L.data;
    L.data = new int[InitSize+l];
    for(int i=0;i<InitSize+l;i++)
        L.data[i]=p[i];
    delete[] p;
}
int main(){


}
