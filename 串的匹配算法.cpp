#include<stdio.h>
#include<string.h>
#include<stdlib.h>
//串的类型定义：顺序串 & 链串 
#define MAXLEN 255
//顺序串 
typedef struct SString{
	char ch[MAXLEN+1];//串一般从1开始计数，所以数组的总长要大一位
	int length; 
}SString; 

//链串 
//定义块 
#define CHUNKSIZE 80 //块的大小可由用户定义（一个结点里放多少个字符 
typedef struct Chunk{   
	char ch[CHUNKSIZE];
	struct Chunk*next;
}Chunk;
typedef struct LString{
	Chunk *head,*tail;//串的头指针和尾指针，分别指向串的头和尾 
	int curlen;//串当前的长度 
}LString;


//串的匹配：BF算法 & KMP算法
//BF算法(pos为开始查找的起点，在S上)
int Index_BF(SString S,SString T,int pos){
	int i = pos,j = 1;
	while(i <= S.length && j <= T.length){
		if(S.ch[i] == T.ch[j]){
			++i;
			++j;
		}else{
			i = i - j + 2;
			j = 1;
		}
	}
	if(j >= T.length)return i-T.length;
	else return -1; 
}

//KMP算法（pos为开始查找的起点，在S上）
//其中找nextval[j]的方法
//void get_nextval(SString T,int nextval[]){
//	int i = 1;
//	nextval[1] = 0;
//	int j = 0;
//	while(i < T.length){
//		if(j == 0 || T.ch[i] == T.ch[j]){
//			++i;++j;
//			if(T.ch[i] != T.ch[j]) nextval[i] = j;
//			else nextval[i] = nextval[j];
//		}
//		else j = nextval[j];
//	}
//} 
int* getNext(char *str)
{
	int len = strlen(str);
	int* next = (int*)calloc(len, sizeof(int));
	next[0] = -1;
	int i = 0, k = -1;
 
	while ( i < len-1) { //这里注意-1
 
		if (k==-1||str[i]==str[k]) {
			i++;
			k++;
			next[i] = (str[i] == str[k] ? next[k] : k);
		}
		else {
			k = next[k];
		}
	}
 
	return next;
}


int Index_KMP(SString S,SString T,int pos)
{
 
	int* next = getNext(T.ch);
	//int c_len = strlen(chang);
	//int d_len = strlen(duan);
	int i = pos-1, k = 0;
 
	while (i<S.length && k<T.length) {
 
		if (k == -1 || S.ch[i] == T.ch[k]) {
			i++;
			k++;
		}
		else {
			k = next[k];
		}
	}
 
	return k < T.length ? -1 : i - k + 1;
}
int main(){
	SString S = {"aaaaabaabcac",12};
	SString T = {"abaabcac",8};
	printf("%d\n",Index_BF(S,T,6));
	printf("%d\n",Index_KMP(S,T,6));
	
}
 

 
