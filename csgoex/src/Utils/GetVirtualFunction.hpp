#pragma once

void**& GetVirtualTable(void* sdk_class) {
	return *static_cast<void***>(sdk_class);
}

template <typename Function = void*> Function GetVirtualFunction(void* sdk_class, size_t function_index) {
	return reinterpret_cast<Function>(GetVirtualTable(sdk_class)[function_index]);
}
