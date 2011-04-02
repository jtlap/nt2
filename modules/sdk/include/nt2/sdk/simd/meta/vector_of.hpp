/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_SIMD_META_VECTOR_OF_HPP_INCLUDED
#define NT2_SDK_SIMD_META_VECTOR_OF_HPP_INCLUDED

#include <boost/array.hpp>
#include <boost/preprocessor/seq/for_each.hpp>

////////////////////////////////////////////////////////////////////////////////
// Forward declaration for native
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace simd
{
  template<class Scalar,class Extension> struct native;
} }

#define NT2_LOCAL(z,d,r)                                                \
template<class T,std::size_t Card>                                      \
struct vector_of< T ,Card                                               \
                , typename boost::                                      \
                  enable_if_c < (   Card*sizeof(T)                      \
                                ==  sizeof(typename as_simd<T,r>::type) \
                                )                                       \
                              >::type                                   \
                >                                                       \
{                                                                       \
  typedef simd::native<T,r> type;                                       \
};                                                                      \
/**/

namespace nt2 { namespace meta
{
  //////////////////////////////////////////////////////////////////////////////
  // vector_of<T,N> computes the proper type for pack of N elements of types T
  // Either <T,N> maps onto a SIMD types, either to array<T,N>
  //////////////////////////////////////////////////////////////////////////////
  template<class T,std::size_t Card, class Enable=void>
  struct vector_of
  {
    typedef boost::array<T,Card> type;
  };

  BOOST_PP_SEQ_FOR_EACH(NT2_LOCAL,~,NT2_SIMD_TAG_SEQ)

} }

#endif
