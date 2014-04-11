//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2014 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_GENERAL_TRSOLVE_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_GENERAL_TRSOLVE_HPP_INCLUDED

#include <nt2/linalg/functions/trsolve.hpp>
#include <nt2/core/functions/transpose.hpp>
#include <nt2/core/functions/ctranspose.hpp>
#include <nt2/include/functions/trsm.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/core/container/dsl/alias.hpp>
#include <nt2/core/container/dsl/as_terminal.hpp>
#include <nt2/core/container/dsl/assign_swap.hpp>
#include <nt2/sdk/memory/forward/container.hpp>
#include <nt2/sdk/memory/category.hpp>
#include <boost/proto/traits.hpp>
#include <boost/assert.hpp>

namespace nt2 { namespace tag
{
  struct side
  {
    BOOST_FORCEINLINE static char call()
    {
      return 'L';
    }
  };

  struct diag
  {
    BOOST_FORCEINLINE static char call()
    {
      return 'N';
    }
  };

} }

namespace nt2 { namespace ext
{
  template<class Domain, int N, class Expr>
  struct  size_of<tag::trsolve_,Domain,N,Expr>
        : meta::size_as<Expr,1>
  {};

  template<class Domain, int N, class Expr>
  struct  value_type<tag::trsolve_,Domain,N,Expr>
        : meta::value_as<Expr,0>
  {};
} }

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::trsolve_, tag::cpu_
                            , (A0)(A1)
                            , ((ast_<A0, nt2::container::domain>))
                              ((ast_<A1, nt2::container::domain>))
                            )
  {
    typedef typename meta::option<typename A0::settings_type,nt2::tag::shape_>::type shape;
    typedef typename A0::value_type T;
    BOOST_DISPATCH_RETURNS(2, (A0 const& a0, A1 const& a1),
      trsolve(a0, a1, One<T>(), tag::blas_normal_(), shape::id_value, tag::side(), tag::diag() )
    )
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::trsolve_, tag::cpu_
                            , (A0)(A1)(A2)
                            , ((ast_<A0, nt2::container::domain>))
                              ((ast_<A1, nt2::container::domain>))
                              (scalar_< unspecified_<A2> >)
                            )
  {
    typedef typename meta::option<typename A0::settings_type,nt2::tag::shape_>::type shape;
    typedef typename A0::value_type T;
    BOOST_DISPATCH_RETURNS(3, (A0 const& a0, A1 const& a1, A2 const& a2),
      trsolve(a0, a1, a2, tag::blas_normal_(), shape::id_value, tag::side(), tag::diag() )
    )
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::trsolve_, tag::cpu_
                            , (A0)(A1)(A2)(A3)(A4)(A5)(A6)
                            , ((ast_<A0, nt2::container::domain>))
                              ((ast_< A1, nt2::container::domain>))
                              (scalar_< unspecified_<A2> >)
                              (unspecified_<A3>)
                              (unspecified_<A4>)
                              (unspecified_<A5>)
                              (unspecified_<A6>)
                            )
  {
    BOOST_DISPATCH_RETURNS_ARGS(7, (A0 const& a0, A1 const& a1, A2 const& a2, A3 const& a3, A4 const& a4,A5 const& a5,A6 const& a6)
                                 , (A0 const& a0, A1 const& a1, A2 const& a2, A3 const&   , A4 const& a4,A5 const& a5,A6 const& a6),
      trsolve(a0, a1, a2, tag::blas_normal_(), a4, a5, a6 )
    )
  };

  // Recognize transpose
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::trsolve_, tag::cpu_
                            , (A0)(A1)(A2)(A3)(A4)(A5)(A6)
                            , ((node_< A0, nt2::tag::transpose_, boost::mpl::long_<1> , nt2::container::domain>))
                              ((ast_< A1, nt2::container::domain>))
                              (scalar_< unspecified_<A2> >)
                              (unspecified_<A3>)
                              (unspecified_<A4>)
                              (unspecified_<A5>)
                              (unspecified_<A6>)
                            )
  {
    BOOST_DISPATCH_RETURNS_ARGS(7, (A0 const& a0, A1 const& a1, A2 const& a2, A3 const& a3, A4 const& a4,A5 const& a5,A6 const& a6)
                                 , (A0 const& a0, A1 const& a1, A2 const& a2, A3 const&   , A4 const& a4,A5 const& a5,A6 const& a6),
      trsolve( boost::proto::child_c<0>(a0), a1, a2, tag::blas_transpose_(), a4, a5, a6 )
    )
  };

  // run_assign
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_assign_, tag::cpu_
                            , (A0)(A1)
                            , ((ast_<A0, nt2::container::domain>))
                              ((node_< A1, nt2::tag::trsolve_, boost::mpl::long_<7> , nt2::container::domain>))
                            )
  {
    typedef A0& result_type;
    typedef typename A0::value_type T;
    typedef nt2::memory::container<tag::table_, T, nt2::_2D> desired_semantic;

    result_type operator()(A0& a0, A1& a1) const
    {
      char side  = A1::proto_child6::proto_child0::call();
      char diag  = A1::proto_child5::proto_child0::call();
      char trans = A1::proto_child3::proto_child0::call();
      char uplo  = boost::proto::value(boost::proto::child_c<4>(a1));
      T alpha    = boost::proto::value(boost::proto::child_c<2>(a1));
      nt2_la_int m   = boost::fusion::at_c<0>( (boost::proto::child_c<0>(a1)).extent() );
      nt2_la_int n   = boost::fusion::at_c<1>( (boost::proto::child_c<0>(a1)).extent() );
      nt2_la_int ldb = boost::fusion::at_c<0>( (boost::proto::child_c<1>(a1)).extent() );

      typename container::as_terminal<desired_semantic, A0&>::type result =
                    container::as_terminal<desired_semantic, A0&>::init(a0);

      typedef typename container::as_terminal<desired_semantic>::type dummy_type;
      typedef typename container::as_view_impl<dummy_type>::type view_type;

      dummy_type dummy;
      view_type result_view;
      bool swap = (void*)&result != (void*)&a0;

      if( !container::alias(result, boost::proto::child_c<1>(a1))  )
      {
        // no overlapping of input and output data so set output with
        // input data for destructive lapack call
        result = boost::proto::child_c<1>(a1) ;
        result_view.reset(result);
      }
      else if (swap)
      {
        dummy = boost::proto::child_c<1>(a1) ;
        result_view.reset(dummy);
        swap = true;
      }
      else result_view.reset(boost::proto::child_c<1>(a1) );

      nt2::trsm(side, uplo, trans, diag, boost::proto::value(boost::proto::child_c<0>(a1))
                                       , boost::proto::value(result_view) );

      if (swap) container::assign_swap(a0, dummy);

      return a0;
    }
  };
}
}

#endif
