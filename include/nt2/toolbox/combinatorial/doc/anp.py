[ ## this file was manually modified by jt
    {
     'functor' : {
         'arity' : '2',
         'call_types' : [],
         'ret_arity' : '0',
         'rturn' : {
             'default' : 'typename boost::result_of<nt2::meta::arithmetic(T)>::type',
            },
         'type_defs' : [],
         'types' : ['real_', 'unsigned_int_', 'signed_int_'],
        },
     'info' : 'manually modified',
     'unit' : {
         'global_header' : {
             'first_stamp' : 'modified by jt the 30/11/2010',
             'included' : [],
             'notes' : [],
             'stamp' : 'modified by jt the 02/01/2011',
            },
         'ranges' : {
             'real_' : [['T(0)', 'T(10)'], ['T(0)', 'T(10)']],
             'signed_int_' : [['00', '100'], ['00', '100']],
             'unsigned_int_' : [['0', '100'], ['0', '100']],
            },
         'specific_values' : {
             'default' : {
                },
             'real_' : {
                 'nt2::Inf<T>()' : 'nt2::Nan<T>()',
                 'nt2::Nan<T>()' : 'nt2::Nan<T>()',
                 'nt2::One<T>()' : 'nt2::One<T>()',
                 'nt2::Zero<T>()' : 'nt2::One<T>()',
                },
             'signed_int_' : {
                 'nt2::One<T>()' : 'nt2::One<T>()',
                 'nt2::Zero<T>()' : 'nt2::One<T>()',
                },
             'unsigned_int_' : {
                 'nt2::One<T>()' : 'nt2::One<T>()',
                 'nt2::Zero<T>()' : 'nt2::One<T>()',
                },
            },
         'verif_test' : {
            },
        },
     'version' : '0.1',
    },
]
