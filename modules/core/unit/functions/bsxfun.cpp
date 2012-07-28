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
#include <nt2/include/functions/isequal.hpp>
#include <nt2/include/functions/reshape.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

// NT2_TEST_CASE_TPL( bsxfun_1, NT2_TYPES)
// {
//   nt2::table<T> a = nt2::rif(nt2::of_size(3, 1), nt2::meta::as_<T>()),
//                     b = nt2::cif(nt2::of_size(1, 3), nt2::meta::as_<T>()),
//                     c, d, e;
//   NT2_DISPLAY(a);
//   NT2_DISPLAY(b);
//   e = bsxfun(nt2::functor<nt2::tag::multiplies_>(),  a, b);
//   NT2_DISPLAY(e);
  
//   for(unsigned int i=1; i <= length(a); i++)
//    {
//      for(unsigned int j=1; j <= length(a); j++)
//        {
//          NT2_TEST_EQUAL(e(i, j), a(i)*b(j)); 
//        }
//    }
// }

// NT2_TEST_CASE( bsxfun_2 )
// {
//   nt2::table<float> a = nt2::rif(nt2::of_size(3, 1), nt2::meta::as_<float>()),
//                     b = nt2::cif(nt2::of_size(1, 3), nt2::meta::as_<float>()),
//                     c, d, e;
//   NT2_DISPLAY(a);
//   NT2_DISPLAY(b);
//   nt2::functor<nt2::tag::plus_> f;
//   c = bsxfun(f,  a, b);
//   NT2_DISPLAY(c);
//   d = bsxfun(nt2::functor<nt2::tag::plus_>(),  a, c);
//   NT2_DISPLAY(d);
//   e = bsxfun(nt2::functor<nt2::tag::plus_>(),  nt2::rif(nt2::of_size(3, 1), nt2::meta::as_<float>()),  nt2::cif(nt2::of_size(1, 3), nt2::meta::as_<float>()));
//   NT2_DISPLAY(e);  
// }

// NT2_TEST_CASE_TPL( bsxfun_3, NT2_REAL_TYPES)
// {
//   nt2::table<T> a = nt2::rif(nt2::of_size(8, 1), nt2::meta::as_<T>()),
//                     m, c, d;
//   m =  nt2::mean(a, 1); 
//   NT2_DISPLAY(a);
//   NT2_DISPLAY(m);
//   nt2::functor<nt2::tag::minus_> f;
//   c = bsxfun(f,  a, m);
//   NT2_DISPLAY(c);
//   d =  a-m(1);
//   NT2_DISPLAY(d);
//   NT2_TEST(isequal(c, d)); 
  

// }
NT2_TEST_CASE_TPL( bsxfun_4, NT2_TYPES)
{
  nt2::table<T> a = nt2::reshape(nt2::_(T(1), T(6)),2, 1, 3);
  nt2::table<T> b = nt2::reshape(nt2::_(T(7), T(12)),1, 2, 1, 3);
  NT2_DISPLAY(a);
  NT2_DISPLAY(b);
  nt2::functor<nt2::tag::plus_> f;
  nt2::table<T> c = nt2::bsxfun(f,  a, b);
  NT2_DISPLAY(c);

}
