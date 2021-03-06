/* Copyright 2015 greenbytes GmbH (https://www.greenbytes.de)
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __mod_h2__h2_io__
#define __mod_h2__h2_io__

/* h2_io is the basic handler of a httpd connection. It keeps two brigades,
 * one for input, one for output and works with the installed connection
 * filters.
 * The read is done via a callback function, so that input can be processed
 * directly without copying.
 */
typedef struct {
    conn_rec *connection;
    apr_bucket_brigade *input;
    apr_bucket_brigade *output;
} h2_io_ctx;

apr_status_t h2_io_init(h2_io_ctx *io, conn_rec *c);
void h2_io_destroy(h2_io_ctx *io);

typedef apr_status_t (*h2_io_on_read_cb)(const char *data, apr_size_t len,
                                         apr_size_t *readlen, int *done,
                                         void *puser);


apr_status_t h2_io_read(h2_io_ctx *io,
                        apr_read_type_e block,
                        h2_io_on_read_cb on_read_cb,
                        void *puser);

apr_status_t h2_io_write(h2_io_ctx *io,
                         const char *buf,
                         size_t length,
                         size_t *written);

apr_status_t h2_io_flush(h2_io_ctx *io);

#endif /* defined(__mod_h2__h2_io__) */
