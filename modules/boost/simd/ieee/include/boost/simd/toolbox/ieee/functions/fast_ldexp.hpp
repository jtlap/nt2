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
#ifndef BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_FAST_LDEXP_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_FAST_LDEXP_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \ingroup boost_simd_ieee
 * \defgroup boost_simd_ieee_fast_ldexp fast_ldexp
 *
 * \par Description
 * The function multiply a floating entry $a_0$
 * by $2^a_1$
 * \par
 * The fast prefix indicates that for speed sake
 * the result may be incorrect for limiting values:
 * inf, -inf nan and zero that deserve special treatment.If you are not sure use \c ldexp, at the expense
 * of some more machine cycles.
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/fast_ldexp.hpp>
 * \endcode
 * 
 * 
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::fast_ldexp_(A0,A0)>::type
 *     fast_ldexp(const A0 & a0,const A0 & a1);
 * }
 * \endcode
 *
 * \param a0 the first parameter of fast_ldexp
 * \param a1 the second parameter of fast_ldexp
 * 
 * \return a value of the common type of the parameters
 *  
 * \par Notes
 * In SIMD mode, this function acts elementwise on the inputs vectors elements
 * \par
 *  
**/

namespace boost { namespace simd { namespace tag
  {         
    /*!
     * \brief Define the tag fast_ldexp_ of functor fast_ldexp 
     *        in namespace boost::simd::tag for toolbox boost.simd.ieee
    **/
    struct fast_ldexp_ : ext::elementwise_<fast_ldexp_> { typedef ext::elementwise_<fast_ldexp_> parent; };
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::fast_ldexp_, fast_ldexp, 2)
} }

#endif

// modified by jt the 25/12/2010
