#include <fstream>
#include <string>
#include <random>
#include <iostream>

#include <stdlib.h>
#include <time.h>
#include <stdio.h>


std::string get_line_by_pos(std::string file_name, int pos) {
    std::string current_line = "";

    std::ifstream input_name;
    input_name.open(file_name);

    if (input_name.is_open()) {
        for (int i = 0; i < pos; i++) {
            std::getline(input_name, current_line);
        }
    }
    input_name.close();

    return current_line;
}

int main() {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist_series(1,9); 
    std::uniform_int_distribution<std::mt19937::result_type> dist_number(1,9);

    std::uniform_int_distribution<std::mt19937::result_type> male_name_distribution(1, 205 - 200); 
    std::uniform_int_distribution<std::mt19937::result_type> male_surname_distribution(323, 522 - 150); 
    std::uniform_int_distribution<std::mt19937::result_type> male_patronymic_distribution(724, 923 - 150);

    std::uniform_int_distribution<std::mt19937::result_type> female_name_distribution(207, 321 - 100); 
    std::uniform_int_distribution<std::mt19937::result_type> female_surname_distribution(524, 722 - 150); 
    std::uniform_int_distribution<std::mt19937::result_type> female_patronymic_distribution(925, 1021 - 50);

    std::uniform_int_distribution<std::mt19937::result_type> gender_random(0, 1);

    std::string name;
    std::string surname;
    std::string patronymic;

    std::ofstream sample;
    sample.open("input_random.txt");
    std::int64_t n = 1000000; 

    for (int i = 0; i < n; i++) {

        if (gender_random(rng) == 0) {
            name = get_line_by_pos("fio_sets.txt", male_name_distribution(rng));
            surname = get_line_by_pos("fio_sets.txt", male_surname_distribution(rng));
            patronymic = get_line_by_pos("fio_sets.txt", male_patronymic_distribution(rng));
        } else {
            name = get_line_by_pos("fio_sets.txt", female_name_distribution(rng));
            surname = get_line_by_pos("fio_sets.txt", female_surname_distribution(rng));
            patronymic = get_line_by_pos("fio_sets.txt", female_patronymic_distribution(rng));
        }

        sample << dist_series(rng) * 1000 << ' ' << dist_number(rng) * 100000 << ' ' << name << ' ' << surname << ' ' << patronymic << std::endl;
    }

    sample.close();
    return 0;
}
