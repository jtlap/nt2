//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_MAGMA_GESVX_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_MAGMA_GESVX_HPP_INCLUDED

#if defined(NT2_USE_MAGMA)

#include <nt2/linalg/functions/gesvx.hpp>
#include <nt2/linalg/details/magma_buffer.hpp>
#include <nt2/linalg/functions/magma/dgerfs.hpp>
#include <nt2/sdk/magma/magma.hpp>

#include <nt2/dsl/functions/terminal.hpp>
#include <nt2/core/container/table/kind.hpp>
#include <nt2/linalg/details/utility/f77_wrapper.hpp>
#include <nt2/linalg/details/utility/workspace.hpp>

#include <nt2/include/functions/of_size.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/width.hpp>

#include <magma.h>
#include <cublas.h>

namespace nt2 { namespace ext
{

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::gesvx_,  nt2::tag::magma_<site>
                            , (A0)(S0)(A1)(S1)(A2)(S2)(A3)(site)
                            , ((container_< nt2::tag::table_,  double_<A0>, S0 >))  //A
                              ((container_< nt2::tag::table_,  double_<A1>, S1 >))  // B
                              ((container_< nt2::tag::table_,  double_<A2>, S2 >))  // X
                              (scalar_< floating_<A3> >)           //rcond
                            )
  {
     typedef nt2_la_int result_type;
     typedef double T;

     BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const& a1, A2& a2, A3& a3) const
     {
        result_type that,iter;
        nt2_la_int  n  = nt2::height(a0);
        nt2_la_int  nhrs = nt2::width(a1);
        nt2_la_int  ldb = n;
        char trans = 'N';
        a3 =1;

        nt2::container::table<T> copya(nt2::of_size(n,n));
        nt2::container::table<T> copyb(nt2::of_size(ldb,nhrs));
        copya = a0;
        copyb = a1;
        nt2::container::table<nt2_la_int> ipiv(nt2::of_size(n,1));

        details::magma_buffer<T>     rwork(n,1);
        details::magma_buffer<T>     dAf(n,n  , copya.raw());
        details::magma_buffer<T>     dA(n,n   , copya.raw());
        details::magma_buffer<T>     dB(n,nhrs, copyb.raw());
        details::magma_buffer<T>     dX(n,nhrs, copyb.raw());
        magma_dgesv_gpu( n, nhrs, dAf.raw(), n, ipiv.raw(),dX.raw(), ldb, &that);

        dgerfs_gpu(    trans
                           , n           , nhrs
                           , dA.raw()    , n
                           , dAf.raw()   , n
                           , ipiv.raw()
                           , dB.raw()    , ldb
                           , dX.raw()    , ldb
                           , rwork.raw() , &iter
                           , &that
                           );
        dX.raw( a2.raw() );



        return that;
     }
  };


  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::gesvx_,  nt2::tag::magma_<site>
                            , (A0)(S0)(A1)(S1)(A2)(S2)(A3)(site)
                            , ((container_< nt2::tag::table_,  single_<A0>, S0 >))  //A
                              ((container_< nt2::tag::table_,  single_<A1>, S1 >))  // B
                              ((container_< nt2::tag::table_,  single_<A2>, S2 >))  // X
                              (scalar_< floating_<A3> >)           //rcond
                            )
  {
     typedef nt2_la_int result_type;
     typedef float T;

     BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const& a1, A2& a2, A3& a3) const
     {
        result_type that,iter;
        nt2_la_int  n  = nt2::height(a0);
        nt2_la_int  nhrs = nt2::width(a1);
        nt2_la_int  ldb = n;
        char trans = 'N';
        a3 =1;

        nt2::container::table<T> copya(nt2::of_size(n,n));
        nt2::container::table<T> copyb(nt2::of_size(ldb,nhrs));
        copya = a0;
        copyb = a1;
        nt2::container::table<nt2_la_int> ipiv(nt2::of_size(n,1));

        details::magma_buffer<T>     rwork(n,1);
        details::magma_buffer<T>     dAf(n,n   , copya.raw());
        details::magma_buffer<T>     dA(n,n   , copya.raw());
        details::magma_buffer<T>     dB(n,nhrs, copyb.raw());
        details::magma_buffer<T>     dX(n,nhrs, copyb.raw());
        magma_sgesv_gpu( n, nhrs, dAf.raw(), n, ipiv.raw(),dX.raw(), ldb, &that);
        sgerfs_gpu(    trans
                           , n           , nhrs
                           , dA.raw()    , n
                           , dAf.raw()   , n
                           , ipiv.raw()
                           , dB.raw()    , ldb
                           , dX.raw()    , ldb
                           , rwork.raw() , &iter
                           , &that
                           );
        dX.raw( a2.raw() );

        return that;
     }
  };


  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::gesvx_,  nt2::tag::magma_<site>
                            , (A0)(S0)(A1)(S1)(A2)(S2)(A3)(site)
                            , ((container_< nt2::tag::table_,  complex_<double_<A0> >, S0 >))  //A
                              ((container_< nt2::tag::table_,  complex_<double_<A1> >, S1 >))  // B
                              ((container_< nt2::tag::table_,  complex_<double_<A2> >, S2 >))  // X
                              (scalar_< floating_<A3> >)           //rcond
                            )
  {
     typedef nt2_la_int result_type;
     typedef double T;
     typedef std::complex<T> cT;

     BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const& a1, A2& a2, A3& a3) const
     {
        result_type that,iter;
        nt2_la_int  n  = nt2::height(a0);
        nt2_la_int  nhrs = nt2::width(a1);
        nt2_la_int  ldb = n;
        char trans = 'N';
        a3 =1;

        nt2::container::table<cT> copya(nt2::of_size(n,n));
        nt2::container::table<cT> copyb(nt2::of_size(ldb,nhrs));
        copya = a0;
        copyb = a1;
        nt2::container::table<nt2_la_int> ipiv(nt2::of_size(n,1));

        details::magma_buffer<cT>     rwork(n,1);
        details::magma_buffer<cT>     dAf(n,n  , copya.raw());
        details::magma_buffer<cT>     dA(n,n   , copya.raw());
        details::magma_buffer<cT>     dB(n,nhrs, copyb.raw());
        details::magma_buffer<cT>     dX(n,nhrs, copyb.raw());
        magma_zgesv_gpu( n, nhrs, (cuDoubleComplex*)dAf.raw(), n, ipiv.raw()
                       , (cuDoubleComplex*)dX.raw(), ldb, &that);

        zgerfs_gpu(    trans
                           , n                             , nhrs
                           , (cuDoubleComplex*)dA.raw()    , n
                           , (cuDoubleComplex*)dAf.raw()   , n
                           , ipiv.raw()
                           , (cuDoubleComplex*)dB.raw()    , ldb
                           , (cuDoubleComplex*)dX.raw()    , ldb
                           , (cuDoubleComplex*)rwork.raw() , &iter
                           , &that
                           );
        dX.raw( a2.raw() );



        return that;
     }
  };


  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::gesvx_,  nt2::tag::magma_<site>
                            , (A0)(S0)(A1)(S1)(A2)(S2)(A3)(site)
                            , ((container_< nt2::tag::table_,  complex_<single_<A0> >, S0 >))  //A
                              ((container_< nt2::tag::table_,  complex_<single_<A1> >, S1 >))  // B
                              ((container_< nt2::tag::table_,  complex_<single_<A2> >, S2 >))  // X
                              (scalar_< floating_<A3> >)           //rcond
                            )
  {
     typedef nt2_la_int result_type;
     typedef float T;
     typedef std::complex<T> cT;

     BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const& a1, A2& a2, A3& a3) const
     {
        result_type that,iter;
        nt2_la_int  n  = nt2::height(a0);
        nt2_la_int  nhrs = nt2::width(a1);
        nt2_la_int  ldb = n;
        char trans = 'N';
        a3 =1;

        nt2::container::table<cT> copya(nt2::of_size(n,n));
        nt2::container::table<cT> copyb(nt2::of_size(ldb,nhrs));
        copya = a0;
        copyb = a1;
        nt2::container::table<nt2_la_int> ipiv(nt2::of_size(n,1));

        details::magma_buffer<cT>     rwork(n,1);
        details::magma_buffer<cT>     dAf(n,n  , copya.raw());
        details::magma_buffer<cT>     dA(n,n   , copya.raw());
        details::magma_buffer<cT>     dB(n,nhrs, copyb.raw());
        details::magma_buffer<cT>     dX(n,nhrs, copyb.raw());
        magma_cgesv_gpu( n, nhrs, (cuFloatComplex*)dAf.raw(), n, ipiv.raw()
                       , (cuFloatComplex*)dX.raw(), ldb, &that);

        cgerfs_gpu(    trans
                           , n                            , nhrs
                           , (cuFloatComplex*)dA.raw()    , n
                           , (cuFloatComplex*)dAf.raw()   , n
                           , ipiv.raw()
                           , (cuFloatComplex*)dB.raw()    , ldb
                           , (cuFloatComplex*)dX.raw()    , ldb
                           , (cuFloatComplex*)rwork.raw() , &iter
                           , &that
                           );
        dX.raw( a2.raw() );



        return that;
     }
  };
} }

#endif

#endif
