//==============================================================================
//         Copyright 2013 - 2014   Jean-Thierry Lapreste
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_BLAS_BLAS2_GER_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_BLAS_BLAS2_GER_HPP_INCLUDED

#include <nt2/linalg/functions/blas_ger.hpp>
#include <nt2/linalg/details/blas/blas2.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/linalg/details/utility/f77_wrapper.hpp>
#include <boost/dispatch/attributes.hpp>
#include <nt2/core/container/table/table.hpp>
#include <complex>

//These functions interchanges two vectors. Uses unrolled loops for increments equal to 1.

namespace nt2 { namespace ext
{

//---------------------------------------------Real-single------------------------------------------------//

  BOOST_DISPATCH_IMPLEMENT  ( blas_ger_, tag::cpu_
                            , (ALPHA)(X)(SX)(INCX)(Y)(SY)(INCY)(A)(SA)
                            , (scalar_<single_<ALPHA>>)// alpha
                              ((container_<nt2::tag::table_,  single_<X>, SX >)) //x
                              (scalar_<integer_<INCX>>)// incx
                              ((container_<nt2::tag::table_,  single_<Y>, SY >)) //y
                              (scalar_<integer_<INCY>>)// incy
                              ((container_<nt2::tag::table_,  single_<A>, SA >)) //y
                            )
  {
    typedef void result_type;

    BOOST_FORCEINLINE void operator()( const ALPHA& alpha
                                     , const X& x, const INCX & incx
                                     , const Y& y, const INCY & incy
                                     , A& a) const
    {
      nt2_la_int m = height(a);
      nt2_la_int lda = a.leading_size();
      nt2_la_int n = width(a);
      nt2_la_int ix = incx;
      nt2_la_int iy = incy;
      NT2_F77NAME(sger) (&m, &n, &alpha, x.raw(), &ix, y.raw(), &iy, a.raw(), &lda);
    }
  };

//---------------------------------------------Real-double------------------------------------------------//

  BOOST_DISPATCH_IMPLEMENT  ( blas_ger_, tag::cpu_
                            , (ALPHA)(X)(SX)(INCX)(Y)(SY)(INCY)(A)(SA)
                            , (scalar_<double_<ALPHA>>)// alpha
                              ((container_<nt2::tag::table_,  double_<X>, SX >)) //x
                              (scalar_<integer_<INCX>>)// incx
                              ((container_<nt2::tag::table_,  double_<Y>, SY >)) //y
                              (scalar_<integer_<INCY>>)// incy
                              ((container_<nt2::tag::table_,  double_<A>, SA >)) //y
                            )
  {
    typedef void result_type;

    BOOST_FORCEINLINE void operator()( const ALPHA& alpha
                                     , const X& x, const INCX & incx
                                     , const Y& y, const INCY & incy
                                     , A& a) const
    {
      nt2_la_int m = height(a);
      nt2_la_int lda = a.leading_size();
      nt2_la_int n = width(a);
      nt2_la_int ix = incx;
      nt2_la_int iy = incy;
      NT2_F77NAME(dger) (&m, &n, &alpha, x.raw(), &ix, y.raw(), &iy, a.raw(), &lda);
    }
  };

//---------------------------------------------Complex-single------------------------------------------------//

  BOOST_DISPATCH_IMPLEMENT  ( blas_ger_, tag::cpu_
                            , (ALPHA)(X)(SX)(INCX)(Y)(SY)(INCY)(A)(SA)
                            , (scalar_<complex_<single_<ALPHA>>>)// n
                              ((container_<nt2::tag::table_,  complex_<single_<X>>, SX >)) //x
                              (scalar_<integer_<INCX>>)// incx
                              ((container_<nt2::tag::table_,  complex_<single_<Y>>, SY >)) //y
                              (scalar_<integer_<INCY>>)// incy
                              ((container_<nt2::tag::table_,  complex_<single_<A>>, SA >)) //y
                            )
  {
    typedef void result_type;

    BOOST_FORCEINLINE void operator()( const ALPHA& alpha
                                     , const X& x, const INCX & incx
                                     , const Y& y, const INCY & incy
                                     , A& a) const
    {
      nt2_la_int m = height(a);
      nt2_la_int lda = a.leading_size();
      nt2_la_int n = width(a);
      nt2_la_int ix = incx;
      nt2_la_int iy = incy;
      NT2_F77NAME(cgerc)(&m, &n, &alpha, x.raw(), &ix, y.raw(), &iy, a.raw(), &lda);
    }
  };

//---------------------------------------------Complex-double------------------------------------------------//

  BOOST_DISPATCH_IMPLEMENT  ( blas_ger_, tag::cpu_
                            , (ALPHA)(X)(SX)(INCX)(Y)(SY)(INCY)(A)(SA)
                            , (scalar_<complex_<double_<ALPHA>>>)// n
                              ((container_<nt2::tag::table_,  complex_<double_<X>>, SX >)) //x
                              (scalar_<integer_<INCX>>)// incx
                              ((container_<nt2::tag::table_,  complex_<double_<Y>>, SY >)) //y
                              (scalar_<integer_<INCY>>)// incy
                              ((container_<nt2::tag::table_,  complex_<double_<A>>, SA >)) //y
                            )
  {
    typedef void result_type;

    BOOST_FORCEINLINE void operator()( const ALPHA& alpha
                                     , const X& x, const INCX & incx
                                     , const Y& y, const INCY & incy
                                     , A& a) const
    {
      nt2_la_int m = height(a);
      nt2_la_int lda = a.leading_size();
      nt2_la_int n = width(a);
      nt2_la_int ix = incx;
      nt2_la_int iy = incy;
      NT2_F77NAME(zgerc) (&m, &n, &alpha, x.raw(), &ix, y.raw(), &iy, a.raw(), &lda);
    }
  };

} }

#endif
