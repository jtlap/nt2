[ ## this file was manually modified by jt
    {
     'functor' : {
         'arity' : '2',
         'call_types' : [],
         'ret_arity' : '0',
         'rturn' : {
             'default' : 'typename boost::result_of<nt2::meta::arithmetic(T,T)>::type',
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
             'unsigned_int_' : [['0', '100'], ['0', '100']],
            },
         'specific_values' : {
            },
         'verif_test' : {
             'property_call' : {
                 'default' : ['nt2::random(a0,a1)'],
                },
            },
        },
     'version' : '0.1',
    },
]