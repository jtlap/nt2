//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 boost.simd.swar toolbox - comparator/simd Mode"

//////////////////////////////////////////////////////////////////////////////
// cover test behavior of boost.simd.swar components in simd mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 24/02/2011
/// 
#include <boost/simd/toolbox/swar/include/functions/comparator.hpp>
#include <boost/simd/include/functions/ulpdist.hpp>
#include <boost/simd/include/functions/max.hpp>
#include <boost/fusion/tuple.hpp>
#include <boost/simd/include/functions/all.hpp>
#include <boost/simd/include/functions/max.hpp>
#include <boost/simd/include/functions/min.hpp>

#include <boost/simd/include/functions/all.hpp>
#include <boost/simd/include/functions/max.hpp>
#include <boost/simd/include/functions/min.hpp>

#include <boost/type_traits/is_same.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/memory/buffer.hpp>
#include <boost/simd/toolbox/constant/constant.hpp>
#include <boost/simd/sdk/memory/is_aligned.hpp>
#include <boost/simd/sdk/memory/aligned_type.hpp>
#include <boost/simd/include/functions/load.hpp>
#include <boost/simd/toolbox/constant/constant.hpp>


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
  typedef typename boost::dispatch::meta::call<comparator_(vT,vT,iT)>::type r_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type sr_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type ssr_t;
  double ulpd;
  ulpd=0.0;

  // random verifications
  static const nt2::uint32_t NR = NT2_NB_RANDOM_TEST;
  {
    NT2_CREATE_BUF(tab_a0,T, NR, boost::simd::Valmin<T>(), boost::simd::Valmax<T>());
    NT2_CREATE_BUF(tab_a1,T, NR, boost::simd::Valmin<T>(), boost::simd::Valmax<T>());
    NT2_CREATE_BUF(tab_a2,iT, NR, iT(0), iT(1));
    double ulp0, ulpd ; ulpd=ulp0=0.0;
    for(nt2::uint32_t j = 0; j < NR/cardinal_of<n_t>::value; j++)
      {
        vT a0 = load<vT>(&tab_a0[0],j);
        vT a1 = load<vT>(&tab_a1[0],j);
        iT a2 = tab_a2[j];
        r_t v = comparator(a0,a1,a2);
        vT ma = boost::simd::max(a0,a1);
        vT mi = boost::simd::min(a0,a1);
        NT2_TEST(boost::simd::all(boost::simd::eq(boost::fusion::get<0>(v),(a2)?ma:mi)));
        NT2_TEST(boost::simd::all(boost::simd::eq(boost::fusion::get<1>(v),(a2)?mi:ma)));
      }
    
  }
} // end of test for real_
