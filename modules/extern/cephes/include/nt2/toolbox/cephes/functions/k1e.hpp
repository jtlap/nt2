//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
/*!
 * \file
**/
#ifndef NT2_TOOLBOX_CEPHES_FUNCTIONS_K1E_HPP_INCLUDED
#define NT2_TOOLBOX_CEPHES_FUNCTIONS_K1E_HPP_INCLUDED
#include <nt2/include/functor.hpp>

/*!
 * \ingroup cephes
 * \defgroup cephes_k1e k1e
 *
 * \par Description
 * Please for details consult the proper documentation of the external
 * library cephes.
 *
 * \par Header file
 *
 * \code
 * #include <nt2/toolbox/cephes/include/functions/k1e.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace nt2
 * {
 *   namespace cephes
 *   {
 *     template <class A0>
 *       meta::call<tag::k1e_(A0)>::type
 *       k1e(const A0 & a0);
 *   }
 * }
 * \endcode
 *
 * \param a0 the unique parameter of k1e
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
 * cephes library defines functions for float and double entries.
 * \par
 * As they are written in C the original name of the float version is
 * generally terminated by and extra 'f',
 * this is not the case for the nt2 version which dispatch to
 * the correct function according to the inputs types.
 *
**/

namespace nt2 { namespace cephes { namespace tag
  {
    /*!
     * \brief Define the tag k1e_ of functor k1e
     *        in namespace nt2::cephes::tag for toolbox cephes
    **/
    struct k1e_ : ext::elementwise_<k1e_> { typedef ext::elementwise_<k1e_> parent; };
  }
  NT2_FUNCTION_IMPLEMENTATION(cephes::tag::k1e_, k1e, 1)
  } }

#include <nt2/toolbox/cephes/functions/scalar/k1e.hpp>
// #include <nt2/toolbox/cephes/functions/simd/all/k1e.hpp>

#endif

// modified by jt the 29/12/2010
