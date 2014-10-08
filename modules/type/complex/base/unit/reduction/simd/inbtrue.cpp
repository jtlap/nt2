//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompinbtrueing file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#include <nt2/reduction/include/functions/inbtrue.hpp>
#include <nt2/include/functions/enumerate.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <nt2/sdk/simd/logical.hpp>
#include <nt2/sdk/functor/meta/call.hpp>

#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/meta/cardinal_of.hpp>
#include <nt2/sdk/complex/complex.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/mone.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/constants/true.hpp>
#include <nt2/include/constants/false.hpp>

NT2_TEST_CASE_TPL ( inbtrue_real__1_0,  NT2_SIMD_REAL_TYPES)
{
  using nt2::inbtrue;
  using nt2::tag::inbtrue_;
  using boost::simd::native;
  using nt2::meta::cardinal_of;

  typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<std::complex<T> ,ext_t>            vcT;
  typedef native<T ,ext_t>                          vT;

  vT r =  nt2::enumerate<vT>();
  vT i =  nt2::enumerate<vT>();
  vcT z = vcT(r, i);

  NT2_TEST_EQUAL(inbtrue(z), cardinal_of<vT>::value-1u);
  i =  nt2::enumerate<vT>(T(cardinal_of<vT>::value-1), T(-1));
  z = vcT(r, i);

  NT2_TEST_EQUAL(inbtrue(z), cardinal_of<vT>::value);

} // end of test for floating_
