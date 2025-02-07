#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

struct Passport {
    private:
        char abc[26] {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
        int get_letter_pos(char letter) const {
            for (int i = 0; i < 26; i++) {
                if (letter == abc[i]) {
                    return i;
                }
            }
            return -1;
        }
        
    public:
        int series;
        int number;

        string name;
        string surname;
        string patronymic;

        int line_number;

        Passport(int series, int number, string name, string surname, string patronymic, int line_number) : series{series}, number{number}, name{name}, surname{surname}, patronymic{patronymic}, line_number{line_number} {};

        bool operator>(const Passport& other) const {
            return (series > other.series) || (series == other.series && number > other.number);
        }
        bool operator<(const Passport& other) const {
            return (series < other.series) || (series == other.series && number < other.number);
        }
        bool operator==(const Passport& other) const {
            return (series == other.series) && (number == other.number);
        }
        bool operator<=(const Passport& other) {
            int name_1_pos = get_letter_pos((char)tolower(name[0]));
            int surname_1_pos = get_letter_pos((char)tolower(surname[0]));
            int patronymic_1_pos = get_letter_pos((char)tolower(patronymic[0]));

            int name_2_pos = get_letter_pos((char)tolower(other.name[0]));
            int surname_2_pos = get_letter_pos((char)tolower(other.surname[0]));
            int patronymic_2_pos = get_letter_pos((char)tolower(other.patronymic[0]));

            if (name_1_pos < name_2_pos) return true;
            if (name_1_pos > name_2_pos) return false;

            if (surname_1_pos < surname_2_pos) return true;
            if (surname_1_pos > surname_2_pos) return false;

            return patronymic_1_pos <= patronymic_2_pos;
        }
        bool operator>=(const Passport& other) {
            int name_1_pos = get_letter_pos((char)tolower(name[0]));
            int surname_1_pos = get_letter_pos((char)tolower(surname[0]));
            int patronymic_1_pos = get_letter_pos((char)tolower(patronymic[0]));

            int name_2_pos = get_letter_pos((char)tolower(other.name[0]));
            int surname_2_pos = get_letter_pos((char)tolower(other.surname[0]));
            int patronymic_2_pos = get_letter_pos((char)tolower(other.patronymic[0]));

            if (name_1_pos > name_2_pos) return true;
            if (name_1_pos < name_2_pos) return false;

            if (surname_1_pos > surname_2_pos) return true;
            if (surname_1_pos < surname_2_pos) return false;

            return patronymic_1_pos >= patronymic_2_pos;
        }

};

const int N = 1000000;

void selection_sort(Passport** elements, int m) {
    if (m >= 10) {
        for (int i = 0; i < m; i++) {

            int maxmin_passport_index = i;

            for (int j = i + 1; j < m; j++) {
                if ( (*elements[j] < *elements[maxmin_passport_index]) || 
                (*elements[j] == *elements[maxmin_passport_index] && *elements[j] >= *elements[maxmin_passport_index]))
                    {

                    maxmin_passport_index = j;

                }
            }
            
            Passport* first_elem = elements[i];
            elements[i] = elements[maxmin_passport_index];
            elements[maxmin_passport_index] = first_elem;

        }
    } else {
        cout << "Размерность массива меньше 10-ти" << endl;
    }

};

void shell_sort(Passport** elements, int m) {
    if (m >= 10) {
        for (int step = m/2; step > 0; step /= 2) {

            for (int i = step; i < m; i++) {

                Passport* tmp = elements[i];
                int j;
                for (j = i; j >= step && ( (*elements[j - step] > *tmp) || 
                                            (*elements[j - step] == *tmp && *elements[j - step] <= *tmp) ); j -= step) {
                    elements[j] = elements[j - step];
                }
                elements[j] = tmp;
            }
        }
    } else {
        cout << "Размерность массива меньше 10-ти" << endl;
    }

}

void split(string str, char del, string* list) {
      string temp = "";
      int j = 0;
  
      for (int i = 0; i < (int)str.size(); i++) {

        if (str[i] != del && i != (int)str.size() - 1) {
            temp += str[i];
        } else {
            list[j] = temp;
            temp = "";
            j++;
        }
    }
      
}

void get_data(string name_of_file, Passport** elements, int m = 10) {
    string string_item;

    ifstream input_name;
    input_name.open(name_of_file);
    for (int i = 0; i < m; i++) {
        getline(input_name, string_item);
        string key_arr[5];
        split(string_item, ' ', key_arr);

        elements[i] = new Passport(stoi(key_arr[0]), stoi(key_arr[1]), key_arr[2], key_arr[3], key_arr[4], i);

    }
    input_name.close();
}

void set_data(string name_of_file, Passport** elements, double time, int m = 10) {
     
    std::ofstream output;
    output.open(name_of_file);
    if (output.is_open()) {
        for (int i = 0; i < m; i++) {
            output << elements[i]->series << ' ' << elements[i]->number << ' ' << elements[i]->name << ' ' << elements[i]->surname << ' ' << elements[i]->patronymic << ' ' << elements[i]->line_number << endl;
        }
        output << time << endl;
    }
    output.close(); 
}



int main() {
    string path_to_input_file = "inputs/input_random.txt";
    int n = 10000;

    auto** array = new Passport*[1000000];
    get_data(path_to_input_file, array, n);

    clock_t start = clock();

    selection_sort(array, n);

    clock_t end = clock();
    double seconds = (double)(end - start) / CLOCKS_PER_SEC; 

    set_data("outputs/output_selection.txt", array, seconds, n);
    
    get_data(path_to_input_file, array, n);

    start = clock();

    shell_sort(array, n);

    end = clock();
    seconds = (double)(end - start) / CLOCKS_PER_SEC; 

    set_data("outputs/output_shell.txt", array, seconds, n);

    return 0;
}