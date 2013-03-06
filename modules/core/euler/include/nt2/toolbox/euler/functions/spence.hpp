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
#ifndef NT2_TOOLBOX_EULER_FUNCTIONS_SPENCE_HPP_INCLUDED
#define NT2_TOOLBOX_EULER_FUNCTIONS_SPENCE_HPP_INCLUDED
#include <nt2/include/functor.hpp>

/*!
 * \ingroup euler
 * \defgroup euler_spence spence
 *
 * \par Description
 * spence function or dilogarithm
 * \par Formula
 * \f[\mathop{\textrm{Li}_2}(a_0)=\int_1^{a_0} \frac{\log t}{t-1}dt\f]
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/spence.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace nt2
 * {
 *   template <class A0>
 *     meta::call<tag::spence_(A0)>::type
 *     spence(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the unique parameter of spence
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
     * \brief Define the tag spence_ of functor spence
     *        in namespace nt2::tag for toolbox euler
    **/
    struct spence_ : ext::elementwise_<spence_> { typedef ext::elementwise_<spence_> parent; };
  }
  NT2_FUNCTION_IMPLEMENTATION(tag::spence_, spence, 1)
}

#endif

// modified by jt the 25/12/2010
