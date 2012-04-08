//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPR_SQUEEZE_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_SQUEEZE_HPP_INCLUDED

#include <nt2/core/functions/squeeze.hpp>

#include <nt2/sdk/memory/copy.hpp>
#include <nt2/core/container/dsl.hpp>
#include <nt2/include/functions/box.hpp>
#include <nt2/include/functions/length.hpp>

namespace nt2 { namespace ext
{
  //============================================================================
  // Generates squeeze
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::squeeze_, tag::cpu_
                            , (A0)
                            , (ast_<A0>)
                            )
  {
    typedef typename boost::remove_const<A0>::type::extent_type extent_type;
    typedef typename meta::strip<extent_type>::type             sizes_t;

    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::squeeze_
                                          , container::domain
                                          , A0 const&
                                          , box<sizes_t>
                                          >::type             result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      sizes_t sizee;
      extent_type e = a0.extent();

      // Squeeze don't affect 2D array
      if(sizes_t::static_size <= 2)
      {
        sizee = e;
      }
      else
      {
        // Copy non singleton dimensions
        std::size_t u = 0;
        for(std::size_t i=0;i<sizes_t::static_size;++i)
        {
          if(e[i] != 1) { sizee[u] = e[i]; ++u; }
        }

        // Ensure non-empty size
        sizee[0] = sizee[0] ? sizee[0] : 1;
      }

      return  boost::proto::
              make_expr < nt2::tag::squeeze_
                        , container::domain
                        > ( boost::cref(a0), boxify(sizee) );
    }
  };
} }

#endif
