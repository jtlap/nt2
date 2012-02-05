//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 fuzzy toolbox - tolerant_floor/simd Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of fuzzy components in simd mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 04/03/2011
/// 
#include <nt2/toolbox/fuzzy/include/functions/tolerant_floor.hpp>
#include <nt2/include/functions/ulpdist.hpp>
#include <nt2/sdk/simd/logical.hpp>

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
#include <nt2/toolbox/constant/constant.hpp>
#include <nt2/sdk/meta/cardinal_of.hpp>
#include <nt2/include/functions/splat.hpp>
#include <nt2/include/functions/load.hpp>


NT2_TEST_CASE_TPL ( tolerant_floor_real__3_0,  NT2_SIMD_REAL_TYPES)
{
  using nt2::tolerant_floor;
  using nt2::tag::tolerant_floor_;
  using nt2::load; 
  using boost::simd::native;
  using nt2::meta::cardinal_of;
  typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename nt2::meta::upgrade<T>::type   u_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                       ivT;
  typedef typename nt2::meta::call<tolerant_floor_(vT)>::type r_t;
  typedef typename nt2::meta::call<tolerant_floor_(T)>::type sr_t;
  typedef typename nt2::meta::scalar_of<r_t>::type ssr_t;
  double ulpd;
  ulpd=0.0;


  // specific values tests
  NT2_TEST_EQUAL(tolerant_floor(nt2::Zero<vT>()), nt2::Zero<r_t>());
  NT2_TEST_EQUAL(tolerant_floor(nt2::Eps<vT>()), nt2::Zero<r_t>());
  NT2_TEST_EQUAL(tolerant_floor(nt2::Eps<vT>()), nt2::Zero<r_t>());
  NT2_TEST_EQUAL(tolerant_floor(-nt2::Eps<vT>()), nt2::Zero<r_t>());
  NT2_TEST_EQUAL(tolerant_floor(-nt2::Two<vT>()*nt2::Eps<vT>()), nt2::Zero<r_t>());
  NT2_TEST_EQUAL(tolerant_floor(-nt2::Three<vT>()*nt2::Eps<vT>()), nt2::Zero<r_t>());
  NT2_TEST_EQUAL(tolerant_floor(-nt2::Four<vT>()*nt2::Eps<vT>()), nt2::Mone<r_t>());

} // end of test for floating_
