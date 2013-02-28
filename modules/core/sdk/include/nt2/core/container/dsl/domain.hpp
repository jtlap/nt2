//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_CONTAINER_DSL_DOMAIN_HPP_INCLUDED
#define NT2_CORE_CONTAINER_DSL_DOMAIN_HPP_INCLUDED

#include <nt2/core/container/dsl/forward.hpp>
#include <nt2/core/container/dsl/generator.hpp>
#include <nt2/core/container/dsl/grammar.hpp>
#include <nt2/dsl/functions/run.hpp>
#include <nt2/toolbox/operator/functions/assign.hpp>
#include <nt2/sdk/memory/container_ref.hpp>
#include <nt2/sdk/memory/container_shared_ref.hpp>
#include <boost/proto/domain.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/is_const.hpp>

namespace nt2 { namespace meta
{
  template<class T>
  struct is_elementwise
  {
    typedef char true_type;
    struct false_type { char dummy[2]; };

    template<class X>
    static true_type call(ext::elementwise_<X> const&);
    static false_type call(...);

    typedef typename boost::dispatch::meta::hierarchy_of<T>::type Tag;
    static const bool value = sizeof(call(Tag())) == sizeof(true_type);
    typedef boost::mpl::bool_<value> type;
  };

  /* If T is an expression, do nothing; otherwise call as_child in the domain
   * with T as a reference */
  template<class T, class Domain, class Dummy = void>
  struct as_child
  {
    typedef typename Domain::template as_child<T&>::result_type type;
    static BOOST_FORCEINLINE type call(T& t)
    {
      return typename Domain::template as_child<T&>()(t);
    }
  };

  template<class T, class Domain>
  struct as_child<T, Domain, typename T::proto_is_expr_>
  {
    typedef T type;
    static BOOST_FORCEINLINE T& call(T& t)
    {
      return t;
    }
  };
} }

namespace nt2 { namespace container
{
  template<class T, class S = nt2::settings()>
  struct table_view
       : expression< boost::proto::basic_expr< boost::proto::tag::terminal, boost::proto::term< memory::container_ref<T, S> >, 0l >
                   , memory::container<T, S>&
                   >
  {
    typedef memory::container_ref<T, S> container_ref;
    typedef boost::proto::basic_expr< boost::proto::tag::terminal, boost::proto::term<container_ref>, 0l > basic_expr;
    typedef memory::container<T, S>& semantic;
    typedef expression<basic_expr, semantic> nt2_expression;

    typedef typename container_ref::iterator iterator;
    typedef typename container_ref::const_iterator const_iterator;

    iterator begin() const
    {
      return boost::proto::value(*this).begin();
    }

    iterator end() const
    {
      return boost::proto::value(*this).end();
    }

    BOOST_FORCEINLINE
    table_view()
    {
    }

    BOOST_FORCEINLINE
    table_view( nt2_expression const& expr )
              : nt2_expression(expr)
    {
    }

    BOOST_FORCEINLINE
    table_view( expression< boost::proto::basic_expr< boost::proto::tag::terminal, boost::proto::term< memory::container<T, S> >, 0l >
                          , memory::container<T, S>
                          > & expr
              )
              : nt2_expression(basic_expr::make(boost::proto::value(expr)))
    {
    }

    BOOST_FORCEINLINE
    table_view( expression< boost::proto::basic_expr< boost::proto::tag::terminal, boost::proto::term< memory::container<T, S>& >, 0l >
                          , memory::container<T, S>&
                          > const& expr
              )
              : nt2_expression(basic_expr::make(boost::proto::value(expr)))
    {
    }

    template<class S2>
    BOOST_FORCEINLINE
    table_view( table_view<T, S2> const& expr )
              : nt2_expression(basic_expr::make(boost::proto::value(expr)))
    {
    }

    using nt2_expression::operator=;
  };

  template<class T, class S>
  struct table_view<T const, S>
       : expression< boost::proto::basic_expr< boost::proto::tag::terminal, boost::proto::term< memory::container_ref<T const, S> >, 0l >
                   , memory::container<T, S> const&
                   >
  {
    typedef memory::container_ref<T const, S> container_ref;
    typedef boost::proto::basic_expr< boost::proto::tag::terminal, boost::proto::term<container_ref>, 0l > basic_expr;
    typedef memory::container<T, S> const& semantic;
    typedef expression<basic_expr, semantic> nt2_expression;

    typedef typename container_ref::iterator iterator;
    typedef typename container_ref::const_iterator const_iterator;

    iterator begin() const
    {
      return boost::proto::value(*this).begin();
    }

    iterator end() const
    {
      return boost::proto::value(*this).end();
    }

    BOOST_FORCEINLINE
    table_view()
    {
    }

    BOOST_FORCEINLINE
    table_view( nt2_expression const& expr )
              : nt2_expression(expr)
    {
    }

    BOOST_FORCEINLINE
    table_view( expression< boost::proto::basic_expr< boost::proto::tag::terminal, boost::proto::term< memory::container<T, S> >, 0l >
                          , memory::container<T, S>
                          > const& expr
              )
              : nt2_expression(basic_expr::make(boost::proto::value(expr)))
    {
    }

    BOOST_FORCEINLINE
    table_view( expression< boost::proto::basic_expr< boost::proto::tag::terminal, boost::proto::term< memory::container<T, S> const& >, 0l >
                          , memory::container<T, S> const&
                          > const& expr
              )
              : nt2_expression(basic_expr::make(boost::proto::value(expr)))
    {
    }

    template<class U, class S2>
    BOOST_FORCEINLINE
    table_view( table_view<U, S2> const& expr )
              : nt2_expression(basic_expr::make(boost::proto::value(expr)))
    {
    }

    using nt2_expression::operator=;
  };

