#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <bits/stdc++.h>
using namespace std;

struct Course {
    string name;
    vector<string> prerequisites;
};

// Function to add a course and its prerequisites to the course list
void addCourse(unordered_map<string, Course>& courses, const string& name, const vector<string>& prerequisites) {
    courses[name] = {name, prerequisites};
}

// Function to input course data from the user
void inputCourses(unordered_map<string, Course>& courses) {
    int numCourses;
    cout << "Enter the number of courses: ";
    cin >> numCourses;
    cin.ignore(); // Ignore newline character from previous input

    for (int i = 0; i < numCourses; ++i) {
        string name;
        cout << "Enter the name of course " << i + 1 << ": ";
        getline(cin, name);

        int numPrerequisites;
        cout << "Enter the number of prerequisites for " << name << ": ";
        cin >> numPrerequisites;
        cin.ignore(); // Ignore newline character from previous input

        vector<string> prerequisites;
        for (int j = 0; j < numPrerequisites; ++j) {
            string prerequisite;
            cout << "Enter prerequisite " << j + 1 << " for " << name << ": ";
            getline(cin, prerequisite);
            prerequisites.push_back(prerequisite);
        }

        addCourse(courses, name, prerequisites);
    }
}

bool topologicalSortDFS(const string& course, unordered_map<string, Course>& courses, unordered_map<string, bool>& visited, vector<string>& schedule) {
    // If the course is already visited, there's no need to visit it again
    if (visited[course])
        return true;

    visited[course] = true;

    for (const string& prerequisite : courses[course].prerequisites) {
        if (!topologicalSortDFS(prerequisite, courses, visited, schedule)) {
            // If a prerequisite cannot be taken, the course cannot be taken either
            return false;
        }
    }

    // All prerequisites are satisfied, add the course to the schedule
    schedule.push_back(course);
    return true;
}

vector<string> topologicalSort(unordered_map<string, Course>& courses) {
    vector<string> schedule;
    unordered_map<string, bool> visited;

    for (const auto& entry : courses) {
        const string& course = entry.first;
        if (!visited[course]) {
            if (!topologicalSortDFS(course, courses, visited, schedule)) {
                // Cycle detected, cannot create a valid schedule
                schedule.clear();
                return schedule;
            }
        }
    }

    // Reverse the order to get the correct schedule (topological order)
    //reverse(schedule.begin(), schedule.end());
    return schedule;
}

int main() {
    unordered_map<string, Course> courses;
    inputCourses(courses);

    vector<string> schedule = topologicalSort(courses);

    if (schedule.empty()) {
        cout << "Cycle detected. Cannot create a valid course schedule." << endl;
    } else {
        cout << "Feasible course schedule:" << endl;
        for (const string& course : schedule) {
            cout << course << endl;
        }
    }

    return 0;
}
