//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 gallery toolbox - randcolu function"

#include <nt2/table.hpp>
#include <nt2/include/functions/randcolu.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/transpose.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/include/functions/linspace.hpp>
#include <nt2/include/functions/svd.hpp>
#include <nt2/include/functions/sort.hpp>
#include <nt2/include/functions/norm.hpp>
#include <nt2/include/functions/sqrt.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/include/functions/asum2.hpp>
#include <nt2/include/functions/svd.hpp>
#include <nt2/include/functions/fliplr.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/module.hpp>


// NT2_TEST_CASE_TPL ( randcolu, NT2_REAL_TYPES)
// {
//   typedef typename nt2::meta::as_<T> ta_t;
//   nt2::table<T> x0 = nt2::colvect(nt2::_(T(2), T(6)));
//    NT2_DISPLAY(x0);
//    NT2_DISPLAY(norm2(x0));
//    nt2::table<T> x =  (x0/nt2::norm(x0))*nt2::sqrt(T(nt2::numel(x0)));
//    NT2_DISPLAY(x);
//    nt2::table<T> rc =  nt2::randcolu(x, 5, 0);
//    NT2_TEST_ULP_EQUAL(nt2::svd(rc), nt2::flipud(x), 5); //check rc has the chosen singular values
//    NT2_TEST_ULP_EQUAL(nt2::asum2(rc), nt2::ones(1, size(rc, 2), ta_t()), 5);//check colons are norm 1
//    NT2_DISPLAY(nt2::asum2(rc));
//    NT2_DISPLAY(rc);
//    NT2_DISPLAY(nt2::svd(rc));


//    rc = nt2::randcolu(x);
//    NT2_TEST_ULP_EQUAL(nt2::svd(rc), nt2::flipud(x), 5); //check rc has the chosen singular values
//    NT2_TEST_ULP_EQUAL(nt2::asum2(rc), nt2::ones(1, size(rc, 2), ta_t()), 5);//check colons are norm 1



//    rc = nt2::randcolu(x, 6, 1);
//    NT2_TEST_ULP_EQUAL(nt2::svd(rc), nt2::flipud(x), 5); //check rc has the chosen singular values
//    NT2_TEST_ULP_EQUAL(nt2::asum2(rc), nt2::ones(1, size(rc, 2), ta_t()), 5);//check colons are norm 1
// }

NT2_TEST_CASE_TPL ( randcolu1, NT2_REAL_TYPES)
{
  typedef typename nt2::meta::as_<T> ta_t;
  nt2::table<T> z =  nt2::cons<T>( nt2::of_size(1, 5), 0.301511344577764,   0.603022689155527,   0.904534033733291,   1.206045378311055,  1.507556722888818);
  nt2::table<T> rc = nt2::randcolu(z, 5, 1);
  NT2_TEST_ULP_EQUAL(nt2::asum2(rc), nt2::ones(1, size(rc, 2), ta_t()), 10);//check colons are norm 1
  nt2::table<T> l = nt2::svd(rc);
  NT2_TEST_ULP_EQUAL(l, nt2::fliplr(z), 5); //check singular values are z
  NT2_TEST_ULP_EQUAL(l, nt2::svd(nt2::fliplr(nt2::randcolu(z, 5, 1))), 10);
  rc = nt2::randcolu(5, 0, ta_t());

  NT2_TEST_ULP_EQUAL(nt2::asum2(rc), nt2::ones(1, size(rc, 2), ta_t()), 10);//check colons are norm 1
  rc = nt2::randcolu(5, 1, ta_t());
  NT2_TEST_ULP_EQUAL(nt2::asum2(rc), nt2::ones(1, size(rc, 2), ta_t()), 10);//check colons are norm 1

}





