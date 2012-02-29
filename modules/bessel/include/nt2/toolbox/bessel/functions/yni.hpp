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
#ifndef NT2_TOOLBOX_BESSEL_FUNCTIONS_YNI_HPP_INCLUDED
#define NT2_TOOLBOX_BESSEL_FUNCTIONS_YNI_HPP_INCLUDED
#include <nt2/include/simd.hpp>
#include <nt2/include/functor.hpp>

/*!
 * \ingroup bessel
 * \defgroup bessel_yni yni
 *
 * \par Description
 * Modified Bessel function of the first kind of order n.
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/yni.hpp>
 * \endcode
 * 
 * 
 * \synopsis
 *
 * \code
 * namespace nt2
 * {
 *   template <class A0>
 *     meta::call<tag::yni_(A0,A0)>::type
 *     yni(const A0 & a0,const A0 & a1);
 * }
 * \endcode
 *
 * \param a0 the first parameter of yni, a scalar integer: the order of the bessel function
 * \param a1 the second parameter of yni
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
     * \brief Define the tag yni_ of functor yni 
     *        in namespace nt2::tag for toolbox bessel
    **/
    struct yni_ : ext::elementwise_<yni_> { typedef ext::elementwise_<yni_> parent; };
  }
  NT2_FUNCTION_IMPLEMENTATION(tag::yni_, yni, 2)
}

#endif

// modified by jt the 25/12/2010