  template<class T, class S = nt2::settings()>
  struct table_shared_view
       : expression< boost::proto::basic_expr< boost::proto::tag::terminal, boost::proto::term< memory::container_shared_ref< T, S, false > >, 0l >
                   , memory::container<T, S>&
                   >
  {
    typedef memory::container_shared_ref< T, S, false > container_ref;
    typedef boost::proto::basic_expr< boost::proto::tag::terminal, boost::proto::term<container_ref>, 0l > basic_expr;
    typedef memory::container<T, S>& semantic;
    typedef expression<basic_expr, semantic> nt2_expression;

    typedef typename container_ref::iterator iterator;
    typedef typename container_ref::const_iterator const_iterator;

    iterator begin() const
    {
      return boost::proto::value(*this).begin();
    }

    iterator end() const
    {
      return boost::proto::value(*this).end();
    }

    BOOST_FORCEINLINE
    table_shared_view()
    {
    }

    BOOST_FORCEINLINE
    table_shared_view( nt2_expression const& expr )
                     : nt2_expression(expr)
    {
    }

    template<class S2, bool Own>
    BOOST_FORCEINLINE
    table_shared_view( expression< boost::proto::basic_expr< boost::proto::tag::terminal, boost::proto::term< memory::container_shared_ref< T, S2, Own > >, 0l >
                                 , memory::container<T, S2>&
                                 > const& expr
                     )
                     : nt2_expression(basic_expr::make(boost::proto::value(expr)))
    {
    }

    using nt2_expression::operator=;
  };

  template<class T, class S>
  struct table_shared_view<T const, S>
       : expression< boost::proto::basic_expr< boost::proto::tag::terminal, boost::proto::term< memory::container_shared_ref< T const, S, false > >, 0l >
                   , memory::container<T, S> const&
                   >
  {
    typedef memory::container_shared_ref< T const, S, false > container_ref;
    typedef boost::proto::basic_expr< boost::proto::tag::terminal, boost::proto::term<container_ref>, 0l > basic_expr;
    typedef memory::container<T, S> const& semantic;
    typedef expression<basic_expr, semantic> nt2_expression;

    typedef typename container_ref::iterator iterator;
    typedef typename container_ref::const_iterator const_iterator;

    iterator begin() const
    {
      return boost::proto::value(*this).begin();
    }

    iterator end() const
    {
      return boost::proto::value(*this).end();
    }

    BOOST_FORCEINLINE
    table_shared_view()
    {
    }

    BOOST_FORCEINLINE
    table_shared_view( nt2_expression const& expr )
                     : nt2_expression(expr)
    {
    }

    template<class U, class S2, bool Own>
    BOOST_FORCEINLINE
    table_shared_view( expression< boost::proto::basic_expr< boost::proto::tag::terminal, boost::proto::term< memory::container_shared_ref< U, S2, Own > >, 0l >
                                 , memory::container<U, S2> /*const?*/&
                                 > const& expr
                     )
                     : nt2_expression(basic_expr::make(boost::proto::value(expr)))
    {
    }

    using nt2_expression::operator=;
  };

  template<class Expr, class T>
  struct as_view_impl_term
       : boost::remove_const<Expr>
  {
  };

  template<class Expr, class T, class S>
  struct as_view_impl_term< Expr, memory::container<T, S>& >
  {
    typedef table_view<T, S> type;
  };

  template<class Expr, class T, class S>
  struct as_view_impl_term< Expr, memory::container<T, S> const& >
  {
    typedef table_view<T const, S> type;
  };

  template<class Expr, class T, class S>
  struct as_view_impl_term< Expr, memory::container_shared_ref<T, S, true> & >
  {
    typedef table_shared_view<T, S> type;
  };

  template<class Expr, class T, class S>
  struct as_view_impl_term< Expr, memory::container_shared_ref<T, S, true> const& >
  {
    typedef table_shared_view<T, S> type;
  };

  template<class T, class Tag = typename T::proto_tag>
  struct as_view_impl
  {
    typedef typename boost::remove_const<T>::type type;
    static BOOST_FORCEINLINE T& call(T& t)
    {
      return t;
    }
  };

