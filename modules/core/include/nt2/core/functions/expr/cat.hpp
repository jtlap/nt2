//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPR_CAT_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_CAT_HPP_INCLUDED

#include <nt2/core/functions/cat.hpp>
#include <nt2/core/functions/common/cat.hpp>
#include <nt2/include/functions/arecatcompatible.hpp>

#include <nt2/sdk/memory/copy.hpp>
#include <nt2/core/container/dsl.hpp>
#include <nt2/core/utility/box.hpp>
#include <nt2/core/functions/of_size.hpp>
#include <nt2/include/functions/length.hpp>

namespace nt2 { namespace ext
{

  //============================================================================
  // Generates linearize_ from 2 expressions
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::cat_, tag::cpu_,
                              (A0)(A1)(A2),
                              (scalar_<integer_<A0> >)
                              (ast_<A1>)
                              (ast_<A2>)
                            )
  {
    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::cat_
                                          , container::domain
                                          , A1 const&
                                          , A2 const&
                                          , std::size_t      
                                          , box<of_size_max>
                                          >::type             result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0,A1 const& a1,A2 const& a2) const
    {
      std::cout << "a0 " << a0 << std::endl; 
//       BOOST_ASSERT_MSG(arecatcompatible(a1, a2, a0),
//                        "cat arguments dimensions are not consistent."); 
      // Expressions must be  matrices
      size_t along = a0-1; 
      of_size_max sizee = of_size_max(a1.extent());
      sizee[along] += a2.extent()[along];
      return boost::proto::make_expr<nt2::tag::cat_, container::domain>
        (boost::cref(a1),boost::cref(a2), along, boxify(sizee));
    }
  };
  
} } 

#endif
