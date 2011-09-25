//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_SIMD_TOOLBOX_BITWISE_FUNCTIONS_BITWISE_ORNOT_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_BITWISE_FUNCTIONS_BITWISE_ORNOT_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \internal functor \endinternal
 * \ingroup boost_simd_bitwise
 * \defgroup bitwise_ornot bitwise_ornot function
 *
 * \par Description
 * return the bitwise or of the first parameter
 * with the bitwise complement of the second parameter.
 * \par
 * The operands must share the same bit size and
 * the result type is the one of the first operand
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/bitwise_ornot.hpp>
 * \endcode
 * 
 * \par Alias 
 * \arg b_ornot
 * 
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::bitwise_ornot_(A0,A0)>::type
 *     bitwise_ornot(const A0 & a0,const A0 & a1);
 * }
 * \endcode
 *
 * \param a0 is the first parameter of bitwise_ornot
 * \param a1 is the second parameter of bitwise_ornot
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
     * \brief Define the tag bitwise_ornot_ of functor bitwise_ornot 
     *        in namespace boost::simd::tag
     * \internal end_tag \endinternal
    **/
    struct bitwise_ornot_ {};
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::bitwise_ornot_, bitwise_ornot, 2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::bitwise_ornot_, b_ornot, 2)
} }

#endif
