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
#include <boost/assert.hpp>

namespace nt2 { namespace tag
  {
   /*!
     @brief sized_mk generic tag

     Represents the sized_mk function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct sized_mk_ : ext::elementwise_<sized_mk_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<sized_mk_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_sized_mk_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
   template<class Site>
   BOOST_FORCEINLINE generic_dispatcher<tag::sized_mk_, Site> dispatching_sized_mk_(adl_helper, boost::dispatch::meta::unknown_<Site>, ...)
   {
     return generic_dispatcher<tag::sized_mk_, Site>();
   }
   template<class... Args>
   struct impl_sized_mk_;
  }
  /*!
    Make a table from values

    @par Semantic:

    For every parameters a1, ..., an

    @code
    auto r = sized_mk(a1, ...,  an);
    @endcode

    produces a table of size (1, n) such that r(i) is T0(ai) where T0 is the type of a1

    @code
    auto r = sized_mk<T>(a1, ...,  an);
    @endcode

    produces a table of size (1, n) such that r(i) is T(ai)

    @code
    auto r = sized_mk<T>(of_size(n1, ..., np), a1, ...,  an);
    auto r = sized_mk(of_size(n1, ..., np), a1, ...,  an);
    @endcode

    produces a table of size given by the first parameter such that r(i) == T(ai);
    (if T is not present T is decltype(a1)).
    too many parameters or too less assert.
    The parameters are taken in the correct visual order opposite to cons.
    sized_mk() is invalid sized_mk<T>() is a table < T >  of size (1, 0)

    @param size
    @param a0, ..., an

    @return a table
  **/

  template < class SIZE, class T, class R> void
  internal_typed_sized_mk(const SIZE&, std::size_t , R& )
  {
  }

  template < class T, class SIZE,  class R, class F> void
  internal_typed_sized_mk(const SIZE&, std::size_t i, R& r, const  F& f)
  {
    if (i <= numel(r))
    {
      r(i) = T(f);
    }
  }
  template <class T, class SIZE,  class R, class F, class ...Args> void
  internal_typed_sized_mk(const SIZE& siz, std::size_t i, R& r, const  F& f, const Args& ...args)
  {
    if (i <= numel(r))
    {
      std::size_t k = (i-1) / (boost::fusion::at_c<1>(siz)*boost::fusion::at_c<0>(siz))+1;
      std::size_t l = (i-1) % (boost::fusion::at_c<1>(siz))+1;
      std::size_t t = i-(k-1)*(boost::fusion::at_c<1>(siz)*boost::fusion::at_c<0>(siz));
      std::size_t c = (t-1) / (boost::fusion::at_c<1>(siz))+1;
      r(c, l, k) = T(f);
      internal_typed_sized_mk<T>(siz, i+1, r, args...);
    }
  }

  template < class SIZE, class F, class ...Args>
  auto sized_mk(const SIZE& siz, const F& f, const Args&  ...args) -> table<F>
  {
    table<F> r(siz);
    r(1) = f;
    internal_typed_sized_mk<F>(siz, 2, r, args...);
    return std::move(r);
  }

  template < class T, class SIZE, class F, class S, class ...Args>
  auto sized_mk(const SIZE& siz, const F& f, const S& s, const Args&  ...args) -> table<T>
  {
    table<T> r(siz);
    std::cout << numel(r) <<  "   " <<  (sizeof...(args)+2u) << std::endl;
    BOOST_ASSERT_MSG(numel(r) >= (sizeof...(args)+2u), "too much initializers");
    BOOST_ASSERT_MSG(numel(r) <= (sizeof...(args)+2u), "not enough initializers");
    r(1) = T(f);
    r(1+height(r)) = T(s);
    internal_typed_sized_mk<T>(siz, 3, r, args...);
    return std::move(r);
  }
  template < class T, class SIZE, class F, class S>
  auto sized_mk(const SIZE& siz, const F& f, const S& s) -> table<T>
  {
    table<T> r(siz);
    BOOST_ASSERT_MSG(numel(r) <= 2u, "not enough initializers");
    r(1) = T(f);
    r(2) = T(s);
    return std::move(r);
  }

  template < class T, class SIZE, class F>
  auto sized_mk(const SIZE& siz, const F& f) -> table<T>
  {
    table<T> r(siz);
    BOOST_ASSERT_MSG(numel(r) <= 1u, "not enough initializers");
    r(1) = T(f);
    return std::move(r);
  }



}

#endif
