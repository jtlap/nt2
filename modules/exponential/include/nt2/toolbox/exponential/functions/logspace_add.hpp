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
#ifndef NT2_TOOLBOX_EXPONENTIAL_FUNCTIONS_LOGSPACE_ADD_HPP_INCLUDED
#define NT2_TOOLBOX_EXPONENTIAL_FUNCTIONS_LOGSPACE_ADD_HPP_INCLUDED
#include <nt2/include/simd.hpp>
#include <nt2/include/functor.hpp>

/*!
 * \ingroup exponential
 * \defgroup exponential_logspace_add logspace_add
 *
 * \par Description
 *  Compute the log of a sum from logs of terms
 *  properly compute \$\log (\exp (\logx) + \exp (\logy))\$
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/logspace_add.hpp>
 * \endcode
 * 
 * 
 * \synopsis
 *
 * \code
 * namespace nt2
 * {
 *   template <class A0>
 *     meta::call<tag::logspace_add_(A0, A0)>::type
 *     logspace_add(const A0 & a0, const A0 & a1);
 * }
 * \endcode
 *
 * \return a value of the same type as the parameters
 *  
 * \par Notes
 * In SIMD mode, this function acts elementwise on the inputs vectors elements
 * \par
 *  
**/

namespace nt2 { namespace tag
  {         
    /*!
     * \brief Define the tag logspace_add_ of functor logspace_add 
     *        in namespace nt2::tag for toolbox exponential
    **/
    struct logspace_add_ : ext::elementwise_<logspace_add_> {};
  }
  NT2_FUNCTION_IMPLEMENTATION(tag::logspace_add_, logspace_add, 2)
}

#endif

// modified by jt the 25/12/2010
