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
#ifndef NT2_TOOLBOX_FDLIBM_FUNCTIONS_SQRT_HPP_INCLUDED
#define NT2_TOOLBOX_FDLIBM_FUNCTIONS_SQRT_HPP_INCLUDED
#include <nt2/include/functor.hpp>

/*!
 * \ingroup fdlibm
 * \defgroup fdlibm_sqrt sqrt
 *
 * \par Description
 * Please for details consult the proper documentation of the external
 * library fdlibm.
 *
 * \par Header file
 *
 * \code
 * #include <nt2/toolbox/fdlibm/include/functions/sqrt.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace nt2
 * {
 *   namespace fdlibm
 *   {
 *     template <class A0>
 *       meta::call<tag::sqrt_(A0)>::type
 *       sqrt(const A0 & a0);
 *   }
 * }
 * \endcode
 *
 * \param a0 the unique parameter of sqrt
 *
 * \return a value of the same type as the parameter
 *
 * \par Notes
 * In SIMD mode, this function acts elementwise on the inputs vectors elements
 * \par
 * When calling external library, nt2 simply encapsulates the
 * original proper call to provide easy use.
 * \par
 * Remenber that SIMD implementation is therefore merely
 * mapping the scalar function to each SIMD vectors elements
 * and will not provide acceleration, but ease.
 * \par
 * fdlibm library defines functions for double entries only.
 * Nevertheless, they can be called with float entries under nt2 calls
 * to return float outputs.
 *
**/

namespace nt2 { namespace fdlibm { namespace tag
  {
    /*!
     * \brief Define the tag sqrt_ of functor sqrt
     *        in namespace nt2::fdlibm::tag for toolbox fdlibm
    **/
    struct sqrt_ : ext::elementwise_<sqrt_> { typedef ext::elementwise_<sqrt_> parent; };
  }
  NT2_FUNCTION_IMPLEMENTATION(fdlibm::tag::sqrt_, sqrt, 1)
  } }

#include <nt2/toolbox/fdlibm/functions/scalar/sqrt.hpp>
// #include <nt2/toolbox/fdlibm/functions/simd/all/sqrt.hpp>

#endif

// modified by jt the 29/12/2010
