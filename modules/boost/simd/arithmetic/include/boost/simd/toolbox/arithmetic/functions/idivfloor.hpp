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
#ifndef BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_IDIVFLOOR_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_IDIVFLOOR_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \ingroup boost_simd_arithmetic
 * \defgroup boost_simd_arithmetic_idivfloor idivfloor
 *
 * \par Description
 * return the \c floor of the operands real divisionin the corresponding integer type
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/idivfloor.hpp>
 * \endcode
 * 
 * 
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::idivfloor_(A0,A0)>::type
 *     idivfloor(const A0 & a0,const A0 & a1);
 * }
 * \endcode
 *
 * \param a0 the first parameter of idivfloor
 * \param a1 the second parameter of idivfloor
 * 
 * \return an integer value
 *  
 * \par Notes
 * In SIMD mode, this function acts elementwise on the inputs vectors elements
 * \par
 *  
**/

namespace boost { namespace simd { namespace tag
  {         
    /*!
     * \brief Define the tag idivfloor_ of functor idivfloor 
     *        in namespace boost::simd::tag for toolbox boost.simd.arithmetic
    **/
    struct idivfloor_ : ext::elementwise_<idivfloor_>{};
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::idivfloor_, idivfloor, 2)
} }

#endif

// modified by jt the 25/12/2010
