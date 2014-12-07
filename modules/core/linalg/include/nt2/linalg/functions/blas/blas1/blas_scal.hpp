//==============================================================================
//         Copyright 2013 - 2014   Jean-Thierry Lapresté
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_BLAS_BLAST_SCAL_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_BLAS_BLAST_SCAL_HPP_INCLUDED

#include <nt2/linalg/functions/blas_scal.hpp>
#include <nt2/linalg/details/blas/blas1.hpp>
#include <nt2/include/functions/numel.hpp>
#include <boost/dispatch/attributes.hpp>
#include <nt2/linalg/details/utility/f77_wrapper.hpp>
#include <nt2/core/container/table/table.hpp>

namespace nt2 { namespace ext
{

//---------------------------------------------Real-single------------------------------------------------//

  BOOST_DISPATCH_IMPLEMENT  ( blas_scal_, tag::cpu_
                            , (N)(A0)(A1)(S1)(A2)
                            , (scalar_<integer_<N>>)// n
                              (scalar_<single_<A0>>) //alpha
                              ((container_<nt2::tag::table_,  single_<A1>, S1 >)) //x
                              (scalar_<integer_<A2>>) //incx

                            )
  {
    typedef void result_type;

    BOOST_FORCEINLINE void operator()( const N& n
                                     , const A0& alpha, A1& x
                                     , const A2& incx) const
    {
      nt2_la_int in =n;
      nt2_la_int ix =incx;
      NT2_F77NAME(sscal) (&in, &alpha, x.raw(), &ix);
    }
  };

//---------------------------------------------Real-double------------------------------------------------//

  BOOST_DISPATCH_IMPLEMENT  ( blas_scal_, tag::cpu_
                            , (N)(A0)(A1)(S1)(A2)
                            , (scalar_<integer_<N>>)// n
                              (scalar_<double_<A0>>) //alpha
                              ((container_<nt2::tag::table_,  double_<A1>, S1 >)) //x
                              (scalar_<integer_<A2>>) //incx
                            )
  {
    typedef void result_type;

    BOOST_FORCEINLINE void operator()( const N& n
                                     , const A0& alpha, A1& x
                                     , const A2& incx) const
    {
      nt2_la_int in = n;
      nt2_la_int ix =incx;
      NT2_F77NAME(dscal) (&in, &alpha, x.raw(), &ix);
    }
  };

//---------------------------------------------Complex-single------------------------------------------------//

  BOOST_DISPATCH_IMPLEMENT  ( blas_scal_, tag::cpu_
                            , (N)(A0)(A1)(S1)(A2)
                            , (scalar_<integer_<N>>)// n
                              (scalar_<complex_<single_<A0>>>) //alpha
                              ((container_<nt2::tag::table_,  complex_<single_<A1>>, S1 >)) //x
                              (scalar_<integer_<A2>>) //incx

                            )
  {
    typedef void result_type;

    BOOST_FORCEINLINE void operator()( const N& n
                                     , const A0& alpha, A1& x
                                     , const A2& incx) const
    {
      nt2_la_int in =n;
      nt2_la_int ix =incx;
      NT2_F77NAME(cscal) (&in, &alpha, x.raw(), &ix);
    }
  };

//---------------------------------------------Complex-double------------------------------------------------//

  BOOST_DISPATCH_IMPLEMENT  ( blas_scal_, tag::cpu_
                            , (N)(A0)(A1)(S1)(A2)
                            , (scalar_<integer_<N>>)// n
                              (scalar_< complex_<double_<A0>>>) //alpha
                              ((container_<nt2::tag::table_,   complex_<double_<A1>>, S1 >)) //x
                              (scalar_<integer_<A2>>) //incx
                            )
  {
    typedef void result_type;

    BOOST_FORCEINLINE void operator()( const N& n
                                     , const A0& alpha, A1& x
                                     , const A2& incx) const
    {
      nt2_la_int in = n;
      nt2_la_int ix = incx;
      NT2_F77NAME(zscal) (&in, &alpha, x.raw(), &ix);
    }
  };
} }

#endif
