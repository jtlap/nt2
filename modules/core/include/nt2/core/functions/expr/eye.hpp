//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPR_EYE_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_EYE_HPP_INCLUDED

#include <nt2/core/container/dsl.hpp>
#include <nt2/core/functions/eye.hpp>
#include <nt2/include/functions/box.hpp>
#include <nt2/core/functions/of_size.hpp>
#include <nt2/include/functions/isrow.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/include/functions/length.hpp>
#include <nt2/include/functions/size.hpp>
#include <nt2/include/functions/first_index.hpp>

namespace nt2 { namespace ext
{
  //============================================================================
  // Generates eye from expression (support size(a) + type calls)
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::eye_, tag::cpu_
                            , (A0)
                            , (ast_<A0>)
                            )
  {
    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::eye_
                                          , container::domain
                                          , box<of_size_<1,2> >
                                          , box<nt2::details::eye>
                                          , meta::as_<double>
                                          >::type             result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      // Expression must be a row vector
      BOOST_ASSERT_MSG
        ( nt2::isrow(a0) // && (nt2::numel(a0) <= 2)
          , "Error using eye: Size vector must be a row vector of at most 2 elements."
          );
      
      of_size_<1, 2> sizee;
      const int first = nt2::first_index<1>(a0); 
      for(int i=0;i<2;++i) sizee[i] = a0(first+i);
      
      return boost::proto::make_expr< nt2::tag::eye_
        , container::domain
        > ( boxify(sizee)
            , boxify(nt2::details::eye())
            , meta::as_<double>()
            );
    }
  };

  //============================================================================
  // Generates eye from expression (support size(a) + type calls)
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::eye_, tag::cpu_
                            , (A0)(T)
                            , (ast_<A0>) 
                              (target_< scalar_< unspecified_<T> > >)
                            )
  {
    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::eye_
                                          , container::domain
                                          , box<of_size_<1,2> >
                                          , box<nt2::details::eye>
                                          , T
                                          >::type             result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, T const& ) const
    {
      // Expression must be a row vector
      BOOST_ASSERT_MSG
        ( nt2::isrow(a0)// && (nt2::numel(a0) <= 2)
          , "Error using eye: Size vector must be a row vector of at most 2 elements."
          );

      of_size_<1,2> sizee;
      const int first = nt2::first_index<1>(a0); 
      for(int i=0;i<2;++i) sizee[i] = a0(first+i);
      
      return boost::proto::make_expr< nt2::tag::eye_
        , container::domain
        > ( boxify(sizee)
            , boxify(nt2::details::eye())
            , T()
            );
    }
  };
} }

#endif
