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
#ifndef NT2_TOOLBOX_FUZZY_FUNCTIONS_TOLERANT_CEIL_HPP_INCLUDED
#define NT2_TOOLBOX_FUZZY_FUNCTIONS_TOLERANT_CEIL_HPP_INCLUDED
#include <nt2/include/simd.hpp>
#include <nt2/include/functor.hpp>

/*!
 * \ingroup fuzzy
 * \defgroup fuzzy_tolerant_ceil tolerant_ceil
 *
 * \par Description
 *  See Knuth, Art Of Computer Programming, Vol. 1, Problem 1.2.4-5.
 *
 *  Tolerant FLOOR function.
 *
 *    X  -  is given as a Double Precision argument to be operated on.
 *          It is assumed that X is represented with M mantissa bits.
 *    CT -  is   given   as   a   Comparison   Tolerance   such   that
 *          0.LT.CT.LE.3-SQRT(5)/2. If the relative difference between
 *          X and A whole number is  less  than  CT,  then  TFLOOR  is
 *          returned   as   this   whole   number.   By  treating  the
 *          floating-point numbers as a finite ordered set  note  that
 *          the  heuristic  EPS=2.**(-(M-1))   and   CT=3*EPS   causes
 *          arguments  of  TFLOOR/TCEIL to be treated as whole numbers
 *          if they are  exactly  whole  numbers  or  are  immediately
 *          adjacent to whole number representations.  Since EPS,  the
 *          "distance"  between  floating-point  numbers  on  the unit
 *          interval, and M, the number of bits in X'S mantissa, exist
 *          on  every  floating-point   computer,   TFLOOR/TCEIL   are
 *          consistently definable on every floating-point computer.
 *
 *          For more information see the following references:
 *    (1) P. E. Hagerty, "More On Fuzzy Floor And Ceiling," APL  QUOTE
 *        QUAD 8(4):20-24, June 1978. Note that TFLOOR=FL5.
 *    (2) L. M. Breed, "Definitions For Fuzzy Floor And Ceiling",  APL
 *        QUOTE QUAD 8(3):16-23, March 1978. This paper cites FL1 through
 *        FL5, the history of five years of evolutionary development of
 *        FL5 - the seven lines of code below - by open collaboration
 *        and corroboration of the mathematical-computing community.
 *
 *  Penn State University Center for Academic Computing
 *  H. D. Knoble - August, 1978.
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/tolerant_ceil.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace nt2
 * {
 *   template <class A0>
 *     meta::call<tag::tolerant_ceil_(A0)>::type
 *     tolerant_ceil(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the first parameter of tolerant_ceil
 *
 * \return a value of the type of the parameter
 *
 * \par Notes
 * In SIMD mode, this function acts elementwise on the inputs vectors elements
 *
**/

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag tolerant_ceil_ of functor tolerant_ceil
     *        in namespace nt2::tag for toolbox fuzzy
    **/
    struct tolerant_ceil_ : ext::elementwise_<tolerant_ceil_> { typedef ext::elementwise_<tolerant_ceil_> parent; };
  }
  NT2_FUNCTION_IMPLEMENTATION(tag::tolerant_ceil_, tolerant_ceil, 1)
  NT2_FUNCTION_IMPLEMENTATION(tag::tolerant_ceil_, tceil, 1)
}

#endif

// modified by jt the 25/12/2010
