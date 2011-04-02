[ ## this file was manually modified by jt
    {
     'functor' : {
         'arity' : '2',
         'call_types' : ['T','iT'],
         'ret_arity' : '0',
         'rturn' : {
             'default' : 'T',
            },
         'simd_types' : [],
         'special' : ['boost_math'],
         'type_defs' : [],
         'types' : ['real_'],
        },
     'info' : 'manually modified',
     'unit' : {
         'global_header' : {
             'first_stamp' : 'created  by jt the 07/03/2011',
             'included' : [],
             'notes' : [],
             'stamp' : 'modified by jt the 07/03/2011',
            },
         'ranges' : {
             'default' : [['T(-10)', 'T(10)'], ['iT(0)', 'iT(10)']],
            },
         'specific_values' : {
            },
         'verif_test' : {
             'property_call' : {
                 'default' : ['nt2::boost_math::falling_factorial(a0,a1)'],
                },
             'property_value' : {
                 'default' : ['nt2::boost_math::falling_factorial(a0,a1)'],
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
