// PHYS30762 INTRO TO OOP PROJECT
// MNA RESISTOR IMPLEMENTATION FILE
// STUDENT ID 11120960
// MAY 2025

#include"../include/Resistor.h"


// Constructors
Resistor::Resistor() : Component("Resistor", -1, -1), resistance(1.0) {};

// label is "R" if unfilled
Resistor::Resistor(const int& new_node_1, const int& new_node_2, 
  const double& new_resistance, const std::string& new_label)
  : Component("Resistor", new_node_1, new_node_2, new_label), resistance(new_resistance) {}


// Destructor
Resistor::~Resistor() = default; 


// Copyers
Resistor::Resistor(const Resistor& other) 
: Component(other), resistance(other.resistance) {}

Resistor& Resistor::operator=(const Resistor& other)
{
  if(this != &other)
  {
    Component::operator=(other); // base class copyer
    resistance = other.resistance;
  }
  return *this;
}


// Movers
Resistor::Resistor(Resistor&& other) noexcept 
  : Component(std::move(other)), resistance(std::move(other.resistance)) {}

Resistor& Resistor::operator=(Resistor&& other) noexcept 
{
  if(this != &other) 
  {
    Component::operator=(std::move(other)); // base class mover
    resistance = std::move(other.resistance);
  }
  return *this;
}


// resistance setter and getter
void Resistor::set_resistance(const double& new_R)
{
  if(new_R <= 0)
  {
    std::cerr<<"Resistor '"<<get_label()<<"' Error: Resistance cannot be negative. " 
             <<"Setting R to 1.0 ohms"<<std::endl;
    resistance = 1.0;
  }
  else
  {
  resistance = new_R;
  } 
}

double Resistor::get_resistance() const {return resistance;}


// overriden from Component (frequency unused)
complex Resistor::get_admittance(const double& frequency) const
{
  (void)frequency; // explicitly mark as unused so compiler doesn't complain
  return 1.0 / resistance;
}

