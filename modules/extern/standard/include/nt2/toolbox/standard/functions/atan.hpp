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
#ifndef NT2_TOOLBOX_STANDARD_FUNCTIONS_ATAN_HPP_INCLUDED
#define NT2_TOOLBOX_STANDARD_FUNCTIONS_ATAN_HPP_INCLUDED
#include <nt2/include/simd.hpp>
#include <nt2/include/functor.hpp>

/*!
 * \ingroup standard
 * \defgroup standard_atan atan
 *
 * \par Description
 * Please for details consult the proper documentation of the external
 * library standard.
 * \par
 * The call is transfered to the standard C++ library function std::atan
 *
 * \par Header file
 *
 * \code
 * #include <nt2/toolbox/standard/include/functions/atan.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace nt2
 * {
 *   namespace standard
 *   {
 *     template <class A0>
 *       meta::call<tag::atan_(A0)>::type
 *       atan(const A0 & a0);
 *   }
 * }
 * \endcode
 *
 * \param a0 the unique parameter of atan
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
 *
**/

namespace nt2 { namespace standard { namespace tag
  {
    /*!
     * \brief Define the tag atan_ of functor atan
     *        in namespace nt2::standard::tag for toolbox standard
    **/
    struct atan_ : ext::elementwise_<atan_> { typedef ext::elementwise_<atan_> parent; };
  }
  NT2_FUNCTION_IMPLEMENTATION(standard::tag::atan_, atan, 1)
  } }

#include <nt2/toolbox/standard/functions/scalar/atan.hpp>
// #include <nt2/toolbox/standard/functions/simd/all/atan.hpp>

#endif

// modified by jt the 29/12/2010
