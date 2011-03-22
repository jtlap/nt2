[ ## this file was manually modified by jt
    {
     'functor' : {
         'arity' : '3',
         'call_types' : ['iT','iT','T'],
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
             'default' : [['iT(0)', 'iT(10)'], ['iT(0)', 'iT(10)'], ['T(-10)', 'T(10)']],
            },
         'specific_values' : {
            },
         'verif_test' : {
             'property_call' : {
                 'default' : ['nt2::boost_math::legendre3_p(a0,a1,a2)'],
                },
             'property_value' : {
                 'default' : ['nt2::boost_math::legendre3_p(a0,a1,a2)'],
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
