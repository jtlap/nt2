//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_MAGMA_GELS_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_MAGMA_GELS_HPP_INCLUDED

#if defined(NT2_USE_MAGMA)

#include <nt2/linalg/functions/gels.hpp>
#include <nt2/linalg/details/magma_buffer.hpp>
#include <nt2/sdk/magma/magma.hpp>
#include <nt2/dsl/functions/terminal.hpp>
#include <nt2/core/container/table/kind.hpp>
#include <nt2/linalg/details/utility/f77_wrapper.hpp>
#include <nt2/linalg/details/utility/workspace.hpp>

#include <nt2/include/functions/of_size.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/width.hpp>

#include <nt2/core/container/table/table.hpp>

#include <magma.h>

namespace nt2 { namespace ext
{
  /// INTERNAL ONLY - Compute the workspace
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::gels_, nt2::tag::magma_<site>
                            , (A0)(S0)(A1)(S1)(site)
                            , ((container_< nt2::tag::table_, double_<A0>, S0 >))
                              ((container_< nt2::tag::table_, double_<A1>, S1 >))
                            )
  {
    typedef nt2_la_int result_type;
    typedef double T ;

  BOOST_FORCEINLINE result_type operator()(A0& a0, A1& a1) const
    {
      result_type that;
      details::workspace<typename A0::value_type> w;
      nt2_la_int  m  = nt2::height(a0);
      nt2_la_int  n  = nt2::width(a0);
      nt2_la_int  ldda = ((m+31)/32)*32;
      nt2_la_int  nhrs = nt2::width(a1);
      nt2_la_int  ldb = a1.leading_size();
      nt2_la_int lwork_query = -1;

      magma_dgels_gpu('N',m,n,nhrs,0,ldda,0,ldb,w.main(),lwork_query,&that);

      w.prepare_main();
      nt2::gels(a0,a1,w);
      return that;
  }
};

  /// INTERNAL ONLY - Workspace is ready
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::gels_, nt2::tag::magma_<site>
                            , (A0)(S0)(A1)(S1)(A2)(site)
                            , ((container_< nt2::tag::table_, double_<A0>, S0 >))
                              ((container_< nt2::tag::table_, double_<A1>, S1 >))
                              (unspecified_<A2>)
                            )
  {
    typedef nt2_la_int result_type;
    typedef double T ;

    BOOST_FORCEINLINE result_type operator()(A0& a0, A1& a1,A2& a2) const
      {
        result_type that;
        nt2_la_int  m  = nt2::height(a0);
        nt2_la_int  n  = nt2::width(a0);
        nt2_la_int  ldda = ((m+31)/32)*32;
        nt2_la_int  wn = a2.main_size();
        nt2_la_int  nhrs = nt2::width(a1);
        nt2_la_int  ldb = a1.leading_size();

        details::magma_buffer<double>     dA(m,n   ,a0.raw());
        details::magma_buffer<double>     dX(m,nhrs, a1.raw());

        magma_dgels_gpu('N',m,n,nhrs,dA.raw(),m,dX.raw(),ldb,a2.main(),wn,&that);

        dX.raw( a1.raw() );

        return that;
  }
};


  /// INTERNAL ONLY - Compute the workspace
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::gels_, nt2::tag::magma_<site>
                            , (A0)(S0)(A1)(S1)(site)
                            , ((container_< nt2::tag::table_, single_<A0>, S0 >))
                              ((container_< nt2::tag::table_, single_<A1>, S1 >))
                            )
  {
    typedef nt2_la_int result_type;
    typedef float T ;

    BOOST_FORCEINLINE result_type operator()(A0& a0, A1& a1) const
      {
        result_type that;
        details::workspace<typename A0::value_type> w;
        nt2_la_int  m  = nt2::height(a0);
        nt2_la_int  n  = nt2::width(a0);
        nt2_la_int  lda = a0.leading_size();
        nt2_la_int  nhrs = nt2::width(a1);
        nt2_la_int  ldb = a1.leading_size();
        nt2_la_int lwork_query = -1;

        magma_sgels_gpu('N',m,n,nhrs,0,lda,0,ldb,w.main(),lwork_query,&that);

        w.prepare_main();
        nt2::gels(a0,a1,w);
        return that;
      }
  };

  /// INTERNAL ONLY - Workspace is ready
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::gels_, nt2::tag::magma_<site>
                            , (A0)(S0)(A1)(S1)(A2)(site)
                            , ((container_< nt2::tag::table_, single_<A0>, S0 >))
                             ((container_< nt2::tag::table_, single_<A1>, S1 >))
                              (unspecified_<A2>)
                            )
    {
    typedef nt2_la_int result_type;
    typedef float T ;

    BOOST_FORCEINLINE result_type operator()(A0& a0, A1& a1,A2& a2) const
    {
      result_type that;
      nt2_la_int  m  = nt2::height(a0);
      nt2_la_int  n  = nt2::width(a0);
      nt2_la_int  wn = a2.main_size();
      nt2_la_int  nhrs = nt2::width(a1);
      nt2_la_int  ldb = a1.leading_size();

      details::magma_buffer<float>     dA(m,n   ,a0.raw());
      details::magma_buffer<float>     dX(m,nhrs, a1.raw());

      magma_sgels_gpu('N',m,n,nhrs,dA.raw(),m,dX.raw(),ldb,a2.main(),wn,&that);

      dX.raw( a1.raw() );

      return that;
    }
  };


} }

#endif

#endif
