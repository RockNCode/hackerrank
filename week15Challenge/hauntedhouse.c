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
    unsigned long long valueGapIni = people[*start_n][0];
    //printf("at sort by l start_n = %lu\n",*start_n);
    for(i = *start_n; i < n ;i++){
        for(j = *start_n ; j < n ;j++){
            //printf("at sortByL\n");
            if(people[j][2] != valueGapIni){
                printf("valulegapini =%llu current =%llu \n",valueGapIni,people[j][2]);
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

void sortByH(unsigned long *start_n,unsigned long n){
    unsigned long i,j;
    unsigned long long tempH,tempL,tempGap;
    unsigned long long valueH = people[*start_n][1];
    //printf("at sort by l start_n = %lu\n",*start_n);
    for(i = *start_n; i < n ;i++){
        for(j = *start_n ; j < n ;j++){
            //printf("at sortByL\n");
            if(people[j][2] != valueH){
                *start_n =i;
                break;
            }
            if(people[j][1] < people[j+1][1]){
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

        if(people[i][1] <= max &&
           people[i][2] != 0){
            i=0;
            //printf("decreasing max H =%llu max=%llu \n",people[i][1] ,max);
            max--;
            //maxL=0;
            continue;
        }
        i++;
    }
    i=0;
    //printf("maxL = %llu max total=%llu \n",maxL,max);
    //if(maxL >= max+1)
    //    return 0;
    while( i < max ){
        if(people[i][0]  > maxL)
            maxL = people[i][0];
        if(people[i][1]  > maxH)
            maxH = people[i][1];
        if(people[i][0]  < minL)
            minL = people[i][0];
        if(people[i][1]  < minH)
            minH = people[i][1];

        if( people[i][0] > max ){//L
            max--;
        }
        i++;
    }

    return max;
}
unsigned long long getMaximumOutput2(unsigned long n)
{
    unsigned long long max = maxH+1;

    unsigned long long countPeople=0;
    unsigned int i =0;

restart :
    countPeople=0;
    i=0;
    while(i < n){
        /*printf("before check L = %llu H= %llu max -1 = %llu \n",
          people[i][0] , people[i][1] ,max - 1 );*/
        if(people[i][0] <= max - 1 && 
           people[i][1] >= max - 1){
            //printf("%u matches \n",i);
            countPeople++;
            if(countPeople == max)
                break;
        }
        i++;
    }
    //printf("before compare max = %llu countPeople = %llu \n",max,countPeople);
    if(max != countPeople){
        //printf("restarting max = %llu countPeople -%llu\n",max,countPeople);
        max--;
        goto restart;
    }
    return max-1;
}
int main() {
    unsigned long start_n=0,n,l,h;
    unsigned long long max =0;
    //printf("Max is %lu \n",getMaxNumberOfPeople(6));
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    scanf("%lu",&n);

    fillPeopleChoices(n);
    /*sortByGap(n);
    while(start_n<n){
        sortByL(&start_n,n);
    }
    printPeopleTable(n);
    start_n=0;
    while(start_n<n){
        sortByH(&start_n,n);
    }
    printf("=================\n");
    printPeopleTable(n);
    */
    max = getMaximumOutput2(n);
    if(max>0)
        printf("%llu\n",max+1);
    else
        printf("%llu\n",max);

    //printPeopleArray(n);
    return 0;
}
