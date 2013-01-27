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
#ifndef NT2_TOOLBOX_CEPHES_FUNCTIONS_HYP2F1_HPP_INCLUDED
#define NT2_TOOLBOX_CEPHES_FUNCTIONS_HYP2F1_HPP_INCLUDED
#include <nt2/include/functor.hpp>

/*!
 * \ingroup cephes
 * \defgroup cephes_hyp2f1 hyp2f1
 *
 * \par Description
 * Please for details consult the proper documentation of the external
 * library cephes.
 *
 * \par Header file
 *
 * \code
 * #include <nt2/toolbox/cephes/include/functions/hyp2f1.hpp>
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
 *       meta::call<tag::hyp2f1_(A0,A0,A0,A0)>::type
 *       hyp2f1(const A0 & a0,const A0 & a1,const A0 & a2,const A0 & a3);
 *   }
 * }
 * \endcode
 *
 * \param a0 the first parameter of hyp2f1
 * \param a1 the second parameter of hyp2f1
 * \param a2 the third parameter of hyp2f1
 * \param a3 the fourth parameter of hyp2f1
 *
 * \return a value of the common type of the parameters
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
     * \brief Define the tag hyp2f1_ of functor hyp2f1
     *        in namespace nt2::cephes::tag for toolbox cephes
    **/
    struct hyp2f1_ : ext::elementwise_<hyp2f1_> { typedef ext::elementwise_<hyp2f1_> parent; };
  }
  NT2_FUNCTION_IMPLEMENTATION(cephes::tag::hyp2f1_, hyp2f1, 4)
  } }

#include <nt2/toolbox/cephes/functions/scalar/hyp2f1.hpp>
// #include <nt2/toolbox/cephes/functions/simd/all/hyp2f1.hpp>

#endif

// modified by jt the 29/12/2010
