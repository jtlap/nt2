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
#ifndef BOOST_SIMD_TOOLBOX_REDUCTION_FUNCTIONS_AT_I_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_REDUCTION_FUNCTIONS_AT_I_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \ingroup boost_simd_reduction
 * \defgroup boost_simd_reduction_at_i at_i
 *
 * \par Description
 * returns the ith element of the input vector.
 * Type of i must be integer and scalar and in the proper vector range.
 * \parNo check is performed to ensure that i is in the correct range
 * [0,meta::cardinal_of<A0>::value[
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/at_i.hpp>
 * \endcode
 * 
 * \par Alias 
 * \arg at
 * 
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::at_i_(A0,A0)>::type
 *     at_i(const A0 & a0,const A0 & a1);
 * }
 * \endcode
 *
 * \param a0 the first parameter of at_i
 * \param a1 the second parameter of at_i
 * 
 * \return always a scalar value
 *  
 * \par Notes
 * \par
 * This is a reduction operation. As such it has not real interest outside
 * SIMD mode.
 * \par
 * Such an operation always has a scalar result which translate a property
 * of the whole SIMD vector.
 * \par
 * If usable and used in scalar mode, it reduces to the operation as acting
 * on a one element vector.
 *  
**/

namespace boost { namespace simd {
  namespace tag
  {
    /*!
     * \brief Define the tag at_i_ of functor at_i 
     *        in namespace boost::simd::tag for toolbox boost.simd.reduction
    **/
    struct at_i_ : ext::reduction_<at_i_>{};
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::at_i_, at_i, 2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::at_i_, at, 2)
} }

#endif
