/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2 function tie"

#include <nt2/table.hpp>
#include <nt2/include/functions/tie.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

NT2_TEST_CASE( semantic_of )
{
  using nt2::table;
  using nt2::settings;
  using boost::mpl::_;
  using nt2::memory::container;
  using boost::fusion::vector1;
  using boost::fusion::vector2;
  using boost::fusion::vector3;
  using boost::fusion::vector4;
  using boost::dispatch::meta::semantic_of;

  table<double> d; double d2;
  table<float>  f; float f2;
  table<short>  s;
  table<char>   c;

  NT2_TEST_EXPR_TYPE( nt2::tie(d)
                    , semantic_of<_>
                    , (vector1< container<double,settings()>& >)
                    );
  NT2_TEST_EXPR_TYPE( nt2::tie(d2)
                    , semantic_of<_>
                    , (vector1< double& >)
                    );

  NT2_TEST_EXPR_TYPE( nt2::tie(f,d)
                    , semantic_of<_>
                    , (vector2< container<float,settings()>&
                              , container<double,settings()>&
                              >
                      )
                    );
  NT2_TEST_EXPR_TYPE( nt2::tie(f2,d2)
                    , semantic_of<_>
                    , (vector2< float&
                              , double&
                              >
                      )
                    );
  NT2_TEST_EXPR_TYPE( nt2::tie(f,d2)
                    , semantic_of<_>
                    , (vector2< container<float,settings()>&
                              , double&
                              >
                      )
                    );
  NT2_TEST_EXPR_TYPE( nt2::tie(f2,d)
                    , semantic_of<_>
                    , (vector2< float&
                              , container<double,settings()>&
                              >
                      )
                    );

  NT2_TEST_EXPR_TYPE( nt2::tie(f,d,s)
                    , semantic_of<_>
                    , (vector3< container<float,settings()>&
                              , container<double,settings()>&
                              , container<short,settings()>&
                              >
                      )
                    );

  NT2_TEST_EXPR_TYPE( nt2::tie(c,f,d,s)
                    , semantic_of<_>
                    , (vector4< container<char,settings()>&
                              , container<float,settings()>&
                              , container<double,settings()>&
                              , container<short,settings()>&
                              >
                      )
                    );
}

template <class T> struct extent_
{
  typedef typename T::extent_type type;
};

NT2_TEST_CASE( extent )
{
  using nt2::table;
  using nt2::of_size_;
  using boost::mpl::_;

  table<double> d;
  table<float>  f;
  table<short>  s;
  table<char>   c;

  NT2_TEST_EXPR_TYPE( nt2::tie(d)       , extent_<_>, (of_size_<1>) );
  NT2_TEST_EXPR_TYPE( nt2::tie(f,d)     , extent_<_>, (of_size_<1>) );
  NT2_TEST_EXPR_TYPE( nt2::tie(f,d,s)   , extent_<_>, (of_size_<1>) );
  NT2_TEST_EXPR_TYPE( nt2::tie(c,f,d,s) , extent_<_>, (of_size_<1>) );
}
