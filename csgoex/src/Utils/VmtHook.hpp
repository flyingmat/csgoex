#pragma once

class VmtHook {
private:
	uintptr_t** class_ptr = nullptr;
	size_t function_amt = 0;
	uintptr_t* current_vmt = nullptr;
	uintptr_t* original_vmt = nullptr;
public:
	VmtHook(void) = default;

	VmtHook(void* class_ptr) {
		this->class_ptr = static_cast<uintptr_t**>(class_ptr);

		while (static_cast<std::uintptr_t*>(*this->class_ptr)[this->function_amt])
			++this->function_amt;

		this->original_vmt = *this->class_ptr;
		this->current_vmt = new uintptr_t [this->function_amt + 1];

		std::memcpy(this->current_vmt, &this->original_vmt[-1], (this->function_amt + 1) * sizeof(std::uintptr_t));

		*this->class_ptr = &this->current_vmt[1];
	};

	~VmtHook() {
		*this->class_ptr = this->original_vmt;
	};

	template <typename Function> inline const Function GetOriginalFunction(size_t i) {
		return reinterpret_cast<Function>(this->original_vmt[i]);
	}

	inline bool Hook(void* fn, const size_t i) {
		if (i > this->function_amt)
			return false;

		this->current_vmt[i + 1] = reinterpret_cast<uintptr_t>(fn);

		return true;
	}
};
