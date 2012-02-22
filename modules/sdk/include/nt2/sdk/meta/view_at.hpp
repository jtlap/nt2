//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_META_VIEW_AT_HPP_INCLUDED
#define NT2_SDK_META_VIEW_AT_HPP_INCLUDED

#include <boost/fusion/include/at.hpp>
#include <boost/fusion/include/single_view.hpp>

namespace nt2 { namespace meta
{
  template<std::size_t N,class Seq>
  boost::fusion::
  single_view< typename boost::fusion::result_of::at_c<Seq, N>::type >
  view_at( Seq& seq )
  {
    typedef typename boost::fusion::result_of::at_c<Seq, N>::type base;
    return boost::fusion::single_view<base>( boost::fusion::at_c<N>(seq) );
  }

  template<std::size_t N,class Seq>
  boost::fusion::
  single_view< typename boost::fusion::result_of::at_c<Seq const, N>::type >
  view_at( Seq const& seq )
  {
    typedef typename boost::fusion::result_of::at_c<Seq const, N>::type base;
    return boost::fusion::single_view<base>( boost::fusion::at_c<N>(seq) );
  }
} }

#endif
