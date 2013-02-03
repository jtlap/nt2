//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 reduction toolbox - sum/simd Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of reduction components in simd mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 24/02/2011
///
#include <nt2/toolbox/reduction/include/functions/sum.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <nt2/sdk/simd/logical.hpp>

#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/meta/scalar_of.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/meta/cardinal_of.hpp>
#include <nt2/sdk/complex/complex.hpp>
#include <nt2/include/functions/arith.hpp>

NT2_TEST_CASE_TPL ( sum_real__1_0,  NT2_SIMD_REAL_TYPES)
{
  using nt2::sum;
  using nt2::tag::sum_;
  using boost::simd::native;
  using nt2::meta::cardinal_of;

  typedef NT2_SIMD_DEFAULT_EXTENSION                ext_t;
  typedef std::complex<T>                           cT;
  typedef native<T ,ext_t>                          vT;
  typedef native<cT ,ext_t>                         vcT;
  typedef typename nt2::meta::call<sum_(vcT)>::type r_t;

  // specific values tests
  vT r =  nt2::arith<vT>(0, 1);
  vT i =  nt2::arith<vT>(0, 1);
  vcT z = vcT(r, i);
  const size_t N = cardinal_of<vT>::value;

  NT2_TEST_EQUAL(sum(z), cT((N*(N-1))/2, (N*(N-1))/2));
  i = nt2::arith<vT>(T(cardinal_of<vT>::value-1), T(-1));
  z = vcT(r, i);

  NT2_TEST_EQUAL(sum(z), cT((N*(N-1))/2,(N*(N-1))/2));

} // end of test for floating_
