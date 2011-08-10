[ ## this file was manually modified by jt
    {
     'functor' : {
         'module' : 'boost',
         'arity' : '2',
         'call_types' : [],
         'ret_arity' : '0',
         'rturn' : {
             'default' : 'typename boost::result_of<boost::dispatch::meta::arithmetic(T,T)>::type',
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
             'default' : {
                },
             'real_' : {
                 'T(1),T(2)' : 'T(0.5)',
                 'boost::simd::Inf<T>()' : 'boost::simd::Nan<T>()',
                 'boost::simd::Minf<T>()' : 'boost::simd::Nan<T>()',
                 'boost::simd::Mone<T>()' : 'boost::simd::One<T>()',
                 'boost::simd::Nan<T>()' : 'boost::simd::Nan<T>()',
                 'boost::simd::One<T>()' : 'boost::simd::One<T>()',
                 'boost::simd::Zero<T>()' : 'boost::simd::Nan<T>()',
                },
             'signed_int_' : {
                 '2,3' : '0',
                 '3,2' : '1',
                 'boost::simd::Mone<T>()' : 'boost::simd::One<T>()',
                 'boost::simd::One<T>()' : 'boost::simd::One<T>()',
                 'boost::simd::Zero<T>()' : 'boost::simd::Zero<T>()',
                },
             'unsigned_int_' : {
                 '2,3' : '0',
                 '3,2' : '1',
                 'boost::simd::One<T>()' : 'boost::simd::One<T>()',
                 'boost::simd::Zero<T>()' : 'boost::simd::Zero<T>()',
                },
            },
         'verif_test' : {
             'property_call' : {
                 'default' : ['boost::simd::rdivide(a0,a1)'],
                },
             'property_value' : {
                 'unsigned_int_' : ['(a1!=0) ? (a0/(a1+((a1==0)?1:0))) : boost::simd::Valmax<r_t>()'],
                 'signed_int_' : ['(a1!=0) ? (a0/(a1+((a1==0)?1:0))) : ((a0>0) ? boost::simd::Valmax<r_t>() : (a0<0) ? boost::simd::Valmin<r_t>() : 0)'],     
                 'real_'   : ['a0/a1'],   
                },
             'ulp_thresh' : {
                 'default' : ['0'],
                },
            },
        },
     'version' : '0.1',
    },
]
