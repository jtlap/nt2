//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
/*!
 * \file
**/
#ifndef NT2_TOOLBOX_STATISTICS_FUNCTIONS_NORMCDF_HPP_INCLUDED
#define NT2_TOOLBOX_STATISTICS_FUNCTIONS_NORMCDF_HPP_INCLUDED

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
 * \defgroup statistics_norm normcdf
 *
 * All cdf (cumulative distribution functions  can be called with the syntax
 * r = xxxcdf(values, param_1, ...,  param_n)
 * the type of values elements determines the type of the output expression elements.
 * normal has 2 parameter: mean value and standard deviation
 * default are 0 and 1 respectively
 *
 * normcdf can also be called using the following syntax:
 *
 *  nt2::tie(x,xlo,xup) = normcdf(p,mu,sigma, pcov, alpha)
 *
 * to produce confidence bounds for p when the input parameters mu and sigma are estimates.
 * pcov is a  2-by-2 matrix containing the covariance matrix of the estimated parameters.
 * alpha has a default value of 0.05, and specifies 100*(1-alpha)% confidence
 * bounds.  xlo and xup are arrays of the same size as x containing the lower
 * and upper confidence bounds.
 *
 * *
 * \par Description
 * normal cumulative distribution
 * \par
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/normcdf.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace nt2
 * {
 *   template <class A0>
 *     meta::call<tag::normcdf_(A0)>::type
 *     normcdf(const A0 & a0, const A1 & m = 0, const A2 & sigma = 1);
 * }
 * \endcode
 *
**/

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag normcdf_ of functor normcdf
     *        in namespace nt2::tag for toolbox statistics
    **/
    struct normcdf_ : ext::tieable_<normcdf_> { typedef ext::tieable_<normcdf_> parent; };
    struct normcdf0_ : ext::elementwise_<normcdf0_> { typedef ext::elementwise_<normcdf0_> parent; };
  }
  NT2_FUNCTION_IMPLEMENTATION(tag::normcdf0_, normcdf, 1)
  NT2_FUNCTION_IMPLEMENTATION(tag::normcdf0_, normcdf, 2)
  NT2_FUNCTION_IMPLEMENTATION(tag::normcdf0_, normcdf, 3)
  NT2_FUNCTION_IMPLEMENTATION(tag::normcdf_,  normcdf, 4)
  NT2_FUNCTION_IMPLEMENTATION(tag::normcdf_,  normcdf, 5)

}

namespace nt2 { namespace ext
{
  template<class Domain, int N, class Expr>
  struct  size_of<tag::normcdf_,Domain,N,Expr> // N =  4 or 5
  {
    typedef typename  boost::proto::result_of::child_c<Expr&,0>
                      ::value_type::extent_type                     ext0_t;
    typedef typename  boost::proto::result_of::child_c<Expr&,1>
                      ::value_type::extent_type                     ext1_t;
    typedef typename  boost::proto::result_of::child_c<Expr&,2>
                      ::value_type::extent_type                     ext2_t;

   typedef typename utility::result_of::max_extent<ext2_t, ext1_t, ext0_t>::type     result_type;
    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
     return utility::max_extent(nt2::extent(boost::proto::child_c<0>(e)),
                       nt2::extent(boost::proto::child_c<1>(e)),
                       nt2::extent(boost::proto::child_c<2>(e)));
    }
  };

  template<class Domain, class Expr>
  struct  size_of<tag::normcdf_,Domain,1,Expr>
        : meta::size_as<Expr,0>
  {};

  template<class Domain, int N, class Expr>
  struct  value_type<tag::normcdf_,Domain,N,Expr>
        : meta::value_as<Expr,0>
  {};
} }

#endif
