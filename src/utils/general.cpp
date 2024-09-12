//
// Created by darekparodia on 9/12/24.
//

#include "general.h"

namespace utils{
    std::string cstring_arr_to_str(char** array, int size){
        std::string str = "";
        for (int i = 0; i < size; i++){
            str += array[i];
            if (i < size - 1){
                str += " ";
            }
        }
        return str;
    }
}