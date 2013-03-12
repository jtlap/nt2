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
#ifndef NT2_TOOLBOX_STATISTICS_FUNCTIONS_UNIFPDF_HPP_INCLUDED
#define NT2_TOOLBOX_STATISTICS_FUNCTIONS_UNIFPDF_HPP_INCLUDED
#include <nt2/include/functor.hpp>

/*!
 * \ingroup statistics
 * \defgroup statistics_unif unifpdf
 *
 * \par Description
 * uniform  distribution
 *
 * All pdf ( distribution functions  can be called with the syntax
 * r = xxxpdf(values, param_1, ...,  param_n)
 * the type of values elements determines the type of the output expression elements.
 * uniform distribution has 2 parameters that are the finite bounds (a < b) of the
 * underlying distibution interval [a, b].
 * default is a = 0,  b = 1.
 * \par
 * differences with matlab
 * when any a >= b the nt2 routine assert,  matlab returns Nan
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/unifpdf.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace nt2
 * {
 *   template <class A0>
 *     meta::call<tag::unifpdf_(A0)>::type
 *     unifpdf(const A0 & a0, const A1 & a = 0, const A2 & b = 1);
 * }
 * \endcode
 *
**/

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag unifpdf_ of functor unifpdf
     *        in namespace nt2::tag for toolbox statistics
    **/
    struct unifpdf_ : ext::elementwise_<unifpdf_> { typedef ext::elementwise_<unifpdf_> parent; };
  }
  NT2_FUNCTION_IMPLEMENTATION(tag::unifpdf_, unifpdf, 1)
  NT2_FUNCTION_IMPLEMENTATION(tag::unifpdf_, unifpdf, 2)
  NT2_FUNCTION_IMPLEMENTATION(tag::unifpdf_, unifpdf, 3)
}

#endif

// /////////////////////////////////////////////////////////////////////////////
// End of unifpdf.hpp
// /////////////////////////////////////////////////////////////////////////////
