#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <forward_list>

namespace A
{
    int x;

    void func()
    {
        ++x;
    }   
}

namespace B
{
    int y;
}

template<typename T>
void print_v(const std::string& s, const T& v)
{
    std::cout << s << std::endl;
    std::copy(v.begin(), v.end(),
        std::ostream_iterator<typename T::value_type>
            (std::cout, ", "));
    std::cout << std::endl;
}

int main()
{
    A::x++;
    A::func();
    ++A::x;

    B::y++;
    std::cout << "A: " << A::x << " "
              << B::y << std::endl;

    int y;
    std::cout << "newY: " << y << std::endl;

    int z{2};
    std::cout << "newZ: " << z << std::endl;

    {
        std::vector<int> v {1, 2, 3, 4, 5, 6, 7, 8, 9};
        std::vector<int> u {11, 12, 13, 14, 15};

        print_v("original:", v);
        for (auto x = u.begin(); x != u.end(); ++x)
            v.push_back(*x);    
        print_v("push:", v);

        std::rotate(v.begin()+4, v.begin()+9, v.end());
        print_v("rotate:", v);
    }

    {
        std::vector<int> v
            {1, 2, 3, 4, 5, 6, 7, 8, 9};
        std::vector<int> u
            {11, 12, 13, 14, 15, 16, 17, 18, 19};

        print_v("original:", v);
        for (auto x = u.begin(); x != u.end(); ++x)
            v.push_back(*x);    
        std::swap_ranges(
            v.begin(), v.begin()+9, v.begin()+9);
        print_v("swap_ranges:", v);
    }

    {
        std::vector<int> v
            {1, 2, 3, 4, 5, 6, 7, 8, 9};
        std::vector<int> u
            {11, 12, 13, 14, 15, 16, 17, 18, 19};

        std::copy(u.begin(), u.end(),
                    std::back_inserter(v));
        print_v("copy:", v);
        auto d = std::distance(v.begin(), v.end());
        auto m = d / 2;
        auto vbi = v.begin();
        for (auto i = 0; i < d/2-1; ++i)
        {
            std::rotate(vbi+i, vbi+m-1, vbi+m);
            std::rotate(vbi+m+i, v.end()-1, v.end());
            print_v("rotate:", v);
        }
        std::swap_ranges(
            v.begin(), v.begin()+m, v.begin()+m);
        print_v("swap_ranges:", v);
    }

    {
        std::forward_list<int> v
            {11, 12, 13, 14, 15, 16, 17, 18, 19};
        std::forward_list<int> u
            {21, 22, 23, 24, 25, 26, 27, 28, 29};

        auto d = std::distance(v.begin(), v.end());
        auto e = v.begin();
        std::advance(e, d-1);
        v.insert_after(e, u.begin(), u.end());
        print_v("insert_after:", v);
        d = std::distance(v.begin(), v.end());
        auto vbi = v.begin();
        auto ve1 = vbi;
        std::advance(ve1, d-1);
        for (; vbi != ve1;)
        {
            std::rotate(vbi, ve1, v.end());
            ++vbi;
            print_v("rotate:", v);
        }
    }
}
