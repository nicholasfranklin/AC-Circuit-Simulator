// PHYS30762 INTRO TO OOP PROJECT
// CIRCUIT IMPLEMENTATION FILE 
// STUDENT ID 11120960
// MAY 2025

#include"../include/Circuit.h"


// store correspondence between nodes as strings and nodes as integers 
int Circuit::get_node_id(const std::string& node_name) // private function 
{
  if(node_ids.count(node_name) == 0) // if node string not already defined 
  {
    int id = ++num_nodes; // increase num_nodes
    // store the new correspondance
    node_ids[node_name] = id; 
    id_to_node[id] = node_name;
  }
  return node_ids[node_name]; // return the int id 
}

// constructors
Circuit::Circuit() : components({}), ac_source(std::make_unique<AC_Source>()) {} // calls AC default constructor

Circuit::Circuit(const std::vector<std::shared_ptr<Component>>& new_components, std::unique_ptr<AC_Source> new_ac_source)
: components(new_components), ac_source(std::move(new_ac_source))
{
  if(nodes_invalid(components)) // check if the circuit is ill-defined 
  {
    std::cerr<<"Warning: Components have invalid nodes (must be >= 0)"<<std::endl;
  }
}


// destructor
Circuit::~Circuit() = default;


// copyers
Circuit::Circuit(const Circuit& other)
  : num_nodes(other.num_nodes),
    components(other.components),
    node_ids(other.node_ids),
    id_to_node(other.id_to_node),
    // create a new pointer to an AC source with the same properties
    ac_source(std::make_unique<AC_Source>(*other.ac_source)) {} 

Circuit& Circuit::operator=(const Circuit& other)
{
  if(this != &other)
  {
    num_nodes = other.num_nodes;
    components = other.components;
    node_ids = other.node_ids;
    id_to_node = other.id_to_node;
    // create a new pointer to an AC source with the same properties
    ac_source = std::make_unique<AC_Source>(*other.ac_source);
  }
  return *this;
}


// movers 
Circuit::Circuit(Circuit&& other) noexcept
  : num_nodes(std::move(other.num_nodes)), components(std::move(other.components)), node_ids(std::move(other.node_ids)), 
  id_to_node(std::move(other.id_to_node)), ac_source(std::move(other.ac_source)) {}

Circuit& Circuit::operator=(Circuit&& other) noexcept
{
  if(this != &other)
  {
    num_nodes = std::move(other.num_nodes); 
    components = std::move(other.components); 
    node_ids = std::move(other.node_ids);
    id_to_node = std::move(other.id_to_node); 
    ac_source = std::move(other.ac_source);
  }
  return *this;
}


// AC_Source functions (allows user to easily tune the AC source)
void Circuit::set_ac_source(const std::string& new_node, const double& new_V0, const double& new_freq)
{
  if(ac_source) // if the AC source exists
  {
    ac_source->set_source_node(get_node_id(new_node)); // node from str -> int
    ac_source->set_V0(new_V0);
    ac_source->set_frequency(new_freq);
  }
  else
  {
    std::cerr<<"Circuit error: AC source is not initialized."<<std::endl;
  }
}

void Circuit::set_ac_source(std::unique_ptr<AC_Source> new_ac_source)
{
  ac_source = std::move(new_ac_source); // move ownership 
}

// returns a reference (not a pointer)
const AC_Source& Circuit::get_ac_source() const {return *ac_source;} // ac_source never null

void Circuit::set_frequency(const double& freq) {ac_source->set_frequency(freq);} // errors handled in AC set_frequency
double Circuit::get_frequency() const {return ac_source->get_frequency();}

void Circuit::set_V0(const double& new_V0) {ac_source->set_V0(new_V0);} // errors handled in AC set_V0
complex Circuit::get_V0() const {return ac_source->get_V0();}

// components getters and setters 
void Circuit::set_components(const std::vector<std::shared_ptr<Component>>& new_comps)
{
  if(nodes_invalid(new_comps)) // check for ill-defined circuit 
  {
    std::cerr<<"Circuit set_components error: Components must have nodes not equal to -1. "
             <<" Leaving components unchanged"<<std::endl;  
  }
  else
  {
    // clear the nodes storage 
    node_ids.clear(); 
    id_to_node.clear();
    num_nodes = new_comps.size(); // set the nr of nodes to match the new components
    components = new_comps; // set the components
    // the new components won't have ids stored as strings, just ints
  }
}

std::vector<std::shared_ptr<Component>> Circuit::get_components() const
{
  if(is_empty())
  {
    std::cout<<"Circuit empty (no components)"<<std::endl;
  }
  return components;
}


// check if components vector is empty 
bool Circuit::is_empty() const {return true ? components.size() == 0 : false;}


// check nodes are valid
bool Circuit::nodes_invalid(const std::vector<std::shared_ptr<Component>>& comps) const
{
   for(const std::shared_ptr<Component>& comp : comps)
   {
     if(comp->get_node_1() == -1 || comp->get_node_2() == -1)
     {
        return true; // if they are invalid
     }
   }
   return false;
}


