//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_SWAR_FUNCTIONS_SHUFFLE_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_SWAR_FUNCTIONS_SHUFFLE_HPP_INCLUDED

/*!
  @file
**/

#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>
#include <boost/simd/toolbox/swar/functions/details/random_permute.hpp>
#include <boost/simd/sdk/simd/extensions.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/mpl/vector_c.hpp>

namespace boost { namespace simd 
{ 
  namespace tag
  {
    /*!
     * \brief Define the tag shuffle_ of functor shuffle
     *        in namespace boost::simd::tag for toolbox boost.simd.swar
    **/
    struct shuffle_ : ext::unspecified_<shuffle_> { typedef ext::unspecified_<shuffle_> parent; };
  }

  template<class T,class A0>
  BOOST_FORCEINLINE
  typename  boost::dispatch::meta
          ::call<tag::shuffle_( A0 const&, boost::dispatch::meta::as_<T>)>::type
  shuffle(A0 const& a0)
  {
    typename boost::dispatch::make_functor<tag::shuffle_, A0>::type callee;
    return callee(a0,boost::dispatch::meta::as_<T>());
  }

  template<class T,class A0, class A1>
  BOOST_FORCEINLINE
  typename  boost::dispatch::meta
          ::call<tag::shuffle_( A0 const&, A1 const& a1
                              , boost::dispatch::meta::as_<T>)
                >::type
  shuffle(A0 const& a0, A1 const& a1)
  {
    typename boost::dispatch::make_functor<tag::shuffle_, A0>::type callee;
    return callee(a0,a1,boost::dispatch::meta::as_<T>());
  }

#define M01(z,n,arg)                                                           \
template<BOOST_PP_ENUM_PARAMS(arg, int I),class A0>                            \
BOOST_FORCEINLINE                                                              \
typename boost::dispatch::meta                                                 \
::call<tag::shuffle_(A0 const&                                                 \
                    ,boost::dispatch::meta::                                   \
                     as_<details::random_permute                               \
                         <boost::mpl::                                         \
                          vector_c<int,BOOST_PP_ENUM_PARAMS(arg, I)>           \
                         >                                                     \
                        >                                                      \
                    )                                                          \
      >::type                                                                  \
shuffle(A0 const& a0)                                                          \
{                                                                              \
  typename boost::dispatch::make_functor<tag::shuffle_, A0>::type callee;      \
  return callee( a0                                                            \
               , boost::dispatch::meta::                                       \
                 as_< details::                                                \
                      random_permute< boost::mpl::                             \
                                      vector_c< int                            \
                                              , BOOST_PP_ENUM_PARAMS(arg, I)   \
                                              >                                \
                                    >                                          \
                    >()                                                        \
               );                                                              \
}                                                                              \
/**/

#define M02(z,n,arg)                                                           \
template<BOOST_PP_ENUM_PARAMS(arg, int I),class A0, class A1>                  \
BOOST_FORCEINLINE                                                              \
typename boost::dispatch::meta                                                 \
::call<tag::shuffle_( A0 const&                                                \
                    , A1 const&                                                \
                    , boost::dispatch::meta::                                  \
                      as_<details::random_permute                              \
                          <boost::mpl::                                        \
                           vector_c                                            \
                           <int                                                \
                           ,BOOST_PP_ENUM_PARAMS(arg, I)                       \
                           >                                                   \
                          >                                                    \
                         >                                                     \
                    )                                                          \
      >::type                                                                  \
shuffle(A0 const& a0, A1 const& a1)                                            \
{                                                                              \
  typename boost::dispatch::make_functor<tag::shuffle_, A0>::type callee;      \
  return callee( a0                                                            \
               , a1                                                            \
               , boost::dispatch::meta::                                       \
                 as_< details::                                                \
                      random_permute                                           \
                      <boost::mpl::                                            \
                       vector_c<int                                            \
                               ,BOOST_PP_ENUM_PARAMS(arg, I)                   \
                               >                                               \
                      >                                                        \
                    >()                                                        \
               );                                                              \
}                                                                              \
/**/

  BOOST_PP_SEQ_FOR_EACH(M01, ~, BOOST_SIMD_CARDINALS)
  BOOST_PP_SEQ_FOR_EACH(M02, ~, BOOST_SIMD_CARDINALS)
  #undef M01
  #undef M02
} }

#endif
