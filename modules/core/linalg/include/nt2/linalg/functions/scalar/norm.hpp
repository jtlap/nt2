//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_SCALAR_NORM_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_SCALAR_NORM_HPP_INCLUDED
#include <nt2/linalg/functions/norm.hpp>
#include <nt2/include/functions/norm.hpp>
#include <nt2/include/functions/isvector.hpp>
#include <nt2/include/functions/ismatrix.hpp>
#include <nt2/include/functions/vecnorm.hpp>
#include <nt2/include/functions/is_nan.hpp>
#include <nt2/include/functions/isempty.hpp>
#include <nt2/include/functions/globalmax.hpp>
#include <nt2/include/functions/asum1.hpp>
#include <nt2/include/functions/gesvd.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/core/container/dsl.hpp>
#include <nt2/core/container/table/table.hpp>
#include <string>

// *     DLANGE = ( max(abs(A(i,j))), NORM = 'M' or 'm'
// *              (
// *              ( norm1(A),         NORM = '1', 'O' or 'o'
// *              (
// *              ( normI(A),         NORM = 'I' or 'i'
// *              (
// *              ( normF(A),         NORM = 'F', 'f', 'E' or 'e'
// *
// *  where  norm1  denotes the  one norm of a matrix (maximum column sum),
// *  normI  denotes the  infinity norm  of a matrix  (maximum row sum) and
// *  normF  denotes the  Frobenius norm of a matrix (square root of sum of
// *  squares).  Note that  max(abs(A(i,j)))  is not a consistent matrix norm.

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::norm_, tag::cpu_,
                              (A0)(A1),
                              ((ast_<A0, nt2::container::domain>))
                              (scalar_<arithmetic_<A1> > )
    )
  {
    typedef typename meta::strip<typename A0::value_type>::type type_t;
    typedef typename meta::as_real<type_t>::type rtype_t;
    typedef rtype_t result_type;
    typedef typename meta::option<typename A0::settings_type,nt2::tag::shape_>::type shape;
    typedef nt2::table<type_t,shape>  matrix_type;
    typedef nt2::table<type_t>  entry_type;

    NT2_FUNCTOR_CALL(2)
    {
      if (isvector(a0))
      {
        return vecnorm(a0, a1);
      }
      else if (ismatrix(a0))
      {
        if (isempty(a0)){
          return Zero<result_type>();
        } else if (a1 == 'I'|| a1 == 'i'|| a1 == Inf<A1>()){
          return nt2::globalmax(nt2::asum1(a0, 2));
        } else if (a1 == Two<A1>()){
        entry_type u,s,v;
        matrix_type work(a0);

        nt2_la_int  m  = nt2::height(work);
        nt2_la_int  n  = nt2::width(work);

        s.resize(nt2::of_size(std::min(m,n), 1));
        nt2::gesvd(work,s,u,v,'N','N');
        return s(1);
        } else if (a1 == '1' || a1 == 'O' || a1 == 'o' ||a1 == One<A1>()) {
         return nt2::globalmax(nt2::asum1(a0, 1));
        } else if (a1 == 'F' || a1 == 'f' || a1 == 'E' ||a1 == 'e'){
          return vecnorm(a0);
        } else {
          BOOST_ASSERT_MSG(false, "Sorry Not Implemented for this parameter a1 value");
          return Nan<result_type>();
        }
      }
      else
      {
        BOOST_ASSERT_MSG(false, "a0 is not matrix nor vector");
        return Nan<result_type>();
      }
      return Nan<result_type>();
    }
  };



  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::norm_, tag::cpu_,
                              (A0)(C),
                              ((ast_<A0, nt2::container::domain>))
                              (unspecified_<C> )
    )
  {
    typedef typename A0::value_type type_t;
    typedef typename meta::as_real<type_t>::type rtype_t;
    typedef typename meta::as_floating<rtype_t>::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0& a0, const char * a1) const
    {
      if (strcmp(a1, "fro") == 0)
      {
        return norm(a0, 'F');
      }
      else if (strcmp(std::string(a1).c_str(), "inf") == 0)
      {
        return norm(a0, 'I');
      }
      else
      {
        BOOST_ASSERT_MSG(false, "unknown option calling norm");
        return Nan<result_type>();
      }
    }
  };


  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::norm_, tag::cpu_,
                              (A0),
                              ((ast_<A0, nt2::container::domain>))
    )
  {
    typedef typename A0::value_type type_t;
    typedef typename meta::as_real<type_t>::type rtype_t;
    typedef typename meta::as_floating<rtype_t>::type result_type;

    NT2_FUNCTOR_CALL(1)
    {
      if (isvector(a0))
      {
        return vecnorm(a0);
      }
      else if (ismatrix(a0))
      {
        return norm(a0, 2);
      }
      else
      {
        BOOST_ASSERT_MSG(false, "a0 is not matrix nor vector");
        return Nan<result_type>();
      }
    }
  };
} }

#endif
