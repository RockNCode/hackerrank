#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define ISNOTVALID 0
#define ISVALID 1

int solnx1[80];
int solny1[80];
int solnx2[80];
int solny2[80];

int checkValid(int sudoku[][9]){
    int i =0;
    int j=0;
    int k=0;

    for(i=0; i<9 ;i++){
        for(j=0;j<9;j++){
            //check horizontally
            for(k = j + 1; k < 9; k++){
                if(sudoku[i][j] == sudoku[i][k])
                    return ISNOTVALID;
            }
            //check vertically
            for(k = j + 1; k < 9; k++){
                if(sudoku[j][i] == sudoku[k][i])
                    return ISNOTVALID;
            }
            //check squares
            int posx=i;
            int posy=j;
            int l,m;
            int xLimit= posx-posx%3+3, yLimit=posy-posy%3+3;
            for(l=posx-posx%3 ; l < xLimit; l++){ //l=i
                for(m=posy-posy%3;m < yLimit;m++){//m=j
                    if(sudoku[l][m] == sudoku[i][j] && !(l == posx && m == posy)){
                        return ISNOTVALID;
                    }
                }
            }
        }
    }

    return ISVALID;
}

void printGrid(int sudoku[][9]){
    int i = 0 ,j = 0;
    for(i=0;i<9;i++){
        if(i%3 ==0 ){
            printf("+-------------------------------+-------------------------------+--------------------------------\n");
        }
        for(j=0;j<9;j++){
            if(j==0 || j==3 ||j==6){
                printf("|\t");
            }
            if(sudoku[i][j] != 0 ){
                printf(" %d\t",sudoku[i][j]);
            }else{
                printf(" \t");
            }
            if(j==8){
                printf("|");
            }
            if(j==8){
                printf("\n");
            }
        }
    }
    printf("+-------------------------------+-------------------------------+--------------------------------\n");
}

void fillSudokuInput(int sudoku[][9])
{
    int i;
    for(i=0; i<9 ;i++){
        scanf("%d %d %d %d %d %d %d %d %d",
              &sudoku[i][0],&sudoku[i][1],
              &sudoku[i][2],&sudoku[i][3],
              &sudoku[i][4],&sudoku[i][5],
              &sudoku[i][6],&sudoku[i][7],
              &sudoku[i][8]);

    }

}

int compareAll(int sudoku[][9],int i, int j,
               int *x1, int *y1,int *x2, int *y2){
    int k,l;
    int temp;
    int soln=0;
    for(k=i; k<9 ;k++){
        for(l=0;l<9;l++){
            if( !(k == i && l <= j) )
            {
                temp = sudoku[k][l];
                sudoku[k][l] = sudoku[i][j];
                sudoku[i][j] = temp;
                if(checkValid(sudoku)){
                    if( (i < k) ||
                        ( (i == k) && (j < l ))
                        ){
                        *x1 = i+1;
                        *y1 = j+1;

                        *x2 = k+1;
                        *y2 = l+1;
                    }else{
                        *x2 = i+1;
                        *y2 = j+1;

                        *x1 = k+1;
                        *y1 = l+1;                        
                    }
                    //swap back
                    temp = sudoku[k][l];
                    sudoku[k][l] = sudoku[i][j];
                    sudoku[i][j] = temp;
                    return 1;
                }
                else{
                    //swap back
                    temp = sudoku[k][l];
                    sudoku[k][l] = sudoku[i][j];
                    sudoku[i][j] = temp;
                }
            }
        }
    }
    return 0;
}
int checkSwap(int sudoku[][9],
               int *x1,int *y1,
               int *x2,int *y2){
    int i =0;
    int j =0;
    int k =0;
    int l =0;
    int soln=0;
    for(i=0; i<9 ;i++){
        for(j=0;j<9;j++){
            if(compareAll(sudoku,i,j,x1,y1,x2,y2)){
                solnx1[soln] = *x1;
                solnx2[soln] = *x2;
                solny1[soln] = *y1;
                solny2[soln] = *y2;
                soln++;
            }
        }
    }
    return soln;
}
int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int i,t=1;
    int soln=0;
    int mySudoku[9][9]={{0,7,8,0,0,0,0,2,0},
                        {0,0,0,0,0,2,0,0,3},
                        {4,0,0,0,0,0,0,7,0},
                        {0,0,5,3,0,0,7,0,0},
                        {0,6,0,9,0,8,0,0,0},
                        {9,0,0,0,7,0,6,3,0},
                        {0,9,0,5,0,0,0,0,2},
                        {2,4,0,8,0,6,0,0,0},
                        {0,5,1,4,2,7,0,9,6},
    };

    scanf("%d",&t);

    for(i = 0; i < t; i++ ){
        fillSudokuInput(mySudoku);
        //printGrid(mySudoku);
        printf("Case #%d:\n",i+1);
        if( checkValid(mySudoku) )
            printf("Serendipity\n");
        else{
            //printf("is not valid\n");
            int x1=-1,y1=-1;
            int x2=-1,y2=-1;
            int j;
            soln = checkSwap(mySudoku,&x1,&y1,&x2,&y2);
            for(j=0; j < soln; j++)
                printf("(%d,%d) <-> (%d,%d)\n",solnx1[j],solny1[j],solnx2[j],solny2[j]);
            soln=0;
        }

    }
    return 0;
}
