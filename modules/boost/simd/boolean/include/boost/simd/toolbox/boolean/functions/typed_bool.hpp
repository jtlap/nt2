//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_SIMD_TOOLBOX_BOOLEAN_FUNCTIONS_TYPED_BOOL_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_BOOLEAN_FUNCTIONS_TYPED_BOOL_HPP_INCLUDED
/*!
 * \file
**/
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \ingroup boost_simd_boolean
 * \defgroup boost_simd_boolean_typed_bool typed_bool
 *
 * \par Description
 * return a "SIMD boolean" value arithmetically compatible
 * with the input type parameter where all bits are set if
 * a0 is not zero else no bit is set is a0 is zero.
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/typed_bool.hpp>
 * \endcode
 * 
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A1>
 *     T typed_bool(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the parameter of typed_bool
 * \param T template parameter of typed_bool
 * 
 * \return a value of the type of the template parameter
 * \par
 *  
**/

namespace boost { namespace simd { namespace tag
  {         
    /*!
     * \brief Define the tag typed_bool_ of functor typed_bool 
     *        in namespace boost::simd::tag for toolbox boost.simd.boolean
    **/
    struct typed_bool_ {};
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::typed_bool_, typed_bool, 1)
} }
 
#endif
