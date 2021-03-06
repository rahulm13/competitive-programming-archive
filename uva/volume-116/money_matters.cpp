#include <iostream>
#include <map>
#include <vector>

using namespace std;

inline void use_io_optimizations()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
}

class UnionFind
{
public:
    UnionFind(unsigned int items):
        parents(items),
        ranks(items),
        components(items)
    {
        for (unsigned int i {0}; i < components; ++i)
        {
            parents[i] = i;
        }
    }

    void link(unsigned int item, unsigned int another_item)
    {
        unsigned int root_i {find(item)};
        unsigned int root_j {find(another_item)};

        if (root_i == root_j)
        {
            return;
        }

        if (ranks[root_i] < ranks[root_j])
        {
            parents[root_i] = root_j;
        }
        else if (ranks[root_i] > ranks[root_j])
        {
            parents[root_j] = root_i;
        }
        else
        {
            parents[root_j] = root_i;
            ++ranks[root_i];
        }

        --components;
    }

    unsigned int find(unsigned int item)
    {
        unsigned int root {item};

        while (root != parents[root])
        {
            root = parents[root];
        }

        while (item != root)
        {
            unsigned int parent {parents[item]};

            parents[item] = root;
            item          = parent;
        }

        return root;
    }

    bool connected(unsigned int item, unsigned int another_item)
    {
        return find(item) == find(another_item);
    }

    unsigned int size() const
    {
        return components;
    }

private:
    std::vector<unsigned int> parents;
    std::vector<unsigned int> ranks;

    unsigned int components;
};

bool can_be_distributed(const vector<int>& money, UnionFind& groups)
{
    map<unsigned int, int> group_distribution;

    for (vector<int>::size_type i {0}; i < money.size(); ++i)
    {
        group_distribution[groups.find(i)] += money[i];
    }

    for (const auto& group_and_money : group_distribution)
    {
        if (group_and_money.second != 0)
        {
            return false;
        }
    }

    return true;
}

int main()
{
    use_io_optimizations();

    unsigned int test_cases;
    cin >> test_cases;

    for (unsigned int i {0}; i < test_cases; ++i)
    {
        unsigned int friends;
        unsigned int friendships;

        cin >> friends >> friendships;

        vector<int> money(friends);

        for (unsigned int j {0}; j < friends; ++j)
        {
            cin >> money[j];
        }

        UnionFind groups(friends);

        for (unsigned int j {0}; j < friendships; ++j)
        {
            unsigned int person_a;
            unsigned int person_b;

            cin >> person_a >> person_b;

            groups.link(person_a, person_b);
        }

        cout << (can_be_distributed(money, groups) ? "POSSIBLE" : "IMPOSSIBLE");
        cout << '\n';
    }

    return 0;
}
