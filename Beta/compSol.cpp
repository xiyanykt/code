#include <bits/stdc++.h>

auto main() ->int {
    std::ofstream compileFile("compileSol.bat");

    if (!compileFile) {
        std::cerr << "build sol fail" << std::endl;
        return 1;
    }

    compileFile << "@echo off\n";
    compileFile << "g++ -O2 -std=c++23 ";

    std::vector<std::string> cppFiles = {
        "sol.cpp",
        
    };

    for (const auto& file : cppFiles) {
        compileFile << file << " ";
    }

    compileFile << "-o sol.exe\n";
    compileFile.close();
    std::cerr << "build sol succ" << std::endl;
    return 0;
}
