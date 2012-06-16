//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_COMMON_TRANS_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_COMMON_TRANS_HPP_INCLUDED

#include <nt2/table.hpp>
#include <nt2/core/functions/trans.hpp>
#include <nt2/core/functions/height.hpp>
#include <nt2/core/functions/width.hpp>


namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::trans_, tag::cpu_,
                              (A0),
                              (ast_<A0>) )
  {
    typedef typename meta::strip<A0>::type                  source_t;
    typedef typename source_t::value_type                     type_t;
    typedef typename source_t::index_type                    index_t;
    typedef nt2::table < type_t, index_t>                result_type;
    typedef nt2::table < type_t>                                tab_; 

    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      tab_t ta = zeros(width(a), height(a), meta::as_<type_t>());
      for (int i = first_index<1>(a); i <= last_index<1>(a); ++i)
        for (int j = first_index<2>(a); j <= last_index<2>(a); ++j)
          ta(j, i) = a0(i, j);
      return ta;
    }
  };
} }

#endif