  template<class T>
  struct as_view_impl<T, boost::proto::tag::terminal>
  {
    typedef typename as_view_impl_term<T, typename boost::proto::result_of::value<T&>::type>::type type;
    static BOOST_FORCEINLINE type call(T& t)
    {
      return type(t);
    }
  };

  template<class T>
  BOOST_FORCEINLINE
  typename as_view_impl<T>::type as_view(T& t)
  {
    return as_view_impl<T>::call(t);
  }

  template<class T>
  BOOST_FORCEINLINE
  typename as_view_impl<T const>::type as_view(T const& t)
  {
    return as_view_impl<T const>::call(t);
  }

  /* The nt2 container domain has special rules so that children are held by value,
   * non-elementwise operations get scheduled and
   * containers are held by reference or as a container_ref value */
  struct  domain
        : boost::proto::domain< container::generator_transform<domain>
                              , container::grammar
                              >
  {
    // Construct an expression from a non-expression
    // - by value unless manually called with a reference
    // - semantic is same as terminal value
    template<class T, class Dummy = void, class Sema = void>
    struct as_child : boost::proto::callable
    {
      typedef typename boost::remove_const<T>::type term_t;
      typedef boost::proto::basic_expr< boost::proto::tag::terminal, boost::proto::term<term_t> > expr_t;
      typedef expression<expr_t, typename boost::mpl::if_< boost::is_void<Sema>, typename boost::remove_const<T>::type, Sema >::type> result_type;
      BOOST_FORCEINLINE result_type operator()(typename boost::add_reference<T>::type t) const
      {
        return result_type(expr_t::make(t));
      }
    };

    template<class T, bool B>
    struct as_child_elementwise;

    template<class T>
    struct as_child_elementwise<T, true>
         : boost::proto::callable
    {
      typedef typename boost::remove_const<T>::type result_type;
      BOOST_FORCEINLINE result_type operator()(T& t) const
      {
        return result_type(t);
      }
    };

    // Schedule non-elementwise expression, return terminal (shared owning container_ref)
    template<class T>
    struct as_child_elementwise<T, false>
         : boost::proto::callable
    {
      typedef typename boost::dispatch::meta::semantic_of<T&>::type              semantic;
      typedef typename boost::dispatch::meta::terminal_of_shared<semantic>::type terminal;
      typedef as_child<terminal>                                                 terminal_expr;
      typedef meta::as_child<terminal, domain>                                   terminal_ref;
      typedef typename terminal_expr::result_type                                result_type;

      BOOST_FORCEINLINE result_type operator()(T& t) const
      {
        terminal term = boost::dispatch::meta::terminal_of_shared<semantic>::make();
        nt2::run(nt2::assign(terminal_ref::call(term), t));
        return terminal_expr()(term);
      }
    };

    template<class T, class Tag, bool Schedule = boost::is_same<typename T::proto_domain, domain>::value>
    struct as_child_expr
         : as_child_elementwise<T, meta::is_elementwise<Tag>::value || !Schedule >
    {
    };

    // Scheduled terminals: converted to views
    template<class T>
    struct as_child_expr<T, boost::proto::tag::terminal, true>
     : boost::proto::callable
    {
      typedef typename as_view_impl<T>::type result_type;

      BOOST_FORCEINLINE result_type operator()(T& t) const
      {
        return as_view_impl<T>::call(t);
      }
    };

    // Non-scheduled terminals: ensure tables are held by reference
    template<class T>
    struct as_child_expr<T, boost::proto::tag::terminal, false>
     : boost::proto::callable
    {
      typedef typename boost::proto::result_of::value<T&>::value_type value_type;
      typedef typename boost::mpl::if_< boost::is_const<T>, typename boost::add_const<value_type>::type, value_type >::type type;
      typedef typename boost::mpl::if_c< meta::is_container<value_type>::value && !meta::is_container_ref<value_type>::value, type&, type >::type type_ref;
      typedef as_child<type_ref, void, typename boost::dispatch::meta::semantic_of<T&>::type> impl;
      typedef typename impl::result_type result_type;

      BOOST_FORCEINLINE result_type operator()(T& t) const
      {
        return impl()(boost::proto::value(t));
      }
    };

    template<class T>
    struct as_child<T, typename T::proto_is_expr_>
         : as_child_expr<T, typename T::proto_tag> {};
  };
} }

namespace boost { namespace dispatch { namespace meta
{
  template<class T, class S>
  struct semantic_of< nt2::container::table_view<T, S> >
  {
    typedef typename nt2::container::table_view<T, S>::semantic type;
  };

  template<class T, class S>
  struct semantic_of< nt2::container::table_shared_view<T, S> >
  {
    typedef typename nt2::container::table_shared_view<T, S>::semantic type;
  };
} } }

namespace nt2
{
  using nt2::container::table_view;
  using nt2::container::table_shared_view;
}

#endif
