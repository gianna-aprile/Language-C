#include <stdio.h>
#include <stdlib.h>


int solve(int **, int);
int check(int **, int, int, int);


// returns 1 if val passes test, 0 if it is a duplicate
int check(int ** grid, int row, int col, int val){

  int i, j, rSub, cSub;

  // check row
  for( i = 0; i < 9; i++){

    if( grid[row][i] == val){

      return 0;
    }
  }
  

  // check col
  for( i = 0; i < 9; i++){

    if( grid[i][col] == val){

      return 0;
    }
  }


  // check square - find which square row and col are in
   rSub = row - row%3;
   cSub = col - col%3;

  for(i = rSub; i < rSub+3; i++){

    for(j = cSub; j < cSub+3; j++){

      if( grid[i][j] == val){

	return 0;
      }
    }
  }


  return 1;
  
}


// returns 1 if solvable, 0 if not solvable
int solve(int ** grid){

  int i, j, r, c, k;
  r = -1;
  c = -1;

  // find empty location in grid
  for(i = 0; i < 9; i++){

    for(j = 0; j < 9; j++){

      if(grid[i][j] == 0){

	r = i;
	c = j;
	break;
      }
    }

    if( r != -1 && c != -1){

        break;
    }
  }

  // if there are no empty locations
  if( r == -1 && c == -1){

    return 1;
  }


  // check each number solution at location (r,c) then backtrack 
  if( r != -1 && c != -1){  

    for(k = 0; k < 9; k++){

      if (check(grid, r, c, (k+1)) == 1){
	   
	grid[r][c] = (k+1);
      
	if( solve(grid, (k+1)) == 1){

	  return 1;
      
	}else{
      
	  grid[r][c] = 0; // failure
	}
      }
  
    }
  }					
  
  return 0;
}



int main(int argc, char** argv){

 if( argc != 2){

    return 0;
  }

  FILE *fp;
  int length;

  fp = fopen(argv[1], "r");

  // if the file doesn't exist
  if(fp == NULL){
    
    printf("error\n");
    return 0;
  }
 
 fscanf( fp, "%d\n", &length);
  
  // if file is empty
 fseek(fp, 0, SEEK_END);
 int fsize = ftell(fp);

   if (fsize == 0) {
    
    printf("0\n");
    return 0;
   }

 // reset pointer to beginning of file
 fseek(fp, 0, SEEK_SET);


 int** grid = (int**)malloc(9*sizeof(int*));
 
 // allocate memory for grid 
 int a; 
 for(a = 0; a < 9; a++){
   
   grid[a] = (int*)malloc(9*sizeof(int));
 }

 int i, j;
 for(i = 0; i < 9; i++){
   
   for(j = 0; j < 9; j++){

     fscanf(fp, "%d\t", &grid[i][j]);
   }
 }

 fclose(fp);


 int solveVal = solve(grid, 1);

 if( solveVal == 0){

   printf("no-solution\n");
 }

 else{

  for(i = 0; i < 9; i++){
   
   for(j = 0; j < 9; j++){

     printf("%d\t", grid[i][j]);
   }
   printf("\n");
 }


  // free memory
  for(i = 0; i < 9; i++){

    free(grid[i]);
  }
  free(grid≈ß);;


 }

  return 0;
}
