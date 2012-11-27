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

  /* Same as boost::proto::as_expr, but doesn't do anything if input
   * is already an expression */
  template<class T, class Domain, class Dummy = void>
  struct as_expr
  {
    typedef typename Domain::template as_expr<T>::result_type type;
    static BOOST_FORCEINLINE type call(T& t)
    {
      return typename Domain::template as_expr<T>()(t);
    }
  };

  template<class T, class Domain>
  struct as_expr<T, Domain, typename T::proto_is_expr_>
  {
    typedef T type;
    static BOOST_FORCEINLINE T& call(T& t)
    {
      return t;
    }
  };

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
  // Convert terminal of containers to terminals of container_ref
  template<class T, class Dummy = void>
  struct as_container_ref
  {
    typedef T type;
    static BOOST_FORCEINLINE typename boost::add_reference<T>::type
    call(typename boost::add_reference<T>::type t)
    {
      return t;
    }
  };

  template<class T>
  struct as_container_ref<T, typename boost::enable_if_c< meta::is_container<T>::value && !meta::is_container_ref<T>::value >::type>
  {
    typedef memory::container_ref<typename boost::remove_reference<T>::type> const type;
    static BOOST_FORCEINLINE type
    call(T& t)
    {
      return type(t);
    }
  };

  template<class Container, bool Own>
  struct as_container_ref< memory::container_shared_ref<Container, Own> >
  {
    typedef memory::container_shared_ref<Container> const type;
    static BOOST_FORCEINLINE type
    call(memory::container_shared_ref<Container, Own>& t)
    {
      return type(t.base());
    }
  };

  template<class Container, bool Own>
  struct as_container_ref< memory::container_shared_ref<Container, Own> const >
  {
    typedef memory::container_shared_ref<Container> const type;
    static BOOST_FORCEINLINE type
    call(memory::container_shared_ref<Container, Own> const& t)
    {
      return type(t.base());
    }
  };

  // Convert container_ref to container for semantic
  template<class T, class Dummy = void>
  struct as_container_noref
  {
    typedef T type;
  };

  template<class T>
  struct as_container_noref<T, typename boost::enable_if< typename meta::is_container_ref<T>::type >::type>
  {
    typedef typename T::base_t type0;
    typedef typename boost::mpl::if_< boost::is_const<T>, type0 const&, type0&>::type type;
  };

  /* The nt2 container domain has special rules so that children are held by value and
   * containers are held by a container_ref value */
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

    template<class T>
    struct as_child_elementwise<T, false>
         : boost::proto::callable
    {
      typedef typename boost::dispatch::meta::semantic_of<T&>::type              semantic;
      typedef typename boost::dispatch::meta::terminal_of_shared<semantic>::type terminal;
      typedef meta::as_expr<terminal, domain>                                    terminal_expr;
      typedef meta::as_child<terminal, domain>                                   terminal_ref;
      typedef typename terminal_expr::type                                       result_type;

      BOOST_FORCEINLINE result_type operator()(T& t) const
      {
        terminal term = boost::dispatch::meta::terminal_of_shared<semantic>::make();
        nt2::run(nt2::assign(terminal_ref::call(term), t));
        return terminal_expr::call(term);
      }
    };

    template<class T, class Tag, bool Schedule = true>
    struct as_child_expr
         : as_child_elementwise<T, meta::is_elementwise<Tag>::value || !Schedule >
    {
    };

    // Existing terminals get unpacked and re-created (necessary for table)
    template<class T, bool Schedule>
    struct as_child_expr<T, boost::proto::tag::terminal, Schedule>
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
