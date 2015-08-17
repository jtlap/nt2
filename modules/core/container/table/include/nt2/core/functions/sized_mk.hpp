//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_SIZED_MK_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_SIZED_MK_HPP_INCLUDED

#include <nt2/core/container/table/table.hpp>
#include <nt2/include/functions/of_size.hpp>
#include <nt2/core/functions/scalar/numel.hpp>
#include <nt2/core/utility/of_size.hpp>
#include <nt2/include/functions/oneplus.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/fnms.hpp>
#include <boost/assert.hpp>

namespace nt2
{
  /*!
    Make a table from values

    @par Semantic:

    For every parameters a1, ..., an

    @code
    auto r = sized_mk<T>(of_size(n1, ..., np), a1, ...,  an);
    @endcode

    or

    @code
    auto r = sized_mk(of_size(n1, ..., np), a1, ...,  an);
    @endcode

    produces a table of size given by the first parameter such that r(i) == T(ai);
    (if T is not present, T is decltype(a1)).
    too many parameters or too less assert.
    The parameters are taken in the correct visual order opposite to cons.

    @param size
    @param a0, ..., an

    @return a table containing the packed values
  **/

  namespace details
  {
    template < class SIZE, class T, class R> void
    BOOST_FORCEINLINE
    internal_typed_sized_mk(const SIZE&, std::size_t , R& )
    {
    }

    template < class T, class SIZE,  class R, class F> void
    BOOST_FORCEINLINE
    internal_typed_sized_mk(const SIZE&, std::size_t j, R& r, const  F& f)
    {
      r(++j) = T(f);
    }
    template <class T, class SIZE,  class R, class F, class ...Args> void
    BOOST_FORCEINLINE
    internal_typed_sized_mk(const SIZE& siz, std::size_t j, R& r, const  F& f
                           , const Args& ...args)
    {
      std::size_t h = boost::fusion::at_c<0>(siz);
      std::size_t w = boost::fusion::at_c<1>(siz);
      std::size_t hw = h*w;
      std::size_t k = j/hw;
      std::size_t l = oneplus(j%w);
      std::size_t c = oneplus(fnms(k,hw,j)/w);
      r(c,l,++k) = T(f);
      internal_typed_sized_mk<T>(siz, ++j, r, args...);
    }
  }

  template < class SIZE, class F, class ...Args>
  BOOST_FORCEINLINE
  table<F> sized_mk(const SIZE& siz, const F& f, const Args&  ...args)
  {
    table<F> r(siz);
    r(1) = f;
    details::internal_typed_sized_mk<F>(siz, 1, r, args...);
    return std::move(r);
  }

  template < class T, class SIZE, class F, class S, class ...Args>
  BOOST_FORCEINLINE
  table<T> sized_mk(const SIZE& siz, const F& f, const S& s, const Args& ...args)
  {
    table<T> r(siz);
    BOOST_ASSERT_MSG(numel(r)>=(sizeof...(args)+2u), "too much initializers");
    BOOST_ASSERT_MSG(numel(r)<=(sizeof...(args)+2u), "not enough initializers");
    r(1) = T(f);
    r(1+height(r)) = T(s);
    details::internal_typed_sized_mk<T>(siz, 2, r, args...);
    return std::move(r);
  }

  template < class T, class SIZE, class F, class S>
  BOOST_FORCEINLINE
  table<T> sized_mk(const SIZE& siz, const F& f, const S& s)
  {
    table<T> r(siz);
    BOOST_ASSERT_MSG(numel(r) <= 2u, "not enough initializers");
    r(1) = T(f);
    r(2) = T(s);
    return std::move(r);
  }

  template < class T, class SIZE, class F>
  BOOST_FORCEINLINE
  table<T> sized_mk(const SIZE& siz, const F& f)
  {
    table<T> r(siz);
    BOOST_ASSERT_MSG(numel(r) <= 1u, "not enough initializers");
    r(1) = T(f);
    return std::move(r);
  }

  template < class T, class SIZE>
  BOOST_FORCEINLINE
  table<T> sized_mk(const SIZE& siz)
  {
    table<T> r(siz);
    return std::move(r);
  }


}

#endif
