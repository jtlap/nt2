//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 boost.simd.swar toolbox - enumerate SIMD Mode"

#include <boost/simd/toolbox/swar/include/functions/arith.hpp>

#include <boost/type_traits/is_same.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/memory/buffer.hpp>
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

  std::cout << arith<vT>() << std::endl; 
  for(std::size_t i=0; i < vT::static_size;++i)
    NT2_TEST_EQUAL(arith<vT>()[i], T(i));
  std::cout << arith<vT>(T(10)) << std::endl; 
  for(std::size_t i=0; i < vT::static_size;++i)
    NT2_TEST_EQUAL(arith<vT>(T(10))[i], T(i+10));
  std::cout << arith<vT>(T(10), T(0.5)) << std::endl; 
  for(std::size_t i=0; i < vT::static_size;++i)
    NT2_TEST_EQUAL(arith<vT>(T(10), T(0.5))[i], T(10 + T(0.5)*i));
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
  std::cout << arith<vT>(int(10)) << std::endl; 
  for(std::size_t i=0; i < vT::static_size;++i)
    NT2_TEST_EQUAL(arith<vT>(int(10))[i], T(10 + i));
  std::cout << arith<vT>(int(10), T(0.5)) << std::endl; 
  for(std::size_t i=0; i < vT::static_size;++i)
    NT2_TEST_EQUAL(arith<vT>(int(10), T(0.5))[i], T(10 + T(0.5)*i));
}
