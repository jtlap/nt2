//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================

#ifndef NT2_CORE_FUNCTIONS_COMMON_ISDIAGONAL_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_COMMON_ISDIAGONAL_HPP_INCLUDED

#include <nt2/core/functions/isdiagonal.hpp>
#include <nt2/include/functions/ismatrix.hpp>
#include <nt2/include/functions/isequal.hpp>
#include <nt2/include/functions/from_diag.hpp>
#include <nt2/include/functions/diag_of.hpp>
#include <nt2/include/functions/expand.hpp>
#include <nt2/include/functions/size.hpp>
#include <nt2/include/functions/is_eqz.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/max.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::isdiagonal_, tag::cpu_
                            , (A0)
                            , ((ast_<A0, nt2::container::domain>))
                            )
  {
    typedef bool result_type;
    BOOST_DISPATCH_FORCE_INLINE result_type operator()(const A0& a0) const
    {
      return nt2::ismatrix(a0) && nt2::isequal(a0, nt2::expand(nt2::from_diag(nt2::diag_of(a0)), size(a0)));
    }
  };
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::isdiagonal_, tag::cpu_
                            , (A0)
                            , (scalar_<unspecified_<A0> >)
                            )
  {
    typedef bool result_type;
    BOOST_DISPATCH_FORCE_INLINE result_type operator()(const A0&) const
    {
      return true;
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::isdiagonal_, tag::cpu_
                            , (A0)(A1)
                            , ((ast_<A0, nt2::container::domain>))
                              (scalar_<floating_<A1> >)
                              )
  {
    typedef bool result_type;
    BOOST_DISPATCH_FORCE_INLINE result_type operator()(const A0& a0, const A1& thresh) const
    {
      if (is_eqz(thresh))
        return isdiagonal(a0);

      A1 r = nt2::max(nt2::abs(a0-nt2::expand(nt2::from_diag(nt2::diag_of(a0)), size(a0)))(_))(begin_);
      return r <= thresh;
    }
  };
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::isdiagonal_, tag::cpu_
                              , (A0)(A1)
                              , (scalar_<unspecified_<A0> >)
                                (scalar_<floating_<A1> >)
                              )
  {
    typedef bool result_type;
    BOOST_DISPATCH_FORCE_INLINE result_type operator()(const A0&, const A1&) const
    {
      return true;
    }
  };
} }

#endif
