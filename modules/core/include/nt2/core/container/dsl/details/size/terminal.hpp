//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_CONTAINER_DSL_DETAILS_SIZE_TERMINAL_HPP_INCLUDED
#define NT2_CORE_CONTAINER_DSL_DETAILS_SIZE_TERMINAL_HPP_INCLUDED

#include <nt2/include/functions/extent.hpp>
#include <nt2/dsl/functions/terminal.hpp>
#include <boost/proto/traits.hpp>

namespace nt2 { namespace ext
{
  //============================================================================
  // Terminal size is stored as a reference to the terminal value size
  //============================================================================
  template<class Domain, class Expr>
  struct size_of<boost::simd::tag::terminal_,Domain,0,Expr>
  {
    typedef typename boost::proto::result_of::value<Expr&>::type  term_t;
    typedef typename meta::call<tag::extent_(term_t)>::type       result_type;

    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      return nt2::extent(boost::proto::value(e));
    }
  };

  template<class Tag, class Domain, class Expr>
  struct size_of<Tag,Domain,0,Expr>
  {
    typedef typename boost::proto::result_of::value<Expr&>::type  term_t;
    typedef typename meta::call<Tag(term_t)>::type                value_t;
    typedef typename meta::call<tag::extent_(value_t)>::type      result_type;

    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      typename make_functor<Tag,Expr>::type callee;
      return nt2::extent(callee(boost::proto::value(e)));
    }
  };
} }

#endif

