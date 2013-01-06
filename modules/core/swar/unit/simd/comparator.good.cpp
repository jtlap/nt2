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
// Test behavior of swar components in simd mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 24/02/2011
/// modified by jt the 20/03/2011
#include <nt2/include/functions/load.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <nt2/sdk/memory/buffer.hpp>
#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/include/constants/real.hpp>
#include <nt2/include/constants/infinites.hpp>
#include <nt2/include/functions/max.hpp>
#include <nt2/toolbox/swar/include/functions/comparator.hpp>
#include <boost/fusion/tuple.hpp>
// specific includes for arity 3 tests
#include <nt2/include/functions/all.hpp>
#include <nt2/include/functions/max.hpp>
#include <nt2/include/functions/min.hpp>

NT2_TEST_CASE_TPL ( comparator_real__3_0,  NT2_REAL_TYPES)
{
  using nt2::comparator;
  using nt2::tag::comparator_;
  using nt2::load;
  using nt2::simd::native;
  using nt2::meta::cardinal_of;
  typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename nt2::meta::upgrade<T>::type   u_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                        ivT;
  typedef typename nt2::meta::call<comparator_(vT,vT,iT)>::type r_t;
  typedef typename nt2::meta::call<comparator_(T,T,iT)>::type sr_t;
  typedef typename nt2::meta::scalar_of<r_t>::type ssr_t;

  // random verifications
  static const nt2::uint32_t NR = NT2_NB_RANDOM_TEST;
  {
    NT2_CREATE_BUF(tab_a0,T, NR, T(-100), T(100));
    NT2_CREATE_BUF(tab_a1,T, NR, T(-100), T(100));
    NT2_CREATE_BUF(tab_a2,iT, NR, iT(0), iT(1));
    double ulp0, ulpd ; ulpd=ulp0=0.0;
    for(uint32_t j = 0; j < NR/cardinal_of<n_t>::value; j++)
      {
        vT a0 = load<vT>(&tab_a0[0],j);
        vT a1 = load<vT>(&tab_a1[0],j);
        iT a2 = tab_a2[j];
        r_t v = comparator(a0,a1,a2);
        vT ma = nt2::max(a0,a1);
        vT mi = nt2::min(a0,a1);
	std::cout << a2 << "  " << mi << "   " << ma << std::endl;
        NT2_TEST(nt2::all(nt2::eq(boost::fusion::get<0>(v),(a2)?ma:mi)));
        NT2_TEST(nt2::all(nt2::eq(boost::fusion::get<1>(v),(a2)?mi:ma)));
      }

  }
} // end of test for floating_
