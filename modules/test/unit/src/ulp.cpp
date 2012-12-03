//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012        MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <cmath>
#include <limits>
#include <algorithm>
#include <nt2/sdk/unit/details/ulp.hpp>
#include <nt2/sdk/unit/details/test_for_equality.hpp>

namespace nt2 { namespace details
{
  template<class T> T ulpdist(T a, T b)
  {
    if(nt2::unit::test_for_equality(a,b)) return T(0);

     int e1(0), e2(0);
     T m1 = std::frexp(a, &e1);
     T m2 = std::frexp(b, &e2);

     int expo = -std::max(e1,e2);

     T e = (e1 == e2)  ? std::abs(m1-m2)
                       : std::abs(std::ldexp(a,expo) - std::ldexp(b,expo));

     return e/std::numeric_limits<T>::epsilon();
  }

  double max_ulps(double a, double b)  { return ulpdist(a,b); }
  float  max_ulps(float  a, float b )  { return ulpdist(a,b); }
} }
