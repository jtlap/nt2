//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_IDIVFIX_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_IDIVFIX_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \internal functor \endinternal
 * \ingroup boost_simd_arithmetic
 * \defgroup idivfix idivfix function
 *
 * \par Description
 * return the \c truncation of the operands real divisionin the corresponding integer type
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/idivfix.hpp>
 * \endcode
 * 
 * 
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::idivfix_(A0,A0)>::type
 *     idivfix(const A0 & a0,const A0 & a1);
 * }
 * \endcode
 *
 * \param a0 is the first parameter of idivfix
 * \param a1 is the second parameter of idivfix
 * 
 * \return an integer value
 *  
 * \internal end_functor \endinternal
**/

namespace boost { namespace simd { namespace tag
  {         
    /*!
     * \internal tag \endinternal
     * \file
     * \brief Define the tag idivfix_ of functor idivfix 
     *        in namespace boost::simd::tag
     * \internal end_tag \endinternal
    **/
    struct idivfix_ {};
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::idivfix_, idivfix, 2)
} }

#endif

// modified by jt the 25/12/2010
