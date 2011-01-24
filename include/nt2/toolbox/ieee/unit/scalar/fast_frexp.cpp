//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 ieee toolbox - fast_frexp/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// Test behavior of ieee components in scalar mode
//////////////////////////////////////////////////////////////////////////////
<<<<<<< HEAD
=======
/// created by jt the 04/12/2010
/// modified by jt the 17/01/2011
>>>>>>> functor2
#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/memory/buffer.hpp>
#include <nt2/sdk/constant/real.hpp>
#include <nt2/sdk/constant/infinites.hpp>
#include <nt2/toolbox/ieee/include/fast_frexp.hpp>
// specific includes for arity 1 tests
#include <boost/fusion/tuple.hpp>
#include <nt2/include/functions/mantissa.hpp>
#include <nt2/include/functions/exponent.hpp>

NT2_TEST_CASE_TPL ( fast_frexp_real__1,  NT2_REAL_TYPES)
{
  using nt2::fast_frexp;
<<<<<<< HEAD
  using nt2::functors::fast_frexp_;
=======
  using nt2::tag::fast_frexp_;
>>>>>>> functor2
  typedef typename nt2::meta::call<fast_frexp_(T)>::type r_t;
  typedef typename nt2::meta::upgrade<T>::type u_t;
  typedef boost::fusion::vector<T,typename nt2::meta::as_integer<T,signed>::type> wished_r_t;

  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 
<<<<<<< HEAD

  // random verifications
  static const uint32_t NR = 100;
  {
    NT2_CREATE_BUFFER(a0,T, 100, T(-10), T(10));
    for (int j =0; j < NR; ++j )
      {
        std::cout << "for param "
                  << "  a0 = "<< u_t(a0 = tab_a0[j])
                  << std::endl;
        r_t r = nt2::fast_frexp(a0);
        typename boost::fusion::result_of::at_c<r_t,0>::type r0 = boost::fusion::get<0>(r);
        typename boost::fusion::result_of::at_c<r_t,1>::type r1 = boost::fusion::get<1>(r);
        NT2_TEST_TUPLE_ULP_EQUAL( r0,nt2::mantissa(a0)/2,0);
        NT2_TEST_TUPLE_ULP_EQUAL( r1,nt2::exponent(a0)+1,0);
     }
   }
=======
  double ulpd;

>>>>>>> functor2
} // end of test for real_