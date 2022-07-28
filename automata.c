#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/**
 * This program simulates the evolution of a group of cells over a number of generations.
 * 
 * It must be run two arguments: the number of generations 
 * and a text file that contains a 5x5 matrix of integers 0 and 1.
 * ex. ./automata.c 5 input.txt
 * 
 * In the text file the 0s represent dead cells and the 1s are alive cells.
 * These are rules that dictate whether a cell lives or dies in each generation:
 * 1) A live cell with fewer than two neighbors dies.
 * 2) A live cell with more than three neighbors dies.
 * 3) A live cell with exactly two or three neighbors lives
 * 4) A dead cell with exactly three live neighbors becomes alive
 * 
 * After the cells have evolved through the given number of generations,
 * an output text file is generated that contains the final generation.
 * 
 * @author Joshua Forlenza
 *
 */

#define SIZE 5 

int createMatrix(int matrix[SIZE][SIZE], char* file){
    FILE *fp = fopen(file, "r");
    if (fp == NULL){
        printf("ERROR: File cannot be opened \n");
        exit(-1);
    }

    int i,j;
    char c;
    i = 0, j = 0;
    while((c = getc(fp)) != EOF){
        //skip over characters that aren't 0 or 1
        if (c==32 || c==10){
            continue;
        }
        if (j>4){
            i++;
            j = 0;
            
        }
        matrix[i][j] = c-'0';
        j++;
        
    }

    return 0;
}

int deadOrAlive(int matrix[SIZE][SIZE], int i, int j){
    int neighbors = 0;

    // for live cells
    if(matrix[i][j]==1){
        //first row
       if(i == 0){
           if(j == 0){
               neighbors = matrix[i][j+1] + matrix[i+1][j] + matrix[i+1][j+1];
               return(neighbors==2 || neighbors==3);
           }
           if(j == 4){
               neighbors = matrix[i][j-1]+matrix[i+1][j-1]+matrix[i+1][j];
               return(neighbors==2 || neighbors==3);
           }
           neighbors = matrix[i][j-1] + matrix[i+1][j-1] + matrix[i+1][j] + matrix[i+1][j+1] + matrix[i][j+1];
           if(neighbors==2 || neighbors==3){
               return 1;
           }
           else{
               return 0;
           }
       }
       //last row
       if(i == 4){
           if(j == 0){
               neighbors = matrix[i-1][j] + matrix[i-1][j+1] + matrix[i][j+1];
               return( neighbors==2 || neighbors==3);
           }
           if(j == 4){
               neighbors = matrix[i-1][j-1] + matrix[i-1][j] + matrix[i][j-1];
               return( neighbors==2 || neighbors==3);
           }
           neighbors = matrix[i][j-1] + matrix[i-1][j-1] + matrix[i-1][j] + matrix[i-1][j+1] + matrix[i][j+1];
           if(neighbors==2 || neighbors==3){
               return 1;
           }
           else{
               return 0;
           }
       }
       //first column
       if(j == 0){
           neighbors = matrix[i-1][j] + matrix[i-1][j+1] + matrix[i][j+1] + matrix[i+1][j+1] + matrix[i+1][j];
           if(neighbors==2 || neighbors==3){
               return 1;
           }
           else{
               return 0;
           }
       }
       //last column
       if(j == 4){
           neighbors = matrix[i-1][j] + matrix[i-1][j-1] + matrix[i][j-1] + matrix[i+1][j-1] + matrix[i+1][j];
           if(neighbors==2 || neighbors==3){
               return 1;
           }
           else{
               return 0;
           }
       }
       //check all neighbors if none of the previous conditions are true
       neighbors = matrix[i-1][j-1] + matrix[i-1][j] + matrix[i-1][j+1] + matrix[i][j-1]
        + matrix[i][j+1] + matrix[i+1][j-1] + matrix[i+1][j] + matrix[i+1][j+1];
       if(neighbors==2 || neighbors==3){
               return 1;
           }
           else{
               return 0;
           }
 
   }

    //for dead cells
    else{
        //first row
       if(i == 0){
           if(j == 0){
               neighbors = matrix[i][j+1] + matrix[i+1][j] + matrix[i+1][j+1];
               return(neighbors==3);
           }
           if(j == 4){
               neighbors = matrix[i][j-1]+matrix[i+1][j-1]+matrix[i+1][j];
               return(neighbors==2 || neighbors==3);
           }
           neighbors = matrix[i][j-1] + matrix[i+1][j-1] + matrix[i+1][j] + matrix[i+1][j+1] + matrix[i][j+1];
           return (neighbors == 3);
       }
       //last row
       if(i == 4){
           if(j == 0){
               neighbors = matrix[i-1][j] + matrix[i-1][j+1] + matrix[i][j+1];
               return(neighbors==3);
           }
           if(j == 4){
               neighbors = matrix[i-1][j-1] + matrix[i-1][j] + matrix[i][j-1];
               return(neighbors==3);
           }
           neighbors = matrix[i][j-1] + matrix[i-1][j-1] + matrix[i-1][j] + matrix[i-1][j+1] + matrix[i][j+1];
           return(neighbors==3);
       }
       //first column
       if(j == 0){
           neighbors = matrix[i-1][j] + matrix[i-1][j+1] + matrix[i][j+1] + matrix[i+1][j+1] + matrix[i+1][j];
           return(neighbors==3);
       }
       //last column
       if(j == 4){
           neighbors = matrix[i-1][j] + matrix[i-1][j-1] + matrix[i][j-1] + matrix[i+1][j-1] + matrix[i+1][j];
           return(neighbors==3);
       }
       //check all neighbors if none of the previous conditions are true
       neighbors = matrix[i-1][j-1] + matrix[i-1][j] + matrix[i-1][j+1] + matrix[i][j-1]
        + matrix[i][j+1] + matrix[i+1][j-1] + matrix[i+1][j] + matrix[i+1][j+1];
       return(neighbors==3);
   }


}

void evolution(int matrix[SIZE][SIZE], int newMatrix[SIZE][SIZE]){
    int i,j;
    // use newMatrix to store next generation
    for(i = 0; i<SIZE; i++){
        for (j = 0; j<SIZE; j++){
            newMatrix[i][j] = deadOrAlive(matrix, i, j);
        }
   }
   //update original matrix and restore newMatrix
   for(i = 0; i<SIZE; i++){
        for (j = 0; j<SIZE; j++){
            matrix[i][j] = newMatrix[i][j];
            newMatrix[i][j] = 0;
        }
   }

}


int main(int argc, char *argv[]){
    if (argc != 3){
        printf("Usage: ./automata N FILENAME");
        exit(-1);
    }

    int matrix[SIZE][SIZE];
    int generations = atoi(argv[1]);

    //read file and create matrix
    createMatrix(matrix, argv[2]);

    int i,j;
    int newMatrix[SIZE][SIZE];
    int a, b;
    //evolve matrix
    for(i = 0; i<generations; i++){
       evolution(matrix, newMatrix);
    }

    //return evolved matrix
    char output_file[1000];
    strcpy(output_file, argv[2]);
    strcpy(output_file + strlen(argv[2]), ".out");
    FILE *fout = fopen(output_file, "w");
    if(fout == NULL){
        printf("Can't open file %s to write.", output_file);
        exit(-1);
    }
    for(i = 0; i<SIZE; i++){
        for (j = 0; j<SIZE; j++){
            fprintf(fout, "%d", matrix[i][j]);
            if(j != SIZE-1) fprintf(fout, "%s", " ");
        }
        fprintf(fout, "%c", '\n');
    }
    fclose(fout);

    return 0;

}
