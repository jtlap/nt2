//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_SIMD_TOOLBOX_PREDICATES_FUNCTIONS_MAJORITY_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_PREDICATES_FUNCTIONS_MAJORITY_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \internal functor \endinternal
 * \ingroup boost_simd_predicates
 * \defgroup majority majority function
 *
 * \par Description
 * Returns True<A0>() if at least two inputs are not zero else False<A0>().
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/majority.hpp>
 * \endcode
 * 
 * 
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::majority_(A0,A0,A0)>::type
 *     majority(const A0 & a0,const A0 & a1,const A0 & a2);
 * }
 * \endcode
 *
 * \param a0 is the first parameter of majority
 * \param a1 is the second parameter of majority
 * \param a2 is the third parameter of majority
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
     * \brief Define the tag majority_ of functor majority 
     *        in namespace boost::simd::tag
     * \internal end_tag \endinternal
    **/
    struct majority_ {};
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::majority_, majority, 3)
} }

#endif

// modified by jt the 25/12/2010
