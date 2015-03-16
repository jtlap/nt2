//==============================================================================
//         Copyright 2014                 Jean-Thierry Lapresté
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_STATISTICS_FUNCTIONS_CORRCOV_HPP_INCLUDED
#define NT2_STATISTICS_FUNCTIONS_CORRCOV_HPP_INCLUDED

#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/size_as.hpp>
#include <nt2/sdk/meta/value_as.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/sdk/meta/tieable_hierarchy.hpp>

namespace nt2
{
  namespace tag
  {
    struct corrcov_ : ext::tieable_<corrcov_>
    {
      typedef ext::tieable_<corrcov_>  parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_corrcov_( ext::adl_helper()
                                                    , static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site>
    BOOST_FORCEINLINE generic_dispatcher<tag::corrcov_, Site>
    dispatching_corrcov_(adl_helper, boost::dispatch::meta::unknown_<Site>, ...)
    {
      return generic_dispatcher<tag::corrcov_, Site>();
    }
    template<class... Args>
    struct impl_corrcov_;
  }

  /**
   *  @brief corrcov compute correlation matrix from covariance matrix.
   *    r = corrcov(c{, check_/nocheck_}) computes the correlation matrix r that corresponds to the
   *    covariance matrix c, by standardizing each row and column of c using the
   *    square roots of the variances (diagonal elements) of c. c must be square,
   *    symmetric, and positive semi-definite. The correlation for a constant
   *    variable (zero diagonal element of c) is undefined.
   *    The optinal second parameter (default check_) verifies (resp. does not verify )
   *    that the input is hermitian semi-definite
   *
   *    tie(r,sigma) = corrcov(c{, check_/nocheck_}) computes the vector of standard deviations sigma
   *    from the diagonal elements of c.
   **/

  NT2_FUNCTION_IMPLEMENTATION(tag::corrcov_, corrcov, 1)
  NT2_FUNCTION_IMPLEMENTATION(tag::corrcov_, corrcov, 2)
}

namespace nt2 { namespace ext
{
  template<class Domain, int N, class Expr>
  struct  size_of<tag::corrcov_,Domain,N,Expr>
        : meta::size_as<Expr,0>
  {};
} }

#endif
