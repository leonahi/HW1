#include<iostream>
#include<cstdlib>
#include<string>
#include<omp.h>

using namespace std;

#define ORDER 5000

//#include"matrix_mult.hpp"
//#include"matrix_initialization.hpp"
//#include"display_matrix.hpp"

int main(int argc, char* argv[])
{
  float *A;
  float *B;
  float *C;
  
  double start, end;
  
  size_t ROWA = ORDER, ROWB = ORDER, COLA = ORDER, COLB = ORDER;
  int errNum;
  
  A = new float[ROWA*COLA];
  B = new float[ROWB*ROWB];
  C = new float[ROWA*COLB];
  
  for(int i=0; i<(ORDER*ORDER); i++)
  {
    A[i] = 1;
    B[i] = 1;
  }
  start = omp_get_wtime();
  
//omp_set_num_threads(16);
#pragma omp parallel for shared (A, B, C, ROWA, COLA, COLB) num_threads(2)
  for(int i = 0; i < ROWA; i++)
  {
    for(int j = 0; j < COLB; j++)
    {
      C[j + i*COLB] = 0;
      for(int k = 0; k < COLA; k++)
      {
        C[j + i*COLB] += A[i*COLA + k]*B[j + COLB*k];   // dot-product
      }    
    } 
  }
  
  end = omp_get_wtime();
  
  cout<<"Time taken to multiply "<<ORDER<<"X"<<ORDER<<" matrix : "<<(end-start)<<" seconds"<<endl;

  //display_matrix(C, COLB, ROWA);
  
  //float *D = new float[12];
  //size_t ColD, RowD;
  
  //errNum = matrix_initialization(argv[1], D, ColD, RowD);
  
  //display_matrix(D, 3, 4);
  
  
  delete [] A;
  delete [] B;
  delete [] C;
  
  return 0;
}
