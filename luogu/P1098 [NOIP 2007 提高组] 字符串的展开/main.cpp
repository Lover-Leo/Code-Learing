#include <cctype>
#include <iostream>
#include <string>

int main()
{
    int p1, p2, p3;
    std::string s;
    std::cin >> p1 >> p2 >> p3 >> s;

    std::string ans;

    for (std::size_t i = 0; i < s.size(); ++i) {
        if (s[i] != '-' || i == 0 || i + 1 == s.size()) {
            ans += s[i];
            continue;
        }

        char left = s[i - 1];
        char right = s[i + 1];

        bool bothDigits = left >= '0' && left <= '9'
                       && right >= '0' && right <= '9';
        bool bothLower = left >= 'a' && left <= 'z'
                      && right >= 'a' && right <= 'z';

        if ((!bothDigits && !bothLower) || left >= right) {
            ans += '-';
            continue;
        }

        int start = (p3 == 1) ? left + 1 : right - 1;
        int stop  = (p3 == 1) ? right : left;
        int step  = (p3 == 1) ? 1 : -1;

        for (int ch = start; ch != stop; ch += step) {
            char out = static_cast<char>(ch);

            if (p1 == 3) {
                out = '*';
            } 
            else if (p1 == 2 && bothLower) {
                out = static_cast<char>(std::toupper(ch));
            }

            ans.append(p2, out);
        }
    }

    std::cout << ans << '\n';
    return 0;
}