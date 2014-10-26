//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/matprod/functions/mul_hn.hpp>
#include <boost/simd/matprod/functions/simd/common/mul_hn.hpp>

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

template < class A, class B, class R>
void  mul(const A &a, const B& b, R& r, size_t card)
{
  size_t H1 = card/2;
  size_t W1 = 2*card;
  size_t H2 = 2*card;
  size_t W2 = 2;
  for(size_t c=0; c < W2 ; c++)
  {
    for(size_t l=0; l < H2 ; l++)
    {
      r.ta[l+H1*c] = 0;
      for(size_t k=0; k <W1 ; k++)
      {
        r.ta[l+H1*c] += a.ta[l+H1*k]*b.ta[k+H2*c];
      }
    }
  }
}


NT2_TEST_CASE_TPL ( mul_hn,BOOST_SIMD_SIMD_REAL_TYPES)
{
  using boost::simd::meta::cardinal_of;
  using boost::simd::mul_hn;
  using boost::simd::tag::mul_hn_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  static const size_t card = cardinal_of<vT>::value;
//   static const int card = sizeof(vT)/sizeof(T);


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

  union trick4
  {
    T ta[4*card];
    boost::array<vT, 4 > va;
    trick4(){}
  };
  trick4 b;

  for(size_t i=0; i <card*4 ; i++)
  {
    b.ta[i] = T(i+1);
  }
  std::cout << "b1 " << b.va << std::endl;

  union trick1
  {
    T ta[card];
    boost::array<vT, 1 > va;
    trick1(){}
  };

   trick1 ref;
  boost::array<vT, 4 > bb = b.va;
  boost::array<vT, card > aa = a.va;

  std::cout << "b2 " << b.va << std::endl;
  mul(a, b, ref, card);
  std::cout << "b3 " << b.va << std::endl;
  std::cout << "bb " << bb << std::endl;

  std::cout << "ref " << ref.va  << std::endl;

   vT res = ref.va[0];
   vT r = mul_hn(aa, bb);
   std::cout << "r   " << r << std::endl;
   std::cout << "ref " << ref.va  << std::endl;
   NT2_TEST_EQUAL(r, res);

   vT v = boost::simd::enumerate<vT>(T(1), T(1));
   r = v;
   mul_hn(aa, bb, r);
   NT2_TEST_EQUAL(r, res+v);

  r = v;
  mul_hn(T(2.0), aa, bb, r);
  NT2_TEST_EQUAL(r, T(2.0)*res+v);

  r = v;
  mul_hn(T(2.0), aa, bb, T(0.5), r);
  NT2_TEST_EQUAL(r, T(2.0)*res+T(0.5)*v);


} // end of test for floating_

