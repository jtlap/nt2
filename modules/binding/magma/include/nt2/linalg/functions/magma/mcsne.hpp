//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2014   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_MAGMA_MCSNE_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_MAGMA_MCSNE_HPP_INCLUDED

#if defined(NT2_USE_MAGMA)

#include <nt2/linalg/functions/mcsne.hpp>
#include <nt2/sdk/magma/magma.hpp>
#include <nt2/linalg/details/magma_buffer.hpp>
#include <nt2/include/functions/lange.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/of_size.hpp>
#include <nt2/include/functions/trsm.hpp>
#include <nt2/include/functions/qr.hpp>
#include <nt2/include/functions/linsolve.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/transpose.hpp>
#include <nt2/include/functions/maximum.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/cast.hpp>
#include <nt2/linalg/details/utility/f77_wrapper.hpp>
#include <nt2/include/constants/eps.hpp>
#include <boost/dispatch/meta/downgrade.hpp>
#include <nt2/sdk/meta/as_real.hpp>

#include <nt2/core/container/table/table.hpp>
#include <magma.h>


 namespace nt2{ namespace ext
 {
   BOOST_DISPATCH_IMPLEMENT  ( mcsne_, nt2::tag::magma_<site>
                             , (A0)(A1)(site)
                             , ((ast_<A0, nt2::container::domain>))
                               ((ast_<A1, nt2::container::domain>))
                             )
   {
     typedef typename A0::value_type                   type_t;
     typedef typename nt2::container::table<type_t>    t_t;
     typedef  t_t                                      result_type;

      BOOST_FORCEINLINE result_type operator()(A0 const& a, A1 const& b) const
     {
       nt2_la_int lda = a.leading_size();
       nt2_la_int m = nt2::height(a);
       nt2_la_int na = nt2::width(a);
       nt2_la_int nhrs = nt2::width(b);
       nt2_la_int ldb = nt2::height(b);
       nt2_la_int nb = magma_get_dgeqrf_nb(m);
       nt2_la_int lwkopt = (2*std::min(m,na)+ ((na+31)/32)*32)*nb;
       nt2_la_int info;
       double one = 1;
       double negone = -1;

       t_t x(nt2::of_size(ldb,nhrs));
       nt2::container::table<float> tau(nt2::of_size(std::min(m,na),1));

       details::magma_buffer<double>      dA(m,na,a.data() );
       details::magma_buffer<double>      dB(ldb,nhrs,b.data() );
       details::magma_buffer<double>      dX(ldb,nhrs);
       details::magma_buffer<double>      dE(ldb,nhrs);
       details::magma_buffer<double>      temp(ldb,nhrs);
       details::magma_buffer<float>       dSR(m,na);
       details::magma_buffer<float>       dSX(ldb,nhrs);
       details::magma_buffer<float>       dT(lwkopt,nhrs);

       double eps = boost::simd::Eps<double>();
       double anrm = magmablas_dlange(MagmaInfNorm, m, na, dA.data(), m, dE.data() );
       double cte = anrm*eps*nt2::sqrt( type_t(na));
       double xnrm, rnrm;

       magmablas_dlag2s(m,na,dA.data(),m,dSR.data(),m, &info);

       magmablas_dlag2s(ldb,nhrs,dB.data(),ldb,dSX.data(),ldb,&info);

       magmablas_sgemv( MagmaTrans, m, na, one, dSR.data(), m, dSX.data(), one, 0, dSX.data(), one );

       magma_sgeqrf2_gpu( m, na, dSR.data(), m, tau.data(), &info );

       magmablas_strsm(MagmaLeft,MagmaUpper,MagmaTrans,MagmaNonUnit,na,nhrs,(float)one,dSR.data(),m,dSX.data(), na);

       magmablas_strsm(MagmaLeft,MagmaUpper,MagmaNoTrans,MagmaNonUnit,na,nhrs,(float)one,dSR.data(),m,dSX.data(), na);

       magmablas_slag2d(ldb,nhrs,dSX.data(),ldb,dX.data(),ldb,&info);

       magmablas_dlacpy(MagmaFull, ldb, nhrs, dB.data(), ldb, dE.data(), ldb);

       magmablas_dgemv( MagmaNoTrans, lda, na, negone, dA.data(), lda, dX.data(), one, one, dE.data(), one );

       for(size_t i = 1; i<=10;++i)
       {
         magmablas_dgemv( MagmaTrans, lda, na, one, dA.data(), lda, dE.data(), one, 0, temp.data(), one );
         magmablas_dlag2s(ldb,nhrs,temp.data(),ldb,dSX.data(),ldb,&info);

         magmablas_strsm(MagmaLeft,MagmaUpper,MagmaTrans,MagmaNonUnit,na,nhrs,(float)one,dSR.data(),m,dSX.data(), na);

         magmablas_strsm(MagmaLeft,MagmaUpper,MagmaNoTrans,MagmaNonUnit,na,nhrs,(float)one,dSR.data(),m,dSX.data(), na);

         magmablas_slag2d(na,nhrs,dSX.data(),ldb,dE.data(),ldb,&info);

         dE.raw(x.data());
         rnrm = nt2::maximum(nt2::abs(x(_)));

         magmablas_dgeadd(na,nhrs,one,dE.data(),ldb,dX.data(),ldb);

         dX.raw(x.data());
         xnrm = nt2::maximum(nt2::abs(x(_)));

         magmablas_dlacpy(MagmaFull, ldb, nhrs, dB.data(), ldb, dE.data(), ldb);
         magmablas_dgemv( MagmaNoTrans, lda, na, negone, dA.data(), lda, dX.data(), one, one, dE.data(), one );

         if(rnrm < xnrm*cte) { break; }
       }

        dX.raw(x.data());

        return x(_(1,na));
     }
   };

 } }

 #endif

 #endif


