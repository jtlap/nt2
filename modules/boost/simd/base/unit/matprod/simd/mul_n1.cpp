//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/matprod/functions/mul_n1.hpp>
#include <boost/simd/matprod/functions/simd/common/mul_n1.hpp>

#include <boost/dispatch/functor/meta/call.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>
#include <boost/simd/sdk/simd/io.hpp>

#include <boost/simd/include/functions/sum.hpp>
#include <boost/simd/include/functions/enumerate.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>

#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/functions/make.hpp>
#include <nt2/table.hpp>

NT2_TEST_CASE_TPL ( mul_n1,  BOOST_SIMD_SIMD_REAL_TYPES)
{
  using boost::simd::meta::cardinal_of;
  using boost::simd::mul_n1;
  using boost::simd::tag::mul_n1_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  static const size_t card = cardinal_of<vT>::value;
//   static const int card = sizeof(vT)/sizeof(T);
  union trick
  {
    T ta[card*card];
    boost::array<vT, card > va;
    trick(){}
  };
  trick t;

  for(size_t i=0; i <card*card ; i++)
  {
    t.ta[i] = T(i+1);
  }
  boost::array<vT, card > a = t.va;
  vT x = boost::simd::enumerate<vT>(T(1), T(1));

  std::cout << "a " << a << std::endl;
  std::cout << "x " << x << std::endl;

  size_t s =  boost::simd::sum(boost::simd::enumerate<vT>(T(1), T(1))*boost::simd::enumerate<vT>(T(1), T(card)));
  vT res = boost::simd::enumerate<vT>(s, card*(card+1)/2);

  vT r = mul_n1(a, x);
  std::cout << "r   " << r << std::endl;
  std::cout << "res " << res << std::endl;
  NT2_TEST_EQUAL(r, res);

  vT v = boost::simd::enumerate<vT>(T(1), T(1));
  r = v;
  mul_n1(a, x, r);
  NT2_TEST_EQUAL(r, res+v);

  r = v;
  mul_n1(T(2.0), a, x, r);
  NT2_TEST_EQUAL(r, T(2.0)*res+v);

  r = v;
  mul_n1(T(2.0), a, x, T(0.5), r);
  NT2_TEST_EQUAL(r, T(2.0)*res+T(0.5)*v);


} // end of test for floating_

