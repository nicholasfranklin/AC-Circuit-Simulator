// PHYS30762 INTRO TO OOP PROJECT 
// MNA COMPONENT HEADER FILE
// STUDENT ID: 11120960
// MAY 2025 


#include"../include/Component.h"


// Constructors 
Component::Component() : type("None"), node_1(-1), node_2(-1), label("None") {} // node = -1 implies invalid

// label is "None" if unfilled 
Component::Component(
  const std::string& new_type, const int& new_node_1, 
  const int& new_node_2, const std::string& new_label) 
  : type(new_type), label(new_label)
  {
    set_node_1(new_node_1);
    set_node_2(new_node_2);
  } 


// Destructor
Component::~Component() = default;


// Copyers
Component::Component(const Component& other)
: type(other.type), node_1(other.node_1), node_2(other.node_2), label(other.label) {}

Component& Component::operator=(const Component& other)
{
  if(this != &other)
  {
    type = other.type;
    node_1 = other.node_1;
    node_2 = other.node_2;
    label = other.label;
  }
  return *this;
}


// Movers
Component::Component(Component&& other) noexcept
: type(std::move(other.type)), node_1(other.node_1), 
  node_2(other.node_2), label(std::move(other.label)) 
{
  // set other member variables to -1.
  other.node_1 = -1;  
  other.node_2 = -1;  
}

Component& Component::operator=(Component&& other) noexcept 
{
  if(this != &other)
  {
    type = std::move(other.type);
    node_1 = other.node_1;
    node_2 = other.node_2;
    label = std::move(other.label);
    // reset the moved-from object's state
    other.node_1 = -1;
    other.node_2 = -1;
  }
  return *this;
}


// set_type is disabled (new_type is an unused parameter)
void Component::set_type(const std::string& new_type)
{
  (void)new_type; // explicitly mark as unused so compiler doesn't raise error 
  std::cout<<"Warning: set_type disabled"<<std::endl; 
}

std::string Component::get_type() const {return type;}


// label setter and getter
void Component::set_label(const std::string& new_label) {label = new_label;} // not strict 

std::string Component::get_label() const {return label;}


// setters for the nodes (nodes cannot be < -1 and cannot be equal [unless =-1])
void Component::set_node_1(const int& n1)
{
  if(n1 == node_2 && node_2 != -1)
  {
    std::cerr<<type<<" node_1 error: node_1 cannot equal node_2 unless node_1 = node_2= -1."
             <<" node_1 is unchanged"<<std::endl; // do nothing 
  }
  else if(n1 < -1)
  {
    std::cerr<<type<<" node_1 error: node_1 needs to be >= -1"
             <<" node_1 is unchanged"<<std::endl; // do nothing 
  }
  else
  {
    node_1 = n1;
  }
}
// same function
void Component::set_node_2(const int& n2)
{
  if(n2 == node_1 && node_1 != -1)
  {
    std::cerr<<type<<" node_2 error: node_2 cannot equal node_1 unless node_1 = node_2= -1."
             <<" node_2 is unchanged"<<std::endl; // do nothing 
  }
  else if(n2 < -1)
  {
    std::cerr<<type<<" node_2 error: node_2 needs to be >= -1"
             <<" node_2 is unchanged"<<std::endl; // do nothing 
  }
  else
  {
    node_2 = n2;
  }
}

// node getters 
int Component::get_node_1() const {return node_1;}
int Component::get_node_2() const {return node_2;}


// get_admittance is pure virtual 
complex Component::get_impedence(const double& frequency) const {return 1./get_admittance(frequency);}



