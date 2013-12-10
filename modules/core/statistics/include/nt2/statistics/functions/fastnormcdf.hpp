
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
#ifndef NT2_STATISTICS_FUNCTIONS_FASTNORMCDF_HPP_INCLUDED
#define NT2_STATISTICS_FUNCTIONS_FASTNORMCDF_HPP_INCLUDED

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
 * \defgroup statistics_norm fastnormcdf
 *
 * All cdf (cumulative distribution functions  can be called with the syntax
 * r = xxxcdf(values, param_1, ...,  param_n)
 * the type of values elements determines the type of the output expression elements.
 * normal has 2 parameter: mean value and standard deviation
 * default are 0 and 1 respectively
 *
 * fastnormcdf can also be called using the following syntax:
 *
 *  nt2::tie(x,xlo,xup) = fastnormcdf(p,mu,sigma, pcov, alpha)
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
 * #include <nt2/include/functions/fastnormcdf.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace nt2
 * {
 *   template <class A0>
 *     meta::call<tag::fastnormcdf_(A0)>::type
 *     fastnormcdf(const A0 & a0, const A1 & m = 0, const A2 & sigma = 1);
 * }
 * \endcode
 *
**/

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag fastnormcdf_ of functor fastnormcdf
     *        in namespace nt2::tag for toolbox statistics
    **/
    struct fastnormcdf_ : ext::elementwise_<fastnormcdf_>
    { typedef ext::elementwise_<fastnormcdf_> parent; };
  }
  NT2_FUNCTION_IMPLEMENTATION(tag::fastnormcdf_, fastnormcdf, 1)
}

#endif
