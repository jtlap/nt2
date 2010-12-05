//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 ieee toolbox - exponentbits/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// Test behavior of ieee components in scalar 
//////////////////////////////////////////////////////////////////////////////
#include <nt2/sdk/functor/meta/call.hpp>
#include <boost/type_traits/is_same.hpp>
#include <nt2/toolbox/ieee/include/exponentbits.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/memory/buffer.hpp>
#include <nt2/sdk/constant/real.hpp>
#include <nt2/sdk/constant/infinites.hpp>
#include <nt2/include/functions/ldexp.hpp>
#include <nt2/include/functions/exponent.hpp>
#include <nt2/include/functions/bits.hpp>

NT2_TEST_CASE_TPL ( exponentbits_real_,  NT2_REAL_TYPES)
{
  using nt2::exponentbits;
  using nt2::functors::exponentbits_;
  typedef typename nt2::meta::call<exponentbits_(T)>::type r_t;
  typedef typename nt2::meta::upgrade<T>::type u_t;
  typedef typename nt2::meta::as_integer<T, signed>::type wished_r_t;

  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 

  // random comparison with other impl or formula 
  static const uint32_t NR = 100;
  {
    NT2_CREATE_BUFFER(a0, T, 100, T(-10000), T(10000));
    for (int j =0; j < NR; ++j )
      {
        std::cout << "for param "
                  << "  a0 = "<< u_t(a0 = tab_a0[j])
                  << std::endl;
        NT2_TEST_ULP_EQUAL( nt2::exponentbits(a0), nt2::bits(nt2::ldexp(nt2::One<T>(),nt2::exponent(a0))),0);
     }
   }
} // end of test for real_