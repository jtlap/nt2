/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2 container generator"

#include <nt2/table.hpp>
#include <nt2/include/functions/toint.hpp>
#include <nt2/include/functions/of_size.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

NT2_TEST_CASE( semantic_of )
{
  using nt2::id_;
  using nt2::table;
  using nt2::tag::table_;
  using nt2::memory::container;
  using boost::dispatch::meta::semantic_of;
  using boost::mpl::_;

  typedef double T;
  typedef nt2::settings S(nt2::_4D);

  table<T, S> a0, a1;

  NT2_TEST_EXPR_TYPE( a0
                    , semantic_of<_>
                    , (container<table_,nt2::id_<0>,T,S>)
                    );

  NT2_TEST_EXPR_TYPE( nt2::assign(a0, a1)
                    , semantic_of<_>
                    , (container<table_,nt2::id_<0>,T,S>&)
                    );

  NT2_TEST_EXPR_TYPE( a0 + a1
                    , semantic_of<_>
                    , (container<table_,nt2::id_<0>,T,S>)
                    );

  NT2_TEST_EXPR_TYPE( nt2::toint(a0)
                    , semantic_of<_>
                    , (container< table_,nt2::id_<0>
                                , boost::dispatch::meta::as_integer<T>::type
                                , S
                                >
                      )
                    );

  NT2_TEST_EXPR_TYPE( a0(1)
                    , semantic_of<_>
                    , T&
                    );

  NT2_TEST_EXPR_TYPE( ((a0 + a1)(1))
                    , semantic_of<_>
                    , T
                    );

  NT2_TEST_EXPR_TYPE( a0 + T(1)
                    , semantic_of<_>
                    , (container<table_,nt2::id_<0>,T,S>)
                    );
}

template<class T>
struct extent_type
{
  typedef typename T::extent_type type;
};

NT2_TEST_CASE( extent_type )
{
  using nt2::table;
  using boost::mpl::_;
  using nt2::of_size_;
  using nt2::of_size;
  using nt2::_3D;
  using nt2::_2D;
  using nt2::_0D;

  typedef double T;
  table<T, _3D> a0;
  table<T, _2D> a1;
  table<T, _3D> a2(of_size(1, 2));
  table<T, _2D> a3(of_size(1, 2));
  table<T, of_size_<1, 2> > a4;

  NT2_TEST_EXPR_TYPE( a0
                    , extent_type<_>
                    , _3D const&
                    );

  NT2_TEST( a0.extent() == of_size(0) );

  NT2_TEST_EXPR_TYPE( a0 + a0
                    , extent_type<_>
                    , _3D  const&
                    );

  NT2_TEST_EXPR_TYPE( a0 + a1
                    , extent_type<_>
                    , _2D const&
                    );

  NT2_TEST_EXPR_TYPE( a2 + a3 + a4
                    , extent_type<_>
                    , (of_size_<1, 2> const&)
                    );

  NT2_TEST_THROW( a0 + a2, nt2::assert_exception );

  NT2_TEST((a2 + a2).extent() == of_size(1, 2));

  NT2_TEST_EXPR_TYPE( a0(1)
                    , extent_type<_>
                    , _0D
                    );

  NT2_TEST_EXPR_TYPE( nt2::assign(a0, a1)
                    , extent_type<_>
                    , _2D const&
                    );
}
