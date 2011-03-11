#ifndef NT2_TOOLBOX_MATLAB_FUNCTION_SIN_HPP_INCLUDED
#define NT2_TOOLBOX_MATLAB_FUNCTION_SIN_HPP_INCLUDED

#include <nt2/toolbox/matlab/function/feval.hpp>
#include <nt2/include/functor.hpp>

namespace nt2
{
    namespace matlab
    {
        struct sin_ {};
        NT2_FUNCTION_IMPLEMENTATION(sin_, sin, 1)
    }
}

NT2_REGISTER_DISPATCH(
    matlab::sin_, tag::cpu_,
    (A0),
    (real_<A0>)
)

namespace nt2
{
    namespace ext
    {
        template<typename Dummy>
        struct call<matlab::sin_(tag::real_), tag::cpu_, Dummy> : callable
        {
            template<typename Sig>
            struct result;
    
            template<typename This, typename A0>
            struct result<This(A0)> { typedef typename meta::strip<A0>::type type; };
        
            NT2_FUNCTOR_CALL(1)
            {
                return matlab::feval<typename NT2_RETURN_TYPE(1)::type>("sin", a0);
            }
        };
    }
}

#endif
