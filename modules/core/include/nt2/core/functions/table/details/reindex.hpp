//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_DETAILS_REINDEX_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_DETAILS_REINDEX_HPP_INCLUDED

#include <boost/fusion/include/at.hpp>
#include <boost/simd/sdk/meta/as_arithmetic.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <nt2/include/functions/relative_index.hpp>
#include <nt2/include/constants/one.hpp>

namespace nt2 { namespace details
{
  /// INTERNAL ONLY
  /// This helper functor forward calls to relative_index
  /// inside a fusion::transform
  struct reindex
  {
    template<typename T> struct result;

    template<typename T> struct result<reindex(T)>
      : meta::
        call< nt2::tag::relative_index_
            ( typename  boost::fusion::result_of::
                        at_c< typename boost::remove_reference<T>::type const
                            , 0
                            >::type
            , typename  boost::fusion::result_of::
                        at_c< typename boost::remove_reference<T>::type const
                            , 1
                            >::type
            , typename  boost::fusion::result_of::
                        at_c< typename boost::remove_reference<T>::type const
                            , 2
                            >::type
            , typename  boost::fusion::result_of::
                        at_c< typename boost::remove_reference<T>::type const
                            , 3
                            >::type
            , typename  boost::fusion::result_of::
                        at_c< typename boost::remove_reference<T>::type const
                            , 4
                            >::type
            )
            >
    {};

    template <typename T>
    BOOST_FORCEINLINE typename result<reindex(T const&)>::type
    operator()(T const& t) const
    {
      return nt2::relative_index( boost::fusion::at_c<0>(t)
                                , boost::fusion::at_c<1>(t)
                                , boost::fusion::at_c<2>(t)
                                , boost::fusion::at_c<3>(t)
                                , boost::fusion::at_c<4>(t)
                                );
    }
  };

  /// INTERNAL ONLY
  /// Turn SIMD values or targets into integer SIMD, use std::size_t for scalars
  template<class T>
  struct as_integer_target
  {
    typedef std::size_t type;
  };

  template<class T, class X>
  struct as_integer_target< boost::simd::native<T, X> >
  {
    typedef typename boost::simd::meta::
            as_arithmetic< boost::simd::native<T, X> >::type          arith_t;
    typedef typename boost::dispatch::meta::as_integer<arith_t>::type type;
  };

  template<class T>
  struct  as_integer_target< boost::dispatch::meta::as_<T> >
        : as_integer_target<T>
  {};

  template<long M, class T, std::size_t N>
  boost::array<T, M> one_extend( boost::array<T, N> const& in )
  {
    boost::array<T, M> array;
    std::size_t i=0;
    for(; i!=N; ++i)
      array[i] = in[i];
    for(; i!=M; ++i)
      array[i] = One<T>();
    return array;
  }
} }

#endif
