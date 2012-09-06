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
#ifndef BOOST_SIMD_TOOLBOX_SWAR_FUNCTIONS_GROUP_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_SWAR_FUNCTIONS_GROUP_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \ingroup boost_simd_swar
 * \defgroup boost_simd_swar_group group
 *
 * \par Description
 * take two SIMD vectors of same type and elements of size n
 * and return a vector collecting the two in a vector in which
 * the elements have size n/2
 * \par
 * Of course the applicability is conditionned by the existence of compatible
 * SIMD vector types
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/group.hpp>
 * \endcode
 * 
 * 
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::group_(A0,A0)>::type
 *     group(const A0 & a0,const A0 & a1);
 * }
 * \endcode
 *
 * \param a0 the first parameter of group
 * \param a1 the second parameter of group
 * 
 * \return a value of the common type of the parameters
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
     * \brief Define the tag group_ of functor group 
     *        in namespace boost::simd::tag for toolbox boost.simd.swar
    **/
    struct group_ : ext::elementwise_<group_> { typedef ext::elementwise_<group_> parent; };
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::group_, group, 1)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::group_, group, 2)
} }

#endif

// modified by jt the 25/12/2010
