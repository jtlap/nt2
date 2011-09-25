//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_SIMD_TOOLBOX_BITWISE_FUNCTIONS_BITWISE_SELECT_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_BITWISE_FUNCTIONS_BITWISE_SELECT_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \internal functor \endinternal
 * \ingroup boost_simd_bitwise
 * \defgroup bitwise_select bitwise_select function
 *
 * \par Description
 * Returns the bitwise selection of bits from the second
 * or third operand according to the setting of the bits
 * of the first operand
 * \par
 * The operands must share the same bit size and
 * the result type is the comon one of the secondand third operands
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/bitwise_select.hpp>
 * \endcode
 * 
 * 
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0,class A1,class A2>
 *     meta::call<tag::bitwise_select_(A0,A1,A2)>::type
 *     bitwise_select(const A0 & a0,const A1 & a1,const A2 & a2);
 * }
 * \endcode
 *
 * \param a0 is the first parameter of bitwise_select
 * \param a1 is the second parameter of bitwise_select
 * \param a2 is the third parameter of bitwise_select
 * 
 * \return a value of the common type of the parameters
 *  
 * \internal end_functor \endinternal
**/

namespace boost { namespace simd { namespace tag
  {         
    /*!
     * \internal tag \endinternal
     * \file
     * \brief Define the tag bitwise_select_ of functor bitwise_select 
     *        in namespace boost::simd::tag
     * \internal end_tag \endinternal
    **/
    struct bitwise_select_ {};
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::bitwise_select_, bitwise_select, 3)
} }

#endif

// modified by jt the 25/12/2010
