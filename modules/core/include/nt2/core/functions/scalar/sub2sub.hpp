//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_SCALAR_SUB2SUB_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_SCALAR_SUB2SUB_HPP_INCLUDED

#include <nt2/core/functions/sub2sub.hpp>
#include <nt2/include/functions/sub2ind.hpp>
#include <nt2/include/functions/ind2sub.hpp>

namespace nt2 { namespace ext
{
  //============================================================================
  // Case for no base index
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::sub2sub_, tag::cpu_
                            , (A0)(A1)(A2)
                            , (fusion_sequence_<A0>)
                              (fusion_sequence_<A1>)
                              (fusion_sequence_<A2>)
                            )
  {
    typedef boost::array<int, boost::fusion::result_of::size<A2>::value> result_type;

    BOOST_DISPATCH_FORCE_INLINE result_type
    operator()(const A0& sizein, const A1& pos, const A2& sizeout) const
    {
      return ind2sub(sizeout, sub2ind(sizein, pos));
    }
  };
} }

#endif
