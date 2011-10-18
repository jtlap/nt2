///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_SIMD_TOOLBOX_BOOLEAN_FUNCTIONS_SELSUB_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_BOOLEAN_FUNCTIONS_SELSUB_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \ingroup boost_simd_boolean
 * \defgroup boost_simd_boolean_selsub selsub
 *
 * \par Description
 * The function returns the second entry or the difference of the second and third entries,
 * according to the first entry being True or False
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/selsub.hpp>
 * \endcode
 * 
 * 
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0, class A1>
 *     meta::call<tag::selsub_(A0,A1,A1)>::type
 *     selsub(const A0 & a0,const A1 & a1,const A1 & a2);
 * }
 * \endcode
 *
 * \param a0 the first parameter of selsub
 * \param a1 the second parameter of selsub, must be an integer value
 * \param a2 the third parameter of selsub
 * 
 * \return a value of the common type of the 2 last parameters
 *  
 * \par Notes
 * In SIMD mode, this function acts elementwise on the inputs vectors elements
 * \par
 *  
**/

namespace boost { namespace simd { namespace tag
  {         
    /*!
     * \brief Define the tag selsub_ of functor selsub 
     *        in namespace boost::simd::tag for toolbox boost.simd.boolean
    **/
    struct selsub_ {};
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::selsub_, selsub, 3)
} }

#endif

// modified by jt the 25/12/2010
