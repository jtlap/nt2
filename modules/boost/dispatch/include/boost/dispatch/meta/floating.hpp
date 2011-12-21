//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_DISPATCH_META_FLOATING_HPP_INCLUDED
#define BOOST_DISPATCH_META_FLOATING_HPP_INCLUDED

/*!
 * \file
 * \brief Defines and implements the meta::floating \metafunction
 */

#include <boost/dispatch/meta/make_floating.hpp>

#if defined(BOOST_DISPATCH_DONT_USE_PREPROCESSED_FILES)
#include <boost/dispatch/details/parameters.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#endif

namespace boost { namespace dispatch  { namespace meta
{
  //============================================================================
  /*!
   * \ingroup metafunctions
   * For a list of types \c T0,...,Tn, floating computes the type able to
   * store a value of the smallest floating-point value type compatible with
   * all \c T0,...,Tn
   *
   * \semantic
   *
   * For types \c T0,...,Tn,
   *
   * \code
   * typedef result_of<floating(T0,...,Tn)>::type type
   * \endcode
   *
   * is equivalent to:
   *
   * \code
   * typedef boost::dispatch::meta:::make_floating< max<sizeof(float),...,sizeof(Tn)>::value >::type type;
   * \endcode
   *
   * \usage:
   *
   * \include floating.cpp
   */
  //============================================================================
  struct floating
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct  result<This(A0)>
    {
      typedef float base_real;
      BOOST_STATIC_CONSTANT ( std::size_t
                            , value = (sizeof(A0) > sizeof(base_real))
                                    ?  sizeof(A0) : sizeof(base_real)
                            );
      typedef typename meta::make_floating<value>::type type;
    };

#if !defined(BOOST_DISPATCH_DONT_USE_PREPROCESSED_FILES)
#include <boost/dispatch/meta/preprocessed/floating.hpp>
#else
#if defined(__WAVE__) && defined(BOOST_DISPATCH_CREATE_PREPROCESSED_FILES) && __INCLUDE_LEVEL__ == 0
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/floating.hpp")
#undef BOOST_STATIC_CONSTANT
#endif

    #define M1(z,n,t)                                               \
    BOOST_STATIC_CONSTANT ( std::size_t                             \
                          , BOOST_PP_CAT(value,BOOST_PP_INC(n)) =   \
                            (   BOOST_PP_CAT(value,n)               \
                              > sizeof(BOOST_PP_CAT(A,n))           \
                            ) ? BOOST_PP_CAT(value,n)               \
                              : sizeof(BOOST_PP_CAT(A,n))           \
                          );                                        \
    /**/
    #define M0(z,n,t)                                                     \
    template<class This,BOOST_PP_ENUM_PARAMS(n,class A)>                  \
    struct  result<This(BOOST_PP_ENUM_PARAMS(n,A))>                       \
    {                                                                     \
      typedef float base_real;                                            \
      BOOST_STATIC_CONSTANT ( std::size_t, value0 =  sizeof(base_real) ); \
      BOOST_PP_REPEAT(n,M1,~)                                             \
      typedef typename                                                    \
      meta::make_floating<BOOST_PP_CAT(value,n)>::type type;                  \
    };                                                                    \
     /**/

    BOOST_PP_REPEAT_FROM_TO(2,BOOST_DISPATCH_MAX_ARITY,M0,~)
    #undef M1
    #undef M0
    
#if defined(__WAVE__) && defined(BOOST_DISPATCH_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif
#endif
    
  };
} } }

#endif
