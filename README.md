## Contest tester
This is a simple framework for writing your own tests for programming contests and run them automatically. 
### Usage
1. Create a directory with your tests. It should be named `tests/` and contain files with the following format: `tests-N.txt` where N is a number of the task. For example, `tests-1.txt` for tests for task 1.
2. In each file, write your tests in the following format (`[x]` - x is variable): 
    ```
    -- [test_name] [test] in
    ... (test lines)
    -- out
    ... (expected output)
    ```
   For example (program that prints the sum of two numbers):
    ```
    -- test 1 in
    1 2
    -- out
    3
    -- test 2 in
    2 4
    -- out
    6
    ```
3. Create a file `main.cpp` and paste framework code into it. You can also use `main.cpp` from this repository.
4. Write your solution in `Task::Solve` and compile it. 
5. If you want to run your tests, set `is_debug` variable in `main` function to true and run your program. If you want to submit your solution, set `is_debug` variable to false. To specify task number, set `task_number` variable in `main` function.

### Example
You can find full code in `main.cpp` file in this repository. This is just a simple example of how to use this framework. This program calculates the sum of two numbers.
```cpp
class Task : public Solution {
 public:
  explicit Task(bool is_debug, int task_num) : Solution(is_debug, task_num) {}

 private:
#ifndef SOLUTION // Write your solution here. Do not change the code above. (ifndef just for prettier code in the editor)

  void Solve() override {
    int x, y;
    *in >> x >> y;
    *out << x + y;
  }

#endif // SOLUTION

};

int main() {
  bool is_debug = true;
  int task_num = 1;

  /// Do not change code below. Implementation of the solution is in the Task class.
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  Task task(is_debug, task_num);
  task.Run();
  /// Do not change code above.

  return 0;
}
```
`tests/tests-1.txt`:
```
-- test 1 in
1 2
-- out
3
-- test 2 in
2 4
-- out
6
```

### Contributing
If you have any ideas or suggestions, feel free to create an issue or pull request.