//==============================================================================
//         Copyright 2014                 Jean-Thierry Lapresté
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_CORRCOEF_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_CORRCOEF_HPP_INCLUDED

#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/size_as.hpp>
#include <nt2/sdk/meta/value_as.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/sdk/meta/tieable_hierarchy.hpp>

namespace nt2
{
  namespace tag
  {
    struct corrcoef_ : ext::tieable_<corrcoef_>
    {
      typedef ext::tieable_<corrcoef_>  parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_corrcoef_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site>
    BOOST_FORCEINLINE generic_dispatcher<tag::corrcoef_, Site> dispatching_corrcoef_(adl_helper, boost::dispatch::meta::unknown_<Site>, ...)
    {
      return generic_dispatcher<tag::corrcoef_, Site>();
    }
    template<class... Args>
    struct impl_corrcoef_;
  }

  /**
   *  @brief corrcoef compute correlation matrix
   *
   *    r=corrcoef(x) calculates a matrix r of correlation coefficients for
   *    an array x, in which each row is an observation and each column is a
   *    variable.
   *
   *    r=corrcoef(x,y), where x and y are vectors,
   *    is equivalent to r=corrcoef(cath(x(_) y(_)))
   *
   *    if c is the covariance matrix, c = cov(x), then corrcoef(x) is
   *    the matrix whose (i,j)'th element is
   *
   *           c(i,j)/sqrt(c(i,i)*c(j,j)).
   **/

  NT2_FUNCTION_IMPLEMENTATION(tag::corrcoef_, corrcoef, 1)
  NT2_FUNCTION_IMPLEMENTATION(tag::corrcoef_, corrcoef, 2)
}

namespace nt2 { namespace ext
{
  template<class Domain, int N, class Expr>
  struct  size_of<tag::corrcoef_,Domain,N,Expr>
        : meta::size_as<Expr,0>
  {};
} }

#endif
