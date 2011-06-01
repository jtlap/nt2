/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_SIMD_EXTENSIONS_NONE_HPP_INCLUDED
#define NT2_SDK_SIMD_EXTENSIONS_NONE_HPP_INCLUDED

#include <nt2/sdk/simd/meta/as_simd.hpp>
#include <nt2/sdk/simd/meta/extension_of.hpp>
#include <nt2/sdk/simd/meta/is_simd_specific.hpp>

#if !defined(NT2_SIMD_DETECTED)
NT2_WARNING(No SIMD extensions detected)
#define NT2_NO_SIMD

#define NT2_SIMD_BYTES      8
#define NT2_SIMD_BITS       64
#define NT2_SIMD_STRING     "none"
#define NT2_SIMD_CARDINALS (1)(2)(4)(8)
#define NT2_SIMD_DEFAULT_EXTENSION ::nt2::tag::none_<boost::mpl::size_t<8> >
#define NT2_SIMD_DEFAULT_SITE ::nt2::tag::cpu_

#if !defined(NT2_SIMD_TYPES)
#include <nt2/sdk/simd/extensions/sse/types.hpp>
#endif

#include <nt2/sdk/functor/meta/hierarchy.hpp>
#include <nt2/sdk/simd/meta/is_simd_specific.hpp>
#include <nt2/sdk/simd/meta/as_simd.hpp>

#include <boost/array.hpp>
#include <boost/mpl/times.hpp>
#include <boost/mpl/sizeof.hpp>

namespace nt2 { namespace tag
{
  template<class N> struct none_ : cpu_
  {
    typedef cpu_ parent;
    typedef none_ type;
  };
} }

namespace nt2 { namespace detail
{
  //============================================================================
  // Work around for xlC
  //============================================================================
  template <class T, class N> struct make_array
  {
    typedef boost::array<T, N::value> type;
  };
} }

namespace nt2 { namespace meta
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
} }

#endif

#endif
