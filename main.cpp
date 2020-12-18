#include <iostream>
#include "Test/Test.h"
#include <time.h>
#include <chrono>

void line() {
    for (int i = 0; i < 20; i++) {
        std::cout << "_";
    }
    std::cout << "\n";
}

void printIntSeq(Sequence<int> *seq) {
    for (int i = 0; i < seq->getLength(); i++) {
        std::cout << seq->get(i) << " ";
    }
    std::cout << "\n";
}

void print_graph(Graph *graph) {
    Sequence<string> *nodeNames = graph->listOfNodes();

    for (int i = 0; i < nodeNames->getLength(); i++) {
        string nodeName = nodeNames->get(i);
        Sequence<string> *currentNeighbours = graph->getNeighbours(nodeNames->get(i));

        std::cout << nodeName << " is connected with: \n";
        for (int j = 0; j < currentNeighbours->getLength(); j++) {
            string neighbourName = currentNeighbours->get(j);
            int indexInTotal = nodeNames->indexOf(neighbourName);          // индекс соседа в списке имен нодов
            unsigned int weight = graph->getEdgeWeight(i, indexInTotal);

            std::cout << "- " << neighbourName << ", weight: " << weight << "\n";
        }
        std::cout << "\n";
    }
}

bool intIsNull(int n) {
    return n == 0;
}

void println(string str) {
    std::cout << str << "\n";
}

void print_info() {
    println("test  -  launch all tests");
    println("create (option) -  create graph and work with it (option == custom or option == random)");

    println("exit  -  exit the program");
}

string firstWord(string str) {
    std::string word;
    int i = 0;
    while (str[i] != ' ' && i != str.length()) {
        word += str[i];
        i++;
    }
    return word;
}

void removeFirstWord(string *str) {
    int i = 0;
    while ((*str)[i] != ' ' && i != (*str).length()) {
        i++;
    }
    if (i == (*str).length()) {
        (*str) = "";
    } else {
        (*str).erase(0, i + 1);
    }
}

void print_colors(ColorizedGraph *colorizedGraph) {
    Sequence<Sequence<string> *> *coloredNodes = colorizedGraph->getColoredNodes();

    for (int i = 0; i < coloredNodes->getLength(); i++) {
        std::cout << (i + 1) << " color: \n";
        for (int j = 0; j < coloredNodes->get(i)->getLength(); j++) {
            std::cout << "- " << coloredNodes->get(i)->get(j) << "\n";
        }
        std::cout << "\n";
    }
}

void print_greetings() {
    std::cout << R"(
  _           _         _  _  ____     _____                 _
 | |         | |      _| || ||___ \   / ____|               | |
 | |     __ _| |__   |_  __  _|__) | | |  __ _ __ __ _ _ __ | |__  ___
 | |    / _` | '_ \   _| || |_|__ <  | | |_ | '__/ _` | '_ \| '_ \/ __|
 | |___| (_| | |_) | |_  __  _|__) | | |__| | | | (_| | |_) | | | \__ \
 |______\__,_|_.__/    |_||_||____/   \_____|_|  \__,_| .__/|_| |_|___/
                                                      | |
                                                      |_|              )" << "\n";
}

void print_operations_with_custom() {
    println("add-node (name)  -  add to graph node <name>");
    println("add-edge (name1) (name2) (weight)  -  add edge between <name1> and <name2> with weight <weight>");
    println("remove-node (name)  -  remove node <name> from the graph");
    println("remove-edge (name1) (name2)  -  remove edge between <name1> and <name2>");
    println("help  -  show commands");
    println("colorize  -  colorize current graph and go out");
}

