// PHYS30762 INTRO TO OOP PROJECT
// EXAMPLES CUBOID HEADER FILE 
// STUDENT ID: 11120960
// MAY 2025

#ifndef CUBOID_H
#define CUBOID_H

#include "../MNA/MNA.h"
#include<fstream>

class Cuboid : public Circuit // create Cuboid class that publicly inherits Circuit 
{
public:
  Cuboid() : Circuit()
  {
    // bottom
    set_ac_source("A", 1.0, 1);
    add_component<Resistor>("A", "B", 1.0, "Rab");
    add_component<Resistor>("B", "C", 1.0, "Rbc");
    add_component<Resistor>("C", "D", 1.0, "Rcd");
    add_component<Resistor>("D", "A", 1.0, "Rda");
    // top 
    add_component<Resistor>("G", "GND", 1.0, "Rhg");
    add_component<Resistor>("G", "F", 1.0, "Rgf");
    add_component<Resistor>("F", "E", 1.0, "Rfe");
    add_component<Resistor>("E", "GND", 1.0, "Regnd");
    // middle
    add_component<Resistor>("C", "GND", 1.0, "Rcgnd");
    add_component<Resistor>("B", "G", 1.0, "Rbg");
    add_component<Resistor>("D", "E", 1.0, "Rde");
    add_component<Resistor>("A", "F", 1.0, "Raf");
  }

  double get_total_resistance() const
  {
    // safely convert I_src to double (it should be > 0)
    double I_source = get_src_current().real(); 
    // to avoid division error 
    if(I_source < 1e-12)
    {
      std::cerr<<"Cuboid Resistance error: R = infty. Returning 1.0 ohms."<<std::endl;
      return 1.0;
    }
    else
    {
      // voltage should also be > 0
      double voltage = get_V0().real();
      // compute the total resistance
      return voltage / I_source; 
    }
  }

  void R_tot_resistance_sweep(const std::string& filename="Cuboid_ResistanceSweep.txt")
  {
    // horizontal resistor AB
    std::shared_ptr<Resistor> p_resistor = std::dynamic_pointer_cast<Resistor>(get_components()[0]); 
    // horizontal resistor BG 
    std::shared_ptr<Resistor> s_resistor = std::dynamic_pointer_cast<Resistor>(get_components()[9]);

    // create the grids 
    std::vector<double> R_grid; // resistance grid 
    std::vector<double> p_R_tot_grid; // total resistance for primary
    std::vector<double> s_R_tot_grid; // total resistance for secondary

    double start = 0.01;
    double end = 5.0;
    size_t N = 25;
    double step = (end - start) / (N - 1);

    // do the sweep for primary resistor
    for(size_t i = 0; i < N; ++i)
    {
      double R = start + step * i;
      p_resistor->set_resistance(R); // set the primary resistance
      double p_R_tot = get_total_resistance(); // compute total resistance 
      // store the data 
      R_grid.push_back(R); 
      p_R_tot_grid.push_back(p_R_tot);
    }

    // reset p_resistance
    p_resistor->set_resistance(1.0);
    R_grid.clear(); 

    // do the same thing but now for the secondary resistor 
    for(size_t i = 0; i < N; ++i)
    {
      double R = start + step * i;
      s_resistor->set_resistance(R);
      double s_R_tot = get_total_resistance();

      R_grid.push_back(R);
      s_R_tot_grid.push_back(s_R_tot);
    }

    // reset resistance
    s_resistor->set_resistance(1.0);

    // write the data to a file
    std::ofstream outFile(filename);
    if(outFile.is_open())
    {
      outFile<<"# R"<<" R_pri"<<" R_sec\n";
      for(size_t i = 0; i < R_grid.size(); ++i) // for all of the R values
      {
        outFile<<R_grid[i]<<" "<<p_R_tot_grid[i]<<" "<<s_R_tot_grid[i]<<"\n";
      }
      outFile.close();
      std::cout<<"Cuboid resistance sweep data saved to '"<<filename<<"'\n";
    }
    else
    {
      std::cerr << "Could not open file.\n";
    }
  }
};

#endif // CUBOID_H