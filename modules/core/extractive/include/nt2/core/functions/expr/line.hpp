//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPR_LINE_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_LINE_HPP_INCLUDED

#include <nt2/core/functions/line.hpp>
#include <nt2/core/container/dsl.hpp>
#include <nt2/include/functions/linesstride.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::line_, tag::cpu_
                            , (A0)(A1)(A2)
                            , ((ast_<A0, nt2::container::domain>))
                              (scalar_<arithmetic_<A1> > )
                              (scalar_<integer_<A2> > )
                            )
  {
    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::line_
                                          , container::domain
                                          , A0 const&
                                          , std::size_t
                                          , std::size_t
                                          , std::size_t
                                          , std::size_t
                                          >::type             result_type;

    BOOST_FORCEINLINE
    result_type operator()(A0 const& a0, A1 const& ind, A2 const& dim) const
    {
      typedef typename A0::extent_type ext_t;
      typedef typename meta::call<nt2::tag::ind2sub_(ext_t,size_t)>::type  sub_t;

      ext_t ex1 = a0.extent();
      std::size_t along = dim-1;
      ex1[along] = 1;
      sub_t pos = ind2sub(ex1, ind);
      std::size_t start = sub2ind(a0.extent(), pos);
      std::size_t stride = nt2::linesstride(a0, dim);

      return boost::proto::make_expr< nt2::tag::line_
                                    , container::domain
                                    > ( boost::cref(a0)
                                      , along
                                      , std::size_t(ind)
                                      , start
                                      , stride
                                      );
    }
  };
} }

#endif
