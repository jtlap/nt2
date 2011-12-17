//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_CONSTANT_REGISTER_HPP_INCLUDED
#define BOOST_SIMD_SDK_CONSTANT_REGISTER_HPP_INCLUDED

/*!
 * \file
 * \brief Defines the BOOST_SIMD_CONSTANT_REGISTER_VALUE macro
 */
 
#include <boost/simd/sdk/meta/int_c.hpp>
#include <boost/simd/sdk/meta/float.hpp>
#include <boost/simd/sdk/meta/double.hpp>
 
//==============================================================================
/*!
 * Generate a named constant from an integral, float and double value set
 * and a default type
 * \param TAG    ID of the constant to generate
 * \param TYPE   Default type of the constant
 * \param INT    Integral value of the constant
 * \param FLOAT  Float value of the constant
 * \param DOUBLE Double value of the constant
 */
//==============================================================================
#define BOOST_SIMD_CONSTANT_REGISTER(TAG,TYPE,INT,FLOAT,DOUBLE)           \
struct TAG                                                                \
{                                                                         \
  typedef TYPE default_type;                                              \
  template<class T, class D=void> struct apply                            \
    : boost::simd::meta::int_c<T,T(INT)> {};                              \
};                                                                        \
template<class D> struct TAG::apply<float,D>                              \
  : boost::simd::meta::single_<FLOAT> {};                                 \
template<class D> struct TAG::apply<double,D>                             \
  : boost::simd::meta::double_<DOUBLE> {};                                \
/**/

#endif
