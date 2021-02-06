#pragma once
#include <vector>

template <typename T, std::size_t BLOCK_SIZE>
class Allocator {
public:
	using value_type = T;
	using pointer = T*;
	using const_pointer = const T*;
	using size_type = std::size_t;

	Allocator() noexcept : freeChunks(0), buffer{ nullptr } {
		static_assert(BLOCK_SIZE > 0, "Размер блока должен быть больше нуля");
		static_assert(sizeof(T) >= sizeof(Header), "Размер типа должен быть не меньше размера заголовка");
	}

	~Allocator() noexcept {
		free(buffer);
	}

	template <typename U>
	Allocator(const Allocator<U, BLOCK_SIZE>& Alloc) noexcept : Allocator() {}

	template <typename U>
	struct rebind
	{
		using other = Allocator<U, BLOCK_SIZE>;
	};

	T* allocate(std::size_t n) {
		if (n == 0)
			return nullptr;

		// Если память для аллокатора не выделена
		if (!buffer) {
			buffer = static_cast<T*>(malloc(sizeof(T) * (BLOCK_SIZE + 1)));

			freeChunks.resize(1);
			reinterpret_cast<Header*>(&buffer[0])->size = BLOCK_SIZE;
			freeChunks[0] = &buffer[0];
		}

		if (freeChunks.empty())
			throw std::bad_alloc();

		// Находим кадр достаточого размера
		Header* ptr = nullptr;
		for (int i = 0; i < freeChunks.size(); ++i) {
			if (reinterpret_cast<Header*>(freeChunks[i])->size >= n) {
				ptr = reinterpret_cast<Header*>(freeChunks[i]);
				freeChunks.erase(freeChunks.begin() + i);
				break;
			}
		}
		// Если не нашли, то кидаем ошибку
		if (!ptr) 
			throw std::bad_alloc();
		// Если кадр больше чем нужно, то делим его 
		if (ptr->size > n) {
			if (ptr->size > n + 1) {
				size_t size = ptr->size;
				ptr->size = n;
				// Создаем новый кадр
				Header* next = reinterpret_cast<Header*>(reinterpret_cast<T*>(ptr) + n + 1);
				next->size = size - n - 1;
				freeChunks.push_back(reinterpret_cast<T*>(next));
			}
		}
		
		return reinterpret_cast<T*>(ptr)+1;
	}

	void deallocate(T* p, std::size_t n) {
		if (!p || n == 0)
			return;

		// Получаем хедр кадра
		Header* head = reinterpret_cast<Header*>(p - 1);
		// Нужно проверить, являются ли соседние кадры свободными
		auto it = freeChunks.begin();
		while (it != freeChunks.end()) {
			Header* neighbour = reinterpret_cast<Header*>(*it);
			// Если сосед слева
			if (neighbour + neighbour->size + 1 == head) {
				neighbour->size += head->size + 1;
				head = neighbour;
				it = freeChunks.erase(it);
			}
			// Сосед справа
			else if (head + head->size + 1 == neighbour) {
				head->size += neighbour->size + 1;
				it = freeChunks.erase(it);
			}
			else
				++it;
		}

		// Нужно пометить кадр как свободный
		freeChunks.push_back(reinterpret_cast<T*>(head));
	}


private:
	struct Header {
		size_t size;
	};

	pointer buffer;
	std::vector<pointer> freeChunks;
};