#include <cassert>
#include <format>
#include <iostream>
#include <sstream>
#include <stacktrace>
#include <thread>

using namespace std::string_literals;

static void basic_formatting_stacktrace() {
    const auto st  = std::stacktrace::current();
    const auto s   = std::format("{}", st);
    const auto exp = std::to_string(st);
    const auto s2  = std::format("{} {} {}", 123, st, "hello world");
    assert(s == exp);
    assert(s2 == "123 "s + exp + " hello world"s);
}
static void basic_formatting_stacktrace_entry() {
    const auto en  = std::stacktrace::current().at(0);
    const auto s   = std::format("{} {:04X}", en, 20);
    const auto exp = std::to_string(en) + " 0014";
    assert(s == exp);
}
static void basic_formatting_thread_id() {
    const auto id = std::this_thread::get_id();
    const auto s  = std::format("{}", id);
    std::stringstream ss{};
    ss << id;
    const auto exp = ss.str();
    assert(s == exp);
}
static void fill_and_width_stacktrace_entry() {
    const auto en               = std::stacktrace::current().at(0);
    const auto orig             = std::to_string(en);
    constexpr size_t full_width = 100ull;
    const std::string align_str((full_width - orig.size()) / 2, '+');
    const auto exp = align_str + orig + align_str;
    const auto s1  = std::format("{:+^{}}", en, full_width);
    const auto s2  = std::format("{:+^100}", en);
    assert(s1 == exp);
    assert(s2 == exp);
}
static void fill_and_width_thread_id() {
    const auto id = std::this_thread::get_id();
    std::ostringstream ss{};
    ss << id;
    const auto orig             = ss.str();
    constexpr size_t full_width = 10ull;
    const std::string align_str((full_width - orig.size()) / 2, '+');
    const auto exp = align_str + orig + align_str + (orig.size() % 2 == 0 ? ""s : "+"s);
    const auto s1  = std::format("{:+^{}}", id, full_width);
    const auto s2  = std::format("{:+^10}", id);
    assert(s1 == exp);
    assert(s2 == exp);
}

int main() {
    basic_formatting_stacktrace();
    basic_formatting_stacktrace_entry();
    basic_formatting_thread_id();
    fill_and_width_stacktrace_entry();
    fill_and_width_thread_id();
}
