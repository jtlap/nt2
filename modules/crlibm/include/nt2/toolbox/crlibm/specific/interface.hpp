//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_CRLIBM_SPECIFIC_INTERFACE_HPP_INCLUDED
#define NT2_TOOLBOX_CRLIBM_SPECIFIC_INTERFACE_HPP_INCLUDED

#include <nt2/toolbox/crlibm/specific/tags.hpp>

#define NT2_CRLIBM_FUNCTION_IMPLEMENTATION_TPL(NAME,ARITY)                      \
template <class Rounding, class A0>                                             \
inline typename nt2::meta::                                                     \
                call<crlibm::tag::NAME##_<Rounding>(A0 const&)>::type           \
NAME(A0 const& a0) { NT2_FUNCTION_BODY(crlibm::tag::NAME##_<Rounding>,ARITY) }  \
/**/

// TODO : Remove ?
#define NT2_CRLIBM_INNER_STRUCT(ROUNDING, NAME, SUF)    \
template<class A> struct inner_##NAME < A, ROUNDING>		\
{									\
static inline result_type						\
  eval(A const& a0,ROUNDING const&){ return NAME##_##SUF(a0);}	\
};										\
/**/

namespace nt2 { namespace crlibm
{
  namespace details
  {
    extern "C"
    {
      /* An init function which sets FPU flags when needed (mostly on Intel
         architectures with default double extended) */
      extern unsigned long long crlibm_init(void);

      /* An exit function which restores FPU flags when needed (mostly on Intel
         architectures with default double extended) */
      extern  void crlibm_exit(unsigned long long);
    }

    ////////////////////////////////////////////////////////////////////////////
    /// Statically constructed object for crlibm initialization
    ////////////////////////////////////////////////////////////////////////////
    struct activator
    {
      unsigned long long i;
       activator()  { i = details::crlibm_init(); }
      ~activator()  { details::crlibm_exit(i);    }
    };

    activator const activate;
  }
} }

#endif
