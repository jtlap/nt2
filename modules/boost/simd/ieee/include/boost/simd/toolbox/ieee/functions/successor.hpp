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
#ifndef BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_SUCCESSOR_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_SUCCESSOR_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \ingroup boost_simd_ieee
 * \defgroup boost_simd_ieee_successor successor
 *
 * \par Description
 * With one parameter it is equivalent to \c next
 * It is in the type \c A0, the least  \c A0 elementwise strictly greater than  \c a0.
 * \par
 * With two parameters, the second is an integer value  \c n
 * and the result is equivalent to applying \c next \c abs(n) times to  \c a0.
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/successor.hpp>
 * \endcode
 * 
 * 
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template<class A0> inline
 *   A0 predecessor(A0 const& a0);
 *    
 *   template<class A0,class A1> inline
 *   A0 predecessor(A0 const& a0,const A1& n);
 * }
 * \endcode
 *
 * \param a0 the first parameter of successor
 * \param a1 the second parameter of successor
 * 
 * \return a value of type A0
 *  
 * \par Notes
 * In SIMD mode, this function acts elementwise on the inputs vectors elements
 * \par
 *  
**/

namespace boost { namespace simd { namespace tag
  {         
    /*!
     * \brief Define the tag successor_ of functor successor 
     *        in namespace boost::simd::tag for toolbox boost.simd.ieee
    **/
    struct successor_ : ext::elementwise_<successor_> { typedef ext::elementwise_<successor_> parent; };
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::successor_, successor, 1)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::successor_, successor, 2)
} }

#endif

// modified by jt the 25/12/2010
