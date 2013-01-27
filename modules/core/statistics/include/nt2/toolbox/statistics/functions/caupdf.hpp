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
#ifndef NT2_TOOLBOX_STATISTICS_FUNCTIONS_CAUPDF_HPP_INCLUDED
#define NT2_TOOLBOX_STATISTICS_FUNCTIONS_CAUPDF_HPP_INCLUDED
#include <nt2/include/functor.hpp>

/*!
 * \ingroup statistics
 * \defgroup statistics_cau caupdf
 *
 * \par Description
 * cauchy  distribution
 *
 * All pcdf ( distribution functions  can be called with the syntax
 * r = xxxcdf(values, param_1, ...,  param_n)
 * the type of values elements determines the type of the output expression elements.
 * cauchy has 2 parameters: median and scale
 * defaults are 0 and 1 respectively
 * \par
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/caupdf.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace nt2
 * {
 *   template <class A0>
 *     meta::call<tag::caupdf_(A0)>::type
 *     caupdf(const A0 & a0, const A1 & median = 0, const A2 & scale = 1);
 * }
 * \endcode
 *
**/

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag caupdf_ of functor caupdf
     *        in namespace nt2::tag for toolbox statistics
    **/
    struct caupdf_ : ext::elementwise_<caupdf_> { typedef ext::elementwise_<caupdf_> parent; };
  }
  NT2_FUNCTION_IMPLEMENTATION(tag::caupdf_, caupdf, 1)
  NT2_FUNCTION_IMPLEMENTATION(tag::caupdf_, caupdf, 2)
  NT2_FUNCTION_IMPLEMENTATION(tag::caupdf_, caupdf, 3)
}

#endif

// /////////////////////////////////////////////////////////////////////////////
// End of caupdf.hpp
// /////////////////////////////////////////////////////////////////////////////
