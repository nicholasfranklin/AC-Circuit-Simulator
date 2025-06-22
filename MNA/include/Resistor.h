// PHYS30762 INTRO TO OOP PROJECT
// MNA RESISTOR HEADER FILE
// STUDENT ID 11120960
// MAY 2025

#ifndef MNA_RESISTOR_H
#define MNA_RESISTOR_H

#include"Component.h"

class Resistor : public Component
{
private:
  double resistance;
public:
  // Constructors
  Resistor(); 
  // label is "R" if unfilled
  Resistor(const int& new_node_1, const int& new_node_2, 
    const double& new_resistance, const std::string& new_label="R");
    
  //Destructor
  ~Resistor() override;
  // Copyers
  Resistor(const Resistor& other);
  Resistor& operator=(const Resistor& other);
  // Movers
  Resistor(Resistor&& other) noexcept;
  Resistor& operator=(Resistor&& other) noexcept;

  // resistance setter and getter
  void set_resistance(const double& new_R);
  double get_resistance() const;

  // overriden from base class
  complex get_admittance(const double& frequency) const override;
};

#endif // MNA_RESISTOR_H