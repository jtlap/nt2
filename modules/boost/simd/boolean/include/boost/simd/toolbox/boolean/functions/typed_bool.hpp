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
 * return a SIMD boolean value arithmetically compatible
 * with the template type parameter where all bits are set if
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
 *   template <class T,class A1>
 *     T typed_bool < T > (const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the parameter of typed_bool
 * \param T template parameter of typed_bool
 * 
 * \return a value of the type of the template parameter
 *  
 * \par Notes
 * In SIMD mode, this function acts elementwise on the inputs vectors elements
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
  
  template<class T, class A0> inline
  typename boost::dispatch::meta::call<tag::typed_bool_(A0, boost::dispatch::meta::as_<T>)>::type
  typed_bool(A0 const& a0)
  {
    typename boost::dispatch::make_functor<tag::typed_bool_, A0>::type callee;
    return callee(a0, boost::dispatch::meta::as_<T>() );
  }
} }
 
#endif
