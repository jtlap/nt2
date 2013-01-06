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
#ifndef NT2_TOOLBOX_COMBINATORIAL_FUNCTIONS_LCM_HPP_INCLUDED
#define NT2_TOOLBOX_COMBINATORIAL_FUNCTIONS_LCM_HPP_INCLUDED
#include <nt2/include/functor.hpp>
#include <nt2/include/functor.hpp>

/*!
 * \ingroup combinatorial
 * \defgroup combinatorial_lcm lcm
 *
 * \par Description
 * least common multiple
 * \par
 * If parameters are floating point and not flint,
 * nan is returned.
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/lcm.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace nt2
 * {
 *   template <class A0>
 *     meta::call<tag::lcm_(A0,A0)>::type
 *     lcm(const A0 & a0,const A0 & a1);
 * }
 * \endcode
 *
 * \param a0 the first parameter of lcm
 * \param a1 the second parameter of lcm
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
     * \brief Define the tag lcm_ of functor lcm
     *        in namespace nt2::tag for toolbox combinatorial
    **/
    struct lcm_ : ext::elementwise_<lcm_> { typedef ext::elementwise_<lcm_> parent; };
  }
  NT2_FUNCTION_IMPLEMENTATION(tag::lcm_, lcm, 2)
}

#endif

// modified by jt the 25/12/2010
