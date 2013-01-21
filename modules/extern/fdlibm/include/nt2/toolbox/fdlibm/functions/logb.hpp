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
#ifndef NT2_TOOLBOX_FDLIBM_FUNCTIONS_LOGB_HPP_INCLUDED
#define NT2_TOOLBOX_FDLIBM_FUNCTIONS_LOGB_HPP_INCLUDED
#include <nt2/include/functor.hpp>
#include <nt2/include/functor.hpp>

/*!
 * \ingroup fdlibm
 * \defgroup fdlibm_logb logb
 *
 * \par Description
 * Please for details consult the proper documentation of the external
 * library fdlibm.
 *
 * \par Header file
 *
 * \code
 * #include <nt2/toolbox/fdlibm/include/functions/logb.hpp>
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
 *       meta::call<tag::logb_(A0)>::type
 *       logb(const A0 & a0);
 *   }
 * }
 * \endcode
 *
 * \param a0 the unique parameter of logb
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
     * \brief Define the tag logb_ of functor logb
     *        in namespace nt2::fdlibm::tag for toolbox fdlibm
    **/
    struct logb_ : ext::elementwise_<logb_> { typedef ext::elementwise_<logb_> parent; };
  }
  NT2_FUNCTION_IMPLEMENTATION(fdlibm::tag::logb_, logb, 1)
  } }

#include <nt2/toolbox/fdlibm/functions/scalar/logb.hpp>
// #include <nt2/toolbox/fdlibm/functions/simd/all/logb.hpp>

#endif

// modified by jt the 29/12/2010
