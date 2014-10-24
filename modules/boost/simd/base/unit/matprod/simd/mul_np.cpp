//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/matprod/functions/mul_np.hpp>
#include <boost/simd/matprod/functions/simd/common/mul_np.hpp>

#include <boost/dispatch/functor/meta/call.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>
#include <boost/simd/sdk/simd/io.hpp>

#include <boost/simd/include/functions/sum.hpp>
#include <boost/simd/include/functions/enumerate.hpp>
#include <boost/simd/include/functions/splat.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>

#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/functions/make.hpp>
#include <nt2/table.hpp>

NT2_TEST_CASE_TPL ( mul_n1,  BOOST_SIMD_SIMD_REAL_TYPES)
{
  using boost::simd::meta::cardinal_of;
  using boost::simd::mul_np;
  using boost::simd::tag::mul_np_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  static const size_t card = cardinal_of<vT>::value;
  static const int P = 3;

  union trickN
  {
    T ta[card*card];
    boost::array<vT, card > va;
    trickN(){}
  };
  union trickP
  {
    T ta[card*P];
    boost::array<vT, P > va;
    trickP(){}
  };
  trickN t;
  trickP v, vr, vrref;
  trickP offset, res1, res2, res3;

  for(size_t i=0; i <P ; i++)
  {
    v.va[i] = boost::simd::splat<vT>(T(i+1));
    offset.va[i] = boost::simd::enumerate<vT>(T(i+1), T(1));
  }
  for(size_t i=0; i <card*card ; i++)
  {
    t.ta[i] = T(i+1);
  }
  boost::array<vT, card > a = t.va;


  boost::array<vT, P >    x = v.va;


  std::cout << "a " << a << std::endl;
  std::cout << "x " << x << std::endl;

  for(size_t c=0; c < P ; c++)
  {
    for(size_t l=0; l <card ; l++)
    {
      vr.ta[l+card*c] = 0;
      for(size_t k=0; k <card ; k++)
      {
        vr.ta[l+card*c] +=t.ta[l+card*k]*v.ta[c*card+k];
      }
    }
  }
  vrref.va = vr.va;
  boost::array<vT, P >    res = vr.va;

  boost::array<vT, P >    r = mul_np(a, x);
  std::cout << "r   " << r << std::endl;
  std::cout << "res " << res << std::endl;
  NT2_TEST_EQUAL(r, res);
  for(size_t i=0; i <P ; i++)
  {
    vr.va[i] =  offset.va[i];
    res1.va[i] = vrref.va[i]+ offset.va[i];
    res2.va[i] = T(2.0)*vrref.va[i]+ offset.va[i];
    res3.va[i] = T(2.0)*vrref.va[i]+ T(0.5)*offset.va[i];
  }

  r = offset.va;
  mul_np(a, x, r);

  NT2_TEST_EQUAL(r, res1.va);

  r = offset.va;
  mul_np(T(2.0), a, x, r);
  NT2_TEST_EQUAL(r, res2.va);

  r = offset.va;
  mul_np(T(2.0), a, x, T(0.5), r);
  NT2_TEST_EQUAL(r, res3.va);


} // end of test for floating_

