//
// Copyright Aliaksei Levin (levlam@telegram.org), Arseny Smirnov (arseny30@gmail.com) 2014-2020
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#pragma once

#include "td/telegram/td_api.h"

#include "td/utils/common.h"
#include "td/utils/StringBuilder.h"

#include <functional>
#include <type_traits>

namespace td {

class GroupCallId {
 public:
  GroupCallId() = default;

  explicit GroupCallId(int32 group_call_id) : id(group_call_id) {
  }

  template <class T, typename = std::enable_if_t<std::is_convertible<T, int32>::value>>
  GroupCallId(T group_call_id) = delete;

  bool is_valid() const {
    return id > 0;
  }

  int32 get() const {
    return id;
  }

  auto get_group_call_id_object() const {
    return td_api::make_object<td_api::groupCallId>(id);
  }

  bool operator==(const GroupCallId &other) const {
    return id == other.id;
  }

 private:
  int32 id{0};
};

struct GroupCallIdHash {
  std::size_t operator()(GroupCallId group_call_id) const {
    return std::hash<int32>()(group_call_id.get());
  }
};

inline StringBuilder &operator<<(StringBuilder &sb, const GroupCallId group_call_id) {
  return sb << "group call " << group_call_id.get();
}

}  // namespace td