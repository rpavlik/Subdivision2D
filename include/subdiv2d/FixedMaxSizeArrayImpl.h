/** @file
    @brief Header

    @date 2020

    @author
    Ryan Pavlik
*/

// Copyright 2020, Collabora, Ltd.
// SPDX-License-Identifier: BSL-1.0

#ifndef INCLUDED_FixedMaxSizeArrayImpl_h
#define INCLUDED_FixedMaxSizeArrayImpl_h

#include <array>
#include <cstddef>
#include <stdexcept>

template <typename T, std::size_t MaxSize> class MaxSizeVector {
    using container_type = std::array<T, MaxSize>;

  public:
    using iterator = typename container_type::iterator;
    using const_iterator = typename container_type::const_iterator;
    void push_back(T const& val) {
        if (size_ == MaxSize) {
            throw std::runtime_error("Too many things!");
        }
        data_[size_] = val;
        ++size_;
    }
    template <typename... A> T& emplace_back(A&&... arg) {

        //! @todo this is not quite what emplace should do
        data_[size_] = T(std::forward<A>(arg)...);
        ++size_;
        return back();
    }

    T const& back() const { return data_[size_ - 1]; }
    T& back() { return data_[size_ - 1]; }

    T const& front() const { return data_[0]; }
    T& front() { return data_[0]; }

    iterator begin() { return data_.begin(); }
    const_iterator begin() const { return data_.begin(); }
    const_iterator cbegin() const { return data_.cbegin(); }
    iterator end() { return data_.begin() + size_; }
    const_iterator end() const { return data_.begin() + size_; }
    const_iterator cend() const { return data_.cbegin() + size_; }

  private:
    std::array<T, MaxSize> data_;
    std::size_t size_ = 0;
};
#endif // INCLUDED_FixedMaxSizeArrayImpl_h
