//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012        MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/sdk/unit/details/main.hpp>
#include <nt2/sdk/unit/details/ulp.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <boost/type_traits/is_integral.hpp>

#include <cmath>
#include <vector>
#include <limits>
#include <typeinfo>
#include <iostream>

template<class T> bool check_ulp_fundamental()
{
  T value(1), different_value;

  different_value = value + 16*std::numeric_limits<T>::epsilon();

  std::cout << "Check for: " << typeid(T).name() << "\t";
  T u0     = nt2::unit::max_ulp(value,value);
  std::cout << "max_ulp(a,a) = " << int(u0) << "\t";
  T u1     = nt2::unit::max_ulp(value,different_value);
  std::cout << "max_ulp(a,b) = " << int(u1) << "\t";
  std::cout << ((!u0 && u1==8) ? "OK" : "NOT OK") << "\n";

  return !u0 && u1==8;
}

template<class T> bool check_ulp_sequence()
{
  std::vector<T> values(17), different_values(17);

  for(std::size_t i=0;i<values.size();++i)
    values[i] = different_values[i] = T(1);

  different_values[9] += 16*std::numeric_limits<T>::epsilon();
  different_values[7] += 5*std::numeric_limits<T>::epsilon();

  std::cout << "Check for: " << typeid(T).name() << "\t";
  T u0     = nt2::unit::max_ulp(values,values);
  std::cout << "max_ulp(a,a) = " << int(u0) << "\t";
  T u1     = nt2::unit::max_ulp(values,different_values);
  std::cout << "max_ulp(a,b) = " << int(u1) << "\t";
  std::cout << ((!u0 && u1==8) ? "OK" : "NOT OK")  << "\n";

  return (!u0 && u1==8);
}

NT2_UNIT_MAIN_SPEC int NT2_UNIT_MAIN(int argc, char* argv[])
{
  std::cout << "Check for basic types\n";
  bool  check =   check_ulp_fundamental<double>()
              &&  check_ulp_fundamental<float>();

  std::cout << "\nCheck for Sequence\n";
        check =   check_ulp_sequence<double>()
              &&  check_ulp_sequence<float>();

  return check ? 0 : 1;
}
