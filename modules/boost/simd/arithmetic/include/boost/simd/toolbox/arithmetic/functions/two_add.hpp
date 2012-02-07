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
#ifndef BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_TWO_ADD_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_TWO_ADD_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \ingroup boost_simd_arithmetic
 * \defgroup boost_simd_arithmetic_two_add two_add
 *
 * \par Description
 * TODO Put description here
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/two_add.hpp>
 * \endcode
 * 
 * 
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::two_add_(A0,A0)>::type
 *     two_add(const A0 & a0,const A0 & a1);
 * }
 * \endcode
 *
 * \param a0 the first parameter of two_add
 * \param a1 the second parameter of two_add
 * 
 * \return a value of the common type of the parameters
 *  
 * \par Notes
 * In SIMD mode, this function acts elementwise on the inputs vectors elements
 * \par
 *  
**/

namespace boost { namespace simd { namespace tag
  {         
    /*!
     * \brief Define the tag two_add_ of functor two_add 
     *        in namespace boost::simd::tag for toolbox boost.simd.arithmetic
    **/
    struct two_add_ : ext::elementwise_<two_add_> { typedef ext::elementwise_<two_add_> parent; };
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::two_add_, two_add, 2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(tag::two_add_, two_add,(A0 const&)(A0 const&)(A0&), 1)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(tag::two_add_, two_add,(A0 const&)(A0 const&)(A0&)(A0&), 1)
} }

#endif

// modified by jt the 25/12/2010
