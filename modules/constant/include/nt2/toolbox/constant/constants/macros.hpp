//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_CONSTANT_CONSTANTS_MACROS_HPP_INCLUDED
#define NT2_TOOLBOX_CONSTANT_CONSTANTS_MACROS_HPP_INCLUDED
#include <nt2/sdk/meta/as.hpp>
#include <nt2/sdk/functor/functor.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/sdk/functor/preprocessor/call.hpp>
#include <boost/proto/proto.hpp>
#include <nt2/sdk/constant/category.hpp>
/*!
 * \file
 * \brief Defines the NT2_CONSTANT_IMPLEMENTATION macro
 */

#define NT2_CONSTANT_IMPLEMENTATION(TAG,NAME)           \
template<class Target> inline                           \
typename meta::call<TAG(nt2::meta::as_<Target>)>::type  \
NAME()                                                  \
{                                                       \
  typename nt2::make_functor<TAG, Target>::type callee; \
  return callee( nt2::meta::as_<Target>() );            \
}                                                       \
/**/

#define NT2_STD_CONSTANT_TAG(NAME)					\
  namespace nt2 { namespace tag { struct NAME{}; } }			\
  /**/

#define NT2_STD_CONSTANT_DEF(NAME)					\
namespace nt2 {						 	        \
  template<class Target> inline						\
  typename nt2::meta::call<nt2::tag::NAME(nt2::meta::as_<Target>)>::type\
  NAME()								\
  {									\
    typename nt2::make_functor<nt2::tag::NAME, Target>::type callee;	\
    return callee( nt2::meta::as_<Target>() );				\
  }									\
}									\
/**/

#define NT2_STD_CONSTANT_STRUCT(NAME,TAG,VAL)			  \
  NT2_FUNCTOR_IMPLEMENTATION(tag::NAME,tag::cpu_,(A0)		  \
			     , (target_< scalar_<TAG<A0> > >)	  \
                            )                                     \
  {                                                               \
    typedef typename strip<A0>::type::type result_type;           \
    NT2_FUNCTOR_CALL(1)                                           \
    {                                                             \
      typedef typename as_integer<result_type>::type itype;	  \
      ignore_unused(a0);                                          \
      return splat<result_type>(bitwise_cast<result_type,	  \
				itype>(VAL));			  \
    }                                                             \
  };                                                              \
  /**/  

#define NT2_PROTOIZE_CONSTANT(NAME)					\
  namespace nt2{							\
    boost::proto::terminal<nt2::constant_<nt2::tag::NAME> >::type	\
      NAME##_= {{}};							\
  }									\
  /**/

//==============================================================================
// Fill up the call needed for a standard constant call
//==============================================================================
#define NT2_STD_CONSTANT_FUNCTOR(NAME,DOUBLE,FLOAT,INT)	  \
namespace nt2 { namespace meta {			  \
    NT2_STD_CONSTANT_STRUCT(NAME,double_, DOUBLE); 	  \
    NT2_STD_CONSTANT_STRUCT(NAME,float_,  FLOAT); 	  \
    NT2_STD_CONSTANT_STRUCT(NAME,integer_,INT);		  \
} }							  \
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

#define NT2_MAKE_STD_CONSTANT(NAME,HEXDOUBLE,HEXFLOAT,INT) \
  NT2_STD_CONSTANT_TAG(NAME)				   \
  NT2_STD_CONSTANT_DEF(NAME)				   \
  NT2_STD_CONSTANT_FUNCTOR(NAME, HEXDOUBLE, HEXFLOAT, INT) \
  NT2_PROTOIZE_CONSTANT(NAME)				   \
  /**/

#endif
