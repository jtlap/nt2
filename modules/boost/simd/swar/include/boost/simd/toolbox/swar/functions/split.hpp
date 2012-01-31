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
#ifndef BOOST_SIMD_TOOLBOX_SWAR_FUNCTIONS_SPLIT_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_SWAR_FUNCTIONS_SPLIT_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \ingroup boost_simd_swar
 * \defgroup boost_simd_swar_split split
 *
 * \par Description
 * takes one SIMD vector of elements of size n
 * and returns two vectors of same type containing respectively
 * the first and last half elements of the input but in vectors
 * in which element size is 2*n
 * \par
 * Of course the applicability is conditionned by the existence of compatible
 * SIMD vector types
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/split.hpp>
 * \endcode
 * 
 * 
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::split_(A0)>::type
 *     split(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the unique parameter of split
 * 
 * \return a value of the same type as the parameter
 *  
 * \par Notes
 * \par
 * This is a swar operation. As such it has not real interest outside
 * SIMD mode.
 * \par
 * Such an operation is a transform of an SIMD vector, that will return
 * vectors obtained on a non necessarily elementwise basis from the inputs
 * elements
 * \par
 * If usable and used in scalar mode, it reduces to the operation
 * on a one element vector.
 *  
**/

namespace boost { namespace simd { namespace tag
  {         
    /*!
     * \brief Define the tag split_ of functor split 
     *        in namespace boost::simd::tag for toolbox boost.simd.swar
    **/
    struct split_ : ext::unspecified_<split_>{};
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::split_, split, 1)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(tag::split_, split, (A0 const &)(A1&)(A1&), 2)
} }

#endif

// modified by jt the 25/12/2010
