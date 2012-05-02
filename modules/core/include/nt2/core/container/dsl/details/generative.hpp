//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_CONTAINER_DSL_DETAILS_GENERATIVE_HPP_INCLUDED
#define NT2_CORE_CONTAINER_DSL_DETAILS_GENERATIVE_HPP_INCLUDED

#include <boost/proto/core.hpp>
#include <boost/proto/traits.hpp>
#include <boost/proto/transform.hpp>
#include <nt2/sdk/memory/container.hpp>
#include <nt2/core/container/dsl/details/generate_as.hpp>

namespace nt2 { namespace container { namespace ext
{
  //============================================================================
  // This is the factorized size_of for all generative function.
  // For any given generative function tag GEN, the registration of their
  // size_of is simply :
  //
  // namespace nt2 { namespace container { namespace ext
  // {
  //  template<class Domain, class Expr, int N>
  //  struct size_of<GEN,Domain,N,Expr> : generative_size_of<Expr>
  //  {};
  // } } }
  //
  //============================================================================
  template<class Expr> struct generative_size_of : boxed_size_of<Expr,0> {};

  //============================================================================
  // This is the factorized generator for all generative function.
  // For any given generative function tag GEN, the registration of their
  // generator is simply :
  //
  // namespace nt2 { namespace container { namespace ext
  // {
  //  template<class Domain, class Expr, int N>
  //  struct generator<GEN,Domain,N,Expr> : generative_generator<Expr>
  //  {};
  // } } }
  //
  //============================================================================
  template<class Expr> struct generative_generator
  {
    // The size is contained in the first child : box<Size>
    typedef typename generative_size_of<Expr>::result_type  sizeof_t;
    typedef typename meta::strip<sizeof_t>::type            sizes_t;

    // The target is contained in the second child : as_<T>
    typedef typename boost::proto::result_of::child_c<Expr,2>::type tgt_term;
    typedef typename boost::proto::result_of::value<tgt_term>::type target_t;

    // Rebuidl proper expression type with semantic
    typedef expression< typename boost::remove_const<Expr>::type
                      , memory::container < typename target_t::type
                                          , sizes_t
                                          >
                      >                                     result_type;

    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      return result_type(e);
    }
  };
} } }

#endif
