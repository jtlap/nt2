/*******************************************************************************
 *         Copyright 2003-2012 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2011-2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_LINALG_FUNCTIONS_GENERAL_POLY_HPP_INCLUDED
#define NT2_TOOLBOX_LINALG_FUNCTIONS_GENERAL_POLY_HPP_INCLUDED

#include <nt2/toolbox/linalg/functions/poly.hpp>
#include <nt2/core/container/table/table.hpp>
#include <nt2/include/functions/horzcat.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/isvector.hpp>
//#include <nt2/include/functions/geneig.hpp>
#include <nt2/include/functions/assign.hpp>
#include <nt2/include/functions/issquare.hpp>
#include <nt2/include/constants/one.hpp>

namespace nt2{ namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_assign_, tag::cpu_
                              , (A0)(A1)(N)
                              , ((ast_<A0, nt2::container::domain>))
                                ((node_<A1, nt2::tag::poly_, N,nt2::container::domain> ))
                            )
  {
    typedef typename boost::proto::result_of::child_c<A1&,0>::type        In0;
    typedef typename A1::value_type                                value_type;
    typedef A0&                                                   result_type;
    result_type operator()(A0& out, const A1& in) const
    {
      In0 & a = boost::proto::child_c<0>(in);
      BOOST_ASSERT_MSG(isvector(a)/* || issquare(a)*/, "input must be a vector or a square matrix");
      out.resize(in.extent());

//       if (issquare(a))
//       {
// //        compute(out,  geneig(a)); //TODO this will wait geneig working... i.e. complex tables
//       }
//       else
//       {
        compute(out, a);
//       }
      return out;
    }
  private:
    template <class S, class T>
    void compute(S out, const T& e) const
    {
       size_t n = length(e);
       table<value_type> tmp,  tmp1;
       out = nt2::cath(One<value_type>(), nt2::zeros(1,n,nt2::meta::as_<value_type>()));

       for(size_t j=1; j <= n; ++j)
       {
         tmp1 = out(_(2u, j+1))- e(j)*out(_(1u, j)); //aliasing !
         out(_(2u, j+1)) = tmp1;
       }

//         The result should be real if the roots are complex conjugates.
//         if isequal(sort(e(imag(e)>0)),sort(conj(e(imag(e)<0))))
//           c = real(c);
    }
  };
} }

#endif
