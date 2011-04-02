/*******************************************************************************
 *         Copyright 2003-2010 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2009-2010 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_SIMD_PACK_GENERATOR_HPP_INCLUDED
#define NT2_SDK_SIMD_PACK_GENERATOR_HPP_INCLUDED

namespace nt2 { namespace simd
{
  //////////////////////////////////////////////////////////////////////////////
  // SIMD Expression use a template parameters so proto generator is extended
  //////////////////////////////////////////////////////////////////////////////
  template<class Type,class Cardinal> struct generator
  {
    template<class Sig> struct result;
    template<class This, class Expr>
    struct result<This(Expr)> { typedef expression<Expr,Type,Cardinal> type; };

    template<class Expr>
    expression<Expr,Type,Cardinal> const operator()(Expr const &xpr) const
    {
      expression<Expr,Type,Cardinal> const that = {xpr};
      return that;
    }
  };
} }

#endif
