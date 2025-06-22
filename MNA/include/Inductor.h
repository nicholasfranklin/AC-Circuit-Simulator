// PHYS30762 INTRO TO OOP PROJECT
// MNA INDUCTOR HEADER FILE
// STUDENT ID 11120960
// MAY 2025


#ifndef MNA_INDUCTOR_H
#define MNA_INDUCTOR_H

#include"Component.h"


class Inductor : public Component
{
private:
  double inductance;
public:
  // Constructors 
  Inductor();
  Inductor(const int& new_node_1, const int& new_node_2, const double& new_inductance, const std::string& new_label="L");
  // Destructor
  ~Inductor() override;
  // Copyers
  Inductor(const Inductor& other);

  Inductor& operator=(const Inductor& other);
  // Movers
  Inductor(Inductor&& other) noexcept;
  Inductor& operator=(Inductor&& other) noexcept;

  // inductance setter and getter
  void set_inductance(const double& new_L);
  double get_inductance() const;

  // overriden from Component
  complex get_admittance(const double& frequency) const override;
};

#endif // MNA_INDUCTOR_H