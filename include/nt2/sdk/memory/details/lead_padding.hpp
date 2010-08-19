/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_MEMORY_LEAD_PADDING_HPP_INCLUDED
#define NT2_SDK_MEMORY_LEAD_PADDING_HPP_INCLUDED

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
  // Lead padding: the leading dimension is padded
  //////////////////////////////////////////////////////////////////////////////
  struct lead_padding
  {
    typedef boost::mpl::pair<tag::padding,lead_padding> nt2_settings_type;

    struct size
    {
      template<class Sig> struct result;
      template<class This,class Seq>
      struct  result<This(Seq)>
      {
        typedef typename boost::fusion::result_of::value_at_c<Seq,0>::type  elem0;
        typedef typename boost::fusion::result_of
                ::fold<
                        typename boost::fusion::result_of::pop_front<Seq>::type
                      , boost::mpl::int_<1>
                      , details::times
                      >::type                                               base;

        typedef typename
                boost::result_of<nt2::result::align_on(elem0)>::type        first;

        typedef typename boost::result_of<details::times(first,base)>::type type;
      };

      template<class Seq> typename result<size(Seq)>::type
      inline operator()(Seq const& sz) const
      {
        nt2::details::times callee;
        return callee ( align_on(boost::fusion::at_c<0>(sz))
                      , boost::fusion::fold ( boost::fusion::pop_front(sz)
                                            , boost::mpl::int_<1>()
                                            , callee
                                            )
                      );
      }
    };

    struct stride
    {
      template<class Sig> struct result;
      template<class This,class Seq>
      struct  result<This(Seq)>
            : boost::result_of<
                  nt2::result::align_on (
                        typename boost::fusion::result_of::value_at_c<Seq,0>::type
                                        )
                              >
      {};

      template<class Seq> typename result<stride(Seq)>::type
      inline operator()(Seq const& sz) const
      {
        return align_on(boost::fusion::at_c<0>(sz));
      }
    };
  };
} }

#endif
