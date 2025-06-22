// PHYS30762 INTRO TO OOP PROJECT
// EXAMPLES MAIN FILE  
// STUDENT ID: 11120960
// MAY 2025

#include "WienBridgeCircuit.h"
#include "Cuboid.h"
#include "RLC.h"


int main() 
{
  double_hline();
  std::cout<<"Running main file to demonstrate example usage of MNA"<<std::endl;
  vspace();
  double_hline();
  /*
  We will:
    - construct a random circuit
      - show that the defualt constructor works  
      - show that the setters for and add_components work
      - show that the copying a circuit works 
    - do the RLC tests
    - do the Wien bridge tests
    - do the Cuboid of resistors tests
  */

  std::cout<<"Creating a circuit on the spot (not as a class)"<<std::endl;
  
  hline();
  Circuit circuit;
  std::cout<<"printing default cicrcuit data"<<std::endl;
  circuit.print_data();

  hline(); 

  std::cout<<"Customising the circuit (add resistor and set source)"<<std::endl;
  // show that set_ac_source works
  circuit.set_ac_source("A", 1.0, 1.0);
  // show that add_component works
  circuit.add_component<Resistor>("A", "GND", 1.0);
  // show that set_V0 works
  circuit.set_V0(100.0);
  // show that set_frequency works
  circuit.set_frequency(150.0);
  // print the data
  circuit.print_data();
  // show that the copying a circuit works 
  hline();
  std::cout<<"Copying the circuit"<<std::endl;
  hline();
  Circuit circuit_2 = circuit; // copy assignment operator
  circuit_2.print_data(); // should be the same data 

  vspace();
  double_hline();
  vspace();

  std::cout<<"Example 2: RLC Circuit"<<std::endl;
  hline();
  RLC rlc;
  rlc.print_data();
  // do the special tests for RLC
  rlc.power_frequency_sweep();
  rlc.phase_frequency_sweep();

  vspace();
  double_hline();
  vspace();

  std::cout<<"Example 3: Wien Bridge Circuit"<<std::endl;
  hline();
  WienBridgeCircuit bridge;
  bridge.print_data();
  // do the special test for the Wien bridge
  bridge.voltage_frequency_sweep();

  vspace();
  double_hline();
  vspace();

  std::cout<<"Example 4: Cuboid of resistors"<<std::endl;
  hline();
  Cuboid cub;
  // print data should show current splits evenly
  cub.print_data();
  // do the special test
  cub.R_tot_resistance_sweep();

  Circuit triangle;
  triangle.set_ac_source("A",1,1);
  triangle.add_component<Resistor>("A", "B", 1);
  triangle.add_component<Resistor>("A", "GND", 1);
  triangle.add_component<Resistor>("A", "C", 1);
  triangle.add_component<Resistor>("B", "C", 1);
  triangle.add_component<Resistor>("C", "GND", 1);
  triangle.add_component<Resistor>("B", "GND", 1);
  std::cout<<"Rtot"<< 1.0/triangle.get_src_current()<<std::endl;
  
  return 0;
}

