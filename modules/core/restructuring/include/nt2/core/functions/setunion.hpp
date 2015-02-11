//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_SETUNION_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_SETUNION_HPP_INCLUDED


#include <nt2/include/functor.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/size.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief setunion generic tag

      Represents the setunion function in generic contexts.

      @par Models:
      Hierarchy
    **/
    struct setunion_ : ext::unspecified_<setunion_>
    {
      /// @brief Parent hierarchy
      typedef ext::unspecified_<setunion_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_setunion_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site>
    BOOST_FORCEINLINE generic_dispatcher<tag::setunion_, Site> dispatching_setunion_(adl_helper, boost::dispatch::meta::unknown_<Site>, ...)
    {
      return generic_dispatcher<tag::setunion_, Site>();
    }
    template<class... Args>
    struct impl_setunion_;
  }

  /*!
    Computes  elements of 2 tables with no repetitions as a column vector

    @par Semantic:

    For every tables expression

    @code
    auto r = setunion(a0, a1);
    @endcode

    returns the  datas of a0 and a1 with no repetitions as a column vector.
    The functor name is setunion and not union for obvious reasons

    @param a0
    éparam a1

    @return a column vector of size less or equal to min(numel(a0), numel(a1))
  **/

  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::setunion_       , setunion, 2)
}

namespace nt2 { namespace ext
{
  /// INTERNAL ONLY
  template<class Domain, int N, class Expr>
  struct  value_type<nt2::tag::setunion_,Domain,N,Expr>
        : meta::value_as<Expr,0>
  {};

  /// INTERNAL ONLY
  template<class Domain, int N, class Expr>
  struct  size_of<nt2::tag::setunion_,Domain,N,Expr>
    : meta::size_as<Expr,0>
  {};

} }

#endif
