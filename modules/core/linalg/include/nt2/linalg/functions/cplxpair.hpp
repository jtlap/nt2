//==============================================================================
//         Copyright 2015   J.T. Lapresté
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_CPLXPAIR_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_CPLXPAIR_HPP_INCLUDED
#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/size_as.hpp>
#include <nt2/sdk/meta/value_as.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/sdk/meta/tieable_hierarchy.hpp>
#include <nt2/core/container/dsl/value_type.hpp>
#include <nt2/sdk/complex/meta/as_complex.hpp>

namespace nt2 { namespace tag
  {
   /*!
     @brief cplxpair generic tag

     Represents the cplxpair function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct cplxpair_ : ext::unspecified_<cplxpair_>
    {
      /// @brief Parent hierarchy
      typedef ext::unspecified_<cplxpair_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY(
        dispatching_cplxpair_( ext::adl_helper(), static_cast<Args&&>(args)... )
      )
    };
  }
  namespace ext
  {
   template<class Site>
   BOOST_FORCEINLINE generic_dispatcher<tag::cplxpair_, Site>
   dispatching_cplxpair_(adl_helper, boost::dispatch::meta::unknown_<Site>, ...)
   {
     return generic_dispatcher<tag::cplxpair_, Site>();
   }
   template<class... Args>
   struct impl_cplxpair_;
  }
  /*!
    Computes the cplxpair reordering of a table composed of real or conjugate pairs of
    elements.

    The conjugate pairs are ordered by increasing real part.
    Within a pair, the element with negative imaginary part comes first.
    The purely real values are returned following all the complex pairs.
    The complex conjugate pairs are forced to be exact complex conjugates.
    A default tolerance of 100*eps relative to abs(x(i)) determines which
    numbers are real and which elements are paired complex conjugates.

    @par Semantic:

    For every table x

    @code
    auto r = cplxpair(x{, tol}{, dim});
    @endcode

    @param x table of type_t elements to be sorted
    @param tol optional default to 100*Eps<type_t>()
    @param dim dimension to sort along default to first non-singleton.

    @return a table of type_t elements
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::cplxpair_, cplxpair, 1)
  /// @overload
  NT2_FUNCTION_IMPLEMENTATION(tag::cplxpair_, cplxpair, 2)
  /// @overload
  NT2_FUNCTION_IMPLEMENTATION(tag::cplxpair_, cplxpair, 3)

}

 namespace nt2 { namespace ext
{
  template<class Domain, int N, class Expr>
  struct  size_of<tag::cplxpair_,Domain,N,Expr>
    : meta::size_as<Expr,0>{};

  template<class Domain, int N, class Expr>
  struct  value_type<tag::cplxpair_,Domain,N,Expr>
    : meta::value_as<Expr,0>{};
} }
#endif
