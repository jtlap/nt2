//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 ieee toolbox - mantissa/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// Test behavior of ieee components in scalar 
//////////////////////////////////////////////////////////////////////////////
#include <nt2/sdk/functor/meta/call.hpp>
#include <boost/type_traits/is_same.hpp>
#include <nt2/toolbox/ieee/include/mantissa.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/memory/buffer.hpp>
#include <nt2/sdk/constant/real.hpp>
#include <nt2/sdk/constant/infinites.hpp>
#include <nt2/include/functions/frexp.hpp>

NT2_TEST_CASE_TPL ( mantissa_real_,  NT2_REAL_TYPES)
{
  using nt2::mantissa;
  using nt2::functors::mantissa_;
  typedef typename nt2::meta::call<mantissa_(T)>::type r_t;
  typedef typename nt2::meta::upgrade<T>::type u_t;
  typedef T wished_r_t;

  // specific values tests
  NT2_TEST_ULP_EQUAL(  mantissa(nt2::Inf<T>()), nt2::One<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(  mantissa(nt2::Minf<T>()), nt2::Mone<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(  mantissa(nt2::Mone<T>()), nt2::Mone<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(  mantissa(nt2::One<T>()), nt2::One<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(  mantissa(nt2::Zero<T>()), nt2::Zero<r_t>(), 0);

  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 

  // random comparison with other impl or formula 
  static const uint32_t NR = 100;
  {
    NT2_CREATE_BUFFER(a0,T, 100, T(-10), T(10));
    for (int j =0; j < NR; ++j )
      {
        std::cout << "for param "
                  << "  a0 = "<< u_t(a0 = tab_a0[j])
                  << std::endl;
        NT2_TEST_ULP_EQUAL( nt2::mantissa(a0), boost::fusion::get<0>(nt2::frexp(a0))*2,0);
     }
   }
} // end of test for real_