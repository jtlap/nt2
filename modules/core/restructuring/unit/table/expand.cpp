/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::expand function"

#include <nt2/table.hpp>
#include <nt2/include/functions/expand.hpp>
#include <nt2/include/functions/size.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/isequal.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

NT2_TEST_CASE_TPL( expand, NT2_TYPES )
{
  nt2::table<T> in( nt2::of_size(3,3) ), ref, out;

  for(int j=1;j<=9;j++) in(j) = T(j);

  out = nt2::expand(in,nt2::of_size(0,0));
  NT2_TEST_EQUAL( nt2::numel(out), 0u);

  for(int j=1;j<10;++j)
  {
    for(int i=1;i<10;++i)
    {
      ref = nt2::zeros(i,j,nt2::meta::as_<T>());

      for(int vj=1;vj<=std::min(j,3);++vj)
        for(int vi=1;vi<=std::min(i,3);++vi)
          ref(vi,vj) = in(vi,vj);

      out = nt2::expand(in,nt2::of_size(i,j));

      NT2_TEST( nt2::isequal(out,ref) );
      NT2_TEST_EQUAL( nt2::extent(out), nt2::of_size(i,j ));
    }
  }
}
