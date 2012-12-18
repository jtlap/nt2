//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012        MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/sdk/unit/details/ulp.hpp>
#include <cmath>

namespace nt2 { namespace details
{
  template<class T> double ulps(T a0, T a1)
  {
    if( (a0 == a1) || ((a0!=a0) && (a1!=a1)) ) return 0.;

    int e1,e2;
    T   m1,m2;
    m1 = std::frexp(a0, &e1);
    m2 = std::frexp(a1, &e2);

    int expo = -std::max(e1, e2);
    T e = (e1 == e2)  ? std::abs(m1-m2)
                      :   std::abs(std::ldexp(a0, expo)- std::ldexp(a1, expo));

    return double(e/std::numeric_limits<T>::epsilon());
  }

  NT2_TEST_UNIT_DECL double max_ulps(double a, double b) { return ulps(a,b); }
  NT2_TEST_UNIT_DECL double max_ulps(float  a, float b ) { return ulps(a,b); }
} }
