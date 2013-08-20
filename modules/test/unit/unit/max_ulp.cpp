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
#include <nt2/sdk/unit/io.hpp>
#include <boost/type_traits/is_integral.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>

#include <cmath>
#include <vector>
#include <limits>
#include <typeinfo>
#include <iostream>

struct foo { double d; float f; char c; };
BOOST_FUSION_ADAPT_STRUCT(foo,(double,d)(float,f)(char,c));

using boost::fusion::operator<<;

template<class T> inline bool check_ulp_fundamental()
{
  T value(1), different_value;
  std::vector< nt2::details::failed_value<T,T> >  fails;

  different_value = value + 16*std::numeric_limits<T>::epsilon();

  std::cout << "Check for: " << typeid(T).name() << "\t";
  double u0 = 0;
  bool ok1 = nt2::unit::max_ulp(value,value,0.5,fails,u0);
  std::cout << "max_ulp(a,a) = " << u0 << "\t";
  std::cout << "nb of fails: " << fails.size() << "\t";

  fails.clear();
  double u1 = 0;
  bool ok2 = nt2::unit::max_ulp(value,different_value,0.5,fails, u1);
  std::cout << "max_ulp(a,b) = " << u1 << "\t";
  std::cout << "nb of fails: " << fails.size() << "\n";
  std::cout << ((!u0 && u1==8) ? "OK" : "NOT OK") << "\n";

  return ok1 && ok2 && !u0 && u1==8;
}

inline bool check_ulp_fusion_sequence()
{
  foo value = { 1.,1.f,'Z' };
  foo different_value = {1.,1.f,'Z'};
  std::vector< nt2::details::failed_value<foo,foo> >  fails;

  different_value.f = value.f + 16*std::numeric_limits<float>::epsilon();

  std::cout << "Check for: foo\t";
  double u0 = 0;
  bool ok1 = nt2::unit::max_ulp(value,value,0.5,fails,u0);
  std::cout << "max_ulp(a,a) = " << u0 << "\t";
  std::cout << "nb of fails: " << fails.size() << "\t";

  fails.clear();
  double u1 = 0;
  bool ok2 = nt2::unit::max_ulp(value,different_value,0.5,fails, u1);
  std::cout << "max_ulp(a,b) = " << u1 << "\t";
  std::cout << "nb of fails: " << fails.size() << "\n";
  std::cout << ((!u0 && u1==8) ? "OK" : "NOT OK") << "\n";

  return ok1 && ok2 && !u0 && u1==8;
}

template<class T> inline bool check_ulp_sequence()
{
  std::vector<T> values(17), different_values(17);
  std::vector< nt2::details::failed_value<T,T> >  fails;

  for(std::size_t i=0;i<values.size();++i)
    values[i] = different_values[i] = T(1);

  different_values[9] += 16*std::numeric_limits<T>::epsilon();
  different_values[7] += 5*std::numeric_limits<T>::epsilon();

  std::cout << "Check for: " << typeid(T).name() << "\t";
  double u0 = 0;
  bool ok1 = nt2::unit::max_ulp(values,values,0.5,fails,u0);
  std::cout << "max_ulp(a,a) = " << u0 << "\t";
  std::cout << "nb of fails: " << fails.size() << "\t";

  fails.clear();
  double u1 = 0;
  bool ok2 = nt2::unit::max_ulp(values,different_values,0.5,fails, u1);
  std::cout << "max_ulp(a,b) = " << u1 << "\t";
  std::cout << "nb of fails: " << fails.size() << "\n";
  std::cout << ((!u0 && u1==8) ? "OK" : "NOT OK")  << "\n";

  return ok1 && ok2 && (!u0 && u1==8);
}

template<class T> inline bool check_ulp_singular_sequence()
{
  std::vector<T> values(1);
  T different_values(1);

  std::vector< nt2::details::failed_value<T,T> >  fails;

  values[0] = T(1);

  different_values += 16*std::numeric_limits<T>::epsilon();

  std::cout << "Check for: " << typeid(T).name() << "\t";
  double u0 = 0;
  bool ok1 = nt2::unit::max_ulp(values,values,0.5,fails,u0);
  std::cout << "max_ulp(a,a) = " << u0 << "\t";
  std::cout << "nb of fails: " << fails.size() << "\t";

  fails.clear();
  double u1 = 0;
  bool ok2 = nt2::unit::max_ulp(values,different_values,0.5,fails, u1);
  std::cout << "max_ulp(a,b) = " << u1 << "\t";
  std::cout << "nb of fails: " << fails.size() << "\t";

  fails.clear();
  double u2 = 0;
  bool ok3 = nt2::unit::max_ulp(different_values,values,0.5,fails, u2);
  std::cout << "max_ulp(b,a) = " << u1 << "\t";
  std::cout << "nb of fails: " << fails.size() << "\n";
  std::cout << ((!u0 && u1==8 && u2==8) ? "OK" : "NOT OK")  << "\n";
  return ok1 && ok2 && ok3 && (!u0 && u1==8 && u2==8);
}

