//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_UNIT_DETAILS_SMALLEST_TYPE_HPP_INCLUDED
#define NT2_SDK_UNIT_DETAILS_SMALLEST_TYPE_HPP_INCLUDED

#include <nt2/sdk/meta/primitive_of.hpp>
#include <nt2/sdk/complex/meta/as_complex.hpp>

namespace nt2 { namespace details
{
  /// INTERNAL ONLY
  /// Compute the smallest type between T and U
  template< class T, class U
          , class pT = typename meta::primitive_of<T>::type
          , class pU = typename meta::primitive_of<U>::type
          >
  struct smallest_impl
  {
    typedef T type;
  };

  template<class T, class U>
  struct smallest_impl<T, U, double, float>
  {
    typedef U type;
  };

  template<class T, class U>
  struct smallest_impl<T, U, long double, float>
  {
    typedef U type;
  };

  template<class T, class U>
  struct smallest_impl<T, U, long double, double>
  {
    typedef U type;
  };

  template<class T, class U, class X>
  struct  smallest_impl<boost::simd::details::soa_proxy<T, X>, U>
        : smallest_impl<T, U>
  {};

  template<class T, class U, class X>
  struct  smallest_impl<T, boost::simd::details::soa_proxy<U, X> >
        : smallest_impl<T, U>
  {};

  template<class T, class U, class X, class Y>
  struct  smallest_impl < boost::simd::details::soa_proxy<T, X>
                        , boost::simd::details::soa_proxy<U, Y>
                        >
        : smallest_impl<T, U>
  {};

  template<class T, class U>
  struct  smallest_impl<T, std::complex<U> >
        : smallest_impl< typename meta::as_complex<T>::type, U >
  {};

  template<class T, class U, class X>
  struct  smallest_impl < boost::simd::details::soa_proxy<T, X>
                        , std::complex<U>
                        >
        : smallest_impl< typename meta::as_complex<T>::type, U >
  {};

  template<class T, class U>
  struct  smallest_impl< nt2::dry<T>, U >
        : smallest_impl< T, U >
  {};

  template<class T, class U, class X>
  struct  smallest_impl< nt2::dry<T>, boost::simd::details::soa_proxy<U, X> >
        : smallest_impl< T, U >
  {};

  template<class T, class U>
  struct  smallest_impl< nt2::dry<T>, std::complex<U> >
        : smallest_impl< std::complex<T>, U >
  {};

  /// INTERNAL ONLY
  /// Cast a value toward the smallest type comaptible with T and U for
  /// proper ULP comparisons
  template<class T, class U>
  typename smallest_impl<T, U>::type
  smallest_a(T const& a, U const&)
  {
    return typename smallest_impl<T, U>::type(a);
  }

  /// INTERNAL ONLY
  /// Cast a value toward the smallest type comaptible with T and U for
  /// proper ULP comparisons
  template<class T, class U>
  typename smallest_impl<U, T>::type
  smallest_b(T const&, U const& b)
  {
    return typename smallest_impl<U, T>::type(b);
  }
} }

#endif
