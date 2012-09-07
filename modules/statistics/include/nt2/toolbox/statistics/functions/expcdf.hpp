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
#ifndef NT2_TOOLBOX_STATISTICS_FUNCTIONS_EXPCDF_HPP_INCLUDED
#define NT2_TOOLBOX_STATISTICS_FUNCTIONS_EXPCDF_HPP_INCLUDED

#include <nt2/options.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/size_as.hpp>
#include <nt2/sdk/meta/value_as.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/core/container/dsl/value_type.hpp>
#include <nt2/sdk/meta/tieable_hierarchy.hpp>

/*!
 *
 * \ingroup statistics
 * \defgroup statistics_exp expcdf
 *
 * \par Description
 * exponential  cumulative distribution
 *
 * All cdf (cumulative distribution functions  can be called with the syntax
 * r = xxxcdf(values, param_1, ...,  param_n)
 * the type of values elements determines the type of the output expression elements.
 * exponential has 1 parameter: mean value
 * default is 1
 *
 * expcdf can also be called using the following syntax:
 *
 *  nt2::tie(p,plo,pup) = expcdf(x,mu,pcov,alpha)
 *
 * to produce confidence bounds for p when the input parameter mu is an estimate.
 *  pcov is the variance of the estimated mu. alpha has a default value of 0.05, and
 * specifies 100*(1-alpha)% confidence bounds.  plo and pup are arrays of
 * the same size as p containing the lower and upper confidence bounds.
 * the bounds are based on a normal approximation for the distribution of
 * the log of the estimate of mu.
 * You can get a more accurate set of
 * bounds simply by using expfit to get a confidence interval for mu,
 * and evaluating expcdf at the lower and upper end points of that interval.
 *
 * \par
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/expcdf.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace nt2
 * {
 *   template <class A0>
 *     meta::call<tag::expcdf_(A0)>::type
 *     expcdf(const A0 & a0, const A1 & mu = 1);
 * }
 * \endcode
**/

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag expcdf_ of functor expcdf
     *        in namespace nt2::tag for toolbox statistics
    **/
    struct expcdf_ : ext::tieable_<expcdf_> { typedef ext::tieable_<expcdf_> parent; };
    struct expcdf0_: ext::elementwise_<expcdf0_> { typedef ext::elementwise_<expcdf0_> parent; };
  }
  NT2_FUNCTION_IMPLEMENTATION(tag::expcdf0_, expcdf, 1)
  NT2_FUNCTION_IMPLEMENTATION(tag::expcdf0_, expcdf, 2)
  NT2_FUNCTION_IMPLEMENTATION(tag::expcdf_, expcdf, 3)
  NT2_FUNCTION_IMPLEMENTATION(tag::expcdf_, expcdf, 4)
}

namespace nt2 { namespace ext
{
  template<class Domain, int N, class Expr>
  struct  size_of<tag::expcdf_,Domain,N,Expr>
  {
    typedef typename  boost::proto::result_of::child_c<Expr&,0>
                      ::value_type::extent_type                     ext0_t;
    typedef typename  boost::proto::result_of::child_c<Expr&,1>
                      ::value_type::extent_type                     ext1_t;

    typedef typename make_size< (ext0_t::static_size > ext1_t::static_size)
                                ? ext0_t::static_size
                                : ext1_t::static_size
                               >::type                             result_type;

    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      result_type sizee  = nt2::extent(boost::proto::child_c<0>(e));
      result_type sizee1 = nt2::extent(boost::proto::child_c<1>(e));

      for(size_t i = 0; i < sizee.size(); ++i)
      {
        if (sizee[i] < sizee1[i]) sizee[i] = sizee1[i];
      }

      return sizee;
    }
  };

  template<class Domain, class Expr>
  struct  size_of<tag::expcdf_,Domain,1,Expr>
        : meta::size_as<Expr,0>
  {};

  template<class Domain, int N, class Expr>
  struct  value_type<tag::expcdf_,Domain,N,Expr>
        : meta::value_as<Expr,0>
  {};
} }

#endif
