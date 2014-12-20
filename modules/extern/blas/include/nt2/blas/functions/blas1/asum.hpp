//==============================================================================
//         Copyright 2013 - 2014   Jean-Thierry Lapreste
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_BLAS_FUNCTIONS_BLAS1_ASUM_HPP_INCLUDED
#define NT2_BLAS_FUNCTIONS_BLAS1_ASUM_HPP_INCLUDED

#include <nt2/blas/functions/asum.hpp>
#include <nt2/blas/details/blas1.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/blas/details/wrapper.hpp>
#include <boost/dispatch/attributes.hpp>
#include <nt2/core/container/table/table.hpp>


namespace nt2 { namespace blas { namespace ext
{

//---------------------------------------------Real-single------------------------------------------------//

  BOOST_DISPATCH_IMPLEMENT  ( asum_, tag::cpu_
                            , (N)(A0)(S0)(INCX)
                            , (scalar_<integer_<N>>)// n
                              ((container_<nt2::tag::table_,  single_<A0>, S0 >)) //x
                              (scalar_<integer_<INCX>>)// incx
                            )
  {
    typedef float result_type;

    BOOST_FORCEINLINE result_type operator()( const N& n
                                            , const A0& x, const INCX & incx) const
     {
       nt2_la_int in = n;
       nt2_la_int ix= incx;
       return NT2_F77NAME(sasum) (&in, x.data(), &ix);
     }
  };

//---------------------------------------------Real-double------------------------------------------------//

  BOOST_DISPATCH_IMPLEMENT  ( asum_, tag::cpu_
                            , (N)(A0)(S0)(INCX)
                            , (scalar_<integer_<N>>)// n
                              ((container_<nt2::tag::table_,  double_<A0>, S0 >)) //x
                              (scalar_<integer_<INCX>>)// incx
                            )
  {
    typedef double result_type;

    BOOST_FORCEINLINE result_type operator()( const N& n
                                     , const A0& x, const INCX & incx) const
    {
      nt2_la_int in = n;
      nt2_la_int ix= incx;
      return NT2_F77NAME(dasum) (&in, x.data(), &ix);
    }
  };

//---------------------------------------------Complex-single------------------------------------------------//

  BOOST_DISPATCH_IMPLEMENT  ( asum_, tag::cpu_
                            , (N)(A0)(S0)(INCX)
                            , (scalar_<integer_<N>>)// n
                              ((container_<nt2::tag::table_,  complex_<single_<A0>>, S0 >)) //x
                              (scalar_<integer_<INCX>>)// incx
                            )
  {
    typedef float result_type;

    BOOST_FORCEINLINE result_type operator()( const N& n
                                     , const A0& x, const INCX & incx) const
     {
       nt2_la_int in = n;
       nt2_la_int ix= incx;
       return NT2_F77NAME(scasum) (&in, x.data(), &ix);
     }
  };

//---------------------------------------------Complex-double------------------------------------------------//

  BOOST_DISPATCH_IMPLEMENT  ( asum_, tag::cpu_
                            , (N)(A0)(S0)(INCX)
                            , (scalar_<integer_<N>>)// n
                              ((container_<nt2::tag::table_,  complex_<double_<A0>>, S0 >)) //x
                              (scalar_<integer_<INCX>>)// incx
                            )
  {
    typedef double result_type;

    BOOST_FORCEINLINE result_type operator()( const N& n
                                     , const A0& x, const INCX & incx) const
    {
      nt2_la_int in = n;
      nt2_la_int ix= incx;
      return NT2_F77NAME(dzasum) (&in, x.data(), &ix);
    }
  };

}  } }

#endif
