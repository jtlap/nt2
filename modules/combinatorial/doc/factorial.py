[ ## this file was manually modified by jt
    {
     'functor' : {
         'arity' : '1',
        'call_types' : [],
         'ret_arity' : '0',
         'rturn' : {
             'default' : 'T',
            },
         'simd_types' : [],
         'special' : ['combinatorial'],
         'type_defs' : [],
         'types' : ['real_','integer_'],
        },
     'info' : 'manually modified',
     'unit' : {
         'global_header' : {
             'first_stamp' : 'created  by jt the 07/03/2011',
             'cover_included' : ["#include <nt2/toolbox/boost_math/include/factorial.hpp>",
                           "#include <nt2/include/functions/toint.hpp>",
                           "#include <nt2/include/functions/abs.hpp>",
                           "#include <nt2/include/functions/min.hpp>"],
             'notes' : [],
             'stamp' : 'modified by jt the 07/03/2011',
            },
         'ranges' : {
             'default' : [['T(0)', 'T(10)']],
            },
         'specific_values' : {
            'default' : {
                'nt2::One<T>()' : 'nt2::One<T>()',
                'nt2::Zero<T>()' : 'nt2::One<T>()',
            },
            'real_' : {
                'nt2::Inf<T>()' : 'nt2::Inf<T>()',
                'nt2::Nan<T>()' : 'nt2::Nan<T>()',
                'nt2::One<T>()' : 'nt2::One<T>()',
                'nt2::Zero<T>()' : 'nt2::One<T>()',
                'nt2::Two<T>()' : 'nt2::Two<T>()',
                'nt2::Three<T>()' : 'nt2::Six<T>()',
            },
            'integer_' : {
                    'nt2::One<T>()' : 'nt2::One<T>()',
                    'nt2::Zero<T>()' : 'nt2::One<T>()',
                    'nt2::Three<T>()' : 'nt2::Six<T>()',
                    'nt2::Thousand<T>()' : 'nt2::Valmax<T>()',
            },
          },
         'verif_test' : {
             'property_call' : {
                 'default' : ['nt2::factorial(a0)'],
                },
             'property_value' : {
                 'default' : ['(nt2::min(nt2::boost_math::factorial<double>(nt2::abs(nt2::toint(a0))),nt2::Valmax<r_t>()))'],
                },
             'simd' : {
                },
             'ulp_thresh' : {
                 'default' : ['1'],
                },
            },
        },
    },
]
