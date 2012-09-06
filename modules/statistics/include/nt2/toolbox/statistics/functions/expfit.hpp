/*******************************************************************************
 *         Copyright 2003-2012 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2011-2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
/*!
 * \file
**/
#ifndef NT2_TOOLBOX_STATISTICS_FUNCTIONS_EXPFIT_HPP_INCLUDED
#define NT2_TOOLBOX_STATISTICS_FUNCTIONS_EXPFIT_HPP_INCLUDED
#include <nt2/include/simd.hpp>
#include <nt2/options.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/tieable_hierarchy.hpp>
#include <nt2/core/container/dsl/size.hpp>

/*!
 * \ingroup statistics
 * \defgroup statistics_exp expfit
 *
 * \par Description
 * exponential  cumulative distribution
 *
 *   muhat = expfit(x) returns the maximum likelihood estimate of the
 *   mean parameter, mu, of the exponential distribution given the data
 *   in x.  if x is a matrix, expfit returns a separate parameter estimate
 *   for each column of x.
 *
 *   tie(muhat,muci) = expfit(x) returns a 95 * confidence interval for the
 *   parameter estimate(s).
 *
 *   tie(muhat,muci) = expfit(x,alpha) returns a 100(1-alpha) percent
 *   confidence interval for the parameter estimate(s).
 *
 *   the following syntaxes require that x be a vector.
 *
 *   tie(...) = expfit(x,alpha,censoring) accepts a boolean vector of the same
 *   size as x that is 1 for observations that are right-censored and 0 for
 *   observations that are observed exactly.
 *
 *   tie(...) = expfit(x,alpha,censoring,freq) accepts a frequency vector of
 *   the same size as x.  freq typically contains integer frequencies for
 *   the corresponding elements in x, but may contain any non-integer
 *   non-negative values.
 *
 *   pass in nt2::_ for alpha, censoring, or freq to use their default values.
 * 
 * \par
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/expfit.hpp>
 * \endcode
 * 
 * 
 * \synopsis
 *
 * \code
 * namespace nt2
 * {
 *   template <class A0>
 *     meta::call<tag::expfit_(A0)>::type
 *     expfit(const A0 & a0, const A1 & mu = 1);
 * }
 * \endcode
**/

namespace nt2 { namespace tag
  {         
    /*!
     * \brief Define the tag expfit_ of functor expfit 
     *        in namespace nt2::tag for toolbox statistics
    **/
    struct expfit_ : ext::tieable_<expfit_> { typedef ext::tieable_<expfit_> parent; };
    struct expfit0_: ext::elementwise_<expfit0_> { typedef ext::elementwise_<expfit0_> parent; };
  }
  NT2_FUNCTION_IMPLEMENTATION(tag::expfit0_, expfit, 1)
  NT2_FUNCTION_IMPLEMENTATION(tag::expfit0_, expfit, 2)
  NT2_FUNCTION_IMPLEMENTATION(tag::expfit_, expfit, 3)
  NT2_FUNCTION_IMPLEMENTATION(tag::expfit_, expfit, 4)
}

namespace nt2 { namespace container { namespace ext
{
  template<class Domain, int N, class Expr>
  struct  size_of<tag::expfit_,Domain,N,Expr>
  {
    typedef typename boost::proto::result_of::child_c<Expr&,0>::type seq_term0;
    typedef typename meta::strip<seq_term0>::type::extent_type          ext0_t;
    typedef typename boost::proto::result_of::child_c<Expr&,1>::type seq_term1;
    typedef typename meta::strip<seq_term1>::type::extent_type          ext1_t;
    typedef typename make_size< (ext0_t::static_size > ext1_t::static_size)
                                ? ext0_t::static_size
                                : ext1_t::static_size
                               >::type                             result_type;
    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      result_type sizee = nt2::extent(boost::proto::child_c<0>(e));
      result_type sizee1 = nt2::extent(boost::proto::child_c<1>(e)); 
      for(size_t i = 0; i < sizee.size(); ++i)
        {
          if (sizee[i] < sizee1[i]) sizee[i] = sizee1[i];
        }
      return sizee;
    }
  };
  template<class Domain, class Expr>
  struct  size_of<tag::expfit_,Domain,1,Expr>
  {
    typedef typename boost::proto::result_of::child_c<Expr&,0>::type seq_term;
    typedef typename meta::strip<seq_term>::type::extent_type        result_type;
    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      return boost::proto::child_c<0>(e).extent();
    }
  };
  template<class Domain, int N, class Expr>
  struct  generator<tag::expfit_,Domain,N,Expr>
  {
    typedef typename boost::proto::result_of::child_c<Expr&,0>::type seq_term;
    typedef typename boost::dispatch::meta::semantic_of<seq_term>::type sema_t;

    // Rebuild proper expression type with semantic
    typedef expression< typename boost::remove_const<Expr>::type
                      , sema_t
                      >                                     result_type;

    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      return result_type(e);
    }
  };
} } }

#endif

// /////////////////////////////////////////////////////////////////////////////
// End of expfit.hpp
// /////////////////////////////////////////////////////////////////////////////
