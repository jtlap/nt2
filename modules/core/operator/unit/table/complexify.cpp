/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::complexify function"

#include <nt2/table.hpp>
#include <nt2/include/functions/complexify.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/include/functions/ones.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/details/helpers.hpp>
#include <nt2/sdk/complex/meta/as_real.hpp>
#include <nt2/sdk/complex/meta/as_imaginary.hpp>
#include <nt2/sdk/complex/meta/as_dry.hpp>


NT2_TEST_CASE_TPL( complexify1, BOOST_SIMD_REAL_TYPES )
{
  nt2::table<T> a0 = nt2::_(T(1), T(3));
  NT2_DISPLAY(complexify(a0));
  NT2_DISPLAY(complexify(complexify(a0)));
  NT2_DISPLAY(complexify(nt2::_(T(1), T(3))));
  typedef typename nt2::meta::as_real<T>::type                          real_type;


  NT2_DISPLAY(nt2::complexify(nt2::_(real_type( 11)
                                     , real_type(-1)
                                     , real_type(0)
                                )));
}
NT2_TEST_CASE_TPL( complexify2, BOOST_SIMD_REAL_TYPES )
{
  typedef typename nt2::meta::as_imaginary<T>::type ciT;
  nt2::table<T>   a00 = nt2::ones(3, 3, nt2::meta::as_<T>());
  NT2_DISPLAY(a00);
  nt2::table<ciT> a0 = ciT(1)*a00;
  //  std::cout << a0 << std::endl;
  //NT2_DISPLAY(a0);

 for(int i=1; i < 9; i++)
   {
     std::cout << a0(i) << std::endl;
   }
  NT2_DISPLAY(complexify(a0));
  NT2_DISPLAY(complexify(complexify(a0)));
}
NT2_TEST_CASE_TPL( complexify3, BOOST_SIMD_REAL_TYPES )
{
  typedef typename nt2::meta::as_dry<T>::type dT;
  nt2::table<dT> a0 = nt2::ones(3, 3, nt2::meta::as_<dT>());
  //  NT2_DISPLAY(a0);
  NT2_DISPLAY(complexify(a0));
  NT2_DISPLAY(complexify(complexify(a0)));
}

NT2_TEST_CASE( complexify4 )
{
  typedef double T;
  typedef std::complex<double> cT;
  nt2::table<T> a0;
  nt2::table<cT> zz = nt2::complexify(a0);
}
