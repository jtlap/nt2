//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_SIMD_DETAILS_MAKE_SOA_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_DETAILS_MAKE_SOA_HPP_INCLUDED

#include <boost/simd/sdk/simd/meta/vector_of.hpp>
#include <boost/simd/sdk/meta/cardinal_as.hpp>
#include <boost/dispatch/meta/strip.hpp>
#include <boost/fusion/include/as_vector.hpp>
#include <boost/mpl/max.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/size_t.hpp>

namespace boost { namespace simd
{
  namespace details
  {
    // Compute maximum cardinal in a sequence
    template<class T,class X>
    struct  max_cardinal_
          : mpl::fold < typename boost::fusion::result_of::as_vector<T>::type
                      , boost::mpl::size_t<1>
                      , mpl::max< mpl::_1, meta::cardinal_as<mpl::_2,X> >
                      >
    {};

    // Build the sequence of proper native
    template<class C> struct vector_of_
    {
      template<class Sig>
      struct result;

      template<class This, class U>
      struct result<This(U)>
      {
        typedef typename dispatch::meta::strip<U>::type sU;
        typedef typename meta::vector_of<sU, C::type::value>::type type;
      };
    };

    // Wrappy wrapper
    template<class T, class X>
    struct make_soa : vector_of_< details::max_cardinal_<T,X> >
    {};
  }
} }

#endif
