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
#include <nt2/sdk/unit/tests/cover.hpp>
#include <nt2/include/native.hpp>
#include <nt2/include/functions/plus.hpp>
#include <nt2/include/functions/divides.hpp>
#include <iostream>
#include <vector>

// Hand-made deactivation of assertions
namespace boost
{
  void assertion_failed_msg ( char const*, char const*
                            , char const*, char const*, long
                            )
  {}
}

struct some_functor
{
  template<typename Sig> struct result;
  template<typename This, class T>
  struct result<This(T)> : boost::dispatch::meta::strip<T> {};

  template<typename T>
  T operator()(T const& x)
  {
    return x/(x+1);
  }
};

NT2_UNIT_MAIN_SPEC int NT2_UNIT_MAIN(int argc, char* argv[])
{
  std::vector<float> a(64),b(64),c(64);

  for(int i=0;i<64;++i)
  {
    a[i] = 1+i;
    b[i] = i/10.f;
  }

  typedef boost::simd::native<float,BOOST_SIMD_DEFAULT_EXTENSION> nT;

  for(int i=0;i<64;++i)
  {
    c[i] = a[i]+b[i];
  }

  std::vector<float> c2 = c;

  c[5]  = 9;
  c[7]  = 5;
  c[12] = 6;

  NT2_COVER_ULP_EQUAL(nt2::tag::plus_, ((float,a))((float,b)), c, 0.5);
  NT2_COVER_ULP_EQUAL(nt2::tag::plus_, ((nT,a))((nT,b)), c, 0.5);
  NT2_COVER_ULP_EQUAL(nt2::tag::plus_, ((nT,a))((nT,b)), c2, 0.5);

  for(int i=0;i<64;++i)
  {
    c[i] = a[i]/(1.f + a[i]);
  }

  c2 = c;
  c[32] = 0;

  NT2_COVER_FN_ULP_EQUAL(some_functor(), ((nT,a)), c, 0.5);
  NT2_COVER_FN_ULP_EQUAL(some_functor(), ((nT,a)), c2, 0.5);

  return 0;
}
