//==============================================================================
//         Copyright 2013 - 2014   Jean-Thierry Lapreste
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_BLAS_DOTU_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_BLAS_DOTU_HPP_INCLUDED

/*!
  @file
  @brief Defines and implements blas_dotu function
**/

#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
    /// @brief Defines blas_dotu function tag
    struct blas_dotu_ : ext::abstract_<blas_dotu_>
    {
      /// INTERNAL ONLY
      typedef ext::abstract_<blas_dotu_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_blas_dotu_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site>
    BOOST_FORCEINLINE generic_dispatcher<tag::blas_dotu_, Site> dispatching_blas_dotu_(adl_helper, boost::dispatch::meta::unknown_<Site>, ...)
    {
      return generic_dispatcher<tag::blas_dotu_, Site>();
    }
    template<class... Args>
    struct impl_blas_dotu_;
  }

  /*!
    @brief dotu product of vector x and vector y

    computes  sum(mtimes(x, y))

    @code
    dotu (result, n, x, incx, y, incy )
    @endcode

    @param n number of elements to use
    @param x first vector (dimension at least (n-1) * |incx| + 1.)
    @param incx step through x (not to be zero)
    @param y second vector (dimension at least (n-1) * |incy| + 1.)
    @param incy step through y (not to be zero)
    @return the scalar product of x and y (conjugate of x is not taken in complex cases)

       When  working  backward  (incx < 0 or incy < 0), each routine starts at
       the end of the vector and moves backward, as follows:

            x(1-incx * (n-1)), x(1-incx * (n-2)), ..., x(1)

            y(1-incy * (n-1)), y(1-incy * (n-2)), ..., y(1)

    @alias dotuc
  **/
  NT2_FUNCTION_IMPLEMENTATION_TPL (tag::blas_dotu_, blas_dotu
                                  , (const A0&)(const A1&)(const A2&)(const A3&)(const A4&)
                                  , 5
                                  );

}

#endif

