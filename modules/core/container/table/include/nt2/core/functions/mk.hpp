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

namespace nt2 { namespace tag
  {
   /*!
     @brief mk generic tag

     Represents the mk function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct mk_ : ext::elementwise_<mk_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<mk_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_mk_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
   template<class Site>
   BOOST_FORCEINLINE generic_dispatcher<tag::mk_, Site> dispatching_mk_(adl_helper, boost::dispatch::meta::unknown_<Site>, ...)
   {
     return generic_dispatcher<tag::mk_, Site>();
   }
   template<class... Args>
   struct impl_mk_;
  }
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

    @code
    auto r = mk<T>(of_size(n1, ..., np)(a1, ...,  an);
    auto r = mk(of_size(n1, ..., np)(a1, ...,  an);
    @endcode

    produces a table of size given by the first parameter such that r(i) == T(ai) if i <= n else T(0);
    (if T is not present T is decltype(a1).
    too many parameters are ignored,  too less are filled by zeros.

    mk() is invalid mk<T>() is a table < T >  of size (1, 0)

    @param a0, ..., an

    @return a value of the same type as the parameter
  **/
//   NT2_FUNCTION_IMPLEMENTATION(tag::mk_, mk, 1)
//   NT2_FUNCTION_IMPLEMENTATION(tag::mk_, mk, 2);

  template < class T, class R> void
  internal_typed_mk(std::size_t , R& )
  {
  }

  template < class T,  class R, class F> void
  internal_typed_mk(std::size_t i, R& r, const  F& f)
  {
    if (i <= numel(r))
    {
      r(i) = T(f);
    }
  }
  template < class T,  class R, class F, class ...Args> void
  internal_typed_mk(std::size_t i, R& r, const  F& f, const Args& ...args)
  {
    if (i <= numel(r))
    {
      r(i) = T(f);
      internal_typed_mk<T>(i+1, r, args...);
    }
  }

  template < class F, class ...Args>
  auto mk(const F& f, const Args&  ...args) -> table<F>
  {
    table<F> r(of_size(1, oneplus(sizeof...(args))));
    r(1) = f;
    internal_typed_mk<F>(2, r, args...);
    return std::move(r);
  }

  template < class T, class F, class S, class ...Args>
  auto mk(const F& f, const S& s, const Args&  ...args) -> table<T>
  {
    table<T> r(of_size(1, sizeof...(args)+2u));
    r(1) = T(f);
    r(2) = T(s);
    internal_typed_mk<T>(3, r, args...);
    return std::move(r);
  }
  template < class T, class F, class S>
  auto mk(const F& f, const S& s) -> table<T>
  {
    table<T> r(of_size(1, 2));
    r(1) = T(f);
    r(2) = T(s);
    return std::move(r);
  }

  template < class T, class F>
  auto mk(const F& f) -> table<T>
  {
    table<T> r(of_size(1, 1));
    r(1) = T(f);
    return std::move(r);
  }



}

#endif
