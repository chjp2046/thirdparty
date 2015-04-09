/*  vim:expandtab:shiftwidth=2:tabstop=2:smarttab:
 * 
 *  libtest
 *
 *  Copyright (C) 2011 Data Differential, http://datadifferential.com/
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 3 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */


/*
  Structures for generic tests.
*/

#include <cstdio>
#include <cstdlib>
#include <stdint.h>
#include <arpa/inet.h>

#include <libmemcached/libtest/visibility.h>
#include <libmemcached/libtest/version.h>

#include <libmemcached/libtest/error.h>
#include <libmemcached/libtest/strerror.h>
#include <libmemcached/libtest/stream.h>
#include <libmemcached/libtest/comparison.hpp>
#include <libmemcached/libtest/server.h>
#include <libmemcached/libtest/server_container.h>
#include <libmemcached/libtest/wait.h>
#include <libmemcached/libtest/callbacks.h>
#include <libmemcached/libtest/test.h>
#include <libmemcached/libtest/core.h>
#include <libmemcached/libtest/runner.h>
#include <libmemcached/libtest/port.h>
#include <libmemcached/libtest/is_local.hpp>
#include <libmemcached/libtest/socket.hpp>
#include <libmemcached/libtest/stats.h>
#include <libmemcached/libtest/collection.h>
#include <libmemcached/libtest/framework.h>
#include <libmemcached/libtest/get.h>
#include <libmemcached/libtest/stream.h>
#include <libmemcached/libtest/cmdline.h>
#include <libmemcached/libtest/string.hpp>
#include <libmemcached/libtest/binaries.h>
