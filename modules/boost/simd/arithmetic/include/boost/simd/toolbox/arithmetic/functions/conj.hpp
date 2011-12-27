//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/U.B.P.
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ. Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
/*!
 * \file
**/
#ifndef BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_CONJ_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_CONJ_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \ingroup boost_simd_arithmetic
 * \defgroup boost_simd_arithmetic_conj conj
 *
 * \par Description
 * conjugate of the entry (identity for reals).
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/conj.hpp>
 * \endcode
 * 
 * \par Alias 
 * \arg conjugate
 * 
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::conj_(A0)>::type
 *     conj(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the unique parameter of conj
 * 
 * \return a value of the same type as the parameter
 *  
 * \par Notes
 * In SIMD mode, this function acts elementwise on the inputs vectors elements
 * \par
 *  
**/

namespace boost { namespace simd { namespace tag
  {
    /*!
     * \brief Define the tag conj_ of functor conj 
     *        in namespace boost::simd::tag for toolbox boost.simd.arithmetic
    **/
    struct conj_ {};
  }

  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::conj_, conj, 1)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::conj_, conjugate, 1)
} }

#endif

// modified by jt the 25/12/2010
