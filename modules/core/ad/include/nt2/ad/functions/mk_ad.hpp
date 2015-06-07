//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_MK_MK_AD_HPP_INCLUDED
#define NT2_MK_MK_AD_HPP_INCLUDED

#include <nt2/include/functions/ad.hpp>
#include <nt2/include/functions/whereij.hpp>
#include <nt2/include/functions/is_equal.hpp>
#include <nt2/include/functions/splat.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/is_equal.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/sdk/meta/adapted_traits.hpp>
#include <boost/assert.hpp>
#include <nt2/table.hpp>


namespace nt2
{
  namespace ad
  {
    struct chooseline
    {
      chooseline(const std::size_t i) : i0(i-1){}

      template<class Sig> struct result;

      template<class This, class A0, class A1>
      struct result<This(A0,A1)>
      {
        typedef typename nt2::meta::strip<A0>::type a0_t;
        typedef typename nt2::meta::as_logical<a0_t>::type type;
      };

      template < class A0, class A1>
      typename nt2::meta::as_logical<A0>::type
      operator()(const A0&i, const A1&) const
      {
        return nt2::is_equal(i, nt2::splat<A0>(i0));
      }
    private :
      const std::size_t i0;
    };


    template < class T > BOOST_FORCEINLINE  valder<T>
    mk_ad(const T & x)
    {
      typedef typename valder<T>::v_t       v_t;
      typedef typename valder<T>::elem_t elem_t;
      BOOST_ASSERT_MSG(nt2::meta::is_floating_point<elem_t>::value, "x must be floating point based");
      return valder<T>(x);
    }

    template < class T1, class T2> valder<T1> BOOST_FORCEINLINE
    mk_ad(const T1& x, const T2 & d)
    {
      typedef typename valder<T1>::v_t       v_t;
      typedef typename valder<T1>::elem_t elem_t;
      BOOST_ASSERT_MSG(nt2::meta::is_floating_point<elem_t>::value, "x must be floating point based");
      return valder<T1>(x, d);
    }

    template < class T > BOOST_FORCEINLINE valder<T>
    mk_ad(const T & x, const std::size_t & i0)
    {
      typedef typename valder<T>::v_t       v_t;
      typedef typename valder<T>::elem_t elem_t;
      BOOST_ASSERT_MSG(nt2::meta::is_floating_point<elem_t>::value, "x must be floating point based");
      auto d = whereij(chooseline(i0), ones(size(x), meta::as_<elem_t>()), zeros(size(x), meta::as_<elem_t>()));
      return valder<T>(x, d);
    }
  }
}

#endif
