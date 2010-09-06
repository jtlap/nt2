#include <nt2/sdk/meta/strip.hpp>

namespace nt2 { namespace $self.tb_namespace$
{
  template<class Extension,class Dummy>
  struct call<$self.tb_taggedname$_,tag::simd_(tag::arithmetic_,Extension),Dummy>
  {
    template<class Sig> struct result;
    template<class This,$self.class_list$>
    struct result<This($self.type_list$)> : meta::strip<A0>{};

    // see documentation http://nt2.lri.fr/extension/custom_function.html
    // for writing the functor implementation code 
    // with or without type dispatching

  };
} }

      