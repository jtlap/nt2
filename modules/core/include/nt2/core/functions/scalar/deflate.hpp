//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_SCALAR_DEFLATE_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_SCALAR_DEFLATE_HPP_INCLUDED

#include <nt2/core/functions/deflate.hpp>
#include <nt2/include/functions/sub2ind.hpp>
#include <boost/fusion/include/value_at.hpp>

namespace nt2 { namespace ext
{
  //============================================================================
  // Case for no base index
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::deflate_, tag::cpu_
                            , (A0)(A1)
                            , (fusion_sequence_<A0>)
                              (fusion_sequence_<A1>)
                            )
  {
    typedef typename boost::fusion::result_of::
                            value_at<A1,boost::mpl::int_<0> >::type index_t;
    typedef boost::fusion::vector<index_t,index_t>                  result_type;

    BOOST_DISPATCH_FORCE_INLINE result_type
    operator()(const A0& size, const A1& pos) const
    {
      index_t const& i = boost::fusion::at_c<0>(pos);

      result_type that( i
                      , sub2ind ( boost::fusion::pop_front(size)
                                , boost::fusion::pop_front(pos)
                                )
                      );
      return that;
    }
  };

  //============================================================================
  // Case for specific base index
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::deflate_, tag::cpu_
                            , (A0)(A1)(A2)
                            , (fusion_sequence_<A0>)
                              (fusion_sequence_<A1>)
                              (fusion_sequence_<A2>)
                            )
  {
    typedef typename boost::fusion::result_of::
                            value_at<A1,boost::mpl::int_<0> >::type index_t;
    typedef boost::fusion::vector<index_t,index_t>                  result_type;

    BOOST_DISPATCH_FORCE_INLINE result_type
    operator()(const A0& size, const A1& pos, const A2& base) const
    {
      index_t const& i = boost::fusion::at_c<0>(pos);

      result_type that( i
                      , sub2ind ( boost::fusion::pop_front(size)
                                , boost::fusion::pop_front(pos)
                                , boost::fusion::pop_front(base)
                                )
                      );
      return that;
    }
  };
} }

#endif
