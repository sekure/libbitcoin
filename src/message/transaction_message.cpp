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
#include <bitcoin/bitcoin/message/transaction_message.hpp>

#include <istream>
#include <utility>
#include <bitcoin/bitcoin/chain/input.hpp>
#include <bitcoin/bitcoin/chain/output.hpp>
#include <bitcoin/bitcoin/utility/data.hpp>
#include <bitcoin/bitcoin/utility/reader.hpp>

namespace libbitcoin {
namespace message {

transaction_message transaction_message::factory_from_data(
    const data_chunk& data)
{
    transaction_message instance;
    instance.from_data(data);
    return instance;
}

transaction_message transaction_message::factory_from_data(
    std::istream& stream)
{
    transaction_message instance;
    instance.from_data(stream);
    return instance;
}

transaction_message transaction_message::factory_from_data(reader& source)
{
    transaction_message instance;
    instance.from_data(source);
    return instance;
}

transaction_message::transaction_message()
  : transaction(), originator_(0)
{
}

transaction_message::transaction_message(const transaction& other)
  : transaction_message(other.version, other.locktime, other.inputs,
        other.outputs)
{
}

transaction_message::transaction_message(const transaction_message& other)
  : transaction_message(other.version, other.locktime, other.inputs,
    other.outputs)
{
}

transaction_message::transaction_message(uint32_t version, uint32_t locktime,
    const chain::input::list& inputs, const chain::output::list& outputs)
  : transaction(version, locktime, inputs, outputs), originator_(0)
{
}

transaction_message::transaction_message(transaction&& other)
  : transaction_message(other.version, other.locktime,
        std::forward<chain::input::list>(inputs),
        std::forward<chain::output::list>(outputs))
{
}

transaction_message::transaction_message(transaction_message&& other)
  : transaction_message(other.version, other.locktime,
        std::forward<chain::input::list>(inputs),
        std::forward<chain::output::list>(outputs))
{
}

transaction_message::transaction_message(uint32_t version, uint32_t locktime,
    chain::input::list&& inputs, chain::output::list&& outputs)
  : transaction(version, locktime, std::forward<chain::input::list>(inputs),
        std::forward<chain::output::list>(outputs)),
    originator_(0)
{
}

transaction_message& transaction_message::operator=(
    transaction_message&& other)
{
    version = other.version;
    locktime = other.locktime;
    inputs = std::move(other.inputs);
    outputs = std::move(other.outputs);
    originator_ = other.originator_;
    return *this;
}

uint64_t transaction_message::originator() const
{
    return originator_;
}

void transaction_message::set_originator(uint64_t value)
{
    originator_ = value;
}

} // namspace message
} // namspace libbitcoin
