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
#include <boost/proto/domain.hpp>

#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_const.hpp>

namespace nt2 { namespace container
{
  struct  domain
        : boost::proto::domain< container::generator_transform<domain>
                              , container::grammar
                              >
  {
    template<class T, class Dummy = void>
    struct  as_child
          : domain::proto_base_domain::template as_child<T> {};

    template<class T>
    struct  as_child<T, typename T::proto_is_expr_>
          : boost::proto::callable
    {
      typedef typename boost::proto::tag_of<T>::type Tag;

      typedef typename boost::mpl::
              if_< boost::is_same<Tag, boost::proto::tag::terminal>
                 , T&
                 , typename boost::remove_const<T>::type
                 >::type                              result_type;

      BOOST_FORCEINLINE result_type operator()(T& t) const
      {
        return result_type(t);
      }
    };
  };
} }

#endif
