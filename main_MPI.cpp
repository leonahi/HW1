#include <iostream>
#include <string.h>
#include <mpi.h>


using namespace std;

#define ORDER 1000

int matrix_multiplication(double* A, double* B, double* C, int order, int local_strip_size);


int main(int argc, char* argv[])
{
    int my_rank;
    int p;
    int source;
    int dest;
    int tag = 0;
    double start, end;
    char message[100];
    MPI_Status status;    
    
    
    double *A, *B, *C;
    int local_strip_size;
    int start_address;
    
    
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &p);

    //cout << "Comm size : " << p << endl;
    
    local_strip_size = ORDER/p;
    
    //cout << "Local size of process : " << my_rank << " = "<< local_strip_size << endl;
    
    B = new double [ORDER*ORDER];
    if(my_rank == 0) {
        A = new double [ORDER*ORDER];
        C = new double [ORDER*ORDER];
        for(int i=0; i<ORDER*ORDER; ++i) {
            A[i] = 1.0;
            B[i] = 1.0;
        }

    }
    else {
        A = new double [ORDER*local_strip_size];
        C = new double [ORDER*local_strip_size];
        for(int i=0; i<ORDER*local_strip_size; ++i) {
            C[i] = 0.0;
        }
    }
    
    
    start = MPI_Wtime();
        
    if(my_rank == 0) {
        start_address = ORDER*local_strip_size;
        for(int i=1; i<p; ++i) {
            MPI_Send(A + start_address, ORDER*local_strip_size, MPI_DOUBLE, i, tag, MPI_COMM_WORLD);
            start_address += ORDER*local_strip_size;
        }
    }
    else {
        MPI_Recv(A, ORDER*local_strip_size, MPI_DOUBLE, 0, tag, MPI_COMM_WORLD, &status);
    }
    
    
    MPI_Bcast(B, ORDER*ORDER, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    
    
    matrix_multiplication(A, B, C, ORDER, local_strip_size);
    
    if(my_rank == 0) {
        start_address = ORDER*local_strip_size;
        for(int i=1; i<p; ++i) {
            MPI_Recv(C + start_address, ORDER*local_strip_size, MPI_DOUBLE, i, 2, MPI_COMM_WORLD, &status);
            start_address += ORDER*local_strip_size;
        }
    }
    else {
        MPI_Send(C, ORDER*local_strip_size, MPI_DOUBLE, 0, 2, MPI_COMM_WORLD);
    }
    
    end = MPI_Wtime();
    
    cout << "Total time taken by process " << my_rank << " = " << end-start << endl;
    
    if(my_rank == 0) {
        if(ORDER > 32) {
            cout << "Size is to large to display..." << endl;
        }
        else {
            for(int i=0; i<ORDER; ++i) {
                for(int j=0; j<ORDER; ++j) {
                    cout << C[j + i*ORDER] << " ";
                }
                cout << endl;
            }
        }
    } 
    
    MPI_Finalize();

    return 0;
}


int matrix_multiplication(double* A, double* B, double* C, int order, int local_strip_size)
{
    for(int i = 0; i < local_strip_size; i++)
    {
        for(int j = 0; j < ORDER; j++)
        {
            C[j + i*ORDER] = 0;
            for(int k = 0; k < ORDER; k++)
            {
                C[j + i*ORDER] += A[i*ORDER + k]*B[j + ORDER*k];          // dot-product
                
            }   
        }
    }
  
  return 0;
}

