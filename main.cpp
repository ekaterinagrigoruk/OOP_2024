#include <fstream>
#include <iostream>
#include "Traversal.h"

/*
int main() {
    std::string name_file = "graph.txt";
    */
/*std::cout << "Input the file name: \n";
    std::cin >> name_file;*//*


    std::string start;
    std::cout << "Input the start vertex: \n";
    std::cin >> start;
    Vertex start_vertex{ start };
    std::string end;
    std::cout << "Input the end vertex: \n";
    std::cin >> end;
    Vertex end_vertex{ end };

    Traversal obj;
    try{
        obj.fill_graph(name_file);
        std::vector<Vertex> path = obj.find_way(start_vertex, end_vertex);
        for (size_t i = 0; i < path.size(); ++i) {
            std::cout << path[i].get_name();
            if (i < path.size() - 1) {
                std::cout << " -> ";
            }
        }
        std::cout << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}
*/
