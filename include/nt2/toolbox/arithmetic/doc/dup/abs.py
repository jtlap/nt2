{ 'arity': 1,
  'dptch': [ 'float',
             'int32_t',
             'unsigned_',
             'signed_',
             'arithmetic_',
             'bool_'],
  'rnges': { "default" : [['nt2::Valmin<T>()', 'nt2::Valmax<T>()']],
             'real_'   : [['T(-100)','T(100)']],
             'signed_int_' :[['T(-100)','T(100)']],
             'unsigned_int_' :[['T(0)','T(100)']], 
             
             },
  'specv': {
      "real_" :{
          'nt2::Inf<T>()' : 'nt2::Inf<T>()',
          'nt2::Minf<T>()': 'nt2::Inf<T>()',
          'nt2::Mone<T>()': 'nt2::One<T>()',
          'nt2::Nan<T>()' : 'nt2::Nan<T>()',
          'nt2::One<T>()' : 'nt2::One<T>()',
          'nt2::Zero<T>()': 'nt2::Zero<T>()'
          },
      "unsigned_int_" : {
          'nt2::One<T>()' : 'nt2::One<T>()',
          'nt2::Zero<T>()': 'nt2::Zero<T>()'
          },
      'signed_int_'  : {
          'nt2::Mone<T>()': 'nt2::One<T>()',
          'nt2::One<T>()' : 'nt2::One<T>()',
          'nt2::Zero<T>()': 'nt2::Zero<T>()'
          },
      },
  'tcall': 'nt2::standard::abs(a0)',
  'types': ['real_','unsigned_int_','signed_int_'],
  'norst': False,
  'stamp': "modified by jt the 30/11/2010",
  'versn': "0.0",
  'notes': ["""for integer standard implementation produces double and there can be
               a loss in precision. This is not the case of nt2::abs that produces unsigned integer
               output for integer entries""",
            """take care that if abs is called with floating types, YOU MUST use nt2::abs. If not
            the punishment is generally calling the wrong system abs function, that transforms your real in
            integer !"""],

  'incld': ["#include<nt2/toolbox/standard/include/abs.hpp>"],
  'rturn': {
      "default" : "T",
      "signed_int_" : "typename nt2::meta::as_integer<T,unsigned>::type"
      },
}
