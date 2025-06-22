// PHYS30762 INTRO TO OOP PROJECT
// COMPONENT HEADER FILE 
// STUDENT ID 11120960
// MAY 2025

#ifndef MNA_COMPONENT_H
#define MNA_COMPONENT_H

#include"helper.h"

#include<string>

class Component // abstract class 
{
private:
  std::string type;
  int node_1;
  int node_2;
  std::string label;

  public:

  // Constructors
  Component();
  // label="None" if unfilled
  Component(const std::string& new_type, const int& new_node_1, 
    const int& new_node_2, const std::string& new_label = "None");

  // Destructor
  virtual ~Component();

  // Copyers
  Component(const Component& other);
  Component& operator=(const Component& other);

  // Movers
  Component(Component&& other) noexcept;
  Component& operator=(Component&& other) noexcept;

  // type and label setters and getters 
  void set_type(const std::string& new_type);
  std::string get_type() const;
  void set_label(const std::string& new_label);
  std::string get_label() const;

  // node setters and getters 
  void set_node_1(const int& n1);
  int get_node_1() const;
  void set_node_2(const int& n2);
  int get_node_2() const;

  // get_admittance will be overriden by different component types 
  virtual complex get_admittance(const double& frequency) const = 0;
  // impedence = 1 / admittance 
  complex get_impedence(const double& frequency) const; 
};


#endif // MNA_COMPONENT_H