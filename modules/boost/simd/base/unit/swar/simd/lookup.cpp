//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/swar/include/functions/lookup.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/include/functions/enumerate.hpp>
#include <boost/simd/include/functions/reverse.hpp>
#include <boost/simd/include/functions/divides.hpp>
#include <boost/simd/include/constants/valmax.hpp>
#include <boost/simd/include/constants/two.hpp>
#include <boost/simd/sdk/simd/io.hpp>

NT2_TEST_CASE_TPL ( lookup,  BOOST_SIMD_SIMD_TYPES)
{
  using boost::simd::lookup;
  using boost::simd::tag::lookup_;
  using boost::simd::native;
  using boost::simd::meta::cardinal_of;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  typedef typename boost::dispatch::meta::as_integer<vT>::type ivT;

  ivT inds =  boost::simd::enumerate<ivT>();
  vT vals  =  boost::simd::enumerate<vT>();
  vT  r =  lookup(vals, inds);
  NT2_TEST_EQUAL(r, vals);
  ivT indsr =  boost::simd::reverse(inds);
  r = lookup(vals, indsr);
  NT2_TEST_EQUAL(r, boost::simd::reverse(vals));

  vals =  boost::simd::enumerate<vT>(boost::simd::Valmax<vT>()/boost::simd::Two<vT>());
  r = lookup(vals, inds);
  NT2_TEST_EQUAL(r, vals);
  r = lookup(vals, indsr);
  NT2_TEST_EQUAL(r, boost::simd::reverse(vals));

}
