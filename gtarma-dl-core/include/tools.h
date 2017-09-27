#include <vector>

#include "models.h"


namespace gtarma {
	__declspec(dllexport) std::vector<model::Item> GetFiles();

	__declspec(dllexport) size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream);

	__declspec(dllexport) void DownloadFile(model::Item item, std::string path);
}