/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef BOOST_SIMD_SDK_SIMD_EXTENSIONS_NONE_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_EXTENSIONS_NONE_HPP_INCLUDED

#if !defined(BOOST_SIMD_DETECTED)
BOOST_SIMD_WARNING(No SIMD extensions detected)
#define BOOST_SIMD_NO_SIMD

#define BOOST_SIMD_BYTES      8
#define BOOST_SIMD_BITS       64
#define BOOST_SIMD_STRING     "none"
#define BOOST_SIMD_CARDINALS (1)(2)(4)(8)
#define BOOST_SIMD_DEFAULT_EXTENSION ::boost::simd::tag::none_<boost::mpl::size_t<8> >
#define BOOST_SIMD_DEFAULT_SITE ::boost::dispatch::tag::cpu_

#if !defined(BOOST_SIMD_SIMD_TYPES)
#include <boost/simd/sdk/simd/extensions/sse/types.hpp>
#endif

#include <boost/dispatch/functor/meta/hierarchy.hpp>
#include <boost/simd/sdk/simd/meta/is_simd_specific.hpp>
#include <boost/simd/sdk/simd/meta/as_simd.hpp>
#include <boost/simd/sdk/simd/meta/extension_of.hpp>

#include <boost/array.hpp>
#include <boost/mpl/times.hpp>
#include <boost/mpl/sizeof.hpp>

namespace boost { namespace simd { namespace tag
{
  template<class N> struct none_ : boost::dispatch::tag::cpu_
  {
    typedef boost::dispatch::tag::cpu_ parent;
    typedef none_ type;
  };
} } }

namespace boost { namespace simd { namespace detail
{
  //============================================================================
  // Work around for xlC
  //============================================================================
  template <class T, class N> struct make_array
  {
    typedef boost::array<T, N::value> type;
  };
} } }

namespace boost { namespace simd { namespace meta
{
  template<class N, class T>
  struct as_simd<T, tag::none_<N> >
  {
    typedef boost::array<T, N::value / sizeof(T)> type;
  };

  template<class T, class N>
  struct is_simd_specific < typename detail::make_array<T,N>::type
                          , tag::none_<boost::mpl::times< N
                                                        , boost::mpl::sizeof_<T>
                                                        >
                                      >
                          > : boost::mpl::true_
  {};

  template<class T, class N>
  struct extension_of<typename detail::make_array<T,N>::type, T, N>
  {
    typedef tag::none_<boost::mpl::times<N, boost::mpl::sizeof_<T> > > type;
  };
} } }

#endif

#endif
