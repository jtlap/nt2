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
#ifndef NT2_TOOLBOX_STATISTICS_FUNCTIONS_NORMINV_HPP_INCLUDED
#define NT2_TOOLBOX_STATISTICS_FUNCTIONS_NORMINV_HPP_INCLUDED

#include <nt2/options.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/size_as.hpp>
#include <nt2/sdk/meta/value_as.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/core/container/dsl/value_type.hpp>
#include <nt2/sdk/meta/tieable_hierarchy.hpp>
#include <nt2/core/utility/max_extent.hpp>

/*!
 * \ingroup statistics
 * \defgroup statistics_norm norminv
 *
 * \par Description
 * normal cumulative distribution
 *
 * All inv (inverse distribution functions  can be called with the syntax
 * r = xxxinv(values, param_1, ...,  param_n)
 * the type of values elements determines the type of the output expression elements.
 * normal has 2 parameter: mean value and standard deviation
 * default are 0 and 1 respectively
 *
 * invcdf can also be called using the following syntax:
 *
 *  nt2::tie(x,xlo,xup) = invcdf(p,mu,sigma, pcov, alpha)
 *
 * to produce confidence bounds for p when the input parameters mu and sigma are estimates.
 * pcov is a  2-by-2 matrix containing the covariance matrix of the estimated parameters.
 * alpha has a default value of 0.05, and specifies 100*(1-alpha)% confidence
 * bounds.  xlo and xup are arrays of the same size as x containing the lower
 * and upper confidence bounds.
 * \par
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/norminv.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace nt2
 * {
 *   template <class A0>
 *     meta::call<tag::norminv_(A0)>::type
 *     norminv(const A0 & a0, const A1 & m = 0, const A2 & sig = 1);
 * }
 * \endcode
**/

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag norminv_ of functor norminv
     *        in namespace nt2::tag for toolbox statistics
    **/
    struct norminv_ : ext::tieable_<norminv_> { typedef ext::tieable_<norminv_> parent; };
    struct norminv0_ : ext::elementwise_<norminv0_> { typedef ext::elementwise_<norminv_> parent; };
  }
  NT2_FUNCTION_IMPLEMENTATION(tag::norminv0_, norminv, 1)
  NT2_FUNCTION_IMPLEMENTATION(tag::norminv0_, norminv, 2)
  NT2_FUNCTION_IMPLEMENTATION(tag::norminv0_, norminv, 3)
  NT2_FUNCTION_IMPLEMENTATION(tag::norminv_,  norminv, 4)
  NT2_FUNCTION_IMPLEMENTATION(tag::norminv_,  norminv, 5)
}
namespace nt2 { namespace ext
{
  template<class Domain, int N, class Expr>
  struct  size_of<tag::norminv_,Domain,N,Expr> // N =  4 or 5
  {
    typedef typename  boost::proto::result_of::child_c<Expr&,0>
                      ::value_type::extent_type                     ext0_t;
    typedef typename  boost::proto::result_of::child_c<Expr&,1>
                      ::value_type::extent_type                     ext1_t;
    typedef typename  boost::proto::result_of::child_c<Expr&,1>
                      ::value_type::extent_type                     ext2_t;
    typedef typename details::max_extent<ext2_t, ext1_t, ext0_t>::type     result_type;
    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
     return max_extent(nt2::extent(boost::proto::child_c<0>(e)),
                       nt2::extent(boost::proto::child_c<1>(e)), 
                       nt2::extent(boost::proto::child_c<2>(e)));
    }
  };

  template<class Domain, class Expr>
  struct  size_of<tag::norminv_,Domain,1,Expr>
        : meta::size_as<Expr,0>
  {};

  template<class Domain, int N, class Expr>
  struct  value_type<tag::norminv_,Domain,N,Expr>
        : meta::value_as<Expr,0>
  {};
} }

#endif
