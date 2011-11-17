/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef BOOST_SIMD_SDK_SIMD_META_VECTOR_OF_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_META_VECTOR_OF_HPP_INCLUDED

#include <boost/simd/sdk/simd/native_fwd.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/mpl/sizeof.hpp>
#include <boost/array.hpp>

/* We use boost::mpl::sizeof_ rather than sizeof because MSVC has trouble
 * with sizeof of dependent names in SFINAE contexts */
#define BOOST_SIMD_LOCAL(z,d,r)                                         \
template<class T,std::size_t Card>                                      \
struct vector_of< T ,Card                                               \
                , typename boost::                                      \
                  enable_if_c < (   Card*sizeof(T)                      \
                                ==  boost::mpl::                        \
                                    sizeof_<                            \
                                             typename as_simd<T,r>::type\
                                           >::value                     \
                                )                                       \
                              >::type                                   \
                >                                                       \
{                                                                       \
  typedef simd::native<T,r> type;                                       \
};                                                                      \
/**/

namespace boost { namespace simd { namespace meta
{
  //////////////////////////////////////////////////////////////////////////////
  // vector_of<T,N> computes the proper type for pack of N elements of types T
  // Either <T,N> maps onto a SIMD types, either to array<T,N>
  //////////////////////////////////////////////////////////////////////////////
  template<class T,std::size_t Card, class Enable=void>
  struct vector_of
  {
    typedef simd::native<T, tag::simd_emulation_<mpl::size_t<sizeof(T)*Card> > > type;
  };

#ifdef BOOST_SIMD_DETECTED
  BOOST_PP_SEQ_FOR_EACH(BOOST_SIMD_LOCAL,~,BOOST_SIMD_TAG_SEQ)
#endif

#undef BOOST_SIMD_LOCAL

} } }

#endif
