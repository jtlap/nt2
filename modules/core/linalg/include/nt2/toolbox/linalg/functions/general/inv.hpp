/*******************************************************************************
 *         Copyright 2003-2012 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2011-2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_LINALG_FUNCTIONS_GENERAL_INV_HPP_INCLUDED
#define NT2_TOOLBOX_LINALG_FUNCTIONS_GENERAL_INV_HPP_INCLUDED

#include <nt2/toolbox/linalg/functions/inv.hpp>
#include <nt2/core/container/table/table.hpp>
#include <nt2/include/functions/lu.hpp>
#include <nt2/include/functions/assign.hpp>
namespace nt2{ namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_assign_, tag::cpu_
                              , (A0)(A1)(N)
                              , (ast_<A0>)
                                ((node_<A1, nt2::tag::inv_, N> ))
                            )
  {
    typedef typename boost::proto::result_of::child_c<A1&,0>::type       Out0;
    typedef A0&                                                   result_type;
    result_type operator()(A0& out, const A1& in) const
    {
      out.resize(in.extent());
      bool warn = choice(in, N());
      choice(in, N()); 
      out = boost::proto::child_c<0>(in); 
      out = nt2::details::lu_result<A0>(out).inv(warn);
      return out; 
    }
  private :
    static bool choice(const A1& in, boost::mpl::long_<1> const &){return true; }
    static bool choice(const A1& in, boost::mpl::long_<2> const &){return boost::proto::child_c<1>(in); }
  };
} }

#endif
