//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_CONSTANT_CONSTANTS_MACROS_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_CONSTANT_CONSTANTS_MACROS_HPP_INCLUDED
#include <boost/dispatch/meta/as.hpp>
#include <boost/dispatch/functor/functor.hpp>
#include <boost/dispatch/meta/strip.hpp>
#include <boost/dispatch/functor/preprocessor/call.hpp>
#include <boost/proto/proto.hpp>
#include <boost/simd/sdk/constant/category.hpp>
/*!
 * \file
 * \brief Defines the BOOST_SIMD_CONSTANT_IMPLEMENTATION macro
 */

/*#define BOOST_SIMD_CONSTANT_IMPLEMENTATION(TAG,NAME)           \
template<class Target> inline                           \
typename boost::dispatch::meta::call<TAG(boost::dispatch::meta::as_<Target>)>::type  \
NAME()                                                  \
{                                                       \
  typename boost::dispatch::make_functor<TAG, Target>::type callee; \
  return callee( boost::dispatch::meta::as_<Target>() );            \
}                                                       \
*//**/

#define BOOST_SIMD_STD_CONSTANT_TAG(NAME)					\
  namespace boost { namespace simd { namespace tag { struct NAME{}; } } }			\
  /**/

#define BOOST_SIMD_STD_CONSTANT_DEF(NAME)					\
namespace boost { namespace simd {						 	        \
  template<class Target> inline						\
  typename boost::dispatch::meta::call<boost::simd::tag::NAME(boost::dispatch::meta::as_<Target>)>::type\
  NAME()								\
  {									\
    typename boost::dispatch::make_functor<boost::simd::tag::NAME, Target>::type callee;	\
    return callee( boost::dispatch::meta::as_<Target>() );				\
  }									\
} }									\
/**/

#define BOOST_SIMD_STD_CONSTANT_STRUCT(NAME,TAG,VAL)			  \
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::NAME,tag::cpu_,(A0)		  \
			     , (target_< scalar_<TAG<A0> > >)	  \
                            )                                     \
  {                                                               \
    typedef typename A0::type result_type;                        \
    BOOST_SIMD_FUNCTOR_CALL(1)                                    \
    {                                                             \
      typedef typename dispatch::meta::as_integer<result_type>::type itype;	  \
      ignore_unused(a0);                                          \
      return boost::simd::splat<result_type>(boost::simd::bitwise_cast<result_type,	  \
				             itype>(VAL));			  \
    }                                                             \
  };                                                              \
  /**/  

#define BOOST_SIMD_PROTOIZE_CONSTANT(NAME)					\
  namespace boost { namespace simd {							\
    boost::proto::terminal<boost::dispatch::constant_<boost::simd::tag::NAME> >::type	\
      NAME##_= {{}};							\
  } }									\
  /**/

//==============================================================================
// Fill up the call needed for a standard constant call
//==============================================================================
#define BOOST_SIMD_STD_CONSTANT_FUNCTOR(NAME,DOUBLE,FLOAT,INT)	  \
namespace boost { namespace simd { namespace ext {           \
    BOOST_SIMD_STD_CONSTANT_STRUCT(NAME,double_, DOUBLE); 	  \
    BOOST_SIMD_STD_CONSTANT_STRUCT(NAME,float_,  FLOAT); 	  \
    BOOST_SIMD_STD_CONSTANT_STRUCT(NAME,integer_,INT);		  \
} } }							          \
/**/


//==============================================================================
/*!
 * Generate a constant function with a given \c NAME 
 *
 * \param NAME Name of the function to build
 * \param HEXDOUBLE  hexadecimal of double value
 * \param HEXFLOAT   hexadecimal of float value
 * \param INT        integer value
 */
//==============================================================================

#define BOOST_SIMD_MAKE_STD_CONSTANT(NAME,HEXDOUBLE,HEXFLOAT,INT) \
  BOOST_SIMD_STD_CONSTANT_TAG(NAME)				   \
  BOOST_SIMD_STD_CONSTANT_DEF(NAME)				   \
  BOOST_SIMD_STD_CONSTANT_FUNCTOR(NAME, HEXDOUBLE, HEXFLOAT, INT) \
  BOOST_SIMD_PROTOIZE_CONSTANT(NAME)				   \
  /**/

#endif
