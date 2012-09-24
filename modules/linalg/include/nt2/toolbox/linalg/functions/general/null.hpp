/*******************************************************************************
 *         Copyright 2003-2012 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2011-2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_LINALG_FUNCTIONS_GENERAL_NULL_HPP_INCLUDED
#define NT2_TOOLBOX_LINALG_FUNCTIONS_GENERAL_NULL_HPP_INCLUDED
#include <nt2/include/functions/null.hpp>
#include <nt2/include/functions/svd.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/asin.hpp>
#include <nt2/include/functions/min.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/orth.hpp>
#include <nt2/include/functions/norm.hpp>
#include <nt2/include/constants/mone.hpp>
#include <nt2/table.hpp>

namespace nt2{ namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_assign_, tag::cpu_
                              , (A0)(A1)(N)
                              , (ast_<A0>)
                                ((node_<A1, nt2::tag::null_, N> ))
                            )
  {
    typedef typename boost::proto::result_of::child_c<A1&,0>::type       Out0;
    typedef A0&                                                   result_type;
    typedef typename A0::value_type                                value_type;
    typedef table<value_type>                                           tab_t; 
    result_type operator()(A0& out, const A1& in) const
    {
      out.resize(in.extent());
      value_type tol = choice(in, N());
      choice(in, N()); 
      Out0& a0 = boost::proto::child_c<0>(in); 
      out =  nt2::details::svd_result<Out0>(a0, 'N', 'O').null(tol);
      return out; 
    }
  private :
    static value_type choice(const A1& in, boost::mpl::long_<1> const &){return Mone<value_type>(); }
    static value_type choice(const A1& in, boost::mpl::long_<2> const &){return boost::proto::child_c<1>(in); }
  };

} }


#endif

