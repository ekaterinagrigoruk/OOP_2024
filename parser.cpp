#include <fstream>
#include "parser.h"

std::vector<Edge> Parser::parse(const std::string& filename, const std::string& delimiter) {
    std::vector<Edge> edges;
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw ParserErrors("File doesn't open");
    }
    std::string line;
    while (std::getline(file, line)) {
        std::vector<std::string> tokens = parse_line(line, delimiter);
        if (tokens.size() == 2) {
            edges.emplace_back(Vertex(tokens[0]), Vertex(tokens[1]));
        } else {
            throw ParserErrors("Invalid data format in file");
        }
    }
    file.close();
    return edges;
}

std::vector<std::string> Parser::parse_line(std::string& line, const std::string& delimiter) {
    std::vector<std::string> tokens;
    size_t pos = 0;
    std::string token;
    while ((pos = line.find(delimiter)) != std::string::npos) {
        token = line.substr(0, pos);
        tokens.push_back(token);
        line.erase(0, pos + delimiter.length());
    }
    tokens.push_back(line);
    return tokens;
}