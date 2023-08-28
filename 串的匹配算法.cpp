#include<stdio.h>
#include<string.h>
#include<stdlib.h>
//�������Ͷ��壺˳�� & ���� 
#define MAXLEN 255
//˳�� 
typedef struct SString{
	char ch[MAXLEN+1];//��һ���1��ʼ����������������ܳ�Ҫ��һλ
	int length; 
}SString; 

//���� 
//����� 
#define CHUNKSIZE 80 //��Ĵ�С�����û����壨һ�������Ŷ��ٸ��ַ� 
typedef struct Chunk{   
	char ch[CHUNKSIZE];
	struct Chunk*next;
}Chunk;
typedef struct LString{
	Chunk *head,*tail;//����ͷָ���βָ�룬�ֱ�ָ�򴮵�ͷ��β 
	int curlen;//����ǰ�ĳ��� 
}LString;


//����ƥ�䣺BF�㷨 & KMP�㷨
//BF�㷨(posΪ��ʼ���ҵ���㣬��S��)
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

//KMP�㷨��posΪ��ʼ���ҵ���㣬��S�ϣ�
//������nextval[j]�ķ���
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
 
	while ( i < len-1) { //����ע��-1
 
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
 

 