inline bool check_ulp_sequence_fusionsequence()
{
  foo values            = {1.,1.f,'A'};
  foo different_values  = {1.,1.f,'I'};
  std::vector<foo> seq(2), diff_seq(2);

  typedef nt2::details::max_ulp_ < std::vector<foo>, std::vector<foo> >::failure_type  f_t;
  std::vector< f_t >  fails;

  seq[0] = seq[1] = values;
  diff_seq[0] = values;
  diff_seq[1] = different_values;

  double u0 = 0;
  double u1 = 0;

  std::cout << "Check for foo :\t";
  bool ok1 = nt2::unit::max_ulp(seq,seq,0.5,fails,u0);
  std::cout << "max_ulp(a,a) = " << u0 << "\t";
  std::cout << "nb of fails: " << fails.size() << "\t";

  fails.clear();
  bool ok2 = nt2::unit::max_ulp(seq,diff_seq,0.5,fails, u1);
  std::cout << "max_ulp(a,b) = " << u1 << "\t";
  std::cout << "nb of fails: " << fails.size() << "\n";
  std::cout << ((!u0 && u1==8) ? "OK" : "NOT OK")  << "\n";
  return ok1 && ok2 && (!u0 && u1==8);
}

template<class T> inline bool check_ulp_sequence_sequence()
{
  std::vector<T> values(3), different_values(3);
  std::vector< std::vector<T> > seq(2), diff_seq(2);

  typedef typename nt2::details::max_ulp_ < std::vector< std::vector<T> >
                                          , std::vector< std::vector<T> >
                                          >::failure_type  f_t;
  std::vector< f_t >  fails;

  for(std::size_t i=0;i<values.size();++i)
    values[i] = different_values[i] = T(1);

  different_values[0] += 16*std::numeric_limits<T>::epsilon();
  different_values[2] += 5*std::numeric_limits<T>::epsilon();

  seq[0] = seq[1] = values;
  diff_seq[0] = values;
  diff_seq[1] = different_values;

  double u0 = 0;
  double u1 = 0;

  std::cout << "Check for: " << typeid(T).name() << "\t";
  bool ok1 = nt2::unit::max_ulp(seq,seq,0.5,fails,u0);
  std::cout << "max_ulp(a,a) = " << u0 << "\t";
  std::cout << "nb of fails: " << fails.size() << "\t";

  fails.clear();
  bool ok2 = nt2::unit::max_ulp(seq,diff_seq,0.5,fails, u1);
  std::cout << "max_ulp(a,b) = " << u1 << "\t";
  std::cout << "nb of fails: " << fails.size() << "\n";
  std::cout << ((!u0 && u1==8) ? "OK" : "NOT OK")  << "\n";
  return ok1 && ok2 && (!u0 && u1==8);
}

template<class T> inline bool check_ulp_invalid()
{
  T value(0), different_value;
  std::vector< nt2::details::failed_value<T,T> >  fails;

  different_value = std::numeric_limits<T>::quiet_NaN();

  std::cout << "Check for: " << typeid(T).name() << "\t";
  double u0 = 0;
  bool ok1 = nt2::unit::max_ulp(value,different_value,0.5,fails, u0);
  std::cout << "max_ulp(a,b) = " << u0 << "\t";
  std::cout << "nb of fails: " << fails.size() << "\t";

  fails.clear();
  double u1 = 0;
  bool ok2 = nt2::unit::max_ulp(different_value,value,0.5,fails, u1);
  std::cout << "max_ulp(a,b) = " << u1 << "\t";
  std::cout << "nb of fails: " << fails.size() << "\n";

  fails.clear();
  different_value = std::numeric_limits<T>::infinity();

  std::cout << "Check for: " << typeid(T).name() << "\t";
  double u2 = 0;
  bool ok3 = nt2::unit::max_ulp(value,different_value,0.5,fails, u2);
  std::cout << "max_ulp(a,b) = " << u2 << "\t";
  std::cout << "nb of fails: " << fails.size() << "\t";

  fails.clear();
  double u3 = 0;
  bool ok4 = nt2::unit::max_ulp(different_value,value,0.5,fails, u3);
  std::cout << "max_ulp(a,b) = " << u3 << "\t";
  std::cout << "nb of fails: " << fails.size() << "\n";

  bool stat =   (u0 != u0) && (u1 != u1)
            &&  (u2 == different_value) && (u3 == different_value)
            &&  ok1 && ok2 && ok3 && ok4;

  std::cout << ( stat ? "OK" : "NOT OK") << "\n";

  return stat;
}

NT2_UNIT_MAIN_SPEC int NT2_UNIT_MAIN(int, char**)
{
  std::cout << "Check for basic types\n";
  bool  check;

  check =   check_ulp_fundamental<double>()
        &&  check_ulp_fundamental<float>();

  std::cout << "\nCheck for Fusion Sequence\n";
  check = check_ulp_fusion_sequence() && check;

  std::cout << "\nCheck for Sequence\n";
  check =   check
        &&  check_ulp_sequence<double>()
        &&  check_ulp_sequence<float>();

  std::cout << "\nCheck for Singular Sequence\n";
  check =   check_ulp_singular_sequence<double>()
        &&  check_ulp_singular_sequence<float>()
        &&  check;

  std::cout << "\nCheck for Sequence of Sequence\n";
  check =   check_ulp_sequence_sequence<double>()
        &&  check_ulp_sequence_sequence<float>()
        &&  check;

  std::cout << "\nCheck for Sequence of Fusion Sequence\n";
  check =   check_ulp_sequence_fusionsequence()
        &&  check;

  std::cout << "\nCheck for Nan\n";
  check =   check_ulp_invalid<double>()
        &&  check_ulp_invalid<float>()
        &&  check;

  return check ? 0 : 1;
}
