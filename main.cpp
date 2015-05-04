/*! 
 *  \mainpage Prima Algorithm
 *  \section intro_sec Description
 *  There is example of using Prima Algorithm.
 */

/*!
 *  \file main.cpp 
 */
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

/* IMPORTANT NOTE:
   Using atoi() instead of stoi()
   atoi() can convert words to 0 value unlike stoi()
   Simple protection from fools */

/*! 
 *  \brief String-splitting algorithm.
 *  \param string Splitted string.
 *  \param delim Delimiter for splitting.
 *  \return items Vector of source string parts.
 */
std::vector <std::string> split(std::string &string, char delim) 
{
    std::vector <std::string> items;
    std::stringstream stringStream (string);
    std::string item;

    while (std::getline(stringStream, item, delim))
        if (item.size())
            items.push_back(item);

    return items;
}

/*! 
 *  \brief Prima algorithm function.
 *  \details The algorithm result will be shown in console.
 *  \param matrix Reference to matrix of weights of routes between vertexes.
 *  \param amount Amount of vertexes.
 *  \param vertex Vertex to start the algorithm.
 *  \return Function returns nothing.
 */
void PrimaAlgorithm (int**& matrix, int amount, int vertex)
{
    int infinity = std::numeric_limits<int>::max(),
        count = 0, minCost = 0,
        minimal, a, b;

    std::vector<int> nextVertex,
                     prevVertex;

    bool* visited = new bool [amount];
    for (int i = 0; i < amount; i ++)
        visited [i] = i == vertex - 1 ? true : false;

    while (count < amount - 1)
    {
        minimal = infinity;
        for (int i = 0; i < amount; i ++)
        {
            for (int j = 0; j < amount; j ++)
            {
                if (matrix[i][j] < minimal)
                {
                    if (visited[i])
                    {
                        minimal = matrix[i][j];
                        a = i;
                        b = j;
                    }
                }
            }
        }

        if (!(visited[a] && visited[b]))
        {
            nextVertex.push_back (b + 1);
            prevVertex.push_back (a + 1);

            visited[b] = true;
            minCost += minimal;
            count ++ ;
        }

        matrix[a][b] = infinity;
        matrix[b][a] = infinity;
    }
 
    std::cout << std::endl << vertex << "(start) --> ";
    for (size_t i = 0; nextVertex.size() && i < nextVertex.size(); i ++)
        std::cout << nextVertex.at(i) << "(" << nextVertex.at(i) << ")" << (i != nextVertex.size() - 1 ? " --> " : "");
 
    std::cout << std::endl << "Minimal tree skeleton cost : " << minCost << std::endl;

    delete [] visited;
}

/*! 
 *  \brief Program entry point.
 *  \details User initializes a graph: he sets amount of vertexes, the vertex for start and the matrix itself. Then, user launches Prima algorithm.
 */
void main()
{
    int amount, number, vertex, **matrix;
    bool successCode;
    
    std::vector <std::string> matrixRow;
    std::string string;
    
    do
    {
        std::cout << "Vertex amount (2 or more) : "; 
        std::cin >> string;

        amount = stoi(string); 

        if (amount < 2)
            std::cout << "Bad vertex amount." << std::endl; 
    }
    while (amount < 2);
    
    matrix = new int* [amount];
    for (int i = 0; i < amount; i ++)
        matrix[i] = new int [amount];

    std::cout << std::endl;
    
    do
    {
        successCode = true;

        for (int i = 0; i < amount; i ++)
        {
            std::cout << "Matrix row #" << i + 1 << " : ";

            fflush (stdin);
            getline (std::cin, string);
            matrixRow = split(string, ' ');

            if (matrixRow.size() != amount)
            {
                std::cout << "Bad matrix row." << std::endl;
                i --;
                continue;
            }

            if (stoi(matrixRow.at(i)) != 0)
            {
                std::cout << "No loops in Prima Algorithm. (self-route should be equal zero)" << std::endl;
                i --;
                continue;
            }

            for (int j = 0; j < amount; j ++)
            {
                number = stoi(matrixRow[j]);
                matrix [i][j] = number <= 0 ? std::numeric_limits<int>::max() : number;
            }
        }

        for (int i = 0; i < amount; i ++)
        {
            for (int j = 0; j < amount; j ++)
            {
                if (i != j && matrix[i][j] != matrix[j][i])
                {
                    std::cout << "Matrix should be symmetric in Prima Algorithm." << std::endl;
                    successCode = false;
                    break;
                }
            }

            if (!successCode)
                break;
        }
    }
    while (!successCode);

    std::cout << std::endl;
    
    do
    {
        std::cout << "Start with vertex : "; 
        std::cin >> string;

        vertex = stoi(string); 
        if (vertex < 1 || vertex > amount)
            std::cout << "Bad vertex chosen." << std::endl;
    
    }
    while (vertex < 1 || vertex > amount);

    PrimaAlgorithm(matrix, amount, vertex);

    for (int i = 0; i < amount; i ++)
        delete [] matrix [i];
    delete [] matrix;
}
