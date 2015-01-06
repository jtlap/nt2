//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2014   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_PREDICATES_FUNCTIONS_TABLE_ISBAND_HPP_INCLUDED
#define NT2_PREDICATES_FUNCTIONS_TABLE_ISBAND_HPP_INCLUDED

#include <nt2/predicates/functions/isband.hpp>
#include <nt2/include/functions/ismatrix.hpp>
#include <nt2/include/functions/isequal.hpp>
#include <nt2/include/functions/from_diag.hpp>
#include <nt2/include/functions/bandwidth.hpp>
#include <nt2/include/functions/diag_of.hpp>
#include <nt2/include/functions/expand.hpp>
#include <nt2/include/functions/size.hpp>
#include <nt2/include/functions/is_eqz.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/max.hpp>
#include <boost/fusion/include/vector_tie.hpp>

namespace nt2 { namespace ext
{
  BOOST_DISPATCH_IMPLEMENT  ( isband_, tag::cpu_
                            , (A0)(A1)(A2)
                            , ((ast_<A0, nt2::container::domain>))
                              (scalar_ < integer_<A1> > )
                              (scalar_ < integer_<A2> > )
                            )
  {
    typedef bool result_type;
    BOOST_FORCEINLINE result_type operator()(const A0& a0, const A1& l, const A2& u) const
    {
      A1 ll;
      A2 uu;
      boost::fusion::vector_tie(ll, uu) = bandwidth(a0);
      return (l <= ll)&&(uu <= u);
    }
  };
} }

#endif
