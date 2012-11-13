//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_POLYNOM_FUNCTIONS_EXPR_ROOTS_HPP_INCLUDED
#define NT2_TOOLBOX_POLYNOM_FUNCTIONS_EXPR_ROOTS_HPP_INCLUDED
#include <nt2/toolbox/polynom/functions/roots.hpp>
#include <nt2/include/functions/scalar/fma.hpp>
#include <nt2/include/functions/isempty.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/include/functions/size.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/issquare.hpp>
#include <nt2/include/functions/rowvect.hpp>
#include <nt2/include/functions/complexify.hpp>
#include <nt2/include/functions/reduce.hpp>
#include <nt2/include/functions/expand_to.hpp>
#include <nt2/include/functions/from_diag.hpp>
#include <nt2/include/functions/size.hpp>
#include <nt2/include/functions/resize.hpp>
#include <nt2/include/functions/compan.hpp>
#include <nt2/include/functions/geneig.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/valuation.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::roots_, tag::cpu_
                            , (A0)
                            , (scalar_<unspecified_<A0> > )
                            )
  {

    typedef typename A0::value_type value_type;
    typedef typename nt2::meta::call<nt2::tag::zeros_(size_t, size_t)>::type  result_type; 
    NT2_FUNCTOR_CALL(1)
    {
      return zeros(1, 0, meta::as_<value_type>());
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_assign_, tag::cpu_
                              , (A0)(A1)(N)
                              , ((ast_<A0, nt2::container::domain>))
                                ((node_<A1, nt2::tag::roots_, N,nt2::container::domain> ))
                            )
  {
    typedef typename A0::value_type                                  value_type;
    typedef typename boost::proto::result_of::child_c<A1&,0>::type       poly_t;
    typedef A0&                                                     result_type;
    result_type operator()(A0& out, const A1& in) const
    {
      BOOST_AUTO_TPL(p,  nt2::reduce(nt2::complexify(nt2::rowvect(boost::proto::child_c<0>(in))), nt2::_));
      ptrdiff_t valua = nt2::valuation(p);
      BOOST_AUTO_TPL(cpan, nt2::compan(p(1, nt2::_(nt2::begin_,numel(p)-valua))));
      BOOST_AUTO_TPL(eigen,
                     nt2::factorization::geneig(cpan,
                                                nt2::eye(nt2::size(cpan, 1), nt2::size(cpan, 2), meta::as_<value_type>()),
                                                'V', 'V', 'S').eigen());
      out = eigen; 
      out.resize(in.extent()); 
      return out; 
    }

  };
 
} }


#endif
