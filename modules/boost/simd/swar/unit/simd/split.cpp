//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 swar toolbox - split/simd Mode"
//COMMENTED
//////////////////////////////////////////////////////////////////////////////
// unit test behavior of swar components in simd mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 24/02/2011
///
#include <boost/simd/toolbox/swar/include/functions/split.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <boost/fusion/tuple.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <boost/simd/include/constants/one.hpp>

#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/module.hpp>

//COMMENTED

NT2_TEST_CASE_TPL ( split_lt_64__1_0, BOOST_SIMD_SIMD_SPLITABLE_TYPES)
{
  using boost::simd::split;
  using boost::simd::tag::split_;
  using boost::simd::native;

  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>   vT;
  typedef typename boost::dispatch::meta::call<split_(vT)>::type r_t;

  // specific values tests
  typedef typename boost::dispatch::meta::strip<typename boost::fusion::result_of::at_c<r_t,0>::type>::type r_t0;
  typedef typename boost::dispatch::meta::strip<typename boost::fusion::result_of::at_c<r_t,1>::type>::type r_t1;

  {
    r_t res = split(boost::simd::One<vT>());
    NT2_TEST_EQUAL( boost::fusion::get<0>(res), boost::simd::One<r_t0>());
    NT2_TEST_EQUAL( boost::fusion::get<1>(res), boost::simd::One<r_t1>());
  }
  {
    r_t res = split(boost::simd::Zero<vT>());
    NT2_TEST_EQUAL( boost::fusion::get<0>(res), boost::simd::Zero<r_t0>());
    NT2_TEST_EQUAL( boost::fusion::get<1>(res), boost::simd::Zero<r_t1>());
  }
} // end of test for lt_64_
