//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_SCALAR_ZEROS_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_SCALAR_ZEROS_HPP_INCLUDED

#include <nt2/core/container/dsl.hpp>
#include <nt2/core/functions/zeros.hpp>
#include <nt2/core/functions/of_size.hpp>
#include <nt2/core/utility/generator/generator.hpp>
#include <nt2/core/utility/generator/preprocessor.hpp>
#include <nt2/core/utility/generator/constant_adaptor.hpp>

namespace nt2 { namespace ext
{
  //============================================================================
  // Generates all integral set + types overload
  //============================================================================
  BOOST_PP_REPEAT_FROM_TO ( 1
                          , BOOST_PP_INC(NT2_MAX_DIMENSIONS)
                          , NT2_PP_GENERATIVE_MAKE_FROM_SIZE
                          , nt2::tag::Zero
                          )

  //============================================================================
  // Generates zeros from fusion sequence (support of_size calls)
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::Zero, tag::cpu_
                            , (Seq), (fusion_sequence_<Seq>)
                            )
  {
    typedef typename boost::fusion::result_of::size<Seq>::type size_type;
    typedef nt2::details::
            generator < nt2::tag::table_
                      , nt2::details::constant_generator<nt2::tag::Zero>
                      , double
                      , settings(typename make_size<size_type::value>::type)
                      > base;

    typedef typename boost::proto::terminal<base>::type  expr_type;
    typedef typename boost::
            result_of<container::domain(expr_type)>::type const result_type;

    BOOST_FORCEINLINE result_type operator()(Seq const& seq) const
    {
      container::domain domain_;
      nt2::details::constant_generator<nt2::tag::Zero> callee;
      typename make_size<size_type::value>::type sizee(seq);

      return domain_( expr_type::make( base(sizee,callee) ) );
    }
  };

  //============================================================================
  // Generates zeros from fusion sequence + types(support of_size calls)
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::Zero, tag::cpu_
                            , (Seq)(T)
                            , (fusion_sequence_<Seq>)
                              (target_< scalar_< unspecified_<T> > >)
                            )
  {
    typedef typename boost::fusion::result_of::size<Seq>::type size_type;
    typedef nt2::details::
            generator < nt2::tag::table_
                      , nt2::details::constant_generator<nt2::tag::Zero>
                      , typename T::type
                      , settings(typename make_size<size_type::value>::type)
                      > base;

    typedef typename boost::proto::terminal<base>::type  expr_type;
    typedef typename boost::
            result_of<container::domain(expr_type)>::type const result_type;

    BOOST_FORCEINLINE result_type operator()(Seq const& seq, T const&) const
    {
      container::domain domain_;
      nt2::details::constant_generator<nt2::tag::Zero> callee;
      typename make_size<size_type::value>::type sizee(seq);

      return domain_( expr_type::make( base(sizee,callee) ) );
    }
  };
} }

#endif
