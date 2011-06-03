//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_FUNCTOR_FORWARD_HPP_INCLUDED
#define NT2_SDK_FUNCTOR_FORWARD_HPP_INCLUDED

#include <nt2/sdk/functor/meta/hierarchy.hpp>
#include <boost/proto/tags.hpp>

namespace nt2
{
  //============================================================================
  /*
   * default_site defines the architecture dependant default evaluation context
   * for functors.
   */
  //============================================================================
  template< class Tag, class Enable = void > struct default_site
  {
    typedef tag::cpu_ type;
  };

  template< class Tag
          , class EvalContext = typename default_site<Tag>::type
          >
  struct functor;
}

namespace nt2 { namespace ext
{
  template< class Signature , class Site, class Dummy = void> struct call;
  template< class Signature , class Site, class Dummy = void> struct validate;
} }

namespace nt2
{
  namespace tag
  {
    typedef boost::proto::tag::terminal terminal_;
  }
}

#endif
