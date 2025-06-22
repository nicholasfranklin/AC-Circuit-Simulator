// PHYS30762 INTRO TO OOP PROJECT
// MNA RESISTOR IMPLEMENTATION FILE
// STUDENT ID 11120960
// MAY 2025

#include"../include/AC_Source.h"

#include<iostream>

// Constructors
AC_Source::AC_Source() : source_node(1), V0(1.0), frequency(1.0) {} // default node is 1 
AC_Source::AC_Source(const int& new_node, const complex& new_V0, const double& new_freq)
{
  set_source_node(new_node); // will raise error if new_node <= 0
  set_V0(new_V0); // will raise error if new_V0 <= 0
  set_frequency(new_freq); // will raise error if new_freq <= 0
}


// Destructor
AC_Source::~AC_Source() = default;


// Copyers
AC_Source::AC_Source(const AC_Source& other)
  : source_node(other.source_node), V0(other.V0), frequency(other.frequency) {}

AC_Source& AC_Source::operator=(const AC_Source& other)
{
  if(this != &other)
  {
    source_node = other.source_node;
    V0 = other.V0;
    frequency = other.frequency;
  }
  return *this;
}


// Movers
AC_Source::AC_Source(AC_Source&& other) noexcept
  : source_node(other.source_node), V0(std::move(other.V0)), frequency(std::move(other.frequency)) 
{
  // Reset the moved-from object to a valid state 
  other.source_node = 1;
}

AC_Source& AC_Source::operator=(AC_Source&& other) noexcept 
{
  if(this != &other) 
  {
    source_node = other.source_node;
    V0 = std::move(other.V0);
    frequency = std::move(other.frequency);
    // Reset the moved-from object to a valid state 
    other.source_node = 1;
  }
  return *this;
}


// AC amplitude getters and setters  
void AC_Source::set_V0(const complex& new_V0)
{
  if(new_V0 == 0.0)
  {
    std::cerr<<"AC Source Voltage Error: AC amplitude V0 must be non-zero. Setting V0 = 1"<<std::endl;
    V0 = 1.0;
  }
  else
  {
    V0 = new_V0;
  }
}
complex AC_Source::get_V0() const {return V0;}


// frequency getters and setters 
void AC_Source::set_frequency(const double& new_freq)
{ 
  if(new_freq <= 0)
  {
    std::cerr<<"AC Source Frequency Error: Frequency must be > 0: Setting Frequency to 1"<<std::endl;
    frequency = 1;
  }
  else
  {
    frequency = new_freq;
  }
}

double AC_Source::get_frequency() const {return frequency;}


// AC source node getters and setters
void AC_Source::set_source_node(const int& new_source_node)
{
  if(new_source_node <= 0)
  {
    std::cerr<<"AC Source Node Error: Source node must be > 0. Setting source_node to 1"<<std::endl;
    source_node = 1;
  }
  else
  {
    source_node = new_source_node;
  }
}

int AC_Source::get_source_node() const {return source_node;}

