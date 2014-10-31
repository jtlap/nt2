//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/matprod/functions/transhn.hpp>
#include <boost/simd/matprod/functions/simd/common/transhn.hpp>

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

template < class A, class R>
void  tra(const A &a,  R& r, size_t card)
{
  size_t h = card/2;
  size_t w = card*2;
  for(size_t c=0; c < card*2 ; c++)
  {
    for(size_t l=0; l < card/2 ; l++)
    {
      r.ta[l+h*c] = a.ta[c+l*w];
    }
  }
}


NT2_TEST_CASE_TPL ( transhn,BOOST_SIMD_SIMD_REAL_TYPES)
{
  using boost::simd::meta::cardinal_of;
  using boost::simd::transhn;
  using boost::simd::tag::transhn_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  static const size_t card = cardinal_of<vT>::value;


  union trickN
  {
    T ta[card*card];
    boost::array<vT, card > va;
    trickN(){}
  };
  trickN a;

  for(size_t i=0; i <card*card ; i++)
  {
    a.ta[i] = T(i+1);
  }
  std::cout << "a " << a.va << std::endl;

  boost::array<vT, card > aa =  a.va;
  boost::array<vT, card > r = transhn(aa);
  trickN res;
  tra(a, res, card);
   std::cout << "res   " << res.va << std::endl;
  boost::array<vT, card > ref = res.va;

   std::cout << "r   " << r << std::endl;
   std::cout << "ref " << ref  << std::endl;
   NT2_TEST_EQUAL(r, ref);

} // end of test for floating_


