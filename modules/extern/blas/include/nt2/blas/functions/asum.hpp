//==============================================================================
//         Copyright 2013 - 2014   Jean-Thierry Lapreste
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_BLAS_FUNCTIONS_BLAS_ASUM_HPP_INCLUDED
#define NT2_BLAS_FUNCTIONS_BLAS_ASUM_HPP_INCLUDED

/*!
  @file
  @brief Defines and implements asum function
**/

#include <nt2/include/functor.hpp>

namespace nt2 { namespace blas
{
  namespace tag
  {
    /// @brief Defines asum function tag
    struct asum_ : ext::abstract_<asum_>
    {
      /// INTERNAL ONLY
      typedef ext::abstract_<asum_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_asum_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site>
    BOOST_FORCEINLINE generic_dispatcher<tag::asum_, Site> dispatching_asum_(adl_helper, boost::dispatch::meta::unknown_<Site>, ...)
    {
      return generic_dispatcher<tag::asum_, Site>();
    }
    template<class... Args>
    struct impl_asum_;
  }

  /*!
    @brief asum sum of the manhattan moduli of x

    @code
    asum ( n, x, incx)
    @endcode

    @param n number of elements to use
    @param x input vector
    @param incx step through x
    return sum(abs(real(x(_(1, incx, (n-1)*incx+1))))+abs(imag(x(_(1, incx, (n-1)*incx+1)))))

    When working backward (incx < 0), each routine starts at the end of the
    vector and moves backward, as follows:

            x(1-incx * (n-1)), x(1-incx * (n-2)), ..., x(1)
  **/
  NT2_FUNCTION_IMPLEMENTATION_TPL (tag::asum_, asum
                                  , (const A0&)(const A1&)(const A2&)
                                  , 3
                                  );


 } }

#endif

