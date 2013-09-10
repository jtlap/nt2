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
#ifndef NT2_EXPONENTIAL_FUNCTIONS_IEXP2_HPP_INCLUDED
#define NT2_EXPONENTIAL_FUNCTIONS_IEXP2_HPP_INCLUDED
#include <nt2/include/functor.hpp>

/*!
 * \ingroup exponential
 * \defgroup exponential_iexp2 iexp2
 *
 * \par Description
 * base two exponential function on integer ranges returning same type integer : \f$2^{a_0}\f$
 * Be careful,  overflows are not reported. The results if the power is greater than the bit cardinality
 * of the type minus one (or minus two for signed types) is unspecified.
 * The function is not defined for floating types
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/iexp2.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace nt2
 * {
 *   template <class A0>
 *     meta::call<tag::iexp2_(A0)>::type
 *     iexp2(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the unique parameter of iexp2
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
     * \brief Define the tag iexp2_ of functor iexp2
     *        in namespace nt2::tag for toolbox exponential
    **/
    struct iexp2_ : ext::elementwise_<iexp2_> { typedef ext::elementwise_<iexp2_> parent; };
  }
  NT2_FUNCTION_IMPLEMENTATION(tag::iexp2_, iexp2, 1)
}

#endif

// modified by jt the 25/12/2010
