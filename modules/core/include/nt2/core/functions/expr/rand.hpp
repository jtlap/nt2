//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPR_RAND_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_RAND_HPP_INCLUDED

#include <nt2/core/functions/rand.hpp>
#include <nt2/core/utility/randstream.hpp>
#include <nt2/sdk/memory/copy.hpp>
#include <nt2/core/container/dsl.hpp>
#include <nt2/core/utility/box.hpp>
#include <nt2/core/functions/of_size.hpp>
#include <nt2/include/functions/isrow.hpp>
#include <nt2/include/functions/length.hpp>
#include <iterator>

namespace nt2 { namespace ext
{
  //============================================================================
  // Generates rand from expression (support size(a) + type calls)
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::rand_, tag::cpu_
                            , (A0)
                            , (ast_<A0>)
                            )
  {
    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::rand_
                                          , container::domain
                                          , box<of_size_max>
                                          , box< meta::constant_<nt2::tag::Nan> >
                                          , meta::as_<double>
                                          >::type             result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      // Expression must be a row vector
      BOOST_ASSERT_MSG
      ( nt2::isrow(a0)
      , "Error using rand: Size vector must be a row vector."
      );

      of_size_max sizee;
      std::size_t sz = std::min(of_size_max::size(),nt2::length(a0));
      nt2::memory::copy(a0.raw(), a0.raw()+sz, &sizee[0]);

      return boost::proto::make_expr< nt2::tag::rand_
                                    , container::domain
                                    > ( boxify(sizee)
                                      , boxify(meta::constant_<nt2::tag::Nan>())
                                      , meta::as_<double>()
                                      );
    }
  };

  //============================================================================
  // Generates nan from expression (support size(a) + type calls)
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::rand_, tag::cpu_
                            , (A0)(T)
                            , (ast_<A0>)
                              (target_< scalar_< unspecified_<T> > >)
                            )
  {
    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::rand_
                                          , container::domain
                                          , box<of_size_max>
                                          , box< meta::constant_<nt2::tag::Nan> >
                                          , T
                                          >::type             result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, T const& tgt) const
    {
      // Expression must be a row vector
      BOOST_ASSERT_MSG
      ( nt2::isrow(a0)
      , "Error using rand: Size vector must be a row vector."
      );

      of_size_max sizee;
      std::size_t sz = std::min(of_size_max::size(),nt2::length(a0));
      nt2::memory::copy(a0.raw(), a0.raw()+sz, &sizee[0]);

      return boost::proto::make_expr< nt2::tag::rand_
                                    , container::domain
                                    > ( boxify(sizee)
                                      , boxify(meta::constant_<nt2::tag::Nan>())
                                      , tgt
                                      );
    }
  };

  //============================================================================
  // rand  evaluation
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_assign_, tag::cpu_
                            , (A0)(A1)
                            , (ast_<A0>)
                              ((node_< A1, nt2::tag::rand_, boost::mpl::long_<3> >))
                            )
  {
    typedef A0& result_type;

    result_type operator()(A0& a0, A1& a1) const
    {
      a0.resize( boost::proto::value(boost::proto::child_c<0>(a1)) );

      // Forward to current random_stream and fill the data
      current_randstream->rand(a0.raw(),0,nt2::numel(a0));
      return a0;
    }
  };
} }

#endif
