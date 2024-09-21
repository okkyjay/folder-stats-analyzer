#include <iostream>
#include <filesystem>
#include <iomanip>

namespace fs = std::filesystem;

int main(int argc, char* argv[]) {
    // Use current directory if none is provided
    fs::path root = (argc > 1) ? fs::path(argv[1]) : fs::current_path();

    if (!fs::exists(root) || !fs::is_directory(root)) {
        std::cerr << "Invalid directory: " << root << "\n";
        return 1;
    }

    std::uintmax_t totalSize = 0;
    std::size_t fileCount = 0;
    std::size_t dirCount = 0;

    try {
        for (const auto& entry : fs::recursive_directory_iterator(root)) {
            if (entry.is_directory()) {
                ++dirCount;
            } else if (entry.is_regular_file()) {
                ++fileCount;
                totalSize += entry.file_size();
            }
        }

        std::cout << "Directory: " << root << "\n";
        std::cout << "---------------------------------\n";
        std::cout << "Total Folders: " << dirCount << "\n";
        std::cout << "Total Files:   " << fileCount << "\n";
        std::cout << "Total Size:    " << std::fixed << std::setprecision(2)
                  << (totalSize / (1024.0 * 1024.0)) << " MB\n";

    } catch (const fs::filesystem_error& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }

    return 0;
}
