// PHYS30762 INTRO TO OOP PROJECT
// MNA CAPACITOR HEADER FILE
// STUDENT ID 11120960
// MAY 2025


#ifndef MNA_CAPACITOR_H
#define MNA_CAPACITOR_H

#include"Component.h"

class Capacitor : public Component
{
private:
  double capacitance{1.0};
public:
  // Constructors 
  Capacitor();
  // if label = "C" if unfilled 
  Capacitor(const int& new_node_1, const int& new_node_2, 
    const double& new_capacitance, const std::string& new_label="C");
    
  // Destructor
  ~Capacitor() override;
  // Copyers
  Capacitor(const Capacitor& other);
  Capacitor& operator=(const Capacitor& other);
  // Movers
  Capacitor(Capacitor&& other) noexcept;

  Capacitor& operator=(Capacitor&& other) noexcept;

  void set_capacitance(const double& new_C);
  double get_capacitance() const;

  complex get_admittance(const double& frequency) const override;
};

#endif // MNA_CAPACITOR_H