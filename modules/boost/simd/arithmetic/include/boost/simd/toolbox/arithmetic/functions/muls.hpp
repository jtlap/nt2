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
#ifndef BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_MULS_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_MULS_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \ingroup boost_simd_arithmetic
 * \defgroup boost_simd_arithmetic_muls muls
 *
 * \par Description
 * return the saturated multiplication of a0 by a1
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/muls.hpp>
 * \endcode
 * 
 * 
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::muls_(A0,A0)>::type
 *     muls(const A0 & a0,const A0 & a1);
 * }
 * \endcode
 *
 * \param a0 the first parameter of muls
 * \param a1 the second parameter of muls
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
     * \brief Define the tag muls_ of functor muls 
     *        in namespace boost::simd::tag for toolbox boost.simd.arithmetic
    **/
    struct muls_ : ext::elementwise_<muls_>{};
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::muls_, muls, 2)
} }

#endif
