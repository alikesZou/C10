int *getNext(char *str)
{
    int len=strlen(str);
    int *next[]=(int *)calloc(len,sizeof(int));
    next[0]=-1;
    next[1]=0;
    int i=2; //����ָ��
    int k=0; //����λ��
    while( i < len ){
        if( k==-1 || str[i-1]==str[k] ){    //�����ж���д��
            next[i]=k+1;   
            i++;
            k++;
        }
        else{
            k=next[k]; 
        }
    }
    return next;
}
