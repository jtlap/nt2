//==============================================================================
//          Copyright 2015   Jean-Thierry Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_STATISTICS_FUNCTIONS_CORRCOEF_HPP_INCLUDED
#define NT2_STATISTICS_FUNCTIONS_CORRCOEF_HPP_INCLUDED

#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/size_as.hpp>
#include <nt2/sdk/meta/value_as.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/sdk/meta/tieable_hierarchy.hpp>
#include <nt2/core/container/dsl/value_type.hpp>


namespace nt2 {
  namespace tag {
    struct corrcoef_ : ext::tieable_<corrcoef_>
    {
      typedef ext::tieable_<corrcoef_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_corrcoef_( ext::adl_helper(),
                                static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext {
    template<class Site>
    BOOST_FORCEINLINE generic_dispatcher<tag::corrcoef_, Site>
    dispatching_corrcoef_(adl_helper, boost::dispatch::meta::unknown_<Site>, ...)
    {
      return generic_dispatcher<tag::corrcoef_, Site>();
    }
    template<class... Args>
    struct impl_corrcoef_;
  }

  /**
    *  @brief corrcoef compute correlation matrix
    *
    *    tie(r{,p{,rlo{,rup}}})=corrcoef(x{, alpha}{, option}) calculates a matrix
    *    r of correlation coefficients for an array x, in which each row is an observation
    *    and each column is a variable.
    *
    *    tie(r{,p{,rlo{,rup}}})=corrcoef(x,y{, alpha}{, option}), where x and y are vectors,
    *    is equivalent to tie(r{,p{,rlo{,rup}}})=corrcoef(cath(x(_) y(_)){, alpha}{, option})
    *
    *    if c is the covariance matrix, c = cov(x), then corrcoef(x) is
    *    the matrix whose (i,j)'th element is
    *
    *           c(i,j)/sqrt(c(i,i)*c(j,j)).
    *
    *
    *    p is a matrix of p-values for testing the hypothesis of no correlation.
    *    Each p-value is the probability
    *    of getting a correlation as large as the observed value by random
    *    chance, when the true correlation is zero.  if p(i,j) is small, say
    *    less than 0.05 (alpha default value), then the correlation r(i,j) is significant.
    *
    *    rlo and rup are matrices rlo and rup, of the same size as r,
    *    containing lower and upper bounds for a 100(1-alpha) percent
    *    confidence interval for each coefficient.
    *
    *       alpha     is a number between 0 and 1 to specify a confidence
    *                 level of 100(1-alpha) percent.  default is 0.05 for 95 percent
    *                 confidence intervals.
    *       option    can be all_, complete_ or pairwise_.
    *                 all_ (default) uses all rows, complete_ uses rows with no nan
    *                 values, pairwise_ compute_ r(i,j) using rows with no nan values
    *                 in column i or j.
    *                 The pairwise_ option potentially uses different sets
    *                 of rows to compute different elements of r, and can
    *                 produce a matrix that is not definite.
    *
    *    the p-value is computed by transforming the correlation to create a T
    *    statistic having n-2 degrees of freedom, where n is the number of rows
    *    of x.  The confidence bounds are based on an asymptotic normal
    *    distribution of atanh(r), with an approximate variance equal
    *    to 1/(n-3).  these bounds are accurate for large samples when x has a
    *    multivariate normal distribution.
    *
    **/

  NT2_FUNCTION_IMPLEMENTATION(tag::corrcoef_, corrcoef, 1)
  NT2_FUNCTION_IMPLEMENTATION(tag::corrcoef_, corrcoef, 2)
  NT2_FUNCTION_IMPLEMENTATION(tag::corrcoef_, corrcoef, 3)
  NT2_FUNCTION_IMPLEMENTATION(tag::corrcoef_, corrcoef, 4)
}

namespace nt2 {
  namespace ext {
    template<class Domain, int N, class Expr>
    struct size_of<tag::corrcoef_,Domain,N,Expr>
    {
      typedef _2D result_type;

      BOOST_FORCEINLINE result_type operator()(Expr& e) const
      {
        return _2D( boost::fusion::at_c<1>(boost::proto::child_c<0>(e).extent())
                  , boost::fusion::at_c<1>(boost::proto::child_c<0>(e).extent())
                  );
      }
    };
    template<class Domain, int N, class Expr>
    struct  value_type<tag::corrcoef_,Domain,N,Expr>
      : meta::value_as<Expr,0>
    {};
  }
}

#endif
