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
#ifndef NT2_TOOLBOX_BESSEL_FUNCTIONS_JNI_HPP_INCLUDED
#define NT2_TOOLBOX_BESSEL_FUNCTIONS_JNI_HPP_INCLUDED
#include <nt2/include/simd.hpp>
#include <nt2/include/functor.hpp>

/*!
 * \ingroup bessel
 * \defgroup bessel_jni jni
 *
 * \par Description
 * Bessel function of the first kind of order n.
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/jni.hpp>
 * \endcode
 * 
 * 
 * \synopsis
 *
 * \code
 * namespace nt2
 * {
 *   template <class A0>
 *     meta::call<tag::jni_(A0,A0)>::type
 *     jni(const A0 & a0,const A0 & a1);
 * }
 * \endcode
 *
 * \param a0 the first parameter of jni, a scalar integer: the order of the bessel function
 * \param a1 the second parameter of jni
 * 
 * \return a value of the common type of the parameters
 *  
 * \par Notes
 * In SIMD mode, this function acts elementwise on the inputs vectors elements
 * \par
 *  
**/

namespace nt2 { namespace tag
  {         
    /*!
     * \brief Define the tag jni_ of functor jni 
     *        in namespace nt2::tag for toolbox bessel
    **/
    struct jni_ : ext::elementwise_<jni_> { typedef ext::elementwise_<jni_> parent; };
  }
  NT2_FUNCTION_IMPLEMENTATION(tag::jni_, jni, 2)
}

#endif

// modified by jt the 25/12/2010
