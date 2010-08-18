/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_MEMORY_PADDING_HPP_INCLUDED
#define NT2_SDK_MEMORY_PADDING_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Padding strategies for memory allocation
////////////////////////////////////////////////////////////////////////////////
#include <functional>
#include <boost/mpl/pair.hpp>
#include <boost/fusion/include/at.hpp>
#include <boost/fusion/include/fold.hpp>
#include <boost/fusion/include/value_at.hpp>

////////////////////////////////////////////////////////////////////////////////
// Settings tag
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace tag { struct padding {}; } }

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

    template<class T> typename boost::fusion::result_of::value_at_c<T,0>::type
    size(T const& sz) const
    {
      typedef typename boost::fusion::result_of::value_at_c<T,0>::type type;
      return boost::fusion::fold(sz,1,std::multiplies<type>());
    }

    template<class T> typename boost::fusion::result_of::value_at_c<T,0>::type
    stride(T const& sz) const
    {
      return boost::fusion::at_c<0>(sz);
    }
  };

  //////////////////////////////////////////////////////////////////////////////
  // Lead padding: the leading dimension is padded
  //////////////////////////////////////////////////////////////////////////////
  struct lead_padding
  {
    typedef boost::mpl::pair<tag::padding,lead_padding> nt2_settings_type;

    template<class T> typename boost::fusion::result_of::value_at_c<T,0>::type
    size(T szs) const
    {
      typedef typename boost::fusion::result_of::value_at_c<T,0>::type type;
      boost::fusion::at_c<0>(szs) = align_on(boost::fusion::at_c<0>(szs));
      return boost::fusion::fold(szs,1,std::multiplies<type>());
    }

    template<class T> typename boost::fusion::result_of::value_at_c<T,0>::type
    stride(T const& szs) const
    {
      return align_on(boost::fusion::at_c<0>(szs));
    }
  };

  //////////////////////////////////////////////////////////////////////////////
  // Global padding: there is padding only at the end of the memory buffer
  //////////////////////////////////////////////////////////////////////////////
  struct global_padding
  {
    typedef boost::mpl::pair<tag::padding,global_padding> nt2_settings_type;

    template<class T> typename boost::fusion::result_of::value_at_c<T,0>::type
    size(T const& szs)
    {
      typedef typename boost::fusion::result_of::value_at_c<T,0>::type type;
      return align_on(boost::fusion::fold(szs,1,std::multiplies<type>()));
    }

    template<class T> typename boost::fusion::result_of::value_at_c<T,0>::type
    stride(T const& szs)
    {
      return boost::fusion::at_c<0>(szs);
    }
  };
} }

#endif
