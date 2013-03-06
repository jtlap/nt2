//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 swar toolbox - comparator/simd Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of swar components in simd mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 24/02/2011
///
#include <nt2/toolbox/swar/include/functions/comparator.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/fusion/tuple.hpp>
#include <nt2/include/functions/all.hpp>
#include <nt2/include/functions/max.hpp>
#include <nt2/include/functions/min.hpp>

#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/meta/as_floating.hpp>
#include <nt2/sdk/meta/as_signed.hpp>
#include <nt2/sdk/meta/upgrade.hpp>
#include <nt2/sdk/meta/downgrade.hpp>
#include <nt2/sdk/meta/scalar_of.hpp>
#include <boost/dispatch/meta/as_floating.hpp>
#include <boost/type_traits/common_type.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/memory/buffer.hpp>
#include <nt2/include/constants/real.hpp>
#include <nt2/include/constants/infinites.hpp>
#include <nt2/sdk/meta/cardinal_of.hpp>
#include <nt2/include/functions/splat.hpp>
#include <nt2/include/functions/load.hpp>
#include <nt2/toolbox/constant/constant.hpp>

//COMMENTED
NT2_TEST_CASE_TPL ( comparator_real__3_0,  NT2_SIMD_REAL_TYPES)
{
  using nt2::comparator;
  using nt2::tag::comparator_;
  using nt2::load;
  using boost::simd::native;
  using nt2::meta::cardinal_of;
  typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename nt2::meta::upgrade<T>::type   u_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                       ivT;
  typedef typename nt2::meta::call<comparator_(vT,vT,int)>::type r_t;
  typedef typename nt2::meta::call<comparator_(T,T,int)>::type sr_t;
  typedef typename nt2::meta::scalar_of<r_t>::type ssr_t;
  double ulpd;
  ulpd=0.0;


//   // specific values tests
  typedef typename nt2::meta::strip<typename boost::fusion::result_of::at_c<r_t,0>::type>::type r_t0;
  typedef typename nt2::meta::strip<typename boost::fusion::result_of::at_c<r_t,1>::type>::type r_t1;
  typedef typename nt2::meta::strip<typename boost::fusion::result_of::at_c<r_t,2>::type>::type r_t2;
  {
    r_t res = comparator(nt2::Inf<vT>(), nt2::Inf<vT>(), 0);
    NT2_TEST_EQUAL( boost::fusion::get<0>(res), nt2::Inf<r_t0>());
    NT2_TEST_EQUAL( boost::fusion::get<1>(res), nt2::Inf<r_t1>());
    NT2_TEST_EQUAL( boost::fusion::get<2>(res), false);
  }
  {
    r_t res = comparator(nt2::Minf<vT>(), nt2::Minf<vT>(), 0);
    NT2_TEST_EQUAL( boost::fusion::get<0>(res), nt2::Minf<r_t0>());
    NT2_TEST_EQUAL( boost::fusion::get<1>(res), nt2::Minf<r_t0>());
    NT2_TEST_EQUAL( boost::fusion::get<2>(res), false);
  }
  {
    r_t res = comparator(nt2::Mone<vT>(), nt2::Mone<vT>(), 0);
    NT2_TEST_EQUAL( boost::fusion::get<0>(res), nt2::Mone<r_t0>());
    NT2_TEST_EQUAL( boost::fusion::get<1>(res), nt2::Mone<r_t0>());
    NT2_TEST_EQUAL( boost::fusion::get<2>(res), 0);
  }
  {
    r_t res = comparator(nt2::Nan<vT>(), nt2::Nan<vT>(), 0);
    NT2_TEST_EQUAL( boost::fusion::get<0>(res), nt2::Nan<r_t0>());
    NT2_TEST_EQUAL( boost::fusion::get<1>(res), nt2::Nan<r_t0>());
    NT2_TEST_EQUAL( boost::fusion::get<2>(res), false);
  }
  {
    r_t res = comparator(nt2::One<vT>(), nt2::One<vT>(), 0);
    NT2_TEST_EQUAL( boost::fusion::get<0>(res), nt2::One<r_t0>());
    NT2_TEST_EQUAL( boost::fusion::get<1>(res), nt2::One<r_t0>());
    NT2_TEST_EQUAL( boost::fusion::get<2>(res), false);
  }
  {
    r_t res = comparator(nt2::Zero<vT>(), nt2::Zero<vT>(), 0);
    NT2_TEST_EQUAL( boost::fusion::get<0>(res), nt2::Zero<r_t0>());
    NT2_TEST_EQUAL( boost::fusion::get<1>(res), nt2::Zero<r_t0>());
    NT2_TEST_EQUAL( boost::fusion::get<2>(res), false);
  }
} // end of test for floating_

