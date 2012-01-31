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
#ifndef NT2_TOOLBOX_FDLIBM_FUNCTIONS_IEEE754_J1_HPP_INCLUDED
#define NT2_TOOLBOX_FDLIBM_FUNCTIONS_IEEE754_J1_HPP_INCLUDED
#include <nt2/include/simd.hpp>
#include <nt2/include/functor.hpp>

/*!
 * \ingroup fdlibm
 * \defgroup fdlibm___ieee754_j1 __ieee754_j1
 *
 * \par Description
 * Please for details consult the proper documentation of the external
 * library fdlibm.
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/toolbox/fdlibm/include/functions/__ieee754_j1.hpp>
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
 *       meta::call<tag::__ieee754_j1_(A0)>::type
 *       __ieee754_j1(const A0 & a0);
 *   }
 * }
 * \endcode
 *
 * \param a0 the unique parameter of __ieee754_j1
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
     * \brief Define the tag __ieee754_j1_ of functor __ieee754_j1 
     *        in namespace nt2::fdlibm::tag for toolbox fdlibm
    **/
    struct __ieee754_j1_ : ext::elementwise_<__ieee754_j1_> { typedef ext::elementwise_<__ieee754_j1_> parent; };
  }
  NT2_FUNCTION_IMPLEMENTATION(fdlibm::tag::__ieee754_j1_, __ieee754_j1, 1)
  } }

#include <nt2/toolbox/fdlibm/functions/scalar/__ieee754_j1.hpp>
// #include <nt2/toolbox/fdlibm/functions/simd/all/__ieee754_j1.hpp> 

#endif

// modified by jt the 29/12/2010
