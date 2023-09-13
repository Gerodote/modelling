#include <Eigen/Dense>
#include <cstdint>
#include <fstream>
#include <iostream>

int main()
{
  std::ifstream fin_matrix;
  fin_matrix.open("matrix.txt");
  uint64_t rows = 0;
  uint64_t cols = 0;
  fin_matrix >> rows >> cols;
  Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> matrix_to_solve(rows, cols);
  double a_value = 0;
  for (uint64_t row = 0; row < rows; ++row)
  {
    for (uint64_t col = 0; col < cols; ++col)
    {
      fin_matrix >> a_value;
      matrix_to_solve(static_cast<Eigen::Index>(row), static_cast<Eigen::Index>(col)) = a_value;
    }
  }

  std::cout << "matrix_to_solve:\n" << matrix_to_solve << '\n';

  std::ifstream fin_vector;
  fin_vector.open("vector.txt");

  Eigen::Matrix<double,Eigen::Dynamic,1,0,Eigen::Dynamic,1> a_vector(rows);

  for (auto& row : a_vector)
  {
    fin_vector >> row;
  }

  std::cout << "vector b:\n" << a_vector << '\n';

  Eigen::MatrixXd pseudo_inverse_of_matrix_to_solve = matrix_to_solve.completeOrthogonalDecomposition().pseudoInverse();

  std::cout << "pseudo_inverse_of_matrix_to_solve:\n" << pseudo_inverse_of_matrix_to_solve << '\n';

  std::cout << "Checking if the only solution exists:\n";

  auto maybe_a_solution = pseudo_inverse_of_matrix_to_solve * a_vector;
  std::cout << "A*(A^+)*b = \n" <<  matrix_to_solve * pseudo_inverse_of_matrix_to_solve * a_vector << "\n";
  if ((matrix_to_solve * pseudo_inverse_of_matrix_to_solve * a_vector).isApprox(a_vector))
  {
    std::cout << "yes\nSolution is:\n" << maybe_a_solution << '\n';
  }
  else
  {
    std::cout << "no\nSet of solution can be described as:\n" << maybe_a_solution << "\n+\n" << Eigen::MatrixXd::Identity(static_cast<Eigen::Index>(rows),static_cast<Eigen::Index>(rows)) - matrix_to_solve * pseudo_inverse_of_matrix_to_solve << " * any_vector_appropriate_size\n";
    
  }

  fin_matrix.close();
  fin_vector.close();
}
