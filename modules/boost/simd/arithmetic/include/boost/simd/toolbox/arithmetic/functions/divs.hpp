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
#ifndef BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_DIVS_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_DIVS_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \ingroup boost_simd_arithmetic
 * \defgroup boost_simd_arithmetic_divs divs
 *
 * \par Description
 * return the saturated  division of the operandsin the input type
 * \par
 * This only differs from standard \c / in division by zero
 * cases, and also for the division of Valmin by -1 that
 * produces Valmax
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/divs.hpp>
 * \endcode
 *
 * \par Alias
 * \arg rdivide
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::divs_(A0,A0)>::type
 *     divs(const A0 & a0,const A0 & a1);
 * }
 * \endcode
 *
 * \param a0 the first parameter of divs
 * \param a1 the second parameter of divs
 *
 * \return a value of the common type of the parameters
 *
 * \par Notes
 * In SIMD mode, this function acts elementwise on the inputs vectors elements
 * \par
 *
**/

namespace boost { namespace simd {
  namespace tag
  {
    /*!
     * \brief Define the tag divs_ of functor divs
     *        in namespace boost::simd::tag for toolbox boost.simd.arithmetic
    **/
    struct divs_ : ext::elementwise_<divs_> { typedef ext::elementwise_<divs_> parent; };
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::divs_, divs, 2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::divs_, saturated_div, 2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::divs_, rdivide, 2)

  template<class A0, class A1>
  BOOST_DISPATCH_FORCE_INLINE
  typename dispatch::meta::call<tag::divs_(A0, A1)>::type
  ldivide(A0 const& a0, A1 const& a1)
  {
    return dispatch::make_functor<tag::divs_, A0>::type()(a1, a0);
  }

  template<class A0, class A1>
  BOOST_DISPATCH_FORCE_INLINE
  typename dispatch::meta::call<tag::divs_(A0, A1)>::type
  ldiv(A0 const& a0, A1 const& a1)
  {
    return dispatch::make_functor<tag::divs_, A0>::type()(a1, a0);
  }

} }

#endif
