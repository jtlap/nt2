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
#ifndef BOOST_SIMD_TOOLBOX_BOOLEAN_FUNCTIONS_BOOLEAN_SELECT_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_BOOLEAN_FUNCTIONS_BOOLEAN_SELECT_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \ingroup boost_simd_boolean
 * \defgroup boost_simd_boolean_boolean_select boolean_select
 *
 * \par Description
 * Returns the boolean selection of the second
 * or third operand according to the setting of the first operand
 * \par
 * The first operand must be a boolean type according to
 * the SIMD architecture compatible to the two other ones.
 * The operands 2 and 3 must share the same type and
 * the result type is the same.
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/boolean_select.hpp>
 * \endcode
 * 
 * 
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0,class A1,class A2>
 *     meta::call<tag::boolean_select_(A0,A1,A2)>::type
 *     boolean_select(const A0 & a0,const A1 & a1,const A2 & a2);
 * }
 * \endcode
 *
 * \param a0 the first parameter of boolean_select
 * \param a1 the second parameter of boolean_select
 * \param a2 the third parameter of boolean_select
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
     * \brief Define the tag boolean_select_ of functor boolean_select 
     *        in namespace boost::simd::tag for toolbox boost.simd.boolean
    **/
    struct boolean_select_ {};
  }
   BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::boolean_select_, boolean_select, 3)
} }
 
#endif

// modified by jt the 25/12/2010
