//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_SHARED_MEMORY_OUTER_FOLD_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_SHARED_MEMORY_OUTER_FOLD_HPP_INCLUDED

#include <nt2/core/functions/outer_fold.hpp>
#include <nt2/sdk/shared_memory/shared_memory.hpp>
#include <nt2/sdk/config/cache.hpp>
#include <cstddef>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION_IF ( nt2::tag::outer_fold_, (nt2::tag::shared_memory_<BackEnd,Site>)
                                , (A0)(K0)(S0)(T0)(N0)(A1)(A2)(A3)(BackEnd)(Site)
                                , ( boost::simd::meta::
                                    is_vectorizable < typename A0::value_type
                                                    , BOOST_SIMD_DEFAULT_EXTENSION
                                                    >
                                  )
                                , ((expr_ < container_<K0,unspecified_<A0>,S0>
                                          , T0
                                          , N0
                                          >
                                  ))
                                  ((ast_< A1, nt2::container::domain>))
                                  (unspecified_<A2>)
                                  (unspecified_<A3>)
                                )
  {
    typedef void                                                              result_type;
    typedef typename boost::remove_reference<A1>::type::extent_type           extent_type;

    BOOST_FORCEINLINE result_type operator()(A0& out, A1& in, A2 const& neutral, A3 const& bop) const
    {
      extent_type ext = in.extent();
      std::size_t obound = boost::fusion::at_c<2>(ext);
      std::size_t ibound = boost::fusion::at_c<0>(ext);
      std::size_t top_cache_line_size = config::top_cache_size(2)/sizeof(typename A0::value_type);
      if(!top_cache_line_size) top_cache_line_size = 1u;

      std::size_t a(ibound);
      std::size_t b(top_cache_line_size);
      while (b) {
        std::size_t  r = a % b;
        a = b;
        b = r;
      }

      std::size_t grain = top_cache_line_size/a;

      nt2::worker<tag::outer_fold_,BackEnd,A0,A1,A2,A3> w(out, in, neutral, bop);
      nt2::spawner< tag::parfor_,BackEnd >              s;

      s(w,0,obound,grain);
    }
  };

} }
#endif
