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
#ifndef NT2_TOOLBOX_LIBC_FUNCTIONS_CEIL_HPP_INCLUDED
#define NT2_TOOLBOX_LIBC_FUNCTIONS_CEIL_HPP_INCLUDED
#include <nt2/include/simd.hpp>
#include <nt2/include/functor.hpp>

/*!
 * \ingroup libc
 * \defgroup libc_ceil ceil
 *
 * \par Description
 * Please for details consult the proper documentation of the external
 * library libc.
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/toolbox/libc/include/functions/ceil.hpp>
 * \endcode
 * 
 * 
 * \synopsis
 *
 * \code
 * namespace nt2
 * {
 *   namespace libc
 *   {
 *     template <class A0>
 *       meta::call<tag::ceil_(A0)>::type
 *       ceil(const A0 & a0);
 *   }
 * }
 * \endcode
 *
 * \param a0 the unique parameter of ceil
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
 * libc library defines functions for float and double entries.
 * \par
 * As they are written in C the original name of the float version is
 * generally terminated by and extra 'f',
 * this is not the case for the nt2 version which dispatch to
 * the correct function according to the inputs types.
 *  
**/

namespace nt2 { namespace libc { namespace tag
  {         
    /*!
     * \brief Define the tag ceil_ of functor ceil 
     *        in namespace nt2::libc::tag for toolbox libc
    **/
    struct ceil_ : ext::elementwise_<ceil_> { typedef ext::elementwise_<ceil_> parent; };
  }
  NT2_FUNCTION_IMPLEMENTATION(libc::tag::ceil_, ceil, 1)
  } }

#include <nt2/toolbox/libc/functions/scalar/ceil.hpp>
// #include <nt2/toolbox/libc/functions/simd/all/ceil.hpp> 

#endif

// modified by jt the 29/12/2010
