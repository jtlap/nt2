//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_SCALAR_NUMEL_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_SCALAR_NUMEL_HPP_INCLUDED

#include <boost/mpl/size_t.hpp>
#include <nt2/core/functions/numel.hpp>
#include <boost/fusion/include/fold.hpp>
#include <nt2/include/functions/multiplies.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::numel_, tag::cpu_
                            , (A0), (scalar_< unspecified_<A0> >)
                            )
  {
    typedef boost::mpl::size_t<1> result_type;

    BOOST_DISPATCH_FORCE_INLINE
    result_type operator()(const A0&) const { return result_type(); }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::numel_, tag::cpu_
                            , (A0)
                            , (fusion_sequence_<A0>)
                            )
  {
    typedef typename  boost::dispatch::
                      make_functor<tag::multiplies_,A0>::type       func_t;
    typedef typename  boost::fusion::result_of::
                      fold<A0,boost::mpl::size_t<1>,func_t>::type   result_type;

    BOOST_DISPATCH_FORCE_INLINE
    result_type operator()(const A0& a0) const
    {
      return boost::fusion::fold( a0
                                , boost::mpl::size_t<1>()
                                , func_t()
                                );
    }
  };
} }

#endif
