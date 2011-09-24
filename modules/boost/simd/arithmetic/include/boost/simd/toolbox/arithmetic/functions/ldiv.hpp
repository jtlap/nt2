//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_LDIV_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_LDIV_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>


/*!
 * \internal functor \endinternal
 * \ingroup boost_simd_arithmetic
 * \defgroup ldiv ldiv function
 *
 * \par Description
 * returns the left division of a1 by a0, i.e. a1/a0
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/ldiv.hpp>
 * \endcode
 * 
 * 
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::ldiv_(A0,A0)>::type
 *     ldiv(const A0 & a0,const A0 & a1);
 * }
 * \endcode
 *
 * \param a0 is the first parameter of ldiv
 * \param a1 is the second parameter of ldiv
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
     * \brief Define the tag ldiv_ of functor ldiv 
     *        in namespace boost::simd::tag
     * \internal end_tag \endinternal
    **/
    struct ldiv_ {};
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::ldiv_, ldiv, 2)
} }
 
#endif

// modified by jt the 25/12/2010
