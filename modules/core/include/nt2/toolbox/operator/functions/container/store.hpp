//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_OPERATOR_FUNCTIONS_CONTAINER_STORE_HPP_INCLUDED
#define NT2_TOOLBOX_OPERATOR_FUNCTIONS_CONTAINER_STORE_HPP_INCLUDED

#include <nt2/core/container/dsl.hpp>
#include <nt2/core/container/category.hpp>
#include <nt2/toolbox/operator/functions/store.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( boost::simd::tag::store_, tag::cpu_
                            , (Container)(Settings)(Position)(Value)
                            , ((ast_<table_<unspecified_<Container>,Settings> >))
                              (fusion_sequence_<Position>)
                              (generic_< arithmetic_<Value> >)
                            )
  {
    typedef Value result_type;
    result_type BOOST_DISPATCH_FORCE_INLINE
    operator()(Container& dst, Position const& pos, Value const& src) const
    {
      // Call the store member of the block held by the container in the AST
      return boost::proto::value(dst).data().store( pos, src );
    }
  };
} }

#endif
