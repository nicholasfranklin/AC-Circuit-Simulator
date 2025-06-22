// PHYS30762 INTRO TO OOP PROJECT
// MNA AC SOURCE HEADER FILE 
// STUDENT ID: 11120960
// MAY 2025

#ifndef MNA_AC_SOURCE_H
#define MNA_AC_SOURCE_H

#include"helper.h"
#include<complex>
#include<vector>


class AC_Source
{
private:
  int source_node;
  complex V0;
  double frequency;
public:
  // Constructors
  AC_Source();
  AC_Source(const int& new_node, const complex& new_V0, const double& new_freq);
  // Destructor
  ~AC_Source();
  // Copyers
  AC_Source(const AC_Source& other);
  AC_Source& operator=(const AC_Source& other);
  // Movers
  AC_Source(AC_Source&& other) noexcept;
  AC_Source& operator=(AC_Source&& other) noexcept;
  void set_V0(const complex& new_V0);
  complex get_V0() const;

  void set_frequency(const double& new_freq);
  double get_frequency() const;

  void set_source_node(const int& new_source_node);
  int get_source_node() const;
};

#endif