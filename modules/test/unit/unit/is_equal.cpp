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
#include <nt2/sdk/unit/details/test_for_equality.hpp>

#include <vector>
#include <typeinfo>
#include <iostream>

template<class T> bool check_equal_fundamental()
{
  T value(42), different_value(21);

  std::cout << "Check for: " << typeid(T).name() << "\t";
  bool same     = nt2::unit::test_for_equality(value,value);
  std::cout << "test_for_equality(a,a) = " << std::boolalpha << same << "\t";
  bool not_same = nt2::unit::test_for_equality(value,different_value);
  std::cout << "test_for_equality(a,b) = " << std::boolalpha << not_same << "\t";
  std::cout << ((same && !not_same) ? "OK" : "NOT OK") << "\n";

  return same && !not_same;
}

template<class T> bool check_equal_sequence()
{
  std::vector<T> values(17), different_values(17);

  for(std::size_t i=0;i<values.size();++i)
    values[i] = different_values[i] = T(1+i);

  different_values[7] = T(99);

  std::cout << "Check for: " << typeid(T).name() << "\t";
  bool same     = nt2::unit::test_for_equality(values,values);
  std::cout << "test_for_equality(a,a) = " << std::boolalpha << same << "\t";
  bool not_same = nt2::unit::test_for_equality(values,different_values);
  std::cout << "test_for_equality(a,b) = " << std::boolalpha << not_same << "\t";
  std::cout << ((same && !not_same) ? "OK" : "NOT OK")  << "\n";

  return same && !not_same;
}

NT2_UNIT_MAIN_SPEC int NT2_UNIT_MAIN(int argc, char* argv[])
{
  std::cout << "Check for basic types\n";
  bool  check =  check_equal_fundamental<double>();
        check =  check_equal_fundamental<float>()           && check;
        check =  check_equal_fundamental<char>()            && check;
        check =  check_equal_fundamental<short>()           && check;
        check =  check_equal_fundamental<int>()             && check;
        check =  check_equal_fundamental<unsigned char>()   && check;
        check =  check_equal_fundamental<unsigned short>()  && check;
        check =  check_equal_fundamental<unsigned int>()    && check;

  std::cout << "\nCheck for Sequence\n";
  check =  check_equal_sequence<double>()         && check;
  check =  check_equal_sequence<float>()          && check;
  check =  check_equal_sequence<char>()           && check;
  check =  check_equal_sequence<short>()          && check;
  check =  check_equal_sequence<int>()            && check;
  check =  check_equal_sequence<unsigned char>()  && check;
  check =  check_equal_sequence<unsigned short>() && check;
  check =  check_equal_sequence<unsigned int>()   && check;

  return check ? 0 : 1;
}
