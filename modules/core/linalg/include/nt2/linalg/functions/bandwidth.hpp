//==============================================================================
//                Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_BANDWIDTH_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_BANDWIDTH_HPP_INCLUDED

#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/size_as.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/sdk/meta/tieable_hierarchy.hpp>

namespace nt2
{
  namespace tag
  {
    struct bandwidth_ : ext::tieable_<bandwidth_>
    {
      typedef ext::tieable_<bandwidth_>  parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_bandwidth_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site>
    BOOST_FORCEINLINE generic_dispatcher<tag::bandwidth_, Site> dispatching_bandwidth_(adl_helper, boost::dispatch::meta::unknown_<Site>, ...)
    {
      return generic_dispatcher<tag::bandwidth_, Site>();
    }
    template<class... Args>
    struct impl_bandwidth_;
  }

  /**

    @brief bandwidth computes the lower and upper bandwidth of a matrix

    @par Semantic:

    available call syntaxes are

    l =  bandwidth(a, lower_);
    u =  bandwidth(a, upper_);
    tie(l, u) =  bandwidth(a);

    where l and u are integral values
   **/
  NT2_FUNCTION_IMPLEMENTATION(tag::bandwidth_, bandwidth, 1)
  NT2_FUNCTION_IMPLEMENTATION(tag::bandwidth_, bandwidth, 2)
}

namespace nt2 { namespace ext
{
  template<class Domain, int N, class Expr>
  struct  size_of<tag::bandwidth_,Domain,N,Expr>
        : meta::size_as<Expr,0>
  {};
} }
#endif
