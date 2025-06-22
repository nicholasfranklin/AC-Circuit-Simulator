// PHYS30762 INTRO TO OOP PROJECT
// MNA INDUCTOR IMPLEMENTATION FILE
// STUDENT ID 11120960
// MAY 2025

#include"../include/Inductor.h"


// Constructors 
Inductor::Inductor() : Component("Inductor", -1, -1), inductance(1.0) {}

// label is "L" if unfilled 
Inductor::Inductor(const int& new_node_1, const int& new_node_2, 
  const double& new_inductance, const std::string& new_label)
  : Component("Inductor", new_node_1, new_node_2, new_label), inductance(new_inductance) {}


// Destructor
Inductor::~Inductor() = default;


// Copyers
Inductor::Inductor(const Inductor& other) 
: Component(other), inductance(other.inductance) {}

Inductor& Inductor::operator=(const Inductor& other)
{
  if(this != &other)
  {
    Component::operator=(other); // base class copyer
    inductance = other.inductance;
  }
  return *this;
}


// Movers
Inductor::Inductor(Inductor&& other) noexcept 
  : Component(std::move(other)), inductance(std::move(other.inductance)) {}

Inductor& Inductor::operator=(Inductor&& other) noexcept
{
  if(this != &other)
  {
    Component::operator=(std::move(other)); // base class mover
    inductance = std::move(other.inductance);
  }
  return *this;
}


// inductance setter and getter
void Inductor::set_inductance(const double& new_L)
{
  if(new_L <= 0)
  {
    std::cerr<<"Inductor '"<<get_label()<<"' Error: Inductance cannot be negative. " 
             <<"Setting R to 1.0 ohms"<<std::endl;
    inductance = 1.0;
  }
  else
  {
    inductance = new_L;
  }
}  

double Inductor::get_inductance() const {return inductance;}


// overriden from Component 
complex Inductor::get_admittance(const double& frequency) const
{
  return complex(0.0, -1.0 / (2.0 * PI * frequency * inductance));
}
