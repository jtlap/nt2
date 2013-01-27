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
#ifndef NT2_TOOLBOX_STATISTICS_FUNCTIONS_GAMPDF_HPP_INCLUDED
#define NT2_TOOLBOX_STATISTICS_FUNCTIONS_GAMPDF_HPP_INCLUDED
#include <nt2/include/functor.hpp>

/*!
 * \ingroup statistics
 * \defgroup statistics_norm gampdf
 *
 * \par Description
 * gamma distribution
 *
 * All pdf ( distribution functions  can be called with the syntax
 * r = xxxpdf(values, param_1, ...,  param_n)
 * the type of values elements determines the type of the output expression elements.
 * gamma has 2 parameters: shape (a) and scale (b)
 *
 * Some references refer to the gamma distribution with a single
 * parameter.  This corresponds to the default of b = 1.
 * a has no default.
 * \par
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/gampdf.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace nt2
 * {
 *   template <class A0>
 *     meta::call<tag::gampdf_(A0)>::type
 *     gampdf(const A0 & a0, const A1 & a, const A2 & b = 1);
 * }
 * \endcode
 **/

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag gampdf_ of functor gampdf
     *        in namespace nt2::tag for toolbox statistics
    **/
    struct gampdf_ : ext::elementwise_<gampdf_> { typedef ext::elementwise_<gampdf_> parent; };
  }
  NT2_FUNCTION_IMPLEMENTATION(tag::gampdf_, gampdf, 2)
  NT2_FUNCTION_IMPLEMENTATION(tag::gampdf_, gampdf, 3)
}

#endif

// /////////////////////////////////////////////////////////////////////////////
// End of gampdf.hpp
// /////////////////////////////////////////////////////////////////////////////
