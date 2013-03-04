//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "boost.simd swar toolbox - comparator/simd Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of swar components in simd mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 24/02/2011
///
#include <boost/simd/toolbox/swar/include/functions/comparator.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <boost/fusion/tuple.hpp>
#include <boost/simd/include/functions/all.hpp>
#include <boost/simd/include/functions/max.hpp>
#include <boost/simd/include/functions/min.hpp>

#include <boost/type_traits/is_same.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/constants/real.hpp>
#include <boost/simd/include/constants/infinites.hpp>
#include <boost/simd/sdk/memory/is_aligned.hpp>
#include <boost/simd/sdk/memory/aligned_type.hpp>
#include <boost/simd/include/functions/load.hpp>

//COMMENTED
NT2_TEST_CASE_TPL ( comparator_real__3_0,  BOOST_SIMD_SIMD_REAL_TYPES)
{
  using boost::simd::comparator;
  using boost::simd::tag::comparator_;
  using boost::simd::load;
  using boost::simd::native;
  using boost::simd::meta::cardinal_of;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename boost::dispatch::meta::upgrade<T>::type   u_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                       ivT;
  typedef typename boost::dispatch::meta::call<comparator_(vT,vT,int)>::type r_t;
  typedef typename boost::dispatch::meta::call<comparator_(T,T,int)>::type sr_t;
  typedef typename boost::dispatch::meta::scalar_of<r_t>::type ssr_t;


//   // specific values tests
  typedef typename boost::dispatch::meta::strip<typename boost::fusion::result_of::at_c<r_t,0>::type>::type r_t0;
  typedef typename boost::dispatch::meta::strip<typename boost::fusion::result_of::at_c<r_t,1>::type>::type r_t1;
  typedef typename boost::dispatch::meta::strip<typename boost::fusion::result_of::at_c<r_t,2>::type>::type r_t2;
  {
    r_t res = comparator(boost::simd::Inf<vT>(), boost::simd::Inf<vT>(), 0);
    NT2_TEST_EQUAL( boost::fusion::get<0>(res), boost::simd::Inf<r_t0>());
    NT2_TEST_EQUAL( boost::fusion::get<1>(res), boost::simd::Inf<r_t1>());
    NT2_TEST_EQUAL( boost::fusion::get<2>(res), r_t2(0) );
  }
  {
    r_t res = comparator(boost::simd::Minf<vT>(), boost::simd::Minf<vT>(), 0);
    NT2_TEST_EQUAL( boost::fusion::get<0>(res), boost::simd::Minf<r_t0>());
    NT2_TEST_EQUAL( boost::fusion::get<1>(res), boost::simd::Minf<r_t0>());
    NT2_TEST_EQUAL( boost::fusion::get<2>(res), r_t2(0) );
  }
  {
    r_t res = comparator(boost::simd::Mone<vT>(), boost::simd::Mone<vT>(), 0);
    NT2_TEST_EQUAL( boost::fusion::get<0>(res), boost::simd::Mone<r_t0>());
    NT2_TEST_EQUAL( boost::fusion::get<1>(res), boost::simd::Mone<r_t0>());
    NT2_TEST_EQUAL( boost::fusion::get<2>(res), r_t2(0) );
  }
  {
    r_t res = comparator(boost::simd::Nan<vT>(), boost::simd::Nan<vT>(), 0);
    NT2_TEST_EQUAL( boost::fusion::get<0>(res), boost::simd::Nan<r_t0>());
    NT2_TEST_EQUAL( boost::fusion::get<1>(res), boost::simd::Nan<r_t0>());
    NT2_TEST_EQUAL( boost::fusion::get<2>(res), r_t2(0) );
  }
  {
    r_t res = comparator(boost::simd::One<vT>(), boost::simd::One<vT>(), 0);
    NT2_TEST_EQUAL( boost::fusion::get<0>(res), boost::simd::One<r_t0>());
    NT2_TEST_EQUAL( boost::fusion::get<1>(res), boost::simd::One<r_t0>());
    NT2_TEST_EQUAL( boost::fusion::get<2>(res), r_t2(0) );
  }
  {
    r_t res = comparator(boost::simd::Zero<vT>(), boost::simd::Zero<vT>(), 0);
    NT2_TEST_EQUAL( boost::fusion::get<0>(res), boost::simd::Zero<r_t0>());
    NT2_TEST_EQUAL( boost::fusion::get<1>(res), boost::simd::Zero<r_t0>());
    NT2_TEST_EQUAL( boost::fusion::get<2>(res), r_t2(0) );
  }
} // end of test for floating_

