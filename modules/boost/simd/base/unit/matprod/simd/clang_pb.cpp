//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <iostream>
#include <boost/simd/sdk/simd/io.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>

template < class A, class B, class R>
void  mul(const A &a, const B& b, R& r, size_t card)
{
  size_t H1 = card/2;
  size_t W1 = 2*card;
  size_t H2 = 2*card;
  size_t W2 = 2*2;
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

NT2_TEST_CASE_TPL ( clang_pb,BOOST_SIMD_SIMD_REAL_TYPES)
{
  using boost::simd::meta::cardinal_of;
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

  union trick8
  {
    T ta[8*card];
    boost::array<vT, 8 > va;
    trick8(){}
  };
  trick8 b;
  union trick2
  {
    T ta[card*2];
    boost::array<vT, 2 > va;
    trick2(){}
  };

   trick2 ref;

   for(size_t i=0; i <card*4*2 ; i++)
  {
    b.ta[i] = T(i+1);
  }
  std::cout << "b1 " << b.va << std::endl;
  boost::array<vT, 8 > bb = b.va;

  std::cout << "bb " << bb << std::endl;
  std::cout << "b2 " << b.va << std::endl;
  mul(a, b, ref, card);
  std::cout << "b3 " << b.va << std::endl;
  NT2_TEST_EQUAL(bb, b.va);
};

