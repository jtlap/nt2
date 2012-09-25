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
#ifndef NT2_TOOLBOX_STATISTICS_FUNCTIONS_EXPPDF_HPP_INCLUDED
#define NT2_TOOLBOX_STATISTICS_FUNCTIONS_EXPPDF_HPP_INCLUDED
#include <nt2/include/simd.hpp>
#include <nt2/include/functor.hpp>

/*!
 * \ingroup statistics
 * \defgroup statistics_exp exppdf
 *
 * \par Description
 * exponential  distribution
 *
 * All pdf ( distribution functions  can be called with the syntax
 * r = xxxpdf(values, param_1, ...,  param_n)
 * the type of values elements determines the type of the output expression elements.
 * cauchy has 1 parameter: mean value
 * default is 1
 * \par

 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/exppdf.hpp>
 * \endcode
 * 
 * 
 * \synopsis
 *
 * \code
 * namespace nt2
 * {
 *   template <class A0>
 *     meta::call<tag::exppdf_(A0)>::type
 *     exppdf(const A0 & a0, const A1 & mu = 1);
 * }
 * \endcode
 *
 *  
**/

namespace nt2 { namespace tag
  {         
    /*!
     * \brief Define the tag exppdf_ of functor exppdf 
     *        in namespace nt2::tag for toolbox statistics
    **/
    struct exppdf_ : ext::elementwise_<exppdf_> { typedef ext::elementwise_<exppdf_> parent; };
  }
  NT2_FUNCTION_IMPLEMENTATION(tag::exppdf_, exppdf, 1)
  NT2_FUNCTION_IMPLEMENTATION(tag::exppdf_, exppdf, 2)
}

#endif

// /////////////////////////////////////////////////////////////////////////////
// End of exppdf.hpp
// /////////////////////////////////////////////////////////////////////////////
