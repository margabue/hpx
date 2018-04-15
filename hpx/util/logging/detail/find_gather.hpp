// find_gather.hpp

// Boost Logging library
//
// Author: John Torjo, www.torjo.com
//
// Copyright (C) 2007 John Torjo (see www.torjo.com for email)
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org for updates, documentation, and revision history.
// See http://www.torjo.com/log2/ for more details


#ifndef JT28092007_find_gather_HPP_DEFINED
#define JT28092007_find_gather_HPP_DEFINED

#include <hpx/util/logging/detail/fwd.hpp>
#include <string>

namespace hpx { namespace util { namespace logging {

    //////////////////////////////////////////////////////////////////////////////////
    // specialize logger for format_write class
    //
    namespace gather { namespace ostream_like {
        template<class, class> struct return_str ;
    }}

    namespace optimize {
        struct cache_string_one_str ;
    }

    namespace detail {
        template <class stream, class param>
        struct find_gather {
            typedef gather::ostream_like::return_str< std::string, stream > type ;
        };

        template< class stream >
        struct find_gather< stream, hpx::util::logging::optimize
            ::cache_string_one_str > {
            typedef gather::ostream_like::return_str< hpx::util::logging::optimize
                ::cache_string_one_str, stream > type;
        };
    }

}}}

#endif
