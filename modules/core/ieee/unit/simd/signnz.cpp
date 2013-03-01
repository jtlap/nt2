//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 ieee toolbox - signnz/simd Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of ieee components in simd mode
//////////////////////////////////////////////////////////////////////////////
/// created by jt the 04/12/2010
///
#include <nt2/toolbox/ieee/include/functions/signnz.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/type_traits/is_same.hpp>
#include <nt2/include/functions/negate.hpp>
#include <nt2/sdk/functor/meta/call.hpp>

#include <nt2/sdk/meta/scalar_of.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/toolbox/constant/constant.hpp>

NT2_TEST_CASE_TPL ( signnz_real__1_0,  NT2_SIMD_REAL_TYPES)
{
  using nt2::signnz;
  using nt2::tag::signnz_;
  using boost::simd::native;

  typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                        vT;
  typedef typename nt2::meta::call<signnz_(vT)>::type r_t;
  typedef typename nt2::meta::call<signnz_(T)>::type sr_t;

  // specific values tests
  NT2_TEST_EQUAL(signnz(-nt2::Zero<vT>())[0], nt2::Mone<sr_t>());
  NT2_TEST_EQUAL(signnz(nt2::Inf<vT>())[0], nt2::One<sr_t>());
  NT2_TEST_EQUAL(signnz(nt2::Minf<vT>())[0], nt2::Mone<sr_t>());
  NT2_TEST_EQUAL(signnz(nt2::Mone<vT>())[0], nt2::Mone<sr_t>());
  NT2_TEST_EQUAL(signnz(nt2::Nan<vT>())[0], nt2::Nan<sr_t>());
  NT2_TEST_EQUAL(signnz(nt2::One<vT>())[0], nt2::One<sr_t>());
  NT2_TEST_EQUAL(signnz(nt2::Zero<vT>())[0], nt2::One<sr_t>());
} // end of test for floating_
