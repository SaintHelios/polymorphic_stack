#pragma once
template <typename T>
class poly_stack
{
private:
	T** pointers_array;
	size_t size;
	int top;
	int highest_top;
	void change_ht() { if (top > highest_top) ++highest_top; }
	void clear();
public:
	poly_stack();
	poly_stack(size_t size);
	bool is_empty() { return top == -1; }
	void push(T& obj);
	void push(T* obj);
	T& pop();
	~poly_stack();
};

template <typename T> void poly_stack<T>::push(T& obj) {
	if (top == size - 1) {
		size += 10;
		T** copy_to = new T*[size];
		for (size_t i = 0; i < size - 10; ++i) {
			copy_to[i] = pointers_array[i]->clone();
		}
		clear();
		pointers_array = copy_to;
	}

	if (top + 1 <= highest_top) {
		delete pointers_array[top + 1];
		pointers_array[top + 1] = obj.clone();
		++top;
	}
	else {
		pointers_array[top + 1] = obj.clone();
		++top;
	}
	change_ht();
}


template <typename T> poly_stack<T>::poly_stack() {
	this->top = -1;
	this->highest_top = -1;
	this->size = 5;
	pointers_array = new T * [this->size];
}

template <typename T> poly_stack<T>::poly_stack(size_t size) {
	this->top = -1;
	this->highest_top = -1;
	this->size = size;
	pointers_array = new T*[this->size];
}

template <typename T> void poly_stack<T>::push(T* obj) {
	if (top == size - 1) { 
		size += 10;
		T** copy_to = new T * [size];
		for (size_t i = 0; i < size - 10; ++i) {
			copy_to[i] = pointers_array[i]->clone();
		}
		clear();                       
		pointers_array = copy_to;
	}
	if (top + 1 <= highest_top) {
		delete pointers_array[top + 1];
		pointers_array[top + 1] = obj->clone();
		++top;
	}
	else {
		pointers_array[top + 1] = obj->clone();
		++top;
	}
	change_ht();
}

template <typename T> T& poly_stack<T>::pop() {
	T& to_return = *pointers_array[top];
	--top;
	return to_return;
}



template <typename T> void poly_stack<T>::clear() {
	if (!is_empty()) {
		for (size_t i = 0; i < highest_top; ++i) {
			delete[] pointers_array[i];
		}
		delete[] pointers_array;
	}
}

template <typename T> poly_stack<T>::~poly_stack() {
	if (!is_empty()) {
		for (size_t i = 0; i < highest_top; ++i) {
			delete[] pointers_array[i];
		}
		delete[] pointers_array;
	}
}
