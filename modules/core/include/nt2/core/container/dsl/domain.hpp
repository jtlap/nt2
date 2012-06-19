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
#include <nt2/sdk/memory/container_ref.hpp>
#include <boost/proto/domain.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/is_const.hpp>

namespace nt2 { namespace container
{
  template<class T>
  struct as_container_ref
  {
    typedef T type;
    static BOOST_FORCEINLINE typename boost::add_reference<T>::type
    call(typename boost::add_reference<T>::type t)
    {
      return t;
    }
  };

  template<class T, class S>
  struct as_container_ref< memory::container<T, S> >
  {
    typedef memory::container_ref<T, S> const type;
    static BOOST_FORCEINLINE type
    call(memory::container<T, S>& t)
    {
      return type(t);
    }
  };

  template<class T, class S>
  struct as_container_ref< memory::container<T, S> const >
  {
    typedef memory::container_ref<T const, S> const type;
    static BOOST_FORCEINLINE type
    call(memory::container<T, S> const& t)
    {
      return type(t);
    }
  };

  template<class T>
  struct as_container_noref
  {
    typedef T type;
  };

  template<class T, class S>
  struct as_container_noref< nt2::memory::container_ref<T, S> >
  {
    typedef nt2::memory::container<typename boost::remove_const<T>::type, S> type0;
    typedef typename boost::mpl::if_< boost::is_const<T>, type0 const&, type0&>::type type;
  };

  struct  domain
        : boost::proto::domain< container::generator_transform<domain>
                              , container::grammar
                              >
  {
    template<class T, class Dummy = void>
    struct as_child : boost::proto::callable
    {
      typedef typename boost::remove_const<T>::type term_t;
      typedef boost::proto::basic_expr< boost::proto::tag::terminal, boost::proto::term<term_t> > expr_t;
      typedef expression<expr_t, typename as_container_noref<term_t>::type> result_type;
      BOOST_FORCEINLINE result_type operator()(typename boost::add_reference<T>::type t) const
      {
        return result_type(expr_t::make(t));
      }
    };

    template<class T, class Tag>
    struct as_child_expr : boost::proto::callable
    {
      typedef typename boost::remove_const<T>::type result_type;
      BOOST_FORCEINLINE result_type operator()(T& t) const
      {
        return result_type(t);
      }
    };

    template<class T>
    struct as_child_expr<T, boost::proto::tag::terminal>
     : boost::proto::callable
    {
      typedef typename boost::proto::result_of::value<T&>::value_type value_type;
      typedef typename boost::mpl::if_< boost::is_const<T>, typename boost::add_const<value_type>::type, value_type >::type type;
      typedef typename as_container_ref<type>::type term;

      typedef as_child<term> impl;
      typedef typename impl::result_type result_type;

      BOOST_FORCEINLINE result_type operator()(T& t) const
      {
        return impl()(as_container_ref<type>::call(boost::proto::value(t)));
      }
    };

    template<class T>
    struct as_child<T, typename T::proto_is_expr_>
         : as_child_expr<T, typename T::proto_tag> {};
  };
} }

#endif
