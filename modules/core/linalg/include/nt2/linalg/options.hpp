//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_OPTIONS_HPP_INCLUDED
#define NT2_LINALG_OPTIONS_HPP_INCLUDED

#include <nt2/sdk/meta/policy.hpp>

namespace nt2
{
  namespace ext
  {
    struct pivot_     : boost::mpl::true_   {};
    struct no_pivot_  : boost::mpl::false_  {};
    struct matrix_    : boost::mpl::true_   {};
    struct vector_    : boost::mpl::false_  {};
    struct fast_      : boost::mpl::false_  {};
    struct precise_   : boost::mpl::false_  {};
    struct classic_   : boost::mpl::false_  {};
    struct econ_      : boost::mpl::false_  {};
    struct lower_     : boost::mpl::false_  {};
    struct upper_     : boost::mpl::false_  {};
    struct real_      : boost::mpl::false_  {};
    struct cmplx_     : boost::mpl::false_  {};
    struct sort_      : boost::mpl::false_  {};
    struct eigs_      : boost::mpl::false_  {};
    struct left_      : boost::mpl::false_  {};
    struct right_     : boost::mpl::false_  {};
    struct both_      : boost::mpl::false_  {};
    struct none_      : boost::mpl::false_  {};
    struct no_perm_   : boost::mpl::false_  {};
    struct perm_      : boost::mpl::false_  {};
    struct balance_   : boost::mpl::true_   {};
    struct no_balance_: boost::mpl::false_  {};
    struct alphabeta_ : boost::mpl::false_  {};
    struct lambda_    : boost::mpl::false_  {};
    struct no_sort_   : boost::mpl::false_  {};
    struct lapack_    : boost::mpl::false_  {};

    struct in_place_  {};
  }

  nt2::policy<ext::pivot_>       const pivot_;
  nt2::policy<ext::no_pivot_>    const no_pivot_;
  nt2::policy<ext::matrix_>      const matrix_;
  nt2::policy<ext::vector_>      const vector_;
  nt2::policy<ext::fast_>        const fast_;
  nt2::policy<ext::precise_>     const precise_;
  nt2::policy<ext::classic_>     const classic_;
  nt2::policy<ext::econ_>        const econ_;
  nt2::policy<ext::lower_>       const lower_;
  nt2::policy<ext::upper_>       const upper_;
  nt2::policy<ext::real_>        const real_;
  nt2::policy<ext::cmplx_>       const cmplx_;
  nt2::policy<ext::sort_>        const sort_;
  nt2::policy<ext::eigs_>        const eigs_;
  nt2::policy<ext::left_>        const left_;
  nt2::policy<ext::right_>       const right_;
  nt2::policy<ext::both_>        const both_;
  nt2::policy<ext::none_>        const none_;
  nt2::policy<ext::no_perm_>     const no_perm_;
  nt2::policy<ext::perm_>        const perm_;
  nt2::policy<ext::balance_>     const balance_;
  nt2::policy<ext::no_balance_>  const no_balance_;
  nt2::policy<ext::alphabeta_>   const alphabeta_;
  nt2::policy<ext::lambda_>      const lambda_;
  nt2::policy<ext::no_sort_>     const no_sort_;
  nt2::policy<ext::lapack_>      const lapack_;

  nt2::policy<ext::in_place_>  const in_place_;
}

#endif
