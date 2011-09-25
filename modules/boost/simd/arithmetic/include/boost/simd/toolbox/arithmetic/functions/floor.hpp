//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_FLOOR_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_FLOOR_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \internal functor \endinternal
 * \ingroup boost_simd_arithmetic
 * \defgroup floor floor function
 *
 * \par Description
 * return a value of the same type of the entry
 * which is the greatest integer less or equal to the entry
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/floor.hpp>
 * \endcode
 * 
 * 
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::floor_(A0)>::type
 *     floor(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 is the unique parameter of floor
 * 
 * \return a value of the same type as the parameter
 *  
 * \internal end_functor \endinternal
**/

namespace boost { namespace simd { namespace tag
  {         
    /*!
     * \internal tag \endinternal
     * \file
     * \brief Define the tag floor_ of functor floor 
     *        in namespace boost::simd::tag
     * \internal end_tag \endinternal
    **/
    struct floor_ {};
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::floor_, floor, 1)
} }

#endif

// modified by jt the 25/12/2010
