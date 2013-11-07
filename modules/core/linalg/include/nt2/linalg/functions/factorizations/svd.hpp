//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_FACTORIZATIONS_SVD_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_FACTORIZATIONS_SVD_HPP_INCLUDED

#include <nt2/include/functions/of_size.hpp>
#include <nt2/include/functions/from_diag.hpp>
#include <nt2/include/functions/resize.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/include/functions/transpose.hpp>
#include <nt2/include/functions/gesvd.hpp>
#include <nt2/include/functions/tie.hpp>
#include <nt2/linalg/details/utility/f77_wrapper.hpp>
#include <nt2/linalg/options.hpp>
#include <nt2/sdk/meta/concrete.hpp>

#include <nt2/table.hpp>

namespace nt2 { namespace ext
{
  //============================================================================
  //SVD
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::svd_, tag::cpu_
                            , (A0)(N0)(A1)(N1)
                            , ((node_<A0, nt2::tag::svd_
                                    , N0, nt2::container::domain
                                      >
                              ))
                              ((node_<A1, nt2::tag::tie_
                                    , N1, nt2::container::domain
                                     >
                              ))
                            )
  {
    typedef void  result_type;
    typedef typename boost::proto::result_of::child_c<A0&,0>::value_type child0;
    typedef typename child0::value_type type_t;
    typedef type_t T;

    BOOST_FORCEINLINE result_type operator()( A0& a0, A1& a1 ) const
    {
      nt2::table<type_t> s , u, vt;
      eval(a0, a1, s, u , vt, N0(), N1());
    }

    //==========================================================================
    /// INTERNAL ONLY - S = SVD(A)
    BOOST_FORCEINLINE
    void eval ( A0& a0, A1& a1
              , nt2::table<type_t>& s    , nt2::table<type_t>& u
              , nt2::table<type_t>& vt
              , boost::mpl::long_<1> const& , boost::mpl::long_<1> const&
              ) const
    {
      nt2::table<type_t> work = boost::proto::child_c<0>(a0);

      nt2_la_int  m  = nt2::height(work);
      nt2_la_int  n  = nt2::width(work);

      char jobu =  'N';
      char jobvt = 'N';

      boost::proto::child_c<0>(a1).resize(nt2::of_size(std::min(m,n),1));

      nt2_la_int info = nt2::gesvd( work,boost::proto::child_c<0>(a1),u,vt,jobu,jobvt);

    }

    //==========================================================================
    /// INTERNAL ONLY - [U,S,V] = SVD(X)
    BOOST_FORCEINLINE
    void eval ( A0& a0, A1& a1
              , nt2::table<type_t>& s    , nt2::table<type_t>& u
              , nt2::table<type_t>& vt
              , boost::mpl::long_<1> const& , boost::mpl::long_<3> const&
              ) const
    {
      nt2::table<type_t> work = boost::proto::child_c<0>(a0);

      char jobu = 'A';
      char jobvt = 'A';

      nt2_la_int  m  = nt2::height(work);
      nt2_la_int  n  = nt2::width(work);

      s.resize(nt2::of_size(std::min(m,n), 1));
      u.resize(nt2::of_size(m,m));
      vt.resize(nt2::of_size(n,n));

      nt2_la_int info = nt2::gesvd(work,s,u,vt,jobu,jobvt);

      boost::proto::child_c<0>(a1) = u;
      boost::proto::child_c<2>(a1) = nt2::trans(vt);

      if (m==n)
        boost::proto::child_c<1>(a1) = nt2::from_diag(s);
      else
      {
        boost::proto::child_c<1>(a1) = nt2::zeros(m,n,nt2::meta::as_<type_t>());
        for(size_t i = 1; i <= nt2::numel(s);i++)
          boost::proto::child_c<1>(a1) (i,i) = s(i);
      }
    }

    //==========================================================================
    /// INTERNAL ONLY - [U,S,V] = SVD(X,0/econ)
    BOOST_FORCEINLINE
    void eval ( A0& a0, A1& a1
              , nt2::table<type_t>& s    , nt2::table<type_t>& u
              , nt2::table<type_t>& vt
              , boost::mpl::long_<2> const& , boost::mpl::long_<3> const&
              ) const
    {
      eval(a0,a1,s,u,vt,boost::proto::value(boost::proto::child_c<1>(a0)));
    }

//==========================================================================
    /// INTERNAL ONLY - [U,S,V] = SVD(X,0)
    BOOST_FORCEINLINE
    void eval ( A0& a0, A1& a1
              , nt2::table<type_t>& s    , nt2::table<type_t>& u
              , nt2::table<type_t>& vt
              , int const&
              ) const
    {
      nt2::table<type_t> work = boost::proto::child_c<0>(a0);

      char jobu = 'A';
      char jobvt = 'A';

      nt2_la_int  m  = nt2::height(work);
      nt2_la_int  n  = nt2::width(work);

      s.resize(nt2::of_size(std::min(m,n), 1));
      vt.resize(nt2::of_size(n,n));


      if(m>n)
      {
        jobu = 'S';
        boost::proto::child_c<0>(a1).resize(nt2::of_size(m,n));
      }
      else boost::proto::child_c<0>(a1).resize(nt2::of_size(m,m)) ;

      nt2_la_int info = nt2::gesvd(work,s,boost::proto::child_c<0>(a1),vt,jobu,jobvt);

      boost::proto::child_c<2>(a1) = nt2::trans(vt);
      boost::proto::child_c<1>(a1) = nt2::from_diag(s);
  }

//==========================================================================
    /// INTERNAL ONLY - [U,S,V] = SVD(X,econ)
    template<typename P> BOOST_FORCEINLINE
    void eval ( A0& a0, A1& a1
              , nt2::table<type_t>& s    , nt2::table<type_t>& u
              , nt2::table<type_t>& vt
              , P const&
              ) const
    {
      nt2::table<type_t> work = boost::proto::child_c<0>(a0);

      char jobu = 'A';
      char jobvt = 'A';

      nt2_la_int  m  = nt2::height(work);
      nt2_la_int  n  = nt2::width(work);

      s.resize(nt2::of_size(std::min(m,n),1));


      if(m>n)
      {
        jobu = 'S';
        boost::proto::child_c<0>(a1).resize(nt2::of_size(m,n));
        vt.resize(nt2::of_size(n,n));
      }
      else if (m<n)
      {
        jobvt = 'S';
        boost::proto::child_c<0>(a1).resize(nt2::of_size(m,m));
        vt.resize(nt2::of_size(m,n));
      }
      else
      {
        boost::proto::child_c<0>(a1).resize(nt2::of_size(m,m));
        vt.resize(nt2::of_size(n,n));
      }


      nt2_la_int info = nt2::gesvd(work,s,boost::proto::child_c<0>(a1),vt,jobu,jobvt);

      boost::proto::child_c<1>(a1) = nt2::from_diag(s);
      boost::proto::child_c<2>(a1) = nt2::trans(vt);

    }
  };
} }

#endif


