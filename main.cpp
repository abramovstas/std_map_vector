/*

Необходимо:

1.заполнить случайными числами от 1 до 9 значения контейнеров
vector[i] и map[i];

2.удалить случайное число элементов (не более 15) в каждом
контейнере;

3.после этого провести синхронизацию, чтобы в vector и map
остались только имеющиеся в обоих контейнерах элементы
(дубликаты не удалять).

*/

#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
#include <random>

using namespace std;

ostream& operator<<(ostream& stream, const pair<int, int>& itPair)
{
    stream << itPair.second;
    return  stream;
}

template<typename  First, typename Second>
void print(const string& info, const First& first, const Second& second)
{
    cout << info;

    for (auto it = first; it != second; ++it)
        cout << *it << " ";

    cout << endl;
}

vector<int> generate_vector(int range_begin, int range_end, const uint container_size)
{
    random_device rnd_device;
    mt19937 mersenne_engine {rnd_device()};  // Generates random integers
    uniform_int_distribution<int> dist {range_begin, range_end};

    auto gen = [&dist, &mersenne_engine](){
        return dist(mersenne_engine);
    };

    vector<int> vec(container_size);
    generate(begin(vec), end(vec), gen);

    print("Generate vector ", vec.begin(), vec.end());

    return vec;
}

map<int, int> generate_map(int range_begin, int range_end, const uint container_size)
{
    random_device rnd_device;
    mt19937 mersenne_engine {rnd_device()};  // Generates random integers
    uniform_int_distribution<int> dist(range_begin, range_end);

    map<int, int> dict;
    for (uint i = 0; i < container_size; ++i)
        dict.insert(make_pair(i, dist(mersenne_engine)));

    print("Generate map    ", dict.begin(), dict.end());

    return dict;
}

vector<int> sample(const vector<int>& vec, uint p)
{
    vector<int> tmp(begin(vec), end(vec));
    shuffle(begin(tmp), end(tmp), default_random_engine {});

    if (uint(p) > tmp.size())
        return  tmp;

    tmp.erase(tmp.begin(), tmp.begin()+p);

    return tmp;
}

map<int, int> sample(const map<int, int>& data_in, uint p)
{
    vector<int> tmp_vec;
    for(const auto& item : data_in)
        tmp_vec.push_back(item.second);

    vector<int> tmp_vec2(sample(tmp_vec, p));
    map<int, int> dict;
    for (uint var = 0; var < tmp_vec2.size(); ++var) {
        dict.insert(make_pair(var, tmp_vec2.at(var)));
    }

    print("Sampled map    ", dict.begin(), dict.end());

    return dict;
}

void synchronize_vec(const map<int, int>& dict, vector<int>& vec)
{
    vector<int> tmp_vec;
    for (const auto& item : dict)
        tmp_vec.push_back(item.second);

    for (auto it = vec.begin(); it != vec.end(); ++it) {
        auto result = find(begin(tmp_vec), end(tmp_vec), *it);
        if (result == end(tmp_vec)) {
            vec.erase(it);
            --it;
        }
    }

    if (vec.size() > 0)
        print("Synchronized vec    ", vec.begin(), vec.end());
}

void synchronize_dict(map<int, int>& dict, const vector<int>& vec)
{
    for (auto it = dict.begin(); it != dict.end();/* ++it*/) {
        auto result = find(begin(vec), end(vec), it->second);
        if (result == end(vec))
            it = dict.erase(it);
        else ++it;
    }

    if (dict.size() > 0)
        print("Synchronize map    ", dict.begin(), dict.end());
}

int main()
{
    const int container_size = 20;
    const int remove_count = 15;

    vector<int> vec(generate_vector(1, 9, container_size));
    map<int, int> dict(generate_map(1, 9, container_size));

    vector<int> vec_sample(sample(vec, remove_count));
    print("Sampled vector ", vec_sample.begin(), vec_sample.end());
    map<int, int> dict_sample(sample(dict, remove_count));

    synchronize_dict(dict_sample, vec_sample);
    synchronize_vec(dict_sample, vec_sample);
}
