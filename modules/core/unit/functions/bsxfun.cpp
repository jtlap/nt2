/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::bsxfun function"

#include <nt2/table.hpp>
#include <nt2/include/functions/size.hpp>
#include <nt2/include/functions/bsxfun.hpp>
#include <nt2/include/functions/rif.hpp>
#include <nt2/include/functions/cif.hpp>
#include <nt2/include/functions/mean.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

NT2_TEST_CASE( bsxfun_size )
{
  nt2::table<float> a = nt2::rif(nt2::of_size(3, 1), nt2::meta::as_<float>()),
                    b = nt2::cif(nt2::of_size(1, 3), nt2::meta::as_<float>()),
                    c, d, e;
  NT2_DISPLAY(a);
  NT2_DISPLAY(b);
  nt2::functor<nt2::tag::plus_> f;
  c = bsxfun(f,  a, b);
  NT2_DISPLAY(c);
  d = bsxfun(nt2::functor<nt2::tag::plus_>(),  a, c);
  NT2_DISPLAY(d);
  e = bsxfun(nt2::functor<nt2::tag::plus_>(),  nt2::rif(nt2::of_size(3, 1), nt2::meta::as_<float>()),  nt2::cif(nt2::of_size(1, 3), nt2::meta::as_<float>()));
 NT2_DISPLAY(e);  
}
NT2_TEST_CASE( bsxfun_2 )
{
  nt2::table<float> a = nt2::rif(nt2::of_size(8, 1), nt2::meta::as_<float>()),
                    m, c;
  m =  nt2::mean(a, 1); 
  NT2_DISPLAY(a);
  NT2_DISPLAY(m);
  nt2::functor<nt2::tag::minus_> f;
  c = bsxfun(f,  a, m);
  NT2_DISPLAY(c);

}
