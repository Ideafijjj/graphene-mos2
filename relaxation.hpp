#include <cmath>
#include <iostream>
#include <vector>

// Relaxation method
typedef std::vector<double> Matrix; // Alias

class Relaxation {
private:
  int _steps;

public:
  // Default constructor
  Relaxation();

  // Destructor
  ~Relaxation();

  // Constructor
  Relaxation(int steps);

  // get-set methods
  int getSteps();
  void setSteps(int steps);

  // Set initial potential discretization conditions.
  Matrix setInitialConditions(Matrix &m, int N);

  // Set Boundary conditions considering geometry.
  Matrix setBoundaryConditions(Matrix &m, int N);

  // Evolution of the system.
  Matrix evolveSystem(Matrix &m, int N);

  // Printing matrix.
  void printMatrix(const Matrix &m, int N);

  // gnuplot methods.
  void init_gnuplot(void);
  void plot_gnuplot(const Matrix &m, int N);
};
