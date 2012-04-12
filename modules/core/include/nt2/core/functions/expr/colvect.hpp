//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPR_COLVECT_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_COLVECT_HPP_INCLUDED

#include <nt2/core/functions/colvect.hpp>

#include <nt2/sdk/memory/copy.hpp>
#include <nt2/core/container/dsl.hpp>
#include <nt2/include/functions/box.hpp>
#include <nt2/include/functions/length.hpp>

namespace nt2 { namespace ext
{
  //============================================================================
  // Generates linearize_ from expression + of_size
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::colvect_, tag::cpu_
                            , (A0)
                            , (ast_<A0>)
                            )
  {
    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::colvect_
                                          , container::domain
                                          , A0 const&
                                          , box<_2D>
                                          >::type             result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      _2D sizee(numel(a0), 1u);                    
      return  boost::proto:: 
              make_expr < nt2::tag::colvect_
                        , container::domain
                        > ( boost::cref(a0), boxify(sizee) );
    }
  };

} }

#endif
