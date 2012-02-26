//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_CORE_FUNCTIONS_SCALAR_LENGTH_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_SCALAR_LENGTH_HPP_INCLUDED

#include <boost/mpl/size_t.hpp>
#include <nt2/core/functions/length.hpp>
#include <nt2/include/functions/max.hpp>
#include <boost/fusion/include/fold.hpp>

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
