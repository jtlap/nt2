//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_MOD_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_MOD_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>


/*!
 * \internal functor \endinternal
 * \ingroup boost_simd_arithmetic
 * \defgroup mod mod function
 *
 * \par Description
 * The function computes the remainder of dividing a0 by a1.
 * The return value is a0-n*a1, where n is the value a0/a1, rounded to -inf.\par
 * if one prefer: if a1 is zero returns a0, else return
 * a0-divfloor(a0,a1)*a1
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/mod.hpp>
 * \endcode
 * 
 * 
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::mod_(A0,A0)>::type
 *     mod(const A0 & a0,const A0 & a1);
 * }
 * \endcode
 *
 * \param a0 is the first parameter of mod
 * \param a1 is the second parameter of mod
 * 
 * \return a value of the common type of the parameters
 *  
 * \internal end_functor \endinternal
**/
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
namespace boost { namespace simd { namespace tag
  {         
    /*!
     * \internal tag \endinternal
     * \file
     * \brief Define the tag mod_ of functor mod 
     *        in namespace boost::simd::tag
     * \internal end_tag \endinternal
    **/
    struct mod_ {};
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::mod_, mod, 2)
} }
 
#endif

// modified by jt the 25/12/2010
