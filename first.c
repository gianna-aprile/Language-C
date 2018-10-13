#include <stdio.h>
#include <stdlib.h>

double ** multiply (double**, double**, int, int, int, int);
double ** transpose(double**, int, int);
double ** invert(double**, int, int);
double ** pivot(double**, int, int, int, int);
double ** nonpivot(double**, int, int, int, int);
double ** upperNonpivot(double**, int, int, int, int);


double ** pivot(double** temp, int rsize, int csize, int row, int col){

  int a;
 
  // multiply by a nonzero scalar
  double val = temp[row][col];

  for(a = 0; a < csize; a++){

    // if statement to prevent "-0" storing
    if( temp[row][a] != 0){
   
      temp[row][a] = (temp[row][a])/val;
    }
  }

  return temp;
}


double ** nonpivot(double** temp, int rsize, int csize, int row, int col){

  double scalar, val1, val2;
  int a, b;

    //find pivot row
    for( a = row-1; a >= 0; a--){

      if(temp[a][col] == 1){

	val1 = (-1)*(temp[row][col]);
	val2 = temp[a][col];

	scalar = val1/val2;
	break;
      }
    }

    // do row opp on row "row"
    for(b=0; b<csize; b++){

      temp[row][b] = temp[row][b] + scalar * (temp[a][b]);
    }
    
  return temp;
}


double ** upperNonpivot(double** temp, int rsize, int csize, int row, int col){

  // converting upper half to zeros
  int a, b;
  double scalar, val1, val2;
  for( a = rsize-1; a>=0; a--){

    if ( temp[a][col] == 1){

      	val1 = (-1)*(temp[row][col]);
	val2 = temp[a][col];

	scalar = val1/val2;
     
	break;
    }
  }
    // do row opp on row "row"
    for(b=0; b<csize; b++){

      temp[row][b] = temp[row][b] + scalar * (temp[a][b]);
    }
  
  return temp;
}


double ** invert(double** mat, int row, int col){

  int ncol = 2*col;

  //memory allocation
  double ** temp = (double**)malloc(row * sizeof(double*));
  int e;
  for (e = 0; e<row; e++){	
      temp[e] = (double*)malloc(ncol*sizeof(double));
   }

  // load mat into the left half of temp
   int a;
   int b;
 

   for( a = 0; a < row; a++){

     for( b = 0; b < col; b++){

       temp[a][b] = mat[a][b];
     }
   }

   //add identity matrix to right half
   for( a = 0; a < row; a++){

     for( b = (ncol/2); b < ncol; b++){
       
       if( (b-row) == a){
         temp[a][b] = 1;
       }
       else{
	 temp[a][b] = 0;
       }
     }
   }
  



   // perform Gauss-Jordan Elimination
   int c;

   for( a = 0; a < row; a++){

     for( b = 0; b < col; b++){
       
       if(a==b){
        
	 if( temp[a][b] != 1){
       
	   temp = pivot(temp, row, ncol, a, b);

	 }


	 for(c = a+1; c < row; c++){
	
	   if(temp[c][b] != 0 ){
        
	     temp = nonpivot(temp, row, ncol, c, b);


	   }
	 }
       }
     }
   }



   for( a = row-1; a >= 0; a--){
     
     for(b = col-1; b >= 0; b--){
     
       if( a != b && b > a){
      
	 temp = upperNonpivot(temp, row, ncol, a, b);
       }
     }
   }




  double ** result = (double**)malloc(row * sizeof(double*));

  for (e = 0; e<row; e++){	
      result[e] = (double*)malloc(col*sizeof(double));
   }

   for( a = 0; a < row; a++){

     for( b = (ncol/2); b < ncol; b++){
       
       result[a][b-col] = temp[a][b];
     }
   }
  

   return result;

}



double ** transpose( double ** mat, int row, int col){

  int nrow = col;
  int ncol = row;

  //memory allocation
  double ** result = (double**)malloc(nrow * sizeof(double*));
  int e;
  for (e = 0; e<nrow; e++){	
      result[e] = (double*)malloc(ncol*sizeof(double));
   }

   int a;
   int b;

   for( a = 0; a < nrow; a++){

     for( b = 0; b < ncol; b++){

       result[a][b] = mat[b][a];
     }
   }
   
   return result;

}


