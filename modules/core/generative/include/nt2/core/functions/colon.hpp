//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_COLON_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_COLON_HPP_INCLUDED

/*!
  @file
  @brief Defines and implements the colon function
**/

#include <nt2/include/functor.hpp>
#include <nt2/core/container/dsl/generative.hpp>
#include <nt2/sdk/meta/generative_hierarchy.hpp>

namespace nt2
{
  namespace tag
  {
    struct colon_ : ext::state_constant_<colon_>
    {
      typedef ext::state_constant_<colon_> parent;
      typedef double                      default_type;
    };

    /// INTERNAL ONLY
    struct relative_colon_ : ext::elementwise_<relative_colon_>
    {
      typedef ext::elementwise_<relative_colon_> parent;
    };
  }

  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::colon_, colon, 2)
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::colon_, colon, 3)
}

namespace nt2 { namespace ext
{
  /// INTERNAL ONLY
  template<class Domain, class Expr, int N>
  struct  value_type<tag::colon_,Domain,N,Expr>
        : meta::generative_value<Expr> {};

  /// INTERNAL ONLY
  template<class Domain, class Expr, int N>
  struct  size_of<tag::colon_,Domain,N,Expr>
        : meta::generative_size<Expr> {};

  /// INTERNAL ONLY
  template<class Domain, class Expr, int N>
  struct  value_type<tag::relative_colon_,Domain,N,Expr>
  {
    typedef int type;
  };

  /// INTERNAL ONLY
  template<class Domain, class Expr>
  struct size_of<tag::relative_colon_,Domain,1,Expr>
  {
    typedef _0D result_type;
    BOOST_FORCEINLINE result_type operator()(Expr&) const
    {
      return result_type();
    }
  };

  /// INTERNAL ONLY
  template<class Domain, class Expr>
  struct size_of<tag::relative_colon_,Domain,2,Expr>
  {
    typedef _0D result_type;
    BOOST_FORCEINLINE result_type operator()(Expr&) const
    {
      return result_type();
    }
  };
} }

#endif
