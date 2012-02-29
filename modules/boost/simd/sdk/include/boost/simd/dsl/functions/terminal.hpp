//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_DSL_FUNCTIONS_TERMINAL_HPP_INCLUDED
#define BOOST_SIMD_DSL_FUNCTIONS_TERMINAL_HPP_INCLUDED

#include <boost/proto/tags.hpp>
#include <boost/dispatch/functor/preprocessor/function.hpp>
#include <boost/simd/sdk/functor/hierarchy.hpp>

namespace boost { namespace simd
{
  namespace tag
  {
    struct terminal_ : ext::elementwise_<terminal_> { typedef ext::elementwise_<terminal_> parent; };
  }

  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::terminal_, terminal, 1)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(tag::terminal_, terminal, (A0 const&)(A1&), 2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(tag::terminal_, terminal, (A0 const&)(A1&)(A2 const&), 3)
} }

namespace boost { namespace dispatch { namespace meta
{
  template<>
  struct hierarchy_of<boost::proto::tag::terminal>
  {
    typedef boost::simd::tag::terminal_ type;
  };
  template<>
  struct proto_tag<boost::simd::tag::terminal_>
  {
    typedef boost::proto::tag::terminal type;
  };
} } }

#endif
