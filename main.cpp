#include "relaxation.hpp"
#include <fstream>
#include <iostream>

// constants
const double DELTA = 0.05;
const double L = 1.479;
const int N = int(L / DELTA) + 1;
const int STEPS = 200;

typedef std::vector<double> Matrix; // Alias

/*
Grahpene layer thickness 0,341 nm
Permittivity 6.9 \epsilon_0
Carrier density ---> 10^{12} m^{-2}
*/
int main(void) {
  //int N = 100;
  Relaxation relax_method(STEPS);
  Matrix data(N * N);

  // Executing method.
  data = relax_method.setInitialConditions(data, N);
  data = relax_method.setBoundaryConditions(data, N);
  for (int ss = 0; ss < STEPS; ++ss) {
    data = relax_method.evolveSystem(data, N);
  }
  std::ofstream dataPlot("relaxation.dat");
  dataPlot.precision(5);

  // save result
  for (int ii = 0; ii < N; ii++) {
    for (int jj = 0; jj < N; jj++) {
      dataPlot << data[ii * N + jj] << " ";
    }
    dataPlot << std::endl;
  }
  dataPlot.close();
  // relax_method.printMatrix(data, N);
  return 0;
}
