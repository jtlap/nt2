/*******************************************************************************
 *         Copyright 2003-2012 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2011-2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_POLYNOM_FUNCTIONS_EXPR_CONV_HPP_INCLUDED
#define NT2_TOOLBOX_POLYNOM_FUNCTIONS_EXPR_CONV_HPP_INCLUDED

#include <nt2/toolbox/polynom/functions/conv.hpp>
#include <nt2/core/container/table/table.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/include/functions/vertcat.hpp>
#include <nt2/include/functions/colvect.hpp>
#include <nt2/include/functions/rowvect.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/trans.hpp>
#include <nt2/include/functions/isvector.hpp>
#include <nt2/include/functions/assign.hpp>
#include <nt2/include/functions/isvector.hpp>
#include <nt2/include/functions/isempty.hpp>
#include <nt2/include/constants/one.hpp>

namespace nt2{ namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_assign_, tag::cpu_
                              , (A0)(A1)(N)
                              , ((ast_<A0, nt2::container::domain>))
                                ((node_<A1, nt2::tag::conv_, N,nt2::container::domain> ))
                            )
  {
    typedef typename boost::proto::result_of::child_c<A1&,0>::type        In0;
    typedef typename boost::proto::result_of::child_c<A1&,1>::type        In1;
    typedef typename A1::value_type                                value_type; 
    typedef A0&                                                   result_type;
    result_type operator()(A0& out, const A1& in) const
    {
      In0 & a = boost::proto::child_c<0>(in);
      In1 & b = boost::proto::child_c<1>(in);  
      BOOST_ASSERT_MSG(nt2::isvector(a)&&nt2::isvector(b), "a0 and a1 must be vectors."); 
      size_t na =  nt2::numel(a);
      size_t nb =  nt2::numel(b);
      out.resize(extent(in)); 
      if (nt2::isempty(a) || nt2::isempty(b))
        out =  nt2::zeros(extent(in));
      else
      {
        out = nt2::eye(na+nb ? na+nb-1u : 0u, meta::as_<value_type>());
        for(size_t i=1; i <= na; i++){
          out(nt2::_(i, (i-1)+nb), i) = colvect(b);  
        } 
        out = rowvect(mtimes(out,  catv(colvect(a), zeros(nb ? nb-1u :0u, 1, meta::as_<value_type>()))));
      }
      return out; 
    }
  };
} }

#endif

// /////////////////////////////////////////////////////////////////////////////
// End of conv.hpp<2>
// /////////////////////////////////////////////////////////////////////////////
