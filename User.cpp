#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <ctime>

using namespace std;

class User {
    private:
        string username;
        int score;
        int time;

    public:
        User(string name = "", int sc = 0, int temp = 0) : username(name), score(sc), time(temp) {}

        void setUsername(string name) {
            username = name;
        }

        string getUsername() const {
            return username;
        }

        void setScore(int sc) {
            score = sc;
        }

        int getScore() const {
            return score;
        }

        void setTime(int temp) {
            time = temp;
        }

        int getTime() const {
            return time;
        }

        void showUser() const {
            cout << "Username: " << username << endl;
            cout << "Score: " << score << endl;
            cout << "Temp: " << time << endl;
        }
};

class UserController {
    private:
        static int userIDCounter;
        static vector<User> userList;

    public:
        static User createUser(string name, int score, int time) {
            return User(name, score, time);
        }

        static void readUsers() {
            ifstream file("users.txt");
            if (file.is_open()) {
                string line;
                while (getline(file, line)) {
                    if (!line.empty()) {
                        int id, score, timeUser;
                        string username;
                        stringstream ss(line);
                        string temp;
                        ss >> temp >> id >> temp >> temp >> username >> temp >> score >> temp >> temp >> timeUser;

                        cout<<"===========>"<<timeUser<<endl;
                        User newUser(username, score, timeUser);
                        userList.push_back(newUser);
                    }
                }
                file.close();
            } else {
                cerr << "Unable to open file for reading!" << endl;
            }
        }

        static void updateUser(User& user, string name, int score, int time) {
            user.setUsername(name);
            user.setScore(score);
            user.setTime(time);
        }

        static void saveUser(const User& user) {
            ofstream file("users.txt", ios::app);
            if (file.is_open()) {
                time_t now = time(0);
                tm* ltm = localtime(&now);
                file << "    " << ++userIDCounter << ",           " << user.getUsername() << ",        " <<  user.getTime() << ",       " << user.getScore() ;
                file << ",       " << ltm->tm_mday << "-" << 1 + ltm->tm_mon << "-" << 1900 + ltm->tm_year << endl;
                file.close();
            } else {
                cerr << "Unable to open file for writing!" << endl;
            }
        }

        static void displayUsers() {
            if (userList.empty()) {
                cout << "User list is empty." << endl;
                return;
            }

            for (const auto& user : userList) {
                user.showUser();
            }
        }
};

// Définition de la variable statique userList
vector<User> UserController::userList;

// Définition de la variable statique userIDCounter
int UserController::userIDCounter = 0;
