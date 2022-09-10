#include <iostream>
#include<stdio.h>
#include<stdlib.h>
#include<sys/malloc.h>
#include<math.h>
#include<ctime>
#include<cstdlib>
using namespace std;

#define OK 1;
#define ERROR 0;
#define LIST_INIT_SIZE 0 // 线性表存储空间的初始分配量
#define LISTINCREMENT 1 // 线性表存储空间的分配增量
#define LENGTH_ERROR 0 // 插入位置错误
#define MIN_NUMBER 1 // 随机数最小值
#define MAX_NUMBER 50 // 随机数最大值

typedef struct {
    int *elem; // 空间基址
    int length; // 当前长度
    int listsize; // 空间大小(单位sizeof(int))
}Sqlist;

int InsertList(Sqlist &L , int i , int e){
    // 在线性表的第i个位置前插入一个新元素e
    if(i < 1 || i > L.length + 1) return ERROR;

    if(L.length >= L.listsize) {
        L.elem = (int *)realloc(L.elem,(L.listsize + LISTINCREMENT) * sizeof(int)); // 重新分配存储空间
        L.listsize += LISTINCREMENT;
    }

    int *tmp_1 = &(L.elem[i - 1]); // 元素插入位置
    for(int *tmp_2 = &(L.elem[L.length - 1]); tmp_2 >= tmp_1; --tmp_2){ // 插入位置后的元素依次右移
        *(tmp_2 + 1) = *tmp_2; 
    }
    *tmp_1 = e; // 插入元素
    ++L.length; // 长度加一

    return OK;
} // InsertList

int InitList(Sqlist &L){
    // 初始化线性表
    L.elem = (int *)malloc(LIST_INIT_SIZE * sizeof(int)); // 分配存储空间
    L.length = 0;
    L.listsize = LIST_INIT_SIZE;

    return OK;
} // InitList

void CreateList(Sqlist &L){

    InitList(L);

    cout << "已创建线性表." << endl
         << "线性表存储空间: " << L.listsize << endl 
         << "线性表目前长度: " << L.length << endl;

    int num_Elem;
    cout << endl << "请指定线性表长度:";
    cin >> num_Elem;

    for(int i = 0;i <= num_Elem;i++){
        //  cout << endl 
        //       << "线性表存储空间: " << L.listsize << endl 
        //       << "线性表目前长度: " << L.length << endl;
        srand(time(nullptr));
        int randnum = (rand() % (MAX_NUMBER - MIN_NUMBER + 1)) + MIN_NUMBER;

        if(i == 0){
            InsertList(L,i,randnum);
        }
        else{
            bool flag = true;
            do{   
                randnum = (rand() % (MAX_NUMBER - MIN_NUMBER + 1)) + MIN_NUMBER;
                int n = 0;
                for(int k = i - 1;k >= 0;k--){
                    if(randnum != L.elem[k]){
                        n++;
                    }
                }
                if(n == i){
                    flag = false;
                }
            }while(flag);
            InsertList(L,i,randnum);
        }
        
    }

    cout << endl
         << "已初始化线性表." << endl
         << "线性表存储空间: " << L.listsize << endl 
         << "线性表目前长度: " << L.length << endl;

}
void Sort(Sqlist &L){
    for (int i = 0; i < L.listsize - 1; i++){
        for (int j = 0; j < L.listsize - 1 - i; j++){
            if (L.elem[j] > L.elem[j + 1]){
                int temp = L.elem[j];
                L.elem[j] = L.elem[j + 1];
                L.elem[j + 1] = temp;
            }
        }
    }           
}

void PrintList(Sqlist &L){
    for(int i = 0;i < L.listsize;i++){
        cout << i+1 << ". " << L.elem[i] << endl;
    }
    cout << endl;
}

int GetMax(Sqlist &L){
    Sort(L);
    return L.elem[L.listsize-1];
}

int main(){

    Sqlist L;
    CreateList(L);
    cout << endl << "排序前:" << endl;
    PrintList(L);
    
    Sort(L);

    cout << endl << "排序后:" << endl;
    PrintList(L);

    cout << "最大值为:" << GetMax(L) << endl;
    return 0;
}