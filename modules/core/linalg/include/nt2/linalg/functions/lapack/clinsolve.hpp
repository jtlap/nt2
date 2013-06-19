//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_LINALG_FUNCTIONS_LAPACK_CLINSOLVE_HPP_INCLUDED
#define NT2_TOOLBOX_LINALG_FUNCTIONS_LAPACK_CLINSOLVE_HPP_INCLUDED


#include <nt2/linalg/functions/clinsolve.hpp>

#include <nt2/include/functions/issquare.hpp>
#include <nt2/include/functions/lsy.hpp>
#include <nt2/include/functions/sv.hpp>
#include <nt2/include/functions/posv.hpp>
#include <nt2/include/functions/ysv.hpp>
#include <nt2/include/functions/lange.hpp>
#include <nt2/include/functions/con.hpp>
#include <nt2/include/functions/sycon.hpp>
#include <nt2/include/functions/pocon.hpp>

#include <nt2/include/functions/tie.hpp>

#include <nt2/linalg/options.hpp>
#include <nt2/sdk/meta/concrete.hpp>
#include <nt2/linalg/functions/details/eval_linsolve.hpp>
#include <nt2/sdk/meta/settings_of.hpp>

#include <nt2/core/container/table/table.hpp>

namespace nt2 { namespace ext
{
  //============================================================================
  // LINSOLVE classic
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::clinsolve_, tag::cpu_
                            , (A0)(A1)(A2)(N2)
                            , ((ast_<A0, nt2::container::domain>))   // A
                              ((ast_<A1, nt2::container::domain>))   // B
                              ((node_<A2, nt2::tag::tie_             // X-R
                                    , N2, nt2::container::domain
                                     >
                              ))
                            )
  {
    typedef void  result_type;
    typedef typename A0::value_type type_t;
    typedef typename meta::option<typename A0::settings_type,nt2::tag::shape_>::type shape;

    typedef nt2::container::table<type_t>  entry_type;

    BOOST_FORCEINLINE result_type operator()( A0 const& a0, A1 const& a1, A2 const& a2  ) const
    {
      nt2::table<nt2_la_int> piv;
      shape_analysis(a0,a1,a2,piv,N2(),shape());
    }

    //==========================================================================
    /// INTERNAL ONLY - Shape analysis

    /// INTERNAL ONLY - Rectangular shape, no usable informations
    BOOST_FORCEINLINE
    void shape_analysis ( A0 const& a0, A1 const& a1 , A2 const& a2
                        , nt2::table<nt2_la_int>& piv, N2 const&
                        , nt2::rectangular_ const&
                        ) const
    {
      eval(a0, a1, a2, piv, N2());
    }

    /// INTERNAL ONLY - symmetric shape - square matrix
    BOOST_FORCEINLINE
    void shape_analysis ( A0 const& a0, A1 const& a1 , A2 const& a2
                        , nt2::table<nt2_la_int>& piv, N2 const&
                        , nt2::symmetric_ const&
                        ) const
    {
      eval(a0, a1, a2, piv, N2(), shape());
    }

    /// INTERNAL ONLY - positive definite shape - square matrix
    BOOST_FORCEINLINE
    void shape_analysis ( A0 const& a0, A1 const& a1 , A2 const& a2
                        , nt2::table<nt2_la_int>& piv, N2 const&
                        , nt2::positive_definite_ const&
                        ) const
    {
      eval(a0, a1, a2, piv, N2(), shape());
    }

    /// INTERNAL ONLY - No info on this shape
    template<typename sh>
    BOOST_FORCEINLINE
    void shape_analysis ( A0 const& a0, A1 const& a1, A2 const& a2
                        , nt2::table<nt2_la_int>& piv, N2 const&
                        , sh const&
             ) const
    {
      eval(a0, a1, a2, piv, N2());
    }

    //==========================================================================
    /// INTERNAL ONLY - X = LINSOLVE(A,B) - rectangular shape
    BOOST_FORCEINLINE
    void eval ( A0 const& a0, A1 const& a1 , A2 const& a2, nt2::table<nt2_la_int>& piv
              , boost::mpl::long_<1> const&
              ) const
    {
      entry_type work = concrete(a1);
      entry_type entry(a0);

      eval_param( a0, a1, work);

      if (issquare(entry)) nt2::sv(entry,piv,work);
      else                 nt2::lsy(entry,piv,work);

      boost::proto::child_c<0>(a2) = work;
    }

    //==========================================================================
    /// INTERNAL ONLY - X = LINSOLVE(A,B) - positive definite shape
    BOOST_FORCEINLINE
    void eval ( A0 const& a0, A1 const& a1 , A2 const& a2, nt2::table<nt2_la_int>& piv
              , boost::mpl::long_<1> const&, nt2::positive_definite_ const&
              ) const
    {
      entry_type work = concrete(a1);
      entry_type entry(a0);

      nt2::posv(entry, a1, work);

      boost::proto::child_c<0>(a2) = work;
    }

    //==========================================================================
    /// INTERNAL ONLY - X = LINSOLVE(A,B) - symmetric shape
    BOOST_FORCEINLINE
    void eval ( A0 const& a0, A1 const& a1 , A2 const& a2, nt2::table<nt2_la_int>& piv
              , boost::mpl::long_<1> const&, nt2::symmetric_ const&
              ) const
    {
      entry_type work = concrete(a1);
      entry_type entry(a0);

      nt2::ysv(entry, piv, a1, work);

      boost::proto::child_c<0>(a2) = work;
    }



    //==========================================================================
    /// INTERNAL ONLY - [X,R] = LINSOLVE(A,B) -- Rectangular shape
    BOOST_FORCEINLINE
    void eval( A0 const& a0, A1 const& a1 , A2 const& a2, nt2::table<nt2_la_int>& piv
              , boost::mpl::long_<2> const&
              ) const
    {
      entry_type work = concrete(a1);
      entry_type entry(a0);

      eval_param( a0, a1, boost::proto::child_c<0>(a2));

      if (issquare(entry))
      {
        nt2::sv(entry, piv, work );
        char norm = '1';
        type_t anorm = nt2::lange(a0,norm);
        boost::proto::child_c<1>(a2) = nt2::con(entry,norm,anorm);
      }
      else
      {
        nt2_la_int rank;
        nt2::lsy(entry, piv, work, rank);
        boost::proto::child_c<1>(a2) = static_cast<type_t>(rank);
      }

      boost::proto::child_c<0>(a2) = work;
    }

    //==========================================================================
    /// INTERNAL ONLY - [X,R] = LINSOLVE(A,B) -- symmetric shape
    BOOST_FORCEINLINE
    void eval ( A0 const& a0, A1 const& a1 , A2 const& a2, nt2::table<nt2_la_int>& piv
              , boost::mpl::long_<2> const&, nt2::symmetric_ const&
              ) const
    {
      entry_type work = concrete(a1);
      entry_type entry(a0);
      char norm = '1';

      type_t anorm = nt2::lange(a0, norm);
      nt2::ysv(entry,piv,a1,work);
      boost::proto::child_c<1>(a2) = nt2::sycon(entry,piv,anorm);

      boost::proto::child_c<0>(a2) = work;
    }

    //==========================================================================
    /// INTERNAL ONLY - [X,R] = LINSOLVE(A,B) -- positive definite shape
    BOOST_FORCEINLINE
    void eval ( A0 const& a0, A1 const& a1 , A2 const& a2, nt2::table<nt2_la_int>& piv
              , boost::mpl::long_<2> const&, nt2::positive_definite_ const&
              ) const
    {
      entry_type work = concrete(a1);
      entry_type entry(a0);

      nt2::posv(entry, a1, work);
      char norm = '1';
      type_t anorm = nt2::lange(a0,norm);
      boost::proto::child_c<1>(a2) = nt2::pocon(entry,anorm);

      boost::proto::child_c<0>(a2) = work;
    }
  };
} }


#endif
