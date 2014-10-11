//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/swar/include/functions/reverse.hpp>
#include <boost/simd/include/constants/signmask.hpp>
#include <boost/simd/include/constants/valmax.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <boost/dispatch/functor/meta/call.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

NT2_TEST_CASE_TPL ( reverse, BOOST_SIMD_SIMD_TYPES)
{
  using boost::simd::reverse;
  using boost::simd::tag::reverse_;
  using boost::simd::native;

  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>               vT;

  NT2_TEST_TYPE_IS(typename boost::dispatch::meta::call<reverse_(vT)>::type, vT);

  vT origin, reversed;

  for(std::size_t i=0; i < vT::static_size;++i)
  {
    origin[i]   = T(i);
    reversed[i] = T(vT::static_size-1-i);
  }

  origin[0] = reversed[vT::static_size-1] = boost::simd::Signmask<T>();
  origin[vT::static_size-1] = reversed[0] = boost::simd::Valmax<T>();

  NT2_TEST_EQUAL(reverse(origin),reversed);
}
