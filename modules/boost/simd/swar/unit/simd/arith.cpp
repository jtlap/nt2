//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 boost.simd.swar toolbox - enumerate SIMD Mode"

#include <boost/simd/toolbox/swar/include/functions/arith.hpp>
#include <boost/simd/sdk/simd/native.hpp>

#include <boost/type_traits/is_same.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/toolbox/constant/constant.hpp>
#include <boost/simd/include/functions/load.hpp>

NT2_TEST_CASE_TPL ( arith, BOOST_SIMD_SIMD_TYPES)
{
  using boost::simd::native;
  using boost::simd::arith;
  using boost::dispatch::meta::as_;
  using boost::simd::tag::arith_;
  using boost::simd::arith;

  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>               vT;
  typedef typename boost::dispatch::meta::call<arith_(T, as_<vT> )>::type r_t;

  for(std::size_t i=0; i < vT::static_size;++i)
    NT2_TEST_EQUAL(arith<vT>()[i], T(i));
  for(std::size_t i=0; i < vT::static_size;++i)
    NT2_TEST_EQUAL(arith<vT>(T(10))[i], T(i+10));
  for(std::size_t i=0; i < vT::static_size;++i)
    NT2_TEST_EQUAL(arith<vT>(T(10), T(2.0))[i], T(10 + T(2.0)*i));
}

NT2_TEST_CASE_TPL ( arith_from_int, BOOST_SIMD_SIMD_TYPES)
{
  using boost::simd::native;
  using boost::simd::arith;
  using boost::dispatch::meta::as_;
  using boost::simd::tag::arith_;

  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>               vT;
  typedef typename boost::dispatch::meta::call<arith_(int, as_<vT> )>::type r_t;

  for(std::size_t i=0; i < vT::static_size;++i)
    NT2_TEST_EQUAL(arith<vT>(int(10))[i], T(10 + i));
  for(std::size_t i=0; i < vT::static_size;++i)
    NT2_TEST_EQUAL(arith<vT>(int(10), T(2.0))[i], T(10 + T(2.0)*i));
}
