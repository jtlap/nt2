/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_MEMORY_SLICE_HPP_INCLUDED
#define NT2_SDK_MEMORY_SLICE_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Compute the number of slice between inner adn the Nth outer dimension
////////////////////////////////////////////////////////////////////////////////
#include <boost/mpl/size_t.hpp>
#include <nt2/sdk/meta/mpl.hpp>
#include <nt2/sdk/meta/fusion.hpp>
#include <nt2/sdk/memory/padding.hpp>
#include <nt2/sdk/functor/functor.hpp>
#include <boost/fusion/include/size.hpp>
#include <nt2/sdk/memory/details/category.hpp>
#include <nt2/sdk/functor/preprocessor/function.hpp>

namespace nt2
{
  namespace tag { struct slice_ {}; }

  //////////////////////////////////////////////////////////////////////////////
  // slice computes the potential padded product of all dimensions in a given
  // dimension set from the Nth.
  //////////////////////////////////////////////////////////////////////////////
  template<std::size_t N, class Seq,class Padding> inline
  typename boost::
  lazy_enable_if_c< (boost::fusion::result_of::size<Seq>::value >= N)
                  , nt2::meta
                    ::enable_call < tag::slice_ ( Seq const&
                                                , Padding const&
                                                , boost::mpl::size_t<N> const&
                                                )
                                  >
                  >::type
  slice(Seq const& s, Padding const& p)
  {
    functor<tag::slice_> callee;
    return callee(s,p,boost::mpl::size_t<N>() );
  }

  //////////////////////////////////////////////////////////////////////////////
  // slice computes the potential padded product of all dimensions in a given
  // dimension set from the Nth. As N is larger than the dimension set size, we
  // naturally return 1.
  //////////////////////////////////////////////////////////////////////////////
  template<std::size_t N, class Seq,class Padding> inline
  typename boost::
  lazy_enable_if_c< !(boost::fusion::result_of::size<Seq>::value >= N)
                  , boost::mpl::int_<1>
                  >::type
  slice(Seq const& , Padding const& )
  {
    return boost::mpl::int_<1>();
  }
}

////////////////////////////////////////////////////////////////////////////////
// slice dispatch on basic padding strategy
////////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH ( tag::slice_, tag::cpu_
                      , (A0)(A1)(A2)
                      , (fusion_sequence_<A0>)
                        (padding_<A1>)
                        (mpl_integral_< integer_<A2> >)
                      )
#endif
