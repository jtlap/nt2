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
#ifndef BOOST_SIMD_TOOLBOX_SWAR_FUNCTIONS_LOOKUP_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_SWAR_FUNCTIONS_LOOKUP_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \ingroup boost_simd_swar
 * \defgroup boost_simd_swar_lookup lookup
 *
 * \par Description
 * shuffles the elements of a1 using indices in a2
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/lookup.hpp>
 * \endcode
 * 
 * 
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::lookup_(A0,A0)>::type
 *     lookup(const A0 & a0,const A0 & a1);
 * }
 * \endcode
 *
 * \param a0 the first parameter of lookup
 * \param a1 the second parameter of lookup
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
     * \brief Define the tag lookup_ of functor lookup 
     *        in namespace boost::simd::tag for toolbox boost.simd.swar
    **/
    struct lookup_ : ext::unspecified_<lookup_> { typedef ext::unspecified_<lookup_> parent; };
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::lookup_, lookup, 2)
} }

#endif

// modified by jt the 25/12/2010
