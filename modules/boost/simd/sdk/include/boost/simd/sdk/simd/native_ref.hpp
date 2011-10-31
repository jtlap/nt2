//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_SIMD_NATIVE_REF_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_NATIVE_REF_HPP_INCLUDED

#include <boost/simd/sdk/simd/native.hpp>
#include <boost/fusion/include/size.hpp>
#include <boost/fusion/include/at_c.hpp>
#include <boost/utility/enable_if.hpp>

namespace boost { namespace simd
{
  namespace details
  {
    template<int N, class T, class Dummy>
    typename boost::lazy_enable_if_c<
      (N < boost::fusion::result_of::size<T>::type::value)
    , boost::fusion::result_of::at_c<T, N>
    >::type
    safe_at_c(T& t, Dummy& dummy)
    {
      return boost::fusion::at_c<N>(t);
    }
  
    template<int N, class T>
    typename boost::disable_if_c<
      (N < boost::fusion::result_of::size<T>::type::value)
    , Dummy&
    >::type
    safe_at_c(T&, Dummy& dummy)
    {
      return dummy;
    }
  }
    
  template<class T, class X, int N>
  struct native_ref_impl;
   
#define M1(z, n, t) T& a##n;
#define M2(z, n, t) a##n(details::safe_at_c<n>(seq, dummy))
#define M3(z, n, t) a##n = other.a##n;
   
#define M0(z, n, t)                                                        \
template<class T, class X>                                                 \
struct native_ref_impl<T, X, n>                                            \
{                                                                          \
  template<class Seq>                                                      \
  native_ref_impl(Seq& seq)                                                \
    : BOOST_PP_ENUM(n, M2, ~)                                              \
  {                                                                        \
  }                                                                        \
                                                                           \
  native_ref_impl& operator=(native_ref_impl const& other)                 \
  {                                                                        \
    BOOST_PP_REPEAT(n, M3, ~)                                              \
    return *this;                                                          \
  }                                                                        \
                                                                           \
  BOOST_PP_REPEAT(n, M1, ~);                                               \
  T dummy;                                                                 \
};                                                                         \
/**/
BOOST_SIMD_REPEAT_POWER_OF_2(M0, ~)
#undef M3
#undef M2
#undef M1
#undef M0

  template<class Scalar, class Extension>
  struct native_ref : native_ref_impl<Scalar, Extension, meta::cardinal_of< native<Scalar, Extension> >::value>
  {
    template<class Seq>
    native_ref(Seq& seq) : native_ref_impl(seq) {}

    template<class Seq>
    native_ref(Seq const& seq) : native_ref_impl(seq) {}
  
    typedef Extension                                       extension_type;
    typedef typename meta::as_simd<Scalar, Extension>::type native_type;

    ////////////////////////////////////////////////////////////////////////////
    // native_ref<S,E> models FusionRandomAccessSequence
    ////////////////////////////////////////////////////////////////////////////
    typedef Scalar                                          value_type;
    typedef value_type&                                     reference;
    typedef value_type const&                               const_reference;
    typedef std::size_t                                     size_type;

    template<class U> struct rebind
    {
      typedef native_ref<U, extension_type> type;
    };

    ////////////////////////////////////////////////////////////////////////////
    // vector size
    ////////////////////////////////////////////////////////////////////////////
    static const std::size_t static_size = native<Scalar, Extension>::static_size;

    ////////////////////////////////////////////////////////////////////////////
    // Array like interface
    ////////////////////////////////////////////////////////////////////////////
    static BOOST_DISPATCH_FORCE_INLINE
    std::size_t size() { return static_size; }

    static BOOST_DISPATCH_FORCE_INLINE
    bool empty() { return false; }
  };
  
} }

#endif
