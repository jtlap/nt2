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
#ifndef NT2_TOOLBOX_EXPONENTIAL_FUNCTIONS_LOG2_HPP_INCLUDED
#define NT2_TOOLBOX_EXPONENTIAL_FUNCTIONS_LOG2_HPP_INCLUDED
#include <nt2/include/functor.hpp>
#include <nt2/include/functions/frexp.hpp>

/*!
 * \ingroup exponential
 * \defgroup exponential_log2 log2
 *
 * \par Description
 * base two logarithm function.
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/log2.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace nt2
 * {
 *   template <class A0>
 *     meta::call<tag::log2_(A0)>::type
 *     log2(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the unique parameter of log2
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
     * \brief Define the tag log2_ of functor log2
     *        in namespace nt2::tag for toolbox exponential
    **/
    struct log2_ : ext::elementwise_<log2_> { typedef ext::elementwise_<log2_> parent; };
  }
  NT2_FUNCTION_IMPLEMENTATION(tag::log2_, log2, 1)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(tag::frexp_, log2,(A0 const&)(A1&)(A2&),3)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(tag::frexp_, log2,(A0 const&)(A1&),2)

}


#endif

