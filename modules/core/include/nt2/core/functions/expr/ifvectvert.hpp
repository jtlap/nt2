//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPR_IFVECTVERT_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_IFVECTVERT_HPP_INCLUDED

#include <nt2/core/functions/ifvectvert.hpp>
#include <nt2/core/container/dsl.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/include/functions/isvector.hpp>

namespace nt2 { namespace ext
{
  /// INTERNAL ONLY
  template<class Domain, int N, class Expr>
  struct size_of<nt2::tag::ifvectvert_,Domain,N,Expr>
  {
    typedef typename boost::proto::result_of::child_c<Expr&,0>::value_type  c0_t;
    typedef typename c0_t::extent_type                               result_type;

    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      result_type siz;
      siz[0] = nt2::numel(boost::proto::child_c<0>(e)); 
      if(nt2::isvector(boost::proto::child_c<0>(e)))
        return siz;
      else
        return extent(boost::proto::child_c<0>(e)); 
    }
  };

  /// INTERNAL ONLY
  template<class Domain, int N, class Expr>
  struct  value_type<nt2::tag::ifvectvert_,Domain,N,Expr>
        : meta::reshaping_value<Expr>
  {};
} }

namespace nt2 { namespace ext
{
  /// INTERNAL ONLY
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::ifvectvert_, tag::cpu_
                            , (A0)
                            , (ast_<A0>)
                            )
  {
    typedef typename meta::call<tag::numel_(A0&)>::type num;
    typedef nt2::of_size_< mpl_value<num>::value > sz;

    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::ifvectvert_
                                          , container::domain
                                          , A0&
                                          >::type             result_type;

    BOOST_FORCEINLINE result_type operator()(A0& a0) const
    {
      return  boost::proto::
              make_expr < nt2::tag::ifvectvert_
                        , container::domain
                        > ( boost::ref(a0)  );
    }
  };

  /// INTERNAL ONLY
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::ifvectvert_, tag::cpu_
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
