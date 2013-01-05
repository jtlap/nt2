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
#ifndef NT2_TOOLBOX_CEPHES_FUNCTIONS_INCBPS_HPP_INCLUDED
#define NT2_TOOLBOX_CEPHES_FUNCTIONS_INCBPS_HPP_INCLUDED
#include <nt2/include/functor.hpp>
#include <nt2/include/functor.hpp>

/*!
 * \ingroup cephes
 * \defgroup cephes_incbps incbps
 *
 * \par Description
 * Please for details consult the proper documentation of the external
 * library cephes.
 *
 * \par Header file
 *
 * \code
 * #include <nt2/toolbox/cephes/include/functions/incbps.hpp>
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
 *       meta::call<tag::incbps_(A0,A0,A0)>::type
 *       incbps(const A0 & a0,const A0 & a1,const A0 & a2);
 *   }
 * }
 * \endcode
 *
 * \param a0 the first parameter of incbps
 * \param a1 the second parameter of incbps
 * \param a2 the third parameter of incbps
 *
 * \return an integer value
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
     * \brief Define the tag incbps_ of functor incbps
     *        in namespace nt2::cephes::tag for toolbox cephes
    **/
    struct incbps_ : ext::elementwise_<incbps_> { typedef ext::elementwise_<incbps_> parent; };
  }
  NT2_FUNCTION_IMPLEMENTATION(cephes::tag::incbps_, incbps, 3)
  } }

#include <nt2/toolbox/cephes/functions/scalar/incbps.hpp>
// #include <nt2/toolbox/cephes/functions/simd/all/incbps.hpp>

#endif

// modified by jt the 29/12/2010