double ** multiply (double** x, double** y, int row1, int col1, int row2, int col2){

  // row1 = n, col2 = k, row2 = m, col2 = k-1

  double ** result = (double**)malloc(row1 * sizeof(double*));
  int e;
  for (e = 0; e<row1; e++){	
      result[e] = (double*)malloc(col2*sizeof(double));
   }


   int a;
   int b;
   int c;
   double add = 0;

   for( a = 0; a < row1; a++){

     for( b = 0; b < col2; b++){
       
       for( c = 0; c < row2; c++){

	 add = add + (x[a][c]*y[c][b]);
       }

       result[a][b] = add;
       add = 0;
     }
   }


   return result;

}



int main( int argc, char** argv ){


 if( argc != 3){

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


 double ** x;
 double ** y;

 int n;
 int k;

    fscanf(fp,"%d\n%d\n",&k,&n);

  //allocate memory for matrix x

    k = k+1;

    x = (double**)malloc(n * sizeof(double*));
    int a;
    for (a = 0; a<n; a++){	
      x[a] = (double*)malloc(k*sizeof(double));
    }

  //allocate memory for matrix y
    y = (double**)malloc(n * sizeof(double*));
     int g;
    for (g = 0; g<n; g++){	
      y[g] = (double*)malloc(1*sizeof(double));
    }


    // set column 1 of x = 1
    int u;
    for( u = 0; u < n; u++){
      
      x[u][0] = 1.0;
    }


   // input data into x and y
   int count = 0; 
   int i;
   int j;

   for( i = 0; i < n; i++){

     for( j = 0; j < k; j++){
       
       if( count == k-1){
	 
	 fscanf(fp, "%lf", &y[i][0]);
	
      
       } else {

	 fscanf(fp, "%lf%*[,]", &x[i][j+1]);
	 count++;

       }
 
     }
      count = 0; 
   }
   
   fclose(fp);

   k = k-1; // reset k to 4 before reading test file
 
   // read test file
    FILE *rp;
   

  rp = fopen(argv[2], "r");

  // if the file doesn't exist
  if(rp == NULL){
    
    printf("error\n");
    return 0;
  }
 
 fscanf( rp, "%d\n", &length);
  
  // if file is empty
 fseek(rp, 0, SEEK_END);
 fsize = ftell(rp);

   if (fsize == 0) {
    
    printf("0\n");
    return 0;
   }

 // reset pointer to beginning of file
 fseek(rp, 0, SEEK_SET);


 double ** data;
 
 int m;

    fscanf(rp,"%d\n", &m);

  //allocate memory for matrix data

    data = (double**)malloc(m * sizeof(double*));
  
    for (a = 0; a<m; a++){	
    
      data[a] = (double*)malloc(k*sizeof(double));
    }  
   

   for( i = 0; i < m; i++){

     for( j = 0; j < k; j++){
	 
       fscanf(rp, "%lf%*[,]", &data[i][j]);
     }
   }

  fclose(rp);



  
  double** tpx = transpose(x, n, (k+1));


  double** mult = multiply(tpx, x, (k+1), n, n, (k+1));

  double** inverse = invert(mult,k+1,k+1);

  double** inTimesXt = multiply(inverse, tpx, (k+1), (k+1), (k+1), n);

  double** w = multiply(inTimesXt, y, (k+1), n, n, 1);

  
  double** result = (double**)malloc(m * sizeof(double*));
   for (a = 0; a<m; a++){	
    
      result[a] = (double*)malloc(1*sizeof(double));
    }  
   

   double add = 0;
  for(i = 0; i < m; i++){
   
    add = w[0][0];
    
    for(j = 0; j < k; j++){

      add = add + (data[i][j] * w[j+1][0]);
    }
    
    printf("%0.0lf\n", add);
  }
   
  return 0;

}
