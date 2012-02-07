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
#ifndef BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_BITOFSIGN_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_BITOFSIGN_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \ingroup boost_simd_ieee
 * \defgroup boost_simd_ieee_bitofsign bitofsign
 *
 * \par Description
 * Returns a value of the same type as the input
 * with all bits set to zero
 * except the bit of sign which is preserved.
 * Returns always zero for unsigned types
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/bitofsign.hpp>
 * \endcode
 * 
 * 
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::bitofsign_(A0)>::type
 *     bitofsign(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the unique parameter of bitofsign
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
     * \brief Define the tag bitofsign_ of functor bitofsign 
     *        in namespace boost::simd::tag for toolbox boost.simd.ieee
    **/
    struct bitofsign_ : ext::elementwise_<bitofsign_> { typedef ext::elementwise_<bitofsign_> parent; };
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::bitofsign_, bitofsign, 1)
} }

#endif

// modified by jt the 25/12/2010
