#include "relaxation.hpp"

const double DELTA = 0.05;
typedef std::vector<double> Matrix; // Alias

// Default Constructor
Relaxation::Relaxation() {}

// Default Destructor
Relaxation::~Relaxation() {}

// Constructor
Relaxation::Relaxation(int steps) : _steps(steps) {}

// get-set methods
int Relaxation::getSteps() { return this->_steps; }

void Relaxation::setSteps(int steps) { this->_steps = steps; }

Matrix Relaxation::setInitialConditions(Matrix &m, int N) {
  //for (int ii = 0; ii < N; ++ii) {
    //for (int jj = 0; jj < N; ++jj) {
      //m[ii * N + jj] = -(1.6 * std::pow(10,-19) * 8.7 * std::pow(10,12))
          /// (6.9 * 8.85 *pow(10,-12)); //graphene
    //}
  //}
  for (int ii = 0; ii < N; ++ii) {
    for (int jj = 0; jj < N; ++jj) {
      m[ii * N + jj] = 0; //vacuum
    }
  }
  return m;
}

Matrix Relaxation::setBoundaryConditions(Matrix &m, int N) {
  int ii = 0, jj = 0;

  ii = 0;
  for (jj = 0; jj < N; ++jj)
    m[ii * N + jj] = 0.0;

  ii = N - 1;
  for (jj = 0; jj < N; ++jj)
    m[ii * N + jj] = 0.0;

  jj = 0;
  for (ii = 1; ii < N - 1; ++ii)
    m[ii * N + jj] = 95.5;

  jj = N - 1;
  for (ii = 1; ii < N - 1; ++ii)
    m[ii * N + jj] = 1.0;
  return m;
}

Matrix Relaxation::evolveSystem(Matrix &m, int N) {
  for (int ii = 0; ii < N; ++ii) {
    for (int jj = 0; jj < N; ++jj) {
      // check if boundary
      if (ii == 0)
        continue;
      if (ii == N - 1)
        continue;
      if (jj == 0)
        continue;
      if (jj == N - 1)
        continue;
      // evolve non boundary
      m[ii * N + jj] = (m[(ii + 1) * N + jj] + m[(ii - 1) * N + jj] +
                        m[ii * N + jj + 1] + m[ii * N + jj - 1]) /
                       4.0;
    }
  }
  return m;
}

void Relaxation::printMatrix(const Matrix &m, int N) {
  for (int ii = 0; ii < N; ++ii) {
    for (int jj = 0; jj < N; ++jj) {
      std::cout << ii * DELTA << " " << jj * DELTA << " " << m[ii * N + jj]
                << "\n";
    }
    std::cout << "\n";
  }
}

void Relaxation::init_gnuplot(void) {
  std::cout << "set contour " << std::endl;
  std::cout << "set terminal gif animate " << std::endl;
  std::cout << "set out 'anim.gif' " << std::endl;
}

void Relaxation::plot_gnuplot(const Matrix &m, int N) {
  std::cout << "splot '-' w pm3d " << std::endl;
  printMatrix(m, N);
  std::cout << "e" << std::endl;
}
