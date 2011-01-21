//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_CRLIBM_SPECIFIC_INTERFACE_HPP_INCLUDED
#define NT2_TOOLBOX_CRLIBM_SPECIFIC_INTERFACE_HPP_INCLUDED

namespace nt2
{
  
#define NT2_CRLIBM_FUNCTION_IMPLEMENTATION_TPL(NAME,ARITY)		\
    template <class Rounding, class A0>					\
    inline typename nt2::meta::enable_call<crlibm::tag::NAME##_<Rounding>(A0&)>::type \
       NAME(A0 const& a0){NT2_FUNCTION_BODY(crlibm::tag::NAME##_<Rounding>,ARITY)}	\
  /**/
  
#define NT2_CRLIBM_INNER_STRUCT(ROUNDING, NAME, SUF)			\
  template<class A0> struct inner_##NAME < A0, ROUNDING>		\
  {									\
    static inline typename NT2_RETURN_TYPE(1)::type		\
      eval(A0 const& a0,ROUNDING const&){ return NAME##_##SUF(a0);}	\
  };									\
  /**/
  
  struct rn{};
  struct rd{};
  struct rz{};
  struct ru{};
  namespace crlibm
  {
    namespace details
    {
      extern "C" {

	
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
  }
}


#endif

// /////////////////////////////////////////////////////////////////////////////
// End of interface.hpp
// /////////////////////////////////////////////////////////////////////////////
