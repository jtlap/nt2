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
#ifndef BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_EPS_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_EPS_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \ingroup boost_simd_ieee
 * \defgroup boost_simd_ieee_eps eps
 *
 * \par Description
 * Returns 2 times the Machine epsilon
 * \par
 * The Machine epsilon gives an upper bound on the relative
 * error due to rounding in floating point arithmetic. Typically $2^{-53}$
 * for floating point doubles and $2^{-24}$ for
 * floats. MATLAB(TM) language defines the value eps 
 * as the distance from 1.0 to the next larger double
 * which is two times the machine epsilon...
 * Returns one for integer types.
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/eps.hpp>
 * \endcode
 * 
 * 
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::eps_(A0)>::type
 *     eps(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the unique parameter of eps
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
     * \brief Define the tag eps_ of functor eps 
     *        in namespace boost::simd::tag for toolbox boost.simd.ieee
    **/
    struct eps_ : ext::elementwise_<eps_>{};
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::eps_, eps, 1)
} }

#endif

// modified by jt the 25/12/2010
