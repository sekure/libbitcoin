/**
 * Copyright (c) 2011-2015 libbitcoin developers (see AUTHORS)
 *
 * This file is part of libbitcoin.
 *
 * libbitcoin is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License with
 * additional permissions to the one published by the Free Software
 * Foundation, either version 3 of the License, or (at your option)
 * any later version. For more information see LICENSE.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef LIBBITCOIN_CHAIN_HEADER_HPP
#define LIBBITCOIN_CHAIN_HEADER_HPP

#include <cstdint>
#include <istream>
#include <string>
#include <vector>
#include <bitcoin/bitcoin/define.hpp>
#include <bitcoin/bitcoin/math/hash.hpp>
#include <bitcoin/bitcoin/utility/data.hpp>
#include <bitcoin/bitcoin/utility/reader.hpp>
#include <bitcoin/bitcoin/utility/writer.hpp>

namespace libbitcoin {
namespace chain {

class BC_API header
{
public:
    typedef std::vector<header> list;

    static header factory_from_data(const data_chunk& data,
        bool with_transaction_count = true);
    static header factory_from_data(std::istream& stream,
        bool with_transaction_count = true);
    static header factory_from_data(reader& source,
        bool with_transaction_count = true);
    static uint64_t satoshi_fixed_size_without_transaction_count();

    bool from_data(const data_chunk& data, bool with_transaction_count = true);
    bool from_data(std::istream& stream, bool with_transaction_count = true);
    bool from_data(reader& source, bool with_transaction_count = true);
    data_chunk to_data(bool with_transaction_count = true) const;
    void to_data(std::ostream& stream, bool with_transaction_count = true) const;
    void to_data(writer& sink, bool with_transaction_count = true) const;
    hash_digest hash() const;
    bool is_valid() const;
    void reset();
    uint64_t serialized_size(bool with_transaction_count = true) const;

    static const std::string command;

    uint32_t version;
    hash_digest previous_block_hash;
    hash_digest merkle;
    uint32_t timestamp;
    uint32_t bits;
    uint32_t nonce;

    // The longest size (64) of a protocol variable int is deserialized here.
    // WHen writing a block the size of the transaction collection is used.
    uint64_t transaction_count;
};

BC_API bool operator==(const header& left, const header& right);
BC_API bool operator!=(const header& left, const header& right);

} // namspace chain
} // namspace libbitcoin

#endif