// solve circuit (private)
std::vector<complex> Circuit::solve_circuit() const
{
  // check for any potential numerical problems
  if(is_empty())
  {
    std::cerr<<"Circuit solve_circuit Error: Cannot solve empty circuit. "
            <<"Returning a vector containing zero."<<std::endl;
    return std::vector<complex>(0.0);
  }
  if(nodes_invalid(components))
  {
    std::cerr<<"Circuit solve_circuit Error: Nodes are invalid (must be >=0)"
             <<"Returning a vector containing zero."<<std::endl;
    return std::vector<complex>(0.0);
  }
  // the size of the matrix A
  int N = num_nodes + 1; // including the ground node adds 1

  // Create zero matrix A and zero vector z using LinAlg
  std::vector<std::vector<complex>> A = LinAlg<complex>::createZeroMatrix(N);
  std::vector<complex> z = LinAlg<complex>::createZeroVector(N);

  // Fill the matrix A based on components (0th row and col stay emtpy)
  for(const std::shared_ptr<Component>& comp : components)
  {
    int i = comp->get_node_1();
    int j = comp->get_node_2();
    complex y = comp->get_admittance(get_frequency());
    if(i != 0) A[i][i] += y; 
    if(j != 0) A[j][j] += y;
    if(i != 0 && j != 0)
    {
      A[i][j] -= y;
      A[j][i] -= y;
    } 
  }

  // Modify A for the source node (fill the 0th row and col)
  int source_node = ac_source->get_source_node(); 
  if(source_node >= 0 && source_node < N)
  {
    A[0][source_node] = 1.0; 
    A[source_node][0] = 1.0;
    z[0] = get_V0();  // first element of z (rest of elements are 0)
  }

  // Solve the system using LU decomposition
  std::vector<complex> output = LinAlg<complex>::LU_solve_x(A, z);
  return output;
}


// get source current
complex Circuit::get_src_current() const
{
  // the zeroth element is actually defined as going into the AC source
  return -1.0 * solve_circuit()[0]; 
}

std::vector<complex> Circuit::get_node_potentials() const
{
  std::vector<complex> solution = solve_circuit();
  solution[0] = 0.0; // set the GND to zero (was initially -I_srs)
  return solution;
}


// print results
void Circuit::print_data()
{
  std::cout<<"Printing Circuit Data"<<std::endl;
  double_hline();

  // check if circuit is empty first
  if(is_empty())
  {
    std::cout<<"Empty circuit"<<std::endl;
    return;
  }

  // get data  
  double frequency = get_frequency();
  std::vector<complex> node_potentials = get_node_potentials();

  // print nodal voltages 
  std::cout<<"Printing node data"<<std::endl;
  hline();
  for(size_t i = 0; i < node_potentials.size(); ++i) 
  { 
    if(id_to_node.count(i)) // if the node has a string ID
    {
      std::cout<<"Node "<<id_to_node[i]<<" has id: "<<i; 
    } 
    else 
    {
      std::cout<<"Node "<<i; // just print the id as an int
    }
    std::cout<< " with voltage V = "<<node_potentials[i]<<" V"<<std::endl;
  }
  hline();

  // print AC Source data
  std::cout<<"Printing AC source data"<<std::endl;
  hline();
  std::cout<<"AC source: \n"
           <<"  Voltage: "<<ac_source->get_V0()<<" V\n"
           <<"  Frequency: "<<frequency<<" Hz"<<std::endl;
  hline();

  // print component data
  std::cout<<"Printing component data"<<std::endl;
  hline();
  for(const std::shared_ptr<Component>& comp : components)
  {
    // get the componend data
    int n1 = comp->get_node_1();
    int n2 = comp->get_node_2();
    complex voltage_drop = node_potentials[n1] - node_potentials[n2]; // between node 1 and 2
    complex admittance = comp->get_admittance(frequency);
    complex impedence = comp->get_impedence(frequency);
    complex current = admittance * voltage_drop;

    // get the nodes formatted correctly 
    std::string node_1_str;
    std::string node_2_str;
    if(id_to_node.count(n1) && id_to_node.count(n2)) // if the nodes have str IDs
    {
        node_1_str = id_to_node[n1];
        node_2_str = id_to_node[n2];
    } 
    else
    {
        node_1_str = std::to_string(n1); // just write them as ints
        node_2_str = std::to_string(n2);
    }

    std::cout<<"Component label: "<<comp->get_label()<<"\n"
             <<"  Type: "<<comp->get_type()
             <<" between nodes "<<node_1_str<<" and "<<node_2_str<<"\n"
             <<"  Impedence: "<<impedence<<" Ohms \n"
             <<"  Voltage drop: "<<voltage_drop<<" V\n"
             <<"  Current: "<<current<<" A"<<std::endl;
  }
}
