//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_POLYNOM_FUNCTIONS_DECONV_HPP_INCLUDED
#define NT2_POLYNOM_FUNCTIONS_DECONV_HPP_INCLUDED
#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/size_as.hpp>
#include <nt2/sdk/meta/value_as.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/sdk/meta/tieable_hierarchy.hpp>
#include <nt2/core/container/dsl/value_type.hpp>

namespace nt2 { namespace tag
  {
   /*!
     @brief deconv generic tag

     Represents the deconv function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct deconv_ : ext::tieable_<deconv_>
    {
      /// @brief Parent hierarchy
      typedef ext::tieable_<deconv_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_deconv_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
   template<class Site>
   BOOST_FORCEINLINE generic_dispatcher<tag::deconv_, Site> dispatching_deconv_(adl_helper, boost::dispatch::meta::unknown_<Site>, ...)
   {
     return generic_dispatcher<tag::deconv_, Site>();
   }
   template<class... Args>
   struct impl_deconv_;
  }
  /*!
    Polynominial euclidian division

    @par Semantic:

    For every expressions representing polynomials a and b

    @code
    tie(q, r)= deconv(a, b);
    @endcode

    Produces 2 polynomials q and r such that (mathematically),
    a = bq+r and degree(r) < degree(b)

    @param a0

    @param a1

    @return a pair of polynomials
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::deconv_, deconv, 2)
}

#endif
