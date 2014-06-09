//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_TABLE_DETAILS_IS_DEFINITELY_VECTOR_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_TABLE_DETAILS_IS_DEFINITELY_VECTOR_HPP_INCLUDED

#include <nt2/sdk/meta/safe_at.hpp>
#include <boost/mpl/bool.hpp>

namespace nt2 { namespace details
{
  template<class Seq>
  struct is_definitely_not_vector
  {
    static const std::size_t n = Seq::static_size;
    static const bool value = n == 0 || (n > 1 && meta::mpl_safe_at_c<typename Seq::values_type, 1, boost::mpl::long_<1> >::type::value != -1);
    typedef boost::mpl::bool_<value> type;
  };

  template<class Seq>
  struct is_definitely_vector
  {
    static const std::size_t n = Seq::static_size;
    static const bool value = n <= 1u || (n == 2u && meta::mpl_safe_at_c<typename Seq::values_type, 0, boost::mpl::long_<1> >::type::value == 1);
    typedef boost::mpl::bool_<value> type;
  };

  template<class Seq>
  struct is_definitely_col_vector
       : boost::mpl::false_
  {
  };

  template<std::ptrdiff_t N>
  struct is_definitely_col_vector< nt2::of_size_<N> >
       : boost::mpl::true_
  {
  };

  template<class Seq>
  struct is_definitely_row_vector
       : boost::mpl::false_
  {
  };

  template<std::ptrdiff_t N>
  struct is_definitely_row_vector< nt2::of_size_<1, N> >
       : boost::mpl::true_
  {
  };
} }

#endif
