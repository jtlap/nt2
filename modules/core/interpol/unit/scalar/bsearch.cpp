//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2::bsearch function"

#include <nt2/table.hpp>
#include <nt2/include/functions/bsearch.hpp>
#include <nt2/include/functions/linspace.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/vertcat.hpp>
#include <nt2/include/functions/reshape.hpp>
#include <nt2/include/functions/isequal.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>


NT2_TEST_CASE_TPL( bsearch, (float))//(double))//NT2_TYPES )
{
  using nt2::_;
typedef typename nt2::meta::as_integer<T>::type i_type;
  nt2::table<T> x =  nt2::linspace(T(1),  T(4), 4);
  nt2::table<T> xi=  nt2::linspace(T(1),  T(3.5), 6);
  NT2_DISPLAY(x);
  NT2_DISPLAY(xi);
//   typedef typename nt2::meta::as_integer<T, signed>::type       index_type;
//   nt2::table<index_type> i=  nt2::Two<index_type>()*nt2::ones(1, 7, nt2::meta::as_<index_type>());
//   NT2_DISPLAY(i);
//   NT2_DISPLAY(xi(1, i));


  nt2::table<i_type> i = nt2::bsearch(x, xi);

  NT2_DISPLAY(i);
  nt2::table<i_type> k = _(i_type(1), i_type(3));
  nt2::table<i_type> j = nt2::reshape(nt2::catv(k, k), 1, 6);
  //  nt2::table<i_type> j1 = nt2::reshape( nt2::catv(_(i_type(1), i_type(3)),  _(i_type(1), i_type(3))), 1, 6);
  NT2_DISPLAY(j);
  NT2_TEST(isequal(i, j));

}

