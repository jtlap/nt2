
//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 reduction toolbox - posmax/simd Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of reduction components in simd mode
//////////////////////////////////////////////////////////////////////////////

#include <nt2/reduction/include/functions/posmax.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <nt2/include/functions/arith.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/meta/cardinal_of.hpp>
#include <nt2/sdk/complex/complex.hpp>
#include <nt2/sdk/complex/meta/as_complex.hpp>

NT2_TEST_CASE_TPL ( posmax_real,  NT2_SIMD_REAL_TYPES)
{
  using nt2::posmax;
  using nt2::tag::posmax_;
  using boost::simd::native;
  using nt2::meta::cardinal_of;
  typedef NT2_SIMD_DEFAULT_EXTENSION                ext_t;
  typedef native<T,ext_t>                              vT;
  typedef typename nt2::meta::call<posmax_(vT)>::type r_t;
  typedef std::complex<T>                              cT;
  typedef native<cT ,ext_t>                           vcT;

  // specific values tests
  vT r =  nt2::arith<vT>(0, 1);
  vT i =  nt2::arith<vT>(0, 1);
  vcT z = vcT(r, i);
  NT2_TEST_EQUAL(posmax(z), r_t(cardinal_of<vT>::value-1));
  i =  nt2::arith<vT>(T(cardinal_of<vT>::value-1), T(-1));
  z = vcT(r, i);
  NT2_TEST_EQUAL(posmax(z), r_t(0));

} // end of test for floating_
