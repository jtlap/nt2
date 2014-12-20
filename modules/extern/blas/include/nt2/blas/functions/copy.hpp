//==============================================================================
//         Copyright 2013 - 2014   Jean-Thierry Lapreste
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_BLAS_FUNCTIONS_BLAS_COPY_HPP_INCLUDED
#define NT2_BLAS_FUNCTIONS_BLAS_COPY_HPP_INCLUDED

/*!
  @file
  @brief Defines and implements copy function
**/

#include <nt2/include/functor.hpp>

namespace nt2 { namespace blas
{
  namespace tag
  {
    /// @brief Defines copy function tag
    struct copy_ : ext::abstract_<copy_>
    {
      /// INTERNAL ONLY
      typedef ext::abstract_<copy_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_copy_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site>
    BOOST_FORCEINLINE generic_dispatcher<tag::copy_, Site> dispatching_copy_(adl_helper, boost::dispatch::meta::unknown_<Site>, ...)
    {
      return generic_dispatcher<tag::copy_, Site>();
    }
    template<class... Args>
    struct impl_copy_;
  }

  /*!
    @brief copy values from vector x to vector y

    @code
    copy ( n, x, incx, y, incy )
    @endcode

    @param n number of elements to copy
    @param x first vector
    @param incx step through x
    @param y L-value to receive the result
    @param incy step through y

  **/
  NT2_FUNCTION_IMPLEMENTATION_TPL (tag::copy_, copy
                                  , (const A0&)(A1&)(const A2&)(A3&)(const A4&)
                                  , 5
                                  );

 } }

#endif

