#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
//N = number of people
//L = min number of people so that a person goes in
//H = highest number of people so that a person goes in

unsigned long long people[100000][2];

void printPeopleArray(unsigned long n)
{
    int i;
    for(i=0; i<n ;i++){
        printf("%llu %llu \n",people[i][0],people[i][1]);
    }
}

void fillPeopleChoices(unsigned long n){
    int i;
    for(i=0; i<n ;i++){
        scanf("%llu %llu",&people[i][0],&people[i][1]);
    }
}
int main() {
    unsigned long n,l,h;

    //printf("Max is %lu \n",getMaxNumberOfPeople(6));
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    scanf("%lu",&n);

    fillPeopleChoices(n);

    printPeopleArray(n);
    return 0;
}
