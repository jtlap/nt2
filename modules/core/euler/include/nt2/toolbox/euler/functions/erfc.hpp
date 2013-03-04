//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
/*!
 * \file
**/
#ifndef NT2_TOOLBOX_EULER_FUNCTIONS_ERFC_HPP_INCLUDED
#define NT2_TOOLBOX_EULER_FUNCTIONS_ERFC_HPP_INCLUDED
#include <nt2/include/functor.hpp>

/*!
 * \ingroup euler
 * \defgroup euler_erfc erfc
 *
 * \par Description
 * Complementary eroor function
 * \par Formula
 * \f[ erfc(x)= 1-erf(x)
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/erfc.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace nt2
 * {
 *   template <class A0>
 *     meta::call<tag::erfc_(A0)>::type
 *     erfc(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the unique parameter of erfc
 *
 * \return a value of the same type as the parameter
 *
 * \par Notes
 * In SIMD mode, this function acts elementwise on the inputs vectors elements
 * \par
 *
**/

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag erfc_ of functor erfc
     *        in namespace nt2::tag for toolbox euler
    **/
    struct erfc_ : ext::elementwise_<erfc_> { typedef ext::elementwise_<erfc_> parent; };
  }
  NT2_FUNCTION_IMPLEMENTATION(tag::erfc_, erfc, 1)
}

#endif

// modified by jt the 25/12/2010
