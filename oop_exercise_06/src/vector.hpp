#pragma once
#include <stdexcept>
#include <memory>

template<typename T, typename Allocator = std::allocator<T>>
class Vector {
public:
	using allocator_type = typename Allocator::template rebind<T>::other;
	
	explicit Vector()
		: buf_{ nullptr, { alloc_, 0 } }, size_{ 0 }, cap_{ 0 }, alloc_{}
	{}
	explicit Vector(const int size)
		: Vector(size, size)
	{}
	explicit Vector(const int size, const int cap) : Vector() {
		this->size_ = size;
		this->cap_ = cap;
		
		if (size_ > cap_)
			throw std::invalid_argument("size_ of vector can't be more then capacity.");
		auto new_buf = std::unique_ptr<T[], ptr_deleter>{ alloc_.allocate(cap_), { alloc_, (std::size_t)cap_ } };
		this->buf_.swap(new_buf);
	}

	Vector(const std::initializer_list<T>& list) 
		: Vector(list.size())
	{
		int count = 0;
		for (const T& el : list) {
			this->buf_.get()[count] = el;
			++count;
		}
	}

	Vector(Vector<T, Allocator>& vec)
		: Vector(vec.size_, vec.cap_)
	{
		for (int i = 0; i < vec.size_; i++) {
			this->buf_[i] = vec[i];
		}
	}

	int size() const {
		return this->size_;
	}

	T& operator[] (const int i) {
		if (i < 0 || i >= this->size_)
			throw std::out_of_range("Out of range");
		return this->buf_.get()[i];
	}

	// Итераторы
	class iterator
	{
		friend class Vector;
	public:
		using iterator_category = std::forward_iterator_tag;
		using value_type = T;
		using difference_type = int;
		using pointer = T*;
		using reference = T&;

		iterator(Vector* vec, T* ptr) : vec{vec}, ptr{ptr}
		{}

		bool operator== (const iterator& it) const {
			return it.vec == vec && it.ptr == ptr;
		}
		bool operator!= (const iterator& it) const {
			return it.vec != vec || it.ptr != ptr;
		}
		T& operator* () {
			is_valid();
			return *ptr;
		}
		T* operator-> () {
			is_valid();
			return ptr;
		}

		iterator& operator++() {
			is_valid();
			ptr++;
			return *this;
		}
		iterator operator++(int) const {
			is_valid();
			return { vec, ptr + 1 };
		}

	private:
		void is_valid() const {
			if (vec == nullptr || ptr == nullptr)
				throw std::runtime_error("Nullptr iterator");
			if (vec->buf_.get() + vec->size_ <= ptr)
				throw std::out_of_range("Iterator gt or eq end");
		}
		Vector<T, Allocator>* vec;
		T* ptr;
	};

	iterator begin() {
		return { this, buf_.get() };
	}
	iterator end() {
		return {this, buf_.get() + size_};
	}
	// Возвращает итератор, который указыавет на элемент под номером index
	iterator iterator_by_index(int index) {
		if (index < 0 || index > size_)
			throw std::out_of_range("bad index");

		return {this, buf_.get() + index};
	}
	
	void push_back(const T& val) {
		if (size_ >= cap_)
			grow();
		buf_.get()[size_] = val;
		++size_;
	}
	void push_back(T&& val) {
		if (size_ >= cap_)
			grow();
		buf_.get()[size_] = val;
		++size_;
	}
	iterator insert(const iterator& position, const T& value) {
		if (position.vec != this || buf_.get() + size_ < position.ptr)
			throw std::invalid_argument("Invalid iterator");
		
		if (position == end()) {
			push_back(value);
			return end();
		}

		int new_element_idx = (int)(position.ptr - buf_.get());
		push_back(buf_[size_ - 1]);
		T temp = buf_.get()[new_element_idx];
		buf_.get()[new_element_idx] = value;
		for(int i = new_element_idx + 1; i < size_; i++) {
			std::swap(temp, buf_.get()[i]);
		}
		
		return iterator_by_index(new_element_idx);
	}
	iterator erase(const iterator& position) {
		if (position.vec != this || buf_.get() + size_ <= position.ptr)
			throw std::invalid_argument("Invalid iterator");

		int del_element_idx = (int)(position.ptr - buf_.get());
		T temp = buf_.get()[size_ - 1];
		for (int i = size_ - 2; i >= del_element_idx; i--) {
			std::swap(temp, buf_.get()[i]);
		}

		--size_;
		return iterator_by_index(del_element_idx);
	}

private:
	void grow() {
		int new_cap = (cap_ == 0) ? 1 : cap_ * 2;
		T* new_buf = alloc_.allocate(new_cap);
		for (int i = 0; i < size_; i++) {
			new_buf[i] = buf_.get()[i];
		}
		auto new_buf_ptr = std::unique_ptr<T[], ptr_deleter>(new_buf, { alloc_, (std::size_t)new_cap });
		buf_.swap(new_buf_ptr);
		cap_ = new_cap;
	}

	struct ptr_deleter {

		ptr_deleter(allocator_type& alloc, size_t size) : alloc{&alloc}, size{size}
		{}

		void operator() (T* ptr) {
			for(std::size_t i = 0; i < size; ++i)
				std::allocator_traits<allocator_type>::destroy(*alloc, &ptr[i]);
			alloc->deallocate(ptr, size);
		}

		allocator_type* alloc;
		std::size_t size;
	};

private:
	allocator_type alloc_;
	std::unique_ptr<T[], ptr_deleter> buf_;
	int size_;
	int cap_;
};