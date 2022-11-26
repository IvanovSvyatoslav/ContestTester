#include <iostream>
#include <sstream>
#include <fstream>

/// @brief Base abstract class for all solutions.
/// @details You should inherit from this class and implement Solve() method.
/// Do not change this class.
class Solution {

 public:
  /// @brief Constructor.
  /// @param is_debug - if true, then the program will read the input from the file (tests/tests-{task_num}.txt).
  /// @param task_num - the number of the task. It is used get the name of the tests file.
  explicit Solution(bool is_debug, int task_num) : is_debug_(is_debug), task_num_(task_num) {
    if (is_debug_) {
      std::cout << "Task: " << task_num_ << std::endl;
      out = new std::ostringstream();
      in = new std::ifstream("tests/tests-" + std::to_string(task_num_) + ".txt");
      if (!*in) {
        std::cout << "file not found" << std::endl;
        exit(1);
      }
    } else {
      out = &std::cout;
      in = &std::cin;
    }
  }

  /// @brief Rule of five.
  Solution(const Solution&) = delete;
  Solution(Solution&&) = delete;
  Solution& operator=(const Solution&) = delete;
  Solution& operator=(Solution&&) = delete;
  ~Solution() {
    if (is_debug_) {
      delete out;
      delete in;
    }
  }

  /// @brief Method to run testing or solving
  void Run() {
    if (is_debug_) {
      while (!in->eof()) {
        Test in_test;
        GetInputHeader(in_test);
        SkipLine();

        Solve();

        GetOutputHeader(in_test.id);
        SkipLine();

        auto out_oss = dynamic_cast<std::ostringstream*>(out);
        if (!out_oss) {
          throw std::runtime_error("out is not ostringstream");
        }
        std::istringstream result_iss(out_oss->str());

        std::string result, expected;
        bool is_ok = true;
        while (std::getline(result_iss, result)) {
          std::getline(*in, expected);
          if (result != expected) {
            std::cout << "test #" << in_test.id << " collapsed" << std::endl;
            std::cout << "expected: " << expected << std::endl;
            std::cout << "result: " << result << std::endl;
            is_ok = false;
          }
        }
        if (is_ok) {
          std::cout << "test #" << in_test.id << " passed" << std::endl;
        }
        out_oss->str("");
      }
    } else {
      Solve();
    }
  }
 protected:
  /// @brief Method for user solution
  virtual void Solve() = 0;
  std::istream* in;
  std::ostream* out;

 private:
  /// @brief Structure for test containing test name and test id.
  struct Test {
    std::string name;
    int id;
  };

  /// @brief Is solution in debug mode(reading from file) or not(reading from stdin)
  bool is_debug_;
  /// @brief Number of task
  int task_num_;

  /// @brief Get header of input test. Format: "--test_name test_id in"
  /// @param test - variable for storing test name and id
  void GetInputHeader(Test& test) {
    std::string in_sticks;
    *in >> in_sticks;
    std::string test_name;
    *in >> test_name;
    int test_id;
    *in >> test_id;
    std::string in_string;
    *in >> in_string;
    if (in_string != "in") {
      std::cout << "test #" << test_id << " collapsed" << std::endl;
      throw std::runtime_error("input file is corrupted: " + std::to_string(test_id) + " " + "collapsed");
    }
    test.name = test_name;
    test.id = test_id;
  }

  /// @brief Get header of output test. Format: "-- out"
  /// @param test_id - id of test (to print in case of error)
  void GetOutputHeader(int test_id) {
    std::string out_sticks;
    *in >> out_sticks;
    std::string out_string;
    *in >> out_string;
    if (out_string != "out" || out_sticks != "--") {
      std::cout << "test #" << test_id << " collapsed" << std::endl;
      return;
    }
  }

  /// @brief Method for skipping line in input
  void SkipLine() {
    std::string line;
    std::getline(*in, line);
  }
};


/// @brief Usings for convenience
using namespace std;
using ll = long long;

/// @brief Class to solve the problem.
/// @details You can write your solution in the Solve() method.
/// Get example input and output in the tests directory.
class Task : public Solution {
 public:
  /// @brief Constructor.
  /// @param is_debug - if true, then the program will read the input from the file (tests/tests-{task_num}.txt).
  /// @param task_num - the number of the task. It is used get the name of the tests file.
  explicit Task(bool is_debug, int task_num) : Solution(is_debug, task_num) {}

 private:
#ifndef SOLUTION // Write your solution here. Do not change the code above. (ifndef just for prettier code in the editor)

  /// @brief The main method where the solution is written.
  void Solve() override {
    int n;
    *in >> n;
    *out << n;
  }

#endif // SOLUTION

};

int main() {
  /// User configurable code

  /// @brief If you want to run the program in debug mode, then set the variable is_debug to true.
  bool is_debug = true;
  /// @brief The number of the task. It is used get the name of the tests file.
  int task_num = 1;

  /// End of user configurable code

  /// Do not change code below. Implementation of the solution is in the Task class.
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  Task task(is_debug, task_num);
  task.Run();
  /// Do not change code above.

  return 0;
}
