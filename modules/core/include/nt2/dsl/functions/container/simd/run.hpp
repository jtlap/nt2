//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_DSL_FUNCTIONS_CONTAINER_SIMD_RUN_HPP_INCLUDED
#define NT2_DSL_FUNCTIONS_CONTAINER_SIMD_RUN_HPP_INCLUDED

#include <nt2/dsl/functions/run.hpp>
#include <nt2/include/functions/extent.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/core/container/table/table.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>
#include <boost/fusion/include/vector_tie.hpp>
#include <boost/fusion/include/pop_front.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_, boost::simd::tag::simd_
                            , (A0)(S0)
                            , ((expr_< table_< unspecified_<A0>, S0 >
                                     , nt2::container::domain
                                     , nt2::tag::assign_
                                     >
                              ))
                            )
  {
    typedef typename boost::proto::result_of::
    child_c<A0 const&, 0>::type                             result_type;

    typedef typename meta::
            strip< typename meta::
                   scalar_of<result_type>::type
                 >::type                                    stype;

    typedef boost::simd::native<stype, BOOST_SIMD_DEFAULT_EXTENSION>
                                                            target_type;

    BOOST_FORCEINLINE result_type
    operator()(A0 const& a0) const
    {
      static const std::size_t N = boost::simd::meta::cardinal_of<target_type>::value;

      boost::proto::child_c<0>(a0).resize(a0.extent());

      typename A0::index_type::type bs;
      std::ptrdiff_t ilow   = boost::fusion::at_c<0>(bs);
      std::ptrdiff_t olow   = boost::fusion::at_c<1>(bs);
      std::ptrdiff_t bound  = boost::fusion::at_c<0>(a0.extent()) + ilow;
      std::ptrdiff_t ibound = ilow + (boost::fusion::at_c<0>(a0.extent())/N) * N;
      std::ptrdiff_t obound = olow + nt2::numel(boost::fusion::pop_front(a0.extent()));

      for(std::ptrdiff_t j=olow; j!=obound; ++j)
      {
        for(std::ptrdiff_t i=ilow; i!=ibound; i+=N)
          nt2::run(a0, boost::fusion::vector_tie(i,j), meta::as_<target_type>());

        for(std::ptrdiff_t i=ibound; i!=bound; ++i)
          nt2::run(a0, boost::fusion::vector_tie(i,j), meta::as_<stype>());
      }

      return boost::proto::child_c<0>(a0);
    }
  };
} }

#endif
