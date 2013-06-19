//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_LINALG_FUNCTIONS_LAPACK_MLINSOLVE_HPP_INCLUDED
#define NT2_TOOLBOX_LINALG_FUNCTIONS_LAPACK_MLINSOLVE_HPP_INCLUDED

#include <nt2/linalg/functions/mlinsolve.hpp>
#include <nt2/include/functions/msv.hpp>
#include <nt2/include/functions/mposv.hpp>
#include <nt2/linalg/options.hpp>
#include <nt2/sdk/meta/concrete.hpp>
#include <nt2/sdk/meta/settings_of.hpp>

#include <nt2/core/container/table/table.hpp>

namespace nt2 { namespace ext
{
  //============================================================================
  // LINSOLVE
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::mlinsolve_, tag::cpu_
                            , (A0)(A1)(A2)
                            , ((ast_<A0, nt2::container::domain>)) // A
                              ((ast_<A1, nt2::container::domain>)) // B
                              ((ast_<A2, nt2::container::domain>)) // X
                            )
  {
    typedef void  result_type;;
    typedef typename A0::value_type type_t;
    typedef typename meta::option<typename A0::settings_type,nt2::tag::shape_>::type shape;

    typedef nt2::container::table<type_t>  entry_type;

    BOOST_FORCEINLINE result_type operator()( A0 const& a0, A1 const& a1, A2& a2 ) const
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


    BOOST_FORCEINLINE
    void shape_analysis ( A0 const& a0, A1 const& a1, A2& a2
                        , nt2::positive_definite_ const&
                        ) const
    {
      entry_type var = concrete(a2);
      entry_type entry = concrete(a0);
      nt2_la_int iter = nt2::mposv(entry,concrete(a1),var);
      a2 = var;
    }

    template<typename sh>
    BOOST_FORCEINLINE
    void shape_analysis ( A0 const& a0, A1 const& a1, A2& a2
                        , sh const&
                        ) const
    {
      eval(a0, a1, a2);
    }
    //==========================================================================
    /// INTERNAL ONLY - Solve with no shape info Todo : Analyse shape
    BOOST_FORCEINLINE
    void eval ( A0 const& a0, A1 const& a1 , A2& a2) const
    {
      entry_type var = concrete(a2);
      entry_type entry(a0);
      nt2_la_int iter = nt2::msv(entry,concrete(a1),var);
      a2 = var;

    }

  };


} }


#endif
