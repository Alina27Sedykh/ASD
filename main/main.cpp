#include "skiplist.h"
#include <iostream>
#include <iomanip>
#include <ctime>
#include "heap.h"
#include "PriorityQueue.h"
#include "HashTable.h"
static Priority getPriority(const string& type)
{
    if (type == "платно" || type == "без записи на платной основе")
    {
        return Priority::PAID;
    }
    if (type == "по записи")
    {
        return Priority::APPOINTMENT;
    }
    return Priority::WALK_IN;
}
template<class T>
HashTableChaining<T> merge_dict(const std::vector<std::pair<std::string, T>>& dict1,const std::vector<std::pair<std::string, T>>& dict2)
{
    HashTableChaining<T> result;
    for (const auto& pair : dict1) 
    {
        result.insert(pair.first, pair.second);
    }
    for (const auto& pair : dict2) 
    {
        if (!result.consist(pair.first))
        {
            result.insert(pair.first, pair.second);
        }
    }

    return result;
}
int main()
{
    setlocale(LC_ALL, "Rus");
    std::cout << "=== Объединение словарей (хеш-таблица методом цепочек) ===\n";

    std::vector<std::pair<std::string, int>> dict1 = {
        {"hash", 10072},
        {"list", 13736},
        {"vector", 16262},
        {"massive", 10626},
        {"table", 10083}
    };

    std::vector<std::pair<std::string, int>> dict2 = {
        {"table", 22727},
        {"vector", 20728},
        {"queue", 28282},
        {"stack", 20607},
        {"list", 20618}
    };

    std::cout << "\nСловарь 1:\n";
    for (const auto& p : dict1) 
    {
        std::cout << "  " << p.first << " -> " << p.second << "\n";
    }

    std::cout << "\nСловарь 2:\n";
    for (const auto& p : dict2) 
    {
        std::cout << "  " << p.first << " -> " << p.second << "\n";
    }

    auto result = merge_dict(dict1, dict2);

    std::cout << "\nРезультат объединения:\n";
    result.print(std::cout);

    std::cout << "\nРазмер: " << result.size() << "\n";
    std::cout << "Ожидаемый размер: 7\n";

    std::cout << "\nПроверка значений:\n";
    std::cout << "  hash -> " << result.find("hash") << " (ожидается 10072)\n";
    std::cout << "  list -> " << result.find("list") << " (ожидается 13736 из 1-го словаря)\n";
    std::cout << "  vector -> " << result.find("vector") << " (ожидается 16262 из 1-го)\n";
    std::cout << "  massive -> " << result.find("massive") << " (ожидается 10626)\n";
    std::cout << "  table -> " << result.find("table") << " (ожидается 10083 из 1-го)\n";
    std::cout << "  queue -> " << result.find("queue") << " (ожидается 28282)\n";
    std::cout << "  stack -> " << result.find("stack") << " (ожидается 20607)\n";

    return 0;
};
    /*setlocale(LC_ALL, "Rus");
    vector<tuple<int, int, string, string>> rawData =
    {
        {12, 30, "Иванов", "по записи"},
        {12, 35, "Петров", "без записи"},
        {12, 50, "Воронин", "по записи"},
        {12, 55, "Сидоров", "платно"},
        {13, 10, "Васильев", "по записи"},
        {13, 15, "Михайлов", "без записи"},
        {14, 5,  "Борисов", "платно"},
        {14, 7,  "Владимиров", "платно"},
        {14, 30, "Федоров", "по записи"},
        {14, 31, "Шишкин", "платно"},
        {14, 50, "Нестеров", "по записи"}
    };

    sort(rawData.begin(), rawData.end());

    PriorityQueue<string> pq;
    vector<string> result;

    int currentTime = 12 * 60 + 30;
    size_t idx = 0;
    const int DURATION = 20;

    cout << "прием пациента\n" << endl;

    while (idx < rawData.size() || !pq.empty())
    {

        while (idx < rawData.size())
        {
            int h = get<0>(rawData[idx]);
            int m = get<1>(rawData[idx]);
            int arrivalTime = h * 60 + m;

            if (arrivalTime <= currentTime)
            {
                string name = get<2>(rawData[idx]);
                string type = get<3>(rawData[idx]);

                pq.enqueue(name, getPriority(type));

                cout << "[" << h << ":" << m << "] пришел: " << name << endl;
                idx++;
            }
            else
            {
                break;
            }
        }

        if (!pq.empty())
        {
            string patient = pq.dequeue();
            result.push_back(patient);

            cout << ">>> прием: " << patient
                << " (начало в " << currentTime / 60 << ":" << currentTime % 60 << ")\n";

            currentTime += DURATION;

            cout << "    Следующее свободное время: " << currentTime / 60 << ":" << currentTime % 60 << "\n";
        }
        else if (idx < rawData.size())
        {
            int h = get<0>(rawData[idx]);
            int m = get<1>(rawData[idx]);
            currentTime = h * 60 + m;
            cout << "ожидание  до " << h << ":" << m << " ---\n";
        }
    }
    cout << "\nПОРЯДОК ПРИЁМА\n";
    for (size_t i = 0; i < result.size(); i++)
    {
        cout << i + 1 << ". " << result[i] << endl;
    }

    return 0;*/

    



















//srand(static_cast<unsigned>(time(nullptr)));
    //SkipList<int, double> skipList(4);
    //skipList.insert(10, 12.15);
    //skipList.insert(5, 4.0);
    //skipList.insert(20, 7.523);
    //skipList.insert(15, 87.2);
    //skipList.insert(25, 78.5);
    //skipList.insert(3, 5.8);
    //skipList.insert(30, 58.4238);
    //skipList.insert(8, 8.769455);
    //skipList.insert(12, 34.5);
    //skipList.insert(18, 92.1);

    //std::cout << "SkipList:" << std::endl;
    //std::cout << "----------------------------------------" << std::endl;
    ////skipList.print(std::cout);

    //return 0;
  /*  Heap<int> heap;
    heap.insert(10);
    heap.insert(5);
    heap.insert(15);
    heap.insert(3);
    heap.insert(8);

    cout << "Куча после вставок: ";
    heap.print();

    int mn = heap.pop();
    cout << "popped: " << mn << endl;

    cout << "Куча после pop: ";
    heap.print();

    heap.erase();
    cout << "Куча после erase(): ";
    heap.print();

    cout << "Извлечение всех элементов: ";
    while (!heap.is_empty())
    {
        cout << heap.pop() << " ";
    }
    cout << endl;
    std::vector<int>vec = { 5, 4, 8, 6, 9 ,3};
    Heap<int> heap1;
    for (int i = 0; i < 6; i++)
    {
        heap1.insert(vec[i]);
    }
    for (int i = 0; i < 6; i++)
    {
        vec[i] = heap1.pop();
        cout << vec[i] << " ";
    }
    return 0;*/

   
