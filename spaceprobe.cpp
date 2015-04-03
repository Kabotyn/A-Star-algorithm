#include "spaceprobe.h"
#include <math.h>
#include <QDebug>
#include <ctime>
#include <iostream>

SpaceProbe::SpaceProbe(int p_N, int p_startR, int p_startC, int p_endR, int p_endC) {
    setSpaceSize(p_N);
    start.row = p_startR;
    start.col = p_startC;
    end.row = p_endR;
    end.col = p_endC;

    /* start and end node as obstacle (no asteroids and gravty wells in this point) */
    allObstacles.push_back(start);
    allObstacles.push_back(end);

    randomAsteroids();
    randomGravityWells();

    prepareVis();

}

SpaceProbe::~SpaceProbe() {

}

bool SpaceProbe::run() {
    AStar as(N, N, start.row, start.col, end.row, end.col);
    for(int i = 2; i < (int)allObstacles.size(); i++) {
        as.setObstacle(allObstacles.at(i).row, allObstacles.at(i).col);
    }

    result = as.find();
    if(result.empty()) {
        qDebug() << "No Complete Path";
        return false;
    } else {
        prepareResult();
        return true;
    }
}

void SpaceProbe::setSpaceSize(int p_N) {
    N = p_N;
    vis = new std::string[p_N];
    // fill vis with dots (sign of empty space)
    for(int r = 0; r < p_N; r++)
        for(int c = 0; c < p_N; c++)
            vis[r].push_back('.');

    countA();
    countG();
    countF();
}

void SpaceProbe::countA() {
    A = ceil(N * N * 0.1); // 30% of all fields will be asteroids
}

void SpaceProbe::countG() {
    G = round(N * N * 0.05);
}

void SpaceProbe::countF() {
    F = N * N - A - G;
}

void SpaceProbe::randomAsteroids() {

    nodePosition random;
    bool found;

    srand (time(NULL));
    while((int)asteroids.size() != A) {
        found = false;
        random.row = rand() % N;
        random.col = rand() % N;
        for(nodePosition x : allObstacles) {
            if(random.row == x.row && random.col == x.col) {
                // this point exists in obstacle
                found = true;
            }
        }

        if(found == true)
            continue;


        asteroids.push_back(random);
        allObstacles.push_back(random);
    }


}

void SpaceProbe::randomGravityWells() {

    nodePosition random;
    bool found;


    srand (time(NULL)); // initialize random seed

    while((int)gravityWells.size() != G) {
        found = false;
        random.row = rand() % N;
        random.col = rand() % N;
        for(nodePosition x : allObstacles) {//int i = 0; i < allObstacles.size(); i++) {
            if(random.row == x.row && random.col == x.col) {
                // this point exists in obstacle
                found = true;
            }
        }

        if(found == true)
            continue;

        gravityWells.push_back(random);


    }

    // count and add filds around gravity well to obstacles
    // prevent out of bounds
    for(int g = 0; g < (int)gravityWells.size(); g++) {
        int minR = gravityWells[g].row == 0 ? 0 : (gravityWells[g].row - 1),
            maxR = gravityWells[g].row == (N-1) ? gravityWells[g].row : (gravityWells[g].row + 1),
            minC = gravityWells[g].col == 0 ? 0 : (gravityWells[g].col - 1),
            maxC = gravityWells[g].col == (N-1) ? gravityWells[g].col : (gravityWells[g].col + 1);

        nodePosition temp;
        for(int r = minR; r <= maxR; r++) {
            for(int c = minC; c <= maxC; c++) {
                temp.row = r; temp.col = c;
                allObstacles.push_back(temp);
            }
        }
    }


}

void SpaceProbe::showSpace() {

    for(int i = 0; i < N; i++) {
        std::cerr << vis[i] << std::endl;
    }

}

void SpaceProbe::prepareVis() {
    vis[start.row][start.col] = 'S';
    vis[end.row][end.col] = 'E';

//    for(auto x : allObstacles) {
//        vis[x.row][x.col] = 'X';
//    }

    for(int i = 0; i < G; i++) {
        vis[gravityWells[i].row][gravityWells[i].col] = 'G';
    }
    for(int i = 0; i < A; i++) {
        vis[asteroids[i].row][asteroids[i].col] = 'A';
    }
}

void SpaceProbe::prepareResult() {

    nodePosition current;
    while(result.empty() == false) {
        current = result.front();
        vis[current.row][current.col] = 'O';
        result.pop_front();
    }

}













