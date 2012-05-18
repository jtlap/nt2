[ ## this file was manually modified by jt
    {
     'functor' : {
            'description' : ["return uniform random numbers of the common type of the entries and",
                             "in the range defined by \\\\f$[\min(a_0,a_1),\max(a0,a1)[\\\\f$"],
         'module' : 'boost',
         'arity' : '2',
         'call_types' : [],
         'ret_arity' : '0',
         'rturn' : {
             'default' : 'typename boost::common_type<T,T>::type',
            },
         'simd_types' : ['real_'],
         'type_defs' : [],
         'types' : ['real_', 'unsigned_int_', 'signed_int_'],
        },
     'info' : 'manually modified',
     'unit' : {
         'global_header' : {
             'first_stamp' : 'modified by jt the 01/12/2010',
             'included' : [],
             'notes' : [],
             'stamp' : 'modified by jt the 13/12/2010',
            },
         'ranges' : {
             'real_' : [['T(-10)', 'T(10)'], ['T(-10)', 'T(10)']],
             'signed_int_' : [['-100', '100'], ['-100', '100']],
             'default' : [['0', '100'], ['0', '100']],
            },
         'specific_values' : {
            },
         'verif_test' : {
             'property_call' : {
                 'default' : ['boost::simd::random(a0,a1)'],
                },
            },
        },
     'version' : '0.1',
    },
]
