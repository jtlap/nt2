//==============================================================================
//         Copyright 2014                 Jean-Thierry Lapresté
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_STATISTICS_FUNCTIONS_CHOLCOV_HPP_INCLUDED
#define NT2_STATISTICS_FUNCTIONS_CHOLCOV_HPP_INCLUDED

#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/size_as.hpp>
#include <nt2/sdk/meta/value_as.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/sdk/meta/tieable_hierarchy.hpp>

namespace nt2
{
  namespace tag
  {
    struct cholcov_ : ext::tieable_<cholcov_>
    {
      typedef ext::tieable_<cholcov_>  parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_cholcov_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site>
    BOOST_FORCEINLINE generic_dispatcher<tag::cholcov_, Site> dispatching_cholcov_(adl_helper, boost::dispatch::meta::unknown_<Site>, ...)
    {
      return generic_dispatcher<tag::cholcov_, Site>();
    }
    template<class... Args>
    struct impl_cholcov_;
  }

  /**
   * @brief cholcov  cholesky-like decomposition for covariance matrix.
   *    t = cholcov(sigma) computes t such that sigma = t'*t.  sigma must be
   *    square, hermitian, and positive semi-definite.  if sigma is positive
   *    definite, then t is the square, upper triangular cholesky factor.
   *
   *    if sigma is not positive definite, t is computed from an eigenvalue
   *    decomposition of sigma.  t is not necessarily triangular or square in
   *    this case.  any eigenvectors whose corresponding eigenvalue is close to
   *    zero (within a small tolerance) are omitted.  if any remaining
   *    eigenvalues are negative, t is empty.
   *
   *    [t,p] = cholcov(sigma) returns the number of negative eigenvalues of
   *    sigma, and t is empty if p>0.  if p==0, sigma is positive semi-definite.
   *
   *    [t,p] = cholcov(sigma,definte_) returns p==0 if sigma is positive definite, and
   *    t is the cholesky factor.  if sigma is not positive definite, p is a
   *    positive integer and t is empty.
   *
   **/

  NT2_FUNCTION_IMPLEMENTATION(tag::cholcov_, cholcov, 1)
  NT2_FUNCTION_IMPLEMENTATION(tag::cholcov_, cholcov, 2)
}

namespace nt2 { namespace ext
{
  template<class Domain, int N, class Expr>
  struct  size_of<tag::cholcov_,Domain,N,Expr>
        : meta::size_as<Expr,0>
  {};
} }

#endif
