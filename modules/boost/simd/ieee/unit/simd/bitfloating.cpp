//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 boost.simd.ieee toolbox - bitfloating/simd Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of boost.simd.ieee components in simd mode
//////////////////////////////////////////////////////////////////////////////
/// created by jt the 04/12/2010
///
#include <boost/simd/toolbox/ieee/include/functions/bitfloating.hpp>
#include <boost/simd/toolbox/constant/constant.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <boost/dispatch/meta/as_floating.hpp>
#include <boost/simd/sdk/meta/scalar_of.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

NT2_TEST_CASE_TPL ( bitfloating_integer_convert__1_0,  BOOST_SIMD_SIMD_UINT_CONVERT_TYPES BOOST_SIMD_SIMD_INT_CONVERT_TYPES)
{
  using boost::simd::bitfloating;
  using boost::simd::tag::bitfloating_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename boost::dispatch::meta::as_floating<T>::type fT;
  typedef native<fT,ext_t>                       fvT;
  typedef typename boost::dispatch::meta::call<bitfloating_(vT)>::type r_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type sr_t;

  NT2_TEST_TYPE_IS(r_t, fvT);

  NT2_TEST_EQUAL(bitfloating(boost::simd::Mone<vT>())[0]  ,bitfloating(boost::simd::Mone<T>())  );
  NT2_TEST_EQUAL(bitfloating(boost::simd::One<vT>() )[0]  ,bitfloating(boost::simd::One<T>())   );
  NT2_TEST_EQUAL(bitfloating(boost::simd::Valmax<vT>())[0],bitfloating(boost::simd::Valmax<T>()));
  NT2_TEST_EQUAL(bitfloating(boost::simd::Valmin<vT>())[0],bitfloating(boost::simd::Valmin<T>()));
  NT2_TEST_EQUAL(bitfloating(boost::simd::Zero<vT>())[0]  ,bitfloating(boost::simd::Zero<T>())  );
} // end of test for integer_convert_
