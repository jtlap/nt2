//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_LINALG_FUNCTIONS_DETAILS_QR_PIVOT_HPP_INCLUDED
#define NT2_TOOLBOX_LINALG_FUNCTIONS_DETAILS_QR_PIVOT_HPP_INCLUDED

#include <nt2/linalg/options.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/inv.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/fliplr.hpp>
#include <nt2/include/functions/inv.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/core/container/dsl/forward.hpp>
#include <nt2/core/container/table/table.hpp>

namespace nt2 { namespace ext
{
  /// INTERNAL ONLY - Helper to extract permutation matrix
  template<typename A1> BOOST_FORCEINLINE
  void extract_p( A1& a1, nt2::container::table<nt2_la_int>& ip
                , nt2::policy<ext::vector_> const&
                )
  {
    boost::proto::child_c<2>(a1) = ip;
  }

  /// INTERNAL ONLY - Helper to extract permutation matrix
  template<typename A1>BOOST_FORCEINLINE
  void extract_p( A1& a1, nt2::container::table<nt2_la_int>& ip
                , int const&
                )
  {
    boost::proto::child_c<2>(a1) = ip;
  }

  /// INTERNAL ONLY - Helper to extract permutation matrix
  template<typename A1>BOOST_FORCEINLINE
  void extract_p( A1& a1, nt2::container::table<nt2_la_int>&
                , nt2::policy<ext::no_pivot_> const&
                )
  {
    nt2_la_int n = nt2::width(boost::proto::child_c<1>(a1));
    boost::proto::child_c<2>(a1) = nt2::eye(n,n);
  }

  /// INTERNAL ONLY - Helper to extract permutation matrix
  template<typename A1, typename Policy> BOOST_FORCEINLINE
  void extract_p( A1& a1, nt2::container::table<nt2_la_int>& ip
                , Policy const&
                )
  {
    typedef typename boost::proto::result_of
                               ::child_c<A1&,2>::value_type::value_type t_t;

    std::size_t d = nt2::numel(ip);
    boost::proto::child_c<2>(a1) = nt2::zeros(d,meta::as_<t_t>());

    for(std::size_t i = 1; i<= d;++i)
      boost::proto::child_c<2>(a1)(ip(i),i) = 1;
  }
} }

#endif
