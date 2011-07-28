//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 swar toolbox - comparator/simd Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of swar components in simd mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 24/02/2011
/// 
#include <nt2/toolbox/swar/include/comparator.hpp>
#include <nt2/include/functions/ulpdist.hpp>
#include <boost/fusion/tuple.hpp>
#include <nt2/include/functions/all.hpp>
#include <nt2/include/functions/max.hpp>
#include <nt2/include/functions/min.hpp>

#include <boost/type_traits/is_same.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <boost/simd/sdk/unit/tests.hpp>
#include <boost/simd/sdk/unit/module.hpp>
#include <boost/simd/sdk/memory/buffer.hpp>
#include <boost/simd/include/constants/real.hpp>
#include <boost/simd/include/constants/infinites.hpp>
#include <boost/simd/sdk/memory/is_aligned.hpp>
#include <boost/simd/sdk/memory/aligned_type.hpp>
#include <boost/simd/include/functions/load.hpp>

//COMMENTED
NT2_TEST_CASE_TPL ( comparator_real__3_0,  NT2_REAL_TYPES)
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
  double ulpd;
  ulpd=0.0; 


//   // specific values tests
  typedef typename boost::dispatch::meta::strip<typename boost::fusion::result_of::at_c<r_t,0>::type>::type r_t0;
  typedef typename boost::dispatch::meta::strip<typename boost::fusion::result_of::at_c<r_t,1>::type>::type r_t1;
  typedef typename boost::dispatch::meta::strip<typename boost::fusion::result_of::at_c<r_t,2>::type>::type r_t2;
  {
    r_t res = comparator(nt2::Inf<vT>(), nt2::Inf<vT>(), 0);
    NT2_TEST_EQUAL( boost::fusion::get<0>(res), nt2::Inf<r_t0>());
    NT2_TEST_EQUAL( boost::fusion::get<1>(res), nt2::Inf<r_t1>());
    NT2_TEST_EQUAL( boost::fusion::get<2>(res), 0);
  }
  {
    r_t res = comparator(nt2::Minf<vT>(), nt2::Minf<vT>(), 0);
    NT2_TEST_EQUAL( boost::fusion::get<0>(res), nt2::Minf<r_t0>());
    NT2_TEST_EQUAL( boost::fusion::get<1>(res), nt2::Minf<r_t0>());
    NT2_TEST_EQUAL( boost::fusion::get<2>(res), 0);
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
    NT2_TEST_EQUAL( boost::fusion::get<2>(res), 0);
  }
  {
    r_t res = comparator(nt2::One<vT>(), nt2::One<vT>(), 0);
    NT2_TEST_EQUAL( boost::fusion::get<0>(res), nt2::One<r_t0>());
    NT2_TEST_EQUAL( boost::fusion::get<1>(res), nt2::One<r_t0>());
    NT2_TEST_EQUAL( boost::fusion::get<2>(res), 0);
  }
  {
    r_t res = comparator(nt2::Zero<vT>(), nt2::Zero<vT>(), 0);
    NT2_TEST_EQUAL( boost::fusion::get<0>(res), nt2::Zero<r_t0>());
    NT2_TEST_EQUAL( boost::fusion::get<1>(res), nt2::Zero<r_t0>());
    NT2_TEST_EQUAL( boost::fusion::get<2>(res), 0);
  }
} // end of test for real_
 
