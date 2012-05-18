//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPR_FILL_PATTERN_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_FILL_PATTERN_HPP_INCLUDED

#include <nt2/core/functions/fill_pattern.hpp>
#include <nt2/core/functions/common/fill_pattern.hpp>

#include <nt2/sdk/memory/copy.hpp>
#include <nt2/core/container/dsl.hpp>
#include <nt2/core/utility/box.hpp>
#include <nt2/include/functions/length.hpp>
#include <nt2/include/functions/repmat.hpp>
#include <nt2/sdk/meta/cardinal_of.hpp>
#include <nt2/table.hpp>

namespace nt2 { namespace ext
{
  //============================================================================
  // Generates linearize_ from expression + of_size
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::fill_pattern_, tag::cpu_
                            , (A0)(A1)
                            , (ast_<A0>)
                              (fusion_sequence_<A1>)
                            )
  {
    typedef typename A0::value_type               value_type; 
    typedef nt2::table<value_type>                     tab_t; 
    typedef typename boost::remove_const<A1>::type   sizes_t;
    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::fill_pattern_
                                          , container::domain
                                          , tab_t const&
                                          , box<sizes_t>
                                          >::type             result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const& a1) const
    {
      typedef typename meta::as_integer<value_type>::type        i_t;
      std::size_t n = meta::cardinal_of<i_t>::value/numel(a0)+
        (numel(a0) != meta::cardinal_of<i_t>::value);
      tab_t p = nt2::repmat(a0,1,n); 
      return  boost::proto::
              make_expr < nt2::tag::fill_pattern_
                        , container::domain
        > ( boost::cref(p), boxify(a1) );
    }
  };

  //============================================================================
  // Generates linearize_ from expression + expression containing size
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::fill_pattern_, tag::cpu_
                            , (A0)(A1)
                            , (ast_<A0>)
                              (ast_<A1>)
                            )
  {
    typedef typename A0::value_type               value_type; 
    typedef nt2::table<value_type>                     tab_t; 
    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::fill_pattern_
                                          , container::domain
                                          , tab_t const&
                                          , box<of_size_max>
                                          >::type             result_type;

    BOOST_FORCEINLINE result_type operator()(A0& a0, A1 const& a1) const
    {
      typedef typename A0::value_type value_type; 
      typedef typename meta::as_integer < value_type>::type              i_t;
      std::size_t n = meta::cardinal_of<i_t>::value/numel(a0)+
        (numel(a0) != meta::cardinal_of<i_t>::value); 
      of_size_max sizee;
      std::size_t sz = std::min(of_size_max::size(),nt2::length(a1));
      nt2::memory::copy(a1.raw(), a1.raw()+sz, &sizee[0]);
      tab_t p = nt2::repmat(a0,1,n); 

      return  boost::proto::
              make_expr < nt2::tag::fill_pattern_
                        , container::domain
                        > ( boost::cref(p), boxify(sizee) );
    }
  };
} }

#endif
