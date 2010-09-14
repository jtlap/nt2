#include <nt2/include/simd.hpp>,
#include <nt2/include/functor.hpp>
#include <nt2/core/numeric/preprocessor/include.hpp>

namespace nt2 { namespace $self.tb_namespace$
  {	       
    struct $self.name$_ {};
  }
  NT2_FUNCTION_IMPLEMENTATION($self.tb_name$::$self.name$_, $self.name$, $self.arity$)
}
 
#include <nt2/core/numeric/function/details/scalar/$self.name$.hpp>
// Uncomment the following line if you implement a proper simd version
//#include NT2_$self.tb_nameupper$_INCLUDE($self.name$.hpp) 

 