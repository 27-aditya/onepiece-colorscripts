#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <random>
#include <algorithm>
#include <vector>

using namespace std;
namespace fs = filesystem;

class ShipDisplay {
private:
    string program_dir;
    string ships_dir;
    random_device rd;
    mt19937 gen;
    vector<string> ships_list;

    string get_install_dir() {
        return "/usr/local/opt/onepiece-colorscripts";
    }

    void init_paths() {
        program_dir = get_install_dir();
        ships_dir = program_dir + "/colorscripts";
    }

    void print_file(const string& file_path) {
        ifstream file(file_path);
        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                cout << line << endl;
            }
        } else {
            throw runtime_error("Unable to open file: " + file_path);
        }
    }

    void load_all_ships() {
        ships_list = {
            "baratie", 
            "oro_jackson", 
            "blackbeard's_raft", 
            "moby_dick", 
            "going_merry", 
            "thousand_sunny", 
            "luffy's_boat", 
            "sea_train", 
            "snapper_head", 
            "victoria_punk", 
            "striker", 
            "thriller_bark", 
            "borsalino", 
            "flying_dutchman", 
            "garp's_warship", 
            "germa_66_floating_fortress", 
            "hawkins_ship", 
            "hitsugibune", 
            "laboon", 
            "marine's_warship", 
            "maxim", 
            "miss_love_duck", 
            "nostra_castello", 
            "numancia_flamingo", 
            "perfume_yuda", 
            "polar_tang", 
            "queen_mama_chanter", 
            "zunesha"
        };
    }

public:
    ShipDisplay(const string& program_path) : gen(rd()) {
        init_paths();
        load_all_ships();
    }

    void list_ships() {
        cout << "Available Ships: " << endl;
        for (const auto& ship : ships_list) {
            cout << ship << endl;
        }
    }

    void show_random_ship() {
        uniform_int_distribution<> dist(0, ships_list.size() - 1);
        string random_ship = ships_list[dist(gen)];
        string ship_file = ships_dir + "/" + random_ship;
        try {
            print_file(ship_file);
        } catch (const exception& e) {
            cerr << "Error displaying the file: " << e.what() << endl;
        }
    }

    void show_specific_ship(const string& ship_name) {
        auto it = find(ships_list.begin(), ships_list.end(), ship_name);
        if (it == ships_list.end()) {
            throw runtime_error("Invalid ship name: " + ship_name);
        }
        string ship_file = ships_dir + "/" + ship_name;
        try {
            print_file(ship_file);
        } catch (const exception& e) {
            cerr << "Error displaying the file: " << e.what() << endl;
        }
    }
};

int main(int argc, char* argv[]) {
    try {
        ShipDisplay display(argv[0]);
        if (argc > 1) {
            string arg = argv[1];
            if (arg == "--list" || arg == "-l") {
                display.list_ships();
            } else if (arg == "--name" || arg == "-n") {
                if (argc < 3) {
                    cout << "Please provide a ship name" << endl;
                    return 1;
                }
                display.show_specific_ship(argv[2]);
            } else {
                cout << "Usage: " << endl
                     << "  --list (-l): List all available ships" << endl
                     << "  --name (-n) <ship_name>: Show specific ship" << endl
                     << "  No arguments: Show random ship" << endl;
            }
        } else {
            display.show_random_ship();
        }
        return 0;
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
}