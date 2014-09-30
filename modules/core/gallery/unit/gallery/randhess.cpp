//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 gallery toolbox - randhess function"

#include <nt2/table.hpp>
#include <nt2/include/functions/randhess.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/transpose.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/include/functions/linspace.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/module.hpp>


NT2_TEST_CASE_TPL ( randhess, NT2_REAL_TYPES)
{
  nt2::table<T> r6 =nt2::trans(nt2::cons(nt2::of_size(5, 5),
    T( 5.403023058681398e-01),    T(-3.501754883740146e-01),    T(-7.574901860152801e-01),    T(-7.057887429219221e-02),    T(-8.171772273977561e-02),
    T(-8.414709848078965e-01),    T(-2.248450953661529e-01),    T(-4.863788550831339e-01),    T(-4.531817402397399e-02),    T(-5.247034636217886e-02),
    T(                     0),    T(-9.092974268256817e-01),    T( 4.119822456656830e-01),    T( 3.838629683166185e-02),    T( 4.444447142228624e-02),
    T(                     0),    T(                     0),    T(-1.411200080598672e-01),    T( 6.471022801057221e-01),    T( 7.492287917633427e-01),
    T(                     0),    T(                     0),    T(                     0),    T( 7.568024953079282e-01),    T(-6.536436208636119e-01))) ;
  NT2_DISPLAY(r6);
  NT2_DISPLAY( nt2::randhess(nt2::_(T(1), T(5))));
  NT2_TEST_ULP_EQUAL(nt2::randhess(nt2::_(T(1), T(5))),
                     r6, 1);
  NT2_DISPLAY( nt2::randhess(nt2::_(T(1), T(5))));
//   NT2_DISPLAY(nt2::randhess(5, nt2::meta::as_<T>())); //these 2 matrices are random and so not tested but for the build
//   NT2_DISPLAY(nt2::randhess<T>(5));

}





