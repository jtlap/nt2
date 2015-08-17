//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_MK_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_MK_HPP_INCLUDED

#include <nt2/core/container/table/table.hpp>
#include <nt2/include/functions/of_size.hpp>
#include <nt2/core/functions/scalar/numel.hpp>
#include <nt2/core/utility/of_size.hpp>
#include <nt2/include/functions/oneplus.hpp>

namespace nt2
{
  /*!
    Make a table from values

    @par Semantic:

    For every parameters a1, ..., an

    @code
    auto r = mk(a1, ...,  an);
    @endcode

    produces a table of size (1, n) such that r(i) is T0(ai) where T0 is the type of a1

    @code
    auto r = mk<T>(a1, ...,  an);
    @endcode

    produces a table of size (1, n) such that r(i) is T(ai)

    mk() is invalid, mk<T>() is a table < T >  of size (1, 0)

    @param a0, ..., an

    @return a table containing the packed values
  **/

  namespace details
  {
    template < class T, class R> void
    BOOST_FORCEINLINE
    internal_typed_mk(std::size_t , R& ) { }

    template < class T,  class R, class F> void
    BOOST_FORCEINLINE
    internal_typed_mk(std::size_t i, R& r, const  F& f)
    {
      r(i) = T(f);
    }
    template < class T,  class R, class F, class ...Args> void
    BOOST_FORCEINLINE
    internal_typed_mk(std::size_t i, R& r, const  F& f, const Args& ...args)
    {
      r(i) = T(f);
      internal_typed_mk<T>(i+1, r, args...);
    }
  }

  template < class F, class ...Args>
  BOOST_FORCEINLINE
  table<F> mk(const F& f, const Args&  ...args)
  {
    table<F> r(of_size(1, oneplus(sizeof...(args))));
    r(1) = f;
    details::internal_typed_mk<F>(2, r, args...);
    return r;
  }

  template < class T, class F, class S, class ...Args>
  BOOST_FORCEINLINE
  table<T> mk(const F& f, const S& s, const Args&  ...args)
  {
    table<T> r(of_size(1, sizeof...(args)+2u));
    r(1) = T(f);
    r(2) = T(s);
    details::internal_typed_mk<T>(3, r, args...);
    return r;
  }
  template < class T, class F, class S>
  BOOST_FORCEINLINE
  table<T> mk(const F& f, const S& s)
  {
    table<T> r(of_size(1, 2));
    r(1) = T(f);
    r(2) = T(s);
    return r;
  }

  template < class T, class F>
  BOOST_FORCEINLINE
  table<T> mk(const F& f)
  {
    table<T> r(of_size(1, 1));
    r(1) = T(f);
    return r;
  }



}

#endif
