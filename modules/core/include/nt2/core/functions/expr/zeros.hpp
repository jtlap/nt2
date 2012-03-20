//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPR_ZEROS_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_ZEROS_HPP_INCLUDED

#include <nt2/core/container/dsl.hpp>
#include <nt2/core/functions/zeros.hpp>
#include <nt2/include/functions/box.hpp>
#include <nt2/core/functions/of_size.hpp>
#include <nt2/include/functions/isrow.hpp>
#include <nt2/include/functions/length.hpp>
#include <boost/detail/workaround.hpp>
#include <iterator>

namespace nt2 { namespace ext
{
  //============================================================================
  // Generates zeros from expression (support size(a) + type calls)
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::zeros_, tag::cpu_
                            , (A0)
                            , (ast_<A0>)
                            )
  {
    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::zeros_
                                          , container::domain
                                          , box<of_size_max>
                                          , box< meta::constant_<nt2::tag::Zero> >
                                          , meta::as_<double>
                                          >::type             result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      // Expression must be a row vector
      BOOST_ASSERT_MSG
      ( nt2::isrow(a0)
      , "Error using zeros: Size vector must be a row vector."
      );

      of_size_max sizee;
      std::size_t sz = std::min(of_size_max::size(),nt2::length(a0));
#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400) && BOOST_WORKAROUND(BOOST_MSVC, < 1600)
      stdext::unchecked_copy(a0.raw(), a0.raw()+sz, &sizee[0]);
#elif BOOST_WORKAROUND(BOOST_MSVC, > 1500)
      std::copy(a0.raw(), a0.raw()+sz, stdext::make_unchecked_array_iterator(&sizee[0]));
#else
      std::copy(a0.raw(), a0.raw()+sz, &sizee[0]);
#endif

      return boost::proto::make_expr< nt2::tag::zeros_
                                    , container::domain
                                    > ( boxify(sizee)
                                      , boxify(meta::constant_<nt2::tag::Zero>())
                                      , meta::as_<double>()
                                      );
    }
  };

  //============================================================================
  // Generates zeros from expression (support size(a) + type calls)
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::zeros_, tag::cpu_
                            , (A0)(T)
                            , (ast_<A0>)
                              (target_< scalar_< unspecified_<T> > >)
                            )
  {
    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::zeros_
                                          , container::domain
                                          , box<of_size_max>
                                          , box< meta::constant_<nt2::tag::Zero> >
                                          , T
                                          >::type             result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, T const& tgt) const
    {
      // Expression must be a row vector
      BOOST_ASSERT_MSG
      ( nt2::isrow(a0)
      , "Error using zeros: Size vector must be a row vector."
      );

      of_size_max sizee;
      std::size_t sz = std::min(of_size_max::size(),nt2::length(a0));
#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400) && BOOST_WORKAROUND(BOOST_MSVC, < 1600)
      stdext::unchecked_copy(a0.raw(), a0.raw()+sz, &sizee[0]);
#elif BOOST_WORKAROUND(BOOST_MSVC, > 1500)
      std::copy(a0.raw(), a0.raw()+sz, stdext::make_unchecked_array_iterator(&sizee[0]));
#else
      std::copy(a0.raw(), a0.raw()+sz, &sizee[0]);
#endif

      return boost::proto::make_expr< nt2::tag::zeros_
                                    , container::domain
                                    > ( boxify(sizee)
                                      , boxify(meta::constant_<nt2::tag::Zero>())
                                      , tgt
                                      );
    }
  };
} }

#endif
