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
#ifndef BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_PREDECESSOR_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_PREDECESSOR_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \ingroup boost_simd_ieee
 * \defgroup boost_simd_ieee_predecessor predecessor
 *
 * \par Description
 * With one parameter it is equivalent to \c prev
 * It is in the type \c A0, the greatest  \c A0 elementwise strictly less than  \c a0.
 * \par
 * With two parameters, the second is an integer value  \c n
 * and the result is equivalent to applying \c prev \c abs(n) times to  \c a0.
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/predecessor.hpp>
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
 * \param a0 the first parameter of predecessor
 * \param a1 the second parameter of predecessor
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
     * \brief Define the tag predecessor_ of functor predecessor 
     *        in namespace boost::simd::tag for toolbox boost.simd.ieee
    **/
    struct predecessor_ : ext::elementwise_<predecessor_> { typedef ext::elementwise_<predecessor_> parent; };
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::predecessor_, predecessor, 2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::predecessor_, predecessor, 1)
} }

#endif

// modified by jt the 25/12/2010
