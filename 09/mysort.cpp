#include "mysort.hpp"


struct positional_value
{
    uint64_t val, pos, max;
    bool operator>(const positional_value& other) const
    {
        return val > other.val;
    }
};

void sort(std::mutex& mut, std::ifstream& input, std::ofstream& tmp, size_t buf_size)
{
    std::unique_ptr<uint64_t[]> arr(new uint64_t[buf_size / sizeof(uint64_t)]);
    for (;;)
    {
        {
            std::lock_guard<std::mutex> lock(mut);
            input.read((char*)arr.get(), buf_size);
        }
        size_t read_count = input.gcount();

        if (read_count == 0)
            break;
        std::sort(arr.get(), arr.get() + read_count / sizeof(uint64_t));

        {
            std::lock_guard<std::mutex> lock(mut);
            tmp.write((char*)&read_count, sizeof(size_t));
            tmp.write((char*)arr.get(), read_count);
        }
    }
}


void mysort(const std::string& input_path, const std::string& output_path)
{
    size_t buf_size = 8388608; 

    std::ifstream input(input_path, std::ios::binary);
    std::ofstream output(output_path, std::ios::binary); 
    std::ofstream tmp("tmp.bin", std::ios::binary);

    if (!input)
        throw std::runtime_error("Error input file");
    if (!output)
        throw std::runtime_error("Error output file");
    if (!tmp)
        throw std::runtime_error("Error tmp file");

    std::mutex mut;

    auto sort_function = std::bind(sort, std::ref(mut), std::ref(input), std::ref(tmp), buf_size);

    std::thread th1 (sort_function);
    std::thread th2 (sort_function);

    th1.join();
    th2.join();

    tmp.close();
    input.close();

    input.open("tmp.bin", std::ios::binary);
    if (!input)
        throw std::runtime_error("Error tmp file\n" );

    std::priority_queue<positional_value, std::vector<positional_value>, std::greater<positional_value>> queue;

    for (;;)
    {
        uint64_t buf;
        size_t count;

        if (!input.read((char*)&count, sizeof(size_t)))
            break;

        input.read((char*)&buf, sizeof(uint64_t));
        queue.push({ buf, static_cast<uint64_t>(input.tellg()),
            static_cast<uint64_t>(input.tellg()) + count - sizeof(uint64_t) });
        input.seekg(count - sizeof(uint64_t), std::ios::cur);
    }
    input.clear();

    while (!queue.empty())
    {
        auto smallest = queue.top();
        queue.pop();

        output.write((char*)&(smallest.val), sizeof(uint64_t));
        if (smallest.pos >= smallest.max)
            continue;

        input.seekg(smallest.pos);
        uint64_t buf;

        input.read((char*)&buf, sizeof(uint64_t));
        queue.push({ buf, smallest.pos + sizeof(uint64_t), smallest.max });
    }
}