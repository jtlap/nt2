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
#include <nt2/sdk/meta/is_container.hpp>
#include <boost/proto/domain.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/is_const.hpp>

namespace nt2 { namespace container
{
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
      typedef expression<expr_t, term_t> result_type;
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
      typedef typename boost::mpl::if_< meta::is_container<type>, typename boost::add_reference<type>::type, type>::type term;

      typedef as_child<term> impl;
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

#endif
