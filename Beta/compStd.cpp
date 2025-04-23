#include <bits/stdc++.h>

auto main() ->int {
    std::ofstream compileFile("compileStd.bat");

    if (!compileFile) {
        std::cerr << "build std fail" << std::endl;
        return 1;
    }

    compileFile << "@echo off\n";
    compileFile << "g++ -O2 -std=c++23 ";

    std::vector<std::string> cppFiles = {
        "std.cpp",
    };

    for (const auto& file : cppFiles) {
        compileFile << file << " ";
    }

    compileFile << "-o std.exe\n";
    compileFile.close();
    std::cerr << "build std succ" << std::endl;
    return 0;
}
