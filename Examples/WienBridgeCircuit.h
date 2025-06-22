// PHYS30762 INTRO TO OOP PROJECT
// EXAMPLES WIEN BRIDGE HEADER FILE  
// STUDENT ID: 11120960
// MAY 2025


#ifndef WIENBRIDGECIRCUIT_H
#define WIENBRIDGECIRCUIT_H

#include "../MNA/MNA.h"
#include<fstream>


class WienBridgeCircuit : public Circuit
{
public:
  WienBridgeCircuit() : Circuit()
  {
    set_ac_source("A", 1.0, 1.0); // AC source at node A, grounded at GND
    // Left Arm
    add_component<Resistor>("A", "B", 1, "R1");
    add_component<Resistor>("B", "GND", 1, "R2"); // will vary 
    // Right arm
    add_component<Capacitor>("A", "C", 1.0, "C1");
    add_component<Resistor>("A", "C", 1.0, "R3");
    add_component<Capacitor>("C", "D", 1.0, "C2"); 
    add_component<Resistor>("D", "GND", 1.0, "R4");
    // Bridge
    add_component<Resistor>("B", "C", 1.0, "R_mid");  
  }
  
  void voltage_frequency_sweep(const std::string& filename = "WienBridge_FreqSweep.txt")
  {
    std::cout<<"Performing Voltage Frequency Sweep for Multiple R2 values"<<std::endl;

    // Define the resistance grid 
    std::vector<double> resistance_grid = {1.0, 1.5, 2.0, 2.5, 3.0};

    // Define the frequency grid
    std::vector<double> frequency_grid;
    size_t N = 50;
    double f_start = 0.01, f_end = 0.6;
    double f_step = (f_end - f_start) / (N - 1);
    for(size_t i = 0; i < N; ++i)
    {
      frequency_grid.push_back(f_start + i * f_step);
    }

    // Open the output file
    std::ofstream outFile(filename);
    if (!outFile.is_open())
    {
      std::cerr<<"Unable to open file"<<std::endl;
      return;
    }

    // Write the header to the file with frequency and R2 columns
    outFile<<"# freq "; // header for freq column
    for(const double& R : resistance_grid)
    {
      outFile<<"V(R2="<<R<<") "; // header for R2 columns 
    }
    outFile<<std::endl;

    // get the R2 resistor object 
    std::shared_ptr<Resistor> Res_2 = std::dynamic_pointer_cast<Resistor>(get_components()[1]);

    // Loop over frequencies and calculate the voltage for each R2 value
    for(const double& freq : frequency_grid)
    {
      outFile<<freq<<" "; // Add the frequency to the first column
       
      // Set the frequency
       set_frequency(freq);

      // Loop over resistance values and compute the voltage for each one
      for(const double& R2 : resistance_grid)
      {
        // Set the value of R2
        Res_2->set_resistance(R2);

        // Get the node potentials
        std::vector<complex> potentials = get_node_potentials();
        // Bridge output = V(B) - V(C)
        std::shared_ptr<Component> Rmid = get_components()[6];
        int b_id = Rmid->get_node_1();
        int c_id = Rmid->get_node_2();
        complex v_out = potentials[b_id] - potentials[c_id];

        // Add the voltage for this R2 value
        outFile<<std::abs(v_out)<<" "; 
      }

      outFile<<std::endl; // New line for the next frequency
    }

    // Reset the values
    set_frequency(1.0);
    Res_2->set_resistance(1.0); 

    // Close the output file
    outFile.close();
    std::cout<<"Voltage Frequency Sweep data written to '"<<filename<<"' successfully."<<std::endl;
  }

};

#endif // WIENBRIDGECIRCUIT_H