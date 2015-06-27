//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_MODULES_CORE_NUMERICAL_DERIVATIVES_UNIT_DETAILS_CHOOSEDIAGS_HPP_INCLUDED
#define NT2_MODULES_CORE_NUMERICAL_DERIVATIVES_UNIT_DETAILS_CHOOSEDIAGS_HPP_INCLUDED
#include <nt2/include/functions/is_equal.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/sdk/meta/as_logical.hpp>

namespace nt2 { namespace details
{
  struct choosediags
  {
    template<class Sig> struct result;

    template<class This, class A0, class A1, class A2>
    struct result<This(A0,A1,A2)>
    {
      typedef typename nt2::meta::strip<A0>::type a0_t;
      typedef typename nt2::meta::as_logical<a0_t>::type type;
    };

    template < class A0, class A1, class A2>
    typename nt2::meta::as_logical<A0>::type
    operator()(const A0&i, const A1&j, const A2& ) const
    {
      return nt2::eq(i, j);
    }
  };
 struct choosediag
  {
    template<class Sig> struct result;

    template<class This, class A0, class A1>
    struct result<This(A0,A1)>
    {
      typedef typename nt2::meta::strip<A0>::type a0_t;
      typedef typename nt2::meta::as_logical<a0_t>::type type;
    };

    template < class A0, class A1>
    typename nt2::meta::as_logical<A0>::type
    operator()(const A0&i, const A1&j) const
    {
      return nt2::eq(i, j);
    }
  };
   struct chooserows
  {
    template<class Sig> struct result;

    template<class This, class A0, class A1, class A2>
    struct result<This(A0,A1,A2)>
    {
      typedef typename nt2::meta::strip<A0>::type a0_t;
      typedef typename nt2::meta::as_logical<a0_t>::type type;
    };

    template < class A0, class A1, class A2>
    typename nt2::meta::as_logical<A0>::type
    operator()(const A0&i, const A1&, const A2&k ) const
    {
      return nt2::eq(i, k);
    }
  };


} }


#endif

