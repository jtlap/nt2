//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_UTILITY_GENERATIVE_ADAPTED_HPP_INCLUDED
#define NT2_CORE_UTILITY_GENERATIVE_ADAPTED_HPP_INCLUDED

#include <nt2/sdk/meta/is_container.hpp>
#include <nt2/sdk/meta/container_of.hpp>
#include <nt2/sdk/meta/dimensions_of.hpp>
#include <boost/dispatch/meta/model_of.hpp>
#include <boost/dispatch/meta/value_of.hpp>
#include <boost/dispatch/meta/terminal_of.hpp>

//==============================================================================
// Forward declaration
//==============================================================================
namespace nt2 { namespace details
{
  template<class Tag, class Functor, class T, class S> struct generative;
} }

namespace nt2 { namespace meta
{
  //============================================================================
  // Register container as a proper container
  //============================================================================
  template<class Tag, class F, class T, class S>
  struct is_container< details::generative<Tag,F,T,S> > : boost::mpl::true_ {};
} }

namespace boost { namespace dispatch { namespace meta
{
  //============================================================================
  // Generative acts as the same hiierarchy of its Tag
  //============================================================================
  template<class Tag, class F, class T, class S, class Origin>
  struct hierarchy_of< nt2::details::generative<Tag,F,T,S>, Origin >
  {
    typedef generative_ < typename hierarchy_of<T,Origin>::type
                        , F
                        > type;
  };

  //============================================================================
  // value_of specialization
  //============================================================================
  template<class Tag, class F, class T, class S>
  struct value_of< nt2::details::generative<Tag,F,T,S> >
  {
    typedef T type;
  };

  //============================================================================
  // model_of specialization
  //============================================================================
  template<class Tag, class F, class T, class S>
  struct model_of< nt2::details::generative<Tag,F,T,S> >
  {
    struct type
    {
      template<class X>
      struct apply { typedef nt2::details::generative<Tag,F,X,S> type; };
    };
  };
} } }

#endif
