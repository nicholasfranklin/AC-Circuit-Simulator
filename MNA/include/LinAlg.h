// PHYS30762 INTRO TO OOP IN C++ PROJECT 
// LINALG HEADER FILE 
// STUDENT ID: 11120960
// MAY 2025


#ifndef MNA_LINALG_H
#define MNA_LINALG_H

#include<vector>
#include<complex>
#include<iostream>
#include<cmath>  


template<typename T> 
class LinAlg // static templated class 
{
public:

  // Function to create a zero matrix of size NxN
  static std::vector<std::vector<T>> createZeroMatrix(int N)
  {
    return std::vector<std::vector<T>>(N, std::vector<T>(N, {0.0, 0.0}));
  }


  // Function to create a zero vector of size N
  static std::vector<T> createZeroVector(int N)
  {
    return std::vector<T>(N, {0.0, 0.0});
  }


  // LU decomposition 
  // pivot is initialised before so that it can be accessed outside of function the 
  static bool LU_decompose(std::vector<std::vector<T>>& A, std::vector<int>& pivot) 
  {
    int N = A.size();

    // Initialize pivot as identity
    for(int i = 0; i < N; ++i)
    {
      pivot[i] = i; // pivot = {0,1,2,...}
    }

    for(int i = 0; i < N; ++i) // ith column 
    {
      // Find pivot row
      int pivot_row = i;
      for(int j = i + 1; j < N; ++j) // check below row i 
      {
        if (std::abs(A[j][i]) > std::abs(A[pivot_row][i]))
        {
        pivot_row = j;
        }
      } 

      if(std::abs(A[pivot_row][i]) < 1e-12)
      {
        // will raise error in another function
        return false; // Singular matrix (A[i][j>i] = 0)
      }

      // Swap rows in A 
      if(pivot_row != i) 
      {
        std::swap(A[i], A[pivot_row]);
        std::swap(pivot[i], pivot[pivot_row]); // transposition i <-> pivot_row
      }

      // Eliminate entries below pivot
      for(int j = i + 1; j < N; ++j) // for each row below i
      {
        A[j][i] /= A[i][i]; // write A[j][i] as a fraction of A[i,i] (note A[i,i] != 0)
        for(int k = i + 1; k < N; ++k)
        {
          A[j][k] -= A[j][i] * A[i][k]; // update the row j 
        }
      }
    }
    return true;
  }


  // solve Ax = b given a pivot 
  static std::vector<T> LU_solve_A_piv_b(
    const std::vector<std::vector<T>>& A, 
    const std::vector<int>& pivot, const std::vector<T>& b)
  {
    int N = A.size();
    std::vector<T> x(N);
    std::vector<T> y(N);

    // Apply pivot to b
    std::vector<T> b_permuted(N);
    for(int i = 0; i < N; ++i)
    {
      b_permuted[i] = b[pivot[i]]; // permute entries of b according to pivot 
    }

    // Forward substitution (solve L*y = pivot * b)
    for(int i = 0; i < N; ++i)
    {
      y[i] = b_permuted[i];
      for(int j = 0; j < i; ++j) // index only the lower triangular part 
      {
        y[i] -= A[i][j] * y[j];
      }
    }

    // Backward substitution (solve U * x = y)
    for(int i = N - 1; i >= 0; --i) // start at the bottom of the vector 
    {
      x[i] = y[i];
      for(int j = i + 1; j < N; ++j) // index only upper triangular part 
      {
        x[i] -= A[i][j] * x[j];
      }
      x[i] /= A[i][i];
    }

    return x;
  }

  
  // solve Ax = b
  static std::vector<T> LU_solve_x(std::vector<std::vector<T>> A, const std::vector<T>& b) 
  {
    int N = A.size();
    std::vector<int> pivot(N);
    
    // error handling 
    if(!LU_decompose(A, pivot))
    {
      std::cerr<<"Matrix is singular or near-singular! "
               <<"There is likely an error with the construction of the circuit. "
               <<"Returning a vector of zeros."<<std::endl;
      return std::vector<T>(N, {0.0, 0.0});
    }

    return LU_solve_A_piv_b(A, pivot, b);
  }


  // print matrix
  static void print_Mat(std::vector<std::vector<T>>& A)
  {
    int n_rows = A.size();
    int n_cols = A[0].size(); // will check this is the same for all rows 
    if(n_rows==0)
    {
      std::cerr<<"LinAlg print_Mat Error: Matrix is empty"<<std::endl;
      return; // do nothing
    }
    for(int i = 1; i < n_rows; i++)
    {
      if(A[i].size() != n_cols) // find the first row with different nr of columns 
      {
        std::cerr<<"LinAlg print_Mat Error: Matrix is not mxn (different sized rows/columns)"<<std::endl;
        return; // do nothing 
      }
    }  
    // if there's nothing wrong with the matrix
    for(int i=0; i < n_rows; i++)
    {
      for(int j=0; j<A[i].size(); j++)
      {
        std::cout<<A[i][j]<<" | ";
      }
      std::cout<<"\n";
    }
  }


  // print vector 
  static void print_Vec(std::vector<T>& V)
  {
    int size = V.size();
    if(size == 0) // check vector non empty
    {
      std::cout<<"LinAlg print_Vec Error: Vector is emtpy"<<std::endl;
      return; // do nothing
    }
    std::cout<<"[ ";
    for(int i = 0; i < size; i++)
    {
      std::cout<<V[i]<<"\n";
    }
    std::cout<<"]"<<std::endl;
  }
};


#endif // MNA_LINALG_H