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
      nt2::run(a0, boost::fusion::vector0<>(), nt2::run(a1, boost::fusion::vector0<>(), meta::as_<stype>()));
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
      typename A0::index_type::type bs;
      std::ptrdiff_t ilow   = boost::fusion::at_c<0>(bs);
      std::ptrdiff_t olow   = boost::fusion::at_c<1>(bs);
      std::ptrdiff_t bound  = boost::fusion::at_c<0>(a0.extent()) + ilow;
      std::ptrdiff_t obound = olow + nt2::numel(boost::fusion::pop_front(a0.extent()));

      for(std::ptrdiff_t j=olow; j!=obound; ++j)
        for(std::ptrdiff_t i=ilow; i!=bound; ++i)
          nt2::run(a0, boost::fusion::vector_tie(i, j), nt2::run(a1, boost::fusion::vector_tie(i,j), meta::as_<stype>()));
    }
  };

} }

#endif
