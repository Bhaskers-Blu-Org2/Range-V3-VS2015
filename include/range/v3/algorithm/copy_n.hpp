/// \file
// Range v3 library
//
//  Copyright Eric Niebler 2014
//
//  Use, modification and distribution is subject to the
//  Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// Project home: https://github.com/ericniebler/range-v3
//
#ifndef RANGES_V3_ALGORITHM_COPY_N_HPP
#define RANGES_V3_ALGORITHM_COPY_N_HPP

#include <tuple>
#include <utility>
#include <functional>
#include <range/v3/range_fwd.hpp>
#include <range/v3/begin_end.hpp>
#include <range/v3/distance.hpp>
#include <range/v3/range_traits.hpp>
#include <range/v3/range_concepts.hpp>
#include <range/v3/utility/functional.hpp>
#include <range/v3/utility/iterator_traits.hpp>
#include <range/v3/utility/iterator_concepts.hpp>
#include <range/v3/utility/static_const.hpp>
#include <range/v3/utility/tagged_pair.hpp>
#include <range/v3/algorithm/tagspec.hpp>

namespace ranges
{
    inline namespace v3
    {
        /// \addtogroup group-algorithms
        /// @{
        struct copy_n_fn
        {
            template<typename I, typename O, typename P = ident,
#ifdef RANGES_WORKAROUND_MSVC_SFINAE_CONSTEXPR
                CONCEPT_REQUIRES_(
                    WeakInputIterator<I>::value &&
                    WeaklyIncrementable<O>::value &&
                    IndirectlyCopyable<I, O>::value
                )>
#else
                CONCEPT_REQUIRES_(
                    WeakInputIterator<I>() &&
                    WeaklyIncrementable<O>() &&
                    IndirectlyCopyable<I, O>()
                )>
#endif
            tagged_pair<tag::in(I), tag::out(O)>
            operator()(I begin, iterator_difference_t<I> n, O out) const
            {
                RANGES_ASSERT(0 <= n);
                auto norig = n;
                auto b = uncounted(begin);
                for(; n != 0; ++b, ++out, --n)
                    *out = *b;
                return {recounted(begin, b, norig), out};
            }
        };

        /// \sa `copy_n_fn`
        /// \ingroup group-algorithms
        namespace
        {
            constexpr auto&& copy_n = static_const<with_braced_init_args<copy_n_fn>>::value;
        }

        /// @}
    } // namespace v3
} // namespace ranges

#endif // include guard
