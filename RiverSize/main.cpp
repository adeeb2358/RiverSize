//
//  main.cpp
//  RiverSize
//
//  Created by adeeb mohammed on 01/05/20.
//  Copyright © 2020 adeeb mohammed. All rights reserved.
//

#include <iostream>
#include <vector>

// river size find the groups of one,s either horizontally or vertically
// not diagonally
// space complexity is o(m*n) , space complexity is o(m*n)

std::vector<std::vector<int>> getUnVisitedNodes(int i,
                                                int j,
                                                std::vector<std::vector<int>> &matrix,
                                                std::vector<std::vector<int>> &visitedMatrix){
    std::vector<std::vector<int>> unvisitedNodes = {};
    // get top node
    if(i > 0 && !visitedMatrix.at(i-1).at(j)){
        unvisitedNodes.push_back({i-1,j});
    }
    // get bottom node
    if(i < (int)matrix.size()-1 && !visitedMatrix.at(i+1).at(j)){
        unvisitedNodes.push_back({i+1,j});
    }
    // get left node
    if (j > 0 && !visitedMatrix.at(i).at(j-1)) {
        unvisitedNodes.push_back({i,j-1});
    }
    //get right node
    if (j < (int)matrix.at(0).size() - 1 && !visitedMatrix.at(i).at(j+1)) {
        unvisitedNodes.push_back({i,j+1});
    }
    return unvisitedNodes;
}

// function for traversing the adjascent nodes
void traverseNodes(int i ,
                   int j,
                   std::vector<std::vector<int>> &matrix,
                   std::vector<std::vector<int>> &visitedMatrix,
                   std::vector<int> &sizes){
    int currentRiverSize = 0;
    std::vector<std::vector<int>> nodesToCheck = {{i,j}};
    while (!nodesToCheck.empty()) {
        auto currentNode = nodesToCheck.back();
        nodesToCheck.pop_back();
        i = currentNode.at(0);
        j = currentNode.at(1);
        if (visitedMatrix.at(i).at(j)) {
            continue;
        }
        visitedMatrix.at(i).at(j) = true;
        if (matrix.at(i).at(j) == 0) {
            continue;
        }
                currentRiverSize++;
        auto unVisitedNodes = getUnVisitedNodes(i, j, matrix, visitedMatrix);
        for (auto node: unVisitedNodes) {
            nodesToCheck.push_back(node);
        }
    }
    if (currentRiverSize > 0) {
        sizes.push_back(currentRiverSize);
    }
}

std::vector<int>riverSizes(std::vector<std::vector<int>> matrix){
    // result vector which gives the size of the rivers the vector gives the total number of rivers
    std::vector<int> sizes = {};
    // the matrix for marking the visited nodes.
    std::vector<std::vector<int>> visitedMatrix(matrix.size(),std::vector<int>(matrix.at(0).size(),0));
    for (int i = 0;  i < matrix.size(); ++i ) {
        for (int j = 0; j < matrix.at(i).size(); ++j) {
            if (visitedMatrix.at(i).at(j)) {
                continue;
            }
            traverseNodes(i, j, matrix, visitedMatrix,sizes);
        }
    }
    return sizes;
}

int main(int argc, const char * argv[]) {
    std::cout << "River sizes problem" << std::endl;
    auto result = riverSizes({{0,1},{1,0},{0,0},{1,1},{0,0},{1,1}});
    for (auto num: result) {
        std::cout << num << std::endl;
    }
    return 0;
}
