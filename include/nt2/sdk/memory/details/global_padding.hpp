/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_MEMORY_GLOBAL_PADDING_HPP_INCLUDED
#define NT2_SDK_MEMORY_GLOBAL_PADDING_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Global Padding strategy for memory allocation
////////////////////////////////////////////////////////////////////////////////
#include <functional>
#include <boost/mpl/pair.hpp>
#include <nt2/sdk/memory/align_on.hpp>
#include <boost/fusion/include/at.hpp>
#include <boost/fusion/include/fold.hpp>
#include <nt2/sdk/memory/details/times.hpp>
#include <boost/fusion/include/value_at.hpp>

namespace nt2 { namespace memory
{
  //////////////////////////////////////////////////////////////////////////////
  // Global padding: there is padding only at the end of the memory buffer
  //////////////////////////////////////////////////////////////////////////////
  struct global_padding
  {
    typedef boost::mpl::pair<tag::padding,global_padding> nt2_settings_type;

    struct size
    {
      template<class Sig> struct result;
      template<class This,class Seq>
      struct  result<This(Seq)>
      : boost
      ::result_of < result::align_on( typename boost::fusion
                                        ::result_of::fold < Seq
                                                          , boost::mpl::int_<1>
                                                          , nt2::details::times
                                                          >::type
                                    )
                  >
      {};

      template<class Seq> typename result<size(Seq)>::type
      inline operator()(Seq const& sz) const
      {
        nt2::details::times callee;
        return align_on(boost::fusion::fold(sz, boost::mpl::int_<1>(), callee));
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
