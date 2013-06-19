//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_LINALG_FUNCTIONS_LAPACK_PLINSOLVE_HPP_INCLUDED
#define NT2_TOOLBOX_LINALG_FUNCTIONS_LAPACK_PLINSOLVE_HPP_INCLUDED

#include <nt2/linalg/functions/plinsolve.hpp>
#include <nt2/include/functions/svx.hpp>
#include <nt2/include/functions/ysvx.hpp>
#include <nt2/include/functions/posvx.hpp>
#include <nt2/linalg/options.hpp>
#include <nt2/sdk/meta/concrete.hpp>
#include <nt2/linalg/functions/details/eval_mldivide.hpp>
#include <nt2/sdk/meta/settings_of.hpp>

#include <nt2/core/container/table/table.hpp>

namespace nt2 { namespace ext
{
  //============================================================================
  // LINSOLVE
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::plinsolve_, tag::cpu_
                            , (A0)(A1)(A2)
                            , ((ast_<A0, nt2::container::domain>))  // A
                              ((ast_<A1, nt2::container::domain>))  // B
                              ((ast_<A2, nt2::container::domain>))  // X
                            )
  {
    typedef void  result_type;
    typedef typename A0::value_type type_t;
    typedef typename meta::option<typename A0::settings_type,nt2::tag::shape_>::type shape;
    typedef nt2::container::table<type_t>  entry_type;

    BOOST_FORCEINLINE result_type operator()( A0 const& a0, A1 const& a1, A2&  a2 ) const
    {
      shape_analysis(a0,a1,a2,shape());
    }

    //==========================================================================
    /// INTERNAL ONLY - Shape analysis

    BOOST_FORCEINLINE
    void shape_analysis ( A0 const& a0, A1 const& a1 , A2& a2
                        , nt2::rectangular_ const&
                        ) const
    {
      eval(a0, a1, a2);
    }

    /// INTERNAL ONLY - Positive definite shape
    BOOST_FORCEINLINE
    void shape_analysis ( A0 const& a0, A1 const& a1 , A2& a2
                        , nt2::positive_definite_ const&
                        ) const
    {
      type_t rcond;
      entry_type var = concrete(a2);
      nt2_la_int iter = nt2::posvx(concrete(a0),concrete(a1),var,rcond);
      a2 = var;
    }
    /// INTERNAL ONLY - Symmetric shape
    BOOST_FORCEINLINE
    void shape_analysis ( A0 const& a0, A1 const& a1 , A2& a2
                        , nt2::symmetric_ const&
                        ) const
    {
      type_t rcond;
      entry_type var = concrete(a2);
      nt2_la_int iter = nt2::ysvx(concrete(a0),concrete(a1),var,rcond);
      a2 = var;
    }

    /// INTERNAL ONLY - No info on this shape
    template<typename sh>
    BOOST_FORCEINLINE
    void shape_analysis ( A0 const& a0, A1 const& a1, A2& a2, sh const&) const
    {
      eval(a0,a1,a2);
    }

    //==========================================================================
    /// INTERNAL ONLY - Solve with no shape info - Todo : Analyse shape
    BOOST_FORCEINLINE
    void eval ( A0 const& a0, A1 const& a1 , A2& a2) const
    {
      type_t rcond;

      entry_type var = concrete(a2);
      nt2::svx( concrete(a0), concrete(a1), var, rcond );
      a2 = var;

    }

  };


} }


#endif