int main() {
    print_greetings();
    srand(time(NULL));

    string request;

    while (firstWord(request) != "exit") {
        println("");
        print_info();
        std::cout << "> ";
        getline(cin, request);
        string command;
        try {
            command = firstWord(request);
        } catch (...) {
            std::cout << "Something went wrong...\n";
            continue;
        }

        if (command == "test") {
            Test::launchAllTests();
        } else if (command == "create") {
            UndirGraph *graph = new UndirGraph();
            removeFirstWord(&request);
            string option = firstWord(request);

            if (option == "custom") {
                string custom_request;
                string custom_command;

                println("* BUILDING GRAPH *");
                print_operations_with_custom();
                std::cout << "\n";

                do {
                    getline(cin, custom_request);
                    custom_command = firstWord(custom_request);
                    removeFirstWord(&custom_request);

                    if (custom_command == "add-node") {
                        string node_name = firstWord(custom_request);

                        if (graph->hasNode(node_name)) {
                            println("Sorry, such node already exist in graph\n");
                            continue;
                        } else {
                            graph->addNode(node_name);
                            std::cout << "node \"" << node_name << "\" was added successfully\n";
                        }
                    } else if (custom_command == "add-edge") {
                        int weight;
                        string node1, node2;
                        try {
                            node1 = firstWord(custom_request);
                            removeFirstWord(&custom_request);
                            node2 = firstWord(custom_request);
                            removeFirstWord(&custom_request);
                            weight = std::stoi(firstWord(custom_request));
                        } catch (...) {
                            std::cout << "Sorry, something wrong with input, try again\n\n";
                            continue;
                        }

                        if (graph->hasEdge(node1, node2)) {
                            std::cout << "Sorry, such edge already exists in graph\n\n";
                            continue;
                        }

                        if (!graph->hasNode(node1) || !graph->hasNode(node2)) {
                            std::cout << "Sorry, there's no such nodes in graph\n\n";
                            continue;
                        }

                        graph->addEdge(node1, node2, weight);
                        std::cout << "edge between \"" << node1 << "\" and \"" << node2
                                  << "\" was added successfully\n";
                    } else if (custom_command == "remove-node") {
                        string nodeName = firstWord(custom_request);

                        if (graph->hasNode(nodeName)) {
                            graph->removeNode(nodeName);
                            std::cout << "node \"" << nodeName << "\" was removed successfully\n";
                        } else {
                            std::cout << "Sorry, there's no such node in graph\n\n";
                            continue;
                        }
                    } else if (custom_command == "remove-edge") {
                        string node1, node2;
                        try {
                            node1 = firstWord(custom_request);
                            removeFirstWord(&custom_request);
                            node2 = firstWord(custom_request);
                        } catch (...) {
                            std::cout << "Sorry, something wrong with input, try again\n\n";
                            continue;
                        }

                        if (graph->hasNode(node1) && graph->hasNode(node2) && graph->hasEdge(node1, node2)) {
                            graph->removeEdge(node1, node2);
                            std::cout << "edge between \"" << node1 << "\" and \"" << node2
                                      << "\" was removed successfully\n";
                        } else {
                            std::cout << "There're not such edge or/and nodes, try again\n\n";
                            continue;
                        }
                    } else if (custom_command == "help") {
                        print_operations_with_custom();
                        std::cout << "\n";
                    }
                } while (custom_command != "colorize");

                std::cout << "** CUSTOM GRAPH **\n";
                print_graph(graph);
                std::cout << "\n";
                std::cout << "** COLORED GRAPH **\n";

                auto start = std::chrono::steady_clock::now();
                ColorizedGraph *coloredGraph = new ColorizedGraph(graph);
                auto end = std::chrono::steady_clock::now();
                std::chrono::duration<double> elapsed_seconds = end - start;

                print_colors(coloredGraph);

                std::cout << "Algorithm duration: " << elapsed_seconds.count() << "s\n";

            } else if (option == "random") {
                int nodeCount;
                string countNodeString;

                println("Enter count of nodes:");
                getline(cin, countNodeString);
                try {
                    nodeCount = std::stoi(countNodeString);
                } catch (...) {
                    println("Something went wrong...\n");
                    continue;
                }

                int maxEdgeCount = (nodeCount * (nodeCount - 1)) / 2;         // добавляем все ноды
                for (int i = 0; i < nodeCount; i++) {
                    graph->addNode(to_string(i));
                }

                int edgeCount;
                if (maxEdgeCount == 0) {
                    edgeCount = 0;
                } else {
                    edgeCount = rand() % maxEdgeCount + 1;                  // добавляем все ребра
                }
                for (int i = 0; i < edgeCount; i++) {
                    string first_node, second_node;
                    do {
                        first_node = to_string(rand() % nodeCount);
                        second_node = to_string(rand() % nodeCount);
                    } while (graph->hasEdge(first_node, second_node) || first_node == second_node);

                    graph->addEdge(first_node, second_node, rand() % 1000 + 1);
                }

                println("** GENERATED GRAPH **");
                print_graph(graph);
                std::cout << "\n";
                println("** COLORIZED GRAPH **");

                auto start = std::chrono::steady_clock::now();
                ColorizedGraph *coloredGraph = new ColorizedGraph(graph);
                auto end = std::chrono::steady_clock::now();

                std::chrono::duration<double> elapsed_seconds = end - start;
                print_colors(coloredGraph);

                std::cout << "Algorithm duration: " << elapsed_seconds.count() << "s\n";
            } else {
                println("Sorry, check your writing");
                continue;
            }
        }
    }
}
