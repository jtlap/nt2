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
#include <nt2/include/functor.hpp>
#include <nt2/include/functions/run.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/core/container/table/table.hpp>
#include <boost/fusion/include/pop_front.hpp>
#include <boost/fusion/include/vector_tie.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::transform_, tag::cpu_
                            , (A0)(A1)(T1)(N1)
                            , (ast_<A0>)
                              ((expr_< scalar_< unspecified_<A1> >
                                     , T1
                                     , N1
                                     >
                              ))
                            )
  {
    typedef void result_type;

    typedef typename meta::
            strip< typename meta::
                   scalar_of<A0>::type
                 >::type                                    stype;

    BOOST_FORCEINLINE result_type
    operator()(A0& a0, A1& a1) const
    {
      nt2::run(a0, 0, nt2::run(a1, 0, meta::as_<stype>()));
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::transform_, tag::cpu_
                            , (A0)(A1)(S1)(T1)(N1)
                            , (ast_<A0>)
                              ((expr_< table_< unspecified_<A1>, S1 >
                                     , T1
                                     , N1
                                     >
                              ))
                            )
  {
    typedef void result_type;

    typedef typename meta::
            strip< typename meta::
                   scalar_of<A0>::type
                 >::type                                    stype;

    BOOST_FORCEINLINE result_type
    operator()(A0& a0, A1& a1) const
    {
      std::ptrdiff_t bound  = nt2::numel(a0);

      for(std::size_t i=0; i < bound; ++i)
        nt2::run(a0, i, nt2::run(a1, i, meta::as_<stype>()));
    }
  };

} }

#endif
