#pragma once
#include <string>

class CIStreamLineReader;

class CIStreamLineReader
{
public:
    class iterator	//实现InputIterator
    {
    public:
        typedef ptrdiff_t difference_type;      //代表迭代器之间距离的类型, ptrdiff_t是标准的指针间差值的类型.
        typedef std::string value_type;         //代表迭代器指向的对象的 值类型.
        typedef const value_type* pointer;      //代表迭代器指向的对象的 指针类型.
        typedef const value_type& reference;    //代表迭代器指向对象的 常引用类型.
        typedef std::input_iterator_tag iterator_category;  //input_iterator_tag标识这个迭代器的类型是input iterator输入迭代器.
    public:
        iterator() noexcept
            : stream_(nullptr)
        {}
        explicit iterator(std::istream& is) noexcept
            : stream_(&is)
        {}
        reference operator*() const noexcept
        {
            return line_;
        }
        pointer operator->() const noexcept
        {
            return &line_;
        }

        iterator& operator++()
        {
            getline(*stream_, line_);
            if(!*stream_)
            {
                stream_ = nullptr;
            }
            return *this;
        }
        iterator operator++(int)
        {
            iterator tmp(*this);
            ++*this;
            return tmp;
        }
        bool operator==(const iterator& rhs) const noexcept
        {
            return stream_ == rhs.stream_;
        }
        bool operator!=(const iterator& rhs) const noexcept
        {
            return !operator==(rhs);
        }

    private:
        std::istream* stream_;
        std::string line_;
    };
    CIStreamLineReader() noexcept
        : stream_(nullptr)
    {}
    explicit CIStreamLineReader(std::istream& is) noexcept
        : stream_(&is)
    {}
    iterator begin()
    {
        return iterator(*stream_);
    }
    iterator end() const noexcept
    {
        return iterator();
    }
private:
    std::istream* stream_;
};