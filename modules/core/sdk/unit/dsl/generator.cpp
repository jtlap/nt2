//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 container generator"

#include <nt2/table.hpp>
#include <nt2/include/functions/toint.hpp>
#include <nt2/include/functions/of_size.hpp>
#include <nt2/include/functions/tie.hpp>
#include <nt2/include/functions/assign.hpp>
#include <nt2/include/functions/sum.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/meta/display_type.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/is_reference.hpp>

#include "as_node.hpp"

// plus-like function with perfect forwarding
namespace nt2
{
  namespace tag
  {
    struct pplus_ : ext::elementwise_<pplus_>
    {
     typedef ext::elementwise_<pplus_> parent;

     template<class... Args>
     static BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
     BOOST_AUTO_DECLTYPE_BODY( dispatching_pplus_(ext::adl_helper(), args...) )
    };
  }

  namespace ext
  {
    template<class Site, class... H>
    boost::dispatch::generic_dispatcher<tag::pplus_, Site> dispatching_pplus_(ext::adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<H>...)
    {
      return boost::dispatch::generic_dispatcher<tag::pplus_, Site>();
    }

    template<class... Args>
    struct impl_pplus_;
  }

  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(tag::pplus_, pplus, (A0&)(A1&), 2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(tag::pplus_, pplus, (A0 const&)(A1&), 2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(tag::pplus_, pplus, (A0&)(A1 const&), 2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(tag::pplus_, pplus, (A0 const&)(A1 const&), 2)

  namespace ext
  {
    BOOST_DISPATCH_IMPLEMENT  ( pplus_, tag::cpu_, (A0)
                              , (scalar_< unspecified_<A0> >)
                                (scalar_< unspecified_<A0> >)
                              )
    {
      typedef A0 result_type;
      result_type operator()(A0 const& a0, A0 const& a1) const
      {
        return a0 + a1;
      }
    };
  }
}

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
                    , (container<table_,T,S>)
                    );

  NT2_TEST_EXPR_TYPE( nt2::assign(a0, a1)
                    , semantic_of<_>
                    , (container<table_,T,S>&)
                    );

  NT2_TEST_EXPR_TYPE( a0 + a1
                    , semantic_of<_>
                    , (container<table_,T,S>)
                    );

  NT2_TEST_EXPR_TYPE( nt2::toint(a0)
                    , semantic_of<_>
                    , (container< table_
                                , boost::dispatch::meta::as_integer<T>::type
                                , S
                                >
                      )
                    );

  /* FIXME: scalar expressions are not supported,
   * to be completely removed                     */
  #if 0
  NT2_TEST_EXPR_TYPE( a0(boost::proto::as_expr(1))
                    , semantic_of<_>
                    , T&
                    );

  NT2_TEST_EXPR_TYPE( ((a0 + a1)(boost::proto::as_expr(1)))
                    , semantic_of<_>
                    , T
                    );
  #endif

  NT2_TEST_EXPR_TYPE( a0 + T(1)
                    , semantic_of<_>
                    , (container<table_,T,S>)
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
struct is_nt2_basic_expr< nt2::table<T, S> > : is_nt2_basic_expr< nt2::container::expression< typename nt2::table<T, S>::proto_base_expr, nt2::memory::container<nt2::tag::table_,T, S>& > > {};

template<class K, class T, class S>
struct  is_nt2_basic_expr< nt2::view<K,T, S> >
      : is_nt2_basic_expr< typename nt2::view<K,T,S>::nt2_expression >
{};

template<class K,class T, class S>
struct  is_nt2_basic_expr< nt2::shared_view<K, T, S> >
      : is_nt2_basic_expr< typename nt2::shared_view<K,T, S>::nt2_expression >
{};

template<class Expr>
void expr_lifetime_0(Expr const&)
{
  using nt2::tag::table_;
  std::cout << __FUNCTION__ << std::endl;

  using nt2::memory::container;

  typedef double T;
  typedef nt2::settings S(nt2::_4D);

  NT2_TEST( is_nt2_basic_expr<Expr>() );

  NT2_TEST_TYPE_IS( typename boost::proto::result_of::value<Expr>::value_type
                  , (nt2::memory::container<table_,T,S>)
                  );
}

template<class Expr>
void expr_lifetime_2_t(Expr const&)
{
  std::cout << __FUNCTION__ << std::endl;

  using nt2::tag::table_;
  using nt2::memory::container;
  using nt2::memory::container_ref;

  typedef double T;
  typedef nt2::settings S(nt2::_4D);

  typedef typename boost::proto::result_of::child_c<Expr, 0>::value_type child0;
  typedef typename boost::proto::result_of::child_c<Expr, 1>::value_type child1;

  NT2_TEST( is_nt2_basic_expr<Expr>() );
  NT2_TEST( is_nt2_basic_expr<child0>() );
  NT2_TEST( is_nt2_basic_expr<child1>() );

  NT2_TEST( !boost::is_reference<child0>::value );
  NT2_TEST( !boost::is_const<child0>::value     );
  NT2_TEST( !boost::is_reference<child1>::value );
  NT2_TEST( !boost::is_const<child1>::value     );

  NT2_TEST_TYPE_IS( typename boost::proto::result_of::value<child0>::value_type
                  , (container_ref<table_,T,S>)
                  );
  NT2_TEST_TYPE_IS( typename boost::proto::result_of::value<child1>::value_type
                  , (container_ref<table_,T,S>)
                  );
}

template<class Expr>
void expr_lifetime_2_ts(Expr const&)
{
  std::cout << __FUNCTION__ << std::endl;

  using nt2::tag::table_;
  using nt2::memory::container;
  using nt2::memory::container_ref;
  using nt2::memory::container_shared_ref;

  typedef double T;
  typedef nt2::settings S(nt2::_4D);

  typedef typename boost::proto::result_of::child_c<Expr, 0>::value_type child0;
  typedef typename boost::proto::result_of::child_c<Expr, 1>::value_type child1;

  NT2_TEST( is_nt2_basic_expr<Expr>() );
  NT2_TEST( is_nt2_basic_expr<child0>() );
  NT2_TEST( is_nt2_basic_expr<child1>() );

  NT2_TEST( !boost::is_reference<child0>::value );
  NT2_TEST( !boost::is_const<child0>::value     );
  NT2_TEST( !boost::is_reference<child1>::value );
  NT2_TEST( !boost::is_const<child1>::value     );

  NT2_TEST_TYPE_IS( typename boost::proto::result_of::value<child0>::value_type
                  , (container_shared_ref<table_, T, S>)
                  );
  NT2_TEST_TYPE_IS( typename boost::proto::result_of::value<child1>::value_type
                  , (container_ref<table_, T, S>)
                  );
}

template<class Expr>
void expr_lifetime_2_i(Expr const&)
{
  std::cout << __FUNCTION__ << std::endl;

  using nt2::tag::table_;
  using nt2::memory::container;
  using nt2::memory::container_ref;

  typedef double T;
  typedef nt2::settings S(nt2::_4D);

  typedef typename boost::proto::result_of::child_c<Expr, 0>::value_type child0;
  typedef typename boost::proto::result_of::child_c<Expr, 1>::value_type child1;

  NT2_TEST( is_nt2_basic_expr<Expr>() );
  NT2_TEST( is_nt2_basic_expr<child0>() );
  NT2_TEST( is_nt2_basic_expr<child1>() );

  NT2_TEST( !boost::is_reference<child0>::value );
  NT2_TEST( !boost::is_const<child0>::value     );
  NT2_TEST( !boost::is_reference<child1>::value );
  NT2_TEST( !boost::is_const<child1>::value     );

  NT2_TEST_TYPE_IS( typename boost::proto::result_of::value<child0>::value_type
                  , (container_ref<table_,T,S>)
                  );
  NT2_TEST_TYPE_IS( typename boost::proto::result_of::value<child1>::value_type
                  , T
                  );
}

template<class Expr>
void expr_lifetime_2_ir(Expr const&)
{
  std::cout << __FUNCTION__ << std::endl;

  using nt2::tag::table_;
  using nt2::memory::container;
  using nt2::memory::container_ref;

  typedef double T;
  typedef nt2::settings S(nt2::_4D);

  typedef typename boost::proto::result_of::child_c<Expr, 0>::value_type child0;
  typedef typename boost::proto::result_of::child_c<Expr, 1>::value_type child1;

  NT2_TEST( is_nt2_basic_expr<Expr>() );
  NT2_TEST( is_nt2_basic_expr<child0>() );
  NT2_TEST( is_nt2_basic_expr<child1>() );

  NT2_TEST( !boost::is_reference<child0>::value );
  NT2_TEST( !boost::is_const<child0>::value     );
  NT2_TEST( !boost::is_reference<child1>::value );
  NT2_TEST( !boost::is_const<child1>::value     );

  NT2_TEST_TYPE_IS( typename boost::proto::result_of::value<child0>::value_type
                  , (container_ref<table_,T,S>)
                  );
  NT2_TEST_TYPE_IS( typename boost::proto::result_of::value<child1>::value_type
                  , T&
                  );
}

template<class Expr>
void expr_lifetime_tie_i(Expr const&)
{
  std::cout << __FUNCTION__ << std::endl;

  using nt2::memory::container;

  typedef double T;
  //typedef nt2::settings S(nt2::_4D);

  typedef typename boost::proto::result_of::child_c<Expr&, 0>::value_type child0;

  NT2_TEST( is_nt2_basic_expr<Expr>() );
  NT2_TEST( is_nt2_basic_expr<child0>() );

  typedef typename boost::proto::result_of::value<child0>::value_type value;
  NT2_TEST( boost::is_reference<value>::value );
  NT2_TEST( !boost::is_const<child0>::value     );

  NT2_TEST_TYPE_IS( typename boost::proto::result_of::value<child0>::value_type
                  , T&
                  );
}

template<class Expr>
void expr_lifetime_tie_t(Expr const&)
{
  std::cout << __FUNCTION__ << std::endl;

  using nt2::tag::table_;
  using nt2::memory::container;

  typedef double T;
  typedef nt2::settings S(nt2::_4D);

  typedef typename boost::proto::result_of::child_c<Expr&, 0>::value_type child0;

  NT2_TEST( is_nt2_basic_expr<Expr>() );
  NT2_TEST( is_nt2_basic_expr<child0>() );

  typedef typename boost::proto::result_of::value<child0>::value_type value;
  NT2_TEST( boost::is_reference<value>::value );
  NT2_TEST( !boost::is_const<child0>::value     );

  NT2_TEST_TYPE_IS( typename boost::proto::result_of::value<child0>::value_type
                  , (container<table_,T,S>&)
                  );
}

template<class Expr>
void expr_lifetime_tie_ts(Expr const&)
{
  std::cout << __FUNCTION__ << std::endl;

  using nt2::tag::table_;
  using nt2::memory::container;
  using nt2::memory::container_ref;
  using nt2::memory::container_shared_ref;

  typedef double T;
  typedef nt2::settings S(nt2::_4D);

  typedef typename boost::proto::result_of::child_c<Expr&, 0>::value_type child0;

  NT2_TEST( is_nt2_basic_expr<Expr>() );
  NT2_TEST( is_nt2_basic_expr<child0>() );

  typedef typename boost::proto::result_of::value<child0>::value_type value;
  NT2_TEST( !boost::is_reference<value>::value );
  NT2_TEST( !boost::is_const<child0>::value     );

  NT2_TEST_TYPE_IS( typename boost::proto::result_of::value<child0>::value_type
                  , (container_shared_ref<table_, T, S, true>)
                  );
}

template<class Expr>
void expr_lifetime_assign(Expr&)
{
  std::cout << __FUNCTION__ << std::endl;

  typedef double T;
  NT2_TEST_TYPE_IS( Expr&, T& );
}

NT2_TEST_CASE( expr_lifetime )
{
  using nt2::table;
  using nt2::tag::table_;
  using boost::mpl::_;

  typedef double T;
  typedef nt2::settings S(nt2::_4D);
  table<T, S> a0, a1;
  T i;
  typedef boost::dispatch::meta::terminal_of_shared< nt2::memory::container<table_,T, S> > shared;
  shared::type a2 = shared::make(), a3 = shared::make();

  expr_lifetime_0(a0);
  expr_lifetime_2_t(nt2::pplus(a0, a1));
  expr_lifetime_2_i(nt2::pplus(a0, i));
  expr_lifetime_2_ir(nt2::pplus(a0, boost::proto::as_child(i)));
  expr_lifetime_tie_i(nt2::tie(i));
  expr_lifetime_tie_t(nt2::tie(a0));
  expr_lifetime_tie_ts(nt2::tie(a2));
  expr_lifetime_2_t(nt2::pplus(boost::proto::child_c<0>(nt2::tie(a0)), a1));
  expr_lifetime_2_ts(nt2::pplus(boost::proto::child_c<0>(nt2::tie(a2)), a1));
  expr_lifetime_assign(nt2::assign(i, nt2::sum(a0(nt2::_))));
}

template<class T>
struct extent_type
{
  typedef typename T::extent_type type;
};

template<class T>
struct sizes_type
{
  typedef typename T::sizes_t type;
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
                    , _3D
                    );
  NT2_TEST_EXPR_TYPE( a0
                    , sizes_type<_>
                    , _3D const&
                    );

  NT2_TEST_EQUAL( a0.extent(), of_size(0 ) );

  NT2_TEST_EXPR_TYPE( a0 + a0
                    , extent_type<_>
                    , _3D
                    );
  NT2_TEST_EXPR_TYPE( a0 + a0
                    , sizes_type<_>
                    , _3D
                    );

  NT2_TEST_EXPR_TYPE( a0 + a1
                    , extent_type<_>
                    , _2D
                    );

  NT2_TEST_EXPR_TYPE( a2 + a3 + a4
                    , extent_type<_>
                    , (of_size_<1, 2>)
                    );

  NT2_TEST_THROW( a0 + a2, nt2::assert_exception );

  NT2_TEST_EQUAL( (a2 + a2).extent(), of_size(1, 2) );

  NT2_TEST_EXPR_TYPE( nt2::assign(a0, a1)
                    , extent_type<_>
                    , _2D
                    );
  NT2_TEST_EXPR_TYPE( nt2::assign(a0, a1)
                    , sizes_type<_>
                    , _2D
                    );

  NT2_TEST_EXPR_TYPE( nt2::assign(a0, a4)
                    , extent_type<_>
                    , (of_size_<1, 2>)
                    );
}


NT2_TEST_CASE( function )
{
  using boost::mpl::_;
  using nt2::table;
  typedef double T;

  table<T> a0, a1, a2;

  NT2_TEST_EXPR_TYPE( a0(a1)
                    , as_node<_>
                    , ( node2 < nt2::tag::function_
                              , nt2::tag::terminal_
                              , node4< nt2::tag::function_index_
                                     , node1 < nt2::tag::aggregate_
                                             , nt2::tag::terminal_
                                             >
                                     , nt2::tag::terminal_
                                     , nt2::tag::terminal_
                                     , nt2::tag::terminal_
                                     >
                              >
                      )
                    );
}

NT2_TEST_CASE( fma )
{
  using boost::mpl::_;
  using nt2::table;
  typedef double T;

  table<T> a0, a1, a2;

  NT2_TEST_EXPR_TYPE( a0 * a1 + a2 * a0
                    , as_node<_>
                    , ( node3< nt2::tag::fma_
                             , nt2::tag::terminal_
                             , nt2::tag::terminal_
                             , node2< nt2::tag::multiplies_
                                    , nt2::tag::terminal_
                                    , nt2::tag::terminal_
                                    >
                             >
                      )
                    );

  NT2_TEST_EXPR_TYPE( a0 * a1 + a2
                    , as_node<_>
                    , ( node3< nt2::tag::fma_
                             , nt2::tag::terminal_
                             , nt2::tag::terminal_
                             , nt2::tag::terminal_
                             >
                      )
                    );

  NT2_TEST_EXPR_TYPE( a0 + a1 * a2
                    , as_node<_>
                    , ( node3< nt2::tag::fma_
                             , nt2::tag::terminal_
                             , nt2::tag::terminal_
                             , nt2::tag::terminal_
                             >
                      )
                    );

  NT2_TEST_EXPR_TYPE( a0 * a1 + (a2 * a0 + a1)
                    , as_node<_>
                    , ( node3< nt2::tag::fma_
                             , nt2::tag::terminal_
                             , nt2::tag::terminal_
                             , node3< nt2::tag::fma_
                                    , nt2::tag::terminal_
                                    , nt2::tag::terminal_
                                    , nt2::tag::terminal_
                                    >
                             >
                      )
                    );

  NT2_TEST_EXPR_TYPE( a0 + a1 * (a2 * a0 + a1)
                    , as_node<_>
                    , ( node3< nt2::tag::fma_
                             , nt2::tag::terminal_
                             , node3< nt2::tag::fma_
                                    , nt2::tag::terminal_
                                    , nt2::tag::terminal_
                                    , nt2::tag::terminal_
                                    >
                             , nt2::tag::terminal_
                             >
                      )
                    );
}
