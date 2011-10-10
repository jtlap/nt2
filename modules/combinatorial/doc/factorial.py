[ ## this file was manually modified by jt
    {
     'functor' : {
        'description' :['Saturated factorial in the A0 type','\par',
                        'be aware that the result is never exact if a0>12',
                        'and that the result is saturated in the input type!'
                        ],
         'arity' : '1',
         'template' : True,
         'return' : ['a value of the template parameter type T.'],   
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
             'included' : ["#include <nt2/include/functions/min.hpp>"],
             'cover_included' : ["#include <nt2/toolbox/boost_math/include/functions/factorial.hpp>",
                           "#include <nt2/include/functions/toint.hpp>",
                           "#include <nt2/include/functions/abs.hpp>"],
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
                'nt2::Inf<T>()'   : 'nt2::Inf<T>()',
                'nt2::Nan<T>()'   : 'nt2::Nan<T>()',
                'nt2::One<T>()'   : 'nt2::One<T>()',
                'nt2::Zero<T>()'  : 'nt2::One<T>()',
                'nt2::Two<T>()'   : 'nt2::Two<T>()',
                'nt2::Three<T>()' : 'nt2::Six<T>()',
                'nt2::Four<T>()'  : 'T(24)',
                'nt2::Five<T>()'  : 'T(120)',
                'nt2::Six<T>()'   : 'nt2::min((T(720ll      )),nt2::Valmax<T>())',
                'nt2::Seven<T>()' : 'nt2::min((T(5040ll     )),nt2::Valmax<T>())',
                'nt2::Eight<T>()' : 'nt2::min((T(40320ll    )),nt2::Valmax<T>())',
                'nt2::Nine<T>()'  : 'nt2::min((T(362880ll   )),nt2::Valmax<T>())',
                'nt2::Ten<T>()'   : 'nt2::min((T(3628800ll  )),nt2::Valmax<T>())',
                'nt2::Eleven<T>()': 'nt2::min((T(39916800ll )),nt2::Valmax<T>())',
                'nt2::Twelve<T>()': 'nt2::min((T(479001600ll)),nt2::Valmax<T>())',
            },
            'integer_' : {
                    'nt2::One<T>()'    : 'nt2::One<T>()',
                    'nt2::Zero<T>()'   : 'nt2::One<T>()',
                    'nt2::Three<T>()'  : 'nt2::Six<T>()',
                    'nt2::Four<T>()'   : 'T(24)',
                    'nt2::Five<T>()'   : 'T(120)',
                    'nt2::Six<T>()'    : 'nt2::min((720ull      ),(unsigned long long)nt2::Valmax<T>())',
                    'nt2::Seven<T>()'  : 'nt2::min((5040ull     ),(unsigned long long)nt2::Valmax<T>())',
                    'nt2::Eight<T>()'  : 'nt2::min((40320ull    ),(unsigned long long)nt2::Valmax<T>())',
                    'nt2::Nine<T>()'   : 'nt2::min((362880ull   ),(unsigned long long)nt2::Valmax<T>())',
                    'nt2::Ten<T>()'    : 'nt2::min((3628800ull  ),(unsigned long long)nt2::Valmax<T>())',
                    'nt2::Eleven<T>()' : 'nt2::min((39916800ull ),(unsigned long long)nt2::Valmax<T>())',
                    'nt2::Twelve<T>()' : 'nt2::min((479001600ull),(unsigned long long)nt2::Valmax<T>())',
            },
          },
         'verif_test' : {
             'property_call' : {
                 'default' : ['nt2::factorial(a0)'],
                },
             'property_value' : {
                 'default' : ['(nt2::min((u_t)nt2::boost_math::factorial<double>(nt2::abs(nt2::toint(a0))),(u_t)nt2::Valmax<r_t>()))'],
                 'real_'   : ['nt2::boost_math::factorial<double>(nt2::abs(nt2::toint(a0)))'],   
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
