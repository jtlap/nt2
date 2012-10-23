//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_REDUCTION_FUNCTIONS_EXPR_DOT_HPP_INCLUDED
#define NT2_TOOLBOX_REDUCTION_FUNCTIONS_EXPR_DOT_HPP_INCLUDED

#include <nt2/toolbox/reduction/functions/dot.hpp>
#include <nt2/core/container/dsl.hpp>
#include <nt2/include/functions/sum.hpp>
#include <nt2/include/functions/conj.hpp>
#include <nt2/include/functions/multiplies.hpp>

namespace nt2 { namespace ext
{
  /// INTERNAL ONLY
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::dot_, tag::cpu_
                            , (A0)(A1)
                            , ((ast_<A0, nt2::container::domain>))((ast_<A1, nt2::container::domain>))
                            )
  {
    typedef typename meta::call < tag::conj_(A1 const&)>::type    conj_t;
    typedef typename meta::call < tag::multiplies_( A0 const&
                                                  , conj_t const&
                                                  )
                                >::type                           mul_t;
    typedef typename meta::call < tag::sum_(mul_t const&)>::type  result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const& a1) const
    {
      return nt2::sum(nt2::multiplies(a0, conj(a1)));
    }
  };

  /// INTERNAL ONLY
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::dot_, tag::cpu_,
                              (A0)(A1)(A2),
                              ((ast_<A0, nt2::container::domain>))((ast_<A1, nt2::container::domain>))
                              (scalar_<integer_<A2> > )
                              )
  {
    typedef typename meta::call < tag::conj_(A1 const&)>::type    conj_t;
    typedef typename meta::call < tag::multiplies_( A0 const&
                                                  , conj_t const&
                                                  )
                                >::type                           mul_t;
    typedef typename meta::call < tag::sum_ ( mul_t const&
                                            , A2
                                            )
                                >::type                           result_type;

    BOOST_FORCEINLINE
    result_type operator()(A0 const& a0, const A1& a1, const A2& a2) const
    {
      return nt2::sum(nt2::multiplies(a0, conj(a1)), a2);
    }
  };
} }

#endif
