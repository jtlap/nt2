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
#ifndef NT2_TOOLBOX_EULER_FUNCTIONS_EXPNI_HPP_INCLUDED
#define NT2_TOOLBOX_EULER_FUNCTIONS_EXPNI_HPP_INCLUDED
#include <nt2/include/simd.hpp>
#include <nt2/include/functor.hpp>

/*!
 * \ingroup euler
 * \defgroup euler_expni expni
 *
 * \par Description
 * exponential integral function
 * \par Formula
 * \f[ E_a_0(a_1)=\int_0^\infty rac{e^{-a_1t)}{t^a_0}dt\f]
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/expni.hpp>
 * \endcode
 * 
 * 
 * \synopsis
 *
 * \code
 * namespace nt2
 * {
 *   template <class A0>
 *     meta::call<tag::expni_(A0,A0)>::type
 *     expni(const A0 & a0,const A0 & a1);
 * }
 * \endcode
 *
 * \param a0 the first parameter of expni, must be scalar integer
 * \param a1 the second parameter of expni, must be non negative
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
     * \brief Define the tag expni_ of functor expni 
     *        in namespace nt2::tag for toolbox euler
    **/
    struct expni_ : ext::elementwise_<expni_> { typedef ext::elementwise_<expni_> parent; };
  }
  NT2_FUNCTION_IMPLEMENTATION(tag::expni_, expni, 2)
}

#endif

// modified by jt the 25/12/2010
