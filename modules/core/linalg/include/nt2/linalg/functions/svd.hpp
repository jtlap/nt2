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
     s = svd(X)
     [u,s,v] = svd(x)
     [u,s,v] = svd(x,0)
     [u,s,v] = svd(x, econ_)
     [u,s,tv] = svd(x, lapack_)

     Description

     The svd command computes the matrix singular value decomposition.

     s = svd(x) returns a vector of singular values.

     [u,s,v] = svd(x) produces a diagonal matrix s of the same
     dimension as x, with nonnegative diagonal elements in decreasing
     order, and unitary matrices u and v so that x = u*s*v'.

     [u,s,v] = svd(x,0) produces the "economy size" decomposition. if
     x is m-by-n with m > n, then svd computes only the first n
     columns of u and s is n-by-n.

     [u,s,v] = svd(x,econ_) also produces the "economy size"
     decomposition. if x is m-by-n with m >= n, it is equivalent to
     svd(x,0). for m < n, only the first m columns of v are computed
     and s is m-by-m.

     [u,s,tv] = svd(x,lapack_) also produces the lapack direct output
     decomposition. s is a real vector of the singular values and tv is
     the transconjugate of matrix v.
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
