#include <ankerl/unordered_dense.h>

#include <doctest.h>

#include <deque>

static_assert(
    ankerl::unordered_dense::detail::is_detected_v<ankerl::unordered_dense::detail::detect_iterator, std::deque<int>>);

static_assert(
    !ankerl::unordered_dense::detail::is_detected_v<ankerl::unordered_dense::detail::detect_iterator, std::allocator<int>>);

TEST_CASE("custom_container") {
    using map_t = ankerl::unordered_dense::
        map<int, std::string, ankerl::unordered_dense::hash<int>, std::equal_to<int>, std::deque<std::pair<int, std::string>>>;

    auto map = map_t();

    for (int i = 0; i < 10; ++i) {
        map[i] = std::to_string(i);
    }

    REQUIRE(std::is_same_v<std::deque<std::pair<int, std::string>>, typename map_t::value_container_type>);
    std::deque<std::pair<int, std::string>> container = std::move(map).extract();

    auto m2 = map_t();
    m2 = map;

    auto map2 = map;
    std::swap(map2, map);
}
