//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 arithmetic toolbox - two_split/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// cover test behavior of arithmetic components in scalar mode
//////////////////////////////////////////////////////////////////////////////

#include <nt2/arithmetic/include/functions/two_split.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <vector>
#include <boost/fusion/include/std_pair.hpp>
#include <nt2/table.hpp>
#include <nt2/include/constants/valmin.hpp>
#include <nt2/include/constants/valmax.hpp>
#include <nt2/include/functions/remainder.hpp>
#include <nt2/include/functions/idivround.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/include/functions/idivround.hpp>

NT2_TEST_CASE_TPL ( two_split_real__1_0_1,  (float))
{

  using nt2::two_split;
  using nt2::tag::two_split_;
  typedef typename nt2::meta::call<two_split_(T)>::type r_t;
  typedef std::pair<T,T> wished_r_t;
  typedef typename nt2::meta::strip<typename boost::fusion::result_of::at_c<r_t,0>::type>::type r_t1;
  typedef typename nt2::meta::strip<typename boost::fusion::result_of::at_c<r_t,1>::type>::type r_t2;
  typedef double U;
  // return type conformity test
  NT2_TEST_TYPE_IS( r_t, wished_r_t );


  nt2::uint32_t NR = NT2_NB_RANDOM_TEST;
  std::vector<T> in1(NR);
  std::vector<r_t1> out1(NR);
  std::vector<r_t2> out2(NR), res1(NR);
  nt2::roll(in1, -1, 1);
  for(nt2::uint32_t i=0; i < NR ; ++i)
  {
    r_t r = two_split(in1[i]);
    out1[i] = boost::fusion::get<0>(r);
    out2[i] = boost::fusion::get<1>(r);
    res1[i] = T(U(out1[i])+U(out2[i]));
  }

  NT2_TEST_ULP_EQUAL(res1, in1, 0);
}

NT2_TEST_CASE_TPL ( two_split_real__1_0_2,  (double))
{

  using nt2::two_split;
  using nt2::tag::two_split_;
  typedef typename nt2::meta::call<two_split_(T)>::type r_t;
  typedef std::pair<T,T> wished_r_t;
  typedef typename nt2::meta::strip<typename boost::fusion::result_of::at_c<r_t,0>::type>::type r_t1;
  typedef typename nt2::meta::strip<typename boost::fusion::result_of::at_c<r_t,1>::type>::type r_t2;
  typedef long double U;
  // return type conformity test
  NT2_TEST_TYPE_IS( r_t, wished_r_t );


  nt2::uint32_t NR = NT2_NB_RANDOM_TEST;
  std::vector<T> in1(NR);
  std::vector<r_t1> out1(NR);
  std::vector<r_t2> out2(NR), res1(NR);
  nt2::roll(in1, -1, 1);
  for(nt2::uint32_t i=0; i < NR ; ++i)
  {
    r_t r = two_split(in1[i]);
    out1[i] = boost::fusion::get<0>(r);
    out2[i] = boost::fusion::get<1>(r);
    res1[i] = T(U(out1[i])+U(out2[i]));
  }

  NT2_TEST_ULP_EQUAL(res1, in1, 0);
}
