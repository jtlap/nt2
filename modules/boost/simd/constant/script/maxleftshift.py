[ ## this file was manually modified by jt
    {
     'functor' : {
         'description' : [ "Constant $Fct$",
                           "It is senseless to shift a value of more bits than the number of bits - 1 ",
                           "of the value type: this is that number."],
         'return' : ["type T value"],
         'type_dependant' : True,   
         'template' : True,   
         'module' : 'boost',
         'special' : ['constant'],   
         'arity' : '0',
         'call_types' : [],
         'ret_arity' : '0',
         'tpl' : '<T>',   
         'rturn' : {
             'default' : 'T',
            },
         'simd_types' : ['real_', 'signed_int_','unsigned_int_'],
         'type_defs' : [],
         'types' : ['real_',  'signed_int_','unsigned_int_'],
        },
     'info' : 'manually modified',
     'unit' : {
         'global_header' : {
             'first_stamp' : 'created  by jt the 02/10/2011',
             'included' : [],
             'no_ulp' : 'True',
             'notes' : [],
             'stamp' : 'modified by jt the 02/10/2011',
            },
         'ranges' : {
             'default' : [['boost::simd::Valmin<T>()/2', 'boost::simd::Valmax<T>()/2']],
            },
         'specific_values' : {
             'default' : {
                 '-' : {'result' : 'T(1)','ulp_thresh' : '0',},
                },
            },
        },
    },
]
