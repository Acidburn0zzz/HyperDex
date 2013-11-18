// Copyright (c) 2012-2013, Cornell University
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
//     * Redistributions of source code must retain the above copyright notice,
//       this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright
//       notice, this list of conditions and the following disclaimer in the
//       documentation and/or other materials provided with the distribution.
//     * Neither the name of HyperDex nor the names of its contributors may be
//       used to endorse or promote products derived from this software without
//       specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

#ifndef hyperdex_daemon_identifier_generator_h_
#define hyperdex_daemon_identifier_generator_h_

// po6
#include <po6/threads/mutex.h>

// HyperDex
#include "namespace.h"
#include "common/ids.h"

BEGIN_HYPERDEX_NAMESPACE

class identifier_generator
{
    public:
        identifier_generator();
        ~identifier_generator() throw ();

    // concurrent methods
    // these methods return "true" if ri is a managed region_id, else "false"
    public:
        // ensure that new identifiers are strictly greater than "id"
        bool bump(const region_id& ri, uint64_t id);
        // look at the next identifier, and store it in "id"
        bool peek(const region_id& ri, uint64_t* id) const;
        // generate one unique identifier, and store it in "id"
        bool generate_id(const region_id& ri, uint64_t* id);
        // generate n sequential identifiers and store the first in "id"
        bool generate_ids(const region_id& ri, uint64_t n, uint64_t* id);

    // external synchronization required; nothing can call other methods during
    // adopt; copy_from must be mutually exclusive with adopt on either
    // generator, and mutually exclusive with all on this generator
    public:
        void adopt(region_id* ris, size_t ris_sz);
        void copy_from(const identifier_generator&);

    private:
        class counter;

    private:
        identifier_generator(const identifier_generator&);
        identifier_generator& operator = (const identifier_generator&);

    private:
        void get_base(counter** counters, uint64_t* counters_sz) const;
        counter* get_counter(const region_id& ri) const;

    private:
        counter* m_counters;
        uint64_t m_counters_sz;
};

END_HYPERDEX_NAMESPACE

#endif // hyperdex_daemon_identifier_generator_h_
