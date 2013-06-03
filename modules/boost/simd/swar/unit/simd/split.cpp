//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/swar/include/functions/split.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <boost/simd/include/functions/splat.hpp>
#include <boost/simd/include/functions/enumerate.hpp>
#include <boost/simd/include/constants/valmin.hpp>
#include <boost/simd/include/constants/valmax.hpp>
#include <boost/fusion/include/vector_tie.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <boost/simd/sdk/simd/native.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

NT2_TEST_CASE_TPL( split, BOOST_SIMD_SPLITABLE_TYPES )
{
  using boost::simd::split;
  using boost::simd::tag::split_;
  using boost::simd::native;
  using boost::simd::splat;
  using boost::simd::enumerate;

  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>             vT;

  typedef typename boost::dispatch::meta::upgrade<T>::type uT;
  typedef typename boost::dispatch::meta::upgrade<vT>::type uvT;

  NT2_TEST_TYPE_IS( (typename boost::dispatch::meta::call<split_(vT)>::type)
                  , (std::pair<uvT,uvT>)
                  );


  uvT ref0, ref1;
  uint64_t i=0;
  for(; i!=uvT::static_size; ++i)
    ref0[i] = uT(i);
  for(; i!=uvT::static_size*2; ++i)
    ref1[i-uvT::static_size] = uT(i);

  {
    uvT out0, out1;
    split(enumerate<vT>(0), out0, out1);
    NT2_TEST_EQUAL(out0, ref0);
    NT2_TEST_EQUAL(out1, ref1);
  }

  {
    uvT out0, out1;
    out0 = split(enumerate<vT>(0), out1);
    NT2_TEST_EQUAL(out0, ref0);
    NT2_TEST_EQUAL(out1, ref1);
  }

  {
    uvT out0, out1;
    boost::fusion::vector_tie(out0,out1) = split(enumerate<vT>(0));
    NT2_TEST_EQUAL(out0, ref0);
    NT2_TEST_EQUAL(out1, ref1);
  }

  {
    std::pair<uvT,uvT> p;
    p = split(enumerate<vT>(0));
    NT2_TEST_EQUAL(p.first, ref0);
    NT2_TEST_EQUAL(p.second, ref1);
  }

  {
    uvT f,s;

    split(boost::simd::Valmax<vT>(), f, s);
    NT2_TEST_EQUAL(f, boost::simd::splat<uvT>(boost::simd::Valmax<T>()) );
    NT2_TEST_EQUAL(s, boost::simd::splat<uvT>(boost::simd::Valmax<T>()) );

    split(boost::simd::Valmin<vT>(), f, s);
    NT2_TEST_EQUAL(f, boost::simd::splat<uvT>(boost::simd::Valmin<T>()) );
    NT2_TEST_EQUAL(s, boost::simd::splat<uvT>(boost::simd::Valmin<T>()) );
  }
}
