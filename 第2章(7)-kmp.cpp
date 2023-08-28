int *getNext(char *str)
{
    int len=strlen(str);
    int *next[]=(int *)calloc(len,sizeof(int));
    next[0]=-1;
    next[1]=0;
    int i=2; //主串指针
    int k=0; //回溯位置
    while( i < len ){
        if( k==-1 || str[i-1]==str[k] ){    //这里有多种写法
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
