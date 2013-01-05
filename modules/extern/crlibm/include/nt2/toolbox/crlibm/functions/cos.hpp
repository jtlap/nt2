//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
/*!
 * \file
**/
#ifndef NT2_TOOLBOX_CRLIBM_FUNCTIONS_COS_HPP_INCLUDED
#define NT2_TOOLBOX_CRLIBM_FUNCTIONS_COS_HPP_INCLUDED
#include <nt2/include/functor.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/toolbox/crlibm/specific/interface.hpp>

/*!
 * \ingroup crlibm
 * \defgroup crlibm_cos cos
 *
 * \par Description
 * Please for details consult the proper documentation of the external
 * library crlibm.
 * \par
 * The template parameter T is used to choose the rounding
 * mode used by the function cos.
 * It can be choosen between:
 * \arg nt2::rn i.e. round to nearest
 * \arg nt2::rd i.e. round to \f$-\infty\f$
 * \arg nt2::ru i.e. round to \f$\infty\f$
 * \arg nt2::rz i.e. round to zero
 *
 * \par Header file
 *
 * \code
 * #include <nt2/toolbox/crlibm/include/functions/cos.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace nt2
 * {
 *   namespace crlibm
 *   {
 *     template <class T,class A0>
 *       meta::call<tag::cos_(A0)>::type
 *       cos(const A0 & a0);
 *   }
 * }
 * \endcode
 *
 * \param a0 the unique parameter of cos
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
 * crlibm library defines functions for double entries only.
 * Nevertheless, they can be called with float entries under nt2 calls
 * to return float outputs.
 *
**/

namespace nt2 { namespace crlibm { namespace tag
  {
    /*!
     * \brief Define the tag cos_ of functor cos
     *        in namespace nt2::crlibm::tag for toolbox crlibm
    **/
    template <class T>
    struct cos_ : ext::elementwise_<cos_<T> > { typedef ext::elementwise_<cos_<T> > parent; };
  }
  NT2_CRLIBM_FUNCTION_IMPLEMENTATION_TPL(cos, 1)
} }

#endif
