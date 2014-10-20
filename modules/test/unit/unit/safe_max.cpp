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

#include <limits>
#include <typeinfo>
#include <iostream>

template<class T> inline bool check_isafe_max()
{
  T a(17), b(54);

  std::cout << "Check for: " << typeid(T).name() << "\n";
  T r1 = nt2::details::safe_max(a,b);
  bool ok1 = r1 == b;
  std::cout << "safe_max("<<a<<","<<b<<") = " << r1<< " : " << (ok1 ? "OK" : "NOT OK") << "\n";

  T r2 = nt2::details::safe_max(b,a);
  bool ok2 = r2 == b;
  std::cout << "safe_max("<<b<<","<<a<<") = " << r2<< " : " << (ok2 ? "OK" : "NOT OK") << "\n";

  std::cout << "\n";
  return ok1 && ok2;
}

template<class T> inline bool check_safe_max()
{
  T a(17), b(54), n(std::numeric_limits<T>::quiet_NaN());

  bool ok12 = check_isafe_max<T>();

  T r3 = nt2::details::safe_max(a,n);
  bool ok3 = (r3 != r3);
  std::cout << "safe_max("<<a<<","<<n<<") = " << n << " : " << (ok3 ? "OK" : "NOT OK") << "\n";

  T r4 = nt2::details::safe_max(n,b);
  bool ok4 = (r4 != r4);
  std::cout << "safe_max("<<n<<","<<b<<") = " << n << " : " << (ok4 ? "OK" : "NOT OK") << "\n";

  T r5 = nt2::details::safe_max(n,n);
  bool ok5 = (r5 != r5);
  std::cout << "safe_max("<<n<<","<<n<<") = " << n << " : " << (ok5 ? "OK" : "NOT OK") << "\n";

  std::cout << "\n";
  return ok12 && ok3 && ok4 && ok5;
}

NT2_UNIT_MAIN_SPEC int NT2_UNIT_MAIN(int, char**)
{
  bool check;

  std::cout << "Check for real safe_max\n";
  check = check_safe_max<double>();
  check = check_safe_max<float>() && check;

  std::cout << "Check for integral safe_max\n";
  check = check_isafe_max<int>() && check;
  check = check_isafe_max<short>() && check;
  check = check_isafe_max<char>() && check;

  return check ? 0 : 1;
}
