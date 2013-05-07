//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_SCALAR_LENGTH_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_SCALAR_LENGTH_HPP_INCLUDED

#include <nt2/core/functions/length.hpp>
#include <boost/mpl/size_t.hpp>
#include <nt2/core/functions/length.hpp>
#include <nt2/include/functions/scalar/max.hpp>
#include <boost/fusion/include/fold.hpp>
#include <boost/fusion/include/front.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::length_, tag::cpu_
                            , (A0), (scalar_< unspecified_<A0> >)
                            )
  {
    typedef boost::mpl::size_t<1> result_type;

    BOOST_DISPATCH_FORCE_INLINE
    result_type operator()(const A0&) const { return result_type(); }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::length_, tag::cpu_
                            , (A0)
                            , (fusion_sequence_<A0>)
                            )
  {
    typedef typename  boost::dispatch::make_functor<tag::max_,A0>::type func_t;
    typedef typename  boost::fusion::result_of::
                      front<A0>::type   first;
    typedef typename  boost::fusion::result_of::
                      fold<A0,first,func_t>::type   result_type;

    BOOST_DISPATCH_FORCE_INLINE
    result_type operator()(const A0& a0) const
    {
      return boost::fusion::fold( a0
                                , boost::fusion::front(a0)
                                , func_t()
                                );
    }
  };
} }

#endif
