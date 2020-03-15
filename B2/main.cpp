#include <iostream>

void task1();
void task2();

int main(int argc, char * argv[])
{
  if (argc != 2) {
    std::cerr << "Incorrect number of arguments\n";
    return 1;
  }

  try {
    const int task = std::stoi(argv[1]);

    switch (task) {
    case 1:
      {
        task1();
        break;
      }

    case 2:
      {
        task2();
        break;
      }

    default:
      {
        std::cerr << "Incorrect task number\n";
        return 1;
      }
    }

  } catch (const std::exception &e) {
    std::cerr << "error occurred: " << e.what() << "\n";
    return 1;
  }

  return 0;
}
