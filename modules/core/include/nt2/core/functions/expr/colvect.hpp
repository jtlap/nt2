//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPR_COLVECT_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_COLVECT_HPP_INCLUDED

#include <nt2/core/functions/colvect.hpp>
#include <nt2/core/container/dsl.hpp>
#include <nt2/include/functions/numel.hpp>

namespace nt2 { namespace ext
{
  /// INTERNAL ONLY
  template<class Domain, int N, class Expr>
  struct size_of<nt2::tag::colvect_,Domain,N,Expr>
  {
    //TODO: Handle static size
    typedef _1D result_type;

    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      return _1D(nt2::numel(boost::proto::child_c<0>(e)));
    }
  };

  /// INTERNAL ONLY
  template<class Domain, int N, class Expr>
  struct  value_type<nt2::tag::colvect_,Domain,N,Expr>
        : meta::reshaping_value<Expr>
  {};
} }

namespace nt2 { namespace ext
{
  /// INTERNAL ONLY
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::colvect_, tag::cpu_
                            , (A0)
                            , (ast_<A0>)
                            )
  {
    typedef typename meta::call<tag::numel_(A0&)>::type num;
    typedef nt2::of_size_< mpl_value<num>::value > sz;

    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::colvect_
                                          , container::domain
                                          , A0&
                                          >::type             result_type;

    BOOST_FORCEINLINE result_type operator()(A0& a0) const
    {
      return  boost::proto::
              make_expr < nt2::tag::colvect_
                        , container::domain
                        > ( boost::ref(a0)  );
    }
  };

  /// INTERNAL ONLY
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::colvect_, tag::cpu_
                            , (A0)
                            , (scalar_<fundamental_<A0> >)
                            )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      return a0;
    }
  };
} }

#endif
