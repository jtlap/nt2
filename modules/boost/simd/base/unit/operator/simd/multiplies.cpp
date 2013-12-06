//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/operator/include/functions/multiplies.hpp>
#include <boost/simd/include/functions/enumerate.hpp>
#include <boost/simd/include/functions/splat.hpp>

#include <boost/dispatch/functor/meta/call.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>
#include <boost/simd/sdk/simd/io.hpp>

#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/constants/mone.hpp>
#include <boost/simd/include/constants/mzero.hpp>
#include <boost/simd/include/constants/two.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/simd/include/constants/inf.hpp>
#include <boost/simd/include/constants/minf.hpp>
#include <boost/simd/include/constants/nan.hpp>


NT2_TEST_CASE_TPL ( multiplies_real,  BOOST_SIMD_SIMD_REAL_TYPES)
{
  using boost::simd::multiplies;
  using boost::simd::tag::multiplies_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  typedef typename boost::dispatch::meta::call<multiplies_(vT,vT)>::type r_t;

  // specific values tests
  NT2_TEST_EQUAL(multiplies(boost::simd::Inf<vT>(), boost::simd::Inf<vT>()), boost::simd::Inf<r_t>());
  NT2_TEST_EQUAL(multiplies(boost::simd::Minf<vT>(), boost::simd::Minf<vT>()), boost::simd::Inf<r_t>());
  NT2_TEST_EQUAL(multiplies(boost::simd::Nan<vT>(), boost::simd::Nan<vT>()), boost::simd::Nan<r_t>());
  NT2_TEST_EQUAL(multiplies(boost::simd::One<vT>(),boost::simd::Zero<vT>()), boost::simd::Zero<r_t>());
  NT2_TEST_EQUAL(multiplies(boost::simd::Zero<vT>(), boost::simd::Zero<vT>()), boost::simd::Zero<r_t>());
  NT2_TEST_EQUAL(multiplies(boost::simd::Mzero<vT>(), boost::simd::One<vT>()), boost::simd::Mzero<r_t>());
} // end of test for floating_

NT2_TEST_CASE_TPL ( multiplies_integer,  BOOST_SIMD_SIMD_INTEGRAL_TYPES)
{
  using boost::simd::Valmin;
  using boost::simd::Valmax;
  using boost::simd::splat;
  using boost::simd::enumerate;
  using boost::simd::multiplies;
  using boost::simd::tag::multiplies_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  typedef typename boost::dispatch::meta::call<multiplies_(vT,vT)>::type r_t;

  T step = (Valmax<T>() - Valmin<T>() ) / 8*(vT::static_size-1);
  vT v = enumerate<vT>( Valmin<T>()/4, step );
  vT w = enumerate<vT>( Valmax<T>()/4, -step );

  vT ref;
  for(std::size_t i=0;i<vT::static_size;++i)
    ref[i] = v[i] * w[i];

  // specific values tests
  NT2_TEST_EQUAL(multiplies(boost::simd::One<vT>(), boost::simd::One<vT>()), boost::simd::One<r_t>());
  NT2_TEST_EQUAL(multiplies(boost::simd::One<vT>(),boost::simd::Zero<vT>()), boost::simd::Zero<r_t>());
  NT2_TEST_EQUAL(multiplies(boost::simd::Zero<vT>(), boost::simd::Zero<vT>()), boost::simd::Zero<r_t>());
  NT2_TEST_EQUAL(multiplies(boost::simd::Mzero<vT>(), boost::simd::One<vT>()), boost::simd::Mzero<r_t>());
  NT2_TEST_EQUAL(multiplies(v,w), ref);
}
