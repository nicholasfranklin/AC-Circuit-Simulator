// PHYS30762 INTRO TO OOP PROJECT
// MNA CAPACITOR IMPLEMENTATION FILE
// STUDENT ID 11120960
// MAY 2025

#include"../include/Capacitor.h"


// Constructors 
// default sets nodes to -1, -1.
Capacitor::Capacitor() : Component("Capacitor", -1, -1), capacitance(1.0) {}

// label is "C" if unfilled 
Capacitor::Capacitor(const int& new_node_1, const int& new_node_2, 
  const double& new_capacitance, const std::string& new_label)
  : Component("Capacitor", new_node_1, new_node_2, new_label), capacitance(new_capacitance) {}


// Destructor
Capacitor::~Capacitor() = default;


// Copyers
Capacitor::Capacitor(const Capacitor& other) 
: Component(other), capacitance(other.capacitance) {}

Capacitor& Capacitor::operator=(const Capacitor& other)
{
  if(this != &other)
  {
    Component::operator=(other); // base class copyer
    capacitance = other.capacitance;
  }
  return *this;
}


// Movers
Capacitor::Capacitor(Capacitor&& other) noexcept 
  : Component(std::move(other)), capacitance(std::move(other.capacitance)) {}

Capacitor& Capacitor::operator=(Capacitor&& other) noexcept
{
  if(this != &other)
  {
    Component::operator=(std::move(other)); // base class mover
    capacitance = std::move(other.capacitance);
  }
  return *this;
}


// capacitor setter and getter 
void Capacitor::set_capacitance(const double& new_C)
{
  if(new_C <= 0)
  {
    std::cerr<<"Capacitor '"<<get_label()<<"' Error: Capacitance cannot be negative. " 
             <<"Setting C to 1.0 F"<<std::endl;
    capacitance = 1.0;
  }
  else
  {
  capacitance = new_C;
  }
}

double Capacitor::get_capacitance() const {return capacitance;}


// overriden from Component 
complex Capacitor::get_admittance(const double& frequency) const
{
  // PI is defined in helper file 
  return complex(0.0, 2.0 * PI * frequency * capacitance);
}
