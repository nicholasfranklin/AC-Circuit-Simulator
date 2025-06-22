// PHYS30762 INTRO TO OOP PROJECT
// CIRCUIT HEADER FILE 
// STUDENT ID 11120960
// MAY 2025

#ifndef MNA_CIRCUIT_H
#define MNA_CIRCUIT_H

#include"helper.h"
#include"Component.h"
#include"LinAlg.h"
#include"AC_Source.h"

#include<unordered_map>
#include<memory>


class Circuit
{
private:
  int num_nodes = 0;
  std::vector<std::shared_ptr<Component>> components;

  // stores correspondence between nodes as strings and as ints
  std::unordered_map<std::string, int> node_ids{{"GND", 0}};
  std::unordered_map<int, std::string> id_to_node{{0, "GND"}}; // GND node is zero

  std::unique_ptr<AC_Source> ac_source;

  int get_node_id(const std::string& node_name); // converts string to int and stores the data 
  std::vector<complex> solve_circuit() const; // solve the MNA system

public:
  // constructors
  Circuit();
  Circuit(const std::vector<std::shared_ptr<Component>>& new_components, std::unique_ptr<AC_Source> new_ac_source);
  // destructor
  ~Circuit();

  // copyers
  Circuit(const Circuit& other);
  Circuit& operator=(const Circuit& other);

  // movers 
  Circuit(Circuit&& other) noexcept;
  Circuit& operator=(Circuit&& other) noexcept;

  void set_ac_source(const std::string& new_node, const double& new_V0, const double& new_freq);
  void set_ac_source(std::unique_ptr<AC_Source> new_ac_source);

  // Add component (has to be in header file)
  template <typename T>
  void add_component(const std::string& n1, const std::string& n2, const double& value)
  {
    // when you add a component, it converts the nodes as strings to integers
    components.push_back
    (
      std::make_shared<T> // resistor inductor or capacitor
      (
      get_node_id(n1), get_node_id(n2), // from str -> int and stored in the node id maps
      value
      )
    ); 
  }
  // Add component (has to be in header file)
  template <typename T>
  void add_component(const std::string& n1, const std::string& n2, const double& value, const std::string& label)
  {
    // when you add a component, it converts the nodes as strings to integers
    components.push_back
    (
      std::make_shared<T> // resistor inductor or capacitor
      (
      get_node_id(n1), get_node_id(n2), // from str -> int and stored in the node id maps
      value, label
      )
    );
  }

  void set_components(const std::vector<std::shared_ptr<Component>>& new_comps);
  std::vector<std::shared_ptr<Component>> get_components() const;
  bool is_empty() const;
  bool nodes_invalid(const std::vector<std::shared_ptr<Component>>& comps) const;
  
  const AC_Source& get_ac_source() const;

  void set_frequency(const double& freq);
  double get_frequency() const;

  void set_V0(const double& new_V0);
  complex get_V0() const;

  complex get_src_current() const;
  std::vector<complex> get_node_potentials() const;

  void print_data();
};

#endif // MNA_CIRCUIT_H