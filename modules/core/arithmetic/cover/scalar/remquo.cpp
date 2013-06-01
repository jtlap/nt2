//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 arithmetic toolbox - remquo/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// cover test behavior of arithmetic components in scalar mode
//////////////////////////////////////////////////////////////////////////////

#include <nt2/arithmetic/include/functions/remquo.hpp>
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
#include <boost/simd/sdk/simd/io.hpp>

template < class T1, class T2>   std::ostream&
operator<<(std::ostream& os, std::pair<T1, T2> const& xpr)
{
  os << "[" << xpr.first << ",  " << xpr.second << "]";
  return os;
}


NT2_TEST_CASE_TPL ( remquo_real__1_0_1,  NT2_REAL_TYPES)
{

  using nt2::remquo;
  using nt2::tag::remquo_;
  typedef typename nt2::meta::call<remquo_(T, T)>::type r_t;
  typedef std::pair<T,typename nt2::meta::as_integer<T,signed>::type> wished_r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS( r_t, wished_r_t );


  nt2::uint32_t NR = NT2_NB_RANDOM_TEST;
  std::vector<T> in1(NR), in2(NR);
  std::vector<r_t> ref(NR);
  nt2::roll(in1, nt2::Valmin<T>()/2, nt2::Valmax<T>()/2);
  nt2::roll(in2, nt2::Valmin<T>()/2, nt2::Valmax<T>()/2);
  for(nt2::uint32_t i=0; i < NR ; ++i)
  {
    ref[i].first = nt2::remainder(in1[i], in2[i]);
    ref[i].second = nt2::idivround(in1[i], in2[i]);
  }

 NT2_COVER_ULP_EQUAL(remquo_, ((T, in1))((T, in2)), ref, 0);
}
