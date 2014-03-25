//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_SVD_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_SVD_HPP_INCLUDED

#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/size_as.hpp>
#include <nt2/sdk/meta/value_as.hpp>
#include <nt2/sdk/meta/as_real.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/sdk/meta/tieable_hierarchy.hpp>
#include <nt2/core/container/dsl/value_type.hpp>

namespace nt2
{
  namespace tag
  {
    struct svd_ : ext::tieable_<svd_>
    {
      typedef ext::tieable_<svd_>  parent;
    };
  }

  /**

   **/
  NT2_FUNCTION_IMPLEMENTATION(tag::svd_, svd, 1)
  NT2_FUNCTION_IMPLEMENTATION(tag::svd_, svd, 2)
}

namespace nt2 { namespace ext
{
  template<class Domain, int N, class Expr>
  struct  size_of<tag::svd_,Domain,N,Expr>
        : meta::size_as<Expr,0>
  {};

  template<class Domain, class Expr>
  struct  value_type<tag::svd_,Domain,1,Expr>
  {
    typedef typename boost::proto::result_of::child_c<Expr&,0>::value_type child0;
    typedef typename child0::value_type c_type;
    typedef typename nt2::meta::as_real<c_type>::type  type;
  };

  template<class Domain, int N, class Expr>
  struct  value_type<tag::svd_,Domain,N,Expr>
        : meta::value_as<Expr,0>
  {};
} }

#endif
