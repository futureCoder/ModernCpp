#pragma once
#include <utility>
namespace Jason
{
	class Counter
	{
	public:
		explicit Counter(long long nCnt) noexcept 
			: __count(nCnt) {}
		void Increase() noexcept
		{
			++__count;
		}
		long long Reduce() noexcept
		{
			return --__count;
		}
		long long Get() const  noexcept { return __count; }
	private:
		long long __count;
	};

	template<typename T>
	class smart_ptr final
	{
	public:
		template<typename U>
		friend class smart_ptr;		//注意不是smart_ptr<U> 

		explicit smart_ptr(T* ptr = nullptr)
		: __ptr(ptr) 
		{
			if(__ptr)
			{
				__refCnt = new Counter(1);
			}
		}
		~smart_ptr() noexcept
		{
			if(__ptr && !__refCnt->Reduce())
			{
				delete __ptr;
				delete __refCnt;
			}
		}
		smart_ptr(const smart_ptr<T>& rhs) noexcept
			:__ptr(rhs.__ptr)
		{
			if(__ptr)
			{
				rhs.__refCnt->Increase();
				__refCnt = rhs.__refCnt;
			}
		}

		template<typename U>
		smart_ptr(const smart_ptr<U>& rhs) noexcept
			:__ptr(rhs.__ptr)
		{
			if(__ptr)
			{
				rhs.__refCnt->Increase();
				__refCnt = rhs.__refCnt;
			}
		}

		template<typename U>
		smart_ptr(smart_ptr<U>&& rhs) noexcept
			:__ptr(rhs.__ptr)
		{
			if (__ptr)
			{
				rhs.__refCnt->Increase();
				__refCnt = rhs.__refCnt;
				rhs.__ptr = nullptr;
			}
		}

		template<typename U>
		smart_ptr(const smart_ptr<U>& rhs, T* ptr) noexcept
			:__ptr(ptr)
		{
			if(__ptr)
			{
				rhs.__refCnt->Increase();
				__refCnt = rhs.__refCnt;
			}
		}

		smart_ptr& operator=(smart_ptr rhs) noexcept
		{
			//smart_ptr<T>(rhs).swap(this);	//进一步简化，将const smart_ptr<T>& 形式的参数改变为 smart_ptr , 即直接用参数作为临时对象
			rhs.swap(*this);
			return *this;
		}

		T& operator*() const noexcept { return *__ptr; }
		T* operator->() const noexcept { return __ptr; }
		operator bool() const noexcept { return __ptr; }

		T* Get() const { return this(); }

		long Count() const noexcept
		{
			if(__ptr)
			{
				return __refCnt->Get();
			}
			return 0;
		}

		void swap(smart_ptr<T>&& rhs) noexcept
		{
			using std::swap;
			swap(__ptr, rhs.__ptr);
			swap(__refCnt, rhs.__refCnt);
		}

	private:
		T* __ptr;
		Counter* __refCnt;
	};

	template<typename T>
	void swap(smart_ptr<T> lhs, smart_ptr<T> rhs) noexcept
	{
		lhs.swap(rhs);
	}

	template<typename T, typename U>
	smart_ptr<U> static_cast_smart_ptr(const smart_ptr<T>& rhs)  noexcept
	{
		U* ptr = static_cast<U>(rhs.Get());
		return smart_ptr<U>(rhs, ptr);
	}
	template<typename T, typename U>
	smart_ptr<U> dynamic_cast_smart_ptr(const smart_ptr<T>& rhs)
	{
		U* ptr = dynamic_cast<U>(rhs.Get());
		return smart_ptr<U>(rhs, ptr);
	}
	template<typename T, typename U>
	smart_ptr<U> const_cast_smart_ptr(const smart_ptr<T>& rhs)
	{
		U* ptr = const_cast<U>(rhs.Get());
		return smart_ptr<U>(rhs, ptr);
	}
	template<typename T, typename U>
	smart_ptr<U> reinterpret_cast_smart_ptr(const smart_ptr<T>& rhs)
	{
		U* ptr = reinterpret_cast<U>(rhs.Get());
		return smart_ptr<U>(rhs, ptr);
	}

}