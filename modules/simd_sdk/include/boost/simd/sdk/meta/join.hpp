//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_META_JOIN_HPP_INCLUDED
#define BOOST_SIMD_SDK_META_JOIN_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Compute the lazy union of two types set
// See: http://nt2.metascale.org/sdk/meta/set/join.hpp
////////////////////////////////////////////////////////////////////////////////
#include <boost/simd/sdk/meta/has_key.hpp>

namespace boost { namespace simd {  namespace meta
{
  //============================================================================
  /*!
   * Computes the compile-time union of two boost::simd::meta::sets.
   *
   * \par Model:
   *
   * \metafunction
   *
   * \semantic
   *
   * For any two boost::simd::meta::set \c S1,S2,
   *
   * \code
   * typedef boost::simd::meta::join<S1,S2>::type r;
   * \endcode
   *
   * evaluates to a type behaving like a boost::simd::meta::set that, for a given
   * key \c K, is defined so that \c has_key<K,r>::type evaluates to \true_
   * if \c has_key<S1,r>::type or \c has_key<S2,r>::type evaluates to \true_.
   *
   * \usage
   *
   * \include join.cpp
   */
  //============================================================================
  template<class H1,class H2> struct join
  {
    typedef void is_set_type;
    template<class T>
    static boost::mpl::bool_< has_key<H1,T>::value ||  has_key<H2,T>::value >
    key(T*);
  };
} } }

#endif
