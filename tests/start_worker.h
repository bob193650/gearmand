/*  vim:expandtab:shiftwidth=2:tabstop=2:smarttab:
 * 
 *  Gearmand client and server library.
 *
 *  Copyright (C) 2011 Data Differential, http://datadifferential.com/
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are
 *  met:
 *
 *      * Redistributions of source code must retain the above copyright
 *  notice, this list of conditions and the following disclaimer.
 *
 *      * Redistributions in binary form must reproduce the above
 *  copyright notice, this list of conditions and the following disclaimer
 *  in the documentation and/or other materials provided with the
 *  distribution.
 *
 *      * The names of its contributors may not be used to endorse or
 *  promote products derived from this software without specific prior
 *  written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */


#include <sys/types.h>

#include <libgearman/gearman.h>
#include <libtest/visibility.h>

#include <boost/thread.hpp>


struct worker_handle_st
{
public:
  worker_handle_st();
  ~worker_handle_st();

  void set_shutdown();
  bool is_shutdown();
  bool shutdown();

  void set_worker_id(gearman_worker_st*);

  boost::barrier* sync_point();

  void wait();


  volatile bool failed_startup;
  boost::thread* _thread;

private:
  bool _shutdown;
  boost::mutex _shutdown_lock;
  gearman_id_t _worker_id;
  boost::barrier _sync_point;
};

#pragma once

LIBTEST_API
  struct worker_handle_st *test_worker_start(in_port_t port, 
					     const char *namespace_key,
					     const char *function_name,
					     gearman_function_t &worker_fn,
					     void *context,
					     gearman_worker_options_t options,
               int timeout= 0);

LIBTEST_API
bool test_worker_stop(struct worker_handle_st *);
