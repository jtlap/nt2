[{'functor': {'arity': '2',
              'call_types': [],
              'ret_arity': '0',
              'rturn': {'default': 'typename boost::result_of<nt2::meta::arithmetic(T)>::type'},
              'type_defs': [],
              'types': ['real_', 'unsigned_int_', 'signed_int_']},
  'unit': {'global_header': {'first_stamp': 'modified by jt the 01/12/2010',
                             'included': ['#include<nt2/include/functions/abs.hpp>',
                                          '#include<nt2/include/functions/negate.hpp>'],
                             'notes': ["""
 The remainder() function computes the remainder of dividing x by y.  The
 return value is x-n*y, where n is the value x / y, rounded to the nearest
 integer.  If the absolute value of x-n*y is 0.5, n is chosen to be even.
 The drem() function does precisely the same thing.
"""
                                 ],
                             'stamp': 'modified by jt the 13/12/2010'},
           'ranges': {'real_': [['T(-10)', 'T(10)'], ['T(-10)', 'T(10)']],
                      'signed_int_': [['-100', '100'], ['1', '100']],
                      'unsigned_int_': [['0', '100'], ['1', '100']]},
           'specific_values': {'default': {},
                               'real_': {'nt2::Inf<T>()': 'nt2::Nan<T>()',
                                         'nt2::Minf<T>()': 'nt2::Nan<T>()',
                                         'nt2::Mone<T>()': 'nt2::Zero<T>()',
                                         'nt2::Nan<T>()': 'nt2::Nan<T>()',
                                         'nt2::One<T>()': 'nt2::Zero<T>()',
                                         'nt2::Zero<T>()': 'nt2::Zero<T>()'},
                               'signed_int_': {'nt2::Mone<T>()': 'nt2::Zero<T>()',
                                               'nt2::One<T>()': 'nt2::Zero<T>()',
                                               'nt2::Zero<T>()': 'nt2::Zero<T>()'},
                               'unsigned_int_': {'nt2::One<T>()': 'nt2::Zero<T>()',
                                                 'nt2::Zero<T>()': 'nt2::Zero<T>()'}},
           'verif_test': {'property_call': None,
                          'property_value': {'default': ['a0-idivround(a0, a1)*a1']},
                          'ulp_thresh': {'default': ['0']}}},
  'version': '0.1'}]
