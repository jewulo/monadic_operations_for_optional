// monadic_operations_for_optional.cpp : This file contains the 'main' function. Program execution begins and ends there.
// https://www.cppstories.com/2023/monadic-optional-ops-cpp23/

#include <iostream>
#include <optional>

struct UserProfile {
    std::string name;
    int age { -1 };
};

std::optional<UserProfile> fetch_from_cache(int userId)
{
    return std::nullopt;
}

std::optional<UserProfile> fetch_from_server(int userId)
{
    return UserProfile{ "Alice", 30 };  // example data
}

std::optional<int> extract_age(const UserProfile& profile)
{
    if (profile.age > 0) return profile.age;
    return std::nullopt;

}

namespace cpp20
{
    void run()
    {
        const int user_id = 12345;
        std::optional<int> age_next;

        std::optional<UserProfile> profile = fetch_from_cache(user_id);

        if (!profile)
            profile = fetch_from_server(user_id);

        if (profile) {
            // optional is modelled as a pointer. It needs to be dereferenced with *
            std::optional<int> age = extract_age(*profile);

            if (age)
                age_next = *age + 1;
        }

        if (age_next)
            std::cout << std::format("Next year the user will be {} years old\n", *age_next);
        else
            std::cout << "Failed to determine user's age.\n";
    }
}

namespace cpp23
{
    void run()
    {
        const int user_id = 12345;

        const auto age_next = fetch_from_cache(user_id)
            .or_else([&]() {return fetch_from_server(user_id); })
            .and_then(extract_age)
            .transform([](int age) { return age + 1; });

        if (age_next)
            std::cout << std::format("Next year the user will be {} years old\n", *age_next);
        else
            std::cout << "Failed to determine user's age.\n";
    }
}
int main()
{
    cpp20::run();
    cpp23::run();

    std::cin.get();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
