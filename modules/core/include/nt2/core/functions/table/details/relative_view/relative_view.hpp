//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_RELATIVE_VIEW_RELATIVE_VIEW_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_RELATIVE_VIEW_RELATIVE_VIEW_HPP_INCLUDED

/**
 * \file
 * \brief Define nt2::relative_view
**/

namespace nt2
{
  namespace tag { struct relative_view_ {}; }

  template<typename Expr, typename Size, typename Pos>
  struct relative_view
  {
    typedef tag::relative_view_ fusion_tag;
    typedef Pos sequence_pos_type;

    relative_view (Expr const& expr, Size const& sz, Pos const& pos) : expr_(expr), sz_(sz), pos_(pos) {}

    Expr const& expr_;
    Size const& sz_;
    Pos const& pos_;
  };
}

#include <nt2/core/functions/table/details/relative_view/fusion.hpp>

#endif
