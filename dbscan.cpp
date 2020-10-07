

#include "cairo_picker/src/cairo_picker.hpp"
#include <vector>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include "RTree/RTree.h"

struct point { double x, y; int class_num; };

std::vector<point> data;
RTree<int, double, 2, double> rdata;

const int rect_w = 20;
const int rect_h = 20;
const int range_w = 800;
const int range_h = 800;

const char * file = "./datas/data__Wed_Oct__7_20:17:00_2020.txt";
const double distance = 90;
const int minsize = 3;
int latest_class_num = 0;

// ======================--

Capr::C_picker picker;

void draw(Capr::Cairo_cont cr);

void cluster(int core, int core_class_num){

    if(data[core].class_num != -1) return;

    const double
        rmin[2]= {data[core].x-distance/2.0, data[core].y-distance/2.0},
        rmax[2]= {data[core].x+distance/2.0, data[core].y+distance/2.0};

    std::vector<int> list = {};

    std::function<bool(const int&)> func = 
        [&](const int num){
            if(std::sqrt((data[num].x-data[core].x)*(data[num].x-data[core].x)+(data[num].y-data[core].y)*(data[num].y-data[core].y)) < distance)
                list.push_back(num);
            return true;
        };

    rdata.Search(rmin, rmax, func);

    if(list.size() < minsize){
        data[core].class_num = -1;
        return;
    }
    
    if(core_class_num == -1){
        data[core].class_num = latest_class_num;
        latest_class_num++;
    }
    else{
        data[core].class_num = core_class_num;
    }

    for(int it:list){
        cluster(it, data[core].class_num);
    }
    
    
}


int main(){

    std::ifstream input(file);


    // データを読み出す。
    for(std::string line;getline(input,line);){
        //std::cout<<line<<std::endl;
        size_t colon = line.find(":");
        std::string sx(""), sy("");

        for(int i=0; i<colon; i++){
            sx.push_back(line[i]);
        }

        for(int i=0; i<line.length()-colon; i++){
            sy.push_back(line[colon+1+i]);
        }

        const int ix = std::atoi(sx.c_str()), iy = std::atoi(sy.c_str());

        data.push_back(point{double(ix), double(iy), -1});
    }

    // 読み出したデータをRTreeで保管
    for(int i=0; i<data.size(); i++){
        const double pa[2]={data[i].x, data[i].y};
        rdata.Insert(pa, pa, i);
    }


    // DBSCAN メイン処理
    for(int i=0; i<data.size(); i++){
        cluster(i, -1);
    }

    picker.set_default_size(range_w, range_h);
    picker.set_loop(0);
    
    picker.run(draw);
}

void draw(Capr::Cairo_cont cr){
    /*
    for(int i=0;i<2;i++){
        for(point it:data){
            if(it.class_num == -1) continue;
            cr->set_source_rgba(0.95-i*0.05, 0.95-i*0.05, 0.95-i*0.05, 1.0);
            cr->arc(it.x, it.y, distance/(2+i*2), 0, 2*M_PI);
            cr->fill();
        }
    }
    */

    for(point it:data){

        if(it.class_num == -1){
            cr->set_source_rgba(0.0, 0.0, 0.0, 0.5);
        }
        else{

            switch(it.class_num%6){
            case 0:
                cr->set_source_rgba(1.0, 0.0, 0.0, 0.5);
                break;
            case 1:
                cr->set_source_rgba(0.0, 0.8, 0.0, 0.5);
                break;
            case 2:
                cr->set_source_rgba(0.0, 0.0, 0.8, 0.5);
                break;
            case 3:
                cr->set_source_rgba(0.0, 0.5, 0.5, 0.5);
                break;
            case 4:
                cr->set_source_rgba(0.5, 0.0, 0.5, 0.5);
                break;
            case 5:
                cr->set_source_rgba(0.5, 0.5, 0.0, 0.5);
                break;
            }
        }
        cr->rectangle(it.x-rect_w/2, it.y-rect_h/2, rect_w/2, rect_h/2);
        cr->fill();
    }
}