#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int getSizeAfterCycles(int cycles){
    int size=1, i;

    for (i=0; i < cycles;i++){
        if( (i % 2) == 0){
            size = 2*size;
        }
        else{
            size += 1;
        }
    }

    return size;
}

int main() {

    /* Enter your code here. Read input from STDIN. Print output to STDOUT */    
    int tests,i,n,result;
    scanf("%d",&tests);
    for ( i = 0;i < tests; i++ ) {
        scanf("%d",&n);
        result = getSizeAfterCycles(n);
        printf("%d\n",result);
    }
    return 0;
}
