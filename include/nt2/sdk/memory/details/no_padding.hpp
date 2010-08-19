/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_MEMORY_NO_PADDING_HPP_INCLUDED
#define NT2_SDK_MEMORY_NO_PADDING_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Padding strategies for memory allocation
////////////////////////////////////////////////////////////////////////////////
#include <functional>
#include <boost/mpl/pair.hpp>
#include <nt2/sdk/memory/align_on.hpp>
#include <boost/fusion/include/at.hpp>
#include <boost/fusion/include/fold.hpp>
#include <nt2/sdk/memory/details/times.hpp>
#include <boost/fusion/include/value_at.hpp>
#include <boost/fusion/include/pop_front.hpp>

////////////////////////////////////////////////////////////////////////////////
// Various pre-made padding strategies
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace memory
{
  //////////////////////////////////////////////////////////////////////////////
  // No padding: all data are allocated as specified
  //////////////////////////////////////////////////////////////////////////////
  struct no_padding
  {
    typedef boost::mpl::pair<tag::padding,no_padding> nt2_settings_type;

    struct size
    {
      template<class Sig> struct result;
      template<class This,class Seq>
      struct  result<This(Seq)>
            : boost::fusion::result_of::fold< Seq
                                            , boost::mpl::int_<1>
                                            , nt2::details::times
                                            >
      {};

      template<class Seq> typename result<size(Seq)>::type
      inline operator()(Seq const& sz) const
      {
        nt2::details::times callee;
        return boost::fusion::fold(sz, boost::mpl::int_<1>(), callee);
      }
    };

    struct stride
    {
      template<class Sig> struct result;
      template<class This,class Seq>
      struct  result<This(Seq)>
            : boost::fusion::result_of::value_at_c<Seq,0>
      {};

      template<class Seq> typename result<stride(Seq)>::type
      inline operator()(Seq const& sz) const
      {
        return boost::fusion::at_c<0>(sz);
      }
    };
  };
} }

#endif
