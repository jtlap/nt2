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
#ifndef NT2_TOOLBOX_STATISTICS_FUNCTIONS_CAUCDF_HPP_INCLUDED
#define NT2_TOOLBOX_STATISTICS_FUNCTIONS_CAUCDF_HPP_INCLUDED
#include <nt2/include/simd.hpp>
#include <nt2/include/functor.hpp>

/*!
 * \ingroup statistics
 * \defgroup statistics_cau caucdf
 *
 * \par Description
 * cauchy cumulative distribution
 * All cdf (cumulative distribution functions  can be called with the syntax
 * r = xxxcdf(values, param_1, ...,  param_n)
 * the type of values elements determines the type of the output expression elements.
 * cauchy has 2 parameters: median and scale
 * defaults are 0 and 1 respectively
 * \par
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/caucdf.hpp>
 * \endcode
 * 
 * 
 * \synopsis
 *
 * \code
 * namespace nt2
 * {
 *   template <class A0>
 *     meta::call<tag::caucdf_(A0)>::type
 *     caucdf(const A0 & a0, const A1 & median, const A2 & scale);
 * }
 * \endcode
 *  
**/

namespace nt2 { namespace tag
  {         
    /*!
     * \brief Define the tag caucdf_ of functor caucdf 
     *        in namespace nt2::tag for toolbox statistics
    **/
    struct caucdf_ : ext::elementwise_<caucdf_> { typedef ext::elementwise_<caucdf_> parent; };
  }
  NT2_FUNCTION_IMPLEMENTATION(tag::caucdf_, caucdf, 1)
  NT2_FUNCTION_IMPLEMENTATION(tag::caucdf_, caucdf, 2)
  NT2_FUNCTION_IMPLEMENTATION(tag::caucdf_, caucdf, 3)  
}

#endif

// /////////////////////////////////////////////////////////////////////////////
// End of caucdf.hpp
// /////////////////////////////////////////////////////////////////////////////
