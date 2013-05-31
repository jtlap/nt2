//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/swar/include/functions/split_multiplies.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <boost/simd/include/functions/enumerate.hpp>
#include <boost/fusion/include/vector_tie.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <boost/simd/sdk/simd/native.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

NT2_TEST_CASE_TPL( split_multiplies, BOOST_SIMD_SPLITABLE_TYPES )
{
  using boost::simd::split_multiplies;
  using boost::simd::enumerate;
  using boost::simd::tag::split_multiplies_;
  using boost::simd::native;

  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>             vT;

  typedef typename boost::dispatch::meta::upgrade<T>::type uT;
  typedef typename boost::dispatch::meta::upgrade<vT>::type uvT;

  NT2_TEST_TYPE_IS( (typename boost::dispatch::meta::call<split_multiplies_(vT, vT)>::type)
                  , (std::pair<uvT,uvT>)
                  );

  uvT ref0, ref1;
  uint64_t i=0;
  for(; i!=uvT::static_size; ++i)
    ref0[i] = uT(i*(i+1));
  for(; i!=uvT::static_size*2; ++i)
    ref1[i-uvT::static_size] = uT(i*(i+1));

  {
    uvT out0, out1;
    split_multiplies(enumerate<vT>(0), enumerate<vT>(1), out0, out1);
    NT2_TEST_EQUAL(out0, ref0);
    NT2_TEST_EQUAL(out1, ref1);
  }

  {
    uvT out0, out1;
    out0 = split_multiplies(enumerate<vT>(0), enumerate<vT>(1), out1);
    NT2_TEST_EQUAL(out0, ref0);
    NT2_TEST_EQUAL(out1, ref1);
  }

  {
    uvT out0, out1;
    boost::fusion::vector_tie(out0,out1) = split_multiplies(enumerate<vT>(0), enumerate<vT>(1));
    NT2_TEST_EQUAL(out0, ref0);
    NT2_TEST_EQUAL(out1, ref1);
  }

  {
    std::pair<uvT,uvT> p;
    p = split_multiplies(enumerate<vT>(0), enumerate<vT>(1));
    NT2_TEST_EQUAL(p.first, ref0);
    NT2_TEST_EQUAL(p.second, ref1);
  }
}
