#include <nt2/include/simd.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/toolbox/$self.tb_name$/include.hpp>

namespace nt2 { namespace $self.tb_namespace$
  {	       
    struct $self.name$_ {};
  }
  NT2_FUNCTION_IMPLEMENTATION($self.tb_namespace$::$self.name$_, $self.name$, $self.arity$)
}
 
#include <nt2/toolbox/$self.tb_name$/function/scalar/$self.name$.hpp>
#include NT2_$self.tb_nameupper$_INCLUDE($self.name$.hpp) 

 