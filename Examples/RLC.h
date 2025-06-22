// PHYS30762 INTRO TO OOP PROJECT
// EXAMPLES RLC HEADER FILE 
// STUDENT ID: 11120960
// MAY 2025

#include "../MNA/MNA.h"
#include<fstream>

class RLC : public Circuit
{
public:
  RLC() : Circuit()
  {
    set_ac_source("A", 1, 1);
    add_component<Resistor>("A", "B", 1.0);
    add_component<Inductor>("B", "C", 1.0);
    add_component<Capacitor>("C", "GND", 1.0);
  }

  void set_resistance(const double& new_R)
  {
    auto resistor = std::dynamic_pointer_cast<Resistor>(get_components()[0]);
    resistor->set_resistance(new_R);
  }

  void power_frequency_sweep(const std::string& filename = "RLC_power_frequency_sweep.txt")
  {
    std::cout<<"Performing Power Frequency Sweep for Multiple R values"<<std::endl;
    // make the resistance grid
    std::vector<double> resistance_grid = {0.5, 1.0, 1.5, 2.0};
    // make the frequency grid
    std::vector<double> frequency_grid;
    size_t N = 50;
    double start = 0.01, end = 0.35;
    double step = (end - start) / (N - 1);
    for(size_t i = 0; i < N; ++i)
    {
      frequency_grid.push_back(start + i * step);
    }
    
    // make the output file 
    std::ofstream outFile(filename);
    if(!outFile.is_open())
    {
      std::cerr<<"Unable to open file"<<std::endl;
      return;
    }

    outFile<<"# freq "; // header for freq column
    for(double R : resistance_grid)
    {
      outFile<<"P(R="<<R<<") "; // header for R columns 
    }
    outFile<<""<<std::endl;

    for(double freq : frequency_grid)
    {
      set_frequency(freq);
      outFile<<freq<<" "; // add the frequency to the first column
      for(double R : resistance_grid)
      {
        set_resistance(R);
        double I_tot = std::abs(get_src_current());
        double power = 0.5 * I_tot * I_tot * R; // = I_rms^2 R 
        outFile<<power<<" "; // add the power for each R value 
      }
      outFile<<""<<std::endl;
    }

    // resest the values 
    set_resistance(1.0);
    set_frequency(1.0);

    outFile.close();
    std::cout<<"Power Frequency Sweep data written to '"<<filename<<"' successfully."<<std::endl;
  }   

  void phase_frequency_sweep(const std::string& filename = "RLC_phase_frequency_sweep.txt")
  {
    std::cout<<"Performing Phase Frequency Sweep for Multiple R values"<<std::endl;
    
    // make the resistance grid
    std::vector<double> resistance_grid = {0.5, 1.0, 1.5, 2.0};

    // make the frequency grid 
    std::vector<double> frequency_grid;
    size_t N = 50;
    double start = 0.01, end = 0.35;
    double step = (end - start) / (N - 1);
    for(size_t i = 0; i < N; ++i)
    {
      frequency_grid.push_back(start + i * step);
    } 

    // make the output file
    std::ofstream outFile(filename);
    if(!outFile.is_open())
    {
      std::cerr<<"Unable to open file."<<std::endl;
      return;
    }

    outFile<<"# freq "; // header
    for(double R : resistance_grid)
    {
      outFile<<"Phase(R="<<R<<") "; // header 
    }
    outFile<<"\n";

    for(double freq : frequency_grid)
    {
      set_frequency(freq);
      outFile<<freq<<" ";
      for(double R : resistance_grid)
      {
        set_resistance(R);
        // get the current leaving the AC source
        complex I_0 = get_src_current();
        // the 'lag' of the current is positive so we multiply by -1
        double phase = -1.0*std::arg(I_0);
        outFile<<phase<<" "; // write the phase to the ouptut file 
      }
        outFile<<""<<std::endl;
    }
    // reset values
    set_resistance(1.0);
    set_frequency(1.0);

    outFile.close();
    std::cout<<"Phase Frequency Sweep data written to '"<<filename<<"' successfully."<<std::endl;
  }

};