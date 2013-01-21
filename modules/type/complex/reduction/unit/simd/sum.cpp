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
#include <nt2/include/functions/ulpdist.hpp>
#include <nt2/include/functions/arith.hpp>
#include <nt2/sdk/simd/logical.hpp>
#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/meta/as_floating.hpp>
#include <nt2/sdk/meta/as_signed.hpp>
#include <nt2/sdk/meta/upgrade.hpp>
#include <nt2/sdk/meta/downgrade.hpp>
#include <nt2/sdk/meta/scalar_of.hpp>
#include <boost/dispatch/meta/as_floating.hpp>
#include <boost/type_traits/common_type.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/memory/buffer.hpp>
#include <nt2/toolbox/constant/constant.hpp>
#include <boost/dispatch/details/ignore_unused.hpp>
#include <nt2/sdk/meta/cardinal_of.hpp>
#include <nt2/include/functions/splat.hpp>
#include <nt2/include/functions/load.hpp>
#include <nt2/toolbox/constant/constant.hpp>
#include <boost/dispatch/details/ignore_unused.hpp>
#include <nt2/sdk/complex/complex.hpp>
#include <nt2/sdk/complex/meta/as_complex.hpp>
#include <nt2/sdk/complex/meta/as_imaginary.hpp>
#include <nt2/sdk/complex/meta/as_dry.hpp>


NT2_TEST_CASE_TPL ( sum_real__1_0,  NT2_SIMD_REAL_TYPES)
{
  using nt2::sum;
  using nt2::tag::sum_;
  using nt2::load;
  using boost::simd::native;
  using nt2::meta::cardinal_of;
  typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename nt2::meta::upgrade<T>::type   u_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                       ivT;
  typedef typename nt2::meta::call<sum_(vT)>::type r_t;
  typedef typename nt2::meta::call<sum_(T)>::type sr_t;
  typedef typename nt2::meta::scalar_of<r_t>::type ssr_t;
  typedef std::complex<T>                         cT;
  typedef native<cT ,ext_t>                      vcT;
  typedef typename nt2::meta::as_imaginary<vT>::type  viT;
  typedef typename nt2::meta::as_dry<vT>::type        vdT;

  // specific values tests
  vT r =  nt2::arith<vT>(0, 1);
  vT i =  nt2::arith<vT>(0, 1);
  vcT z = vcT(r, i);
  const size_t N = cardinal_of<vT>::value;
  std::cout << "z  " << z << std::endl;
  std::cout << "mz " << sum(z) << std::endl;
  NT2_TEST_EQUAL(sum(z), cT((N*(N-1))/2, (N*(N-1))/2));
  i =  nt2::arith<vT>(T(cardinal_of<vT>::value-1), T(-1));
  z = vcT(r, i);
  std::cout << "z  " << z << std::endl;
  std::cout << "mz " << sum(z) << std::endl;
  std::cout << "absz "<< nt2::abs(z) << std::endl;
  std::cout << "argz "<< nt2::arg(z) << std::endl;
  NT2_TEST_EQUAL(sum(z), cT((N*(N-1))/2,(N*(N-1))/2));

} // end of test for floating_
