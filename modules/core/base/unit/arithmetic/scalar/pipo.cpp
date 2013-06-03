#include <iostream>
template < class T >  T pip(const T & a); //{ return a; }
template < > double pip(const double & a){return 2*a; }
template < class T >  T pip(const T & a); //{ return a; }
template < > int pip(const int & a){return 4*a; }


int main(){
  std::cout << pip(1) << std::endl;
  std::cout << pip(1.0) << std::endl;
  return 0;
}
