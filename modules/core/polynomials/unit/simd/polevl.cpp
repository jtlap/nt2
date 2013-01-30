//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 polynomials toolbox - polevl/simd Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of polynomials components in simd mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 06/03/2011
///
#include <nt2/toolbox/polynomials/include/functions/polevl.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <nt2/sdk/meta/as_integer.hpp>

#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/memory/buffer.hpp>
#include <nt2/include/constants/real.hpp>
#include <nt2/include/constants/infinites.hpp>
#include <nt2/include/functions/load.hpp>
#include <boost/array.hpp>


NT2_TEST_CASE_TPL ( polevl_real__2_0,  NT2_SIMD_REAL_TYPES)
{
  using nt2::polevl;
  using nt2::tag::polevl_;
  using nt2::load;
  using boost::simd::native;
  using nt2::meta::cardinal_of;
  typedef boost::array<T, 4 > A_t;
  typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                       ivT;
  typedef typename nt2::meta::call<polevl_(vT,A_t)>::type r_t;
  typedef typename nt2::meta::scalar_of<r_t>::type ssr_t;

  static const boost::array<T, 4 > A= {{ T(1), T(2), T(3), T(4) }};

  NT2_TEST_EQUAL(polevl( nt2::splat<vT>(1), A)[0], T(10)); //1*1^3 + 2*1^2 + 3*1 +4
  NT2_TEST_EQUAL(polevl( nt2::splat<vT>(2), A)[0], T(26)); //1*2^3 + 2*2^2 + 3*2 +4
  NT2_TEST_EQUAL(polevl( nt2::splat<vT>(3), A)[0], T(58)); //1*3^3 + 2*3^2 + 3*3 +4

} // end of test for floating_
