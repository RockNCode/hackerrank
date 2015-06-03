#include <stdio.h>
#include <string.h>

unsigned int absol(int num)
{
    return num < 0 ? -num:num; 
}

int isFunny(char str[]){
    int len = strlen(str)-1;
    char *start = str;
    char *end = str+len;

    while(*(start+1) != '\0'){
        //printf("start = %c end = %c ",*start,*end);
        if( absol ( *(start+1) - *start) !=
            absol( *end - *(end-1))){
            return 0;
        }

        start++;
        end--;
    }

    return 1;
}

int main()
{
    int tests,i,len,result;
    char str[10001];
    scanf("%d",&tests);

    for ( i = 0; i <= tests; i++ ) {
        fgets(str, 10001, stdin);
        len = strlen(str)-1;

        if( str[ len ] == '\n') 
            str[len] = '\0';

        if(i > 0){
            if(isFunny(str))
                printf("Funny\n");
            else
                printf("Not Funny\n");
        }
    }

}
