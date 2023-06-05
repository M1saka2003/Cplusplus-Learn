#include <iostream>
#include <ranges>

template<std::ranges::range Args_range, typename value_type>
constexpr void iota(Args_range &args_range, value_type &&value) noexcept {
    auto iota_iter = []<std::ranges::range lambda_Args_range>
        (auto self, lambda_Args_range &cur_range, value_type &value)constexpr noexcept -> void {
        for (auto &i : cur_range) {
            using sub_range = std::ranges::range_value_t<lambda_Args_range>;
            if constexpr (std::ranges::range<sub_range> && !std::is_convertible_v<sub_range, value_type>) {
                self(self, i, value);
            } else {
                i = value++;
            }
        }
    };
    iota_iter(iota_iter, args_range, value);
}
