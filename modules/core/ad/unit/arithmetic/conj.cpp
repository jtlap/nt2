//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/ad.hpp>
#include <nt2/include/functions/ad_io.hpp>

#include <nt2/ad/arithmetic.hpp>

#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>


template < class T>
auto test(const T & x) -> decltype(conj(x))
{
  return conj(x);
}

using nt2::ad::valder;

NT2_TEST_CASE_TPL ( conj,  NT2_REAL_TYPES)
{
  valder<T> vx(2, 1); //take x derivative
  valder<T> r1 = test(vx);
  NT2_TEST_EQUAL(r1.der(), 1);
}



