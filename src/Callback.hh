/*                                                                                                                                                                                                 
 * Rados Filesystem - A filesystem library based in librados                                                                                                                                       
 *                                                                                                                                                                                                 
 * Copyright (C) 2014 CERN, Switzerland                                                                                                                                                            
 *                                                                                                                                                                                                 
 * Author: Joaquim Rocha <joaquim.rocha@cern.ch>                                                                                                                                                   
 *                                                                                                                                                                                                 
 * This library is free software; you can redistribute it and/or                                                                                                                                   
 * modify it under the terms of the GNU Lesser General Public                                                                                                                                      
 * License as published by the Free Software Foundation; either                                                                                                                                    
 * version 3 of the License, or (at your option) any later version.                                                                                                                                
 *                                                                                                                                                                                                 
 * This library is distributed in the hope that it will be useful, but                                                                                                                             
 * WITHOUT ANY WARRANTY; without even the implied warranty of                                                                                                                                      
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU                                                                                                                                
 * Lesser General Public License at http://www.gnu.org/licenses/lgpl-3.0.txt                                                                                                                       
 * for more details.                                                                                                                                                                               
 */

#ifndef __RADOS_FS_CALLBACK_HH__
#define __RADOS_FS_CALLBACK_HH__

#define RADOS_FS_BEGIN_NAMESPACE namespace radosfs {
#define RADOS_FS_END_NAMESPACE }

#include <stdio.h>

RADOS_FS_BEGIN_NAMESPACE

class Callback {
public:
  typedef struct callback_data {
    void* caller;
    int retc;
  } CallbackData;

  typedef void (*callback_t)(CallbackData*);

  Callback() { call = 0; data.caller=0; data.retc=-1;}
  Callback(callback_t tocall, CallbackData& info) { call = tocall; data = info; data.retc=0;    fprintf(stderr,"^^^^^^^^^^ Constructor %llx %llx\n", call,data.caller);}
  Callback(callback_t tocall, void* callerinfo) { call = tocall; data.caller = callerinfo; data.retc=0;fprintf(stderr,"^^^^^^^^^^ Constructor %llx %llx\n", call,data.caller);}

  virtual ~Callback() {};

  Callback(const Callback &obj) {
    call = obj.call;
    data = obj.data;
    fprintf(stderr,"^^^^^^^^^^ Copy Constructor %llx %llx %llx\n", obj.call,data.caller, obj.data.caller);
  }

  callback_t call;
  CallbackData data;
};

RADOS_FS_END_NAMESPACE

#endif // __RADOS_FS_CALLBACK_HH__       
