#include <ankerl/unordered_dense.h>

#include <doctest.h>

#include <cstdint>    // for uint32_t
#include <functional> // for equal_to
#include <limits>     // for numeric_limits

TEST_CASE("max_load_factor") {
    auto map_60 = ankerl::unordered_dense::map<int, int>();
    auto map_90 = ankerl::unordered_dense::map<int, int>();
    REQUIRE(map_60.max_load_factor() == doctest::Approx(0.8));
    map_60.max_load_factor(0.6F);
    map_90.max_load_factor(0.9F);
    REQUIRE(map_60.max_load_factor() == doctest::Approx(0.6));
    REQUIRE(map_90.max_load_factor() == doctest::Approx(0.9));

    map_60[0];
    map_90[0];
    REQUIRE(map_60.bucket_count() == map_90.bucket_count());

    auto const old_bucket_count = map_60.bucket_count();

    // fill up maps until bucket_count increases
    int i = 0;
    while (map_60.bucket_count() == old_bucket_count) {
        map_60[++i];
    }
    while (map_90.bucket_count() == old_bucket_count) {
        map_90[++i];
    }

    // 0.9 max_load should fit more than map_60
    REQUIRE(map_90.size() > map_60.size());

    map_60.max_load_factor(0.9F);
    REQUIRE(map_60.max_load_factor() == map_90.max_load_factor());
}

TEST_CASE("key_eq") {
    auto const map = ankerl::unordered_dense::map<int, int>();
    auto eq = map.key_eq();
    REQUIRE(eq(5, 5));
}
