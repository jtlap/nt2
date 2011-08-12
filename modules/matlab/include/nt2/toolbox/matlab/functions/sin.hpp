#ifndef NT2_TOOLBOX_MATLAB_FUNCTIONS_SIN_HPP_INCLUDED
#define NT2_TOOLBOX_MATLAB_FUNCTIONS_SIN_HPP_INCLUDED

#include <nt2/toolbox/matlab/functions/feval.hpp>
#include <nt2/include/functor.hpp>

namespace nt2
{
    namespace matlab
    {
        struct sin_ {};
        NT2_FUNCTION_IMPLEMENTATION(sin_, sin, 1)
    }
}

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::matlab::sin_, tag::cpu_,
                             (A0),
                             (scalar_< real_<A0> >)
                            )
  {
    typedef A0 result_type; 
    NT2_FUNCTOR_CALL(1)
    {
      return matlab::feval<result_type>("sin", a0);
    }
  };
} }

#endif
