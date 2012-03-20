//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_CONTAINER_DSL_DETAILS_EXTRACTIVE_HPP_INCLUDED
#define NT2_CORE_CONTAINER_DSL_DETAILS_EXTRACTIVE_HPP_INCLUDED

#include <boost/proto/core.hpp>
#include <boost/proto/traits.hpp>
#include <boost/proto/transform.hpp>

namespace nt2 { namespace container { namespace ext
{
  //============================================================================
  // This is the factorized generator for all extractive function.
  // For any given generative function tag XTR, the registration of their
  // generator is simply :
  //
  // namespace nt2 { namespace container { namespace ext
  // {
  //  template<class D, class X, int N>
  //  struct generator<XTR,D,N,X> : extractive_generator<X> {};
  // } } }
  //
  //============================================================================
  template<class Expr> struct extractive_generator
  {
    //==========================================================================
    // Behaves like his first child
    //==========================================================================
    typedef typename boost::proto::result_of::child_c<Expr,0>::type   expr_t;
    typedef typename boost::dispatch::meta::semantic_of<expr_t>::type sema_t;

    //==========================================================================
    // Extractive is like a normal expression *except* it change the shape of
    // the result which is accessible via Tag::shape_type
    //==========================================================================
    typedef typename boost::proto::tag_of<Expr>::type             tag_type;
    typedef typename tag_type::shape_type                         shape_type;
    typedef typename meta::add_settings<sema_t, shape_type>::type type;

    typedef expression< typename boost::remove_const<Expr>::type
                      , type
                      >                                     result_type;

    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      return result_type(e);
    }
  };

  //============================================================================
  // This is the factorized size_of for all extractive function.
  // For any given generative function tag XTR, the registration of their
  // size_of is simply :
  //
  // namespace nt2 { namespace container { namespace ext
  // {
  //  template<class D, class X, int N>
  //  struct size_of<XTR,D,N,X> : extractive_size_of<X> {};
  // } } }
  //
  //============================================================================
  template<class Expr> struct extractive_size_of
  {
    typedef typename boost::proto::result_of::child_c<Expr,0>::type expr_t;
    typedef typename expr_t::extent_type                            result_type;

    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      return boost::proto::child_c<0>(e).extent();
    }
  };
} } }

#endif
