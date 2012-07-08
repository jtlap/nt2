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
#include <nt2/include/functions/ndims.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

NT2_TEST_CASE_TPL( semantic, NT2_TYPES )
{
  using boost::mpl::_;
  using nt2::settings;
  using nt2::memory::container;
  using boost::dispatch::meta::semantic_of;

  nt2::table<T> in;

  NT2_TEST_EXPR_TYPE( (nt2::expand(in,nt2::of_size(3,2)))
                    , (semantic_of<_>)
                    , ( container<T, settings ( settings(nt2::rectangular_, nt2::_2D)
                                              , settings()
                                              )
                                  >
                      )
                    );

  NT2_TEST_EXPR_TYPE( (nt2::expand(in,nt2::of_size(3,1,2)))
                    , (semantic_of<_>)
                    , ( container<T, settings ( settings(nt2::rectangular_, nt2::_3D)
                                              , settings()
                                              )
                                  >
                      )
                    );

  NT2_TEST_EXPR_TYPE( (nt2::expand(in,nt2::of_size(3,1,2,2)))
                    , (semantic_of<_>)
                    , ( container<T, settings ( settings(nt2::rectangular_, nt2::_4D)
                                              , settings()
                                              )
                                  >
                      )
                    );
}

NT2_TEST_CASE_TPL( expand, NT2_TYPES )
{
  nt2::table<T> in( nt2::of_size(3,3) ), out;

  for(int j=1;j<=9;j++) in(j) = T(j);

  out = nt2::expand(in,nt2::of_size(0,0));
  NT2_TEST_EQUAL( nt2::numel(out), 0u);

  for(int j=1;j<10;++j)
  {
    for(int i=1;i<10;++i)
    {
      out = nt2::expand(in,nt2::of_size(i,j));

      NT2_TEST_EQUAL( nt2::extent(out), nt2::of_size(i,j ));

      for(int vj=1;vj<=j;++vj)
        for(int vi=1;vi<=i;++vi)
          NT2_TEST_EQUAL( out(vi,vj), (vi<=3 && vj<=3) ? in(vi,vj) : 0);
    }
  }
}
NT2_TEST_CASE_TPL( expand1, NT2_TYPES )
{
  nt2::table<T> in( nt2::of_size(3,2) ), out;

  for(int j=1;j<=6;j++) in(j) = j;

  out = nt2::expand(in,nt2::of_size(0,0));
  NT2_TEST_EQUAL( nt2::numel(out), 0u);

  for(int j=1;j<10;++j)
  {
    for(int i=1;i<10;++i)
    {
      out = nt2::expand(in,nt2::of_size(i,j));

      NT2_TEST_EQUAL( nt2::extent(out), nt2::of_size(i,j ));

      for(int vj=1;vj<=j;++vj)
        for(int vi=1;vi<=i;++vi)
          NT2_TEST_EQUAL( out(vi,vj), (vi<=3 && vj<=2) ? in(vi,vj) : T(0));
    }
  }
}
