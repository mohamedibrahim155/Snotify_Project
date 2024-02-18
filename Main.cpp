
#include "Utils/List.h"
#include "Snotify/cMusicGenerator.h"
int main()
{
	List<int> test;

	test.Add(10);
	test.Add(20);
	test.Add(30);
	test.Add(20);
	test.Add(20);

	for (size_t i = 0; i < test.GetLength(); i++)
	{
		std::cout << " Added : " << test[i] << std::endl;

	}
 
  test.Remove(20);
  test.Remove(20);

  int value = test.GetAt(1);
  std::cout << "Value : " << value << std::endl;
  for (size_t i = 0; i < test.GetLength(); i++)
  {
	  std::cout << "Current list i : " << test[i] << std::endl;
  }

	return 0;
}