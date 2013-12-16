//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/include/functions/repeat_lower_half.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

NT2_TEST_CASE_TPL(repeat_lower_half, BOOST_SIMD_SIMD_TYPES)
{
  using boost::simd::native;
  using boost::simd::tag::repeat_lower_half_;
  using boost::simd::meta::cardinal_of;

  typedef BOOST_SIMD_DEFAULT_EXTENSION      ext_t;
  typedef native<T,ext_t>                      vT;

  NT2_TEST_TYPE_IS( typename boost::dispatch::meta
                                            ::call<repeat_lower_half_(vT)>::type
                  , vT
                  );

  const std::size_t card = cardinal_of<vT>::value;
  vT origin,ref;

  for(std::size_t i=0; i<card; ++i)
  {
    origin[i] = T(i+1);
    ref[i]    = i<(card/2) ? T(i+1) : T(i+1-card/2);
  }

  NT2_TEST_EQUAL(boost::simd::repeat_lower_half(origin),ref);
}
