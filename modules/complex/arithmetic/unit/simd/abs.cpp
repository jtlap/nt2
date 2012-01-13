//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 complex.arithmetic toolbox - cmplx_testing/simd Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of complex.arithmetic components in simd  mode
//////////////////////////////////////////////////////////////////////////////
/// created by jt the 13/01/2012
/// 
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/splat.hpp>
#include <nt2/include/functions/ulpdist.hpp>
#include <nt2/include/functions/real.hpp>
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

#include <nt2/toolbox/constant/constant.hpp>
#include <nt2/sdk/meta/cardinal_of.hpp>
#include <nt2/include/functions/splat.hpp>

#include <nt2/include/functions/load.hpp>
#include <nt2/sdk/complex/complex.hpp>

NT2_TEST_CASE_TPL ( abs_cplx__1_0,  (float))
{
  using boost::simd::native;
  typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef std::complex<T>                         cT; 
  typedef native<T ,ext_t>                        vT;
  typedef native<cT ,ext_t>                      vcT;

  //  vcT vca0  nt2::splat<vcT>(nt2::Two<cT>()); 
  vcT vca = vcT(nt2::Two<vT>(), nt2::One<vT>());
  //  vT  vra = nt2::real(vca); 
  //  std::cout << nt2::real(vca) << std::endl; 
  //  std::cout << vca << std::endl;
  //  std::cout << nt2::abs(vca) << std::endl; 
} // end of test for floating_


