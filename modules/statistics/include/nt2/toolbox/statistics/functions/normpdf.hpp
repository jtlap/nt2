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
#ifndef NT2_TOOLBOX_STATISTICS_FUNCTIONS_NORMPDF_HPP_INCLUDED
#define NT2_TOOLBOX_STATISTICS_FUNCTIONS_NORMPDF_HPP_INCLUDED
#include <nt2/include/simd.hpp>
#include <nt2/include/functor.hpp>

/*!
 * \ingroup statistics
 * \defgroup statistics_norm normpdf
 *
 * \par Description
 * normal  distribution
 *
 * All pdf ( distribution functions  can be called with the syntax
 * r = xxxpdf(values, param_1, ...,  param_n)
 * the type of values elements determines the type of the output expression elements.
 * cauchy has 2 parameters: mean value and standard deviation
 * defaults are 0 and 1 respectively
 * \par
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/normpdf.hpp>
 * \endcode
 * 
 * 
 * \synopsis
 *
 * \code
 * namespace nt2
 * {
 *   template <class A0>
 *     meta::call<tag::normpdf_(A0)>::type
 *     normpdf(const A0 & a0, const A1 & m = 0, const A2 & sigma = 1);
 * }
 * \endcode
 **/

namespace nt2 { namespace tag
  {         
    /*!
     * \brief Define the tag normpdf_ of functor normpdf 
     *        in namespace nt2::tag for toolbox statistics
    **/
    struct normpdf_ : ext::elementwise_<normpdf_> { typedef ext::elementwise_<normpdf_> parent; };
  }
  NT2_FUNCTION_IMPLEMENTATION(tag::normpdf_, normpdf, 1)
  NT2_FUNCTION_IMPLEMENTATION(tag::normpdf_, normpdf, 2)
  NT2_FUNCTION_IMPLEMENTATION(tag::normpdf_, normpdf, 3)  
}

#endif

// /////////////////////////////////////////////////////////////////////////////
// End of normpdf.hpp
// /////////////////////////////////////////////////////////////////////////////
