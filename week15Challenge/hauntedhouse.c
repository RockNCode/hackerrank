#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#define STATE_H 0
#define STATE_L 1

//N = number of people
//L = min number of people so that a person goes in
//H = highest number of people so that a person goes in

unsigned long long people[1000000][3];
unsigned long long peopleSorted[1000000][2];
unsigned long long maxH =0;
unsigned long long maxL =0;
unsigned long long minH =0;
unsigned long long minL =0;

void printPeopleArray(unsigned long n)
{
    int i;
    for(i=0; i<n ;i++){
        printf("%llu %llu \n",people[i][0],people[i][1]);
    }
}

void fillPeopleChoices(unsigned long n){
    unsigned long i;
    for(i=0; i<n ;i++){
        scanf("%llu %llu",&people[i][0],&people[i][1]);
        if(i == 0){
            minL = people[i][0];
            minH = people[i][1];
            maxL = people[i][0];
            minH = people[i][1];
        }else{
            if(people[i][0]  > maxL)
                maxL = people[i][0];
            if(people[i][1]  > maxH)
                maxH = people[i][1];
            if(people[i][0]  < minL)
                minL = people[i][0];
            if(people[i][1]  < minH)
                minH = people[i][1];
        }
        people[i][2] = people[i][1] - people[i][0];
    }
    /*printf("minL = %d minH = %d maxL = %d maxH = %d \n",
      minL, minH, maxL, maxH);*/

}

void sortByGap(unsigned long n){
    unsigned long long tempH,tempL,tempGap;
    unsigned long i,j;
    for(i = 0; i < n ;i++){
        for(j = 0 ; j < n ;j++){
            if(people[j][2] < people[j+1][2]){
                tempL = people[j+1][0];
                tempH = people[j+1][1];
                tempGap = people[j+1][2];

                people[j+1][0] = people[j][0];
                people[j+1][1] = people[j][1];
                people[j+1][2] = people[j][2];

                people[j][0] = tempL;
                people[j][1] = tempH;
                people[j][2] = tempGap;
            }
        }
    }
}

void printPeopleTable(unsigned long n){
    int i,j;
    for(i=0; i<n ;i++){
        printf(" %llu %llu %llu \n",
               people[i][0],
               people[i][1],
               people[i][2]
            );
    }
}

void sortByL(unsigned long *start_n,unsigned long n){
    unsigned long i,j;
    unsigned long long tempH,tempL,tempGap;
    unsigned long long valueH = people[*start_n][0];
    //printf("at sort by l start_n = %lu\n",*start_n);
    for(i = *start_n; i < n ;i++){
        for(j = *start_n ; j < n ;j++){
            //printf("at sortByL\n");
            if(people[j][2]!= valueH){
                *start_n =i;
                break;
            }
            if(people[j][0] < people[j+1][0]){
                tempL = people[j+1][0];
                tempH = people[j+1][1];
                tempGap = people[j+1][2];

                people[j+1][0] = people[j][0];
                people[j+1][1] = people[j][1];
                people[j+1][2] = people[j][2];

                people[j][0] = tempL;
                people[j][1] = tempH;
                people[j][2] = tempGap;
            }
        }
    }
    *start_n=i;
}

unsigned long long getMaximumOutput(unsigned long n){
    unsigned long long max =maxH;
    //max < n
    //max < max h
    unsigned long i=0;
    unsigned long long max_h=0;
    unsigned long long max_l=0;
    int state = STATE_H;
    while( i < max ){
        if(people[i][0]  > maxL)
            maxL = people[i][0];
        if(people[i][1]  > maxH)
            maxH = people[i][1];
        if(people[i][0]  < minL)
            minL = people[i][0];
        if(people[i][1]  < minH)
            minH = people[i][1];

        if(people[i][1] <= max ){ //checking H
            i=0;
            max--;
            maxL=0;
            continue;
        }
        i++;
    }
    i=0;
    //printf("maxL = %llu max total=%llu \n",maxL,max+1);
    if(maxL >= max+1)
        return 0;
    while( i < max ){
        if(people[i][0]  > maxL)
            maxL = people[i][0];
        if(people[i][1]  > maxH)
            maxH = people[i][1];
        if(people[i][0]  < minL)
            minL = people[i][0];
        if(people[i][1]  < minH)
            minH = people[i][1];

        if( people[i][0] > max )
            max--;
        i++;
    }

    return max;
}

int main() {
    unsigned long start_n=0,n,l,h;
    unsigned long long max =0;
    //printf("Max is %lu \n",getMaxNumberOfPeople(6));
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    scanf("%lu",&n);

    fillPeopleChoices(n);
    sortByGap(n);
    while(start_n<n){
        sortByL(&start_n,n);
    }
    //printPeopleTable(n);
    max = getMaximumOutput(n);
    if(max>0)
        printf("%llu\n",max+1);
    else
        printf("%llu\n",max);

    //printPeopleArray(n);
    return 0;
}
