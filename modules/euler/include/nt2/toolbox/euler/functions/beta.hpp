//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_EULER_FUNCTIONS_BETA_HPP_INCLUDED
#define NT2_TOOLBOX_EULER_FUNCTIONS_BETA_HPP_INCLUDED

#include <nt2/include/simd.hpp>
#include <nt2/include/functor.hpp>

/*!
 * \internal functor \endinternal
 * \ingroup euler
 * \defgroup euler_beta Euler beta function
 *
 * In mathematics, the beta function, also called the Euler integral of 
 * the first kind, is a special function ... The beta function was studied 
 * by Euler and Legendre and was given its name by Jacques Binet; its symbol 
 * B is a Greek capital beta rather than the similar Latin capital b.
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/beta.hpp>
 * \endcode
 * 
 * \synopsis
 *
 * \code
 * namespace nt2
 * {
 *   template<class A0, class A1> 
 *   meta::call<tag::beta_(A0,A1)>::type beta(A0 const& x, A1 const& y);
 * }
 * \endcode
 *
 * \param x First parameter of B(x,y)
 * \param y Second parameter of B(x,y)
 * \return A real number equals to the value of \b B(x,y)
 *  
 **/

namespace nt2 
{ 
  namespace tag 
  {         
    /*!
     * \internal tag \endinternal
     * \ingroup euler
     * \brief Tag designing the nt2::beta function
     *          in zzz
     **/
    struct beta_ {};
  }
  NT2_FUNCTION_IMPLEMENTATION(tag::beta_, beta, 2)
}
 
 
#endif

// modified by jt the 25/12/2010