// namespace nt2{ namespace ext
// {
//   BOOST_DISPATCH_IMPLEMENT  ( mcsne_, nt2::tag::magma_<site>
//                             , (A0)(A1)(site)
//                             , ((ast_<A0, nt2::container::domain>))
//                               ((ast_<A1, nt2::container::domain>))
//                             )
//   {
//     typedef typename A0::value_type ctype_t;
//     typedef typename nt2::meta::as_real<ctype_t>::type   type_t;
//     typedef typename boost::dispatch::meta::downgrade<ctype_t>::type dtype;
//     typedef typename nt2::container::table<ctype_t> t_ct;
//     typedef  t_ct                                      result_type;

//      BOOST_FORCEINLINE result_type operator()(A0 const& a, A1 const& b) const
//     {
//       nt2_la_int lda = a.leading_size();
//       nt2_la_int na = nt2::width(a);

//       t_ct e,x;

//       double eps = boost::simd::Eps<double>();
//       double anrm = nt2::lange( boost::proto::value(a),MagmaInfNorm);
//       double cte = anrm*eps*nt2::sqrt( double(na));
//       double xnrm, rnrm;

//       nt2::container::table<dtype> sa,sb,sx;
//       nt2::container::table<dtype,nt2::upper_triangular_> sr,sr1(nt2::of_size(na,na));
//       sa = nt2::cast<dtype>(a);
//       sr = nt2::qr(sa,nt2::no_pivot_);

//       size_t size_n = sizeof(dtype)*(na);

//       for(nt2_la_int i=0; i<na; i++)
//       {
//         std::memcpy(sr1.data()+i*na, sr.data()+i*lda, size_n);
//       }

//       boost::proto::value(sr).swap(boost::proto::value(sr1) );

//       sx= nt2::mtimes(nt2::trans(sa),nt2::cast<dtype>(b));

//       sx = nt2::linsolve(nt2::trans(sr),sx);
//       sx = nt2::linsolve(sr,sx);

//       x = nt2::cast<ctype_t>(sx);
//       e = b - nt2::mtimes(a,x);

//       for( size_t i = 1; i<=10;++i)
//       {
//         sx = nt2::cast<dtype> (nt2::mtimes(nt2::trans(a),e) ) ;

//         sx = nt2::linsolve(nt2::trans(sr),sx);
//         sx = nt2::linsolve(sr,sx);

//         e = nt2::cast<ctype_t>(sx);
//         rnrm = nt2::maximum(nt2::abs(e(_)));
//         x = x + e;
//         e = b - nt2::mtimes(a,x);

//         xnrm = nt2::maximum(nt2::abs(x(_)));

//         if(rnrm < xnrm*cte) { break; }
//       }
//       return x;
//     }
//   };

// } }

// #endif

// #endif
