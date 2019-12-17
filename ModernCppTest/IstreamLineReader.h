#pragma once
#include <string>

class CIStreamLineReader;

class CIStreamLineReader
{
public:
    class iterator	//ʵ��InputIterator
    {
    public:
        typedef ptrdiff_t difference_type;      //���������֮����������, ptrdiff_t�Ǳ�׼��ָ����ֵ������.
        typedef std::string value_type;         //���������ָ��Ķ���� ֵ����.
        typedef const value_type* pointer;      //���������ָ��Ķ���� ָ������.
        typedef const value_type& reference;    //���������ָ������ ����������.
        typedef std::input_iterator_tag iterator_category;  //input_iterator_tag��ʶ�����������������input iterator���������.
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