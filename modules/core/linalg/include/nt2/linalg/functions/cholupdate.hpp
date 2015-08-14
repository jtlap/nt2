//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_CHOLUPDATE_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_CHOLUPDATE_HPP_INCLUDED

#include <nt2/linalg/options.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/size_as.hpp>
#include <nt2/sdk/meta/value_as.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/sdk/meta/tieable_hierarchy.hpp>
#include <nt2/core/container/dsl/value_type.hpp>


namespace nt2
{
  namespace tag
  {
    struct cholupdate_ :  ext::tieable_<cholupdate_>
    {
      typedef ext::tieable_<cholupdate_>  parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_cholupdate_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site>
    BOOST_FORCEINLINE generic_dispatcher<tag::cholupdate_, Site> dispatching_cholupdate_(adl_helper, boost::dispatch::meta::unknown_<Site>, ...)
    {
      return generic_dispatcher<tag::cholupdate_, Site>();
    }
    template<class... Args>
    struct impl_cholupdate_;
  }

  NT2_FUNCTION_IMPLEMENTATION(tag::cholupdate_, cholupdate, 2)
  NT2_FUNCTION_IMPLEMENTATION(tag::cholupdate_, cholupdate, 3)
  /*
   *   r1 = cholupdate(r,x) where r = chol(a) is the original Cholesky factorization of a,
   *   returns the upper triangular Cholesky factor of A + x*trans(x), where x is
   *   a column vector of appropriate length. cholupdate uses only the diagonal
   *   and upper triangle of r. The lower triangle of r is ignored.
   *
   *   r1 = cholupdate(r,x,'-') (or any third parameter) returns the cholesky factor of a - x*trans(x).
   *   an error message reports when r is not a valid cholesky factor
   *   or when the downdated matrix is not positive definite and so does
   *   not have a Cholesky factorization.
   *
   *   tie(r1,p) = cholupdate(r,x,'-') will not return an error message. if p is 0, r1 is the
   *   Cholesky factor of a - x*trans(x). if p is greater than 0, r1 is the cholesky factor of
   *   the original a. If p is 1, cholupdate failed because the downdated matrix is not positive
   *   definite. If p is 2, cholupdate failed because the upper triangle of r
   *   was not a valid Cholesky factor.
   *
   *   This functor can only be used with real types arrays
   */
}

namespace nt2 { namespace ext
{
  template<class Domain, int N, class Expr>
  struct  size_of<tag::cholupdate_,Domain,N,Expr>
        : meta::size_as<Expr,0>
  {};

  template<class Domain, int N, class Expr>
  struct  value_type<tag::cholupdate_,Domain,N,Expr>
        : meta::value_as<Expr,0>
  {};
} }

#endif
