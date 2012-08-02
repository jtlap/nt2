//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_COMMON_TRANSFORM_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_COMMON_TRANSFORM_HPP_INCLUDED

#include <nt2/core/functions/transform.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/include/functions/run.hpp>

namespace nt2 { namespace ext
{
  //============================================================================
  // Global version
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::transform_, tag::cpu_
                            , (A0)(A1)
                            , (ast_<A0>)
                              (ast_<A1>)
                            )
  {
    typedef void result_type;

    BOOST_FORCEINLINE result_type operator()(A0& a0, A1& a1) const
    {
      nt2::transform(a0,a1,0,nt2::numel(a0),1);
    }
  };

  //============================================================================
  // Partial version - Process in*out elements starting at element p
  // Note that p should be properly set beforehand
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::transform_, tag::cpu_
                            , (A0)(A1)(A2)(A3)(A4)
                            , (ast_<A0>)
                              (ast_<A1>)
                              (scalar_< integer_<A2> >)
                              (scalar_< integer_<A3> >)
                              (scalar_< integer_<A4> >)
                            )
  {
    typedef void result_type;

    typedef typename A0::value_type                stype;

    BOOST_FORCEINLINE result_type
    operator()(A0& a0, A1& a1, A2 p, A3 in, A4 out) const
    {
      std::size_t bound = p+in*out;
      for(std::size_t i=p; i != bound; ++i)
        nt2::run(a0, i, nt2::run(a1, i, meta::as_<stype>()));
    }
  };
} }

#endif
