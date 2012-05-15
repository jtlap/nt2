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
#include <nt2/include/functions/tie.hpp>
#include <nt2/include/functions/assign.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/is_reference.hpp>

NT2_TEST_CASE( semantic_of )
{
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
                    , (container<T,S>)
                    );

  NT2_TEST_EXPR_TYPE( nt2::assign(a0, a1)
                    , semantic_of<_>
                    , (container<T,S>&)
                    );

  NT2_TEST_EXPR_TYPE( a0 + a1
                    , semantic_of<_>
                    , (container<T,S>)
                    );

  NT2_TEST_EXPR_TYPE( nt2::toint(a0)
                    , semantic_of<_>
                    , (container< boost::dispatch::meta::as_integer<T>::type
                                , S
                                >
                      )
                    );

  NT2_TEST_EXPR_TYPE( a0(1)
                    , semantic_of<_>
                    , T
                    );

  NT2_TEST_EXPR_TYPE( ((a0 + a1)(1))
                    , semantic_of<_>
                    , T
                    );

  NT2_TEST_EXPR_TYPE( a0 + T(1)
                    , semantic_of<_>
                    , (container<T,S>)
                    );
}

template<class Expr>
struct is_nt2_basic_expr
{
  operator bool() const
  {
    std::cout << "Following expression is not basic Proto expression:\n";
    nt2::display_type<Expr>();
    return false;
  }
};

template<class Tag, class Args, long int Arity, class Result>
struct is_nt2_basic_expr< nt2::container::expression< boost::proto::basic_expr<Tag, Args, Arity>, Result> >
{
  operator bool() const
  {
    return true;
  }
};

template<class T, class S>
struct is_nt2_basic_expr< nt2::table<T, S> > : is_nt2_basic_expr< nt2::container::expression< typename nt2::table<T, S>::proto_base_expr, nt2::memory::container<T, S>& > > {};

template<class Expr>
void expr_lifetime_0(Expr const&)
{
  using nt2::memory::container;

  typedef double T;
  typedef nt2::settings S(nt2::_4D);

  NT2_TEST( is_nt2_basic_expr<Expr>() );

  NT2_TEST_TYPE_IS( typename boost::proto::result_of::value<Expr>::value_type
                  , (nt2::memory::container<T, S>)
                  );
}

template<class Expr>
void expr_lifetime_2_t(Expr const&)
{
  using nt2::memory::container;

  typedef double T;
  typedef nt2::settings S(nt2::_4D);

  typedef typename boost::proto::result_of::child_c<Expr, 0>::value_type child0;
  typedef typename boost::proto::result_of::child_c<Expr, 1>::value_type child1;

  NT2_TEST( is_nt2_basic_expr<Expr>() );
  NT2_TEST( is_nt2_basic_expr<child0>() );
  NT2_TEST( is_nt2_basic_expr<child1>() );

  NT2_TEST( !boost::is_reference<child1>::value );
  NT2_TEST( !boost::is_const<child1>::value     );

  NT2_TEST_TYPE_IS( typename boost::proto::result_of::value<child1>::value_type
                  , (nt2::memory::container<T, S>&)
                  );
}

template<class Expr>
void expr_lifetime_2_i(Expr const&)
{
  using nt2::memory::container;

  typedef double T;
  typedef nt2::settings S(nt2::_4D);

  typedef typename boost::proto::result_of::child_c<Expr, 0>::value_type child0;
  typedef typename boost::proto::result_of::child_c<Expr, 1>::value_type child1;

  NT2_TEST( is_nt2_basic_expr<Expr>() );
  NT2_TEST( is_nt2_basic_expr<child0>() );
  NT2_TEST( is_nt2_basic_expr<child1>() );

  NT2_TEST( !boost::is_reference<child1>::value );
  NT2_TEST( !boost::is_const<child1>::value     );

  NT2_TEST_TYPE_IS( typename boost::proto::result_of::value<child1>::value_type
                  , T
                  );
}

template<class Expr>
void expr_lifetime_2_ir(Expr const&)
{
  using nt2::memory::container;

  typedef double T;
  typedef nt2::settings S(nt2::_4D);

  typedef typename boost::proto::result_of::child_c<Expr, 0>::value_type child0;
  typedef typename boost::proto::result_of::child_c<Expr, 1>::value_type child1;

  NT2_TEST( is_nt2_basic_expr<Expr>() );
  NT2_TEST( is_nt2_basic_expr<child0>() );
  NT2_TEST( is_nt2_basic_expr<child1>() );

  NT2_TEST( !boost::is_reference<child1>::value );
  NT2_TEST( !boost::is_const<child1>::value     );

  NT2_TEST_TYPE_IS( typename boost::proto::result_of::value<child1>::value_type
                  , T&
                  );
}

template<class Expr>
void expr_lifetime_tie(Expr const&)
{
  using nt2::memory::container;

  typedef double T;
  typedef nt2::settings S(nt2::_4D);

  typedef typename boost::proto::result_of::child_c<Expr, 0>::value_type child0;

  NT2_TEST( is_nt2_basic_expr<Expr>() );
  NT2_TEST( is_nt2_basic_expr<child0>() );

  NT2_TEST( !boost::is_reference<child0>::value );
  NT2_TEST( !boost::is_const<child0>::value     );

  NT2_TEST_TYPE_IS( typename boost::proto::result_of::value<child0>::value_type
                  , T&
                  );
}

NT2_TEST_CASE( expr_lifetime )
{
  using nt2::table;
  using boost::mpl::_;

  typedef double T;
  typedef nt2::settings S(nt2::_4D);
  table<T, S> a0, a1;
  T i;

  expr_lifetime_0(a0);
  expr_lifetime_2_t(a0 + a1);
  expr_lifetime_2_i(a0 + i);
  expr_lifetime_2_ir(a0 + boost::proto::as_child(i));

  // TODO?
  // nt2::display_type(boost::proto::make_expr<boost::proto::tag::assign, nt2::container::domain>(boost::ref(i), boost::ref(i)));

  expr_lifetime_tie(nt2::tie(i));
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

  NT2_TEST_EXPR_TYPE( nt2::assign(a0, a1)
                    , extent_type<_>
                    , _2D const&
                    );
}
