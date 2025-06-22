// PHYS30762 INTRO TO OOP PROJECT
// MNA HELPER FILE 
// STUDENT ID: 11120960
// MAY 2025


#ifndef MNA_HELPER_H
#define MNA_HELPER_H

#include<iostream>
#include<complex>
#include<iomanip>

constexpr double PI = 3.141592653589793;

using complex = std::complex<double>; 


// formatting functions
inline void hline()
{
  std::cout<<"------------------------------------------------"<<std::endl;
}
inline void double_hline()
{
  std::cout<<"================================================"<<std::endl;
}
inline void vspace()
{
  std::cout<<"\n\n"<<std::endl; // double vertical space
}

// format phasors
template<typename T>
std::ostream& operator<<(std::ostream& os, const std::complex<T>& complex_nr) 
{
  double magnitude = std::abs(complex_nr);
  double phase = std::arg(complex_nr); // in radians

  os<<std::setprecision(4); // nr sig figs 
  os<<magnitude<<" cis "<<(phase / PI)<<" pi";
  return os;
}

#endif // MNA_HELPER_H