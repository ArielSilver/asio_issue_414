//
// execution/sender.hpp
// ~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_EXECUTION_SENDER_HPP
#define BOOST_ASIO_EXECUTION_SENDER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/type_traits.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace execution {
namespace detail {

namespace sender_base_ns { struct sender_base {}; }

template <typename S, typename = void>
struct sender_traits_base
{
  typedef void asio_execution_sender_traits_base_is_unspecialised;
};

template <typename S>
struct sender_traits_base<S,
    typename enable_if<
      is_base_of<sender_base_ns::sender_base, S>::value
    >::type>
{
};

} // namespace detail

/// Base class used for tagging senders.
#if defined(GENERATING_DOCUMENTATION)
typedef unspecified sender_base;
#else // defined(GENERATING_DOCUMENTATION)
typedef detail::sender_base_ns::sender_base sender_base;
#endif // defined(GENERATING_DOCUMENTATION)

/// Traits for senders.
template <typename S>
struct sender_traits
#if !defined(GENERATING_DOCUMENTATION)
  : detail::sender_traits_base<S>
#endif // !defined(GENERATING_DOCUMENTATION)
{
};

namespace detail {

template <typename S, typename = void>
struct has_sender_traits : true_type
{
};

template <typename S>
struct has_sender_traits<S,
    typename enable_if<
      is_same<
        typename boost::asio::execution::sender_traits<
          S>::asio_execution_sender_traits_base_is_unspecialised,
        void
      >::value
    >::type> : false_type
{
};

} // namespace detail

/// The is_sender trait detects whether a type T satisfies the
/// execution::sender concept.

/**
 * Class template @c is_sender is a type trait that is derived from @c
 * true_type if the type @c T meets the concept definition for a sender,
 * otherwise @c false_type.
 */
template <typename T>
struct is_sender :
#if defined(GENERATING_DOCUMENTATION)
  integral_constant<bool, automatically_determined>
#else // defined(GENERATING_DOCUMENTATION)
  integral_constant<bool,
    is_move_constructible<typename remove_cvref<T>::type>::value
      && detail::has_sender_traits<typename remove_cvref<T>::type>::value
  >
#endif // defined(GENERATING_DOCUMENTATION)
{
};

#if defined(BOOST_ASIO_HAS_VARIABLE_TEMPLATES)

template <typename T>
BOOST_ASIO_CONSTEXPR const bool is_sender_v = is_sender<T>::value;

#endif // defined(BOOST_ASIO_HAS_VARIABLE_TEMPLATES)

#if defined(BOOST_ASIO_HAS_CONCEPTS)

template <typename T>
BOOST_ASIO_CONCEPT sender = is_sender<T>::value;

#define BOOST_ASIO_EXECUTION_SENDER ::boost::asio::execution::sender

#else // defined(BOOST_ASIO_HAS_CONCEPTS)

#define BOOST_ASIO_EXECUTION_SENDER typename

#endif // defined(BOOST_ASIO_HAS_CONCEPTS)

} // namespace execution
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_EXECUTION_SENDER_HPP